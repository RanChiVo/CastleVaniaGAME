#include "PlayScence.h"
#include "Textures/Textures.h"	
#include "SpriteManagements/Sprites.h"
#include "Animations/Animation.h"
#include "Animations/Animations.h"
#include "GameObjects/Floor.h"
#include "Door.h"
#include "Brick.h"
#include "GameObjects/BurnBarrel.h"
#include "VampireBat.h"
#include "Wall.h"
#include "Candle.h"
#include "GameObjects/Entrance.h"
#include "SpawnEnemy.h"
#include "FishMan.h"
#include "DarkBat.h"
#include "CastleWall.h"
#include "Panther.h"
#include "ObjectGridCreation.h"
#include "../CastleVania/GameObjects/Whip.h"
#include "Portal.h"
#include "PortalPosMap.h"
#include "ActivationBox.h"
#include "Crown.h"
#include "SpearKnight.h"
#include "MovingBrick.h"
#include "Ghost.h"
#include "Fleamen.h"

PlayScene::PlayScene(EntityID id, std::string filePath) :Scene(id, filePath)
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	menuPoint = new MenuPoint();
	viewport = Direct3DManager::getInstance()->getViewport();
}

void PlayScene::Load()
{
	ReadFile_FONTS(L"Resources\\Fonts\\prstart.ttf");

	Textures::GetInstance()->Add(ID_ENTITY_BBOX, L"Resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	pugi::xml_document docMap;

	if (!docMap.load_file(sceneFilePath.c_str()))
	{
		DebugOut(L"[ERROR] Read Screne file failed\n", sceneFilePath);
		return;
	}

	std::string objectPath = "";

	for (auto property : docMap.child("map").child("properties").children("property"))
	{
		std::string name = property.attribute("name").as_string();
		if (name.compare("ObjectPath") == 0)
		{
			objectPath = property.attribute("value").as_string();
		}
		else if (name.compare("StartViewportX") == 0)
		{
			viewport->setStartViewPortX(property.attribute("value").as_float());
		}
		else if (name.compare("EndViewportX") == 0)
		{
			viewport->setEndViewPortX(property.attribute("value").as_float());
		}
		else if (name.compare("StartViewportY") == 0)
		{
			viewport->setStartViewPortY(property.attribute("value").as_float());
		}
	}

	pugi::xml_document docObject;

	if (!docObject.load_file(objectPath.c_str()))
	{
		DebugOut(L"[ERROR] Read Objects file failed\n", objectPath);
		return;
	}

	for (auto object : docObject.child("objectList"))
	{
		std::string pathSprite = object.attribute("spritePath").as_string();
		std::string pathAni = object.attribute("animationPath").as_string();
		pugi::xml_document docSprite;
		pugi::xml_document docAni;
		LPDIRECT3DTEXTURE9 texID = NULL;

		if (!docSprite.load_file(pathSprite.c_str()))
		{
			DebugOut(L"[ERROR] Reading Objects file is failed\n", pathSprite);
			return;
		}

		ReadFile_TEXTURES(docSprite.child("loadresource").child("imagelayer"), texID);

		if (!texID)
		{
			OutputDebugString(L"[ERROR] Read image is failed \n");
			return;
		}

		ReadFile_SPRITES(docSprite.child("loadresource").child("sprites"), texID);

		if (!pathAni.empty())
		{
			if (!docAni.load_file(pathAni.c_str()))
			{
				DebugOut(L"[ERROR] Read Objects file is failed\n", pathAni);
				return;
			}
		}

		ReadFile_ANIMATIONS(docAni.child("loadresource").child("animations"));
	}

	tiled_map = new TiledMap(docMap.child("map"));

	tiled_map->readMapfromfile();

	ReadFile_OBJECTS(docMap.child("map"));

	menuPoint->loadResource();
}

void PlayScene::Update(DWORD dt)
{
	tiled_map->Update(dt);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);
		if (objects[i]->GetState() == objects[i]->STATE_DETROY)
		{
			objects.erase(objects.begin() + i);
		}
	}

	player->Update(dt, &objects);

	UpdateViewport(dt);

	menuPoint->update(dt);
}

void PlayScene::Render(Viewport* viewport)
{
	menuPoint->Draw(font);

	tiled_map->draw(viewport);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render(viewport);
	}

	player->Render(viewport);


	if (castleWall)
	{
		castleWall->Render(viewport);
	}
}

void PlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	castleWall = nullptr;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void PlayScene::UpdateViewport(DWORD dt)
{
	if (viewport->getState() == viewport->STATE_ACTION)
	{
		int widthframeSimon = player->getWidth();
		D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};

		newPosViewport.x = player->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
		newPosViewport.y = int((player->getPosition().y - EXTRA_HEIGHT_SCREEN) / 384) *384;

		newPosViewport.x = min(viewport->getEndViewportX() + 24 - viewport->getWidth(), newPosViewport.x);
		newPosViewport.y = min(384 * 2, newPosViewport.y);
		newPosViewport.x = max(viewport->getStartViewportX(), newPosViewport.x);
		viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
	}
	else return;
}

