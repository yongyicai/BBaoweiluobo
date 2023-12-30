#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"
#include "TowerBottle.h"
#include "Bullet.h"
USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocos2d;

const int _tower_bottle = 1;


Bottle::Bottle() : level(1), attackPower(10), attackSpeed(1.0f), towerType(0)
{
    // 初始化代码
}



Bottle* Bottle::create(Vec2 position)
{
    Bottle* bottle = new (std::nothrow) Bottle();
    if (bottle && bottle->levelToImagePathMap.count(bottle->level) > 0&& bottle->initWithFile(bottle->levelToImagePathMap.at(bottle->level)))
    {
        bottle->autorelease();
        //bottle->towerType = towerType;
        // 根据类型初始化不同的属性
        bottle->setPosition(position);
        auto scene = cocos2d::Director::getInstance()->getRunningScene();
        scene->addChild(bottle);
        return bottle;
    }
    
    CC_SAFE_DELETE(bottle);
    return nullptr;
}

//bool Bottle::init()
//{
  //  if (!Sprite::init())
    //{
      //  return false;
    //}
    // 初始化炮台
    //return true;
//}
void Bottle::attack()
{
   // Bullet* bullet = Bullet::create();
    //if (bullet) {
        // 设置子弹的起始位置为塔的位置
     //    bullet->setPosition(this->getPosition());

     //    // 计算瞄准目标的方向向量
     //    cocos2d::Vec2 direction = target->getPosition() - this->getPosition();
     //    direction.normalize();

     //    // 计算子弹的速度向量
     //    float bulletSpeed = 500.0f;  // 子弹速度
     //    cocos2d::Vec2 velocity = direction * bulletSpeed;

     //    // 设置子弹的速度
     //    bullet->setVelocity(velocity);

     //    // 将子弹添加到场景中
     //    auto scene = cocos2d::Director::getInstance()->getRunningScene();
     //    scene->addChild(bullet);
     //}
     // 实现攻击逻辑
     // 这可能涉及到创建一个 Projectile 类，并将其发射到目标
     // 这里可能不应该直接new bullet，因为bullet应该是发射物的基类，对于每一个tower都应该有对应的发射物子类
    //}
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