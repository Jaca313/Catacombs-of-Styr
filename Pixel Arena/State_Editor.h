#pragma once
#include "GameState.h"
#include "LevelMap.h"
#include "ResourceManager.h"
struct EditorQuad {
	sf::VertexArray vQuad;
	sf::Texture* tex;
	float z[4];
};

struct WorldRender {
	std::vector<EditorQuad> Decal;
};

class State_Editor :
	public GameState
{
public:
	State_Editor(sf::RenderWindow* _pWindow, ResourceManager* _Resources);
	~State_Editor();
private:
	sf::RenderWindow* Window;///< Final Output
	sf::RenderTexture* ScreenBuffer;///< Intermediary drawing target for shader use
public:
	void eventLoop();///< Queries and resolves SFML events
	void input(float _fTime);///< User Input (Keyboard and Mouse)
	void update(float _fTime);///< Calculates Internal Resource Changes
	void draw(sf::RenderTexture* _ScreenBuffer);///< Outputs Elements to ScreenBuffer

	void resumeState();///< When a state is resumed
//Resources
private:

	WorldRender sRender;

	LevelMap Level;///< Contains Level Data

	ResourceManager* Resources;///< Pointer to Resources
	LogManager& Info = LogManager::getInstance();///< Reference to Internal Messaging

	//Camera Settings
	sf::Vector3f vCamera = { 1,1,0 };
	float fCameraAngle = 0.0f;
	float fCameraPitch = 5.5f;
	float fCameraZoom = 10.0f;

	//Cursor
	sf::Vector2i vCursor = { 0,0 };

	bool bVisible[6];
	//Drawing
	std::array<sf::Vector3f, 8> CreateCube(sf::Vector2i _Cell);
	void CalculateVisibleFaces(std::array<sf::Vector3f, 8> & _Cube);
	void GetFaceQuads(sf::Vector2i _Cell,sf::Texture* _overwriteTex = nullptr);
};

