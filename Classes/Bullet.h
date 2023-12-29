// Bullet.h
#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
public:
    Bullet();
    

    static Bullet* create(const cocos2d::Vec2& position, const cocos2d::Vec2& direction);

    virtual bool init() override;
    virtual void update(float delta) override;

    void setDamage(int damage);

protected:
    int damage;
    int speed;
    int level;
    cocos2d::Vec2 direction;
};

#endif


