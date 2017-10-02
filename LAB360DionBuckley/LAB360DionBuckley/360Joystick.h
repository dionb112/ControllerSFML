#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
/// <summary>
/// data storing current state of controller
/// </summary>
struct GamePadState
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbClick;
	bool RightThumbClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;
	bool Back;
	bool Xbox;
	float RTrigger;
	float LTrigger;
	sf::Vector2f RightThumbStick;
	sf::Vector2f LeftThumbStick;

	void reset();
};

/// <summary>
/// Xbox controller class to query state of controller to mimic the controller states, similar to XNA
/// </summary>
class Xbox360Controller
{
private:
	//deadzone for the 'dpad'
	const int dpadThreshold = 50;
	sf::RenderWindow m_window;
public:
	//index count for multiple controllers if connected 
	int sf_Joystick_index;
	//the current state of all the buttons
	GamePadState m_currState;
	//the previous state to use to check  for the	instant a button is pressed
	GamePadState m_prevState;

	Xbox360Controller();
	~Xbox360Controller();
	void run();
	void update();
	void isConnected();
	void connect();
	void processEvents();
	void render();
};