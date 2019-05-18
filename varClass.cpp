#include "varClass.hpp"

BoolClass::BoolClass()
{
	is_initial_detected = false;
	horizontal_shift = false;
}

void BoolClass::Show()
{
	cout << "The following is the current state of detection" <<endl;
	cout << "===============================================" << endl;

	if (is_initial_detected)
	{
	cout << "The first hand has being detected" << endl;
	}
	else
	{
	cout << "Nothing is yet to be detected" << endl;
	}
	
	if (horizontal_shift)
	{
	cout << "There has being a confirmed horizontal shift" << endl;


	cout << "The coordinates for the vertical shift are at: " <<endl;
	cout << "Secondary hand: is at x: " << secondary_x_detected;
	cout << " y: " << secondary_y_detected << endl;

	cout << "Tertiary hand: is at x: " << tertiary_x_detected;
	cout << " y: " << tertiary_y_detected << endl;
	}
	else 
	{
	cout << "No confirmed horizontal shift" << endl;
	}
	
	if (secondary_y_detected +50 < tertiary_y_detected)
	{
	cout << "There should have being an activation" << endl;
	}
	else
	{
	cout << "No confirmed activation detected" << endl;
	}
}
