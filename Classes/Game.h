#pragma once

#include "cocos2d.h"
#include "Ship.h"
#include <iostream>
#include "PlayerControler.h"
#include "AiControler.h"
#include "VictoryScene.h"
#include "LostScene.h"


enum Turn {
	PlayerTurn,
	AiTurn
};

class Game
{
public:
	Game(int id);
	cocos2d::TMXTiledMap* Getmap();
	cocos2d::Sprite* GetSprite();
	void Action(cocos2d::Vec2 pos);
	std::vector<cocos2d::Sprite*> GetSprites();
	void ChengeTurn();
	Turn CheckTurn();
private:
	PlayerControler* Player;
	AiControler* Ai;
	cocos2d::TMXTiledMap* map;
	cocos2d::Sprite* MapPng;
	Turn turn = PlayerTurn;
	std::vector<Ship*> PlayerShips;
	std::vector<Ship*> AiShips;
	cocos2d::Vec2 scale;
	std::vector<cocos2d::Sprite*> sprite;
	std::vector<cocos2d::Sprite*> selected;
};

