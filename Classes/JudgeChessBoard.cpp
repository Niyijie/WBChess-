#include"GameScene.h"

void GameScene::FindLocation(bool cflag[64][8],int position[64][2])
{
    int s=0;
    for(int i=0;i<64;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(cflag[i][j]==true)
            {
                position[s][0]=i%8;
                position[s][1]=(i-i%8)/8;
                s++;
                break;
            }
        }
    }
    position[s][0]=-1;
    position[s][1]=-1;
}

void GameScene::SimulateChange(int x,int y,int _board[8][8],int _side)
{

    int px,py;
    int otherside = turnside-_side;
    //seach left
    if(x>=2)
    {
        px = x-1;
        while(_board[px][y]==otherside)
                _board[px][y]=_side;
            px=px-1;
    }
    //seach right
    if(x<=5)
    {
        px = x+1;
        while(_board[px][y]==otherside)
            _board[px][y]=_side;
        px=px+1;
    }
    //seach up
    if(y<=5)
    {
        py = y+1;
        while(_board[x][py]==otherside)
        {
            _board[x][py]=_side;
        }
        py=py+1;
    }
    //seach down
    if(y>=2)
    {
        py = y-1;
        while(_board[x][py]==otherside)
            _board[x][py]=_side;
        py=py-1;
    }
    //search left up
    if(x>=2&&y<=5)
    {
        px = x-1;
        py = y+1;
        while(_board[px][py]==otherside)
            _board[px][py]=_side;
        px=px-1;
        py=py+1;
    }
    //search left down
    if(x>=2&&y>=2)
    {
        px = x-1;
        py = y-1;
        while(_board[px][py]==otherside)
            _board[px][py]=_side;
        px=px-1;
        py=py-1;
    }
    //search right up
    if(x<=5&&y<=5)
    {
        px = x+1;
        py = y+1;
        while(_board[px][py]==otherside)
            _board[px][py]=_side;
        px=px+1;
        py=py+1;
    }
    //search right down
    if(x<=5&&y>=2)
    {
        px = x+1;
        py = y-1;
        while(_board[px][py]==otherside)
            _board[px][py]=_side;
        px=px+1;
        py=py-1;
    }
}

bool GameScene::FindSetlocation(int myside)
{
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

void GameScene::Replace(int (*from)[8], int (*to)[8])
{
    for(int i=0;i>8;i++)
    {
        for(int j=0;j<8;j++)
        {
            to[i][j] = from[i][j];
        }
    }
}


//find the max
void GameScene::Max(int location[2],int position[64][2])
{
    int max = -120;
    int xx,yy;
    int px = 0;
    int py = 0;
    for(int i=0;i<64;i++)
    {
        xx = position[i][0];
        yy = position[i][1];
        if(position[i][0]==-1)
            break;
        else
        {
            if(ValueList[xx][yy]>max)
            {
                max = ValueList[xx][yy];
                px = xx;
                py = yy;
            }
        }
    }
    location[0] = px;
    location[1] = py;
}

void recoverArray(int (*Array)[8])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            Array[i][j] = 0;
        }
    }
}

