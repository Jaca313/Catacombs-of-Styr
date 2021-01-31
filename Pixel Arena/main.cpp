//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "PixelArena.h"
int WinMain()
{
	//Init Game-Engine
	PixelArena GameInstance;
	GameInstance.Run();//Enter Game Loop
	return 0;
}