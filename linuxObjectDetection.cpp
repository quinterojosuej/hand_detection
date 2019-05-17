/*
Created by Jose Caudillo, Brenda Jacobo, Kevin Piffero and Jonathan Quintero
Date: 5/18/19
Hand Detection program that allows for a specified gesture, see video or gifs, 
to open certain programs already present in the system. Using OpenCV and System 
commands on c++.
*/
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

bool dummy;
int dummyy;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
CascadeClassifier hand_cascade;

/** @function main */
int main( int argc, const char** argv )
{

    //-- 1. Load the cascades

    if( !hand_cascade.load( "aGest.xml" ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };

    VideoCapture capture;
    
    //-- 2. Read the video stream
    
    capture.open( 0 );
    if ( ! capture.isOpened() )
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }

    Mat frame;
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );

        if( waitKey(10) == 27 )
        {
            break; // escape
        }
    }
    return 0;
}

///This vector is for duplicating the first hand detections
std::vector<Rect> initial_x_detected;

///is_initial_detected is for finding first objects
bool is_initial_detected = false;
///the following variables store the locations of the second detected objects
int secondary_x_detected;
int secondary_y_detected;

///horizontal_shift is used to verify that there was a horizontal shift
bool horizontal_shift = false;
///the following variables store the data location of the final detection 
int tertiary_x_detected;
int tertiary_y_detected;

/// The function obtains the data regarding two hands detected
// and determines whether or not there was a shift on the corresponding hands
// in regards to the location of the hand. If there was a true horizontal shift
// then horizontal_shift = true, else horizontal_shift = false.
void second_object_shift_correctly(int first_x, int second_x, int frame_size)
{

	if(first_x >= frame_size*.66)
    {
        if(second_x > first_x)
        {
            horizontal_shift = true;
        }
        else
        {
            horizontal_shift = false;
        }
    }
    if(first_x <= frame_size*.33)
    {
        if(second_x < first_x)
        {
            horizontal_shift = true;
        }
        else
        {
            horizontal_shift = false;
        }
    }
}

/// The following function activates the corresponding app on whether the last
// location of the final activation was on either the left or right side of the 
// total screen
void corresponding_program(int third_x, int framewidth)
{
	// for the left it is firefox 
	if( third_x < framewidth *.5 )
	{
		system("firefox");
		cout << "FIREFOX"<< endl;
	}
	// for the right it is terminal
	else
	{
		system("gnome-terminal");
		cout << "TERMINAL" << endl;
	}
}


/// The following function determines whether there was a vertical shift after
// the horizontal shift was confirmed. If there was a shift with a definite movement
// then the corresponding_program function gets called. 
void third_object_shift_correctly(int second_y, int third_y, int frameheight, int framewidth, int third_x)
{
	if(third_y > second_y + frameheight * .1)
	{
		corresponding_program( third_x, framewidth);
	}
}

/// Simply returns the value of the duplicated vector's data of hand-objects detected
// makes more on an eye pleasing look.
int initial_looper(int the_counter)
{
	return(initial_x_detected[the_counter].x);
}

/// This counter deals with the fact that the frames only
// detect hand objects every 10 frames. This just 
// initializes it
int counter = 0;

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    Mat frame_gray;
    // Allows for color change to occur and aid the detection process
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    /// equalizeHist( frame_gray, frame_gray ); // If used then detection rate decreases

    //The following places the frame's data into a vector
    std::vector<Rect> gests;
    //This function determines whether an object is present or not and pushes to the vector gests
    hand_cascade.detectMultiScale( frame_gray, gests, 1.1, 0, 0, Size(30,30), Size(300,300) );
    if(counter == 10)
    {
	counter = 0;
	cout << "~~~~~~~~~~~~~~~~~~~~~~";
    }
    //The counter is printed to show the rate at which detection occurs
    //otherwise is optional. THE COUNTER IS NOT OPTIONAL.
    cout << counter << endl;
    counter++;

    //The for loop uses the vector to cycle through all of the detections
    for ( size_t i = 0; i < gests.size(); i++ )
    {
	//For development a box is created around the hand-obect that are detected
        Point center( gests[i].x + gests[i].width/2, gests[i].y + gests[i].height/2 );
	
	//This if allows for a 'death zone' to not have beards or shadws activate the program
	if(gests[i].x < .33 *frame_gray.size().width || gests[i].x > .66 *frame_gray.size().width)
	{
	
	// This if allows for only frame data of every 10 frames to be used	
	if(counter == 1){	
	
	//	cout << gests[i].x << "   ,    " << gests[i].y << endl; 
	// for development purposes, prints coordinates of the objects
	//      cout << gests[i].size() << "-------------" << endl;
	
	//This will create a rectangle around the hand-objects created
	rectangle ( frame, gests[i], Scalar( 255, 0, 0 ), 5, 8, 0);

	//If there is a confirmed horizontal_shift then a new objects are 
	//tried to see if a confirmed third_object_shift_correctly
	//occurs
	if(horizontal_shift)
	{
		tertiary_x_detected = gests[i].x;
		tertiary_y_detected = gests[i].y;
		third_object_shift_correctly( secondary_y_detected , tertiary_y_detected, frame.size().height, frame.size().width, tertiary_x_detected );
		i = gests.size();
	}
	//If there was an initial objects than have the new detections
	//be compared with the initial detections. If so then horizontal_shift = true
	//making it so that the loop stops. Maintains the values for those that made 
	//the horizontal_shift = true. Else keeps it as false.
	if(is_initial_detected)
	{
		secondary_x_detected = gests[i].x;
		secondary_y_detected = gests[i].y;
		for( int x = 0; x < initial_x_detected.size(); x++)
		{
			if(horizontal_shift)
			{
				x = initial_x_detected.size();
				i = gests.size();
			}
			else
			{
				second_object_shift_correctly( initial_looper(x), secondary_x_detected, frame.size().width );
			}
		}
		cout << "FOUND SECOND HAND!";
	}

	///The last possible event is that there were objects detected. If 
	//there were, then they are stored in another vector for comparison
	//in the horizontal shift 
	if(i==0)
	{
	initial_x_detected = gests;
	is_initial_detected = true;
	cout << "FOUND HAND!" << endl;
	}
	
	}
    }
    }

    //Display camera feed and hand detections, really optional. Just needed for 
    //demos and development.
    imshow( "Capture - Hand detection", frame );
}

