#pragma once

#include "AttackData.h"

class AttackData_Pan : public AttackData
{
public:
	// Pan
	static AttackData_Pan* create(const cocos2d::Vec2& base, const cocos2d::Vec2& direction, const float angle);
	// Circle
	static AttackData_Pan* create(const cocos2d::Vec2& base, float radius);

	// Pan
	bool init(const cocos2d::Vec2& base, const cocos2d::Vec2& direction, const float angle);
	// Circle
	bool init(const cocos2d::Vec2& base, float radius);

	AttackData_Pan();
	virtual ~AttackData_Pan(){}

	virtual bool checkCircleCollision(const cocos2d::Vec2& pos, const float radius) const override;

protected:
	// 부채꼴의 각도 radian
	// direction을 중심으로 angle만큼 펼쳐진다.
	// 즉, direction 왼쪽으로 angle/2, 오른쪽으로 angle/2
	// 연산을 줄이기 위해 이미 반으로 나눈 angle을 저장한다.
	float halfAngle;

};