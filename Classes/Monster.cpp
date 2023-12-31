#include<Monster.h>
#include<Global.h>
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
USING_NS_CC;

Monster* Monster::createWithType(int monsterType) {
    int hitPoints = 100; // 默认生命值，根据怪物类型可以不同
    // 根据怪物类型设置不同的生命值
    switch (monsterType) {
        case 1:
            hitPoints = 150;
            break;
        case 2:
            hitPoints = 200;
            break;
        case 3:
            hitPoints = 300;
            break;
        default:
            break;
    }

    Monster* monster = new (std::nothrow) Monster(monsterType, hitPoints);
    if (monster && monster->init()) {
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return nullptr;
}

Monster::Monster(int monsterType, int hitPoints)
    : _monsterType(monsterType), _hitPoints(hitPoints) {
}

bool Monster::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 根据类型初始化怪物的外观
    std::string filename = "Monster/monster" + std::to_string(_monsterType) + ".png";
    this->initWithFile(filename);

    // 创建显示生命值的标签
    //_hpLabel = Label::createWithSystemFont(std::to_string(_hitPoints), "Arial", 12);
    //_hpLabel->setPosition(Vec2(this->getContentSize() / 2));
    //this->addChild(_hpLabel);

    return true;
}

void Monster::moveOnPath(const std::vector<cocos2d::Vec2>& path) {
    if (path.empty()) return;

    // 创建动作序列
    Vector<FiniteTimeAction*> actions;

    for (size_t i = 1; i < path.size(); ++i) {
        // 每段路径移动所需的时间，您可以根据怪物的速度进行调整
        float moveDuration = path[i].length() / speed;

        // 创建移动到下一个点的动作
        auto moveAction = MoveTo::create(moveDuration, path[i]);
        actions.pushBack(moveAction);
    }
    // 添加一个回调函数，当移动完成时调用
    auto callbackAction = cocos2d::CallFunc::create([this]() {

        if (this->_hitPoints > 0)
            globalCarrot->decreaseHealth();// 减少萝卜的血量
        removeFromMonstersArray(this);
        this->removeFromParent(); // 移除怪物
        // 还可以在这里添加其他代码，例如更新游戏状态
        });
    actions.pushBack(callbackAction);

    // 创建序列动作
    auto sequence = Sequence::create(actions);

    // 运行动作
    runAction(sequence);
}

void Monster::getAttacked(int damage) {
    //updateHPLabel();
    if (!isAlive) return; // 如果怪物已经死亡，直接返回

    _hitPoints -= damage;

    if (_hitPoints <= 0) {
        _hitPoints = 0;
        die();
    }
    else {
        showHitEffect();
    }
}

void Monster::showHitEffect() {
    // 实现被攻击的特效，如闪烁或红色叠加
}

void Monster::dropCoins() {
    // 掉落30金币
    goldCoin->earnGold(30);
}

/*
void Monster::updateHPLabel() {
    _hpLabel->setString(std::to_string(_hitPoints));
}
*/

void Monster::removeFromMonstersArray(Monster* monster)
{
    auto iter = std::find(monsters.begin(), monsters.end(), monster);
    if (iter != monsters.end())
    {
        monsters.erase(iter);
    }
}

void Monster::die() {
    // 爆炸特效
    auto explosion = cocos2d::Sprite::create("Monster/explosion.PNG");
    explosion->setPosition(this->getPosition());
    this->getParent()->addChild(explosion);

    // 设置一个动作来移除爆炸特效
    auto fadeOut = cocos2d::FadeOut::create(0.5f); // 持续时间可以根据需要调整
    auto removeExplosion = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(fadeOut, removeExplosion, nullptr);
    explosion->runAction(sequence);

    dropCoins();
    removeFromMonstersArray(this);
    this->setVisible(false);
    //this->removeFromParent();
}