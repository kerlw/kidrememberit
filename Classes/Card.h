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
		CARD_0 = 0,
		CARD_1,
	};

	bool init(const CardType& type);
	virtual ~Card();

	static Card* create(const CardType& type);

	void flipCard();

private:
	Card();


};

#endif /* CARD_H_ */
