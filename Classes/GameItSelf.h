#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Game.h"

class GameItSelf : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(int LevelId);

	virtual bool init();

	void Turn(Ref* pSender);

	CREATE_FUNC(GameItSelf);
};
