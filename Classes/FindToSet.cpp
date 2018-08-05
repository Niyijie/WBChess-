#include"GameScene.h"

//find where can be setted
bool GameScene::FindSetPoint(int myside)
{
    //remove all elements
    for(auto box:fourConerBox)
    {
        auto spr = Sprite::create();
        spr = box;
        this->removeChild(spr);
    }
    
    //init flag
    for(int i=0;i<64;i++)
        for(int j=0;j<8;j++)
            flag[i][j]=false;
    
    //find location
    int px,py,search=0;
    int otherside = turnside - myside;
    for(int y=0;y<8;y++)
    {
        for(int x=0;x<8;x++)
        {
            if(chessboard[x][y]==myside)
            {
                //search left forward
                if(x>=2)
                {
                    px = x-1;
                    while(chessboard[px][y]==otherside&&px>=1)
                    {
                        search = search + 1;
                        if(chessboard[px-1][y]==empty&&search>0)
                        {
                            auto canSet = Sprite::create("res/css/canset.png");
                            int pxx = int((px-1)*BlockWidth);
                            int pyy = int(y*BlockWidth);
                            canSet->setPosition(Point((pxx+138.5),(pyy+73.5)));
                            this->addChild(canSet,1);
                            fourConerBox.pushBack(canSet);
                            flag[px-1+8*y][0]=true;
                            break;
                        }
                        px=px-1;
                    }
                    search = 0;
                }
            
                //search right forward
                if(x<=5)
                {
                    px = x+1;
                    while(chessboard[px][y]==otherside&&px<=6)
                    {
                        search = search+1;
                        if(chessboard[px+1][y]==empty&&search>0)
                        {
                            auto canSet = Sprite::create("res/css/canset.png");
                            int pxx = int((px+1)*BlockWidth);
                            int pyy = int(y*BlockWidth);
                            canSet->setPosition(Point((pxx+138.5),(pyy+73.5)));
                            this->addChild(canSet,1);
                            fourConerBox.pushBack(canSet);
                            flag[px+1+8*y][1]=true;
                            break;
                        }
                        px = px+1;
                    }
                    search = 0;
                }
                //search up forward
                if(y<=5)
                {
                    py = y+1;
                    while(chessboard[x][py]==otherside&&py<=6)
                    {
                        search = search+1;
                        if(chessboard[x][py+1]==empty&&search>0)
                        {
                            auto canSet = Sprite::create("res/css/canset.png");
                            int pxx = int(x*BlockWidth);
                            int pyy = int((py+1)*BlockWidth);
                            canSet->setPosition(Point((pxx+138.5),(pyy+73.5)));
                            this->addChild(canSet,1);
                            fourConerBox.pushBack(canSet);
                            flag[x+(py+1)*8][2]=true;
                            break;
                        }
                        py = py+1;
                    }
                }
                //search down forward
                if(y>=2)
                {
                    py = y-1;
                    while(chessboard[x][py]==otherside&&py>=1)
                    {
                        search = search+1;
                        if(chessboard[x][py-1]==empty&&search>0)
                        {
                            auto canSet = Sprite::create("res/css/canset.png");
                            int pxx = int(x*BlockWidth);
                            int pyy = int((py-1)*BlockWidth);
                            canSet->setPosition(Point((pxx+138.5),(pyy+73.5)));
                            this->addChild(canSet,1);
                            fourConerBox.pushBack(canSet);
                            flag[x+(py-1)*8][3]=true;
                            break;
                        }
                        py = py-1;
                    }
                }
                //search left up forward
                if(x>=2&&y<=5)
                {
                    py = y+1;
                    px = x-1;
                    while(chessboard[px][py]==otherside&&px>=1&&py<=6)
                    {
                        search = search+1;
                        if(chessboard[px-1][py+1]==empty&&search>0)
                        {
                            auto canSet = Sprite::create("res/css/canset.png");
                            int pxx = int((px-1)*BlockWidth);
                            int pyy = int((py+1)*BlockWidth);
                            canSet->setPosition(Point((pxx+138.5),(pyy+73.5)));
                            this->addChild(canSet,1);
                            fourConerBox.pushBack(canSet);
                            flag[px-1+8*(py+1)][4]=true;
                            break;
                        }
                        py = py+1;
                        px = px-1;
                    }
                }
                //search right up forward
                if(x<=5&&y<=5)
                {
                    py = y+1;
                    px = x+1;
                    while(chessboard[px][py]==otherside&&px<=6&&py<=6)
                    {
                        search = search+1;
                        if(chessboard[px+1][py+1]==empty&&search>0)
                        {
                            auto canSet = Sprite::create("res/css/canset.png");
                            int pxx = int((px+1)*BlockWidth);
                            int pyy = int((py+1)*BlockWidth);
                            canSet->setPosition(Point((pxx+138.5),(pyy+73.5)));
                            this->addChild(canSet,1);
                            fourConerBox.pushBack(canSet);
                             flag[px+1+(py+1)*8][5]=true;
                            break;
                        }
                        py = py+1;
                        px = px+1;
                    }
                }
                //search left down
                if(x>=2&&y>=2)
                {
                    py = y-1;
                    px = x-1;
                    while(chessboard[px][py]==otherside&&px>=1&&py>=1)
                    {
                        search = search+1;
                        if(chessboard[px-1][py-1]==empty&&search>0)
                        {
                            auto canSet = Sprite::create("res/css/canset.png");
                            int pxx = int((px-1)*BlockWidth);
                            int pyy = int((py-1)*BlockWidth);
                            canSet->setPosition(Point((pxx+138.5),(pyy+73.5)));
                            this->addChild(canSet,1);
                            fourConerBox.pushBack(canSet);
                             flag[px-1+(py-1)*8][6]=true;
                            break;
                        }
                        py = py-1;
                        px = px-1;
                    }
                }
                //search right down
                if(x<=5&&y>=2)
                {
                    py = y-1;
                    px = x+1;
                    while(chessboard[px][py]==otherside&&px<=6&&py>=1)
                    {
                        search = search+1;
                        if(chessboard[px+1][py-1]==empty&&search>0)
                        {
                            auto canSet = Sprite::create("res/css/canset.png");
                            int pxx = int((px+1)*BlockWidth);
                            int pyy = int((py-1)*BlockWidth);
                            //CCLOG("x:%d y:%d",px+1,py-1);
                            canSet->setPosition(Point((pxx+138.5),(pyy+73.5)));
                            this->addChild(canSet,1);
                            fourConerBox.pushBack(canSet);
                            flag[px+1+(py-1)*8][7]=true;
                            break;
                        }
                        py = py-1;
                        px = px+1;
                    }
                }
            }
        }
    }
    for(int i=0;i<64;i++)
        for(int j=0;j<8;j++)
        {
            if(flag[i][j]==true)
            {
                return true;
            }
        }
    return false;
}
