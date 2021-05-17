#pragma once

#include"cocos2d.h"
#include "MusicClass.h"
#include <iostream>

class Ship {
public:
	virtual cocos2d::Vec2 GetPos() = 0;
	virtual void SetPos(cocos2d::Vec2 pos) = 0;
	virtual int GetMoveRange() = 0;
	virtual int GetAttackRange() = 0;
	virtual int GetAttackDamage() = 0;
	virtual void ChengeHealth(int damage) = 0;
	virtual cocos2d::Sprite* GetSprite() = 0;
	virtual void Refreash() = 0;
	virtual int GetHealth() = 0;
	virtual bool Check(std::vector<cocos2d::Vec2> Poses) = 0;
	virtual std::vector<cocos2d::Vec2> GetPosses(cocos2d::Vec2* = nullptr) = 0;
private:
	virtual void Remove(cocos2d::Node* sender, bool cleanup) = 0;
};
