#pragma once
#include "Ship.h"
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class Destroyer : public Ship
{
public:
	Destroyer(cocos2d::Vec2, cocos2d::Sprite*, cocos2d::Vec2);
	cocos2d::Vec2 GetPos();
	void SetPos(cocos2d::Vec2 pos);
	int GetMoveRange();
	int GetAttackRange();
	int GetAttackDamage();
	void ChengeHealth(int damage);
	cocos2d::Sprite* GetSprite();
	void Refreash();
	int GetHealth();
	bool Check(std::vector<cocos2d::Vec2>);
	std::vector<cocos2d::Vec2> GetPosses(cocos2d::Vec2* = nullptr);
private:
	cocos2d::Vec2 pos;
	int MoveRange;
	int MaxMoveRange;
	int AttackRange;
	int Health;
	int Damage;
	cocos2d::Vec2 Scale;
	cocos2d::Sprite* sprite;
	void Remove(cocos2d::Node* sender, bool cleanup);
};

