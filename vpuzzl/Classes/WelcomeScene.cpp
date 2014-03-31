#include "WelcomeScene.h"
#include "SelScene.h"

#include "res.h"

using namespace cocos2d;

CCScene* Welcome::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        Welcome *layer = (Welcome *)Welcome::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Welcome::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        CC_BREAK_IF(! CCLayer::init());
		winSize = CCDirector::sharedDirector()->getWinSize();

		if(ifFirstStart)
		{
			ifFirstStart = false;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(item_sel_eff);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(bgMusic,true);
		}		

		//add the backGround image
		CCSprite* pBkSprite = CCSprite::spriteWithFile(bg);
        CC_BREAK_IF(! pBkSprite);
        pBkSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(pBkSprite, 0);

		//add the vlogo
		pvlogoSprite = CCSprite::spriteWithFile(vlogo);
        CC_BREAK_IF(! pvlogoSprite);
		pvlogoSprite->setPosition(ccp(winSize.width/2, winSize.height - pvlogoSprite->getContentSize().height/2 - 50));
        this->addChild(pvlogoSprite, 0);

		//add the menu_layer
		l_menu_main = CCLayer::node();
		elasticOutXY = ccp(winSize.width, winSize.height);
		
		l_menu_main->setPosition(elasticOutXY);//
		this->addChild(l_menu_main, 0);
		//sin play
		float dltY = 90.0;
		CCMenuItemImage *pSinplayItem = CCMenuItemImage::itemWithNormalImage(
            menu_sin,
            menu_sin_sel,
            this,
            menu_selector(Welcome::menuSinglePlayCallback));
        CC_BREAK_IF(! pSinplayItem);
		pSinplayItem->setPosition(ccp(0, 0));
		//mul play
		CCMenuItemImage *pMulPlayItem = CCMenuItemImage::itemWithNormalImage(
            menu_mul,
            menu_mul_sel,
            this,
            menu_selector(Welcome::menuMultiPlayCallback));
        CC_BREAK_IF(! pMulPlayItem);
		pMulPlayItem->setPosition(ccp(0, -dltY));
		//about
		CCMenuItemImage *pAboutItem = CCMenuItemImage::itemWithNormalImage(
            menu_about,
            menu_about_sel,
            this,
            menu_selector(Welcome::menuAboutUsCallback));
        CC_BREAK_IF(! pAboutItem);
		pAboutItem->setPosition(ccp(0, -2*dltY));

		CCMenu* pMenu = CCMenu::menuWithItems(pSinplayItem, pMulPlayItem, pAboutItem, NULL);
        pMenu->setPosition(ccp(winSize.width/2, winSize.height/2));
        CC_BREAK_IF(! pMenu);
		l_menu_main->addChild(pMenu);		

		//add the studio log
		CCSprite* pslogoSprite = CCSprite::spriteWithFile(slogo);
        CC_BREAK_IF(! pslogoSprite);
		pslogoSprite->setPosition(ccp(pslogoSprite->getContentSize().width/2, pslogoSprite->getContentSize().height/2));
        this->addChild(pslogoSprite, 0);

		//add 'help' and 'sound'
		CCMenuItemImage *pHelpItem = CCMenuItemImage::itemWithNormalImage(
            help,
            help_sel,
            this,
            menu_selector(Welcome::menuHelpCallback));
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
																menu_selector(Welcome::menuSoundPlayCallback), 
																pSoundItem,
																pSoundDisItem,
																NULL );
		}else
		{
			soundToggle = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(Welcome::menuSoundPlayCallback), 
																pSoundDisItem,
																pSoundItem,
																
																NULL );
		}

		
		soundToggle->setPosition(ccp(winSize.width - 100, pSoundItem->getContentSize().height));

		CCMenu* pMenu2 = CCMenu::menuWithItems(pHelpItem, soundToggle,  NULL);
        pMenu2->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu2);
		l_menu_main->addChild(pMenu2);	

		
		schedule(schedule_selector(Welcome::logoAction),0.3);
		schedule(schedule_selector(Welcome::menuAction),0.3);
		bRet = true;
    } while (0);

    return bRet;
}

void Welcome::logoAction(float dt)
{
	unschedule(schedule_selector(Welcome::logoAction));
	CCActionInterval* s_main_ease_out = CCScaleTo::actionWithDuration(12.0,(1.05));
	CCActionInterval* s_main_ease_in = (CCScaleTo::actionWithDuration(12.0,(0.95)));
	CCFiniteTimeAction* seq1 = CCSequence::actions(
		s_main_ease_out, 
		s_main_ease_in,
		NULL);
	pvlogoSprite->runAction( CCRepeatForever::actionWithAction((CCActionInterval*)seq1));
}

void Welcome::menuAction(float dt)
{
	unschedule(schedule_selector(Welcome::menuAction));
	CCActionInterval* move = CCMoveBy::actionWithDuration(0.8, ccpSub(CCPointZero, elasticOutXY));
	CCActionInterval* move_ease_out = CCEaseElasticOut::actionWithAction((CCActionInterval*)(move->copy()->autorelease()) );

	l_menu_main->runAction(move_ease_out);
}

void Welcome::menuSinglePlayCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(item_sel_eff);

	CCScene *pScene = Sel::scene();
	CCScene *tmpScene = CCTransitionFade::transitionWithDuration(1.2f, pScene);
	//pScene ->autorelease();
	CCDirector::sharedDirector()->replaceScene(tmpScene);
}

void Welcome::menuMultiPlayCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(item_sel_eff);
	//CCLog("menuMultiPlayCallback");
}

void Welcome::menuAboutUsCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(item_sel_eff);
    //CCLog("menuAboutUsCallback");
}

void Welcome::menuHelpCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(item_sel_eff);
    //CCLog("menuHelpCallback");
}

void Welcome::menuSoundPlayCallback(CCObject* pSender)
{
	if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
	}else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(bgMusic,true);
	}
	
}

