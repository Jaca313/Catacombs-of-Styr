#include "ResourceManager.h"

sf::Texture* ResourceManager::getTex(int nr)
{
	//Returns a pointer to Texture in array
	if (Textures.size() > nr) return &Textures.at(nr);
	else return nullptr;
}

void ResourceManager::LoadTextures()
{
	//Loads Textures filling the array

	//0 - 9 Reserved for Walls
	//0
	LoadSingleTexture("Walls/Wall Door.bmp");//Reserved for some kind of door?
	//1
	LoadSingleTexture("Walls/Handwall.png");
	//2
	LoadSingleTexture("Walls/bonewall.png");
	//3
	LoadSingleTexture("Walls/dirtybrick.jpg");
	//4
	LoadSingleTexture("Walls/Handwall.png");////////////////////////Empty
	//5
	LoadSingleTexture("Walls/Handwall.png");
	//6
	LoadSingleTexture("Walls/Handwall.png");
	//7
	LoadSingleTexture("Walls/Handwall.png");
	//8
	LoadSingleTexture("Walls/Handwall.png");
	//9
	LoadSingleTexture("Walls/Handwall.png");

	//10 - 29 Reserved for UI
	//10
	LoadSingleTexture("Faces/Face_Trog.png");
	//11
	LoadSingleTexture("");
	//12
	LoadSingleTexture("");
	//13
	LoadSingleTexture("");
	//14
	LoadSingleTexture("");
	//15
	LoadSingleTexture("");
	//16
	LoadSingleTexture("");
	//17
	LoadSingleTexture("GUI/EditorCursor.png");
	//18
	LoadSingleTexture("GUI/Background.png");
	//19
	LoadSingleTexture("GUI/MapBack.png");
	//20
	LoadSingleTexture("GUI/MenuButton.png");
	//21
	LoadSingleTexture("GUI/MenuButtonInactive.png");
	//22
	LoadSingleTexture("GUI/MenuButtonHover.png");
	//23
	LoadSingleTexture("GUI/MenuButtonPressed.png");
	//24
	LoadSingleTexture("GUI/MenuButtonQuit.png");
	//25
	LoadSingleTexture("GUI/MenuWindow.png");
	//26
	LoadSingleTexture("GUI/Logo.png");
	//27
	LoadSingleTexture("GUI/LifeProgressBar.png");
	//28
	LoadSingleTexture("GUI/PopUpMenu.png");
	//29
	LoadSingleTexture("GUI/MainMenuBack.png");

	//30 - 59 Reserved for Entities (Enemies)
	//30
	LoadSingleTexture("Orcs/orc_green.png");
	//31
	LoadSingleTexture("Orcs/orc_brown.png");
	//32
	LoadSingleTexture("Orcs/orc_warrior_green.png");
	//33
	LoadSingleTexture("Orcs/orc_warrior_brown.png");
	//34
	LoadSingleTexture("Orcs/orc_spearman_green.png");
	//35
	LoadSingleTexture("Orcs/orc_spearman_brown.png");
	//36
	LoadSingleTexture("Orcs/orc_hunter_green.png");
	//37
	LoadSingleTexture("Orcs/orc_hunter_brown.png");
	//38
	LoadSingleTexture("Orcs/orc_salesman_green.png");
	//39
	LoadSingleTexture("Orcs/orc_salesman_brown.png");
	//40
	LoadSingleTexture("Orcs/orc_shaman_green.png");
	//41
	LoadSingleTexture("Orcs/orc_shaman_brown.png");
	//42
	LoadSingleTexture("Orcs/orc_chief_green.png");
	//43
	LoadSingleTexture("Orcs/orc_chief_brown.png");
	//44
	LoadSingleTexture("Drops/gold.png");
	//45
	LoadSingleTexture("");
	//46
	LoadSingleTexture("");
	//47
	LoadSingleTexture("");
	//48
	LoadSingleTexture("");
	//49
	LoadSingleTexture("");
	//50
	LoadSingleTexture("");
	//51
	LoadSingleTexture("");
	//52
	LoadSingleTexture("");
	//53
	LoadSingleTexture("");
	//54
	LoadSingleTexture("");
	//55
	LoadSingleTexture("");
	//56
	LoadSingleTexture("");
	//57
	LoadSingleTexture("");
	//58
	LoadSingleTexture("");
	//59
	LoadSingleTexture("");

	//60 - 79 Reserved for Ceiling and Floor Textures
	//60
	LoadSingleTexture("FloorNCeiling/Floor_00.bmp");
	//61
	LoadSingleTexture("FloorNCeiling/Floor_01.bmp");
	//62
	LoadSingleTexture("FloorNCeiling/Floor_02.bmp");
	//63
	LoadSingleTexture("FloorNCeiling/Floor_03.bmp");
	//64
	LoadSingleTexture("FloorNCeiling/Floor_04.bmp");
	//65
	LoadSingleTexture("FloorNCeiling/Floor_05.bmp");
	//66
	LoadSingleTexture("FloorNCeiling/Floor_06.bmp");
	//67
	LoadSingleTexture("FloorNCeiling/Floor_07.bmp");
	//68
	LoadSingleTexture("FloorNCeiling/Floor_08.bmp");
	//69
	LoadSingleTexture("FloorNCeiling/Floor_09.bmp");
	//70
	LoadSingleTexture("FloorNCeiling/Floor_10.bmp");
	//71
	LoadSingleTexture("FloorNCeiling/ceiling_01.bmp");
	//72
	LoadSingleTexture("");
	//73
	LoadSingleTexture("");
	//74
	LoadSingleTexture("");
	//75
	LoadSingleTexture("");
	//76
	LoadSingleTexture("");
	//77
	LoadSingleTexture("");
	//78
	LoadSingleTexture("");
	//79
	LoadSingleTexture("");


}

void ResourceManager::LoadShaders()
{
	//Load Shader used in GameState to flip screen and clip entites behind walls
	if (!ClipEntity.loadFromFile("Shaders/ClipEntity.frag", sf::Shader::Fragment)) {
		std::string Error = "Shader Shaders/ClipEntity.frag failed to load";
		InfoTool.ERR(4, Error);
	}
	//Load Shader that flips screen
	if (!m_sFlipScreen.loadFromFile("Shaders/FlipScreen.frag", sf::Shader::Fragment)) {
		std::string Error = "Shader Shaders/FlipScreen.frag failed to load";
		InfoTool.ERR(4, Error);
	}
	//Load Shader used in PauseState, blurs and flips screen
	if (!m_sFlipScreenBlur.loadFromFile("Shaders/FlipScreenBlur.frag", sf::Shader::Fragment)) {
		std::string Error = "Shader Shaders/FlipScreenBlur.frag failed to load";
		InfoTool.ERR(4, Error);
	}

}

void ResourceManager::LoadFonts()
{
	//Load Font used in Buttons
	std::string path = "Fonts/" + std::string("Langar.ttf");
	if (!m_sFontLanger.loadFromFile(path)) {
		std::string Error = "Font " + std::string("Langar.ttf") + " failed to load";
		InfoTool.ERR(4, Error);
	}
}

void ResourceManager::LoadSingleTexture(std::string _filename)
{
	//Loads Single Texture from file
	Textures.push_back(sf::Texture());
	if (_filename != "") {
		std::string path = "Textures/" + _filename;
		if (!Textures.back().loadFromFile(path)) {
			std::string Error = "Texture " + _filename + " failed to load";
			InfoTool.ERR(4, Error);
		}

		Textures.back().setRepeated(true);
		Textures.back().setSmooth(true);
	}

}
