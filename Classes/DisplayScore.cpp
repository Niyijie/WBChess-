#include"GameScene.h"

void GameScene::DisplayScore()
{
    
    this->removeChildByTag(100);
    this->removeChildByTag(101);
    WhiteChessNumber=0;
    BlackChessNumber=0;
    
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(chessboard[i][j]==white)
                WhiteChessNumber++;
            else if(chessboard[i][j]==black)
                BlackChessNumber++;
        }
    }
    
    
    std::string ws,wb;
    ws=std::to_string(WhiteChessNumber);
    wb=std::to_string(BlackChessNumber);
    
    auto WhiteScore = Label::createWithSystemFont("", "Thonburi", 10);
    WhiteScore->setPosition(Point(80.16,196.5));
    WhiteScore->setTag(100);
    WhiteScore->setString(ws);
    this->addChild(WhiteScore,1);
    
    auto BlackScore = Label::createWithSystemFont("", "Thonburi", 10);
    BlackScore->setPosition(Point(80.16,81.5));
    BlackScore->setTag(101);
    BlackScore->setString(wb);
    this->addChild(BlackScore,1);
}
