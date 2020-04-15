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
#include "GameObjects/Entrance.h"
#include "WallEntrance.h"
#include "WallChangingMap.h"
#include "Candle.h"
#include "SpawnEnemy.h"
#include "FishMan.h"
#include "DarkBat.h"
#include "CastleWall.h"
#include "Panther.h"
#include "ObjectGridCreation.h"


PlayScene::PlayScene(EntityID id, std::string filePath):Scene(id, filePath)
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	menuPoint = new MenuPoint();
	viewport = Direct3DManager::getInstance()->getViewport();
}

void PlayScene::Load()
{
	ReadFile_FONTS(L"Resources\\Fonts\\prstart.ttf");

	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	pugi::xml_document docMap;

	if (!docMap.load_file(sceneFilePath.c_str()))
	{
		DebugOut(L"[ERROR] Read Screne file failed\n", sceneFilePath);
		return;
	}

	std::string pathObject = docMap.child("map").child("properties").child("property").attribute("value").as_string();

	pugi::xml_document docObject;

	if (!docObject.load_file(pathObject.c_str()))
	{
		DebugOut(L"[ERROR] Read Objects file failed\n", pathObject);
		return;
	}
	
	for (auto object: docObject.child("objectList"))
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
	
	menuPoint->update();

	tiled_map->Update(dt);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);
		if (objects[i]->GetState() == objects[i]->STATE_DETROY)
		{
			objects.erase(objects.begin() + i);
		}
	}

	Simon::getInstance()->Update(dt, &objects);

	UpdateViewport(dt);
}

void PlayScene::Render(Viewport* viewport)
{
	menuPoint->Draw(font);

	tiled_map->draw(viewport);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		if (objects[i]->getID() != ID_ENTITY_CASTLEVANIA_WALL)
		{
			objects[i]->Render(viewport);
		}
	}
	Simon::getInstance()->Render(viewport);
	for (int i = 0; i < (int)objects.size(); i++)
	{
		if (objects[i]->getID() == ID_ENTITY_CASTLEVANIA_WALL)
		{
			objects[i]->Render(viewport);
		}
	}
}

void PlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void PlayScene::UpdateViewport(DWORD dt)
{
	if (viewport->getState() == viewport->STATE_ACTION)
	{
		D3DXVECTOR2 pos_Simon = Simon::getInstance()->getPosition();
		int widthframeSimon = Simon::getInstance()->getWidth();
		D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};
		newPosViewport.x = Simon::getInstance()->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
		newPosViewport.x = min(tiled_map->getWidthWorld() - viewport->getWidth(), newPosViewport.x);
		newPosViewport.y = min(tiled_map->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
		newPosViewport.x = max(0, newPosViewport.x);
		newPosViewport.y = max(0, newPosViewport.y);
		viewport->setX(float(newPosViewport.x));
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
	CastleWall* castleWall = nullptr;

	for (auto objectGroupNode : node.children("objectgroup"))
	{
		for (auto objectNode : objectGroupNode.children("object"))
		{
			ObjectInfo* objectInfo = new ObjectInfo();
			
			objectInfo->set_id(objectNode.attribute("id").as_int());
			objectInfo->set_ObjectType(objectGroupNode.attribute("name").as_string());
			objectInfo->set_name(objectNode.attribute("name").as_string());

			float x = objectNode.attribute("x").as_float();
			float y = objectNode.attribute("y").as_float() + EXTRA_HEIGHT_SCREEN;
			objectInfo->set_position(D3DXVECTOR2(x, y));

			int width = objectNode.attribute("width").as_int();
			int height = objectNode.attribute("height").as_int();
			objectInfo->set_width(width);
			objectInfo->set_height(height);

			auto properties = objectNode.child("properties");
			for (auto propertyNode : properties)
			{
				std::string nameProperty = propertyNode.attribute("name").as_string();
				if (nameProperty.compare("Hidden Item ID") == 0)
				{
					objectInfo->set_idHiddenItem(propertyNode.attribute("value").as_string());
				}
				else if (nameProperty.compare("Object ID") == 0)
				{
					objectInfo->set_ObjectId(propertyNode.attribute("value").as_string());
				}
				else if (nameProperty.compare("Enemy Name") == 0)
				{
					objectInfo->set_name(propertyNode.attribute("value").as_string());
				}
				else if (nameProperty.compare("Stair Height") == 0)
				{
					objectInfo->set_height(propertyNode.attribute("value").as_int());
				}
				else if (nameProperty.compare("nx") == 0)
				{
					objectInfo->set_nx(propertyNode.attribute("value").as_int());
				}
				else if (nameProperty.compare("ny") == 0)
				{
					objectInfo->set_ny(propertyNode.attribute("value").as_int());
				}
				else if (nameProperty.compare("StartViewport") == 0)
				{
					objectInfo->set_startViewPort(propertyNode.attribute("value").as_float());
				}
				else if (nameProperty.compare("EndViewport") == 0)
				{
					objectInfo->set_endViewPort(propertyNode.attribute("value").as_float());
				}
				else if (nameProperty.compare("Cell ID") == 0)
				{
					objectInfo->set_cellId(propertyNode.attribute("value").as_string());
				}
			}
			GameObject *objectInit = nullptr;
			int idObject = Utils::getInstance()->getStringToEntityID()[objectInfo->get_ObjectId()];

			switch (idObject)
			{
			case ID_ENTITY_SIMON:
				objectInit = Simon::getInstance();
				player = (Simon*)objectInit;
				break;
			case ID_ENTITY_FLOOR:
				objectInit = new Floor();
				break;
			case ID_ENTITY_DOOR:
				objectInit = new Door(objectInfo->get_postition());
				break;
			case ID_ENTITY_BRICK:
				objectInit = new CBrick(objectInfo->get_name());
				break;
			case ID_ENTITY_BURNBARREL:
				objectInit = new BurnBarrel();
				break;
			case ID_ENTITY_VAMPIRE_BAT:
				objectInit = new VampireBat();
				break;
			case ID_ENTITY_ENTRANCE:
				objectInit = new Entrance();
				break;
			case ID_ENTITY_WALL_ENTRANCE:
				objectInit = new WallEntrance();
				break;
			case ID_ENTITY_WALL_CHANGINGMAP:
				objectInit = new WallChangingMap();
				break;
			case ID_ENTITY_CANDLE:
				objectInit = new Candle();
				break;
			case ID_ENTITY_SPAWN_ENEMY:
				objectInit = new SpawnEnemy();
				break;
			case ID_ENTITY_FISH_MAN:
				objectInit = new FishMan(objectInfo->get_postition());
				break;
			case ID_ENTITY_DARK_BAT:
				objectInit = new DarkBat(objectInfo->get_postition());
				break;
			case ID_ENTITY_CASTLEVANIA_WALL:
				objectInit = new CastleWall();
				break;
			case ID_ENTITY_STAIR:
				objectInit = new ObjectStair(objectInfo->get_postition(), D3DXVECTOR4(objectInfo->get_width(),
					objectInfo->get_height(), objectInfo->get_nx(), objectInfo->get_ny()), objectInfo->get_stairHeight());
				objectInit->setMainId(objectInfo->get_id());
				objectInit->setCellId(objectInfo->getCellId());
				break;
			case ID_ENTITY_PANTHER:
				objectInit = new Panther(objectInfo->get_postition(), objectInfo->get_nx());
				break;
			}
			if (objectInit)
			{
				AnimationSets * animation_sets = AnimationSets::GetInstance();
				LPANIMATION_SET ani_set = animation_sets->Get(idObject);

				if (ani_set !=nullptr)
				{
					objectInit->SetAnimationSet(ani_set);
				}

				if (idObject != ID_ENTITY_STAIR)
				{
					objectInit->setMainId(objectInfo->get_id());
					objectInit->setCellId(objectInfo->getCellId());
					objectInit->setName(objectInfo->get_name());
					objectInit->SetPosition(objectInfo->get_postition());
					objectInit->setHeight(objectInfo->get_height());
					objectInit->setWidth(objectInfo->get_width());
					objectInit->setIdHiddenItem(objectInfo->get_idHiddenItem());
					objectInit->setEnemyName(objectInfo->get_enemyName());
					objectInit->setStartViewPort(objectInfo->get_StartViewPort());
				}
				if (idObject!=ID_ENTITY_SIMON)
				{
					objects.push_back(objectInit);
				}
			}
		}
	}
}
