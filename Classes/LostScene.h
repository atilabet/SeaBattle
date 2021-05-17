#pragma once

#include "cocos2d.h"

class LostScene: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void Back(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(LostScene);
};

