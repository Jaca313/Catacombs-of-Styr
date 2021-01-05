//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "PixelArena.h"
int WinMain()
{
	PixelArena GameInstance;
	GameInstance.Run();
	return 0;
}