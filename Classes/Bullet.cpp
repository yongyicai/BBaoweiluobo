#include "BottleBullet.h"

Bullet::Bullet() : damage(0)
{
    // 初始化代码
}

//Bullet::~Bullet()
//{
//    // 清理代码
//}

Bullet* Bullet::create(const cocos2d::Vec2& position, const cocos2d::Vec2& direction)
{
    Bullet* bullet = new (std::nothrow) Bullet();
    
    if (bullet && bullet->initWithFile("Resources/Tower/Bottle/ID1_2.PNG"))
    {
        bullet->autorelease();
        bullet->setPosition(position);
        bullet->direction = direction;
        // 根据需要进行进一步的初始化
        auto scene = cocos2d::Director::getInstance()->getRunningScene();
        scene->addChild(bullet);
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}

bool Bullet::init()
{
    if (!cocos2d::Sprite::init())
    {
        return false;
    }

    // 根据子弹的需求进行初始化操作

    return true;
}

void Bullet::update(float delta)
{
    // 根据子弹的速度和方向更新子弹的位置
    float speed = 100.0f; // 根据实际需求调整速度
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

void Bullet::setDamage(int damage)
{
    this->damage = damage;
}