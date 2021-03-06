#include "State_Gameplay.h"

State_Gameplay::State_Gameplay(sf::RenderWindow* _Window, ResourceManager* _Resources)
{
	//Basic Setup
	this->ID = 100;
	this->Window = _Window;
	Window->setMouseCursorVisible(false);
	Window->setVerticalSyncEnabled(true);
	//Load Level
	//TODO: LOAD BIN
	//Level.LoadLevel(L"M1.jac");
	Level.BinaryLoadData(L"Level1.Jaca");
	//Create player
	Butcher = new Player(128.f, 128.f,&Level);
	//Link Resources
	Entities.setPlayerPointer(Butcher);
	this->Resources = _Resources;

	//Calculate distance to screen from fov
	this->m_cdistancetoProj = (Window->getSize().x / 2.f) / tan(LogManager::DegtoRad(m_cFov / 2.f));

	//Create a Depth Buffer
	m_sZ_Buffer = new float[Window->getSize().x];
}

State_Gameplay::~State_Gameplay()
{
	//Cleanup Player
	delete Butcher;
	//Cleanup Z-Buffer
	delete[] m_sZ_Buffer;
}


void State_Gameplay::eventLoop()
{
	//Handle SFML Events
	sf::Event event;
	while (this->Window->pollEvent(event))
	{
		//Close Window
		if (event.type == sf::Event::Closed)
			this->Window->close();
		//Push Pause Menu
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			m_iRequestState = 300;
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
			Butcher->tryOpenDoor();
		}

	}
}

