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

		bool is_initial_detected;

		bool horizontal_shift;

};
#endif //BOOLCLASS_HPP
