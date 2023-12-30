#ifndef __GOLD_COIN_H__
#define __GOLD_COIN_H__

#include "cocos2d.h"

USING_NS_CC;

class GoldCoin : public Node
{
public:

    int m_value;
    Label* m_label;

    virtual bool init() override;
  
    //更新金币
    void updateGoldValue(int goldValue);


    // 击败怪物获得金币
    void earnGold(int amount);
    
    // 购买炮塔消耗金币
    bool purchaseTower(int cost);
    CREATE_FUNC(GoldCoin);

private:
    void updateGoldLabel();
};
#endif