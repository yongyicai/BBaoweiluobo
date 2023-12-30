#include"cocos2d.h"
#include "GoldCoin.h"

USING_NS_CC;

bool GoldCoin::init()
{
    if (!Node::init())
    {
        return false;
    }

    m_value = 0;

    // 创建用于显示金币数量的标签
    m_label = Label::createWithTTF("", "fonts/arial.ttf", 24);
    m_label->setPosition(Vec2(120, 607));
    addChild(m_label);

    return true;
}

//击败怪物或卖出物品
void GoldCoin::earnGold(int amount)
{
    m_value += amount;
    updateGoldLabel();
}
//买炮
bool GoldCoin::purchaseTower(int cost)
{
    if (m_value >= cost)
    {
        m_value -= cost;
        updateGoldLabel();
        return true;
    }

    return false;
}
void GoldCoin::updateGoldValue(int goldValue)
{
    m_value = goldValue;
    this->m_label->setString(std::to_string(m_value));
}

void GoldCoin::updateGoldLabel()
{
    this->m_label->setString(std::to_string(m_value));
}