#include "LostScene.h"
#include "HelloWorldScene.h"
#include "MusicClass.h"
USING_NS_CC;

Scene* LostScene::createScene() {
	return LostScene::create();
}

bool LostScene::init() {
	if (!Scene::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	LayerColor* _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(_bgColor, -10);
	auto label = Label::createWithTTF("You losttttttttttt", "fonts/Marker Felt.ttf", 24);
	this->addChild(label, 1);
	label->setScale(6.0);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(Vec2(origin.x + 1000, origin.y + 700));
	auto MenuItem = MenuItemImage::create("GoBack.png", "GoBack.png", CC_CALLBACK_1(LostScene::Back, this));
	auto menu = Menu::create(MenuItem, NULL);
	MenuItem->setPosition(Vec2(origin.x + 1000, origin.y + 400));
	MenuItem->setScale(4.0);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	music::Lost();
	return true;
}

void LostScene::Back(Ref* pSender) {
	music::ButtonClickEffect();
	auto scene = HelloWorld::createScene();
	Director::getInstance()->pushScene(scene);
}