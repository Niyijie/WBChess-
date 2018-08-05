#include"GameScene.h"

void GameScene::DjugeIfEnd()
{
    if(FindSetPoint(side)==false)
    {
        GameEnd[side-1]=true;
        side = turnside - side;
        if(FindSetPoint(side)==false)
        {
            GameEnd[side-1]=true;
            GameEvent();
        }
        
        //如果玩家没位置下 AI继续下
        if(PVCgameStart == true)
        {
            JudgeChessBoard(1.0);
            DisplayScore();
            if(FindSetPoint(side)==false)
            {
                GameEnd[side-1]=true;
                side = turnside - side;
                if(FindSetPoint(side)==false)
                {
                    GameEnd[side-1]=true;
                    GameEvent();
                }
            }
        }
        GameEvent();
        //FindSetPoint(side);
        if(side == white)
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

void GameScene::AddChess (Touch *touch,Event *unused_event)
{
    if(PVCgameStart==true&&side == black)
    {
        return;
    }
    //(124.6,58.6) width 218 height 218
    Rect rect = Rect(124.6,58.6, 218, 218);
    auto WChessman = Sprite::create();
    Point place =touch->getLocation();
    
    if(rect.containsPoint(place)&&(PVPgameStart==true||PVCgameStart==true))
    {
        int xx = place.x-124.6;
        int yy = place.y-58.6;
        int bx = int(xx/BlockWidth);
        int by = int(yy/BlockWidth);
        
        //check whether can set chess
        for(int i=0;i<8;i++)
        {
            if(flag[bx+by*8][i]==true)
                break;
            else if(i==7)
            {
                return;
            }
        }
        
        //if can be set
        if(chessboard[bx][by] == empty)
        {
            SimpleAudioEngine::getInstance()->playEffect("res/bgm/setchess.mp3");
            GameEnd[side-1]=false;
            if(side==white)
                WChessman = Sprite::create("res/css/wb1.png");
            if(side==black)
                WChessman = Sprite::create("res/css/wb5.png");
            chessboard[bx][by]  = side;
            WChessman->setScale(1.1,1.1);
            int px = int(int(bx*BlockWidth));
            int py = int(int(by*BlockWidth));
            
            WChessman->setPosition(Point((px+138.5),(py+73.5)));
            WChessman->setTag(bx+8*by);
            chessArray.pushBack(WChessman);
            this->addChild(WChessman,1);
        }
        EatChess(int(bx), int(by));
        playerSide.push_back(side);//side information
        side = turnside - side;
        DisplayScore();
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
    else
        return;
    
    //store information
    for(auto s:chessArray)
    {
        if(s->getTag()>=0)
            RegretChess[s->getTag()].pushBack(s);
    }
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            location[i][j].push_back(chessboard[i][j]);
    
    
    if(PVCgameStart==true&&FindSetPoint(side)==true)
    {
        scheduleOnce(schedule_selector(GameScene::JudgeChessBoard), 0.6f);
        //JudgeChessBoard(1.0);
        DisplayScore();
        return;
    }
    DjugeIfEnd();
}
