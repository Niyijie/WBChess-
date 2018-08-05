#include"GameScene.h"

void GameScene::Regret(Ref *sender)
{
    if(playerSide.size()>=1&&(PVPgameStart==true||PVCgameStart==true))
    {
        //判断是人机或者人人
        int modes = 0;
        if(PVCgameStart == true)
            modes = 1;
        else
            modes = 0;
        //如果是人机则一次性倒退两步前到状态
        for(int mode=0;mode<=modes;mode++)
        {
            for(auto s:chessArray)
            {
                if(s->getTag()>=0)
                {
                    this->removeChild(s);
                }
            }
            chessArray.clear();
            //将悔棋栈上的棋子添加进来
            for(int i=0;i<64;i++)
            {
                if(RegretChess[i].size()>0)
                {
                    RegretChess[i].popBack();
                   // if(PVCgameStart==true)
                     //   RegretChess[i].popBack();
                    if(RegretChess[i].size()>0)
                    {
                        auto spr = RegretChess[i].back();
                        chessArray.pushBack(spr);
                        this->addChild(spr,1);
                    }
                }
            }
            //将棋盘状态到上一步
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    location[i][j].pop_back();
                    //if(PVCgameStart == true)
                      //   location[i][j].pop_back();
                    chessboard[i][j]=location[i][j].back();
                }
            }
            side = playerSide.back();
            playerSide.pop_back();
            FindSetPoint(side);
            
            //display who to set
            if(side==white)
            {
                WhitePlayer->setVisible(true);
                BlackPlayer->setVisible(false);
            }
            else
            {
                WhitePlayer->setVisible(false);
                BlackPlayer->setVisible(true);
            }
        }
    }
    
    DisplayScore();
}

void GameScene::PvPGame(Ref *sender)
{
    if(PVPgameStart==true)
    {
        CCLOG("Game already started!");
        return;
    }
    PVPgameStart = true;
    PVCgameStart = false;
    InitchessBoard();
}

void GameScene::PvCGame(Ref *sender)
{
    if(PVCgameStart==true)
    {
        CCLOG("Game already started!");
        return;
    }
    PVCgameStart = true;
    PVPgameStart = false;
    InitchessBoard();
    return;
}

void GameScene::ReStartGame(Ref *sender)
{
    if(PVPgameStart==true)
    {
        PVPgameStart = true;
        PVCgameStart = false;
        InitchessBoard();
    }
    if(PVCgameStart == true)
    {
        PVPgameStart = false;
        PVCgameStart = true;
        InitchessBoard();
    }
    return;
}

void GameScene::Peace(Ref *sender)
{
    CCLOG("Peace");
}

void GameScene::GiveUp(Ref *sender)
{
    int groudwidth,groudheight;
    groudwidth=Director::getInstance()->getWinSize().width;
    groudheight=Director::getInstance()->getWinSize().height;
    
    PVCgameStart = false;
    PVPgameStart = false;
    
    if(side==white)
    {
        auto WhiteGiveUp = Sprite::create("res/css/WhiteGiveUp.png");
        WhiteGiveUp->setPosition(Point(groudwidth/2,groudheight/2));
        this->addChild(WhiteGiveUp,1);
    }
    if(side==black)
    {
        auto BlackGiveUp = Sprite::create("res/css/BlackGiveUp.png");
        BlackGiveUp->setPosition(Point(groudwidth/2,groudheight/2));
        this->addChild(BlackGiveUp,1);
    }
}



bool GameScene::onTouchBegan(Touch *touch,Event *unused_event)
{
    Point point = touch->getLocation();
    CCLOG("x:%f y:%f",point.x,point.y);
    return true;
}

