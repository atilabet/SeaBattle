#pragma once

#include "cocos2d.h"
#include<iostream>
#include "Ship.h"

USING_NS_CC;

class PlayerControler
{
public:
	PlayerControler(Vec2);
	void OnClick(std::vector<Ship*>, std::vector<Ship*>, TMXTiledMap*, Vec2, std::vector<Sprite*>);
private:
	unsigned int Selected = -1;
	Vec2 scale;
	Vec2 GetTileNum(TMXTiledMap* ,Vec2);
};

