#include "ResourceManager.h"

sf::Texture* ResourceManager::getTex(int nr)
{
	if (Textures.size() > nr) return &Textures.at(nr);
	else return nullptr;
}

void ResourceManager::LoadTextures()
{
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
	LoadSingleTexture("Walls/");
	//5
	LoadSingleTexture("Walls/");
	//6
	LoadSingleTexture("Walls/");
	//7
	LoadSingleTexture("Walls/");
	//8
	LoadSingleTexture("Walls/");
	//9
	LoadSingleTexture("");

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
	LoadSingleTexture("");
	//18
	LoadSingleTexture("");
	//19
	LoadSingleTexture("");
	//20
	LoadSingleTexture("");
	//21
	LoadSingleTexture("");
	//22
	LoadSingleTexture("");
	//23
	LoadSingleTexture("");
	//24
	LoadSingleTexture("");
	//25
	LoadSingleTexture("");
	//26
	LoadSingleTexture("");
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

	//60 - 69 Reserved for Ceiling and Floor Textures
	//60
	LoadSingleTexture("FloorNCeiling/Floor_00.bmp");
	//61
	LoadSingleTexture("FloorNCeiling/Floor_02.bmp");
	//62
	LoadSingleTexture("");
	//63
	LoadSingleTexture("");
	//64
	LoadSingleTexture("");
	//65
	LoadSingleTexture("");
	//66
	LoadSingleTexture("");
	//67
	LoadSingleTexture("");
	//68
	LoadSingleTexture("");
	//69
	LoadSingleTexture("");

	//69
	LoadSingleTexture("");


}

void ResourceManager::LoadShaders()
{
	if (!ClipEntity.loadFromFile("Shaders/ClipEntity.frag", sf::Shader::Fragment)) {
		std::string Error = "Shader Shaders/ClipEntity.frag failed to load";
		InfoTool.ERR(4, Error);
	}
	if (!m_sFlipScreen.loadFromFile("Shaders/FlipScreen.frag", sf::Shader::Fragment)) {
		std::string Error = "Shader Shaders/FlipScreen.frag failed to load";
		InfoTool.ERR(4, Error);
	}

}

void ResourceManager::LoadSingleTexture(std::string _filename)
{
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
