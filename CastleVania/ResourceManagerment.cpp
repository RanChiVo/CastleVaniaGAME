#include "ResourceManagement.h"
#include "Direct3DManager.h"

ResourceManagement * ResourceManagement::__instance = nullptr;

D3DXVECTOR2 ResourceManagement::getFontSize(ID3DXFont* font, std::string text)
{
	RECT r;

	if (font)
		font->DrawTextA(nullptr, text.c_str(), -1,&r , DT_CALCRECT, D3DCOLOR_XRGB(255, 0, 255));
	
	return D3DXVECTOR2(r.right - r.left, r.bottom - r.top);
}

Sprites * ResourceManagement::getSprite(EntityID id)
{
	 return this->SpriteMapper.find(id)->second;
}

void ResourceManagement::loadResource()
{
	Sprites* pSprite;

	loadTexture(ID_TEX_SIMON, L"Resources\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	pSprite->Add("WalkingRight1", RECT{ 730, 2, 790, 65 }, texSimon);
	pSprite->Add("WalkingRight1", RECT{ 730, 2, 790, 65 }, texSimon);
	pSprite->Add("WalkingRight2", RECT{ 790, 3, 850, 65 }, texSimon);
	pSprite->Add("WalkingRight3", RECT{ 850, 1, 910, 65 }, texSimon);
	pSprite->Add("WalkingRight4", RECT{ 910, 3, 970, 65 }, texSimon);


	//left
	pSprite->Add("WalkingLeft1", RECT{ 180, 2, 240, 65 }, texSimon);
	pSprite->Add("WalkingLeft2", RECT{ 1, 3, 180, 65 }, texSimon);
	pSprite->Add("WalkingLeft3", RECT{ 60, 1, 120, 65  }, texSimon);
	pSprite->Add("WalkingLeft4", RECT{ 0, 3, 60, 65 }, texSimon);

	//jump right	
	pSprite->Add("JumpRight", RECT{ 670, 0, 730, 48 }, texSimon);

	//jump left
	pSprite->Add("JumpLeft", RECT{ 240, 0, 300, 48 }, texSimon);

	//sit down right
	pSprite->Add("SitdownRight", RECT{ 670, -15, 730, 48 }, texSimon);

	//sit down left
	pSprite->Add("SitdownLeft", RECT{ 240, -15, 300, 48 }, texSimon);


	//facing backward
	//resourceManagement->loadSprites(10040, 857, 65, 891, 131, ID_TEX_SIMON);

	//attack standing right
	pSprite->Add("AttackStandRight1", RECT{ 490, 3, 550, 65 }, texSimon);
	pSprite->Add("AttackStandRight2", RECT{ 550, 3, 610, 65 }, texSimon);
	pSprite->Add("AttackStandRight3", RECT{ 610, 3, 670, 65 }, texSimon);

	//attack standing left
	pSprite->Add("AttackStandLeft1", RECT{ 420, 3, 480, 65 }, texSimon);
	pSprite->Add("AttackStandLeft2", RECT{ 360, 3, 420, 65 }, texSimon);
	pSprite->Add("AttackStandLeft3", RECT{ 300, 3, 360, 65 }, texSimon);

	//attack Sitdown right
	pSprite->Add("AttackSitdownRight1", RECT{ 850, 134, 910, 200 }, texSimon);
	pSprite->Add("AttackSitdownRight2", RECT{ 910, 132, 970, 200 }, texSimon);
	pSprite->Add("AttackSitdownRight3", RECT{ 490, 66, 550, 114 }, texSimon);

	//attack Sitdown left
	pSprite->Add("AttackSitdownLeft1", RECT{ 60, 134, 120, 180 }, texSimon);
	pSprite->Add("AttackSitdownLeft2", RECT{ 0, 132, 60, 180 }, texSimon);
	pSprite->Add("AttackSitdownLeft3", RECT{ 420, 66, 480, 114 }, texSimon);

	SpriteMapper[EntityID::ID_TEX_SIMON] = pSprite;

	loadTexture(ID_TEX_WHIP, L"Resources\\whip.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	pSprite->Add("AttackRight1", RECT{ 130, 10, 190, 60 }, texWhip);
	pSprite->Add("AttackRight2", RECT{ 280, 10, 330, 60 }, texWhip);
	pSprite->Add("AttackRight3", RECT{ 350, 10, 410, 60 }, texWhip);
	
	SpriteMapper[EntityID::ID_TEX_WHIP] = pSprite;

	//load background of menugame.
	textures->Add(ID_TEX_MAINMENU, L"Resources\\Screens\\mainmenu.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMenu = textures->Get(ID_TEX_MAINMENU);
	pSprite->Add("Texture1", RECT{ 0, 0, 640, 480 }, texMenu);

	SpriteMapper[EntityID::ID_TEX_MAINMENU] = pSprite;

	loadTexture(ID_TEX_GAMEPLAYSCREEN, L"map\\mapEntrance.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textPlayScreen = textures->Get(ID_TEX_GAMEPLAYSCREEN);
	pSprite->Add("Texture2", RECT{ 0, 0, 640, 480 }, textPlayScreen);

	SpriteMapper[EntityID::ID_TEX_GAMEPLAYSCREEN] = pSprite;

}

void ResourceManagement::loadFont(LPTSTR path)
{
	LPDIRECT3DDEVICE9 gDevice = Direct3DManager::getInstance()->GetDirect3DDevice();

	AddFontResourceEx(path, FR_PRIVATE, NULL);

	HRESULT result = D3DXCreateFont(
		gDevice, 20, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);
}

void ResourceManagement::loadTexture(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	textures->Add(id, filePath, transparentColor);
}

void ResourceManagement::loadSprites(std::string id, RECT r, int idCharater)
{
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(idCharater);
	sprites->Add(id, r, texSimon);
}

//void ResourceManagerment::loadAnimation(int time
//{
//	Animations * animations = Animations::GetInstance();
//	LPANIMATION ani;
//
//}

ResourceManagement::ResourceManagement()
{
	textures = Textures::GetInstance();
	sprites = Sprites::GetInstance();
	Getanimations = Animations::GetInstance();
}

ResourceManagement * ResourceManagement::GetInstance()
{
	if (__instance == nullptr) __instance = new ResourceManagement();
	return __instance;
}

ResourceManagement::~ResourceManagement()
{
}
