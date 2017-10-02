#include "Joystick.h"
#include <windows.h>
void Joystick::isConnected()
{
	if (sf::Joystick::isConnected(0))
	{
		std::cout << "Joystick 0 is connected" << std::endl;
		unsigned int buttonCount = sf::Joystick::getButtonCount(0);
		std::cout << "Button Count: " << buttonCount << std::endl;
		bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);
		if (hasZ)
		{
			std::cout << "Joy 0 has Z axis funtionality" << std::endl;
		}
		else
		{
			std::cout << "Joy 0 has NO Z axis funtionality" << std::endl;
		}
	}
}
void Joystick::processEvents()
{
	// is button i of joystick number 0 pressed?
	for (int i = 0; i < 10; i++)
	{
		if (sf::Joystick::isButtonPressed(0, i))
		{
			std::cout << "Button " << i << " was pressed ! " << std::endl;
			Sleep(400); // just to space out time between presses
			break;
		}
	}

	float x = (sf::Joystick::getAxisPosition(0, sf::Joystick::X));
	float y = (sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
	std::cout << x << " " << y << std::endl;
	//character.move(x,y);

}