#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class GameScene : public Scene
{
private:
    void removePickTower(float dt) {
        this->removeChildByName("PickTower");
    }
    LayerColor* maskLayer;      // 蒙版,添加在类内是为了屏蔽暂停时对地图的操作
    bool isGamePaused = false;  // 跟踪暂停状态
   
public:
    static Scene* createScene();

    virtual bool init()override;

    void options();

    void updateWaveDisplay(); // 更新波数显示的函数

    void createCountdownAnimation();

    CREATE_FUNC(GameScene);
};

class GameMap : public Layer
{
public:
    // 初始化方法
    virtual bool init();

    // 关卡
    int level;

    // 定义网格大小 12X8
    static const int GRID_WIDTH = 12;
    static const int GRID_HEIGHT = 8;

    // 格子结构
    struct Grid {
        int x, y;
    };

    // 创建格子
    vector<vector<bool>> gridMap;

    // 存储路径
    vector<Grid> path;

    // 转换函数，将网格坐标转换为像素坐标
    Vec2 gridToPixel(int x, int y);

    // 逆转换函数，将像素坐标转换为网格坐标
    Grid pixelToGrid(float x, float y);

    // 方法来初始化网格和路径
    void setupGrid();
    void addPathPoint(Grid g);

    // 打印放置炮台的位置
    void printStartSprite();

    CREATE_FUNC(GameMap);
};

#endif