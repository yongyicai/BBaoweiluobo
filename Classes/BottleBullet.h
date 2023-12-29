// Bullet.h
#ifndef __BOTTLE_BULLET_H__
#define __BOTTLE_BULLET_H__

#include "Bullet.h"

class BottleBullet : public Bullet
{
public:
    BottleBullet();
    /*virtual ~BottleBullet();*/

    static BottleBullet* create();

    virtual bool init() override;
    virtual void update(float delta) override;

    void setDamage(int damage);

private:
    int damage;
    int speed;
    int level;
    cocos2d::Vec2 direction;
    std::unordered_map<int, std::string> levelToImagePathMap =
    {
        {1,"Resources/Tower/Bottle/ID1_22.PNG"},
        {2,"Resources/Tower/Bottle/ID1_15.PNG"},
        {3,"Resources/Tower/Bottle/ID1_5.PNG"}
    };
};

#endif


