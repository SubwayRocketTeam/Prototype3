#pragma once
#include "Character.h"

#define SCARF 30
#define SCARF_DELAY 2
#define SCARF_LEN 4

class Player : public Character
{
public:
	CREATE_FUNC(Player);
	Player();
	virtual ~Player(){}
	virtual bool init();

	virtual void update(float dt) override;

	virtual void Attack() override;
	virtual void SpecialAttack() override;

private:
	void updateScarf(float dt);

private:
	struct ScarfNode
	{
		cocos2d::Vec2 point;
		cocos2d::Vec2 velocity[SCARF_DELAY];
		cocos2d::Vec2 tail;
	};

	ScarfNode scarfNode[SCARF];

	cocos2d::Vec2 scarfStartDirection;

	cocos2d::DrawNode* scarf;

	int attackState;

};