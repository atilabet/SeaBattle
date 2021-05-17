#include "MusicClass.h"

USING_NS_CC;

void music::ButtonClickEffect() {
	AudioEngine::play2d("music/ButtonClick.mp3");
}

void music::CheckBoxClickEffect() {
	AudioEngine::play2d("music/CheckBoxClick.mp3");
}

void music::Shoot() {
	AudioEngine::play2d("music/ShootDestroyer.mp3");
}

void music::Victory() {
	AudioEngine::stopAll();
	AudioEngine::play2d("music/Victory.mp3");
}

void music::Lost() {
	AudioEngine::stopAll();
	AudioEngine::play2d("music/Lost.mp3");
}

void music::Move(int n) {
	for (int i = 0; i <= n % 6; i++) {
		AudioEngine::play2d("music/MoveSound.mp3", false, 0.1F);
	}
}

void music::PlaneAttack() {
	AudioEngine::play2d("music/PlanesAttack.mp3");
}