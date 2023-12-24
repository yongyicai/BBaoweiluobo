#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

class Monster : public cocos2d::Sprite {
public:
    static Monster* createWithType(int monsterType);

    void moveOnPath(const std::vector<cocos2d::Vec2>& path);
    void getAttacked(int damage);
    void showHitEffect();
    void dropCoins();

    CC_SYNTHESIZE_READONLY(int, _hitPoints, HitPoints); // 使用 CC_SYNTHESIZE_READONLY 宏来创建 getter 方法
    CC_SYNTHESIZE_READONLY(int, _monsterType, MonsterType);
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, _hpLabel, HPLabel); // 生命值显示

protected:
    Monster(int monsterType, int hitPoints);
    virtual bool init() override;

private:
    void updateHPLabel();
    void die(); // 当怪物死亡时调用
};

#endif
