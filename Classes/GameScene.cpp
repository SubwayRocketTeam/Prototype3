#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "AttackData.h"
#include "Random.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->setName("scene");

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool GameScene::init()
{
	if (!Layer::init()) return false;

	auto mouseListener = EventListenerMouse::create();
	auto keyboardListener = EventListenerKeyboard::create();

	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);

	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyDown, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyUp, this);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 게임 레이어와 UI 레이어
	gameLayer = Layer::create();
	uiLayer = Layer::create();

	uiLayer->setAnchorPoint(Vec2::ZERO);

	gameLayer->setPosition(origin + visibleSize / 2);

	addChild(gameLayer);
	addChild(uiLayer);

	// 디버그용
	debugLabel = LabelTTF::create("", "Arial", 22, Size(800, 600), TextHAlignment::LEFT);
	debugLabel->setAnchorPoint(Vec2::ZERO);
	addChild(debugLabel, 100);

	initGame();

	scheduleUpdate();

	// spawnEnemy();

	return true;
}

void GameScene::initGame()
{
	gameLayer->addChild(Sprite::create("floor.png"), -100);

	player = Player::create();
	gameLayer->addChild(player);

}


void GameScene::spawnEnemy(int enemyNum)
{
	static float width = 1600;
	static float height = 1200;

	if (enemyNum <= 0) return;

	while (enemyNum --> 0)
	{
		Enemy* enemy = Enemy::create();
		enemy->setPosition((Random::rand.NextDouble() - 0.5) * width, (Random::rand.NextDouble() - 0.5) * height);
		gameLayer->addChild(enemy);
		enemies.push_back(enemy);
	}

}




void GameScene::update(float dt)
{
	static float width = 1600;
	static float height = 1200;

	/*
	char buf[128] = {0};
	Vec2 charpos = player->getLookingDirection();
	sprintf(buf, "%.2f %.2f",
	charpos.x, charpos.y
	);
	debugLabel->setString(buf);
	*/

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size halfSize = visibleSize / 2;
	Vec2 playerPos = player->getPosition();
	Vec2 playerScreenPos = gameLayer->convertToWorldSpace(playerPos);

	// Camera
	Vec2 center = playerPos + (lastMousePos - halfSize) / 2;

	center.x = MIN(width - halfSize.width, MAX(halfSize.width, center.x + width / 2)) - width / 2;
	center.y = MIN(height - halfSize.height, MAX(halfSize.height, center.y + height / 2)) - height / 2;

	gameLayer->setPosition((Vec2)halfSize - center);

	// Chracter looking direction
	player->setLookingDirection(lastMousePos - playerScreenPos);

	// Update enemy list
	int deletedEnemyNum = 0;

	for (Enemy* enemy : enemies)
	{
		if (enemy->isHaveToDelete())
		{
			gameLayer->removeChild(enemy, true);
			++deletedEnemyNum;
		}
	}

	enemies.erase(
		std::remove_if(
			enemies.begin(),
			enemies.end(),
			[](const Character* c){ return c->isHaveToDelete(); }
		), enemies.end());

	spawnEnemy(deletedEnemyNum*2);
}


void GameScene::attackEnemies(const AttackData* const attackData)
{
	for (Enemy* enemy : enemies)
	{
		if (attackData->checkCircleCollision(enemy->getPosition(), enemy->getRadius()))
		{
			enemy->Damage(1);
		}
	}
}

void GameScene::attackPlayer(const AttackData* const attackData)
{
	if (attackData->checkCircleCollision(player->getPosition(), player->getRadius()))
	{
		player->Damage(1);
	}
}


void GameScene::onKeyDown(EventKeyboard::KeyCode keycode, Event* event)
{
	Vec2 moveDirection = player->getMoveDirection();
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		moveDirection += Vec2::UNIT_Y;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		moveDirection -= Vec2::UNIT_X;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		moveDirection -= Vec2::UNIT_Y;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		moveDirection += Vec2::UNIT_X;
		break;
	}
	player->setMoveDirection(moveDirection);
}

void GameScene::onKeyUp(EventKeyboard::KeyCode keycode, Event* event)
{
	Vec2 moveDirection = player->getMoveDirection();
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		moveDirection -= Vec2::UNIT_Y;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		moveDirection += Vec2::UNIT_X;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		moveDirection += Vec2::UNIT_Y;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		moveDirection -= Vec2::UNIT_X;
		break;
	}
	player->setMoveDirection(moveDirection);
}


void GameScene::onMouseDown(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	switch (e->getMouseButton())
	{
		case MOUSE_BUTTON_LEFT:
			player->Attack();
			break;
		case MOUSE_BUTTON_RIGHT:
			player->SpecialAttack();
			break;
		default:
			break;
	}
}


void GameScene::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	lastMousePos = e->getLocationInView();
}


Player* GameScene::getPlayer() { return player; }
