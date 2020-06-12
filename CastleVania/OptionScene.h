#pragma once
#include "Scene.h"
#include "SpriteManagements/Sprite.h"
#include "MenuPoint.h"

class OptionScene: public Scene
{
	ID3DXFont *font;
	RECT R;
	Sprite* heart;
	std::string content;
	MenuPoint* menuPoint;
	D3DXVECTOR2 positionHeart;
public:
	OptionScene(EntityID id, std::string filePath);
	void Load();
	void Unload();
    void Update(DWORD dt);
	void Render(Viewport* viewport);
	void ReadFile_FONTS(LPTSTR path);
	void SetPosHeart(D3DXVECTOR2 pos);
	D3DXVECTOR2 GetPosHeart();
	~OptionScene();
};

class OptionSceneKeyHandler : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	OptionSceneKeyHandler(Scene *s) :ScenceKeyHandler(s) {};
};
