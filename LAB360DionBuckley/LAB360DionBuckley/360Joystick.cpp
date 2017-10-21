#include "360Joystick.h"

Xbox360Controller::Xbox360Controller() : m_window{ sf::VideoMode{ 900,600,32 }, "360 Controller with SFML!" }
{
	m_currState.reset();
	m_lastState.reset();

	if (!m_texture.loadFromFile("IMAGES/controller.jpg"))
	{
		std::cout << "Error loading texture";
	}
	if (!m_font.loadFromFile("FONTS/ariblk.ttf"))
	{
		std::cout << "Error loading font";
	}
	m_backGround.setTexture(m_texture);
	setText(m_aPressed, 0);
	setText(m_bPressed, 1);
	setText(m_xPressed, 2);
	setText(m_yPressed, 3);

	//using the text stup function for all the characteristics, then manually setting position
	setText(m_startPressed, 0);
	setText(m_rbPressed, 0);
	setText(m_lbPressed, 0);
	m_startPressed.setPosition(sf::Vector2f{ 755,500 });
	m_rbPressed.setPosition(sf::Vector2f{ 700,125 });
	m_lbPressed.setPosition(sf::Vector2f{ 15,125 });

	setText(m_lsX, 0);
	setText(m_lsY, 0);
	setText(m_rsX, 0);
	setText(m_rsY, 0);
	setText(m_lTriggerCoord, 0);
	setText(m_rTriggerCoord, 0);
	m_lsX.setPosition(20, 200);
	m_lsY.setPosition(20, 225);
	m_rsX.setPosition(525, 525);
	m_rsY.setPosition(525, 550);
	m_lTriggerCoord.setPosition(225, 28);
	m_rTriggerCoord.setPosition(600, 25);
	m_lsX.setString(std::to_string(static_cast<float>(m_currState.LeftThumbStick.x)));
	m_lsY.setString(std::to_string(static_cast<float>(m_currState.LeftThumbStick.y)));
	m_rsX.setString(std::to_string(static_cast<float>(m_currState.RightThumbStick.x)));
	m_rsY.setString(std::to_string(static_cast<float>(m_currState.LeftThumbStick.y)));
	m_lTriggerCoord.setString(std::to_string(static_cast<float>(m_currState.LTrigger)));
	m_rTriggerCoord.setString(std::to_string(static_cast<float>(m_currState.RTrigger)));

	setText(m_dPadLeftPressed, 0);
	setText(m_dPadRightPressed, 0);
	setText(m_dPadUpPressed, 0);
	setText(m_dPadDownPressed, 0);
	m_dPadLeftPressed.setPosition(250, 525);
	m_dPadRightPressed.setPosition(365, 525);
	m_dPadUpPressed.setPosition(360, 475);
	m_dPadDownPressed.setPosition(300, 550);
	m_dPadLeftPressed.setString("Left");
	m_dPadRightPressed.setString("Right");
	m_dPadDownPressed.setString("Down");
	m_dPadUpPressed.setString("UP");


	
	m_lastPressed.setString("Last Face Button Pressed: ");
	m_lastPressed.setFont(m_font);
	m_lastPressed.setPosition(600, 200);
	m_lastPressed.setFillColor(sf::Color::Black);
	m_lastPressed.setCharacterSize(15);
}

Xbox360Controller::~Xbox360Controller()
{
}

void Xbox360Controller::run()
{
	isConnected();
	sf::Clock clock;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceUpdate = sf::Time::Zero;
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceUpdate += clock.restart();
		while (timeSinceUpdate > timePerFrame)
		{
			processEvents();
			timeSinceUpdate -= timePerFrame;
			update();
		}
		render();
	}
}

void Xbox360Controller::update()
{
	setLast();
}

void Xbox360Controller::isConnected()
{
	if (sf::Joystick::isConnected(0))
	{
		std::cout << "Joystick 0 is connected" << std::endl;
	}
}

void Xbox360Controller::connect()
{
}

