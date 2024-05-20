#pragma once
#include <Box2D/Box2D.h>

class Obstacle {
private:
    b2Body* obstacleBody;
public:
    Obstacle(b2World* world, float x, float y);
};
