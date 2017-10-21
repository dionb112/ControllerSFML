#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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
	bool LB = false;
	bool RB = false;
	bool LeftThumbClick = false;
	bool RightThumbClick = false;
	bool DpadUp = false;
	bool DpadDown = false;
	bool DpadLeft = false;
	bool DpadRight = false;
	bool Start = false;
	float RTrigger = 0;
	float LTrigger = 0;
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
	//index count for multiple controllers if connected 
	int sf_Joystick_index;
	//the current state of all the buttons
	GamePadState m_currState;
	//the previous state to use to check  for the	instant a button is pressed
	GamePadState m_lastState;

	sf::Font m_font;
	sf::Sprite m_backGround;
	sf::Texture m_texture;
	sf::Text m_lastPressed;

	sf::Text m_aPressed;
	sf::Text m_bPressed;
	sf::Text m_xPressed;
	sf::Text m_yPressed;
	sf::Text m_lbPressed;
	sf::Text m_rbPressed;
	sf::Text m_startPressed;
	sf::Text m_rsX;
	sf::Text m_rsY;
	sf::Text m_lsX;
	sf::Text m_lsY;
	sf::Text m_lTriggerCoord;
	sf::Text m_rTriggerCoord;
	sf::Text m_dPadUpPressed;
	sf::Text m_dPadDownPressed;
	sf::Text m_dPadLeftPressed;
	sf::Text m_dPadRightPressed;



	//deadzone for the 'dpad'
	const int dpadThreshold = 50;
	sf::RenderWindow m_window;

	void update();
	void isConnected();
	void connect();
	void processEvents();
	void render();
	void setLast();
	void setText(sf::Text &text, int scalar);
public:
	Xbox360Controller();
	~Xbox360Controller();
	void run();

};