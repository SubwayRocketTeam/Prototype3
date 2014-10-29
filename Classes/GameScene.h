#pragma once

#include "cocos2d.h"

// class Character;
class Player;
class Enemy;
class AttackData;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void update(float dt);
	
	CREATE_FUNC(GameScene);

	void attackEnemies(const AttackData* const attackData);
	void attackPlayer(const AttackData* const attackData);

	Player* getPlayer();

private:
	void initGame();

	void spawnEnemy(int enemyNum = 1);

	void onKeyDown(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyUp(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	void onMouseDown(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);

private:
	cocos2d::Layer* gameLayer;
	cocos2d::Layer* uiLayer;

	Player* player;
	std::vector<Enemy*> enemies;

	cocos2d::Vec2 lastMousePos;

	cocos2d::LabelTTF* debugLabel;

};

