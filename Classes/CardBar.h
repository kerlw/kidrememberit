/*
 * CardBar.h
 *
 *  Created on: 2015.09.24
 *      Author: kerlw
 */

#ifndef CARDBAR_H_
#define CARDBAR_H_

#include "cocos2d.h"

#include <vector>

class Card;

USING_NS_CC;

class CardBar: public Node {
public:
	CardBar();
	virtual ~CardBar();

	CREATE_FUNC(CardBar);

	bool init();

	void setPadding(const int& left, const int& top, const int& right, const int& bottom) {
		m_iPaddingLeft = left;
		m_iPaddingTop = top;
		m_iPaddingRight = right;
		m_iPaddingBottom = bottom;
	}

	void setCardsGap(const int& gap) {
		m_iGap = gap;
	}

	void setCardsFlag(uint16_t flag);

	Card* cloneCardAtLocation(Vec2 loc);
private:
	std::vector<Card*> m_vctBaseCards;
	std::vector<Card*> m_vctCards;

	int m_iPaddingLeft;
	int m_iPaddingRight;
	int m_iPaddingTop;
	int m_iPaddingBottom;
	int m_iGap;
};

#endif /* CARDBAR_H_ */
