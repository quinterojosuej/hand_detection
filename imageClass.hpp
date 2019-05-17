#ifndef IMAGECLASS_HPP
#define IMAGECLASS_HPP

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

/// This function allows for variables to be readily available 
// detail is in the implementation file
class ImageClass
{
	public:
		ImageClass();
		void second_object_shift_correctly(int first_x, int second_x, int frame_size);
		void corresponding_program(int third_x, int framewidth);
		void third_object_shift_correctly(int second_y, int third_y, int frameheight, int framewidth, int third_x);

		std::vector<Rect> initial_x_detected;

		int initial_looper(int the_counter);

		bool is_initial_detected;
		int secondary_x_detected;
		int secondary_y_detected;

		bool horizontal_shift;
		int tertiary_x_detected;
		int tertiary_y_detected;

};
#endif //IMAGECLASS_HPP
