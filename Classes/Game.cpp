#include "Game.h"
#include <algorithm>
#include "Destroyer.h"
#include "BattleShip.h"
USING_NS_CC;

Game::Game(int id) {
	switch (id) {
	case 1: {
		MapPng = Sprite::create("maps/level1.png");
		MapPng->setScaleX(4);
		MapPng->setScaleY(4);
		scale.x = 128;
		scale.y = 128;
		Sprite* DestroyerBlue1 = Sprite::create("Ships/DestroyerBlue.png");
		DestroyerBlue1->setScale(1.5);
		Sprite* DestroyerBlue2 = Sprite::create("Ships/DestroyerBlue.png");
		DestroyerBlue2->setScale(1.5);
		Sprite* DestroyerRed1 = Sprite::create("Ships/DestroyerRed.png");
		DestroyerRed1->setRotation(180);
		DestroyerRed1->setScale(1.5);
		Destroyer* Destroyer1_blue = new Destroyer(cocos2d::Vec2(3, 10), DestroyerBlue1, scale);
		PlayerShips.push_back(Destroyer1_blue);
		Destroyer* Destroyer2_blue = new Destroyer(Vec2(3, 3), DestroyerBlue2, scale);
		PlayerShips.push_back(Destroyer2_blue);
		Destroyer* Destroyer1_red = new Destroyer(Vec2(14, 10), DestroyerRed1, scale);
		AiShips.push_back(Destroyer1_red);
		Sprite* DestroyerRed2 = Sprite::create("Ships/DestroyerRed.png");
		DestroyerRed2->setRotation(180);
		DestroyerRed2->setScale(1.5);
		Destroyer* Destroyer2_red = new Destroyer(Vec2(14, 3), DestroyerRed2, scale);
		Sprite* BattleShipRed1 = Sprite::create("Ships/BattelshipRed.png");
		BattleShipRed1->setScaleY(2);
		BattleShipRed1->setScaleX(3);
		BattleShipRed1->setRotation(180);
		BattleShip* BattleShipRed_1 = new BattleShip(Vec2(15, 6), BattleShipRed1, scale);
		AiShips.push_back(BattleShipRed_1);
		AiShips.push_back(Destroyer2_red);
		Sprite* BattleShipBlue1 = Sprite::create("Ships/BattelshipBlue.png");
		BattleShipBlue1->setScaleY(2);
		BattleShipBlue1->setScaleX(3);
		BattleShip* BattleShipBlue_1 = new BattleShip(Vec2(2, 6), BattleShipBlue1, scale);
		PlayerShips.push_back(BattleShipBlue_1);
		break;
	}
	case 2:
	{
		MapPng = Sprite::create("maps/level2.png");
		MapPng->setScaleX(2);
		MapPng->setScaleY(2);
		scale.x = 50;
		scale.y = 64;
		Sprite* DestroyerBlue1 = Sprite::create("Ships/DestroyerBlue.png");
		DestroyerBlue1->setScaleX(0.7);
		Destroyer* Destroyer1_blue = new Destroyer(Vec2(3,10), DestroyerBlue1, scale);
		PlayerShips.push_back(Destroyer1_blue);
		Sprite* DestroyerRed1 = Sprite::create("Ships/DestroyerRed.png");
		DestroyerRed1->setScaleX(0.7);
		Destroyer* Destroyer1_red = new Destroyer(Vec2(34, 10), DestroyerRed1, scale);
		AiShips.push_back(Destroyer1_red);
		DestroyerRed1->setRotation(180);
	}
		 default:
			 break;
	}
	auto spritss = Sprite::create("Selected.png");
	spritss->setVisible(false);
	selected.push_back(spritss);
	sprite.push_back(spritss);
	Ai = new AiControler(scale);
	Player = new PlayerControler(scale);
}

cocos2d::TMXTiledMap* Game::Getmap() {
	return map;
}

cocos2d::Sprite* Game::GetSprite() {
	return MapPng;
}

void Game::Action(cocos2d::Vec2 pos) {
	if (turn == PlayerTurn) {
		Player->OnClick(PlayerShips, AiShips, map, pos, sprite);
	}
}

std::vector<Sprite*> Game::GetSprites() {
	std::vector<Sprite*> sprites;
	for (int i = 0; i < this->PlayerShips.size(); i++) {
		sprites.push_back(PlayerShips[i]->GetSprite());
	}
	for (int i = 0; i < this->AiShips.size(); i++) {
		sprites.push_back(AiShips[i]->GetSprite());
	}
	sprites.push_back(sprite[0]);;
	return sprites;
}

void Game::ChengeTurn() {
	if (turn == PlayerTurn) {
		for (int i = 0; i < PlayerShips.size(); i++) {
			PlayerShips[i]->Refreash();
		}
		turn = AiTurn;
		for (int i = AiShips.size() - 1; i >= 0; i--) {
			if (AiShips[i]->GetHealth() <= 0) {
				AiShips.erase(AiShips.begin() + i);
			}
		}
		if (AiShips.size() == 0) {
			auto scene = VictoryScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		Ai->Turn(PlayerShips, AiShips);
		this->ChengeTurn();
	}
	else {
		for (int i = 0; i < AiShips.size(); i++) {
			AiShips[i]->Refreash();
		}
		for (int i = PlayerShips.size()-1; i >= 0; i--) {
			if (PlayerShips[i]->GetHealth() <= 0){
				PlayerShips.erase(PlayerShips.begin()+i);
			}
		}
		if (PlayerShips.size() == 0) {
			auto scene = LostScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		turn = PlayerTurn;
	}
}

Turn Game::CheckTurn() {
	return turn;
}
