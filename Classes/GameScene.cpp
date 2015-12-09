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
#include "ui/UIScale9Sprite.h"

static const char* COUNTING_STRING[] = { "READY", "GO!" };
static const int GO_INDEX = 1;

const int GameScene::kMaxColumns = 7;

GameScene::GameScene()
		: m_pLabelCounting(nullptr), m_pProgressTimer(nullptr), m_pCardBar(nullptr),
		  m_pSelectedCard(nullptr), m_pPuzzle(nullptr), m_eTimerType(UNKNONW_TIMER) {
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

GameScene::~GameScene() {
	this->unscheduleAllSelectors();
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

	//back menu item
    auto backItem = MenuItemImage::create("back0.png", "back1.png",
                                           CC_CALLBACK_1(GameScene::menuBackCallback, this));

	backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width/2 + 10,
                                origin.y + visibleSize.height - 10 - backItem->getContentSize().height/2));


    // create menu, it's an autorelease object
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	uint16_t score = UserDefault::getInstance()->getIntegerForKey("player"); //TODO player should be nickname of player
	auto data = PuzzleData::create(score);

	m_pPuzzle = Puzzle::create();
	CC_SAFE_RETAIN(m_pPuzzle);

	m_pPuzzle->setPuzzleData(data);

	if (!m_pPuzzle->generate()) {
		return false;	//TODO give out error tips.
	}

	// create count down timer progress bar, TODO : create a new ProgressBar class
	m_pProgressTimer = ProgressTimer::create(Sprite::create("progressbar_fg.png"));
	m_pProgressTimer->setType(kCCProgressTimerTypeBar);
	m_pProgressTimer->setPosition(visibleSize.width / 2, visibleSize.height - m_pProgressTimer->getContentSize().height);
	m_pProgressTimer->setPercentage(100.0f);
	m_pProgressTimer->setMidpoint(Vec2(0, 0));
	m_pProgressTimer->setBarChangeRate(Vec2(1, 0));
	m_pProgressTimer->setVisible(false);
	this->addChild(m_pProgressTimer, 1);

	// create CardBar
	m_pCardBar = CardBar::create();
	m_pCardBar->setCardsGap(10);
	m_pCardBar->setPadding(10, 10, 20, 20);
	m_pCardBar->setCardsFlag(data->getCardBitMask());
	m_pCardBar->setPosition(Vec2(visibleSize.width / 2, 0));
	m_pCardBar->setVisible(false);
	this->addChild(m_pCardBar);

	initGameBoardLayout(visibleSize.width, visibleSize.height);

	m_pLabelCounting = Label::create();
	m_pLabelCounting->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(m_pLabelCounting);

	return true;
}

void GameScene::menuBackCallback(Ref* pSender) {
	GameController::getInstance()->leaveScene();
}

