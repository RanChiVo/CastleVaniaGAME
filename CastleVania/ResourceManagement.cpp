#include "ResourceManagement.h"
#include "Direct3DManager.h"
#include "Library/pugixml.hpp"

ResourceManagement * ResourceManagement::__instance = nullptr;

D3DXVECTOR2 ResourceManagement::getFontSize(ID3DXFont* font, std::string text)
{
	RECT r;

	if (font)
		font->DrawTextA(nullptr, text.c_str(), -1, &r, DT_CALCRECT, D3DCOLOR_XRGB(255, 0, 255));

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
	Textures::GetInstance()->Add(ID_ENTITY_BBOX, L"Resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	readSpriteFromFile("Resources\\simon.xml");
	readAnimationFromFile("Resources\\simonAnimation.xml");

	readSpriteFromFile("Resources\\whip.xml");
	readAnimationFromFile("Resources\\whipAnimation.xml");

	readSpriteFromFile("Resources\\Items\\burn_barrel.xml");
	readAnimationFromFile("Resources\\Items\\burn_barrelAnimation.xml");

	readSpriteFromFile("Resources\\Items\\effect_fire.xml");
	readAnimationFromFile("Resources\\Items\\effect_fireAnimation.xml");

	readSpriteFromFile("Resources\\Items\\effect_money.xml");
	readAnimationFromFile("Resources\\Items\\effect_moneyAnimation.xml");

	readSpriteFromFile("Resources\\Items\\star.xml");
	readAnimationFromFile("Resources\\Items\\starAnimation.xml");

	readSpriteFromFile("Resources\\Items\\heart.xml");
	readAnimationFromFile("Resources\\Items\\heartAnimation.xml");

	readSpriteFromFile("Resources\\Items\\weapon_reward.xml");
	readAnimationFromFile("Resources\\Items\\weapon_rewardAnimation.xml");

	readSpriteFromFile("Resources\\Items\\katana.xml");
	readAnimationFromFile("Resources\\Items\\katanaAnimation.xml");

	readSpriteFromFile("Resources\\Items\\miraculous_bag.xml");
	readAnimationFromFile("Resources\\Items\\miraculous_bagAnimation.xml");

	readSpriteFromFile("Resources\\Enemy\\zombie.xml");
	readAnimationFromFile("Resources\\Enemy\\zombieAnimation.xml");

	readSpriteFromFile("TiledMap\\Candle.xml");
	readAnimationFromFile("TiledMap\\CandleAnimation.xml");

	readSpriteFromFile("TiledMap\\WallCastle.xml");
	readAnimationFromFile("TiledMap\\WallCastleAnimation.xml");

	readSpriteFromFile("Resources\\Items\\small_heart.xml");
	readAnimationFromFile("Resources\\Items\\small_heartAnimation.xml");

	readSpriteFromFile("Resources\\Items\\fire_bomb.xml");
	readAnimationFromFile("Resources\\Items\\firebombAnimation.xml");

	readSpriteFromFile("Resources\\Items\\cross.xml");
	readAnimationFromFile("Resources\\Items\\crossAnimation.xml");

	readSpriteFromFile("Resources\\Items\\stop_watch.xml");
	readAnimationFromFile("Resources\\Items\\stop_watchAnimation.xml");

	readSpriteFromFile("Resources\\Enemy\\black_leopard.xml");
	readAnimationFromFile("Resources\\Enemy\\black_leopardAnimation.xml");

	/*readSpriteFromFile("Resources\\MenuPoint\\black.xml");*/
	readSpriteFromFile("Resources\\MenuPoint\\HP.xml");
	readSpriteFromFile("Resources\\MenuPoint\\enemy_HP.xml");
	readSpriteFromFile("Resources\\MenuPoint\\lost_HP.xml");
	readSpriteFromFile("Resources\\MenuPoint\\place_item.xml");

	//readSpriteFromFile("Resources\\MenuPoint\\double_shot.xml");
	//readSpriteFromFile("Resources\\MenuPoint\\double_shoot.xml");
	//readSpriteFromFile("Resources\\MenuPoint\\triple_shot.xml");
	//readSpriteFromFile("Resources\\MenuPoint\\triple_shoot.xml");
	textures->Add(ID_ENTITY_MAP_ENTRANCE, L"TiledMap\\Entrance_bank.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textMap_Entrance = textures->Get(ID_ENTITY_MAP_ENTRANCE);
	TiledMap* tiled_map = new TiledMap("TiledMap\\Entrance_map.tmx", textMap_Entrance);
	TiledMapList[EntityID::ID_ENTITY_MAP_ENTRANCE] = tiled_map;

	textures->Add(ID_ENTITY_GAMEPLAYSCREEN, L"TiledMap\\GamePlay_bank.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textPlayScreen = textures->Get(ID_ENTITY_GAMEPLAYSCREEN);
	tiled_map = new TiledMap("TiledMap\\GamePlay_map.tmx", textPlayScreen);
	TiledMapList[EntityID::ID_ENTITY_MAP_PLAYGAME] = tiled_map;
}

void ResourceManagement::readAnimationFromFile(std::string resourcepath)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(resourcepath.c_str());

	if (!result)
	{
		OutputDebugString(L"[ERROR] Reading failed\n");
		return;
	}

	auto sourceDoc = doc.child("loadresource").child("animations");

	for (auto aniDoc : sourceDoc.children("animation"))
	{
		std::string idAnimation = aniDoc.attribute("name").as_string();
		int defaultTime = aniDoc.attribute("default_time").as_int();
		LPANIMATION animation = new Animation(defaultTime);

		for (auto aniFrame : aniDoc.children("animation_frame"))
		{
			animation->Add(aniFrame.attribute("sprite_id").as_string());
		}
		ANI_ID aniID = stringToAniID[idAnimation];
		Getanimations->Add(aniID, animation);
	}

}

void ResourceManagement::readSpriteFromFile(std::string resourcepath)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(resourcepath.c_str());

	if (!result)
	{
		OutputDebugString(L"[ERROR] Reading failed\n");
		return;
	}

	auto sourceDoc = doc.child("loadresource");
	std::string idText = sourceDoc.child("imagelayer").attribute("id").as_string();
	EntityID idTextfromfile = stringToEntityID[idText];

	std::string pathImage = sourceDoc.child("imagelayer").child("image").attribute("source").as_string();
	std::wstring pathImagefromfile(pathImage.begin(), pathImage.end());

	LPCWSTR pathImageLoad = pathImagefromfile.c_str();
	loadTexture(idTextfromfile, pathImageLoad, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texID = textures->Get(idTextfromfile);
	textures->setSizeObject(idTextfromfile, sourceDoc.child("imagelayer").attribute("width").as_int(),
		sourceDoc.child("imagelayer").attribute("height").as_int());

	auto sprites = sourceDoc.child("sprites");
	for (auto sprite : sprites.children("spriteframe"))
	{
		std::string id_sprite_from_file = sprite.attribute("id").as_string();
		int l, t, r, b;
		RECT rect = RECT{};
		l = sprite.attribute("left").as_int();	t = sprite.attribute("top").as_int();
		b = sprite.attribute("bottom").as_int(); r = sprite.attribute("right").as_int();
		rect.left = l; rect.top = t;
		rect.right = r; rect.bottom = b;
		this->sprites->Add(id_sprite_from_file, rect, texID);
	}
	SpriteMapper[idTextfromfile] = this->sprites;
}

void ResourceManagement::loadFont(LPTSTR path)
{
	LPDIRECT3DDEVICE9 gDevice = Direct3DManager::getInstance()->GetDirect3DDevice();

	AddFontResourceEx(path, FR_PRIVATE, NULL);

	HRESULT result = D3DXCreateFont(
		gDevice, 17, 0, FW_NORMAL, 1, false,
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

	stringToEntityID = {
	{"ID_ENTITY_SIMON",EntityID::ID_ENTITY_SIMON },
	{"ID_ENTITY_MAINMENU",EntityID::ID_ENTITY_MAINMENU },
	{"ID_ENTITY_GAMEPLAYSCREEN",EntityID::ID_ENTITY_GAMEPLAYSCREEN },
	{"ID_ENTITY_WHIP",EntityID::ID_ENTITY_WHIP },
	{"ID_ENTITY_BURNBARREL",EntityID::ID_ENTITY_BURNBARREL },
	{"ID_ENTITY_BBOX",EntityID::ID_ENTITY_BBOX },
	{"ID_ENTITY_HEART",EntityID::ID_ENTITY_HEART },
	{"ID_ENTITY_EFFECT",EntityID::ID_ENTITY_EFFECT },
	{"ID_ENTITY_STAR",EntityID::ID_ENTITY_STAR },
	{"ID_ENTITY_WEAPON_REWARD",EntityID::ID_ENTITY_WEAPON_REWARD },
	{"ID_ENTITY_DAGGER",EntityID::ID_ENTITY_DAGGER },
	{"ID_ENTITY_MIRACULOUS_BAG",EntityID::ID_ENTITY_MIRACULOUS_BAG },
	{"ID_ENTITY_RED_100_MIRACULOUS_BAG",EntityID::ID_ENTITY_RED_100_MIRACULOUS_BAG},
	{"ID_ENTITY_BLUE_400_MIRACULOUS_BAG",EntityID::ID_ENTITY_BLUE_400_MIRACULOUS_BAG},
	{"ID_ENTITY_WHITE_700_MIRACULOUS_BAG",EntityID::ID_ENTITY_WHITE_700_MIRACULOUS_BAG},
	{"ID_ENTITY_BONUS_1000_MIRACULOUS_BAG",EntityID::ID_ENTITY_BONUS_1000_MIRACULOUS_BAG},
	{"ID_ENTITY_WALL",EntityID::ID_ENTITY_WALL },
	{"ID_ENTITY_FLOOR",EntityID::ID_ENTITY_FLOOR },
	{"ID_ENTITY_ENTRANCE",EntityID::ID_ENTITY_ENTRANCE },
	{"ID_ENTITY_DAGGER_WEAPON",EntityID::ID_ENTITY_DAGGER_WEAPON },
	{"ID_ENTITY_MAP_ENTRANCE",EntityID::ID_ENTITY_MAP_ENTRANCE },
	{"ID_ENTITY_MAP_PLAYGAME",EntityID::ID_ENTITY_MAP_PLAYGAME },
	{"ID_ENTITY_CASTLEVANIA_WALL",EntityID::ID_ENTITY_CASTLEVANIA_WALL },
	{"ID_ENTITY_CANDLE",EntityID::ID_ENTITY_CANDLE },
	{"ID_ENTITY_PODIUM_ON_WALL",EntityID::ID_ENTITY_PODIUM_ON_WALL },
	{"ID_ENTITY_WALL_ENTRANCE",EntityID::ID_ENTITY_WALL_ENTRANCE },
	{"ID_ENTITY_ZOMBIE",EntityID::ID_ENTITY_ZOMBIE },
	{"ID_ENTITY_SMALL_HEART",EntityID::ID_ENTITY_SMALL_HEART },
	{"ID_ENTITY_CROSS",EntityID::ID_ENTITY_CROSS },
	{"ID_ENTITY_FIRE_BOMB",EntityID::ID_ENTITY_FIRE_BOMB },
	{"ID_ENTITY_HP", EntityID::ID_ENTITY_HP },
	{"ID_ENTITY_HP_ENEMY", EntityID::ID_ENTITY_HP_ENEMY },
	{"ID_ENTITY_LOST_HP", EntityID::ID_ENTITY_LOST_HP },
	{"ID_ENTITY_PLACE", EntityID::ID_ENTITY_PLACE},
	{"ID_ENTITY_BLACK_LEOPARD", EntityID::ID_ENTITY_BLACK_LEOPARD},
	};
	stringToAniID = {
	{"SIMON_ANI_IDLE", ANI_ID::SIMON_ANI_IDLE },
	{"SIMON_ANI_WALKING", ANI_ID::SIMON_ANI_WALKING},
	{"SIMON_ANI_JUMPING", ANI_ID::SIMON_ANI_JUMPING},
	{"SIMON_ANI_SITDOWN", ANI_ID::SIMON_ANI_SITDOWN},
	{"SIMON_ANI_ATTACK_STANDING", ANI_ID::SIMON_ANI_ATTACK_STANDING},
	{"SIMON_ANI_ATTACK_SITDOWN", ANI_ID::SIMON_ANI_ATTACK_SITDOWN},
	{"SIMON_ANI_COLOR", ANI_ID::SIMON_ANI_COLOR},
	{"SIMON_ANI_COLOR1", ANI_ID::SIMON_ANI_COLOR1},
	{"SIMON_ANI_HURT", ANI_ID::SIMON_ANI_HURT},
	{"TYPE1_WHIP",ANI_ID::TYPE1_WHIP},
	{"TYPE2_WHIP", ANI_ID::TYPE2_WHIP},
	{"TYPE3_WHIP",ANI_ID::TYPE3_WHIP},
	{"TYPE4_WHIP",ANI_ID::TYPE4_WHIP},
	{"BURNBARREL_ANI", ANI_ID::BURNBARREL_ANI},
	{"CANDLE_ANI", ANI_ID::CANDLE_ANI},
	{"ANI_EFFECT", ANI_ID::ANI_EFFECT},
	{"EFFECT_100_MONEY_ANI", ANI_ID::EFFECT_100_MONEY_ANI},
	{"EFFECT_400_MONEY_ANI", ANI_ID::EFFECT_400_MONEY_ANI},
	{"EFFECT_700_MONEY_ANI", ANI_ID::EFFECT_700_MONEY_ANI},
	{"EFFECT_1000_MONEY_ANI", ANI_ID::EFFECT_1000_MONEY_ANI},
	{"HEART_ANI", ANI_ID::HEART_ANI},
	{"WEAPONREWARD_ANI", ANI_ID::WEAPONREWARD_ANI},
	{"DAGGER_ANI", ANI_ID::DAGGER_ANI},
	{"RED_MIRACULOUSBAG_ANI", ANI_ID::RED_MIRACULOUSBAG_ANI},
	{"BLUE_MIRACULOUSBAG_ANI", ANI_ID::BLUE_MIRACULOUSBAG_ANI},
	{"WHITE_MIRACULOUSBAG_ANI", ANI_ID::WHITE_MIRACULOUSBAG_ANI},
	{"BONUS_MIRACULOUSBAG_ANI", ANI_ID::BONUS_MIRACULOUSBAG_ANI},
	{"CASTLE_ANI", ANI_ID::CASTLE_ANI},
	{"SIMON_ANI_GO_STAIR", ANI_ID::SIMON_ANI_GO_STAIR},
	{"SIMON_ANI_IDLE_STAIR", ANI_ID::SIMON_ANI_IDLE_STAIR},
	{"ZOMBIE_ANI_WALKING", ANI_ID::ZOMBIE_ANI_WALKING},
	{"SMALL_HEART_ANI", ANI_ID::SMALL_HEART_ANI},
	{"STOP_WATCH_ANI", ANI_ID::STOP_WATCH_ANI},
	{"CROSS_ANI", ANI_ID::CROSS_ANI},
	{"FIRE_BOMB_ANI", ANI_ID::FIRE_BOMB_ANI},
	{"BLACK_LEOPARD_ANI_IDLE", ANI_ID::BLACK_LEOPARD_ANI_IDLE},
	{"BLACK_LEOPARD_ANI_MOVE", ANI_ID::BLACK_LEOPARD_ANI_MOVE},
	};
}

ResourceManagement * ResourceManagement::GetInstance()
{
	if (__instance == nullptr) __instance = new ResourceManagement();
	return __instance;
}

std::unordered_map<std::string, EntityID> ResourceManagement::getStringToEntity()
{
	return stringToEntityID;
}

ResourceManagement::~ResourceManagement()
{
}