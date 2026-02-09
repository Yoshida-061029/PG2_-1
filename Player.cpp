#include "Player.h"
#include "Novice.h"

Player::Player(float x, float y) {
    pos.x = x;
    pos.y = y;
    speed = 5.0f;
    radius = 15;
    isAlive = true;
}

void Player::Update(char* keys) {
    if (!isAlive) return;

    if (keys[DIK_W]) {
        pos.y -= speed;
    }
    if (keys[DIK_S]) {
        pos.y += speed;
    }
    if (keys[DIK_A]) {
        pos.x -= speed;
    }
    if (keys[DIK_D]) {
        pos.x += speed;
    }

    if (pos.x < radius) pos.x = static_cast<float>(radius);
    if (pos.x > 1280 - radius) pos.x = 1280.0f - radius;
    if (pos.y < radius) pos.y = static_cast<float>(radius);
    if (pos.y > 720 - radius) pos.y = 720.0f - radius;
}

void Player::Draw() {
    if (!isAlive) return;

    Novice::DrawEllipse(
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        radius,
        radius,
        0.0f,
        BLUE,
        kFillModeSolid
    );
}

void Player::Reset() {
    pos.x = 640.0f;
    pos.y = 600.0f;
    isAlive = true;
}