void GameScene::initGameBoardLayout(int w, int h) {
	m_vctCards.clear();
	m_vctSlots.clear();
	m_bInRepresentStage = false;

	if (!m_pPuzzle || !m_pPuzzle->getPuzzleData())
		return;

	auto data = m_pPuzzle->getPuzzleData();
	int cardCounts = data->size;
	int cols = cardCounts > kMaxColumns ? kMaxColumns : cardCounts;
	int rows = (cardCounts + kMaxColumns - 1) / kMaxColumns;

	// create a tmp card to calculate layout parameters
	auto tmpCard = Card::create(Card::CardType::CARD_MIN, false);
	const Size cardSize = tmpCard->getContentSize();

	int cellWidth = (w - 2 * cardSize.width) / cols;
	int cellHeight = (h - 2 * cardSize.height) / rows;

	for (int i = 0; i < cardCounts; i++) {
		auto card = Card::create((Card::CardType)data->data[i], false);

		int row = i / kMaxColumns;
		int col = i % kMaxColumns;
		int x = cardSize.width + cellWidth * col + cellWidth / 2;
		int y = h - (cardSize.height + cellHeight * row + cellWidth / 2);

		auto slot = CardSlot::create("slot.png");
		slot->setPosition(Vec2(x, y));
		slot->setContentSize((cardSize + Size(5, 5)));
		m_vctSlots.push_back(slot);
		this->addChild(slot);

		card->setPosition(Vec2(x, y));
		m_vctCards.push_back(card);
		this->addChild(card);
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
	m_eTimerType = READYGO_TIMER;
	schedule(schedule_selector(GameScene::startCountingCallback), 0.01f);

//	// another way to implements the start counting animation
//	m_pLabelCounting->runAction(Sequence::create(ScaleTo::create(1, 0),
//				CallFunc::create([this](){
//					m_pLabelCounting->setString(COUNTING_STRING[GO_INDEX]);
//				}),
//				ScaleTo::create(1, 1),
//				CallFunc::create([this](){
//					m_pLabelCounting->removeFromParent();
//					this->showGameBoard();
//				}),
//				nullptr));
}

void GameScene::startCountingCallback(float delta) {
	if (!m_pLabelCounting)
		return;

	if (m_eTimerType != READYGO_TIMER) {
		this->unschedule(schedule_selector(GameScene::startCountingCallback));
		return;
	}

	m_fTimeCounter += delta;
	if (m_fTimeCounter <= 1.0f) {
//		int index = (int) m_fTimeCounter;
		int size = ((int)(m_fTimeCounter * 100)) % 100 * 3;
//		if (index != m_iCounter) {
//			m_iCounter = index;
//			m_pLabelCounting->setString(COUNTING_STRING[m_iCounter]);
//		}
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

void GameScene::countdownTimerCallback(float delta) {
	if (!m_pProgressTimer)
		return;

	if (m_eTimerType != REMEMBER_TIMER && m_eTimerType != REPRESENT_TIMER) {
		this->unschedule(schedule_selector(GameScene::countdownTimerCallback));
		return;
	}

	m_fTimeCounter += delta;
	auto data = m_pPuzzle->getPuzzleData();

	// set total & callback according to timer type
	float total = 0;
	SEL_SCHEDULE callback = nullptr;
	switch (m_eTimerType) {
	case REMEMBER_TIMER:
		total = data->rem_time;
		callback = schedule_selector(GameScene::onRememberTimerDone);
		break;
	case REPRESENT_TIMER:
		callback = schedule_selector(GameScene::onRepresentTimerDone);
		total = data->rep_time;
		break;
	}

	float left = total - m_fTimeCounter;
	if (left < 0)
		left = 0;
	// set percentage of progress bar
	m_pProgressTimer->setPercentage(left * 100 / total);

	if (left <= 0) {	// count down timer done
		if (callback)
			(this->*callback)(0.0f);	//!!!DONT use scheduleOnce!!!
		else
			this->unschedule(schedule_selector(GameScene::countdownTimerCallback));
	}
}

void GameScene::showGameBoard() {
	for (int i = 0; i < m_vctCards.size(); i++) {
		m_vctCards[i]->flipCard();
	}

	auto data = m_pPuzzle->getPuzzleData();

	// show count down timer progress bar
	m_pProgressTimer->setPercentage(100.0f);
	m_pProgressTimer->setVisible(true);

	m_eTimerType = REMEMBER_TIMER;
	m_fTimeCounter = 0.0f;
	this->schedule(schedule_selector(GameScene::countdownTimerCallback), 0.1f);
}

void GameScene::onRememberTimerDone(float left) {
	// stop count down timer
	this->unschedule(schedule_selector(GameScene::countdownTimerCallback));
	m_eTimerType = UNKNONW_TIMER;

	m_pProgressTimer->setVisible(false);

	for (int i = 0; i < m_vctCards.size(); i++) {
		Card* card = m_vctCards[i];
		card->runAction(MoveTo::create(0.8, Vec3(-100, 800, 10)));
	}

	m_pCardBar->setAnchorPoint(Vec2(0.5, 0));
	m_pCardBar->setRotation3D(Vec3(270, 0, 0));
	m_pCardBar->setVisible(true);

	// show CardBar then start represent-stage's timer
	m_pCardBar->runAction(Sequence::create(RotateBy::create(1, Vec3(90, 0, 0)),
			CallFunc::create([this](){
				m_pProgressTimer->setPercentage(100.0f);
				m_pProgressTimer->setVisible(true);
				m_eTimerType = REPRESENT_TIMER;
				m_fTimeCounter = 0.0f;
				m_bInRepresentStage = true;
				this->schedule(schedule_selector(GameScene::countdownTimerCallback), 0.1f);
			}),
			nullptr));
}

void GameScene::onRepresentTimerDone(float left) {
	m_bInRepresentStage = false;

	// stop count down timer
	this->unschedule(schedule_selector(GameScene::countdownTimerCallback));
	m_eTimerType = UNKNONW_TIMER;

	if (left < 0)
		left = 0;
	//TODO calculate score
//	auto dlg = DialogBuilder::create(this, this)->setPadding(80, 100, 80, 180)
//			->setPositiveButton("OK", "")->setNegativeButton("Cancel", "")->build();
//
//	if (dlg)
//		dlg->show();
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
	if (!m_bInRepresentStage)
		return false;

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
	if (!m_bInRepresentStage)
		return;

	if (m_pSelectedCard) {
		m_pSelectedCard->setPosition(touch->getLocation());
	}
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {
	if (!m_bInRepresentStage || !m_pSelectedCard)
		return;

	CC_SAFE_RETAIN(m_pSelectedCard);
	// remove the selected card from scene at first.
	this->removeChild(m_pSelectedCard);

	Vec2 location = touch->getLocation();
	bool done = true;
	bool found = false;
	for (int i = 0; i < m_vctSlots.size(); i++) {
		if (!found && m_vctSlots[i]->hitTest(location)) {
			m_vctSlots[i]->setCard(m_pSelectedCard);
			found = true;
		}

		if (done && !m_vctSlots[i]->getCard())
			done = false;
	}
	CC_SAFE_RELEASE(m_pSelectedCard);

	if (done) {
		this->onRepresentTimerDone(m_pPuzzle->getPuzzleData()->rep_time - m_fTimeCounter);
	}
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event) {
	if (m_pSelectedCard) {
		this->removeChild(m_pSelectedCard);
	}
}

void GameScene::onDialogButtonClicked(Dialog* dlg, const DialogButtonType& which) {
	log("onDialogButtonClicked %p %d", dlg, (int)which);
	dlg->dismiss();
}

void GameScene::onDialogDismissed(Dialog* dlg) {
	log("onDialogDissmissed %p", dlg);
}
