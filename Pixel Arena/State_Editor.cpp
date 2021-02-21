#include "stdafx.h"
#include "State_Editor.h"

State_Editor::State_Editor(sf::RenderWindow* _pWindow, ResourceManager* _Resources)
{
	//Basic Setup
	this->ID = 400;
	this->Window = _pWindow;
	//Link Resources
	this->Resources = _Resources;

	Window->setMouseCursorVisible(true);
	Window->setVerticalSyncEnabled(true);

	//Load Level
	Level.BinaryLoadData(L"Level1.Jaca");
	
	//Set Cursor to the middle of Map
	vCursor = { Level.getMapX()/2,Level.getMapY()/2 };
}

State_Editor::~State_Editor()
{
}

void State_Editor::eventLoop()
{
	//Rotation Movement PreCalc
	int cosWSAD = 0;
	int sinWSAD = 0;
	float cAngle = cos(fCameraAngle);
	float sAngle = sin(fCameraAngle);
	if (cAngle >= 0.5f)cosWSAD = 1;
	else if (cAngle <= -0.5f)cosWSAD = -1;
	if (sAngle >= 0.5f)sinWSAD = 1;
	else if (sAngle <= -0.5f)sinWSAD = -1;

	sf::Event event;
	while (this->Window->pollEvent(event))
	{
		//Close Window
		if (event.type == sf::Event::Closed)
			this->Window->close();
		//Exit to Menu
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			m_bWantsQuit = true;
		//Cursor Movement
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) { vCursor.y -= cosWSAD; vCursor.x += sinWSAD; }
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) { vCursor.y += cosWSAD; vCursor.x -= sinWSAD; }
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) { vCursor.x -= cosWSAD; vCursor.y -= sinWSAD; }
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) { vCursor.x += cosWSAD; vCursor.y += sinWSAD; }
		//Place Wall
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)SetWall();
	}
}

void State_Editor::input(float _fTime)
{
	////Camera Movement
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))vCamera.y -= 100.f * _fTime;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))vCamera.y += 100.f * _fTime;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))vCamera.x -= 100.f * _fTime;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))vCamera.x += 100.f * _fTime;

	//PickTexture
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))CurrentTextureCursor = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))CurrentTextureCursor = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))CurrentTextureCursor = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))CurrentTextureCursor = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))CurrentTextureCursor = 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))CurrentTextureCursor = 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))CurrentTextureCursor = 6;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7))CurrentTextureCursor = 7;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8))CurrentTextureCursor = 8;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9))CurrentTextureCursor = 9;


	//Camera Rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))fCameraAngle += 1.f * _fTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))fCameraAngle -= 1.f * _fTime;

	//Camera Tilt
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))fCameraPitch -= 1.f * _fTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))fCameraPitch += 1.f * _fTime;

	//Camera Zoom
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))fCameraZoom += 10.f * _fTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))fCameraZoom -= 10.f * _fTime;


	////Control Cursor
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { vCursor.y -= cosWSAD; vCursor.x += sinWSAD; }
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { vCursor.y += cosWSAD; vCursor.x -= sinWSAD; }
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { vCursor.x -= cosWSAD; vCursor.y -= sinWSAD; }
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { vCursor.x += cosWSAD; vCursor.y += sinWSAD; }

	//Bound Cursor
	if (vCursor.x < 0)vCursor.x = 0;
	if (vCursor.y < 0)vCursor.y = 0;
	if (vCursor.x >= Level.getMapX())vCursor.x = Level.getMapX() - 1;
	if (vCursor.y >= Level.getMapY())vCursor.y = Level.getMapY() - 1;

	//Position Camera in World
	vCamera.x = vCursor.x + 0.5f;
	vCamera.z = vCursor.y + 0.5f;
	vCamera.x *= fCameraZoom;
	vCamera.z *= fCameraZoom;


	//Debug
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))Level.editCell(Level.getMapX()*vCursor.y+vCursor.x)->wall = !Level.editCell(Level.getMapX() * vCursor.y + vCursor.x)->wall;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))Level.getCell(vCursor.x, vCursor.y).wall = !Level.getCell(vCursor.x, vCursor.y).wall;

}

void State_Editor::update(float _fTime)
{

}

