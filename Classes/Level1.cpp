#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <string.h>
#include "ui/CocosGUI.h"
#include "SelectScene.h"
#include "Level1.h"
#include "Monster.h"
#include <vector>
using namespace cocos2d;
using namespace cocos2d::ui;

USING_NS_CC;

Scene* Level1Scene::createScene()
{
    return Level1Scene::create();
}

bool Level1Scene::init()
{
    /* 初始化场景 */
    if (!Scene::init())
    {
        return false;
    }

    /* 获取屏幕大小 */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* 设置背景 */
    auto bg = Sprite::create("Level_1/Level1_bg.png");
    bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bg);

    /* 设置游戏画面 */
    this->addChild(GameScene::create());

    /* 打印放置炮台的位置 */
    auto gamemap = GameMap::create();
    this->addChild(gamemap);


    // 初始化路径和波次
    currentWave = 0;
    getPath(gamemap);

    // 开始第一波
    this->schedule(CC_SCHEDULE_SELECTOR(Level1Scene::startNextWave), 3.0f);


    return true;
}


void Level1Scene::getPath(GameMap* gamemap)
{
    // 计算路径的像素坐标
    for (const auto& grid : gamemap->path)
    {
        path.push_back(gamemap->gridToPixel(grid.x, grid.y));
    }
}

void Level1Scene::startNextWave(float dt) {
    if (currentWave >= totalWaves) {
        // 所有波次完成，游戏结束
        unschedule(CC_SCHEDULE_SELECTOR(Level1Scene::startNextWave));
        endGame();
        return;
    }

    // 开始下一波怪物的生成
    spawnMonsters(currentWave);

    // 准备下一波
    currentWave++;
}

void Level1Scene::spawnMonsters(int waveIndex) {
    // 根据波次决定生成怪物的类型和数量
    int monsterType = (waveIndex % 3) + 1; // 举例：每波切换一种怪物类型
    int monsterCount = 5 + (waveIndex % 3); // 举例：每波怪物数量在5到7之间

    for (int i = 0; i < monsterCount; ++i) {
        // 创建怪物并设置位置到路径起点
        auto monster = Monster::createWithType(monsterType);
        monster->setPosition(path.front()); // 假设路径的第一个点是起点
        this->addChild(monster);

        // 设置怪物的移动路径
        monster->moveOnPath(path);

        // 设置怪物间的出现时间间隔
        this->scheduleOnce([this, monster](float dt) {
            monster->setVisible(true);
            monster->moveOnPath(this->path);
            }, i * 1.0f, "spawn_monster_" + std::to_string(i)); // 每隔0.5秒出现一只怪物
    }
}

void Level1Scene::endGame() {
    // 处理游戏结束逻辑
    cocos2d::log("Game Over!");
}