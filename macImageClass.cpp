#include "macImageClass.hpp"
// This function comprises all of the logic required for the 
// corresponding functions to activate.

ImageClass::ImageClass()
{
	// Initializes variables accordingly
	vals.secondary_x_detected = 0;
	vals.secondary_y_detected = 0;

	vals.tertiary_x_detected = 0;
	vals.tertiary_y_detected = 0;
}
void ImageClass::second_object_shift_correctly(int first_x, int second_x, int frame_size)
{
	// Determines whether there was an hand-object horizontal shift
	if(first_x >= frame_size*.66)
    {
        if(second_x > first_x)
        {
            vals.horizontal_shift = true;
        }
        else
        {
            vals.horizontal_shift = false;
        }
    }
    if(first_x <= frame_size*.33)
    {
        if(second_x < first_x)
        {
            vals.horizontal_shift = true;
        }
        else
        {
            vals.horizontal_shift = false;
        }
    }
}

void ImageClass::corresponding_program( int third_x , int frame_size)
{
	// for the left it is firefox 
	if( third_x < frame_size *.5 )
	{
		system("open -a slack");
		cout << "SLACK"<< endl;
	}
	// for the right it is terminal
	else
	{
		system("open -a safari");
		cout << "SAFARI" << endl;
	}
}

void ImageClass::third_object_shift_correctly(int second_y, int third_y, int frameheight, int framewidth, int third_x)
{
	// If there was a vertical shift then activate 
	// the corresponding program
	if(third_y > second_y + frameheight * .1)
	{
		corresponding_program( third_x, framewidth);
	}
}

int ImageClass::initial_looper(int the_counter)
{
	// Returns the data of the vector
	return (vect.initial_x_detected[the_counter].x);
}
