#pragma once

#include "cocos2d.h"

class VictoryScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void Back(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(VictoryScene);
};

