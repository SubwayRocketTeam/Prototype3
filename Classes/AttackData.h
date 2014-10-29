#pragma once

#include "cocos2d.h"

enum class AttackType
{
	NONE,
	PAN,
	LINE,
};

class AttackData : public cocos2d::Ref
{
public:
	AttackData(const AttackType type = AttackType::NONE);
	virtual ~AttackData(){}

	virtual bool checkCircleCollision(const cocos2d::Vec2& pos, const float radius) const = 0;

	AttackType getType() const;
	const cocos2d::Vec2& getBase() const;
	const cocos2d::Vec2& getDirection() const;

protected:
	// 공격 타입
	AttackType type;

protected:
	// 공격이 시작되는 위치
	cocos2d::Vec2 base;

	// 공격의 방향과 크기
	cocos2d::Vec2 direction;

};