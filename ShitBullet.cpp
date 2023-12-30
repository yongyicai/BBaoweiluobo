// Bullet.cpp
#include "ShitBullet.h"

USING_NS_CC;

ShitBullet* ShitBullet::createWithTarget(Monster* target, const std::string& filename, float speed, int damage) {
    ShitBullet* shitbullet = new (std::nothrow) ShitBullet();
    if (shitbullet && shitbullet->initWithFile(filename)) {
        shitbullet->autorelease();
        shitbullet->initOptions(target, speed, damage);
        return shitbullet;
    }
    CC_SAFE_DELETE(shitbullet);
    return nullptr;
}

void ShitBullet::initOptions(Monster* target, float speed, int damage) {
    this->target = target;
    this->speed = speed;
    this->damage = damage;
    this->moveToTarget();
}

void ShitBullet::moveToTarget() {
    if (!target || target->dead || target->getHitPoints() <= 0) {
        this->removeFromParent();
        return;
    }

    // 计算移动到目标的时间
    float distance = this->getPosition().distance(target->getPosition());
    float duration = distance / speed;


    // 创建移动动作
    auto moveAction = MoveTo::create(duration, target->getPosition());
    auto checkTargetValid = CallFunc::create([this]() {
        if (!target || target->getHitPoints() <= 0) {
            this->stopAllActions();
            this->removeFromParent();
        }
        });
    auto removeSelf = RemoveSelf::create();
    auto damageCallback = CallFunc::create([this]() {
        if (target && target->getHitPoints() > 0) {
            target->takeHalfspeed();
            target->beSloweddown();
            target->getAttacked(damage);
        }
        });


    // 运行动作序列
    auto sequence = Sequence::create(moveAction, checkTargetValid, damageCallback, removeSelf, nullptr);
    this->runAction(sequence);
}

void ShitBullet::targetDied() {
    target = nullptr; // 将目标设置为 nullptr
    // 或者采取其他适当的行动
}