#ifndef __TOWER_H__
#define __TOWER_H__

#include "cocos2d.h"
#include "Monster.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;

class Tower : public cocos2d::Sprite
{
public:
    Tower();
    /*virtual ~Tower();//在sprite类中已经有析构函数了*/

    static Tower* create(Vec2 position,int towerType);//创建一个塔，在指定位置加载图片

    virtual bool init() override;//判断初始化是否成功
    virtual void attack();//攻击，实例化一个bullet，寻路，到怪物身上消失，再次生成。瞄准时要改变角度
    virtual void upgrade() ;//升级，各项属性的升级，改变图片
    virtual void remove() ;//移除
    void showAttackRange(); // 显示攻击范围
    void showUpgradeAndRemoveButtons(); // 显示升级和移除按钮
    void hideAttackRangeAndButtons();
protected:
    int level; // 等级
    int towerType;
    std::vector<Monster*> monstersInRange; // 在范围内的怪物数组
    int attackDamage; // 攻击伤害
    float attackRange; //攻击范围
    float attackSpeed; // 攻击速度
    float timeSinceLastAttack;

    cocos2d::ui::Button* upgradeButton; // 升级按钮
    cocos2d::ui::Button* removeButton;  // 移除按钮
    Sprite* attackRange_;
};
#endif