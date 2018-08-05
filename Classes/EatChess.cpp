#include"GameScene.h"

//0:right 1:left 2:down 3:up 4:right down 5:left down 6:right up 7:left up

void GameScene::changeChess(int xx,int yy,int cside)
{
    int pxx = int(xx*BlockWidth);
    int pyy = int(yy*BlockWidth);
    for(auto s:chessArray)
    {
        if(s->getTag()==(xx+yy*8))
        {
            this->removeChild(s);
            chessArray.eraseObject(s);
            chessboard[xx][yy]=side;
        }
    }
    auto WBChess = Sprite::create();
    if(cside==white)
        WBChess = Sprite::create("res/css/wb1.png");
    if(cside==black)
        WBChess = Sprite::create("res/css/wb5.png");
    WBChess->setPosition(Point((pxx+138.5),(pyy+73.5)));
    WBChess->setScale(1.1, 1.1);
    WBChess->setTag(xx+yy*8);
    chessArray.pushBack(WBChess);
    this->addChild(WBChess,1);
    
    auto animation = Animation::create();
    for(int i=5;i>=1;i--)
    {
        char nameSize[28]={0};
        sprintf(nameSize, "res/css/wb%d.png",i);
        CCLOG("%s",nameSize);
        animation->addSpriteFrameWithFile(nameSize);
    }
    animation->setDelayPerUnit(0.5f/5);
    animation->setRestoreOriginalFrame(true);
    auto action_1 = Animate::create(animation);
    if(side==black)
        action_1 = action_1->reverse();
    WBChess->runAction(action_1);
}

void GameScene::EatChess(int x,int y)
{
    int px,py;
    int locationX= x+y*8;
    int otherside = turnside-side;
    
    //seach left
    if(x>=2)
    {
        px = x-1;
        while(chessboard[px][y]==otherside&&flag[locationX][1]==true)
        {
            if(chessboard[px][y]==otherside)
            {
                changeChess(px, y, side);
            }
            px=px-1;
         }
    }
    //seach right
    if(x<=5)
    {
        px = x+1;
        while(chessboard[px][y]==otherside&&flag[locationX][0]==true)
        {
            if(chessboard[px][y]==otherside)
            {
                changeChess(px, y, side);
            }
            px=px+1;
        }
    }
    //seach up
    if(y<=5)
    {
        py = y+1;
        while(chessboard[x][py]==otherside&&flag[locationX][3]==true)
        {
            if(chessboard[x][py]==otherside)
            {
                changeChess(x, py, side);
            }
            py=py+1;
        }
    }
        //seach down
        if(y>=2)
        {
            py = y-1;
            while(chessboard[x][py]==otherside&&flag[locationX][2]==true)
            {
                if(chessboard[x][py]==otherside)
                {
                    changeChess(x, py, side);
                }
                py=py-1;
            }
        }
        //search left up
        if(x>=2&&y<=5)
        {
            px = x-1;
            py = y+1;
            while(chessboard[px][py]==otherside&&flag[locationX][7]==true)
            {
                if(chessboard[px][py]==otherside)
                {
                    changeChess(px, py, side);
                }
                px=px-1;
                py=py+1;
            }
        }
    //search left down
    if(x>=2&&y>=2)
    {
        px = x-1;
        py = y-1;
        while(chessboard[px][py]==otherside&&flag[locationX][5]==true)
        {
            if(chessboard[px][py]==otherside)
            {
                changeChess(px, py, side);
            }
            px=px-1;
            py=py-1;
        }
    }
    //search right up
    if(x<=5&&y<=5)
    {
        px = x+1;
        py = y+1;
        while(chessboard[px][py]==otherside&&flag[locationX][6]==true)
        {
            if(chessboard[px][py]==otherside)
            {
                changeChess(px, py, side);
            }
            px=px+1;
            py=py+1;
        }
    }
    //search right down
    if(x<=5&&y>=2)
    {
        px = x+1;
        py = y-1;
        while(chessboard[px][py]==otherside&&flag[locationX][4]==true)
        {
            if(chessboard[px][py]==otherside)
            {
                changeChess(px, py, side);
            }
            px=px+1;
            py=py-1;
        }
    }
}
