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
	// ��ä���� ���� radian
	// direction�� �߽����� angle��ŭ ��������.
	// ��, direction �������� angle/2, ���������� angle/2
	// ������ ���̱� ���� �̹� ������ ���� angle�� �����Ѵ�.
	float halfAngle;

};