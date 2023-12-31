#include "Shit.h"
#include "ShitBullet.h"
#include "Monster.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Global.h"

USING_NS_CC;

Shit* Shit::create(const Vec2& position) {
    Shit* shit = new (std::nothrow) Shit();
    if (shit && shit->initWithFile("Tower/Shit/Level1.PNG")) {
        shit->autorelease();
        shit->setPosition(position);

        shit->attackDamage = 50;     // 设置攻击伤害
        shit->attackRange = 200.0f;  // 设置攻击范围
        shit->attackSpeed = 1000.0f; // 设置攻击速度
        shit->timeSinceLastAttack = 0;
        shits.push_back(shit);
        return shit;
    }
    CC_SAFE_DELETE(shit);
    return nullptr;
}

void Shit::upgrade()
{
    if (level < 3 || goldCoin->m_value > 120) {
        level++;

        // 更新外观
        std::string textureName = "Tower/Shit/Level" + std::to_string(level) + ".PNG";
        setTexture(textureName);

        // 战力提升
        attackSpeed += 400;
        attackDamage += 50;
        attackRange += 100;

        // 扣钱
        goldCoin->earnGold(-120);
    }
}

void Shit::remove()
{
    if (level == 1)
        goldCoin->earnGold(80);
    else if (level == 2)
        goldCoin->earnGold(120);
    else
        goldCoin->earnGold(180);

    // 删除特效
    auto Delete = cocos2d::Sprite::create("Tower/Tower_Delete.PNG");
    Delete->setPosition(this->getPosition());
    this->getParent()->addChild(Delete);

    // 设置一个动作来移除删除特效
    auto fadeOut = cocos2d::FadeOut::create(0.5f); // 持续时间可以根据需要调整
    auto removeExplosion = cocos2d::RemoveSelf::create();
    auto sequence = cocos2d::Sequence::create(fadeOut, removeExplosion, nullptr);
    Delete->runAction(sequence);

    this->hideAttackRangeAndButtons();
    this->removeAllChildren();
    this->removeFromParentAndCleanup(true);
}

void Shit::update(float dt, std::vector<Monster*> monsters) {
    timeSinceLastAttack += dt;
    if (timeSinceLastAttack >= 1) {
        checkForMonstersInRange(monsters);
        if (!monstersInRange.empty()) {
            attack(monstersInRange.front()); // 攻击第一个怪物
            timeSinceLastAttack = 0;
        }
    }
}

bool Shit::isMonsterInRange(Monster* monster) {
    return (getPosition().distance(monster->getPosition()) <= attackRange);
}

void Shit::checkForMonstersInRange(std::vector<Monster*> monsters) {
    // 假设 monsters 是场景中所有怪物的列表
    monstersInRange.clear();
    if (monsters.size())
    {
        for (Monster* monster : monsters) {
            if (isMonsterInRange(monster)) {
                monstersInRange.push_back(monster);
            }
        }
    }
}

void Shit::attack(Monster* target) {
    auto shitbullet = ShitBullet::createWithTarget(target, "Tower/Shit/ID2_43.PNG", attackSpeed, attackDamage);
    shitbullet->setPosition(getPosition());
    this->getParent()->addChild(shitbullet);
}