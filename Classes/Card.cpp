/*
 * Card.cpp
 *
 *  Created on: 2015.08.18
 *      Author: kerlw
 */

#include "Card.h"

Card* Card::create(const CardType& type) {
	Card *pRet = new (std::nothrow) Card();
	if (pRet && pRet->init(type)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

Card::Card() {
	// TODO Auto-generated constructor stub

}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

bool Card::init(const CardType& type) {
	return true;
}

void Card::flipCard() {

}