void State_Editor::draw(sf::RenderTexture* _ScreenBuffer)
{
	//Create a Cube to calculate which faces to cull(not render due to orthographic projection)
	std::array<sf::Vector3f, 8> cullCube = CreateCube({ 0,0 });
	CalculateVisibleFaces(cullCube);
	//Get Quads to draw
	sRender.Decal.clear();
	for (int y = 0; y < Level.getMapY(); y++)
		for (int x = 0; x < Level.getMapX(); x++)
			GetFaceQuads({ x,y });
	//Sort Quads by center distance
	std::sort(sRender.Decal.begin(), sRender.Decal.end(), [](const EditorQuad& E1, const EditorQuad& E2) {
		float z1 = (E1.z[0] + E1.z[1] + E1.z[2] + E1.z[3]) * 0.25f;
		float z2 = (E2.z[0] + E2.z[1] + E2.z[2] + E2.z[3]) * 0.25f;
		return z1 < z2;
		});

	//Append Cursor (drawn as last)
	GetFaceQuads(vCursor,Resources->getTex(17));

	//Drawing Scene
	this->ScreenBuffer = _ScreenBuffer;
	this->ScreenBuffer->clear(sf::Color(0, 120, 120, 255));//Clear Buffer

	for (int i = 0; i < sRender.Decal.size(); i++) {
		this->ScreenBuffer->draw(sRender.Decal.at(i).vQuad, sRender.Decal.at(i).tex);
	}

}

void State_Editor::resumeState()
{
	//if resumed
	m_bResume = false;
}

std::array<sf::Vector3f, 8> State_Editor::CreateCube(sf::Vector2i _Cell)
{
	const float fAngle = fCameraAngle;
	const float fPitch = fCameraPitch;
	const float fScale = fCameraZoom;
	const sf::Vector3f Camera = { vCamera.x,0.0f,vCamera.z };

	//Unit Cube
	std::array<sf::Vector3f, 8> unitCube, rotCube, worldCube, projCube;
	//screen space pre multiply
	unitCube[0] = { 0.0f,0.0f,0.0f };
	unitCube[1] = { fScale,0.0f,0.0f };
	unitCube[2] = { fScale,-1.5f *fScale,0.0f };
	unitCube[3] = { 0.0f,-1.5f *fScale,0.0f };
	unitCube[4] = { 0.0f,0.0f,fScale };
	unitCube[5] = { fScale,0.0f,fScale };
	unitCube[6] = { fScale,-1.5f*fScale,fScale };
	unitCube[7] = { 0.0f,-1.5f *fScale,fScale };

	//Translate Cube in X-Y Plane
	for (int i = 0; i < 8; i++) {
		unitCube[i].x += (_Cell.x * fScale - Camera.x);
		unitCube[i].y += -Camera.y ; //cos(fAngle) *
		unitCube[i].z += (_Cell.y * fScale - Camera.z);
	}

	//Rotate Cube in Y-Axis around origin
	float s = sin(fAngle);
	float c = cos(fAngle);
	for (int i = 0; i < 8; i++) {
		rotCube[i].x = unitCube[i].x * c + unitCube[i].z * s;
		rotCube[i].y = unitCube[i].y;
		rotCube[i].z = unitCube[i].x * -s + unitCube[i].z * c;
	}

	//Rotate Cube in X-Axis around origin (tilt slightly overhead)
	s = sin(fPitch);
	c = cos(fPitch);
	for (int i = 0; i < 8; i++) {
		worldCube[i].x = rotCube[i].x;
		worldCube[i].y = rotCube[i].y * c - rotCube[i].z * s;
		worldCube[i].z = rotCube[i].y * s + rotCube[i].z * c;
	}

	//Project Cube Orthographically - Full Screen Centered
	for (int i = 0; i < 8; i++) {
		projCube[i].x = worldCube[i].x + Window->getSize().x * 0.5f;
		projCube[i].y = worldCube[i].y + Window->getSize().y * 0.5f;
		projCube[i].z = worldCube[i].z;
	}

	return projCube;
}

