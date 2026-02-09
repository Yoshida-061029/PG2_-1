#pragma once
#include "Vector2.h"

class Bullet {
private:
    Vector2 pos;
    float speed;
    int radius;
    bool isActive;

public:
    Bullet();

    void Shoot(float x, float y);
    void Update();
    void Draw();

    Vector2 GetPos() const { return pos; }
    float GetPosX() const { return pos.x; }
    float GetPosY() const { return pos.y; }
    int GetRadius() const { return radius; }
    bool GetIsActive() const { return isActive; }

    void SetIsActive(bool active) { isActive = active; }
};