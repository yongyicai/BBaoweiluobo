#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <string.h>
#include "ui/CocosGUI.h"
#include "SelectScene.h"
#include "Level1.h"
#include"Global.h"
#include <vector>
using namespace cocos2d;
using namespace cocos2d::ui;

USING_NS_CC;
std::vector<Monster*> monsters; 
Bottle* bottle = Bottle::create();


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
    auto bg = Sprite::create("Level_1/Level_1_1_bg.png");
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

    //globalCarrot = Carrot::create();
   // globalCarrot->setPosition(path[path.size() - 1]);
   // this->addChild(globalCarrot);

    // 点击事件
    Level1Scene::click(gamemap);


    // 开始第一波
    this->schedule(CC_SCHEDULE_SELECTOR(Level1Scene::startNextWave), 6.0f);

    
    //bottle->setPosition(this->getContentSize() / 2);
    //this->addChild(bottle);
    //this->scheduleUpdate();
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
void Level1Scene::click(GameMap* gamemap)
{
    for (int y = 0; y < gamemap->GRID_HEIGHT; ++y) {
        for (int x = 0; x < gamemap->GRID_WIDTH; ++x) {
            if (gamemap->gridMap[y][x]) {
                auto startSprite = ImageView::create("GameScene/click.png");
                // 修改位置计算方式，确保图片位置与点击位置一致
                startSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
                startSprite->setPosition(gamemap->gridToPixel(x, y));
                startSprite->setVisible(false);  // 将图片设置为不可见
                addChild(startSprite);
            }
        }
    }
    // 添加触摸事件监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 location = touch->getLocation();
        bool clickedOnImage = false;

        // 遍历所有子节点，查找包含点击位置的图片节点
        for (auto image : getChildren()) {
            if (auto sprite = dynamic_cast<ImageView*>(image)) {
                if (sprite->getBoundingBox().containsPoint(location)) {
                    sprite->setVisible(true);
                    clickedOnImage = true;
                }
                else {
                    sprite->setVisible(false);
                }
            }
        }
        // 如果点击位置没有图片且没有点击到其他非图片的区域，则不进行任何操作
        if (!clickedOnImage) {
            return false;
        }

        return true;
    };

    
    // 创建怪物列表（假设已实现）

    // 设置每帧调用更新
    this->scheduleUpdate();

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
    int monsterCount = 4 + (waveIndex % 3); // 举例：每波怪物数量在5到7之间

    for (int i = 0; i < monsterCount; ++i) {
        // 创建怪物并设置位置到路径起点
        auto monster = Monster::createWithType(monsterType);
        monster->setPosition(path.front()); // 假设路径的第一个点是起点
        this->addChild(monster);
        monster->setVisible(false);

        monsters.push_back(monster);

        // 设置怪物间的出现时间间隔
        this->scheduleOnce([this, monster](float dt) {
            monster->setVisible(true);
            monster->moveOnPath(this->path);
            }, i * 1.0f, "spawn_monster_" + std::to_string(i)); // 每隔0.5秒出现一只怪物
    }
}

void Level1Scene::endGame() {
    // 处理游戏结束逻辑
    globalCarrot = nullptr;
    log("Game Over!");
}

void Level1Scene::update(float dt) {
    // 更新 Bottle
    for (Monster* monster : monsters) {
         if (bottle->findTargetInAttackRange(monsters)) {
             bottle->attack(monster); // 如果怪物在范围内，进行攻击
         }
        
    }

    // 更新怪物列表（假设已实现）
}