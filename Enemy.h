#pragma once
#include "Vector2.h"

class Enemy {
private:
    Vector2 pos;
    Vector2 speed;
    int radius;
    bool isAlive;
    int hp;

public:
    Enemy();

    void Respawn();
    void Update();
    void Draw();
    void TakeDamage();

    Vector2 GetPos() const { return pos; }
    float GetPosX() const { return pos.x; }
    float GetPosY() const { return pos.y; }
    int GetRadius() const { return radius; }
    bool GetIsAlive() const { return isAlive; }

    void SetIsAlive(bool alive) { isAlive = alive; }
};