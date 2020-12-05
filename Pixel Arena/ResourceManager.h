#pragma once
#include <vector>

class ResourceManager
{
private:
	LogManager& InfoTool = LogManager::getInstance();

	ResourceManager(){
		LoadTextures();
		LoadShaders();
	}
	~ResourceManager() {

	}
public:
	static ResourceManager& getInstance() {
		static ResourceManager theInstance;
		return theInstance;
	}

public:
	std::vector<sf::Texture> Textures;//deprecated for direct use
	sf::Texture* getTex(int nr);

	sf::Shader ClipEntity;
	sf::Shader m_sFlipScreen;
	sf::Image Z_BufferImage;
	sf::Texture Z_BufferTex;
private:
	void LoadTextures();
	void LoadShaders();

	void LoadSingleTexture(std::string filename);

};

