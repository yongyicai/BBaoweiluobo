#ifndef __TOWER_H__
#define __TOWER_H__

#include "cocos2d.h"
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
    virtual void onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//点击时展示范围
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void setTowerImage(const std::string& imagePath);
protected:
    int level;
    int attackPower;
    int towerType;
    float attackSpeed;
    float attackRange;
    

};
#endif