void GameScene::JudgeChessBoard(float dt)
{
    int AIside = side;
    int position[64][2];
    int position2[64][2];
    int position3[64][2];
    int position4[64][2];
    int side2,side3,side4;
    int carray[8][8];
    int xx,yy,i,ii,iii;
    int chessScore[64]={0};
    //寻找AI可以下的位置
    FindSetlocation(AIside);
    //将可以下的位置存在position数组中
    FindLocation(flag, position);
//    CopyArray(chessboard, carray);
    //复制棋盘
    for(i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            carray[i][j]=chessboard[i][j];
        }
    }
    //遍历棋盘寻找所有可以下的位置
    side2 = turnside - side;
    side3 = turnside - side2;
    side4 = turnside - side3;
    
    int _location[2];
    int layer2_Score[8][8]={0};
    int layer3_Score[8][8]={0};
    
    int x1,y1;
    int x2,y2;
    int x3,y3;
    
    int board1[8][8];
    int board2[8][8];
    int board3[8][8];
    
    int ms;
    std::vector<int> list;

    //保存第一层的状态
    Replace(chessboard, board1);
    for(i=0;i<64;i++)
    {
        //第一层
        if(position[i][0]==-1)
            break;
        else
        {
            x1 = position[i][0];
            y1 = position[i][1];
            board1[position[i][0]][position[i][1]] = side;
            SimulateChange(position[i][0], position[i][1],board1,side);
            FindSetlocation(side2);
            FindLocation(flag, position2);
            //保存第二层的状态
            Replace(board1, board2);
            //第二层
            for(ii=0;ii<64;ii++)
            {
                if(position2[ii][0]==-1)
                    break;
                else
                {
                    x2 = position2[ii][0];
                    y2 = position2[ii][1];
                    board2[position2[ii][0]][position2[ii][1]] = side2;
                    SimulateChange(position2[ii][0], position2[ii][1],board2,side2);
                    FindSetlocation(side3);
                    FindLocation(flag, position3);
                    //保存第三层的状态
                    Replace(board2, board3);
                    //第三层
                    for(iii=0;iii<64;iii++)
                    {
                        if(position3[iii][0] == -1)
                            break;
                        else
                        {
                            x3 = position3[iii][0];
                            y3 = position3[iii][1];
                            board3[position3[iii][0]][position3[iii][1]] = side3;
                            SimulateChange(position3[iii][0], position3[iii][1],board3,side3);
                            FindSetlocation(side4);
                            FindLocation(flag, position4);
                            Max(_location, position4);
                            //得到第三层的分数
                            layer3_Score[x3][y3] = -ValueList[_location[0]][_location[1]];
                            layer3_Score[x3][y3] += ValueList[x3][y3];
                            list.push_back(layer3_Score[x3][y3]);
                            //复原到第三层初始时的状态
                            Replace(board2, board3);
                        }
                        
                    }
                    //找到第三层分数最大的位置
                    ms = list[0];
                    for(auto pl:list)
                    {
                        if(pl > ms)
                        {
                            ms = pl;
                        }
                    }
                    list.clear();//清空list
                    //恢复第三层分数
                    recoverArray(layer3_Score);
                    
                    //得到第二层的该位置的分数
                    layer2_Score[x2][y2] = ms;
                    layer2_Score[x2][y2] = -ValueList[x2][y2];
                    list.push_back(layer2_Score[x2][y2]);
                    //恢复到第二层初始的状态
                    Replace(board1, board2);
                }
            }
            //找到第二层分数最大的位置
            if(list.size()!=0)
            {
                ms = list[0];
                for(auto pl:list)
                {
                    if(pl > ms)
                    {
                        ms = pl;
                    }
                }
                list.clear();//清空list
            }
            else
            {
                ms = 0;
            }
            //恢复分数
            recoverArray(layer2_Score);
            
            AIscore = ValueList[x1][y1];
            AIscore += ms;
           
            chessScore[i] = AIscore;
            CCLOG("score: %d",AIscore);

        }
    }
    //把尾后位置置为-1000 表示为截止位置
    chessScore[i]=-1000;

    int max = -1000;
    int index = 0;
    for(int j=0;j<64;j++)
    {
        //优先下四个角
         if((position[j][0]==0||position[j][1]==7)&&(position[j][1]==0||position[j][1]==7))
         {
             xx = position[j][0];
             yy = position[j][1];
             break;
        }
        //找到分数最大的位置
        if(chessScore[j]>max)
        {
            max = chessScore[j];
            xx = position[j][0];
            yy = position[j][1];
            index = j;
        }
        if(chessScore[j]==-1000)
            break;
    }
    
    CCLOG("x: %d, y: %d", xx,yy);
    CCLOG("score: %d",max);
    
    FindSetPoint(side);

    int pxx = int(xx*BlockWidth);
    int pyy = int(yy*BlockWidth);
   // CCLOG("x: %d,y: %d",xx,yy);
    auto action = DelayTime::create(5.0);
    auto WChessman = Sprite::create("res/css/wb5.png");
    WChessman->setScale(1.1, 1.1);
    WChessman->setPosition(Point((pxx+138.5),(pyy+73.5)));
    WChessman->setTag(xx+8*yy);
    chessArray.pushBack(WChessman);
    WChessman->runAction(action);
    
    this->addChild(WChessman,1);
    chessboard[xx][yy] = side;
    EatChess(xx, yy);
    playerSide.push_back(side);//side information
    side = turnside - side;

    FindSetPoint(side);
    //store information
    for(auto s:chessArray)
    {
        if(s->getTag()>=0)
            RegretChess[s->getTag()].pushBack(s);
    }
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            location[i][j].push_back(chessboard[i][j]);

        WhitePlayer->setVisible(true);
        BlackPlayer->setVisible(false);
    
    DjugeIfEnd();
}

