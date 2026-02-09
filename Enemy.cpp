#include "Enemy.h"
#include "Novice.h"
#include <stdlib.h>
#include <time.h>

Enemy::Enemy() {
    pos.x = 0.0f;
    pos.y = 0.0f;
    speed.x = 0.0f;
    speed.y = 0.0f;
    radius = 15;
    isAlive = false;
    hp = 1;

    srand(static_cast<unsigned int>(time(NULL)));
}

void Enemy::Respawn() {
    pos.x = static_cast<float>(rand() % 1200 + 40);
    pos.y = static_cast<float>(-radius);

    speed.x = static_cast<float>((rand() % 3 - 1));
    speed.y = static_cast<float>(rand() % 3 + 2);

    isAlive = true;
    hp = 1;
}

void Enemy::Update() {
    if (!isAlive) return;

    pos.x += speed.x;
    pos.y += speed.y;

    if (pos.y > 720 + radius) {
        Respawn();
    }

    if (pos.x <= radius || pos.x >= 1280 - radius) {
        speed.x = -speed.x;
    }
}

void Enemy::Draw() {
    if (!isAlive) return;

    Novice::DrawEllipse(
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        radius,
        radius,
        0.0f,
        RED,
        kFillModeSolid
    );
}

void Enemy::TakeDamage() {
    hp--;
    if (hp <= 0) {
        isAlive = false;
    }
}