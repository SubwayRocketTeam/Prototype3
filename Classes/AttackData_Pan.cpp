#include "AttackData_Pan.h"

USING_NS_CC;

AttackData_Pan::AttackData_Pan()
:AttackData(AttackType::PAN), halfAngle(0)
{
}

AttackData_Pan* AttackData_Pan::create(const Vec2& base, const Vec2& direction, const float angle)
{
	AttackData_Pan* o = new(std::nothrow) AttackData_Pan();
	if (o && o->init(base, direction, angle))
	{
		o->autorelease();
		return o;
	}
	delete o;
	return nullptr;
}

AttackData_Pan* AttackData_Pan::create(const Vec2& base, float radius)
{
	AttackData_Pan* o = new(std::nothrow) AttackData_Pan();
	if (o && o->init(base, radius))
	{
		o->autorelease();
		return o;
	}
	delete o;
	return nullptr;
}


bool AttackData_Pan::init(const Vec2& base, const Vec2& direction, const float angle)
{
	this->base = base;
	this->direction = direction;
	this->halfAngle = angle / 2;
	return true;
}

bool AttackData_Pan::init(const Vec2& base, float radius)
{
	this->base = base;
	this->direction = Vec2(radius, 0);
	this->halfAngle = std::_Pi;
	return true;
}


bool AttackData_Pan::checkCircleCollision(const Vec2& pos, const float radius) const
{
	float total_radius = direction.length() + radius;
	float distance = (pos - base).length();

	if (distance > total_radius) return false;

	float deltaAngle = std::acos(base.dot(pos));

	if (deltaAngle > halfAngle) return false;

	return true;
}
