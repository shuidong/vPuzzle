#include "GameScene.h"
#include "SelScene.h"
#include "NoTouchLayer.h"
#include "PiecesBoard.h"
#include "Unit.h"
//#include "glew.h"
#include "res.h"
//#define GL_TEXTURE_ENV 0x2300
//#define GL_TEXTURE_ENV_MODE 0x2200
//#define GL_MODULATE 0x2100
using namespace cocos2d;

CCScene* Game::scene()
{
    CCScene * scene = NULL;
    do 
    {
		scene = CCScene::node();
        CC_BREAK_IF(! scene);

		Game *layer = (Game *)Game::node();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

	return scene;
}

void Game::onExit()
{
	if(!pauseLayer)
	{
		//CCLog("pauseLayer auto.");
		pauseLayer->autorelease();
	}
	unschedule(schedule_selector(Game::step));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect(magic_eff);
	CCLayer::onExit();

}

bool Game::init()
{
    bool bRet = false;
    do 
    {
		//
		CC_BREAK_IF(! CCLayer::init());
		winSize = CCDirector::sharedDirector()->getWinSize();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(magic_eff);
		//add the backGround image
		CCSprite* pBkSprite = CCSprite::spriteWithFile(bg);
        CC_BREAK_IF(! pBkSprite);
        pBkSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(pBkSprite, 0);

		float menuX = 50;
		float menuY = 80;
		//pause
		CCMenuItemImage *pPauseItem = CCMenuItemImage::itemWithNormalImage(
            pausex,
            pause_sel,
			this,
            menu_selector(Game::menuPauseCallback)
			);
        CC_BREAK_IF(! pPauseItem);
		pPauseItem->setPosition(ccp(menuX, winSize.height - menuY));
		//back
		CCMenuItemImage *pBackItem = CCMenuItemImage::itemWithNormalImage(
            back_ico,
            back_ico_sel,
			this,
            menu_selector(Game::menuBackCallback)
			);
        CC_BREAK_IF(! pBackItem);
		pBackItem->setPosition(ccp(menuX, winSize.height - menuY * 2));
		//
		CCMenuItemImage *pHelpItem = CCMenuItemImage::itemWithNormalImage(
            help,
            help_sel,
            this,
            menu_selector(Game::menuHelpCallback));
        CC_BREAK_IF(! pHelpItem);
		pHelpItem->setPosition(ccp(menuX, winSize.height - menuY * 3));
		//sound
		CCMenuItemImage *pSoundItem = CCMenuItemImage::itemWithNormalImage(
            sound,
            sound_disable
            );
		CC_BREAK_IF(! pSoundItem);
		CCMenuItemImage *pSoundDisItem = CCMenuItemImage::itemWithNormalImage(
            sound_disable,
            sound
			);
        CC_BREAK_IF(! pSoundDisItem);
				
		CCMenuItemToggle* soundToggle = NULL;
		if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			soundToggle = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(Game::menuSoundPlayCallback), 
																pSoundItem,
																pSoundDisItem,
																NULL );
		}else
		{
			soundToggle = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(Game::menuSoundPlayCallback), 
																pSoundDisItem,
																pSoundItem,																
																NULL );
		}
		soundToggle->setPosition(ccp(menuX, winSize.height - menuY * 4));

		CCMenu* pMenu = CCMenu::menuWithItems(pPauseItem, pBackItem, pHelpItem, soundToggle, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
		this->addChild(pMenu);

		//magic Menu
		CCMenuItemImage *pMagicItem1 = CCMenuItemImage::itemWithNormalImage(
            magic1,
            magic1_sel,
            this,
            menu_selector(Game::menuMagic1Callback));
        CC_BREAK_IF(! pMagicItem1);
		pMagicItem1->setPosition(ccp(menuX, menuY * 1));

		CCMenuItemImage *pMagicItem2 = CCMenuItemImage::itemWithNormalImage(
            magic1,
            magic1_sel,
            this,
            menu_selector(Game::menuMagic2Callback));
        CC_BREAK_IF(! pMagicItem2);
		pMagicItem2->setPosition(ccp(menuX, menuY * 2));

		CCMenuItemImage *pMagicItem3 = CCMenuItemImage::itemWithNormalImage(
            magic1,
            magic1_sel,
            this,
            menu_selector(Game::menuMagic3Callback));
        CC_BREAK_IF(! pMagicItem3);
		pMagicItem3->setPosition(ccp(menuX, menuY * 3));
		CCMenu* pMagicMenu = CCMenu::menuWithItems(pMagicItem1, pMagicItem2, pMagicItem3, NULL);
        pMagicMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMagicMenu);
		this->addChild(pMagicMenu);
		
		//pause layer
		pauseLayer = (NoTouchLayer*)NoTouchLayer::node();
		pauseLayer->retain();
		//this->addChild(pauseLayer);
		pauseLayer->setAnchorPoint(ccp(winSize.width/2, winSize.height/2));
		//continue
		CCMenuItemImage *pContinueItem = CCMenuItemImage::itemWithNormalImage(
            contin,
            contin_sel,
            this,
            menu_selector(Game::menuContinueCallback));
        CC_BREAK_IF(! pContinueItem);
		pContinueItem->setPosition(ccp(0, menuY));
		//restart
		CCMenuItemImage *pRestartItem = CCMenuItemImage::itemWithNormalImage(
            restart,
            restart_sel,
            this,
            menu_selector(Game::menuRestartCallback));
        CC_BREAK_IF(! pRestartItem);
		pRestartItem->setPosition(ccp(0, 0));
		//main
		CCMenuItemImage *pMainMenuItem = CCMenuItemImage::itemWithNormalImage(
            mainMenu,
            mainMenu_sel,
            this,
            menu_selector(Game::menuMainMenuCallback));
        CC_BREAK_IF(! pMainMenuItem);
		pMainMenuItem->setPosition(ccp(0, -menuY));

		CCMenu* pPauseBoardMenu = CCMenu::menuWithItems(pContinueItem, pRestartItem, pMainMenuItem, NULL);
		pPauseBoardMenu->setPosition(ccp(winSize.width/2, winSize.height/2 - 100));
        CC_BREAK_IF(! pPauseBoardMenu);
		pauseLayer->addChild(pPauseBoardMenu, 1, 0);	
		//pause_logo
		CCSprite* pvlogoSprite = CCSprite::spriteWithFile(vlogo);
        CC_BREAK_IF(! pvlogoSprite);
		pvlogoSprite->setPosition(ccp(winSize.width/2, winSize.height - pvlogoSprite->getContentSize().height/2 - 50));
        pauseLayer->addChild(pvlogoSprite, 0);

		//gameArea
		CCSprite* pDesktopSprite = CCSprite::spriteWithFile(desktop);
        CC_BREAK_IF(! pDesktopSprite);
		pDesktopSprite->setPosition(ccp(winSize.width/2 - 40, winSize.height/2));
        this->addChild(pDesktopSprite, 0);
		
		//thumb image
		char imgPath[20] = {0};
		sprintf(imgPath, "thumbnail%d.jpg", stageIndex);
		CCSprite* pThumbSprite = CCSprite::spriteWithFile(imgPath);
		CC_BREAK_IF(! pThumbSprite);
		pThumbSprite->setPosition(ccp(winSize.width - 90, pThumbSprite->getContentSize().height/2 + 20));
		this->addChild(pThumbSprite, THUMB_SPRITE_Z_ORDER);

		//gen puzzle elements
		maskInitPos[0][0] = ccp(0, 0);
		maskInitPos[0][1] = ccp(95, 0);
		maskInitPos[0][2] = ccp(220, 0);
		maskInitPos[0][3] = ccp(366, 0);
		maskInitPos[0][4] = ccp(466, 0);
		maskInitPos[0][5] = ccp(588, 0);
		
		maskInitPos[1][0] = ccp(0, 96);
		maskInitPos[1][1] = ccp(118, 96);
		maskInitPos[1][2] = ccp(220, 119);
		maskInitPos[1][3] = ccp(342, 96);
		maskInitPos[1][4] = ccp(488, 96);
		maskInitPos[1][5] = ccp(611, 96);

		maskInitPos[2][0] = ccp(0, 218);
		maskInitPos[2][1] = ccp(95, 219);
		maskInitPos[2][2] = ccp(242, 219);
		maskInitPos[2][3] = ccp(342, 219);
		maskInitPos[2][4] = ccp(488, 218);
		maskInitPos[2][5] = ccp(612, 242);

		maskInitPos[3][0] = ccp(0, 342);
		maskInitPos[3][1] = ccp(118, 364);
		maskInitPos[3][2] = ccp(242, 342);
		maskInitPos[3][3] = ccp(342, 365);
		maskInitPos[3][4] = ccp(466, 342);
		maskInitPos[3][5] = ccp(612, 342);

		maskInitPos[4][0] = ccp(0, 488);
		maskInitPos[4][1] = ccp(96, 464);
		maskInitPos[4][2] = ccp(242, 488);
		maskInitPos[4][3] = ccp(366, 465);
		maskInitPos[4][4] = ccp(488, 488);
		maskInitPos[4][5] = ccp(612, 464);

		maskInitPos[5][0] = ccp(0, 611);
		maskInitPos[5][1] = ccp(118, 588);
		maskInitPos[5][2] = ccp(242, 610);
		maskInitPos[5][3] = ccp(366, 588);
		maskInitPos[5][4] = ccp(466, 588);
		maskInitPos[5][5] = ccp(612, 588);
        
        
        
        CCEGLView* eglView = CCEGLView::sharedOpenGLView();
       // eglView->setDesignResolutionSize(1024,768,kResolutionExactFit); 
        CCSize xsize = CCDirector::sharedDirector()->getWinSize();
        CCSize tt = eglView->getFrameSize();
        
        
        float scx = tt.width / xsize.width;
        float scy = tt.height / xsize.height;
        
        /*
        CCLog("－－－－－－－－－－－－－scx = %f", scx);
        for(int i = 0; i<6; i++){
            for(int j = 0; j < 6; j++){
                maskInitPos[i][j].x *= scx;
                maskInitPos[i][j].y *= scy;
            }
        }*/
		
		sprintf(imgPath, "stage%d.jpg", stageIndex);
		CCSprite* origSprite = CCSprite::spriteWithFile(imgPath);
		origSprite->setAnchorPoint(ccp(0 , 0));
		origSprite->retain();

		int W = origSprite->getContentSize().width;
		int H = origSprite->getContentSize().height;
		//CCRenderTexture* rt = CCRenderTexture::renderTextureWithWidthAndHeight(W, H);
		
		ccBlendFunc bfMask = ccBlendFunc();
		bfMask.src = GL_ONE;
		bfMask.dst = GL_ZERO;

		ccBlendFunc bfTexture = ccBlendFunc();
		bfTexture.src = GL_DST_ALPHA;
		bfTexture.dst = GL_ZERO;

		
		origSprite->setPosition(CCPointZero);	
		
		piecesLayer = PiecesBoard::node();//for holding all the pieces which haven't used
		((PiecesBoard*)piecesLayer)->pGame = this;
		((PiecesBoard*)piecesLayer)->setRect(winSize.width - 170, pThumbSprite->getContentSize().height + 20 , 170, winSize.height - 250);
		piecesLayer->setAnchorPoint(CCPointZero);
		piecesLayer->setPosition(CCPointZero);
		this->addChild(piecesLayer, PIECE_LAYER_Z_ORDER);

		float pieceInitY = 350;//first piece's Y position

		//maskSprites[i][j]
		
		for(int i = 0; i < 6; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				sprintf(imgPath,"mask1/gm%d-%d.png",i,j);
				maskSprites[i][j] = CCSprite::spriteWithFile(imgPath);
				sprintf(imgPath,"mask1/sgm%d-%d.png",i,j);
				shadowSprites[i][j] = CCSprite::spriteWithFile(imgPath);
				//maskSprites[i][j]->retain();

				int w = (int)maskSprites[i][j]->getContentSize().width;
				int h = (int)maskSprites[i][j]->getContentSize().height;
				maskSprites[i][j]->setAnchorPoint(ccp(0 , 0));
				maskSprites[i][j]->setBlendFunc(bfMask);
				maskSprites[i][j]->setPosition(ccp(0, 0));
				//maskSprites[i][j]->getTexture()->setAliasTexParameters();

				CCRect  rect = CCRectMake(maskInitPos[i][j].x, maskInitPos[i][j].y, w, h);
				CCSprite *pTextureSprite = CCSprite::spriteWithTexture(origSprite->getTexture(), rect);
				pTextureSprite->setBlendFunc(bfTexture);
				pTextureSprite->setAnchorPoint(ccp(0 , 0));
				pTextureSprite->setPosition(CCPointZero);

				CCRenderTexture* rt = CCRenderTexture::renderTextureWithWidthAndHeight(w, h);
				rt->begin();
				maskSprites[i][j]->visit();

				pTextureSprite->visit();
				//glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				rt->end();

				pSprites[i][j] = CCSprite::spriteWithTexture(rt->getSprite()->getTexture());
				CC_BREAK_IF(! pSprites[i][j]);
				pSprites[i][j]->setFlipY(true);

				float ratio = 1;
				float w1 = maskSprites[i][j]->getContentSize().width * ratio;
				float h1 = maskSprites[i][j]->getContentSize().height * ratio;
				maskSprites[i][j]->setAnchorPoint(ccp(0.5, 0.5));
				//gen the edge image
				maskSprites[i][j]->setScale(ratio);
				

				//CCPoint tmpP = ccp(3, 3);
				maskSprites[i][j]->setPosition(ccp(w1/2 + 1,h1/2 + 1));
				//maskSprites[i][j]->setAnchorPoint(ccp(0,0));

				pSprites[i][j]->setPosition(ccp(w1/2,h1/2));
				pSprites[i][j]->setAnchorPoint(ccp(0.5, 0.5));
				maskSprites[i][j]->getTexture()->setAntiAliasTexParameters();

				CCRenderTexture* rt2 = CCRenderTexture::renderTextureWithWidthAndHeight(w1, h1);
				rt2->begin();
				maskSprites[i][j]->visit();
				pSprites[i][j]->visit();
				rt2->end();
				pSprites[i][j] = CCSprite::spriteWithTexture(rt2->getSprite()->getTexture());
				
				pSprites[i][j]->getTexture()->setAntiAliasTexParameters();
				pSprites[i][j]->setAnchorPoint(ccp(0.5, 0.5));
			//	piecesLayer->addChild(pSprites[i][j], 100+ i*6 + j);//add to piecesLayer
				
				pSprites[i][j]->setFlipY(true);
				
				
			//	piecesLayer->addChild(shadowSprites[i][j], i*6 + j);//add the shadow
				shadowSprites[i][j]->setAnchorPoint(ccp(0.5, 0.5));
				isSpritesUsed[i][j] = false;
			}

		}
		int radomArray[6*6];
		for(int i=0; i<36; i++){
			radomArray[i] = i;
		}
		for(int i=0; i<36; i++){
			int tmp = (i+1) + CCRANDOM_0_1()* (34-i);
			CC_SWAP(radomArray[i], radomArray[tmp], int);
		}
		//radom the pieces
		for(int k=0; k<36; k++){
			int i= radomArray[k]%6;
			int j= radomArray[k]/6;
			/*
			int i= k%6;
			int j= k/6;
			*/
			piecesLayer->addChild(pSprites[i][j], 100+ i*6 + j);//add to piecesLayer
			piecesLayer->addChild(shadowSprites[i][j], i*6 + j);//add to piecesLayer
			
			pSprites[i][j]->setPosition(ccp(winSize.width - 100, pieceInitY));
			shadowSprites[i][j] ->setPosition(ccp(winSize.width - 100 + 5, pieceInitY - 5));
			//
			Unit* pUnit = new Unit(maskInitPos[i][j].x * scx,
					winSize.height - maskInitPos[i][j].y * scy,
					pSprites[i][j],
					i,j);
				

			Block* blk = new Block();
			blk->addUnit(pUnit);

			blocks.push_back(blk);
				//
			

			pieceInitY += pSprites[i][j]->getContentSize().height + 25;
		}

		//pSprites[0][1]->setPosition(ccp(winSize.width/2, winSize.height/2));
		//this->addChild(pSprites[0][1]);
		//timeArea
		CCLabelBMFont* label1 = CCLabelBMFont::labelWithString("00:00", numberFont);
		//label1->setAnchorPoint( ccp(0,0) );
		label1->setPosition(ccp(winSize.width - 85, winSize.height - 50));
		this->addChild(label1, NUMBER_AREA_Z_ORDER, NUMBER_AREA_TAG);
		//update the timeArea
		m_time = 0;
		schedule( schedule_selector(Game::step), 1);

		this->setTouchEnabled(true);
		bRet = true;
	} while (0);

	setTouchEnabled(true);
    return bRet;
}


