// Bottle.h
#ifndef __Bottle_H__
#define __Bottle_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Bullet.h"
#include "Tower.h"
#include "ui/CocosGUI.h"

class Bottle : public Tower {
public:
    static Bottle* create(const cocos2d::Vec2& position);

    // ¹¥»÷Ïà¹ØÂß¼­
    void update(float dt, std::vector<Monster*> monsters);
    bool isMonsterInRange(Monster* monster);
    void checkForMonstersInRange(std::vector<Monster*> monsters);
    void attack(Monster* target);

    void upgrade();
    void remove() override;
    void showAttackRange()override; // ÏÔÊ¾¹¥»÷·¶Î§
    void showUpgradeAndRemoveButtons()override; // ÏÔÊ¾Éý¼¶ºÍÒÆ³ý°´Å¥
    void hideAttackRangeAndButtons(); // ÒÆ³ý

private:
    cocos2d::ui::Button *upgradeButton; // Éý¼¶°´Å¥
    cocos2d::ui::Button *removeButton;  // ÒÆ³ý°´Å¥
    Sprite* attackRange_;
};

#endif // __Bottle_H__
