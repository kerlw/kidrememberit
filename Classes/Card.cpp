/*
 * Card.cpp
 *
 *  Created on: 2015.08.18
 *      Author: kerlw
 */

#include "Card.h"

#include "Const.h"

Card* Card::create(const CardType& type, bool front) {
	Card *pRet = new (std::nothrow) Card();
	if (pRet && pRet->init(type, front)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

Card::Card()
	: m_pFront(nullptr), m_pBack(nullptr) {
}

Card::~Card() {
}

bool Card::init(const CardType& type, bool front) {
	auto cache = SpriteFrameCache::getInstance();
	m_pFront = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName(FRAME_NAME[FRAME_INDEX_CARD0]));
	m_pBack = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName(FRAME_NAME[FRAME_INDEX_CARD1]));
	if (type >= Card::CardType::CARD_MIN && type <= Card::CardType::CARD_MAX) {
		auto content = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName(FRAME_NAME[(int)type]));
		auto size = m_pFront->getContentSize();
		content->setPosition(Vec2(size.width / 2, size.height / 2));
		m_pFront->addChild(content);
	}

	m_bFront = front;
	if (front) {
		m_pFront->setVisible(true);
		m_pBack->setVisible(false);
	} else {
		m_pFront->setVisible(false);
		m_pBack->setVisible(true);
	}

	this->addChild(m_pFront);
	this->addChild(m_pBack);
	return true;
}

void Card::flipCard() {

}
