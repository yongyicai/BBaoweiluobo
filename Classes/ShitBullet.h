#pragma once

#ifndef __SHIT_BULLET_H__
#define __SHIT_BULLET_H__

#include "cocos2d.h"
#include "Monster.h"

class ShitBullet : public cocos2d::Sprite {
public:
    bool targetDead = false;
    static ShitBullet* createWithTarget(Monster* target, const std::string& filename, float speed, int damage);
    void initOptions(Monster* target, float speed, int damage);
    void moveToTarget();
    void targetDied();
private:
    Monster* target;
    float speed;
    int damage;
};

#endif 
