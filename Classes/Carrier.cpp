#include "Carrier.h"

USING_NS_CC;

Carrier::Carrier(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, Vec2 scale) :
	pos(pos), sprite(sprite), Scale(scale)
{
	int x = -13;
	if (sprite->getRotation() == 180) {
		x = -x;
	}
	MoveRange = MaxMoveRange = 3;
	AttackRange = 5;
	Health = 24;
	Damage = 5;
	sprite->setPosition(Vec2(pos.x * scale.x - scale.x / 2, pos.y * scale.y - scale.y / 2 + x));
}

int Carrier::GetMoveRange() {
	return this->MoveRange;
}

int Carrier::GetAttackDamage() {
	music::PlaneAttack();
	MoveRange = -1;
	return this->Damage;
}

int Carrier::GetAttackRange() {
	return this->AttackRange;
}

Vec2 Carrier::GetPos() {
	return this->pos;
}

Sprite* Carrier::GetSprite() {
	return this->sprite;
}

void Carrier::SetPos(Vec2 pos) {
	int distance = abs(this->pos.x - pos.x) + abs(this->pos.y - pos.y);
	if (distance <= this->MoveRange) {
		MoveRange -= distance;
	}
	else {
		return;
	}
	int x = -10;
	if (sprite->getRotation() == 180) {
		x = -x;
	}
	auto move = MoveTo::create(distance / 2, Vec2(pos.x * Scale.x - Scale.x / 2, pos.y * Scale.y - Scale.y / 2 + x));
	this->sprite->runAction(move);
	this->pos = pos;
	music::Move(distance);
}

void Carrier::ChengeHealth(int damage) {
	Health -= damage;
	if (Health <= 0) {
		auto action = CallFuncN::create(CC_CALLBACK_1(Carrier::Remove, this, false));
		if (sprite->getParent() != nullptr)
			sprite->runAction(action);
	}
}

void Carrier::Refreash() {
	this->MoveRange = this->MaxMoveRange;
}

int Carrier::GetHealth() {
	return Health;
}

void Carrier::Remove(Node* sender, bool cleanup) {
	sender->removeFromParentAndCleanup(cleanup);
}

bool Carrier::Check(std::vector<cocos2d::Vec2> Posses) {
	for (int i = 0; i < Posses.size(); i++) {
		if (Posses[i].x == pos.x && Posses[i].y == pos.y) {
			return true;
		}
		else if (Posses[i].x == pos.x - 1 && Posses[i].y == pos.y) {
			return true;
		}
		else if (Posses[i].x == pos.x + 1 && Posses[i].y == pos.y) {
			return true;
		}
	}
	return false;
}
std::vector<cocos2d::Vec2> Carrier::GetPosses(cocos2d::Vec2* poss) {
	if (poss != nullptr) {
		return std::vector<cocos2d::Vec2>{Vec2(poss->x + 1, poss->y), * poss, Vec2(poss->x - 1, poss->y)};
	}
	return std::vector<cocos2d::Vec2>{Vec2(pos.x + 1, pos.y), pos, Vec2(pos.x - 1, pos.y)};
}