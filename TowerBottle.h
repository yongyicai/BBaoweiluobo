#ifndef __Bottle_H__
#define __Bottle_H__

#include "cocos2d.h"
#include "Monster.h"
#include "GptBullet.h"

class Bottle : public cocos2d::Sprite {
public:
    static Bottle* create(const cocos2d::Vec2& position);
    void update(float dt, std::vector<Monster*> monsters);
    bool isMonsterInRange(Monster* monster);
    void attack(Monster* target);

private:
    std::vector<Monster*> monstersInRange;
    float attackRange;
    float attackSpeed;
    float timeSinceLastAttack;

    void checkForMonstersInRange(std::vector<Monster*> monsters);
};

#endif // __Bottle_H__
