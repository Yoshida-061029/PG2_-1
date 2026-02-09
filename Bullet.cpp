#include "Bullet.h"
#include "Novice.h"

Bullet::Bullet() {
    pos.x = 0.0f;
    pos.y = 0.0f;
    speed = 10.0f;
    radius = 5;
    isActive = false;
}

void Bullet::Shoot(float x, float y) {
    pos.x = x;
    pos.y = y;
    isActive = true;
}

void Bullet::Update() {
    if (!isActive) return;

    pos.y -= speed;

    if (pos.y < -radius) {
        isActive = false;
    }
}

void Bullet::Draw() {
    if (!isActive) return;

    Novice::DrawEllipse(
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        radius,
        radius,
        0.0f,
        WHITE,
        kFillModeSolid
    );
}