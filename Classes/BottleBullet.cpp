#include "BottleBullet.h"

BottleBullet::BottleBullet() : damage(0),speed(10)
{
    // 初始化代码
}

//BottleBullet::~Bullet()
//{
//    // 清理代码
//}

BottleBullet* BottleBullet::create()
{
    //bottle&& bottle->levelToImagePathMap.count(bottle->level) > 0 && bottle->initWithFile())
    BottleBullet* bottlebullet = new (std::nothrow) BottleBullet();
    if (bottlebullet && bottlebullet->levelToImagePathMap.count(bottlebullet->level) > 0&& bottlebullet->initWithFile(bottlebullet->levelToImagePathMap.at(bottlebullet->level)))
    {
        bottlebullet->autorelease();
        
        
        // 根据需要进行进一步的初始化
        return bottlebullet;
    }
    CC_SAFE_DELETE(bottlebullet);
    return nullptr;
}

bool BottleBullet::init()
{
    if (!cocos2d::Sprite::init())
    {
        return false;
    }
    return true;
}

void BottleBullet::update(float delta)
{
    // 根据子弹的速度和方向更新子弹的位置
    // 根据实际需求调整速度
    cocos2d::Vec2 newPosition = getPosition() + (direction * speed * delta);
    setPosition(newPosition);

    // 检测子弹与怪物的碰撞，根据实际游戏逻辑处理
    // ...

    // 检测子弹是否超出游戏区域，如果是，则销毁子弹对象
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    if (newPosition.x < 0 || newPosition.x > visibleSize.width || newPosition.y < 0 || newPosition.y > visibleSize.height)
    {
        removeFromParentAndCleanup(true);
    }
}

void BottleBullet::setDamage(int damage)
{
    this->damage = damage;
}