void Game::step(float dt)
{
	m_time += dt;
	////CCLog("m_time=%f",m_time);
	char string[10] = {0};
    sprintf(string, "%02d:%02d", int(m_time)/60, int(m_time)%60);
	
	CCLabelBMFont* label1 = (CCLabelBMFont*) getChildByTag(NUMBER_AREA_TAG);
	label1->setString(string);
}

void Game::menuContinueCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->resume();
	this->removeChild(pauseLayer, false);
};
	 
void Game::menuRestartCallback(CCObject* pSender)
{
	//CCLog("restart.");
};
	 
void Game::menuMainMenuCallback(CCObject* pSender)
{
	//CCLog("mainMenu.");
};

void Game::menuMagic1Callback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(magic_eff);
	//CCLog("magic1");
}

void Game::menuMagic2Callback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(magic_eff);
	//CCLog("magic2");
}

void Game::menuMagic3Callback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(magic_eff);
	//CCLog("magic3");
}

void Game::menuPauseCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(item_sel_eff);
	this->addChild(pauseLayer, 99, 1);
	//CCLog("pause");
	CCDirector::sharedDirector()->pause();
}

void Game::menuBackCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(item_sel_eff);
	CCScene *pScene = Sel::scene();
	CCScene *tmpScene = CCTransitionFade::transitionWithDuration(0.8f, pScene);
	CCDirector::sharedDirector()->replaceScene(tmpScene);
}