PlayScene::~PlayScene()
{
}

void PlayScene::ReadFile_FONTS(LPTSTR path)
{
	LPDIRECT3DDEVICE9 gDevice = Direct3DManager::getInstance()->GetDirect3DDevice();

	AddFontResourceEx(path, FR_PRIVATE, NULL);

	HRESULT result = D3DXCreateFont(
		gDevice, 17, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);
}

void PlayScene::ReadFile_TEXTURES(pugi::xml_node node, LPDIRECT3DTEXTURE9 &texID)
{
	std::string idText = node.attribute("id").as_string();
	EntityID idTextfromfile = Utils::getInstance()->getStringToEntityID()[idText];
	std::string pathImage = node.child("image").attribute("source").as_string();
	std::wstring pathImagefromfile(pathImage.begin(), pathImage.end());
	LPCWSTR pathImageLoad = pathImagefromfile.c_str();

	Textures::GetInstance()->Add(idTextfromfile, pathImageLoad, D3DCOLOR_XRGB(255, 0, 255));
	texID = Textures::GetInstance()->Get(idTextfromfile);
	Textures::GetInstance()->setSizeObject(idTextfromfile, node.attribute("width").as_int(),
		node.attribute("height").as_int());
}

void PlayScene::ReadFile_SPRITES(pugi::xml_node node, LPDIRECT3DTEXTURE9 texID)
{
	for (auto sprite : node.children("spriteframe"))
	{
		std::string id_sprite_from_file = sprite.attribute("id").as_string();
		int l, t, r, b;
		RECT rect = RECT{};
		l = sprite.attribute("left").as_int();	t = sprite.attribute("top").as_int();
		b = sprite.attribute("bottom").as_int(); r = sprite.attribute("right").as_int();
		rect.left = l; rect.top = t;
		rect.right = r; rect.bottom = b;
		Sprites::GetInstance()->Add(id_sprite_from_file, rect, texID);
	}
}

void PlayScene::ReadFile_ANIMATIONS(pugi::xml_node sourceAnimation)
{
	EntityID ani_set_id = Utils::getInstance()->getStringToEntityID()[sourceAnimation.attribute("id").as_string()];

	LPANIMATION_SET setAnimations = new AnimationSet();

	for (auto aniDoc : sourceAnimation.children("animation"))
	{
		std::string idAnimation = aniDoc.attribute("name").as_string();
		int defaultTime = aniDoc.attribute("default_time").as_int();
		LPANIMATION animation = new Animation(defaultTime);

		for (auto aniFrame : aniDoc.children("animation_frame"))
		{
			animation->Add(aniFrame.attribute("sprite_id").as_string());
		}
		ANI_ID aniID = Utils::getInstance()->getStringToAniID()[idAnimation];
		Animations::GetInstance()->Add(aniID, animation);
		setAnimations->emplace(aniID, Animations::GetInstance()->Get(aniID));
	}
	AnimationSets::GetInstance()->Add(ani_set_id, setAnimations);
}

