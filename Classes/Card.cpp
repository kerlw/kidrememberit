/*
 * Card.cpp
 *
 *  Created on: 2015.08.18
 *      Author: kerlw
 */

#include "Card.h"

#include "Const.h"

static const float kDuration = 0.8f;

#define kInAngleZ        270 //里面卡牌的起始同Z轴角度
#define kInDeltaZ        90  //里面卡牌旋转的同Z轴角度差
#define kOutAngleZ       0   //封面卡牌的起始同Z轴角度
#define kOutDeltaZ       90  //封面卡牌旋转的同Z轴角度差


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
	: m_pFront(nullptr), m_pBack(nullptr),
	  m_pAnimIn(nullptr), m_pAnimOut(nullptr),
	  m_bFront(false) {
}

Card::~Card() {
//	if (m_pFront) {
//		m_pFront->stopAllActions();
//	}
//
//	if (m_pBack) {
//		m_pBack->stopAllActions();
//	}

	if (m_pAnimIn)
		m_pAnimIn->release();
	if (m_pAnimOut)
		m_pAnimOut->release();
}

bool Card::init(const CardType& type, bool front) {
	m_eType = type;
	// set touch mode to ONE_BY_ONE
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(0.5, 0.5));

	// init front & back sprite
	auto cache = SpriteFrameCache::getInstance();
	m_pFront = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName(FRAME_NAME[FRAME_INDEX_CARD0]));
	m_pBack = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName(FRAME_NAME[FRAME_INDEX_CARD1]));
	Size size = m_pFront->getContentSize();
	this->setContentSize(size);

	m_pFront->setPosition(Vec2(size.width / 2, size.height / 2));
	m_pBack->setPosition(Vec2(size.width / 2, size.height / 2));

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

	// init animation
	m_pAnimIn = Sequence::create(DelayTime::create(kDuration / 2),
						Show::create(),
						OrbitCamera::create(kDuration / 2, 1, 0, kInAngleZ, kInDeltaZ, 0, 0),
						NULL);
	m_pAnimIn->retain();
	m_pAnimOut = Sequence::create(OrbitCamera::create(kDuration / 2, 1, 0, kOutAngleZ, kOutDeltaZ, 0, 0),
						Hide::create(),
						DelayTime::create(kDuration / 2),
						NULL);
	m_pAnimOut->retain();

	return true;
}

void Card::setClickable(bool enabled) {
	setTouchEnabled(enabled);
}

void Card::flipCard() {
	if (!m_pFront || !m_pBack)
		return;

//	m_pFront->stopAllActions();
//	m_pBack->stopAllActions();

	if (m_bFront) {
		m_pFront->runAction(m_pAnimOut);
		m_pBack->runAction(m_pAnimIn);
	} else {
		m_pFront->runAction(m_pAnimIn);
		m_pBack->runAction(m_pAnimOut);
	}
	m_bFront = (!m_bFront);
}

bool Card::onTouchBegan(Touch *touch, Event *unusedEvent) {
	Vec2 loc = touch->getLocationInView();
	Rect rt = this->getBoundingBox();

	return rt.containsPoint(loc);
}

void Card::onTouchMoved(Touch *touch, Event *unusedEvent) {
}

void Card::onTouchEnded(Touch *touch, Event *unusedEvent) {
	Vec2 startLoc = touch->getStartLocationInView();
	Vec2 loc = touch->getLocationInView();
	Rect rt = this->getBoundingBox();

	if (rt.containsPoint(startLoc) && rt.containsPoint(loc) &&
			(m_pAnimIn->getElapsed() == 0.0f || m_pAnimIn->isDone()) &&
			(m_pAnimOut->getElapsed() == 0.0f || m_pAnimOut->isDone()))
		this->flipCard();
}

void Card::onTouchCancelled(Touch *touch, Event *unusedEvent) {
}

Card* Card::clone() {
	return Card::create(m_eType, m_bFront);
}


//////////////////////////////////////////////////////////////////
//	CardSlot
//////////////////////////////////////////////////////////////////
CardSlot* CardSlot::create(const std::string& file) {
	CardSlot* pRet = new (std::nothrow) CardSlot();
	if (pRet && pRet->init(file)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool CardSlot::init(const std::string& file) {
	auto sp = ui::Scale9Sprite::create(file);
	if (!sp)
		return false;

	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->ignoreAnchorPointForPosition(false);

	sp->setCapInsets(Rect(20, 20, 10, 10));
	sp->setAnchorPoint(Vec2(0,0));
	sp->ignoreAnchorPointForPosition(false);
	sp->setPosition(Vec2(0, 0));

	m_pBg = sp;
	this->addChild(sp);
	return true;
}

void CardSlot::setContentSize(const Size & size) {
	Layer::setContentSize(size);
	if (m_pBg) {
		m_pBg->setPreferredSize(size);
		m_pBg->setPosition(Vec2(0, 0));
	}
}

void CardSlot::setCard(Card* card) {
	if (card == m_pCard)
		return;

	CC_SAFE_RETAIN(card);
	if (card)
		this->addChild(card);
	if (m_pCard)
		this->removeChild(m_pCard);
	CC_SAFE_RELEASE(m_pCard);

	m_pCard = card;

}
