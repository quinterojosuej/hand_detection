#include "vectorClass.hpp"

VectorClass::VectorClass()
{
	std::vector<Rect> initial_x_detected;
} 

void VectorClass::Show()
{
	cout << "The following are where the hand x coordinates were found" 
		<< "\n==============================";
	for( int i = 0; i<initial_x_detected.size(); i++)
	{
		cout << initial_x_detected[i].x;
	}
}
