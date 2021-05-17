#include "PickLevel.h"
#include"MusicClass.h"

USING_NS_CC;

int LevelId = 0;

Scene* PickLevel::createScene() {
	return PickLevel::create();
}

bool PickLevel::init() {
	if (!Scene::init())
	{
		return false;
	}
	LayerColor* _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(_bgColor, -10);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto label = Label::createWithTTF("Pick Level", "fonts/Marker Felt.ttf", 24);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(Vec2(origin.x + 1000, origin.y + 1400));
	this->addChild(label, 1);
	label->setScale(6.0);
	auto label1 = Label::createWithTTF("Level 1", "fonts/arial.ttf", 24);
	label1->setColor(Color3B(0,0,0));
	label1->setPosition(Vec2(origin.x+300, origin.y+1240));
	this->addChild(label1, 1);
	auto checkbox1 = ui::CheckBox::create("CheckBox/Normal.png", "CheckBox/Normal_Disable.png", "CheckBox/Active.png", "CheckBox/Normal_Disable.png", "CheckBox/Active_Disable.png");
	checkbox1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				LevelId = 1;
				music::CheckBoxClickEffect();
				break;
			default:
				break;
		}
	});
	auto checkbox2 = ui::CheckBox::create("CheckBox/Normal.png", "CheckBox/Normal_Disable.png", "CheckBox/Active.png", "CheckBox/Normal_Disable.png", "CheckBox/Active_Disable.png");
	checkbox2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			LevelId = 2;
			music::CheckBoxClickEffect();
			break;
		default:
			break;
		}
		});
	this->addChild(checkbox2, 1);
	checkbox2->setPosition(Vec2(origin.x + 500, origin.y + 1200));
	auto label2 = Label::createWithTTF("Level 2", "fonts/arial.ttf", 24);
	label2->setColor(Color3B(0, 0, 0));
	label2->setPosition(Vec2(origin.x + 500, origin.y + 1240));
	this->addChild(label2, 1);
	auto backitem = MenuItemImage::create("GoBack.png", "GoBack.png", CC_CALLBACK_1(PickLevel::GoBack, this));
	auto playitem = MenuItemImage::create("Play.png", "Play.png", CC_CALLBACK_1(PickLevel::Play, this));
	auto menu = Menu::create(backitem, playitem, NULL);
	playitem->setScale(4.0);
	backitem->setScale(4.0);
	playitem->setPosition(Vec2(origin.x+1700, origin.y+300));
	backitem->setPosition(Vec2(origin.x + 1300, origin.y+300));
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	this->addChild(checkbox1, 1);
	checkbox1->setPosition(Vec2(origin.x+300, origin.y+1200));
	return true;
}

void PickLevel::GoBack(cocos2d::Ref* pSender) {
	music::ButtonClickEffect();
	Director::getInstance()->popScene();
}

void PickLevel::Play(Ref* pSender) {
	if (LevelId != 0) {
		music::ButtonClickEffect();
		auto scene = GameItSelf::createScene(LevelId);
		Director::getInstance()->replaceScene(scene);
	}
}