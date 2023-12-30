#include "Global.h"
using namespace cocos2d;
using namespace cocos2d::ui;
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
        // 创建萝卜
        setupCarrot(Vec2::ZERO);

        // 创建血量底图精灵
        auto healthBackground = cocos2d::Sprite::create("myCarrot/Hp.png");
        healthBackground->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 60));
        this->addChild(healthBackground);

        // 创建血量标签
        healthLabel = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 24);
        healthLabel->setPosition(healthBackground->getContentSize().width / 2 + 10, healthBackground->getContentSize().height / 2);
        healthLabel->setString(std::to_string(health));
        healthBackground->addChild(healthLabel);

        // 萝卜摇摆动作
        setupSwingAction();
        });
    auto sequence = Sequence::create(delay, createCarrot, nullptr);
    runAction(sequence);

    return true;
}

void Carrot::setupCarrot(const Vec2& position) {
    aCarrot = Sprite::create("myCarrot/HP_MAX.PNG");
    aCarrot->setPosition(position.x + 10, position.y + 10);
    this->addChild(aCarrot);
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

    // 更新血量
    healthLabel->setString(std::to_string(health));
    updateAppearance();
}

void Carrot::updateAppearance() {
    if (health  == 9) {
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