#include "Unit.h"

using namespace cocos2d;
Unit::Unit(int x, int y, CCSprite* msprite, int xIdx, int yIdx)
{
	this->ox = x;
	this->oy = y;
	this->mSprite = msprite;
	this->idxOfX = xIdx;
	this->idxOfY = yIdx;

	mSprite->setUserData(this);
	this->dtX = mSprite->getPosition().x - (ox + mSprite->getContentSize().width/2);
	this->dtY = mSprite->getPosition().y - (oy - mSprite->getContentSize().height/2);
}

void Unit::setBlock(Block* pBlock){
	this->parentBlock = pBlock;
}

Unit::~Unit(void)
{
}
