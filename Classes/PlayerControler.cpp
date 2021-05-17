#include "PlayerControler.h"

PlayerControler::PlayerControler(Vec2 pos) {
	scale.x = pos.x;
	scale.y = pos.y;
}

void PlayerControler::OnClick(std::vector<Ship*> PlayerShips, std::vector<Ship*> AiShips, TMXTiledMap* map, Vec2 ClickPos, std::vector<Sprite*> select) {
	if (Selected == -1){
		Vec2 MapPos = GetTileNum(map, ClickPos);
		for (int i = 0; i < PlayerShips.size(); i++) {
			if (PlayerShips[i]->GetPos().x == MapPos.x && PlayerShips[i]->GetPos().y == MapPos.y) {
				if (PlayerShips[i]->GetPosses().size() == 1) {
					select[0]->setPosition(Vec2(MapPos.x*scale.x - 54, MapPos.y*scale.y - 74));
					select[0]->setScale(0);
					select[0]->setScaleX(20);
					select[0]->setScaleY(20);
				}
				else if (PlayerShips[i]->GetPosses().size() == 3) {
					select[0]->setPosition(Vec2(MapPos.x * scale.x - 36, MapPos.y * scale.y - 74));
					select[0]->setScale(0);
					select[0]->setScaleX(61);
					select[0]->setScaleY(20);
				}
				select[0]->setVisible(true);
				Selected = i;
				break;
			}
		}
	}
	else {
		select[0]->setVisible(false);
		if (PlayerShips[Selected]->GetMoveRange() == -1) {
			Selected = -1;
			return;
		}
		Vec2 MapPos = GetTileNum(map, ClickPos);
		for (int i = 0; i < AiShips.size(); i++) {
			if (AiShips[i]->Check(std::vector<Vec2>{MapPos})) {
				int distance = abs(AiShips[i]->GetPos().x - PlayerShips[Selected]->GetPos().x)+ abs(AiShips[i]->GetPos().y - PlayerShips[Selected]->GetPos().y);
				if (distance <= PlayerShips[Selected]->GetAttackRange()) {
					AiShips[i]->ChengeHealth(PlayerShips[Selected]->GetAttackDamage());
				}
				Selected = -1;
				return;
			}
		}
		for (int i = 0; i < PlayerShips.size(); i++) {
			if (PlayerShips[i]->Check(PlayerShips[Selected]->GetPosses(&MapPos)) && i != Selected) {
				return;
			}
		}
		for (int i = 0; i < AiShips.size(); i++) {
			if (AiShips[i]->Check(PlayerShips[Selected]->GetPosses(&MapPos))) {
				return;
			}
		}
		PlayerShips[Selected]->SetPos(MapPos);
		Selected = -1;
	}
}

Vec2 PlayerControler::GetTileNum(TMXTiledMap* map, Vec2 ClickPos) {
	Vec2 Pos;
	Pos.y = int(ClickPos.y / scale.y)+1;
	Pos.x = int(ClickPos.x/ scale.x)+1;
	return Pos;
}