/*
 * Puzzle.cpp
 *
 *  Created on: 2015.09.14
 *      Author: kerlw
 */

#include "Puzzle.h"

#include <stdlib.h>
#include "Const.h"

#define SCORE_RANK  100

PuzzleData *PuzzleData::create(const uint16_t& score) {
	PuzzleData *pRet = new (std::nothrow) PuzzleData();
	if (pRet && pRet->init(score)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void PuzzleData::resetScore(const uint16_t& score) {
//	this->score = score;
}

bool PuzzleData::init(const uint16_t& score) {
	this->type = (PuzzleType) (score / SCORE_RANK);

	//TODO size, rem_time, rep_time should be dynamic calculated
	this->size = 5 + score / 15;
	if (this->size > 0) {
		this->data = new uint8_t[this->size];
		memset(this->data, 0, size);
	}

	this->rem_time = 5.0f * this->size;
	this->rep_time = 5.0f * this->size;
	return true;
}

Puzzle::Puzzle() : m_pData(nullptr) {
}

Puzzle::~Puzzle() {
	CC_SAFE_RELEASE(m_pData);
}


bool Puzzle::generate() {
	if (!m_pData)
		return false;

	for (int i = 0; i < m_pData->size; i++)
		m_pData->data[i] = rand() % CARD_TYPE_COUNT;

	return true;
}
