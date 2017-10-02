#include "360Joystick.h"

Xbox360Controller::Xbox360Controller() : m_window{ sf::VideoMode{ 900,600,32 }, "360 Controller with SFML!" }
{
	m_currState.reset();
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
		if (sf::Joystick::isButtonPressed)
		{

			switch (event.joystickButton.button)
			{
			case 0:
				m_currState.A = true;
				break;
			case 1:
				m_currState.B = true;
				break;
			case 2:
				m_currState.X = true;
				break;
			case 3:
				m_currState.Y = true;
				break;
			case 4:
				m_currState.LB = true;
				break;
			case 5:
				m_currState.RB = true;
				break;
			case 6:
				m_currState.Back = true;
				break;
			case 7:
				m_currState.Start = true;
				break;
			case 8:
				m_currState.LeftThumbClick = true;
				break;
			case 9:
				m_currState.RightThumbClick = true;
				break;
			default:
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
	m_window.display();
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
