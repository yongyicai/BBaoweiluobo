#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"
#include "TowerBottle.h"
#include "BottleBullet.h"
#include "Monster.h"
USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocos2d;

const int _tower_bottle = 1;


Bottle::Bottle() : level(1), attackPower(10), attackSpeed(1.0f), towerType(0),attackRange(100)
{
    // 初始化代码
}



Bottle* Bottle::create()
{
    Bottle* bottle = new (std::nothrow) Bottle();

    
        if (bottle && (bottle->initWithFile("Tower/Bottle/ID1_22.PNG")))
        {
            bottle->autorelease();


            return bottle;
        }

    CC_SAFE_DELETE(bottle);
    return nullptr;
}


void Bottle::attack(cocos2d::Sprite* target)
{
    BottleBullet* bottlebullet = BottleBullet::create();
    if (bottlebullet) {
        // 设置子弹的起始位置为塔的位置
        bottlebullet->setPosition(this->getPosition());
      
        // 将子弹添加到场景中
        auto scene = cocos2d::Director::getInstance()->getRunningScene();
        scene->addChild(bottlebullet);
    }
    
}

void Bottle::upgrade()
{
    // 升级炮台，提高属性
    level++;
    attackPower += 5; // 示例：每次升级增加5点攻击力
}

//void Bottle::remove()
//{
//    // 移除炮台
//    this->removeFromParent();
//}


void Bottle::setTowerImage(const std::string& imagePath) {
    auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(imagePath);
    setTexture(texture);
}

void Bottle::update(float deltaTime, std::vector<Monster*>& monsterList)
{
    // 检测攻击范围内是否有怪物
    Monster* target = findTargetInAttackRange(monsterList);

    if (target)
    {
        // 自动瞄准敌人
        rotateTowerTowardsTarget(target);

        //应该设置冷却时间
        attack(target);
    }
}

Monster* Bottle::findTargetInAttackRange(std::vector<Monster*> monsterList)
{
    // 遍历怪物列表，查找位于攻击范围内的怪物
    for (Monster* monster : monsterList)
    {
        float distance = (getPosition().distance(monster->getPosition()));

        if (distance <= attackRange)
        {
            return monster;
        }
    }

    return nullptr;
}

void Bottle::rotateTowerTowardsTarget(Monster* target)
{
    // 计算塔与目标怪物之间的角度
    Vec2 direction = target->getPosition() - getPosition();
    float angle = atan2(direction.y, direction.x);

    // 将角度应用于塔的旋转
    setRotation(-CC_RADIANS_TO_DEGREES(angle));
}