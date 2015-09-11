/*
 * Card.h
 *
 *  Created on: 2015.08.18
 *      Author: kerlw
 */

#ifndef CARD_H_
#define CARD_H_

#include "cocos2d.h"

USING_NS_CC;

class Card: public Layer {
public:
	enum class CardType {
		CARD_MIN = 0,
	    CARD_MAX = 8,
		CARD_0 = 0,
		CARD_1,
	};

	bool init(const CardType& type, bool front);
	virtual ~Card();

	static Card* create(const CardType& type, bool front);

	void flipCard();

private:
	Card();

private:
	Sprite* m_pFront;
	Sprite* m_pBack;
	bool m_bFront;
};

#endif /* CARD_H_ */
