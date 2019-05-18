#ifndef VECTORCLASS_HPP
#define VECTORCLASS_HPP

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


#include <iostream>

using namespace std;
using namespace cv;

/// This function allows for the duplicating vector to be readily available 
// detail is in the implementation file
class VectorClass
{
        public:
                VectorClass();
		void Show();
                std::vector<Rect> initial_x_detected;

};
#endif //IMAGECLASS_HPP

