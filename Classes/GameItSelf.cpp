#include "GameItSelf.h"
#include "MusicClass.h"
USING_NS_CC;

Game* game;

Scene* GameItSelf::createScene(int LevelId) {
	game = new Game(LevelId);
	return GameItSelf::create();
}

bool GameItSelf::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto map = game->GetSprite();
	map->setPosition(Vec2(origin.x+1024, origin.y+770));
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchEnded = [&](Touch* touch, Event* event) {
		Vec2 position = touch->getLocation();
		game->Action(position);
	};
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event) {
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->addChild(map, 1);
	Sprite* sprite = new Sprite;
	std::vector<Sprite*> Ships = game->GetSprites();
	for (int i = 0; i < Ships.size(); i++) {
		this->addChild(Ships[i], 1);
	}
	auto TurnObject = MenuItemImage::create("Turn.png", "Turn.png", CC_CALLBACK_1(GameItSelf::Turn, this));
	TurnObject->setScale(4);
	TurnObject->setPosition(Vec2(origin.x+1700, origin.y+100));
	auto menu = Menu::create(TurnObject, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void GameItSelf::Turn(Ref* pSender) {
	music::ButtonClickEffect();
	if (game->CheckTurn() == AiTurn) {
		return;
	}
	game->ChengeTurn();
}