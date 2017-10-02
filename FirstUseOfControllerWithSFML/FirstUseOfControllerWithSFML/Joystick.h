#pragma once
#include <SFML\Window\Joystick.hpp>
#include <iostream>

class Joystick {
private:

public:
	void isConnected();
	void processEvents();
};