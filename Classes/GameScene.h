#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__
#define BoaredSize 8
#define white 1
#define black 2
#define cansetchess -1

#define empty 0
#define turnside 3
#define BlockWidth 27.25
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

class GameScene: public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(GameScene);
    virtual bool onTouchBegan(Touch *touch,Event *unused_event);
    virtual void AddChess(Touch *touch,Event *unused_event);
    bool FindSetPoint(int mysize);
    void InitchessBoard();
    void GameRestart();
    void Regret(Ref *sender);
    void GiveUp(Ref *sender);
    void Peace(Ref *sender);
    void PvCGame(Ref *sender);
    void PvPGame(Ref *sender);
    void ReStartGame(Ref *sender);
    void EatChess(int x,int y);
    void GameEvent();
    void DisplayScore();
    void JudgeChessBoard(float dt);
    void changeChess(int xx,int yy,int cside);
    void DjugeIfEnd();
    
    void FindLocation(bool cflag[64][8],int position[64][2]);
    bool FindSetlocation(int myside);
    void SimulateChange(int x,int y,int board[8][8],int _side);
    void Max(int location[2],int position[64][2]);
    void Replace(int from[8][8],int to[8][8]);
    
    int chessboard[BoaredSize][BoaredSize];
    int side;    //store player's color
    int WhiteChessNumber,BlackChessNumber;
    int AIscore;
    bool flag[64][8];//0:right 1:left 2:down 3:up 4:right down 5:left down 6:right up 7:left up
    bool GameEnd[2];
    bool PVPgameStart;
    bool PVCgameStart;
    
    const int ValueList[8][8]={
        {200,-60,10,10,10,10,-60,200},
        {-60,-80, 5, 5, 5, 5,-80,-60},
        {10, 5, 5, 1, 1, 5, 5, 10},
        {10, 5, 5, 1, 1, 5, 5, 10},
        {10, 5, 5, 1, 1, 5, 5, 10},
        {10, 5, 5, 1, 1, 5, 5, 10},
        {-60,-80, 5, 5, 5, 5,-80,-60},
        {200,-60,10,10,10,10,-60,200}
    };
    
    Sprite *WhitePlayer;
    Sprite *BlackPlayer;
    std::vector<int> location[8][8];
    std::vector<int> playerSide;
    Vector<Sprite*> fourConerBox;
    Vector<Sprite*> chessArray;
    Vector<Sprite*> RegretChess[64];   //store regret information
};

#endif // __HELLOWORLD_SCENE_H__


//{120,-60,10,10,10,10,-60,120},
//{-60,-80, 5, 5, 5, 5,-80,-60},
//{10, 5, 1, 1, 1, 1, 5, 10},
//{10, 5, 5, 1, 1, 1, 5, 10},
//{10, 5, 5, 1, 1, 1, 5, 10},
//{10, 5, 5, 1, 1, 1, 5, 10},
//{-60,-80, 5, 5, 5, 5,-80,-60},
//{120,-60,10,10,10,10,-60,120}  };

