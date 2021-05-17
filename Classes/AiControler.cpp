#include "AiControler.h"
#include <algorithm>

AiControler::AiControler(Vec2 scale):scale(scale){
}

void AiControler::Turn(std::vector<Ship*> PlayerShips, std::vector<Ship*> AiShips) {
	for (int i = 0; i < AiShips.size(); i++) {
		int min_distance = 0;
		std::vector<std::vector<int>> arr;
		std::vector<int> distan;
		for (int j = 0; j < PlayerShips.size(); j++) {
			if (PlayerShips[j]->GetHealth() <= 0) {
				continue;
			}
			int distance = abs(AiShips[i]->GetPos().x- PlayerShips[j]->GetPos().x) + abs(AiShips[i]->GetPos().y - PlayerShips[j]->GetPos().y);
			distan.push_back(distance);
			if (distance <= AiShips[i]->GetAttackRange()) {
				arr.push_back(std::vector<int>{PlayerShips[j]->GetHealth(), j});
			}
		}
		if (arr.size() != 0) {
			int min = arr[0][0];
			int index = arr[0][1];
			for (int j = 1; j < arr.size(); j++) {
				if (min < arr[j][1]) {
					min = arr[j][0];
					index = arr[j][1];
				}
			}
			PlayerShips[index]->ChengeHealth(AiShips[i]->GetAttackDamage());
		}
		else {
			if (distan.size() == 0) {
				return;
			}
			int MoveRange = AiShips[i]->GetMoveRange();
			for (int j = PlayerShips.size() - 1; j >= 0; j--) {
				if (PlayerShips[j]->GetHealth() <= 0) {
					PlayerShips.erase(PlayerShips.begin()+j);
					continue;
				}
				distan[j] = abs(AiShips[i]->GetPos().x - PlayerShips[j]->GetPos().x) + abs(AiShips[i]->GetPos().y - PlayerShips[j]->GetPos().y);
			}
			auto min = std::min(distan.begin(), distan.end());
			Vec2 TargetPos;
			int index = distan.end() - min - 1;
			TargetPos.x = PlayerShips[index]->GetPos().x;
			TargetPos.y = PlayerShips[index]->GetPos().y;
			Vec2 Pos(AiShips[i]->GetPos());
			while (Pos.x > TargetPos.x && MoveRange > 0) {
				Pos.x--;
				MoveRange--;
				for (int j = 0; j < AiShips.size(); j++) {
					if (AiShips[j]->Check(std::vector<Vec2>{Pos}) && j != i) {
						Pos.x++;
						if (abs(TargetPos.x - Pos.x) + abs(TargetPos.y - Pos.y + 1) > abs(TargetPos.x - Pos.x) + abs(TargetPos.y - Pos.y - 1)) {
							Pos.y--;
						}
						else {
							Pos.y++;
						}
					}
				}
				if (abs(TargetPos.x - Pos.x) + abs(TargetPos.y - Pos.y) <= AiShips[i]->GetAttackRange()) {
					MoveRange = -1;
					AiShips[i]->SetPos(Pos);
					PlayerShips[index]->ChengeHealth(AiShips[i]->GetAttackDamage());
				}
			}	
			while (Pos.x < TargetPos.x && MoveRange > 0) {
				Pos.x++;
				MoveRange--;
				for (int j = 0; j < AiShips.size(); j++) {
					if (AiShips[j]->Check(std::vector<Vec2>{Pos}) && j != i) {
						Pos.x--;
						if (abs(TargetPos.x - Pos.x) + abs(TargetPos.y - Pos.y + 1) > abs(TargetPos.x - Pos.x) + abs(TargetPos.y - Pos.y - 1)) {
							Pos.y--;
						}
						else {
							Pos.y++;
						}
					}
				}
				if (abs(TargetPos.x - Pos.x) + abs(TargetPos.y - Pos.y) <= AiShips[i]->GetAttackRange()) {
					MoveRange = -1;
					AiShips[i]->SetPos(Pos);
					PlayerShips[index]->ChengeHealth(AiShips[i]->GetAttackDamage());
				}
			}
			while (Pos.y > TargetPos.y && MoveRange > 0) {
				Pos.y--;
				MoveRange--;
				for (int j = 0; j < AiShips.size(); j++) {
					if (AiShips[j]->Check(std::vector<Vec2>{Pos}) && j != i) {
						Pos.y++;
						if (abs(TargetPos.x - Pos.x + 1) + abs(TargetPos.y - Pos.y) > abs(TargetPos.x - Pos.x - 1) + abs(TargetPos.y - Pos.y)) {
							Pos.x--;
						}
						else {
							Pos.x++;
						}
					}
				}
				if (abs(TargetPos.x - Pos.x) + abs(TargetPos.y - Pos.y) <= AiShips[i]->GetAttackRange()) {
					MoveRange = -1;
					AiShips[i]->SetPos(Pos);
					PlayerShips[index]->ChengeHealth(AiShips[i]->GetAttackDamage());
				}
			}
			while (Pos.y < TargetPos.y && MoveRange > 0) {
				Pos.y++;
				MoveRange--;
				for (int j = 0; j < AiShips.size(); j++) {
					if (AiShips[j]->Check(std::vector<Vec2>{Pos}) && j != i) {
						Pos.y--;
						if (abs(TargetPos.x - Pos.x + 1) + abs(TargetPos.y - Pos.y) > abs(TargetPos.x - Pos.x - 1) + abs(TargetPos.y - Pos.y)) {
							Pos.x--;
						}
						else {
							Pos.x++;
						}
					}
				}
				if (abs(TargetPos.x - Pos.x) + abs(TargetPos.y - Pos.y) <= AiShips[i]->GetAttackRange()) {
					MoveRange = -1;
					AiShips[i]->SetPos(Pos);
					PlayerShips[index]->ChengeHealth(AiShips[i]->GetAttackDamage());
				}
			}
			if (MoveRange != -1) {
				AiShips[i]->SetPos(Pos);
			}
		}
	}
}