#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include  "GameItSelf.h"

class PickLevel : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void GoBack(cocos2d::Ref* pSender);

	void Play(Ref* pSender);

	CREATE_FUNC(PickLevel);
};
