#ifndef __LEVEL1_SCENE_H__
#define __LEVEL1_SCENE_H__
#include "Global.h"
#include "cocos2d.h"
#include "TowerBottle.h"
using namespace cocos2d;
using namespace std;

class Level1Scene: public Scene
{
public:
    struct Grid {
        int x, y;
    };
    static Scene* createScene();

    virtual bool init();
    void click(GameMap* gamemap);
    void startNextWave(float dt);
    void spawnMonsters(int waveIndex);
    void endGame();
    void update(float dt) override;
    int currentWave;
    const int totalWaves = 15;
    // 存储路径
    vector<Vec2> path;

    void getPath(GameMap* gamemap);

     // 用来存储怪物的数组
    
    CREATE_FUNC(Level1Scene);
};
#endif
