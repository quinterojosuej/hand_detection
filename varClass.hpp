#ifndef BOOLCLASS_HPP
#define BOOLCLASS_HPP

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

/// This function allows for boolean variables to be readily available 
// detail is in the implementation file
class BoolClass
{
	public:
		BoolClass();
		
		void Show();

		bool is_initial_detected;
		bool horizontal_shift;

		int secondary_x_detected;
                int secondary_y_detected;

                int tertiary_x_detected;
                int tertiary_y_detected;

};
#endif //BOOLCLASS_HPP
