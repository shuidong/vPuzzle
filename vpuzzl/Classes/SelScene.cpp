#include "SelScene.h"
#include "WelcomeScene.h"
#include "CCRadioMenu.h"

#include "StagesBoard.h"

#include "res.h"

using namespace cocos2d;

CCScene* Sel::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        Sel *layer = (Sel *)Sel::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Sel::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        CC_BREAK_IF(! CCLayer::init());
		winSize = CCDirector::sharedDirector()->getWinSize();
		//add the backGround image
		CCSprite* pBkSprite = CCSprite::spriteWithFile(bg);
        CC_BREAK_IF(! pBkSprite);
        pBkSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(pBkSprite, 0);

		//add the vlogo
		pvlogoSprite = CCSprite::spriteWithFile(vlogo);
        CC_BREAK_IF(! pvlogoSprite);
		pvlogoSprite->setScale(0.6f);
		pvlogoSprite->setPosition(ccp(winSize.width/2, winSize.height - pvlogoSprite->getContentSize().height/2));
        this->addChild(pvlogoSprite, 0);

		l_menu_main = CCLayer::node();
		
		l_menu_main->setPosition(CCPointZero);//
		this->addChild(l_menu_main, 0);

		//add the stage chooser
		stageChoserY = winSize.height * 0.6 - 40.0f;
		CCSprite* pLevelPanSprite = CCSprite::spriteWithFile(level_pan);
        CC_BREAK_IF(! pLevelPanSprite);
		pLevelPanSprite->setScaleX(winSize.width/pLevelPanSprite->getContentSize().width);
        pLevelPanSprite->setPosition(ccp(winSize.width/2, stageChoserY));
        this->addChild(pLevelPanSprite, 0);

		//left-side
		CCSprite* pLevelPanLeftSprite = CCSprite::spriteWithFile(level_pan_side);
        CC_BREAK_IF(! pLevelPanLeftSprite);
		pLevelPanLeftSprite->setScaleY(pLevelPanSprite->getContentSize().height/pLevelPanLeftSprite->getContentSize().height);
		pLevelPanLeftSprite->setPosition(ccp(pLevelPanLeftSprite->getContentSize().width/2, stageChoserY));
        this->addChild(pLevelPanLeftSprite, 5);

		//right-side
		CCSprite* pLevelPanRightSprite = CCSprite::spriteWithFile(level_pan_side);
        CC_BREAK_IF(! pLevelPanRightSprite);
		pLevelPanRightSprite->setRotation(180);
		pLevelPanRightSprite->setScaleY(pLevelPanSprite->getContentSize().height/pLevelPanRightSprite->getContentSize().height);
        pLevelPanRightSprite->setPosition(ccp(winSize.width - pLevelPanRightSprite->getContentSize().width/2, stageChoserY));
        this->addChild(pLevelPanRightSprite, 5);

		//stage layer
		l_stage_main = StagesBoard::node();
		((StagesBoard*)l_stage_main)->setRect(0, stageChoserY - pLevelPanSprite->getContentSize().height/2,winSize.width, pLevelPanSprite->getContentSize().height);
		l_stage_main->setPosition(CCPointZero);//
		this->addChild(l_stage_main, 0);
		//s1
		CCPoint stageXY = ccp(winSize.width, stageChoserY);
		CCSprite* selectedStage = CCSprite::spriteWithFile(stage_sel);
		selectedStage->setVisible(false);

		CCSprite** stages = ((StagesBoard*)l_stage_main)->stages;
		stageInfo * stageInfos = ((StagesBoard*)l_stage_main)->stageInfos;
		

		const int lock_til = 9;
		for(int i=0; i<10; i++)
		{
			CCSprite* tmp = CCSprite::spriteWithFile(stage_sel);
			CC_BREAK_IF(! tmp);
			tmp->setUserData(NULL);
			tmp->setPosition(ccpAdd(stageXY, ccp(i * (tmp->getContentSize().width  + 50) + 10, -10)));
			l_stage_main->addChild(tmp);	


			char stgImg[20];
			sprintf(stgImg, "thumbnail%d.jpg", i);
			stages[i] = CCSprite::spriteWithFile(i < lock_til ? stgImg: locked);
			CC_BREAK_IF(! stages[i]);

			stageInfos[i].isLocked = i < lock_til ? false : true;
			stageInfos[i].stageIndex = i;
			stages[i]->setUserData(stageInfos+i);

			stages[i]->setPosition(ccpAdd(stageXY, ccp(i * (stages[i]->getContentSize().width  + 50), 0)));
			l_stage_main->addChild(stages[i]);	
		}

		
        
		//add the levels_layer
		float levelMenuY = stageChoserY -  pLevelPanSprite->getContentSize().height * 0.6f;
		CCMenuItemImage *pEasyItem = CCMenuItemImage::itemWithNormalImage(
            easy,
            easy_sel,
            this,
            menu_selector(Sel::menuHelpCallback));
        CC_BREAK_IF(! pEasyItem);
		pEasyItem->setPosition(ccp(winSize.width/2 - 200, levelMenuY));

		CCMenuItemImage *pMidItem = CCMenuItemImage::itemWithNormalImage(
            mid,
            mid_sel,
            this,
            menu_selector(Sel::menuHelpCallback));
        CC_BREAK_IF(! pMidItem);
		pMidItem->setPosition(ccp(winSize.width/2, levelMenuY));

		CCMenuItemImage *pHardItem = CCMenuItemImage::itemWithNormalImage(
            hard,
            hard_sel,
            this,
            menu_selector(Sel::menuHelpCallback));
        CC_BREAK_IF(! pHardItem);
		pHardItem->setPosition(ccp(winSize.width/2 + 200, levelMenuY));

		CCRadioMenu* pLevelMenu= CCRadioMenu::radioMenuWithItems(pEasyItem, pMidItem, pHardItem, NULL);
		pLevelMenu->setPosition(CCPointZero);
		pLevelMenu->setSelectedRadioItem(pEasyItem);
        CC_BREAK_IF(! pLevelMenu);
		this->addChild(pLevelMenu);	

		//add the 'Back' menu
		CCMenuItemImage *pBackItem = CCMenuItemImage::itemWithNormalImage(
            back,
            back_sel,
            this,
            menu_selector(Sel::menuBackCallback));
        CC_BREAK_IF(! pBackItem);
		pBackItem->setPosition(ccp(100, pBackItem->getContentSize().height));
		
		//add 'help' and 'sound'
		CCMenuItemImage *pHelpItem = CCMenuItemImage::itemWithNormalImage(
            help,
            help_sel,
            this,
            menu_selector(Sel::menuHelpCallback));
        CC_BREAK_IF(! pHelpItem);
		pHelpItem->setPosition(ccp(winSize.width - 200, pHelpItem->getContentSize().height));
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
																menu_selector(Sel::menuSoundPlayCallback), 
																pSoundItem,
																pSoundDisItem,
																NULL );
		}else
		{
			soundToggle = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(Sel::menuSoundPlayCallback), 
																pSoundDisItem,
																pSoundItem,																
																NULL );
		}
		soundToggle->setPosition(ccp(winSize.width - 100, pSoundItem->getContentSize().height));

		CCMenu* pMenu2 = CCMenu::menuWithItems(pBackItem, pHelpItem, soundToggle, NULL);
        pMenu2->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu2);
		l_menu_main->addChild(pMenu2);	

	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(item_sel_eff);
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(bgMusic,true);

		schedule(schedule_selector(Sel::stageAction),0.5f);
		bRet = true;
    } while (0);

    return bRet;
}


void Sel::stageAction(float dt)
{
	unschedule(schedule_selector(Sel::stageAction));	
	CCActionInterval* move = CCMoveBy::actionWithDuration(3.8f, ccp(200 - winSize.width, 0));
	CCActionInterval* move_ease_out = CCEaseElasticOut::actionWithAction((CCActionInterval*)(move->copy()->autorelease()) );

	l_stage_main->runAction(move_ease_out);
}

void Sel::menuBackCallback(CCObject* pSender)
{
	CCScene *pScene = Welcome::scene();
	CCScene *tmpScene = CCTransitionFade::transitionWithDuration(0.8f, pScene);
	CCDirector::sharedDirector()->replaceScene(tmpScene);
}

void Sel::menuHelpCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(item_sel_eff);
    //CCLog("menuHelpCallback");
}

void Sel::menuSoundPlayCallback(CCObject* pSender)
{
	if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
	}else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(bgMusic,true);
	}
	
}

