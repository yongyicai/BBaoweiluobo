#pragma once
// Bullet.h
#ifndef __FAN_BULLET_H__
#define __FAN_BULLET_H__

#include "cocos2d.h"
#include "Monster.h"

class FanBullet : public cocos2d::Sprite {
public:
    bool targetDead = false;
    static FanBullet* createWithTarget(Monster* target, const std::string& filename, float speed, int damage);
    void initOptions(Monster* target, float speed, int damage);
    void moveToTarget();
    //void targetDied();
private:
    Monster* target;
    float speed;
    int damage;
};

#endif 
