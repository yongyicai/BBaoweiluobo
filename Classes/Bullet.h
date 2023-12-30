// Bullet.h
#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Monster.h"

class Bullet : public cocos2d::Sprite {
public:
    static Bullet* createWithTarget(Monster* target, const std::string& filename, float speed, int damage);
    void initOptions(Monster* target, float speed, int damage);
    void moveToTarget();
    void onHitMonster(Monster* monster);

private:
    Monster* target;
    float speed;
    int damage;
};

#endif // __BULLET_H__