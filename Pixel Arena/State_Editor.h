#pragma once
#include "GameState.h"
#include "LevelMap.h"
#include "ResourceManager.h"
struct EditorQuad {
	sf::VertexArray vQuad;///< Quad to be rendered
	sf::Texture* tex;///< Texture of drawn Quad
	float z[4];///< Z-Buffer Values of Quad
};

struct WorldRender {
	std::vector<EditorQuad> Decal;///< Array of All Quads to be drawn (walls,floor,ceiling)
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

	WorldRender sRender;///< Contains Quad Data

	LevelMap Level;///< Contains Level Data

	ResourceManager* Resources;///< Pointer to Resources
	LogManager& Info = LogManager::getInstance();///< Reference to Internal Messaging

	//Camera Settings
	sf::Vector3f vCamera = { 1,1,0 };///< Camera Position in Space
	float fCameraAngle = 0.0f;///< Angle of Camera
	float fCameraPitch = 5.5f;///< Pitch of Camera
	float fCameraZoom = 10.0f;///< Zoom of Camera

	//Cursor
	sf::Vector2i vCursor = { 0,0 };///< Position of Highlight in Map Space

	bool bVisible[6];///< Computed Visibility of Faces in a Cube(orthographic projection)
	//Drawing
	std::array<sf::Vector3f, 8> CreateCube(sf::Vector2i _Cell);///< Creates a Cube out of Quads with the projection applied
	void CalculateVisibleFaces(std::array<sf::Vector3f, 8> & _Cube);///< Calculates which 3 faces of Cube are visible
	void GetFaceQuads(sf::Vector2i _Cell,sf::Texture* _overwriteTex = nullptr);///< Calculates Quads to be drawn and textures them

	int CurrentTextureCursor = 1;///< Current Selected Wall Texture

	void SetWall();///< Sets tile as wall or not wall with the chosen texture

	void endState();///< used to save cell data when exiting
};

