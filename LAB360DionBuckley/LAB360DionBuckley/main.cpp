/// <summary>
/// Lab where we show off the functionality with a 360 joystick
/// 
/// @author Dion Buckley
/// @date Oct 2017
/// 
/// Time log 2017:
/// 02/10: started 4:15pm
/// 
/// Known Bugs:
/// </summary>
#include "360Joystick.h"
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

/// <summary>
/// main entry point
/// </summary>
/// <returns>zero</returns>
int main()
{
	Xbox360Controller game;
	game.run();
	return 0;
}