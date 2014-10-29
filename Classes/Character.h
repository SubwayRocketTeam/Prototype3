#pragma once

#include "cocos2d.h"
#include "Attributes.h"

#define BODY_PART 6

class Character : public cocos2d::Node
{
public:
	CREATE_FUNC(Character);
	Character();
	virtual ~Character(){}
	virtual bool init(const std::string& imageName = std::string("character1"));

	virtual void update(float dt);

	virtual void Attack(){};
	virtual void SpecialAttack(){};
	virtual void Damage(int damage);


	virtual float getRotation() const override;
	virtual const cocos2d::Color3B& getColor() const override;
	virtual void setRotation(float rotation) override;
	virtual void setColor(const cocos2d::Color3B& color) override;


	const cocos2d::Vec2& getMoveDirection() const;
	const cocos2d::Vec2& getLookingDirection() const;
	float getRadius() const;

	bool isAttackable() const;

	// Degree
	float getLookingAngle() const;

	void setMoveDirection(const cocos2d::Vec2& direction);
	void setLookingDirection(const cocos2d::Vec2& direction);
	void setBlokingTime(const float time);
	void setAttackDelay(const float time);

	void deleteThis();
	bool isHaveToDelete() const;

protected:
	cocos2d::Vec2 getHeadPos() const;

private:
	cocos2d::Sprite* body[BODY_PART];
	/*
	cocos2d::Sprite* head;
	cocos2d::Sprite* sholder;
	cocos2d::Sprite* arm;
	cocos2d::Sprite* hand;
	cocos2d::Sprite* leg;
	cocos2d::Sprite* foot;
	*/

	bool controlBlocked;
	float controlBlockingTime;
	float attackDelay;

	bool haveToDelete;

protected:
	int hp;
	int mp;

	Attributes attribute;

	float radius;

	cocos2d::Vec2 moveDirection;
	cocos2d::Vec2 lookingDirection;
};