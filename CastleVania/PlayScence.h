#pragma once
#include "Scene.h"
#include "GameObjects/Simon.h"

class PlayScene: public Scene
{
protected:
	Simon* Player;
	vector<LPGAMEOBJECT> objects;
	ID3DXFont* font = nullptr;
	TiledMap* tiled_map;

	std::unordered_map<std::string, EntityID> StringToEntityID;
	std::unordered_map<std::string, ANI_ID> StringToAniID;
	std::unordered_map<EntityID, Sprites*> SpriteMapper;
	std::unordered_map<EntityID, TiledMap*> TiledMapList;

	void ReadFile_FONTS(std::string path);
	void ReadFile_TEXTURES(std::string path);
	void ReadFile_SPRITES(std::string path);
	void ReadFile_ANIMATIONS(std::string path);
	void ReadFile_ANIMATION_SETS(std::string path);
	void ReadFile_OBJECTS(std::string path);
public:
	PlayScene(int id, std::string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	~PlayScene();
};

