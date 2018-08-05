#include "GameScene.h"
Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    //480 320
    //375 267
    if ( !Layer::init() )
    {
        return false;
    }
    //init bgm
    SimpleAudioEngine::getInstance()->playBackgroundMusic("res/bgm/music.mp3");
    
    PVPgameStart=false;
    PVCgameStart=false;
    
    //init game
    InitchessBoard();
    
    //add chessman
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan , this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::AddChess , this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
    return true;
}


void GameScene::InitchessBoard()
{
    this->removeAllChildren();
    chessArray.clear();
    playerSide.clear();
    
    for(int i=0;i<64;i++)
        RegretChess[i].clear();
    
    //init side
    side = white;
    
    //init chessArray
    for(int i=0;i<64;i++)
    {
        auto initSpr = Sprite::create();
        chessArray.pushBack(initSpr);
    }
    
    
    //init chessBoard array
    for(int i=0;i<BoaredSize;i++)
    {
        for(int j=0;j<BoaredSize;j++)
        {
            chessboard[i][j]=empty;
        }
    }
    
    
    //add background
    auto background = Sprite::create("res/css/ChessBoard.png");
    Size visibleSize = Director::getInstance()->getWinSize();
    background ->setScale(visibleSize.width/400, visibleSize.height/267);
    background ->setAnchorPoint(Point(0.5,0.5));
    background ->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(background,0);
    
    //add menu
    auto regret = MenuItemImage::create("res/css/regret_normal.png","res/css/regret_selected.png",CC_CALLBACK_1(GameScene::Regret, this));
    regret->setPosition(Point(-50,-127));
    auto giveup = MenuItemImage::create("res/css/giveup_normal.png","res/css/giveup_selected.png",CC_CALLBACK_1(GameScene::GiveUp, this));
    giveup->setPosition(Point(45,-127));
    auto peace = MenuItemImage::create("res/css/peace_normal.png","res/css/peace_selected.png",CC_CALLBACK_1(GameScene::Peace, this));
    peace->setPosition(Point(-2,-127));
    auto PvPStart = MenuItemImage::create("res/css/PVP_normal.png","res/css/PVP_selected.png",CC_CALLBACK_1(GameScene::PvPGame, this));
    PvPStart->setPosition(Point(172,-40));
    auto PvCStart = MenuItemImage::create("res/css/PVC_normal.png","res/css/PVC_selected.png",CC_CALLBACK_1(GameScene::PvCGame, this));
    PvCStart->setPosition(Point(172,-80));
    auto ReStartButton = MenuItemImage::create("res/css/Restart_normal.png","res/css/Restart_selected.png",CC_CALLBACK_1(GameScene::ReStartGame, this));
    
    ReStartButton->setPosition(Point(172,-120));
    ReStartButton->setScale(0.5,0.5);
    auto menu = Menu::create(regret,giveup,peace,PvPStart,PvCStart,ReStartButton,NULL);
    this->addChild(menu);
    
    //init judgement state
    GameEnd[white-1]=false;
    GameEnd[black-1]=false;

    chessboard[3][3] = black;
    chessboard[4][4] = black;
    chessboard[3][4] = white;
    chessboard[4][3] = white;
    
    //Display Score
    auto WhiteScore = Label::createWithSystemFont("", "Thonburi", 10);
    WhiteScore->setPosition(Point(80.16,196.5));
    WhiteScore->setTag(100);
    this->addChild(WhiteScore,1);
    
    auto BlackScore = Label::createWithSystemFont("", "Thonburi", 10);
    BlackScore->setPosition(Point(80.16,85.5));
    BlackScore->setTag(101);
    this->addChild(BlackScore,1);
    DisplayScore();
    
    
    //display who set chess
    WhitePlayer = Sprite::create("res/css/wb1.png");
    WhitePlayer->setScale(1.5, 1.5);
    WhitePlayer->setPosition(Point(83,251.2));
    this->addChild(WhitePlayer,1);
    BlackPlayer = Sprite::create("res/css/wb5.png");
    BlackPlayer->setScale(1.5, 1.5);
    BlackPlayer->setPosition(Point(83,138));
    this->addChild(BlackPlayer,1);
    BlackPlayer->setVisible(false);
    
    
    //regret location
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            location[i][j].push_back(chessboard[i][j]);
    
    //lets chess board have four init chess
    auto initWhiteChessman1 = Sprite::create("res/css/wb1.png");
    auto initWhiteChessman2 = Sprite::create("res/css/wb1.png");
    auto initBlackChessman1 = Sprite::create("res/css/wb5.png");
    auto initBlackChessman2 = Sprite::create("res/css/wb5.png");
    initWhiteChessman1->setScale(1.1, 1.1);
    initWhiteChessman2->setScale(1.1, 1.1);
    initBlackChessman1->setScale(1.1, 1.1);
    initBlackChessman2->setScale(1.1, 1.1);
    //1
    initBlackChessman1->setPosition(Point((81.75+138.5),(81.75+73.5)));
    this->addChild(initBlackChessman1,1);
    initBlackChessman1->setTag(3+3*8);
    chessArray.pushBack(initBlackChessman1);
    RegretChess[3+3*8].pushBack(initBlackChessman1);
    //2
    initBlackChessman2->setPosition(Point((109+138.5),(109+73.5)));
    this->addChild(initBlackChessman2,1);
    initBlackChessman2->setTag(4+4*8);
    chessArray.pushBack(initBlackChessman2);
    RegretChess[4+4*8].pushBack(initBlackChessman2);
    //3
    initWhiteChessman1->setPosition(Point((81.75+138.5),(109+73.5)));
    this->addChild(initWhiteChessman1,1);
    initWhiteChessman1->setTag(3+4*8);
    chessArray.pushBack(initWhiteChessman1);
    RegretChess[3+4*8].pushBack(initWhiteChessman1);
    //4
    initWhiteChessman2->setPosition(Point((109+138.5),(81.75+73.5)));
    this->addChild(initWhiteChessman2,1);
    initWhiteChessman2->setTag(4+3*8);
    chessArray.pushBack(initWhiteChessman2);
    RegretChess[4+3*8].pushBack(initWhiteChessman2);
    
    if(PVPgameStart==true||PVCgameStart==true)
        FindSetPoint(white);

}

//
//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif


