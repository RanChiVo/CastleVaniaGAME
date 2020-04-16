#pragma once
#include "Scene.h"
#include "GameObjects/Simon.h"
#include "MenuPoint.h"
#include "TiledMap.h"
#include "CastleWall.h"

class PlayScene: public Scene
{
protected:
	CastleWall* castleWall;
	Simon* player;
	vector<LPGAMEOBJECT> objects;
	ID3DXFont* font = nullptr;
	TiledMap* tiled_map;
	MenuPoint* menuPoint;
	Viewport* viewport;

	void ReadFile_FONTS(LPTSTR path);
	void ReadFile_TEXTURES(pugi::xml_node node, LPDIRECT3DTEXTURE9 &texID);
	void ReadFile_SPRITES(pugi::xml_node node, LPDIRECT3DTEXTURE9 texID);
	void ReadFile_ANIMATIONS(pugi::xml_node node);
	void ReadFile_OBJECTS(pugi::xml_node node);
public:
	PlayScene(EntityID id, std::string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render(Viewport* viewport);
	virtual void Unload();
	void UpdateViewport(DWORD dt);

	~PlayScene();
};