void Game::menuHelpCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(item_sel_eff);
    //CCLog("menuHelpCallback");
}

void Game::menuSoundPlayCallback(CCObject* pSender)
{
	if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
	}else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(bgMusic,true);
	}
}

void Game::ccTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	//CCLog("touched");
	/*CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint pos = touch->locationInView(touch->view());
	pos = CCDirector::sharedDirector()->convertToGL(pos);

	pSprite_= NULL;
	pActiveBlk = NULL;
	((PiecesBoard*)piecesLayer)->isBlockSelected = false;
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			if(CCRect::CCRectContainsPoint(((CCNode* )pSprites[i][j])->boundingBox(), pos)  ){
				pSprite_ = pSprites[i][j];
				
				Unit* pu = (Unit*)pSprite_->getUserData();
				pActiveBlk = pu->parentBlock;

				int tmp = 200;
				for (vector<Unit*>::iterator it = pActiveBlk->unit_vector_.begin();
					it != pActiveBlk->unit_vector_.end(); ++it)
				{
					reorderChild((*it)->mSprite, tmp);
				}
				((PiecesBoard*)piecesLayer)->isBlockSelected  = true;
				return;
		}
		}
	}	*/
}

void Game::ccTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	/*CCPoint pre_position = GetFirstTouchPrePosInGL(pTouches);
	CCPoint position = Game::GetFirstTouchPosInGL(pTouches);
	if (piecesLayer != NULL)
	{
		CCPoint current_point = piecesLayer->getPosition();
		piecesLayer->setPosition(ccp(0, current_point.y + position.y - pre_position.y));
					
	}*/
}

CCPoint Game::GetFirstTouchPosInGL(CCSet* touches) {
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint pos = touch->locationInView();
	pos = CCDirector::sharedDirector()->convertToGL(pos);
	return pos;
}

CCPoint Game::GetFirstTouchPrePosInGL(CCSet* touches) {
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint pos = touch->previousLocationInView();
	pos = CCDirector::sharedDirector()->convertToGL(pos);
	return pos;
}
