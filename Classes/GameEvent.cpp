#include"GameScene.h"

void GameScene::GameEvent()
{
    if(GameEnd[0]==true&&GameEnd[1]==true)
    {
        PVPgameStart = false;
        PVCgameStart = false;
        
        SimpleAudioEngine::getInstance()->playBackgroundMusic("res/bgm/win.mp3");
        
        int groudwidth,groudheight;
        groudwidth=Director::getInstance()->getWinSize().width;
        groudheight=Director::getInstance()->getWinSize().height;
        
        //白棋赢
        if(WhiteChessNumber>BlackChessNumber)
        {
            auto WhiteWin = Sprite::create("res/css/WhiteWin.png");
            WhiteWin->setPosition(Point(groudwidth/2,groudheight/2));
            this->addChild(WhiteWin,1);
        }
        //黑棋赢
        if(WhiteChessNumber<BlackChessNumber)
        {
            auto BlackWin = Sprite::create("res/css/BlackWin.png");
            BlackWin->setPosition(Point(groudwidth/2,groudheight/2));
            this->addChild(BlackWin,1);
        }
        //和棋
        if(WhiteChessNumber==BlackChessNumber)
        {
            auto GamePeace = Sprite::create("res/css/Peace.png");
            GamePeace->setPosition(Point(groudwidth/2,groudheight/2));
            this->addChild(GamePeace, 1);
        }
    }
}
