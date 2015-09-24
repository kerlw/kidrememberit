/*
 * CardBar.cpp
 *
 *  Created on: 2015.09.24
 *      Author: kerlw
 */

#include "CardBar.h"

#include "Card.h"

CardBar::CardBar() : m_iPaddingLeft(0), m_iPaddingRight(0),
		m_iPaddingTop(0), m_iPaddingBottom(0), m_iGap(0) {
}

CardBar::~CardBar() {
	m_vctCards.clear();
	removeAllChildren();

	for (int i = 0; i < m_vctBaseCards.size(); i++) {
		CC_SAFE_RELEASE(m_vctBaseCards[i]);
	}
}

bool CardBar::init() {
	for (int i = (int) Card::CardType::CARD_MIN; i <= (int) Card::CardType::CARD_MAX; i++) {
		auto card = Card::create((Card::CardType)i, true);
		CC_SAFE_RETAIN(card);
		m_vctBaseCards.push_back(card);
	}

	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->ignoreAnchorPointForPosition(false);

	return true;
}

void CardBar::setCardsFlag(uint16_t flag) {
	for (int i = 0; i < m_vctCards.size(); i++)
		this->removeChild(m_vctCards[i]);

	m_vctCards.clear();

	for (int i = (int) Card::CardType::CARD_MIN; i <= (int) Card::CardType::CARD_MAX; i++) {
		uint16_t mask = 1 << i;
		if ((flag & mask)) {
			m_vctCards.push_back(m_vctBaseCards[i]);
		}
	}

	Size cardSize = m_vctBaseCards.front()->getContentSize();
	int count = m_vctCards.size();
	for (int i = 0; i < count; i++) {
		auto card = m_vctCards[i];
		card->setPosition(Vec2(m_iPaddingLeft + i * (cardSize.width + m_iGap) + cardSize.width / 2,
				m_iPaddingBottom + cardSize.height / 2));
		this->addChild(card);
	}
	this->setContentSize(Size(m_iPaddingLeft + m_iPaddingRight + count * (cardSize.width + m_iGap) - m_iGap,
			m_iPaddingTop + m_iPaddingBottom + cardSize.height));
}

Card* CardBar::cloneCardAtLocation(Vec2 loc) {
	for (int i = 0; i < m_vctCards.size(); i++) {
		auto card = m_vctCards[i];
		Vec2 pos = card->getPosition();
		Size size = card->getContentSize();
		Rect rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
		if (rect.containsPoint(loc))
			return card->clone();
	}
	return nullptr;
}
