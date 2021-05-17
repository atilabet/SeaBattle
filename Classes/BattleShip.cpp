#include "BattleShip.h"

USING_NS_CC;

BattleShip::BattleShip(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, Vec2 scale) :
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

int BattleShip::GetMoveRange() {
	return this->MoveRange;
}

int BattleShip::GetAttackDamage() {
	music::Shoot();
	MoveRange = -1;
	return this->Damage;
}

int BattleShip::GetAttackRange() {
	return this->AttackRange;
}

Vec2 BattleShip::GetPos() {
	return this->pos;
}

Sprite* BattleShip::GetSprite() {
	return this->sprite;
}

void BattleShip::SetPos(Vec2 pos) {
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

void BattleShip::ChengeHealth(int damage) {
	Health -= damage;
	if (Health <= 0) {
		auto action = CallFuncN::create(CC_CALLBACK_1(BattleShip::Remove, this, false));
		if (sprite->getParent() != nullptr)
			sprite->runAction(action);
	}
}

void BattleShip::Refreash() {
	this->MoveRange = this->MaxMoveRange;
}

int BattleShip::GetHealth() {
	return Health;
}

void BattleShip::Remove(Node* sender, bool cleanup) {
	sender->removeFromParentAndCleanup(cleanup);
}

bool BattleShip::Check(std::vector<cocos2d::Vec2> Posses) {
	for (int i = 0; i < Posses.size(); i++) {
		if (Posses[i].x == pos.x && Posses[i].y == pos.y) {
			return true;
		}
		else if (Posses[i].x == pos.x-1 && Posses[i].y == pos.y){
			return true;
		}
		else if (Posses[i].x == pos.x + 1 && Posses[i].y == pos.y) {
			return true;
		}
	}
	return false;
}
std::vector<cocos2d::Vec2> BattleShip::GetPosses(cocos2d::Vec2* poss) {
	if (poss != nullptr) {
		return std::vector<cocos2d::Vec2>{Vec2(poss->x+1, poss->y), *poss, Vec2(poss->x-1, poss->y)};
	}
	return std::vector<cocos2d::Vec2>{Vec2(pos.x+1, pos.y), pos, Vec2(pos.x-1, pos.y)};
}