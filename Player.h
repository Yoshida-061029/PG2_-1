#pragma once
#include "Vector2.h"

class Player {
private:
    Vector2 pos;
    float speed;
    int radius;
    bool isAlive;

public:
    Player(float x, float y);

    void Update(char* keys);
    void Draw();

    Vector2 GetPos() const { return pos; }
    float GetPosX() const { return pos.x; }
    float GetPosY() const { return pos.y; }
    int GetRadius() const { return radius; }
    bool GetIsAlive() const { return isAlive; }

    void SetPos(Vector2 newPos) { pos = newPos; }
    void SetPosX(float x) { pos.x = x; }
    void SetPosY(float y) { pos.y = y; }
    void SetIsAlive(bool alive) { isAlive = alive; }

    void Reset();
};