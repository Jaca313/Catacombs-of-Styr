#pragma once
#include <vector>

class ResourceManager///< Manages Resources in App
{
private:
	LogManager& InfoTool = LogManager::getInstance();///<Logging Tool and Global Helper

	ResourceManager(){///<Inline Constructor (Loads Resources)
		LoadTextures();//Load Textures
		LoadShaders();//Load Shaders
		LoadFonts();//Load Fonts
	}
	~ResourceManager() {///< Empty Destructor

	}
public:
	///<Singleton Implementation
	static ResourceManager& getInstance() {
		static ResourceManager theInstance;
		return theInstance;
	}

public:
	std::vector<sf::Texture> Textures;///< deprecated for direct use!/ Direct pointer to Texture Array
	sf::Texture* getTex(int nr);///<Returns a Texture based on number in vector (maybe switch to map?)

	sf::Shader ClipEntity;///< Shader to Clip Entities obscured by Raytraced Walls (used in Favour of CPU computing)
	sf::Shader m_sFlipScreen;///< Shader to Flip Screen (SFML y axis starts left top and increments downwards)
	sf::Shader m_sFlipScreenBlur;///< Shader to Flip Screen and blur (used on Pause ingame)
	sf::Image Z_BufferImage;///< Z_Buffer for Raycasted Walls (used in Clipping)
	sf::Texture Z_BufferTex;///< Z_Buffer for Raycasted Walls (used in Clipping)

	sf::Font m_sFontLanger;///< Default font for all text in App
private:
	void LoadTextures();///<Loads Textures from files
	void LoadShaders();///Loads Shaders from files
	void LoadFonts();///<Loads Fonts from files
	void LoadSingleTexture(std::string filename);///<Helper Loads Single Texture File

};

