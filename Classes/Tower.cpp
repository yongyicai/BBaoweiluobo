#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"
#include "Tower.h"


USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocos2d;

Tower::Tower() : level(1), attackSpeed(1.0f), towerType(0)
{
    // 初始化代码
}

//Tower::~Tower()
//{
//    // 清理代码
//}
Tower* Tower::create(Vec2 position,int towerType)
{
    Tower* tower = new (std::nothrow) Tower();
    if (tower && tower->initWithFile("tower_base.png"))
    {
        tower->autorelease();
        tower->towerType = towerType;
        tower->setPosition(position);
        // 根据类型初始化不同的属性
        return tower;
    }
    CC_SAFE_DELETE(tower);
    return nullptr;
}

bool Tower::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // 初始化炮台
    return true;
}
void Tower::attack()
{
    // 实现攻击逻辑
    // 这可能涉及到创建一个 Projectile 类，并将其发射到目标
}

void Tower::upgrade()
{
    // 升级炮台，提高属性
    //将原先的炮台移除，重新生成一个新炮台
}

void Tower::remove()
{
    // 移除炮台
    this->removeFromParentAndCleanup(true);
}
void Tower::showAttackRange() {

    // 显示攻击范围
} 
void Tower::showUpgradeAndRemoveButtons() {

    // 显示升级和移除按钮
}