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
    attackRange_ = Sprite::create("GameScene/Tower/AttackRange.PNG");
    attackRange_->setPosition(this->getPosition());
    this->getParent()->addChild(attackRange_);

}
void Tower::showUpgradeAndRemoveButtons() {
    // 创建升级按钮
    upgradeButton = cocos2d::ui::Button::create("GameScene/Tower/Btn_CanUpLevel.png");
    upgradeButton->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 85)); // 设置位置
    upgradeButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->upgrade();
        }
        });
    this->getParent()->addChild(upgradeButton);

    // 创建移除按钮
    removeButton = cocos2d::ui::Button::create("GameScene/Tower/Btn_SellTower.png");
    removeButton->setPosition(Vec2(this->getPosition().x, this->getPosition().y - 85)); // 设置位置
    removeButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->remove();
        }
        });
    this->getParent()->addChild(removeButton);

    // 添加一个全局触摸监听器
    auto globalListener = EventListenerTouchOneByOne::create();
    globalListener->setSwallowTouches(false); // 不吞噬触摸事件
    globalListener->onTouchBegan = [this](Touch* touch, Event* event) {
        Vec2 touchLocation = touch->getLocation();

        // 检测触摸点是否在炮台、升级按钮或移除按钮上
        if (!this->getBoundingBox().containsPoint(touchLocation) &&
            !this->upgradeButton->getBoundingBox().containsPoint(touchLocation) &&
            !this->removeButton->getBoundingBox().containsPoint(touchLocation)) {
            // 点击在炮台和按钮之外，隐藏攻击范围和按钮
            this->hideAttackRangeAndButtons();
            return true;
        }
        return false; // 允许事件继续传递
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(globalListener, this);
}

void Tower::hideAttackRangeAndButtons() {
    // 隐藏攻击范围指示
    if (attackRange) attackRange_->setVisible(false);

    // 隐藏升级和移除按钮
    if (upgradeButton) upgradeButton->setVisible(false);
    if (removeButton) removeButton->setVisible(false);
}