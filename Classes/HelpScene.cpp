#include "HelpScene.h"
#include"MusicClass.h"

USING_NS_CC;

Scene* HelpScene::createScene() {
	return HelpScene::create();
}

bool HelpScene::init() {
	if (!Scene::init()) {
		return false;
	}
	LayerColor* _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(_bgColor, -10);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto item = MenuItemImage::create("GoBack.png", "GoBack.png", CC_CALLBACK_1(HelpScene::GoBack, this));
	item->setPosition(Vec2(origin.x + 1000, origin.y + 700));
	item->setScale(4.0);
	auto menu = Menu::create(item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	auto label = Label::createWithTTF("There is no help for you", "fonts/Marker Felt.ttf", 24);
	label->setScale(5.0);
	label->setColor(Color3B(0,0,0));
	label->setPosition(Vec2(origin.x + 1000, origin.y + 900));
	this->addChild(label, 1);
	return true;
}

void HelpScene::GoBack(cocos2d::Ref* pSender) {
	music::ButtonClickEffect();
	Director::getInstance()->popScene();
}