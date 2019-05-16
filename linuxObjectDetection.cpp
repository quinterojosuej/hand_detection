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
    ///if( !face_cascade.load( face_cascade_name ) )

    if( !hand_cascade.load( "aGest.xml" ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };

    //int camera_device = parser.get<int>("camera");
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

///updatable variables

///int initial_x_detected;
std::vector<Rect> initial_x_detected;


bool is_initial_detected = false;
int secondary_x_detected;
int secondary_y_detected;

bool horizontal_shift = false;
int tertiary_x_detected;
int tertiary_y_detected;

///function usage
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

///function usage
void corresponding_program(int third_x, int framewidth)
{
	// for the left it is firefox, for the right it is terminal
	if( third_x < framewidth *.5 )
	{
		system("firefox");
		cout << "FIREFOX"<< endl;
	}
	else
	{
		system("gnome-terminal");
		cout << "TERMINAL" << endl;
	}
}


///function usage
void third_object_shift_correctly(int second_y, int third_y, int frameheight, int framewidth, int third_x)
{
	if(third_y > second_y + frameheight * .1)
	{
		corresponding_program( third_x, framewidth);
	}
}
///function usage
int initial_looper(int the_counter)
{
	return(initial_x_detected[the_counter].x);
}



int counter = 0;

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    ///equalizeHist( frame_gray, frame_gray );

    //-- Detect
    std::vector<Rect> gests;
    hand_cascade.detectMultiScale( frame_gray, gests, 1.1, 0, 0, Size(30,30), Size(300,300) );
    if(counter == 10)
    {
	counter = 0;
	cout << "~~~~~~~~~~~~~~~~~~~~~~";
    }
    cout << counter << endl;
    counter++;

    for ( size_t i = 0; i < gests.size(); i++ )
    {
        Point center( gests[i].x + gests[i].width/2, gests[i].y + gests[i].height/2 );

	if(gests[i].x < .33 *frame_gray.size().width || gests[i].x > .66 *frame_gray.size().width)
	{
//	cout << gests[i].x << "   ,    " << gests[i].y << endl;
//	cout << gests[i].size() << "-------------" << endl;
	
	if(counter == 1){	
	rectangle ( frame, gests[i], Scalar( 255, 0, 0 ), 5, 8, 0);

	if(horizontal_shift)
	{
		tertiary_x_detected = gests[i].x;
		tertiary_y_detected = gests[i].y;
		third_object_shift_correctly( secondary_y_detected , tertiary_y_detected, frame.size().height, frame.size().width, tertiary_x_detected );
	}
	
	if(is_initial_detected)
	{
		secondary_x_detected = gests[i].x;
		secondary_y_detected = gests[i].y;
		for( int x = 0; x < initial_x_detected.size(); x++)
		{
			if(horizontal_shift)
			{
				x = initial_x_detected.size();
			}
			else
			{
				second_object_shift_correctly( initial_looper(x), secondary_x_detected, frame.size().width );
			}
		}
		cout << "FOUND SECOND HAND!";
	}


	///this is the last possible thing
	if(i==0)
	{
	initial_x_detected = gests;
	is_initial_detected = true;
	cout << "FOUND HAND!" << endl;
	}
	
	}
    }
    }

    //-- Display camera feed and hand detections
    imshow( "Capture - Hand detection", frame );
}

