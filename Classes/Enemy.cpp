#include "Enemy.h"
#include "Player.h"
#include "GameScene.h"
#include "AttackData_Pan.h"

USING_NS_CC;

bool Enemy::init()
{
	if (!Character::init()) return false;
	hp = 4;
	attribute.maxHp = 4;
	attribute.moveSpeed = 4;
	attribute.attackDelay = 1.f;
	return true;
}

void Enemy::update(float dt)
{
	Character::update(dt);

	// Follow Player
	GameScene* scene = (GameScene*)Director::getInstance()->getRunningScene()->getChildByName("scene");
	Player* player = scene->getPlayer();
	moveDirection = player->getPosition() - getPosition();
	lookingDirection = moveDirection.getNormalized();

	// Attack Player
	if (isAttackable())
		Attack();

	// delete if hp is under 0
	if (hp <= 0)
		deleteThis();

}

void Enemy::Attack()
{
	Sprite* effect = Sprite::create("attack1.png");
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
	setAttackDelay(attribute.attackDelay);

	GameScene* scene = (GameScene*)Director::getInstance()->getRunningScene()->getChildByName("scene");
	scene->attackPlayer(AttackData_Pan::create(getPosition(), lookingDirection * 100, 120 * std::_Pi / 180));
}

void Enemy::SpecialAttack()
{

}
