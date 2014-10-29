#include "Player.h"
#include "GameScene.h"
#include "AttackData_Pan.h"

USING_NS_CC;

Player::Player()
:attackState(0)
{
}

bool Player::init()
{
	if (!Character::init()) return false;

	scarf = DrawNode::create();
	addChild(scarf, 5);

	for (int i = 0; i < SCARF; ++i)
	{
		scarfNode[i].point = Vec2(i*SCARF_LEN, 0);
//		scarfNode[i].velocity[i] = Vec2(0, 0);
		scarfNode[i].tail = Vec2(1, 0);
	}
	scarfStartDirection = Vec2(1, 0);

	return true;
}

void Player::update(float dt)
{
	Character::update(dt);
	updateScarf(dt);
	scarf->clear();
	Vec2 pos = getPosition() - getHeadPos() - getHeadPos().getNormalized()*20;
	for (int i = 0; i < SCARF - 1; i++)
		scarf->drawSegment(scarfNode[i].point - pos, scarfNode[i + 1].point - pos, 5 + i / 10, Color4F(1.f, 0, 0, 1.f));

}

void Player::updateScarf(float dt)
{
	static float t = 0;
	t += dt*8;

	Vec2 pos = getPosition();
	scarfStartDirection = -getLookingDirection();
	scarfStartDirection.rotate(Vec2::ZERO, std::sin(t)*0.25);

	for (int i = SCARF - 1; i > 0; --i)
	{
		scarfNode[i].point += scarfNode[i].velocity[SCARF_DELAY - 1];
		scarfNode[i].point += (scarfNode[i - 1].tail - scarfNode[i].tail) * (SCARF_LEN * i);

		for (int j = SCARF_DELAY - 1; j > 0; --j)
		{
			scarfNode[i].velocity[j] = scarfNode[i].velocity[j - 1];
		}

		scarfNode[i].velocity[0] = scarfNode[i - 1].velocity[SCARF_DELAY - 1];
		scarfNode[i].tail = scarfNode[i - 1].tail;
	}

	for (int j = SCARF_DELAY - 1; j > 0; --j)
	{
		scarfNode[0].velocity[j] = scarfNode[0].velocity[j - 1];
	}

	scarfNode[0].velocity[0] = pos - scarfNode[0].point;
	scarfNode[0].tail += (scarfStartDirection - scarfNode[0].tail)*0.25;
	scarfNode[0].point = pos;

}


void Player::Attack()
{
	Sprite* effect;
	switch (attackState)
	{
	case 0:
		effect = Sprite::create("attack1.png");
		break;
	case 1:
		effect = Sprite::create("attack2.png");
		break;
	default:
		effect = Sprite::create("attack1.png");
		break;
	}
	effect->setPosition(getPosition());
	effect->setRotation(getLookingAngle());
	effect->runAction(
			Sequence::create(
				FadeOut::create(0.5f),
				CallFunc::create(CC_CALLBACK_0(Node::removeFromParentAndCleanup, effect, true)),
				NULL
			)
		);
	getParent()->addChild(effect);
	attackState = (attackState + 1) % 2;

	GameScene* scene = (GameScene*)Director::getInstance()->getRunningScene()->getChildByName("scene");
	scene->attackEnemies(AttackData_Pan::create(getPosition(), lookingDirection * 200, 120 * std::_Pi / 180));
}

void Player::SpecialAttack()
{
	Sprite* effect = Sprite::create("attack3.png");
	effect->setPosition(getPosition());
	effect->setRotation(getLookingAngle());
	effect->runAction(
			Sequence::create(
				DelayTime::create(0.25f),
				FadeOut::create(0.5f),
				CallFunc::create(CC_CALLBACK_0(Node::removeFromParentAndCleanup, effect, true)),
				NULL
			)
		);
	runAction(
		Sequence::create(
			EaseOut::create(RotateBy::create(0.4f, 360), 2),
			RotateTo::create(0.1f, getLookingAngle()),
			NULL
		));
	setBlokingTime(0.5f);
	getParent()->addChild(effect);
}