#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
	CREATE_FUNC(Enemy);
	virtual ~Enemy(){};
	virtual bool init();

	virtual void update(float dt) override;

	virtual void Attack() override;
	virtual void SpecialAttack() override;

private:
};