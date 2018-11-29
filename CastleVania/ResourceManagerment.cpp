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

TiledMap * ResourceManagement::getTiledMap(EntityID id)
{
	if (TiledMapList.find(id)->second != nullptr)
		return TiledMapList.find(id)->second;
}

void ResourceManagement::loadResource()
{
	loadTexture(ID_TEX_SIMON, L"Resources\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	sprites->Add("Walking1", RECT{ 0, 0, 60, 66 }, texSimon);
	sprites->Add("Walking2", RECT{ 60, 0, 120, 66 }, texSimon);
	sprites->Add("Walking3", RECT{ 120, 0, 180, 66 }, texSimon);
	sprites->Add("Walking4", RECT{ 180, 0, 240, 66 }, texSimon);


	//jump right	
	sprites->Add("Jump", RECT{ 240, 0, 300, 66 }, texSimon);

	//sit down right
	sprites->Add("Sitdown", RECT{ 240, -9, 300, 57 }, texSimon);

	//facing backward
	//resourceManagement->loadSprites(10040, 857, 65, 891, 131, ID_TEX_SIMON);

	//attack standing right
	sprites->Add("AttackStand1", RECT{ 300, 66, 360, 132 }, texSimon);
	sprites->Add("AttackStand2", RECT{ 360, 66, 420, 132 }, texSimon);
	sprites->Add("AttackStand3", RECT{ 420, 66, 480, 132}, texSimon);
	
	//attack Sitdown right
	sprites->Add("AttackSitdown1", RECT{ 300, -9, 360, 57 }, texSimon);
	sprites->Add("AttackSitdown2", RECT{ 360, -9, 420, 57 }, texSimon);
	sprites->Add("AttackSitdown3", RECT{ 420, -9, 480, 57 }, texSimon);

	//change color right
	sprites->Add("1ChangeColor1", RECT{ 180, 264, 240, 330 }, texSimon);
	sprites->Add("1ChangeColor2", RECT{ 240, 264, 300, 330 }, texSimon);
	sprites->Add("1ChangeColor3", RECT{ 300, 264, 360, 330 }, texSimon);

	//change color left

	sprites->Add("2ChangeColor1", RECT{ 0, 198, 60, 264 }, texSimon);
	sprites->Add("2ChangeColor2", RECT{ 60, 198, 120, 264 }, texSimon);
	sprites->Add("2ChangeColor3", RECT{ 120, 198, 180, 264 }, texSimon);

	SpriteMapper[EntityID::ID_TEX_SIMON] = sprites;

	loadTexture(ID_TEX_WHIP, L"Resources\\whip.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);

	sprites->Add("1Attack1", RECT{ 0, 7, 18, 55 }, texWhip);
	sprites->Add("1Attack2", RECT{ 41, 1, 73, 39 }, texWhip);
	sprites->Add("1Attack3", RECT{ 95, 5, 141, 21 }, texWhip);

	sprites->Add("2Attack1", RECT{ 0, 60, 18, 110 }, texWhip);
	sprites->Add("2Attack2", RECT{ 40, 58, 72, 96 }, texWhip);
	sprites->Add("2Attack3", RECT{ 94, 68, 172, 80 }, texWhip);

	sprites->Add("3Attack1", RECT{ 0, 124, 18, 170 }, texWhip);
	sprites->Add("3Attack2", RECT{ 40, 118, 72, 156 }, texWhip);
	sprites->Add("3Attack3", RECT{ 94, 128, 172, 140 }, texWhip);

	sprites->Add("4Attack1", RECT{ 0, 184, 18, 230 }, texWhip);
	sprites->Add("4Attack2", RECT{ 40, 178, 72, 216 }, texWhip);
	sprites->Add("4Attack3", RECT{ 94, 188, 172, 200 }, texWhip);
	
	SpriteMapper[EntityID::ID_TEX_WHIP] = sprites;

	loadTexture(ID_TEX_BURNBARREL, L"Resources\\Items\\burn_barrel.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texBurnBarrel = textures->Get(ID_TEX_BURNBARREL);
	loadTexture(ID_TEX_EFFECT, L"Resources\\Items\\effect.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texEffect = textures->Get(ID_TEX_EFFECT);
	sprites->Add("Burn1", RECT{ 0, 0, 32, 64 }, texBurnBarrel);
	sprites->Add("Burn2", RECT{ 32, 0, 64, 64 }, texBurnBarrel);
	sprites->Add("Effect1", RECT{ 20, 0, 50, 40}, texEffect);
	sprites->Add("Effect2", RECT{ 60, 0, 70, 40 }, texEffect);
	sprites->Add("Effect3", RECT{ 100, 0, 120, 40 }, texEffect);
	sprites->Add("Effect4", RECT{ 140, 0, 160, 40 }, texEffect);

	SpriteMapper[EntityID::ID_TEX_BURNBARREL] = sprites;
	
	textures->Add(ID_TEX_MAINMENU, L"Resources\\Screens\\mainmenu.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMenu = textures->Get(ID_TEX_MAINMENU);
	sprites->Add("Texture1", RECT{ 0, 0, 640, 480 }, texMenu);

	SpriteMapper[EntityID::ID_TEX_MAINMENU] = sprites;

	loadTexture(ID_TEX_HEART, L"Resources\\Items\\heart.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texHeart = textures->Get(ID_TEX_HEART);
	sprites->Add("Heart1", RECT{ 0, 0, 24, 20 }, texHeart);

	SpriteMapper[EntityID::ID_TEX_HEART] = sprites;

	loadTexture(ID_TEX_WEAPON_REWARD, L"Resources\\Items\\weapon_reward.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texWeapon_reward = textures->Get(ID_TEX_WEAPON_REWARD);
	sprites->Add("weapon_reward1", RECT{ 0, 0, 30, 30 }, texWeapon_reward);

	SpriteMapper[EntityID::ID_TEX_WEAPON_REWARD] = sprites;
	
	loadTexture(ID_TEX_KATANA, L"Resources\\Items\\katana.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texKatana = textures->Get(ID_TEX_KATANA);
	sprites->Add("katana1", RECT{ 0, 0, 30, 20 }, texKatana);

	SpriteMapper[EntityID::ID_TEX_KATANA] = sprites;

	loadTexture(ID_TEX_MIRACULOUS_BAG, L"Resources\\Items\\miraculous_bag.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMiraculous_bag = textures->Get(ID_TEX_MIRACULOUS_BAG);
	sprites->Add("miraculous_bag1", RECT{ 0, 0, 30, 30 }, texMiraculous_bag);
	sprites->Add("miraculous_bag2", RECT{ 30, 0, 60, 30 }, texMiraculous_bag);
	sprites->Add("miraculous_bag3", RECT{ 60, 0, 90, 30 }, texMiraculous_bag);

	SpriteMapper[EntityID::ID_TEX_MIRACULOUS_BAG] = sprites;

	loadTexture(ID_TEX_BRICK, L"Resources\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	LPDIRECT3DTEXTURE9 texBrick = textures->Get(ID_TEX_BRICK);
	sprites->Add("brick1", RECT{ 408, 225, 424, 241 }, texBrick);

	SpriteMapper[EntityID::ID_TEX_BRICK] = sprites;

	TiledMap* tiled_map = new TiledMap();

	textures->Add(ID_TEX_MAP_ENTRANCE, L"TiledMap\\Entrance.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 textMap_Entrance = textures->Get(ID_TEX_MAP_ENTRANCE);

	tiled_map->readMapfromfile("TiledMap\\Entrance.tmx", textMap_Entrance);

	TiledMapList[EntityID::ID_TEX_MAP_ENTRANCE] = tiled_map;

	tiled_map = new TiledMap();

	textures->Add(ID_TEX_GAMEPLAYSCREEN, L"TiledMap\\GamePlay1.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 textPlayScreen = textures->Get(ID_TEX_GAMEPLAYSCREEN);

	tiled_map->readMapfromfile("TiledMap\\GamePlay.tmx", textPlayScreen);

	TiledMapList[EntityID::ID_TEX_MAP_PLAYGAME] = tiled_map;
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
