/*
 * GameScene.cpp
 *
 *  Created on: 2015.7.12
 *      Author: kerlw
 */

#include "GameScene.h"
#include "Const.h"
#include "GameController.h"
#include "Card.h"
#include "CardBar.h"
#include "Puzzle.h"

#include "ui/UIButton.h"

static const char* COUNTING_STRING[] = { "Ready~", "Go!" };
static const int GO_INDEX = 1;

const int GameScene::kMaxColumns = 7;

GameScene::GameScene()
		: m_pLabelCounting(nullptr), m_pCardBar(nullptr),
		  m_pSelectedCard(nullptr), m_pPuzzle(nullptr) {
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

GameScene::~GameScene() {
	CC_SAFE_RELEASE(m_pPuzzle);
}

bool GameScene::init() {
	if (!Layer::init())
		return false;

	auto director = Director::getInstance();
	auto pView = director->getOpenGLView();
	pView->setDesignResolutionSize(RESOLUTION_WIDTH, RESOLUTION_HEIGHT, ResolutionPolicy::SHOW_ALL);

	Size visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();

	m_pLabelCounting = Label::create();
	m_pLabelCounting->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(m_pLabelCounting);

	uint16_t score = UserDefault::getInstance()->getIntegerForKey("player"); //TODO player should be nickname of player
	auto data = PuzzleData::create(score);

	m_pPuzzle = Puzzle::create();
	CC_SAFE_RETAIN(m_pPuzzle);

	m_pPuzzle->setPuzzleData(data);

	if (!m_pPuzzle->generate()) {
		return false;	//TODO give out error tips.
	}

	m_vctCards.clear();
	for (int i = 0; i < data->size; i++) {
		m_vctCards.push_back(Card::create((Card::CardType)data->data[i], false));
	}

	// create CardBar
	m_pCardBar = CardBar::create();
	m_pCardBar->setCardsGap(10);
	m_pCardBar->setPadding(10, 10, 20, 20);
	m_pCardBar->setCardsFlag(data->getCardBitMask());
	m_pCardBar->setPosition(Vec2(visibleSize.width / 2, m_pCardBar->getContentSize().height / 2));
	m_pCardBar->setVisible(false);
	this->addChild(m_pCardBar);

	initGameBoardLayout(visibleSize.width, visibleSize.height);

	return true;
}

void GameScene::initGameBoardLayout(int w, int h) {
	int cardCounts = m_vctCards.size();
	int cols = cardCounts > kMaxColumns ? kMaxColumns : cardCounts;
	int rows = (cardCounts + kMaxColumns - 1) / kMaxColumns;

	auto card = m_vctCards.front();
	if (!card)
		return;

	const Size cardSize = card->getContentSize();

	int cellWidth = (w - 2 * cardSize.width) / cols;
	int cellHeight = (h - 2 * cardSize.height) / rows;

	int row = 0;
	for (int i = 0; i < m_vctCards.size(); i++) {
		int row = i / kMaxColumns;
		int col = i % kMaxColumns;
		int x = cardSize.width + cellWidth * col + cellWidth / 2;
		int y = h - (cardSize.height + cellHeight * row + cellWidth / 2);
		m_vctCards[i]->setPosition(Vec2(x, y));

		this->addChild(m_vctCards[i], -1);
	}
}

void GameScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();

	showStartCounting();
}

void GameScene::showStartCounting() {
	m_iCounter = 0;
	m_fTimeCounter = 0;
	m_pLabelCounting->setString(COUNTING_STRING[m_iCounter]);
	m_pLabelCounting->setSystemFontSize(300);
	schedule(schedule_selector(GameScene::startCountingCallback), 0.01f);
}

void GameScene::startCountingCallback(float tm) {
	if (!m_pLabelCounting)
		return;

	m_fTimeCounter += tm;
	if (m_fTimeCounter < 1.5f) {
		int index = (int) m_fTimeCounter;
		int size = ((int)(m_fTimeCounter * 100)) % 100 * 3;
//		log("tm is %f, index is %d, size is %d", m_fTimeCounter, index, size);
		if (index != m_iCounter) {
			m_iCounter = index;
			m_pLabelCounting->setString(COUNTING_STRING[m_iCounter]);
		}
		m_pLabelCounting->setSystemFontSize(320 - size);
	} else if (m_fTimeCounter <= 2.0f) {
		m_pLabelCounting->setString(COUNTING_STRING[GO_INDEX]);
		m_pLabelCounting->setSystemFontSize(300);
	} else {
		unschedule(schedule_selector(GameScene::startCountingCallback));
		m_pLabelCounting->removeFromParent();

		showGameBoard();
	}
}

void GameScene::showGameBoard() {
	for (int i = 0; i < m_vctCards.size(); i++) {
		m_vctCards[i]->flipCard();
	}

	auto data = m_pPuzzle->getPuzzleData();

	auto pt = ProgressTimer::create(Sprite::create("progressbar_fg.png"));
	pt->setType(kCCProgressTimerTypeBar);
	pt->setPosition(500, 30);
	pt->setPercentage(100.0f);
	pt->setMidpoint(Vec2(0, 0)); //- m_pProgressTimer->getContentSize().height / 2));
	pt->setBarChangeRate(Vec2(1, 0));

	this->addChild(pt, 1);

	auto sc = Director::getInstance()->getScheduler();
	sc->schedule([=](float delta) {
		static float totalDelta = 0;
		totalDelta += delta;
		float left = data->rem_time - totalDelta;
		if (left < 0)
			left = 0;
		pt->setPercentage(left * 100 / data->rem_time);

		if (left <= 0) {
			Director::getInstance()->getScheduler()->unschedule("tester", this);
			this->onRememberTimerDone(0.0f);
		}

	}, this, 0.1f, false, "tester");
}

void GameScene::onRememberTimerDone(float left) {
	//TODO flip cards or move cards out ??
	for (int i = 0; i < m_vctCards.size(); i++) {
		Card* card = m_vctCards[i];
		card->flipCard();
	}
	m_pCardBar->setVisible(true);
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
	Vec2 location = touch->getLocation();
	if (m_pCardBar) {
		auto card = m_pCardBar->cloneCardAtLocation(m_pCardBar->convertToNodeSpace(location));
		if (!card)
			return false;

		m_pSelectedCard = card;
		m_pSelectedCard->setPosition(location);
		this->addChild(m_pSelectedCard);
	}
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
	if (m_pSelectedCard) {
		m_pSelectedCard->setPosition(touch->getLocation());
	}
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {
	if (m_pSelectedCard) {
		this->removeChild(m_pSelectedCard);
	}
}
void GameScene::onTouchCancelled(Touch *touch, Event *unused_event) {
	if (m_pSelectedCard) {
		this->removeChild(m_pSelectedCard);
	}
}
