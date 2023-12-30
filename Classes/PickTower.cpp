#include "PickTower.h"
#include "BottleBullet.h"
#include "Level1.h"
using namespace cocos2d;

USING_NS_CC;

bool PickTower::init()
{
    if (!Node::init()) {
        return false;
    }

    // 初始化 tower1 和 tower2
    tower1 = Sprite::create("Tower/Bottle/CanClick1.PNG", Rect(0, 0, 78, 82));
    if (tower1 != nullptr) {
        tower1->setVisible(false);
        this->addChild(tower1);
    }

    tower2 = Sprite::create("Tower/Fan/CanClick1.PNG", Rect(0, 82, 78, 78));
    if (tower2 != nullptr) {
        tower2->setVisible(false);
        this->addChild(tower2);
    }

    // 初始化网格内的图像并存储在容器中
    for (const auto& pos : initPositions) {
        auto sprite = Sprite::create("GameScene/click.png");
        sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
        sprite->setPosition(pos);
        sprite->setVisible(false); // 初始设置为不可见
        addChild(sprite);
        gridSprites.push_back(sprite);
    }

    // 鼠标监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        Vec2 location = touch->getLocation();

        for (auto& gridSprite : gridSprites) {
            if (gridSprite->getBoundingBox().containsPoint(location)) {
                // 显示点击的网格图像和对应的 tower1, tower2
                gridSprite->setVisible(true);
                this->tower1->setPosition(gridSprite->getPosition().x, gridSprite->getPosition().y + 72);
                this->tower2->setPosition(gridSprite->getPosition().x - 72, gridSprite->getPosition().y + 72);
                this->tower1->setVisible(true);
                this->tower2->setVisible(true);
            }
            else {
                // 隐藏其他网格图像及其对应的 tower1, tower2
                gridSprite->setVisible(false);
            }
        }

        return true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