void State_Editor::CalculateVisibleFaces(std::array<sf::Vector3f, 8> & _Cube)
{
	//Check which faces are facing the right way (to the camera)
	auto CheckNormal = [&](int v1, int v2, int v3) {
		sf::Vector2f a = { _Cube[v1].x , _Cube[v1].y };
		sf::Vector2f b = { _Cube[v2].x , _Cube[v2].y };
		sf::Vector2f c = { _Cube[v3].x , _Cube[v3].y };

		sf::Vector2f V1 = b - a;
		sf::Vector2f V2 = c - a;
		return (V1.x * V2.y - V1.y * V2.x) > 0;
	};

	bVisible[Face::Floor] = CheckNormal(4, 0, 1);
	bVisible[Face::South] = CheckNormal(3, 0, 1);
	bVisible[Face::North] = CheckNormal(6, 5, 4);
	bVisible[Face::East] = CheckNormal(7, 4, 0);
	bVisible[Face::West] = CheckNormal(2, 1, 5);
	bVisible[Face::Top] = CheckNormal(7, 3, 2);
}

void State_Editor::GetFaceQuads(sf::Vector2i _Cell, sf::Texture* _overwriteTex)
{
	//Make quads to Cube from Cells
	const float fAngle = fCameraAngle;
	const float fPitch = fCameraPitch;
	const float fScale = fCameraZoom;
	const sf::Vector3f Camera = vCamera;

	//Create Cube
	std::array<sf::Vector3f, 8> projCube = CreateCube(_Cell);
	auto& mapCell = Level.getMapCell(_Cell.x, _Cell.y);

	//Calculate Quad
	auto MakeFace = [&](int v1, int v2, int v3, int v4, Face f) {
		sRender.Decal.push_back(EditorQuad{});
		if(_overwriteTex) sRender.Decal.back().tex = _overwriteTex;
		else sRender.Decal.back().tex = Resources->getTex(mapCell.id[f]);

		sf::Vector2u texSize = sRender.Decal.back().tex->getSize();
		
		sf::Vertex P1{ sf::Vector2f(projCube[v1].x,projCube[v1].y),sf::Vector2f(0.f,0.f) };
		sf::Vertex P2{ sf::Vector2f(projCube[v2].x,projCube[v2].y),sf::Vector2f(0.f,texSize.y) };
		sf::Vertex P3{ sf::Vector2f(projCube[v3].x,projCube[v3].y),sf::Vector2f(texSize.x,texSize.y) };
		sf::Vertex P4{ sf::Vector2f(projCube[v4].x,projCube[v4].y),sf::Vector2f(texSize.x,0.f) };




		sRender.Decal.back().z[0] = projCube[v1].z;
		sRender.Decal.back().z[1] = projCube[v2].z;
		sRender.Decal.back().z[2] = projCube[v3].z;
		sRender.Decal.back().z[3] = projCube[v4].z;


		sf::VertexArray vP;

		vP.append(P1);
		vP.append(P2);
		vP.append(P3);
		vP.append(P4);

		vP.setPrimitiveType(sf::Quads);

		sRender.Decal.back().vQuad = vP;
	};

	//Set Faces depending on visibility
	if (!mapCell.wall) {
		if (bVisible[Face::Floor])MakeFace(4, 0, 1, 5, Face::Floor);
	}
	else {
		if (bVisible[Face::South])MakeFace(3, 0, 1, 2, Face::South);
		if (bVisible[Face::North])MakeFace(6, 5, 4, 7, Face::North);
		if (bVisible[Face::East])MakeFace(7, 4, 0, 3, Face::East);
		if (bVisible[Face::West])MakeFace(2, 1, 5, 6, Face::West);
		if (bVisible[Face::Top])MakeFace(7, 3, 2, 6, Face::Top);
	}


}

void State_Editor::SetWall()
{
	//Set Textures and Wall Bool when editing
	Level.getMapCell(vCursor.x, vCursor.y).wall = !Level.getMapCell(vCursor.x, vCursor.y).wall;
	int t = CurrentTextureCursor;
	Level.getMapCell(vCursor.x, vCursor.y).id[Face::Floor] = Level.getTexFloor();
	Level.getMapCell(vCursor.x, vCursor.y).id[Face::Top] = Level.getTexCeil();
	Level.getMapCell(vCursor.x, vCursor.y).id[Face::North] = t;
	Level.getMapCell(vCursor.x, vCursor.y).id[Face::South] = t;
	Level.getMapCell(vCursor.x, vCursor.y).id[Face::West] = t;
	Level.getMapCell(vCursor.x, vCursor.y).id[Face::East] = t;
}

void State_Editor::endState()
{
	//Save Level Data when exiting
	Level.BinarySaveData(L"Level1.Jaca");
}
