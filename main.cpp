#include <Novice.h>
#include "Vector2.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <cmath>

const char kWindowTitle[] = "GC1B_12_ヨシダ_ハルキ";

enum Scene {
	TITLE,
	GAME,
	GAME_OVER
};

const int BULLET_MAX = 30;
const int ENEMY_MAX = 5;

bool CheckCircleCollision(float x1, float y1, int r1, float x2, float y2, int r2) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float distance = sqrtf(dx * dx + dy * dy);
	float radiusSum = static_cast<float>(r1 + r2);

	return distance < radiusSum;
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	Novice::Initialize(kWindowTitle, 1280, 720);

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Scene currentScene = TITLE;

	Player player(640.0f, 600.0f);

	Bullet bullets[BULLET_MAX];

	Enemy enemies[ENEMY_MAX];

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemies[i].Respawn();
	}

	int score = 0;

	int shootCooldown = 0;

	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();

		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		switch (currentScene) {
		case TITLE:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				currentScene = GAME;
				player.Reset();
				score = 0;
				for (int i = 0; i < BULLET_MAX; i++) {
					bullets[i].SetIsActive(false);
				}
				for (int i = 0; i < ENEMY_MAX; i++) {
					enemies[i].Respawn();
				}
			}
			break;

		case GAME:
			player.Update(keys);

			if (shootCooldown > 0) {
				shootCooldown--;
			}

			if (keys[DIK_SPACE] && shootCooldown == 0) {
				for (int i = 0; i < BULLET_MAX; i++) {
					if (!bullets[i].GetIsActive()) {
						bullets[i].Shoot(player.GetPosX(), player.GetPosY());
						shootCooldown = 10;
						break;
					}
				}
			}

			for (int i = 0; i < BULLET_MAX; i++) {
				bullets[i].Update();
			}

			for (int i = 0; i < ENEMY_MAX; i++) {
				enemies[i].Update();

				if (!enemies[i].GetIsAlive()) {
					enemies[i].Respawn();
				}
			}

			for (int i = 0; i < BULLET_MAX; i++) {
				if (bullets[i].GetIsActive()) {
					for (int j = 0; j < ENEMY_MAX; j++) {
						if (enemies[j].GetIsAlive()) {
							if (CheckCircleCollision(
								bullets[i].GetPosX(), bullets[i].GetPosY(), bullets[i].GetRadius(),
								enemies[j].GetPosX(), enemies[j].GetPosY(), enemies[j].GetRadius()
							)) {
								bullets[i].SetIsActive(false);
								enemies[j].TakeDamage();
								score += 100;
							}
						}
					}
				}
			}

			if (player.GetIsAlive()) {
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (enemies[i].GetIsAlive()) {
						if (CheckCircleCollision(
							player.GetPosX(), player.GetPosY(), player.GetRadius(),
							enemies[i].GetPosX(), enemies[i].GetPosY(), enemies[i].GetRadius()
						)) {
							player.SetIsAlive(false);
							currentScene = GAME_OVER;
						}
					}
				}
			}

			break;

		case GAME_OVER:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				currentScene = TITLE;
			}
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (currentScene) {
		case TITLE:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000033FF, kFillModeSolid);
			Novice::ScreenPrintf(500, 300, "STG GAME");
			Novice::ScreenPrintf(450, 400, "Press SPACE to Start");
			Novice::ScreenPrintf(400, 500, "WASD: Move  SPACE: Shoot");
			break;

		case GAME:

			player.Draw();

			for (int i = 0; i < BULLET_MAX; i++) {
				bullets[i].Draw();
			}

			for (int i = 0; i < ENEMY_MAX; i++) {
				enemies[i].Draw();
			}
			break;

		case GAME_OVER:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x330000FF, kFillModeSolid);
			Novice::ScreenPrintf(500, 300, "GAME OVER");
			Novice::ScreenPrintf(450, 400, "Final Score: %d", score);
			Novice::ScreenPrintf(400, 500, "Press SPACE to Title");
			break;
		}

		///
		/// ↑描画処理ここまで
		///

		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}