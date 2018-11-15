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

Sprites* ResourceManagement::getSprite(EntityID id)
{
	if (SpriteMapper.find(id)->second != nullptr)
	 return SpriteMapper.find(id)->second;
}

void ResourceManagement::loadResource()
{
	loadTexture(ID_TEX_SIMON, L"Resources\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	sprites->Add("WalkingRight1", RECT{ 250, 0, 310, 65 }, texSimon);
	sprites->Add("WalkingRight2", RECT{ 310, 0, 370, 65 }, texSimon);
	sprites->Add("WalkingRight3", RECT{ 370, 0, 430, 65 }, texSimon);
	sprites->Add("WalkingRight4", RECT{ 430, 0, 490, 65 }, texSimon);

	//left
	sprites->Add("WalkingLeft1", RECT{ 680, 0, 740, 65 }, texSimon);
	sprites->Add("WalkingLeft2", RECT{ 620, 0, 680, 65 }, texSimon);
	sprites->Add("WalkingLeft3", RECT{ 560, 0, 620, 65  }, texSimon);
	sprites->Add("WalkingLeft4", RECT{ 500, 0, 560, 65 }, texSimon);

	//jump right	
	sprites->Add("JumpRight", RECT{ 190, 0, 250, 48 }, texSimon);

	//jump left
	sprites->Add("JumpLeft", RECT{ 740, 0, 800, 48 }, texSimon);

	//sit down right
	sprites->Add("SitdownRight", RECT{ 190, -15, 250, 48 }, texSimon);

	//sit down left
	sprites->Add("SitdownLeft", RECT{ 740, -15, 800, 48 }, texSimon);


	//facing backward
	//resourceManagement->loadSprites(10040, 857, 65, 891, 131, ID_TEX_SIMON);

	//attack standing right
	sprites->Add("AttackStandRight1", RECT{ 10, 60, 70, 125 }, texSimon);
	sprites->Add("AttackStandRight2", RECT{ 430, 130, 490, 195 }, texSimon);
	sprites->Add("AttackStandRight3", RECT{ 370, 130, 430, 195}, texSimon);
	

	//attack standing left
	sprites->Add("AttackStandLeft1", RECT{ 560, 130, 620, 195 }, texSimon);
	sprites->Add("AttackStandLeft2", RECT{ 500, 130, 560, 195 }, texSimon);
	sprites->Add("AttackStandLeft3", RECT{ 920, 60, 980, 125 }, texSimon);

	//attack Sitdown right
	sprites->Add("AttackSitdownRight1", RECT{ 15, -15, 75, 50 }, texSimon);
	sprites->Add("AttackSitdownRight2", RECT{ 130, -15, 180, 50 }, texSimon);
	sprites->Add("AttackSitdownRight3", RECT{ 70, -15, 130, 50 }, texSimon);

	//attack Sitdown left
	sprites->Add("AttackSitdownLeft1", RECT{ 920, -15, 980, 50 }, texSimon);
	sprites->Add("AttackSitdownLeft2", RECT{ 865, -15, 920, 50 }, texSimon);
	sprites->Add("AttackSitdownLeft3", RECT{ 805, -15, 865, 50 }, texSimon);

	SpriteMapper[EntityID::ID_TEX_SIMON] = sprites;

	loadTexture(ID_TEX_WHIP, L"Resources\\whip.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	sprites->Add("1AttackRight1", RECT{ 13, 17, 29, 65 }, texWhip);
	sprites->Add("1AttackRight2", RECT{ 87, 11, 119, 49 }, texWhip);
	sprites->Add("1AttackRight3", RECT{ 215, 14, 261, 30 }, texWhip);

	sprites->Add("1AttackLeft1", RECT{ 620, 10, 640, 60 }, texWhip);
	sprites->Add("1AttackLeft2", RECT{ 490, 10, 520, 50 }, texWhip);
	sprites->Add("1AttackLeft3", RECT{ 360, 10, 420, 30 }, texWhip);

	//sprites->Add("2AttackRight1", RECT{ 13, 85, 29, 133 }, texWhip);
	//sprites->Add("2AttackRight2", RECT{ 87, 79, 119, 117 }, texWhip);
	//sprites->Add("2AttackRight3", RECT{ 215, 88, 261, 160 }, texWhip);

	//sprites->Add("3AttackRight1", RECT{ 13, 130, 29, 201 }, texWhip);
	//sprites->Add("3AttackRight2", RECT{ 87, 147, 119, 185 }, texWhip);
	//sprites->Add("3AttackRight3", RECT{ 215, 156, 293, 268 }, texWhip);

	
	
	SpriteMapper[EntityID::ID_TEX_WHIP] = sprites;

	loadTexture(ID_TEX_BURNBARREL, L"Resources\\Items\\burn_barrel.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texBurnBarrel = textures->Get(ID_TEX_BURNBARREL);
	sprites->Add("Burn1", RECT{ 0, 0, 32, 64 }, texBurnBarrel);
	sprites->Add("Burn2", RECT{ 32, 0, 64, 64 }, texBurnBarrel);

	SpriteMapper[EntityID::ID_TEX_BURNBARREL] = sprites;

	//load background of menugame.
	textures->Add(ID_TEX_MAINMENU, L"Resources\\Screens\\mainmenu.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMenu = textures->Get(ID_TEX_MAINMENU);
	sprites->Add("Texture1", RECT{ 0, 0, 640, 480 }, texMenu);

	SpriteMapper[EntityID::ID_TEX_MAINMENU] = sprites;

	loadTexture(ID_TEX_GAMEPLAYSCREEN, L"TiledMap\\Entrance.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textPlayScreen = textures->Get(ID_TEX_GAMEPLAYSCREEN);
	sprites->Add("Texture2", RECT{ 0, 0, 640, 480 }, textPlayScreen);

	SpriteMapper[EntityID::ID_TEX_GAMEPLAYSCREEN] = sprites;
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