void State_Gameplay::input(float _fTime)
{
	//Movement
	float cos0 = float(+cos(LogManager::DegtoRad(float(Butcher->DegAngle)))) * _fTime;
	float sin0 = float(+sin(LogManager::DegtoRad(float(Butcher->DegAngle)))) * _fTime;

	float cos90 = float(+cos(LogManager::DegtoRad(float(Butcher->DegAngle + 90)))) * _fTime;
	float sin90 = float(+sin(LogManager::DegtoRad(float(Butcher->DegAngle + 90)))) * _fTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		Butcher->vectorPlayer(sf::Vector2f(+cos0, -sin0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		Butcher->vectorPlayer(sf::Vector2f(-cos0, +sin0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		Butcher->vectorPlayer(sf::Vector2f(+cos90, -sin90));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		Butcher->vectorPlayer(sf::Vector2f(-cos90, +sin90));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))Butcher->setSprint(true);
	else Butcher->setSprint(false);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
	//	Butcher->tryOpenDoor();
	//}

	/*
	//Try to Open Door
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		Butcher->tryOpenDoor();
	}
	*/

	//Rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		Butcher->DegAngleTemp += 90 * _fTime;
		Butcher->DegAngleTemp = LogManager::FixAngle(Butcher->DegAngleTemp);
		Butcher->DegAngle = (int)Butcher->DegAngleTemp;
		printf("%f,%f:%d\n", Butcher->x / 64, Butcher->y / 64, Butcher->DegAngle);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		Butcher->DegAngleTemp -= 90 * _fTime;
		Butcher->DegAngleTemp = LogManager::FixAngle(Butcher->DegAngleTemp);
		Butcher->DegAngle = (int)Butcher->DegAngleTemp;
	}

	//Debug
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
		Butcher->setHealth(Butcher->getHealth() + _fTime * 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)) {
		Butcher->setHealth(Butcher->getHealth() - _fTime * 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
		m_bWantsQuit = true;
	}

	//Mouse
	//distance vector calc should feel better but i plan to add y axis later

	float sensitivity = 100000.f;
	sf::Vector2i MPos = sf::Mouse::getPosition(*Window);
	sf::Vector2u WSize = Window->getSize();
	Butcher->DegAngleTemp -= (MPos.x - WSize.x / 2.f) / WSize.x/2.f * _fTime * sensitivity;
	Butcher->DegAngleTemp = LogManager::FixAngle(Butcher->DegAngleTemp);
	Butcher->DegAngle = (int)Butcher->DegAngleTemp;
	sf::Mouse::setPosition(sf::Vector2i(WSize.x / 2, WSize.y / 2),*Window);

}

void State_Gameplay::update(float _fTime)
{
	updateMousePos(Window);//Grab mouse position from window

	Butcher->update(_fTime);//Update Player
	Entities.UpdateAll();//Update Entities
}

void State_Gameplay::draw(sf::RenderTexture* _ScreenBuffer)
{
	//Set and Clear ScreenBuffer
	this->ScreenBuffer = _ScreenBuffer;
	this->ScreenBuffer->clear(sf::Color(120, 120, 120, 255));//Clear Buffer

	//Clear
	//Draw Floor and Ceiling
	//Draw Walls 
	//Draw Sprites (sort them in order, back to front)
	//Draw Weapons
	//Draw UI



	//CastRaysFloorCeil2();
	//CastRays3DWalls();
	CastRaysFloorCeil();//Render Floor and Ceiling
	CastRays3DWalls();//Render Walls by Texture Type
	Fill_Z_Buffer();//Copy from Data to Image(passthrough to GPU later)
	DrawEntities();//Draw Entities
	DrawUI();//Draw HUD
}

void State_Gameplay::resumeState()
{
	//if resuming
	m_bResume = false;

	Window->setMouseCursorVisible(false);//make mouse invisible

	//if Window size changes in meantime

	//Calculate distance to screen from fov
	this->m_cdistancetoProj = (Window->getSize().x / 2.f) / tan(LogManager::DegtoRad(m_cFov / 2.f));

	//Recreate Depth Buffer
	delete[] m_sZ_Buffer;
	m_sZ_Buffer = new float[Window->getSize().x];
}

void State_Gameplay::CastRays3DWalls()
{
	//Precision is needed (double from now on)

	//Window size
	int winSizeX = Window->getSize().x;
	int winSizeY = Window->getSize().y;

	int maxdof = 150;//How far to look for walls

	int mx;//Tile X
	int my;//Tile Y
	int mp;//Current tile
	int dof;//Current distance by tiles

	double vx;
	double vy;

	double ra = LogManager::FixAngle(Butcher->DegAngle + m_cFov / 2);//ray angle in deg
	double rx;//ray vector x
	double ry;//ray vector y

	double xo;//step of whole tile in X of Vector
	double yo;//step of whole tile in Y of Vector

	//Player position in 64*Tiles
	double px = Butcher->x;
	double py = Butcher->y;

	//Made to group Vertices By Wall Type (drawing is done by wall type)
	//TODO: CHANGE IT
	sf::VertexArray TexturedWall[10];

	//To compensate for angle discrepancies when projecting to flat screen from a camera behind it
	std::vector<double> WallRays;
	double angle = 0;
	for (int i = -winSizeX / 2; i < winSizeX / 2; i++) {
		angle = atan(i / m_cdistancetoProj);
		WallRays.push_back(LogManager::RadtoDeg(angle));
	}

	//Left to Right -> across the screen)
	for (int r = 0; r < winSizeX; ++r) {
		ra = LogManager::FixAngle(Butcher->DegAngle - WallRays.at(r));

		//Vertical Line
		dof = 0;
		double disV = FLT_MAX;
		double Tan = tan(LogManager::DegtoRad(ra));

		if (cos(LogManager::DegtoRad(ra)) > 0.001) { //looking left
			rx = (((int)px >> 6) << 6) + 64.0;
			ry = (px - rx) * Tan + py;
			xo = 64.0;
			yo = -xo * Tan;
		}
		else if (cos(LogManager::DegtoRad(ra)) < -0.001) { //looking right
			rx = (((int)px >> 6) << 6) - 0.0001;
			ry = (px - rx) * Tan + py;
			xo = -64.0;
			yo = -xo * Tan;
		}
		else {  //looking up or down. no hit  
			rx = px; ry = py; dof = maxdof;
		}


		while (dof < maxdof)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * Level.getMapX() + mx;
			//TODO: REMOVE LIMITS below
			if (mp > 0 && mp < Level.getMapX() * Level.getMapY() && Level.getMapCell(mp).wall && Level.getMapCell(mp).wall) {//hit 
				dof = maxdof;
				disV = cos(LogManager::DegtoRad(ra)) * (rx - px) - sin(LogManager::DegtoRad(ra)) * (ry - py);
			}
			else { //check next horizontal
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		vx = rx; vy = ry;


		//Horizontal Line
		dof = 0;
		double disH = FLT_MAX;
		Tan = 1.0 / Tan;
		if (sin(LogManager::DegtoRad(ra)) > 0.001) { //looking up 
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * Tan + px; yo = -64;
			xo = -yo * Tan;
		}
		else if (sin(LogManager::DegtoRad(ra)) < -0.001) { //looking down
			ry = (((int)py >> 6) << 6) + 64.0;
			rx = (py - ry) * Tan + px; yo = 64.0;
			xo = -yo * Tan;
		}
		else {//looking straight left or right
			rx = px;
			ry = py;
			dof = maxdof;
		}

		while (dof < maxdof)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * Level.getMapX() + mx;
			if (mp > 0 && mp < Level.getMapX() * Level.getMapY() && Level.getMapCell(mp).wall && Level.getMapCell(mp).wall) { //hit
				dof = maxdof;
				disH = cos(LogManager::DegtoRad(ra)) * (rx - px) - sin(LogManager::DegtoRad(ra)) * (ry - py);
			}
			else { //check next horizontal
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		sf::Color Kolor = sf::Color(169, 193, 193, 255);
		int HitSide = 1;//Vertical
		if (disV < disH) {//horizontal hit first
			rx = vx;
			ry = vy;
			disH = disV;
			Kolor = sf::Color(190, 210, 210, 255);
			HitSide = 2;//Horizontal
		}

		double DistanceCorrect = disH;

		double ca = LogManager::FixAngle((float)Butcher->DegAngle - ra); disH = disH * cos(LogManager::DegtoRad(ca));    //fix fisheye
		if (disH < 1)disH = 1;
		int lineH = int((160 * winSizeY / 2) / (disH));

		if (lineH > winSizeY * 50) { lineH = winSizeY * 50; }//line height and limit
		int lineOff = winSizeY / 2 - (lineH >> 1);      //line offset


		sf::Vertex Line[4];
		Line[0].position.x = float(r);
		Line[0].position.y = float(winSizeY - lineOff);
		Line[1].position.x = float(r);
		Line[1].position.y = float(winSizeY - (lineOff + lineH));
		Line[2].position.x = float((r + 1));
		Line[2].position.y = float(winSizeY - (lineOff + lineH));
		Line[3].position.x = float((r + 1));
		Line[3].position.y = float(winSizeY - lineOff);

		//Uniform Color
		//Line[0].color = Kolor;
		//Line[1].color = Kolor;
		//Line[2].color = Kolor;
		//Line[3].color = Kolor;
		int HitCell = (int)(ry / 64.f) * Level.getMapX() + (int)(rx / 64.f);
		int TexCall = Level.getMapCell(HitCell).id[Face::North];//TODO:ADD FACES
		TexCall = TexCall < 0 ? 1 : TexCall;
		TexCall = TexCall > 9 ? 1 : TexCall;
		float TexSizeX = (float)Resources->Textures.at(TexCall).getSize().x;
		float TexSizeY = (float)Resources->Textures.at(TexCall).getSize().y;

		if (HitSide == 1) { // Horizontal
			rx /= Level.getTileSize();//64
			float normX = (rx - (int)rx);
			Line[0].texCoords.x = TexSizeX * normX;
			Line[0].texCoords.y = TexSizeY;

			Line[1].texCoords.x = TexSizeX * normX;
			Line[1].texCoords.y = 0.f;

			Line[2].texCoords.x = TexSizeX * normX;
			Line[2].texCoords.y = 0.f;

			Line[3].texCoords.x = TexSizeX * normX;
			Line[3].texCoords.y = TexSizeY;
		}
		else if (HitSide == 2) {//Vertical
			ry /= Level.getTileSize();// /64
			float normY = (ry - (int)ry);
			Line[0].texCoords.x = TexSizeX * normY;
			Line[0].texCoords.y = TexSizeY;

			Line[1].texCoords.x = TexSizeX * normY;
			Line[1].texCoords.y = 0.f;

			Line[2].texCoords.x = TexSizeX * normY;
			Line[2].texCoords.y = 0.f;

			Line[3].texCoords.x = TexSizeX * normY;
			Line[3].texCoords.y = TexSizeY;
		}

		//Add Vertices to the right array
		TexturedWall[TexCall].append(Line[0]);
		TexturedWall[TexCall].append(Line[1]);
		TexturedWall[TexCall].append(Line[2]);
		TexturedWall[TexCall].append(Line[3]);


		m_sZ_Buffer[r] = static_cast<float>(DistanceCorrect);
	}


	//Draw Segments with same wall texture
	for (int i = 0; i < 10; i++) {
		TexturedWall[i].setPrimitiveType(sf::Quads);
		if (TexturedWall[i].getVertexCount())ScreenBuffer->draw(TexturedWall[i], &Resources->Textures.at(i));
	}

}

void State_Gameplay::DrawUI()
{
	//Draw Player HUD
	UI.drawUI(Butcher, *ScreenBuffer);
}

void State_Gameplay::DrawEntities()
{
	//draw Entites only if in view(on Screen)
	for (auto E : *Entities.getEntities()) {
		if (E->InView(sf::Vector2f(Butcher->x, Butcher->y), (float)Butcher->DegAngle, m_cFov))E->drawEntity(m_sZ_Buffer, *ScreenBuffer);
	}
}

void State_Gameplay::Fill_Z_Buffer()
{
	//Convert float data to image (Z-Buffer) (GPU shader)
	unsigned winSize_X = Window->getSize().x;
	Resources->Z_BufferImage.create(winSize_X, 1, sf::Color(0, 0, 0, 255));
	for (unsigned int i = 0; i < winSize_X; i++) {
		//unsigned char CP1 = (int(Z_Buffer[i]) & 0xff000000UL) >> 24;
		//unsigned char CP2 = (int(Z_Buffer[i]) & 0x00ff0000UL) >> 16;
		//unsigned char CP3 = (int(Z_Buffer[i]) & 0x0000ff00UL) >> 8;
		//unsigned char CP4 = (int(Z_Buffer[i]) & 0x000000ffUL);
		//Resources->Z_BufferImage.setPixel(i, 0, sf::Color(CP1, CP2, CP3, CP4));
		Resources->Z_BufferImage.setPixel(i, 0, sf::Color(unsigned int(m_sZ_Buffer[i])));
	}
	Resources->Z_BufferTex.loadFromImage(Resources->Z_BufferImage);

}

void State_Gameplay::CastRaysFloorCeil()
{
	//Cast Floor and Ceiling (Affine mapping)

	//Get Window Size
	float WinH = (float)Window->getSize().y;
	float WinW = (float)Window->getSize().x;

	//Get Player True tilemap position and view direction
	float px = Butcher->x / Level.getTileSize();
	float py = Butcher->y / Level.getTileSize();
	float pDeg = (float)Butcher->DegAngle;//in Deg

	//Camera Rays 
	float rayDirX0;//Leftmost Camera Ray
	float rayDirY0;
	float rayDirX1;//Rightmost Camera Ray
	float rayDirY1;


	float p;
	float posZ;
	float rowDistance = -1.f;

	//Leftmost and Rightmost Coordinates in Tiles hit when screencasting
	float floorX;
	float floorY;

	float floorX2;
	float floorY2;

	//Make sure the ceiling and floor textures are the same size!!!
	//The Ceiling and Floors are tiled at the same time to save CPU cycles
	int texWidth = Resources->Textures.at(Level.getTexCeil()).getSize().x;
	int texHeight = Resources->Textures.at(Level.getTexFloor()).getSize().y;


	//Keeps Vertices to bundle in one draw call
	sf::VertexArray Floor;
	sf::VertexArray Ceiling;


	//FLOOR CASTING
	//Goes middle ->bottom for floor also tiles ceiling by inverting coordinates
	for (int y = 0; y < WinH / 2.f; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		//-sin is due to Y being flipped
		rayDirX0 = cos(LogManager::DegtoRad(pDeg + m_cFov / 2.f));
		rayDirY0 = -sin(LogManager::DegtoRad(pDeg + m_cFov / 2.f));
		rayDirX1 = cos(LogManager::DegtoRad(pDeg - m_cFov / 2.f));
		rayDirY1 = -sin(LogManager::DegtoRad(pDeg - m_cFov / 2.f));

		// Current y position compared to the center of the screen (the horizon) ergo scanline height
		p = WinH / 2.f - y;

		// Vertical position of the camera.
		posZ = m_cdistancetoProj;//0.5 * WinH; assume 45 degrees

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		rowDistance = posZ / p;// +distancetoProj / WinW;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		floorX = (px + rowDistance * rayDirX0);
		floorY = (py + rowDistance * rayDirY0);

		floorX2 = (px + rowDistance * rayDirX1);
		floorY2 = (py + rowDistance * rayDirY1);

		float dX = floorX2 - floorX;
		float dY = floorY2 - floorY;


		// the cell coord is simply got from the integer parts of floorX and floorY
		int cellX = (int)(floorX);
		int cellY = (int)(floorY);

		float fX = floorX - cellX;
		float fY = floorY - cellY;

		// get the texture coordinate from the fractional part
		float tx = texWidth * fX;
		float tx2 = texWidth * (fX + dX);

		float ty = texHeight * (fY);
		float ty2 = texHeight * (fY + dY);


		// floor
		sf::Vertex HFloor[4];

		HFloor[0].position = sf::Vector2f(0, WinH - y);
		HFloor[1].position = sf::Vector2f(0, WinH - y - 1);
		HFloor[2].position = sf::Vector2f(WinW, WinH - y - 1);
		HFloor[3].position = sf::Vector2f(WinW, WinH - y);

		HFloor[0].texCoords = sf::Vector2f(tx, ty);
		HFloor[1].texCoords = sf::Vector2f(tx, ty + 1.f / WinH);
		HFloor[2].texCoords = sf::Vector2f(tx2, ty2 + 1.f / WinH);
		HFloor[3].texCoords = sf::Vector2f(tx2, ty2);

		// ceiling
		sf::Vertex HCeil[4];

		HCeil[0].position = sf::Vector2f(0, (float)y);
		HCeil[1].position = sf::Vector2f(0, y + 1.f);
		HCeil[2].position = sf::Vector2f(WinW, y + 1.f);
		HCeil[3].position = sf::Vector2f(WinW, (float)y);

		HCeil[0].texCoords = sf::Vector2f(tx, ty);
		HCeil[1].texCoords = sf::Vector2f(tx, ty - 1.f / WinH);
		HCeil[2].texCoords = sf::Vector2f(tx2, ty2 - 1.f / WinH);
		HCeil[3].texCoords = sf::Vector2f(tx2, ty2);

		Floor.append(HFloor[0]);
		Floor.append(HFloor[1]);
		Floor.append(HFloor[2]);
		Floor.append(HFloor[3]);
		Floor.setPrimitiveType(sf::Quads);

		Ceiling.append(HCeil[0]);
		Ceiling.append(HCeil[1]);
		Ceiling.append(HCeil[2]);
		Ceiling.append(HCeil[3]);
		Ceiling.setPrimitiveType(sf::Quads);
	}

	ScreenBuffer->draw(Floor, &Resources->Textures.at(Level.getTexFloor()));
	ScreenBuffer->draw(Ceiling, &Resources->Textures.at(Level.getTexCeil()));

	Floor.clear();
	Ceiling.clear();
}

