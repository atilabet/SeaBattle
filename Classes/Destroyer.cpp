#include "Destroyer.h"
#include "MusicClass.h"

Destroyer::Destroyer(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, Vec2 scale) :
	pos(pos), sprite(sprite), Scale(scale)
{
	int x = -11;
	if (sprite->getRotation() == 180) {
		x = -x;
	}
	MoveRange = MaxMoveRange = 5;
	AttackRange = 4;
	Damage = 3;
	Health = 12;
	sprite->setPosition(Vec2(pos.x * scale.x - scale.x / 2, pos.y * scale.y - scale.y / 2 + x));
}

int Destroyer::GetMoveRange() {
	return this->MoveRange;
}

int Destroyer::GetAttackDamage() {
	music::Shoot();
	MoveRange = -1;
	return this->Damage;
}

int Destroyer::GetAttackRange() {
	return this->AttackRange;
}

Vec2 Destroyer::GetPos() {
	return this->pos;
}

Sprite* Destroyer::GetSprite() {
	return this->sprite;
}

void Destroyer::SetPos(Vec2 pos) {
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

void Destroyer::ChengeHealth(int damage) {
	Health -= damage;
	if (Health <= 0) {
		auto action = CallFuncN::create(CC_CALLBACK_1(Destroyer::Remove, this, false));
		if (sprite->getParent() != nullptr)
			sprite->runAction(action);
	}
}

void Destroyer::Refreash() {
	this->MoveRange = this->MaxMoveRange;
}

int Destroyer::GetHealth() {
	return Health;
}

void Destroyer::Remove(Node* sender, bool cleanup) {
	sender->removeFromParentAndCleanup(cleanup);
}

bool Destroyer::Check(std::vector<cocos2d::Vec2> Posses) {
	for (int i = 0; i < Posses.size(); i++) {
		if (Posses[i].x == pos.x && Posses[i].y == pos.y) {
			return true;
		}
	}
	return false;
}

std::vector<cocos2d::Vec2> Destroyer::GetPosses(cocos2d::Vec2* poss) {
	if (poss != nullptr) {
		return std::vector<cocos2d::Vec2>{*poss};
	}
	return std::vector<cocos2d::Vec2>{pos};
}