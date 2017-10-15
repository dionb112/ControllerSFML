#include "360Joystick.h"

Xbox360Controller::Xbox360Controller() : m_window{ sf::VideoMode{ 900,600,32 }, "360 Controller with SFML!" }, m_anyFaceButtonPressed{ false }
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
	
	m_lastPressed.setString("Last Pressed: ");
	m_lastPressed.setFont(m_font);
	m_lastPressed.setPosition(600, 200);
	m_lastPressed.setFillColor(sf::Color::Black);
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
			case 6:
				m_currState.Back = false;
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
			default:
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
	m_window.draw(m_lastPressed);
	m_window.display();
}

void Xbox360Controller::setLast()
{
	if (m_lastState.A)
	{
		m_lastPressed.setString("Last Pressed: A");
	}
	if (m_lastState.B)
	{
		m_lastPressed.setString("Last Pressed: B");
	}
	if (m_lastState.X)
	{
		m_lastPressed.setString("Last Pressed: X");
	}
	if (m_lastState.Y)
	{
		m_lastPressed.setString("Last Pressed: Y");
	}
}
///function to setup all the face button text objects
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
	LB = false;
	RB = false;
	Back = false;
	Start = false;
	LeftThumbClick = false;
	RightThumbClick = false;
}
