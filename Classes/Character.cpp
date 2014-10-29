#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

Character::Character()
	:hp(1), mp(0), radius(5)
	, controlBlocked(false), haveToDelete(false)
	, controlBlockingTime(0)
	// , head(nullptr), sholder(nullptr), arm(nullptr), hand(nullptr), leg(nullptr), foot(nullptr)
{
	ZeroMemory(body, sizeof(body));
}

bool Character::init(const std::string& imageName)
{
	if (!Node::init()) return false;
	
	/*
	head = Sprite::create(imageName + "_1.png");
	sholder = Sprite::create(imageName + "_2.png");
	arm = Sprite::create(imageName + "_3.png");
	hand = Sprite::create(imageName + "_4.png");
	leg = Sprite::create(imageName + "_5.png");
	foot = Sprite::create(imageName + "_6.png");
	
	addChild(head, 6, "head");
	addChild(sholder, 5, "sholder");
	addChild(arm, 4, "arm");
	addChild(hand, 3, "hand");
	addChild(leg, 2, "leg");
	addChild(foot, 1, "foot");
	*/

	for (int i = 0; i < BODY_PART; ++i)
	{
		body[i] = Sprite::create(imageName + '_' + (char)('1' + i) + ".png");
//		body[i]->setGlobalZOrder(6 - i);
		addChild(body[i], -i);

	}
	scheduleUpdate();

	return true;
}

void Character::update(float dt)
{
	static float ratio = 0.03f;
	// static float speed = 10;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 CharacterPos = getPosition();
	Vec2 characterScreenPos = getParent()->convertToWorldSpace(CharacterPos);

	Vec2 deltaFromCenter = characterScreenPos - (origin + visibleSize / 2);

	/*
	head->setPosition(deltaFromCenter * ratio * 5);
	sholder->setPosition(deltaFromCenter * ratio * 4);
	arm->setPosition(deltaFromCenter * ratio * 3);
	hand->setPosition(deltaFromCenter * ratio * 2);
	leg->setPosition(deltaFromCenter * ratio * 1);
	*/

	for (int i = 0; i < BODY_PART; ++i)
		body[i]->setPosition(deltaFromCenter * ratio * (5-i));

	if (controlBlocked = controlBlockingTime > 0)
		controlBlockingTime -= dt;

	if (attackDelay > 0)
		attackDelay -= dt;

	if (!controlBlocked)
	{
		// Moving
		if (moveDirection.getLengthSq() > 0)
		{
			setPosition(CharacterPos + moveDirection.getNormalized() * attribute.moveSpeed);
		}

		// Rotation
		setRotation(getLookingAngle());
	}

}


void Character::Damage(int damage)
{
	hp -= MAX(0, damage - attribute.defence);
	setColor(Color3B(255, 0, 0));
	runAction(TintTo::create(0.5f, 255, 255, 255));
	setBlokingTime(0.25f);
	setPosition(getPosition() + lookingDirection * 5);
}


float Character::getRotation() const
{
	return getLookingAngle();
}

const Color3B& Character::getColor() const
{
	return body[0]->getColor();
}


void Character::setRotation(float rotation)
{
	// auto vec = getChildren();
	for (auto node : body)
	{
		node->setRotation(rotation);
	}
}

void Character::setColor(const cocos2d::Color3B& color)
{
	for (int i = 0; i < BODY_PART; ++i)
		body[i]->setColor(color);
}


Vec2 Character::getHeadPos() const
{
	return body[0]->getPosition();
}


const Vec2& Character::getMoveDirection() const { return moveDirection; }
const Vec2& Character::getLookingDirection() const { return lookingDirection; }
float Character::getLookingAngle() const { return -lookingDirection.getAngle() * 180 / std::_Pi - 90; }
float Character::getRadius() const { return radius; }
bool Character::isAttackable() const { return attackDelay <= 0; }

void Character::setMoveDirection(const Vec2& direction) { moveDirection = direction; }
void Character::setLookingDirection(const Vec2& direction) { lookingDirection = direction.getNormalized(); }
void Character::setBlokingTime(const float time) { controlBlockingTime = time; }
void Character::setAttackDelay(const float time) { attackDelay = time; }

void Character::deleteThis() { haveToDelete = true; }
bool Character::isHaveToDelete() const { return haveToDelete; }