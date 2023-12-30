#pragma once
// Fan.h
#ifndef __FAN_H__
#define __FAN_H__

#include "cocos2d.h"
#include "Monster.h"
#include "GptBullet.h"

class Fan : public cocos2d::Sprite {
public:
    bool init(const std::string& topImageFile, const std::string& bottomImageFile);
    static Fan* create(const cocos2d::Vec2& position);
    void update(float dt, std::vector<Monster*> monsters);
    bool isMonsterInRange(Monster* monster);
    void attack(Monster* target);
    void checkForMonstersInRange(std::vector<Monster*> monsters);
private:
    std::vector<Monster*> monstersInRange;
    float attackRange;
    float attackSpeed;
    float timeSinceLastAttack;

    
};

#endif // __Fan_H__