void PlayScene::ReadFile_OBJECTS(pugi::xml_node node)
{
	for (auto objectGroupNode : node.children("objectgroup"))
	{
		for (auto objectNode : objectGroupNode.children("object"))
		{
			int id = objectNode.attribute("id").as_int();
			std::string objectType = objectGroupNode.attribute("name").as_string();
			std::string name = objectNode.attribute("name").as_string();
			float x = objectNode.attribute("x").as_float();
			float y = objectNode.attribute("y").as_float() + EXTRA_HEIGHT_SCREEN;
			int width = objectNode.attribute("width").as_int();
			int height = objectNode.attribute("height").as_int();
			std::string idHiddenItemString = "";
			EntityID activationObjectID = ID_ENTITY_NULL;
			std::string objectId = "";
			std::string enemyName = "";
			float startViewPortX = 0;
			float endViewPortX = 0;
			float startViewPortY = 0;
			EntityID sceneID = ID_ENTITY_NULL;

			std::string cellId = "";
			int stairHeight = 0;
			int nx = 0;
			int ny = 0;
			int maxPosition = 0;

			auto properties = objectNode.child("properties");

			for (auto propertyNode : properties)
			{
				std::string nameProperty = propertyNode.attribute("name").as_string();
				if (nameProperty.compare("Hidden Item ID") == 0)
				{
					idHiddenItemString = propertyNode.attribute("value").as_string();
				}
				else if (nameProperty.compare("Activation Object ID") == 0)
				{
					activationObjectID = Utils::getInstance()->getStringToEntityID()[propertyNode.attribute("value").as_string()];
				}
				else if (nameProperty.compare("Object ID") == 0)
				{
					objectId = propertyNode.attribute("value").as_string();
				}
				else if (nameProperty.compare("MaxPosition") == 0)
				{
					maxPosition = propertyNode.attribute("value").as_int();
				}
				else if (nameProperty.compare("Enemy Name") == 0)
				{
					enemyName = propertyNode.attribute("value").as_string();
				}
				else if (nameProperty.compare("Stair Height") == 0)
				{
					stairHeight = propertyNode.attribute("value").as_int();
				}
				else if (nameProperty.compare("nx") == 0)
				{
					nx = propertyNode.attribute("value").as_int();
				}
				else if (nameProperty.compare("ny") == 0)
				{
					ny = propertyNode.attribute("value").as_int();
				}
				else if (nameProperty.compare("StartViewportX") == 0)
				{
					startViewPortX = propertyNode.attribute("value").as_float();
				}
				else if (nameProperty.compare("EndViewportX") == 0)
				{
					endViewPortX = propertyNode.attribute("value").as_float();
				}
				else if (nameProperty.compare("StartViewportY") == 0)
				{
					startViewPortX = propertyNode.attribute("value").as_float();
				}
				else if (nameProperty.compare("SceneID") == 0)
				{
					sceneID = Utils::getInstance()->getStringToEntityID()[propertyNode.attribute("value").as_string()];
				}
				else if (nameProperty.compare("Cell ID") == 0)
				{
					cellId = propertyNode.attribute("value").as_string();
				}
			}
			GameObject *objectInit = nullptr;
			int  idObject = Utils::getInstance()->getStringToEntityID()[objectId];
			if (!idObject)
			{
				DebugOut(L"[ERROR] Read object from map failed\n", objectId);
				return;
			}
			AnimationSets * animation_sets = AnimationSets::GetInstance();
			LPANIMATION_SET ani_set = animation_sets->Get(idObject);

			switch (idObject)
			{
			case ID_ENTITY_SIMON:
				player = Simon::getInstance();
				Simon::getInstance()->SetPosition(D3DXVECTOR2(x, y - EXTRA_HEIGHT_SCREEN));
				player = (Simon*)player;
				player->setHeight(height);
				player->setWidth(width);
				player->SetAnimationSet(ani_set);
				break;
			case ID_ENTITY_FLOOR:
				objectInit = new Floor(D3DXVECTOR2(x, y), height, width);
				objectInit->setName(name);
				break;
			case ID_ENTITY_DOOR:
				objectInit = new Door(D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_BRICK:
				objectInit = new CBrick(name, D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_BURNBARREL:
				objectInit = new BurnBarrel(D3DXVECTOR2(x, y), height, width);
				objectInit->setIdHiddenItem(idHiddenItemString);
				break;
			case ID_ENTITY_VAMPIRE_BAT:
				objectInit = new VampireBat(D3DXVECTOR2(x, y), height, width);
				objectInit->setName(name);
				break;
			case ID_ENTITY_WALL:
				objectInit = new Wall(D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_ENTRANCE:
				objectInit = new Entrance(D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_PORTAL:
				objectInit = new Portal(D3DXVECTOR2(x, y), sceneID, height, width);
				break;
			case ID_ENTITY_PORTAL_POS_MAP:
				objectInit = new PortalPosMap(D3DXVECTOR2(x, y),height, width, startViewPortX, endViewPortX, startViewPortY);
				break;
			case ID_ENTITY_CANDLE:
				objectInit = new Candle(D3DXVECTOR2(x, y), height, width);
				objectInit->setIdHiddenItem(idHiddenItemString);
				break;
			case ID_ENTITY_SPAWN_ENEMY:
				objectInit = new SpawnEnemy(D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_FISH_MAN:
				objectInit = new FishMan(D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_DARK_BAT:
				objectInit = new DarkBat(D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_CASTLEVANIA_WALL:
				castleWall = new CastleWall(D3DXVECTOR2(x, y), height, width);
				castleWall->setHeight(height);
				castleWall->setWidth(width);
				break;
			case ID_ENTITY_STAIR:
				objectInit = new ObjectStair(D3DXVECTOR2(x, y), width,
					height, nx, ny, stairHeight);
				objectInit->setMainId(id);
				objectInit->setCellId(cellId);
				break;
			case ID_ENTITY_PANTHER:
				objectInit = new Panther(D3DXVECTOR2(x, y), nx, height, width);
				break;
			case ID_ENTITY_ACTIVATEBOX:
				objectInit = new ActivationBox(D3DXVECTOR2(x, y), activationObjectID, height, width);
				objectInit->setName(name);
				break;
			case ID_ENTITY_CROWN:
				objectInit = new Crown(D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_SPEAR_KNIGHT:
				objectInit = new SpearKnight(D3DXVECTOR2(x, y), maxPosition, height, width);
				break;
			case ID_ENTITY_MOVING_BRICK:
				objectInit = new MovingBrick(D3DXVECTOR2(x, y), maxPosition, height, width);
				break;
			case ID_ENTITY_GHOST:
				objectInit = new Ghost(D3DXVECTOR2(x, y), height, width);
				break;
			case ID_ENTITY_FLEAMEN:
				objectInit = new Fleamen(D3DXVECTOR2(x, y), height, width);
				objectInit->setName(name);
				break;
			}

			if (ani_set != nullptr && objectInit)
			{
				objectInit->SetAnimationSet(ani_set);
			}

			if (objectInit && idObject != ID_ENTITY_SIMON)
			{
				objects.push_back(objectInit);
			}
		}
	}
}
