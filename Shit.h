#ifndef __SHIT_H__
#define __SHIT_H__

#include "cocos2d.h"
#include "Monster.h"
#include "GptBullet.h"

class Shit : public cocos2d::Sprite {
public:
    int level = 1;
    static Shit* create(const cocos2d::Vec2& position);
    void upgrade();
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

#endif 

