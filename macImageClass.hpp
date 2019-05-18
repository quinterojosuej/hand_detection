#ifndef IMAGECLASS_HPP
#define IMAGECLASS_HPP

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "varClass.cpp"
#include "vectorClass.cpp"
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
		int initial_looper(int the_counter);

		BoolClass vals;
		VectorClass vect;


};
#endif //IMAGECLASS_HPP