void Xbox360Controller::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{

		if (event.type == sf::Event::JoystickMoved) // I have these external if statements so that we won't run through all the ifs unless that general event has taken place
		{
			//Dpad
			if (event.joystickMove.axis == sf::Joystick::Axis::PovX)
			{
				
				if (event.joystickMove.position > dpadThreshold)
				{
					m_currState.DpadRight = true;
				}
				else if (event.joystickMove.position < -dpadThreshold)
				{
					m_currState.DpadLeft = true;
				}
				else
				{
					m_currState.DpadRight = false;
					m_currState.DpadLeft = false;
				}
			}
			if (event.joystickMove.axis == sf::Joystick::Axis::PovY)
			{
				if (event.joystickMove.position > dpadThreshold)
				{
					m_currState.DpadUp = true;
				}
				else if (event.joystickMove.position < -dpadThreshold)
				{
					m_currState.DpadDown = true;
				}
				else
				{
					m_currState.DpadUp = false;
					m_currState.DpadDown = false;
				}
			}

			//Right Thumb Stick
			if (event.joystickMove.axis == sf::Joystick::Axis::U)
			{
				m_currState.RightThumbStick.x = event.joystickMove.position;
				m_rsX.setString(std::to_string(static_cast<float>(m_currState.RightThumbStick.x)));
			}
			if (event.joystickMove.axis == sf::Joystick::Axis::R)
			{
				m_currState.RightThumbStick.y = event.joystickMove.position;
				m_rsY.setString(std::to_string(static_cast<float>(m_currState.RightThumbStick.y)));
			}

			//Left Thumb Stick
			if (event.joystickMove.axis == sf::Joystick::Axis::X)
			{
				m_currState.LeftThumbStick.x = event.joystickMove.position;
				m_lsX.setString(std::to_string(static_cast<float>(m_currState.LeftThumbStick.x)));

			}
			if (event.joystickMove.axis == sf::Joystick::Axis::Y)
			{
				m_currState.LeftThumbStick.y = event.joystickMove.position;
				m_lsY.setString(std::to_string(static_cast<float>(m_currState.LeftThumbStick.y)));

			}

			//Left and Right Triggers
			if (event.joystickMove.axis == sf::Joystick::Axis::Z)
			{
				if (event.joystickMove.position <= 0)
				{
					m_currState.LTrigger = event.joystickMove.position;
					m_lTriggerCoord.setString(std::to_string(m_currState.LTrigger));
				}
				if (event.joystickMove.position >= 0)
				{
					m_currState.RTrigger = event.joystickMove.position;
					m_rTriggerCoord.setString(std::to_string(m_currState.RTrigger));
				}
			}
		}

		//Rest of buttons (Xbox is not counted as a button)
		if (sf::Event::JoystickButtonPressed == event.type)
		{
			switch (event.joystickButton.button)
			{
			case 0:
				m_currState.A = true;
				m_lastState.reset();
				m_lastState.A = true;
				break;
			case 1:
				m_currState.B = true;
				m_lastState.reset();
				m_lastState.B = true;
				break;
			case 2:
				m_currState.X = true;
				m_lastState.reset();
				m_lastState.X = true;
				break;
			case 3:
				m_currState.Y = true;
				m_lastState.reset();
				m_lastState.Y = true;
				break;
			case 4:
				m_currState.LB = true;
				break;
			case 5:
				m_currState.RB = true;
				break;
			case 6:
				m_window.close(); //exit
			case 7:
				m_currState.Start = true;
				break;
			case 8:
				m_currState.LeftThumbClick = true;
				break;
			case 9:
				m_currState.RightThumbClick = true;
				break;
			}
		}

		if (sf::Event::JoystickButtonReleased == event.type)
		{
			switch (event.joystickButton.button)
			{
			case 0:
				m_currState.A = false;
				break;
			case 1:
				m_currState.B = false;
				break;
			case 2:
				m_currState.X = false;
				break;
			case 3:
				m_currState.Y = false;
				break;
			case 4:
				m_currState.LB = false;
				break;
			case 5:
				m_currState.RB = false;
				break;
			case 7:
				m_currState.Start = false;
				break;
			case 8:
				m_currState.LeftThumbClick = false;
				break;
			case 9:
				m_currState.RightThumbClick = false;
				break;
			}
		}
	}
}

void Xbox360Controller::render()
{
	m_window.clear();
	m_window.draw(m_backGround);
	if (m_currState.A)
	{
		m_window.draw(m_aPressed);
	}
	if (m_currState.B)
	{
		m_window.draw(m_bPressed);
	}
	if (m_currState.X)
	{
		m_window.draw(m_xPressed);
	}
	if (m_currState.Y)
	{
		m_window.draw(m_yPressed);
	}
	if (m_currState.Start)
	{
		m_window.draw(m_startPressed);
	}
	if (m_currState.LB)
	{
		m_window.draw(m_lbPressed);
	}
	if (m_currState.RB)
	{
		m_window.draw(m_rbPressed);
	}
	if (m_currState.DpadDown)
	{
		m_window.draw(m_dPadDownPressed);
	}
	if (m_currState.DpadUp)
	{
		m_window.draw(m_dPadUpPressed);
	}
	if (m_currState.DpadLeft)
	{
		m_window.draw(m_dPadLeftPressed);
	}
	if (m_currState.DpadRight)
	{
		m_window.draw(m_dPadRightPressed);
	}
	m_window.draw(m_lsX);
	m_window.draw(m_lsY);
	m_window.draw(m_rsX);
	m_window.draw(m_rsY);
	m_window.draw(m_lTriggerCoord);
	m_window.draw(m_rTriggerCoord);

	m_window.draw(m_lastPressed);
	m_window.display();
}

void Xbox360Controller::setLast()
{
	if (m_lastState.A)
	{
		m_lastPressed.setString("Last Face Button Pressed: A");
	}
	if (m_lastState.B)
	{
		m_lastPressed.setString("Last Face Button Pressed: B");
	}
	if (m_lastState.X)
	{
		m_lastPressed.setString("Last Face Button Pressed: X");
	}
	if (m_lastState.Y)
	{
		m_lastPressed.setString("Last Face Button Pressed: Y");
	}
}
///function to setup all the face button text objects
//using it later for all button presses
void Xbox360Controller::setText(sf::Text &text, int scalar)
{
	text.setString("Pressed");
	text.setFont(m_font);
	int y = 420 - (scalar * 60);
	text.setPosition(750, y);
	text.setFillColor(sf::Color::Black);
}

void GamePadState::reset()
{
	A = false;
	B = false;
	X = false;
	Y = false;
}
