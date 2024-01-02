#include "Fan.h"
#include "FanBullet.h"
#include "Monster.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Global.h"
USING_NS_CC;


Fan* Fan::create(const Vec2& position) {
    Fan* fan = new (std::nothrow) Fan();
    if (fan && fan->init()) { // 使用您的炮塔图片
        auto base = Sprite::create("Tower/Fan/ID4_0.PNG");
        base->setPosition(fan->getPosition().x + 20, fan->getPosition().y + 10);
        fan->addChild(base, -1);

        fan->setTexture("Tower/Fan/Level1.PNG"); // 初始外观
        fan->autorelease();
        fan->setPosition(position.x + 5, position.y + 10);

        fan->attackDamage = 100;    // 设置攻击伤害
        fan->attackRange = 200.0f;  // 设置攻击范围
        fan->attackSpeed = 1000.0f; // 设置攻击速度
        fan->timeSinceLastAttack = 0;
        fans.push_back(fan);

        return fan;
    }
    CC_SAFE_DELETE(fan);
    return nullptr;
}
void Fan::upgrade()
{
    if (level < 3 && goldCoin->m_value > 120) {
        level++;

        // 更新外观
        std::string textureName = "Tower/Fan/Level" + std::to_string(level) + ".PNG";
        setTexture(textureName);

        // 战力提升
        attackSpeed += 400;
        attackDamage += 150;
        attackRange += 100;

        // 扣钱
        goldCoin->earnGold(-120);
    }
}

void Fan::remove()
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
    /****1/2更新 指针向量置零*****************************/
    for (auto iter = fans.begin(); iter != fans.end();)
    {
        if (this == *iter)
        {
            iter = fans.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    this->hideAttackRangeAndButtons();
    this->removeAllChildren();
    this->removeFromParentAndCleanup(true);
}


void Fan::update(float dt, std::vector<Monster*> monsters) {
    timeSinceLastAttack += dt;
    if (timeSinceLastAttack >= 1) {
        checkForMonstersInRange(monsters);
        if (!monstersInRange.empty()) {
            attack(monstersInRange.front()); // 攻击第一个怪物
            timeSinceLastAttack = 0;
        }
    }
}

bool Fan::isMonsterInRange(Monster* monster) {
    return (getPosition().distance(monster->getPosition()) <= attackRange);
}

void Fan::checkForMonstersInRange(std::vector<Monster*> monsters) {
    // 假设 monsters 是场景中所有怪物的列表
    monstersInRange.clear();
    if (monsters.size())
    {
        for (Monster*& monster : monsters) {
            if (isMonsterInRange(monster)) {
                monstersInRange.push_back(monster);
            }
        }
    }
}

void Fan::attack(Monster* target) {
    auto fanbullet = FanBullet::createWithTarget(target, "Resource/Tower/Fan/ID1_0.PNG", attackSpeed, attackDamage);
    fanbullet->setPosition(getPosition());
    this->getParent()->addChild(fanbullet);
}