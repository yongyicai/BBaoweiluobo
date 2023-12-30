#include "Global.h"

USING_NS_CC;

bool Carrot::init() {
    if (!Node::init()) {
        return false;
    }

    health = 10; // 假设萝卜最大血量为10
    healthTextures = { "myCarrot/HP_MAX.PNG","myCarrot/HP_9.PNG","myCarrot/HP_7-8.PNG","myCarrot/HP_5-6.PNG","myCarrot/HP_4.PNG","myCarrot/HP_3.PNG","myCarrot/HP_2.PNG","myCarrot/HP_1.PNG" };

    // 延迟3秒后创建萝卜
    auto delay = DelayTime::create(3.0f);
    auto createCarrot = CallFunc::create([this]() {
        setupCarrot(Vec2::ZERO);
        // setupBloodBar();
        setupSwingAction();
        updateAppearance(); // 根据初始血量更新外观
        });
    auto sequence = Sequence::create(delay, createCarrot, nullptr);
    runAction(sequence);

    return true;
}
void Carrot::setupCarrot(const Vec2& position) {
    aCarrot = Sprite::create("myCarrot/HP_MAX.PNG");
    aCarrot->setPosition(position);
    this->addChild(aCarrot);
}

void Carrot::setupBloodBar() {
    bloodBar = Sprite::create("myCarrot/bloodBackground.png");
    bloodBar->setPosition(Vec2(aCarrot->getPosition().x,
        aCarrot->getPosition().y + aCarrot->getContentSize().height / 2 + 10));
    this->addChild(bloodBar);
}

void Carrot::setupSwingAction() {
    auto swingAction = Sequence::create(
        RotateBy::create(0.3f, 30.0f),
        RotateBy::create(0.3f, -30.0f),
        RotateBy::create(0.3f, -30.0f),
        RotateBy::create(0.3f, 30.0f),
        nullptr
    );

    auto standAction = RotateTo::create(0.3f, 0.0f);
    auto rotateAction = RepeatForever::create(
        Sequence::create(
            swingAction,
            DelayTime::create(6.0f),
            standAction,
            nullptr
        )
    );

    aCarrot->runAction(rotateAction);
}

void Carrot::decreaseHealth() {
    health--;
    if (health < 0) health = 0; // 防止血量变成负数

    updateAppearance();

    if (health <= 0) {
        globalCarrot = nullptr;
    }
}

void Carrot::updateAppearance() {
    if (health == 9) {
        aCarrot->setTexture(healthTextures[1]);
    }
    else if (health == 8 || health == 7) {
        aCarrot->setTexture(healthTextures[2]);
    }
    else if (health == 6 || health == 5) {
        aCarrot->setTexture(healthTextures[3]);
    }
    else if (health == 4) {
        aCarrot->setTexture(healthTextures[4]);
    }
    else if (health == 3) {
        aCarrot->setTexture(healthTextures[5]);
    }
    else if (health == 2) {
        aCarrot->setTexture(healthTextures[6]);
    }
    else if (health == 1) {
        aCarrot->setTexture(healthTextures[7]);
    }

}