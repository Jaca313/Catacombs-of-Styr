//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "PixelArena.h"
int main()
{
	PixelArena GameInstance;
	GameInstance.Run();
	return 0;
}