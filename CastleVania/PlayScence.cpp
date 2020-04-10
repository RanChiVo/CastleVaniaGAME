#include "PlayScence.h"



PlayScene::PlayScene(int id, std::string filePath)
{

}

void PlayScene::Load()
{
}

void PlayScene::Update(DWORD dt)
{
}

void PlayScene::Render()
{
}

void PlayScene::Unload()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::ReadFile_FONTS(std::string path)
{
	LPDIRECT3DDEVICE9 gDevice = Direct3DManager::getInstance()->GetDirect3DDevice();

	AddFontResourceEx(path, FR_PRIVATE, NULL);

	HRESULT result = D3DXCreateFont(
		gDevice, 17, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);
}

void PlayScene::ReadFile_TEXTURES(std::string path)
{
}

void PlayScene::ReadFile_SPRITES(std::string path)
{
}

void PlayScene::ReadFile_ANIMATIONS(std::string path)
{
}

void PlayScene::ReadFile_ANIMATION_SETS(std::string path)
{
}

void PlayScene::ReadFile_OBJECTS(std::string path)
{
}
