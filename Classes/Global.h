#ifndef GLOBAL_H
#define GLOBAL_H

#include "ui/CocosGUI.h"
#include "Carrot.h"
#include "Monster.h"
#include "GoldCoin.h"
#include "Fan.h"
#include "Bottle.h"
#include "Shit.h"


extern Carrot* globalCarrot; // 全局变量的声明
extern GoldCoin* goldCoin; // 金币系统

extern std::vector<Monster*> monsters; // 用来存储怪物的数组

// 储存建造的炮台
extern std::vector<Fan*> fans;
extern std::vector<Bottle*> bottles;
extern std::vector<Shit*> shits;

// 记录是否完成关卡
extern bool isLevel1Finish;
extern bool isLevel2Finish;

#endif