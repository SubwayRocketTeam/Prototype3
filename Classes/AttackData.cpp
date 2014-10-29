#include "AttackData.h"

USING_NS_CC;

AttackData::AttackData(const AttackType type)
: type(type)
{
}

AttackType AttackData::getType() const { return type; }
const Vec2& AttackData::getBase() const { return base; }
const Vec2& AttackData::getDirection() const { return direction; }
