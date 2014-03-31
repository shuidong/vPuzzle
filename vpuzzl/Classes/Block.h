#ifndef __MENU_BLOCK_H__
#define __MENU_BLOCK_H__

#include "cocos2d.h"
class Unit;

class Block
{
public:
	int zOrder;
	Block(void);
	~Block(void);
	void addUnit(Unit*);
	int getDtX();
	int getDtY();
	bool isConnector(Block* tarB);
	std::vector <Unit*> unit_vector_;
};

#endif
