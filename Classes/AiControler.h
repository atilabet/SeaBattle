#pragma once

#include "cocos2d.h"
#include "Ship.h"
#include <iostream>

USING_NS_CC;

class AiControler {
public:
	AiControler(Vec2);
	void Turn(std::vector<Ship*>, std::vector<Ship*>);
private:
	Vec2 scale;
};