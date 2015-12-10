/*
 * Puzzle.cpp
 *
 *  Created on: 2015.09.14
 *      Author: kerlw
 */

#include "Puzzle.h"

#include <stdlib.h>
#include "Const.h"
#include "UserData.h"

#define SCORE_RANK  80

PuzzleData *PuzzleData::create(const UserData* usr) {
	PuzzleData *pRet = new (std::nothrow) PuzzleData();
	if (pRet && pRet->init(usr)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void PuzzleData::resetUserData(const UserData* usr) {
//	this->score = score;
}

bool PuzzleData::init(const UserData* usr) {
	type = PuzzleType::PT_REMEMBER_AND_REPRESENT; //(PuzzleType) (usr->score / SCORE_RANK);

	size = 5 + usr->score / 8;
	card_types = 2 + usr->score % 8;
	if (size > 0) {
		data = new uint8_t[size];
		memset(data, 0, size);
	}

	rem_time = 5.0f * size;
	rep_time = 5.0f * size;
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

	std::set<uint8_t> types;
	std::vector<uint8_t> types_v;
	for (int i = 0; i < m_pData->card_types; ) {
		uint8_t type = rand() % CARD_TYPE_COUNT;
		if (types.find(type) != types.end())
			continue;

		types.insert(type);
		types_v.push_back(type);
		i++;
	}

	std::set<int> indexes;
	for (int i = 0; i < m_pData->card_types; ) {
		int index = rand() % m_pData->size;
		if (indexes.find(index) != indexes.end())
			continue;

		m_pData->data[i] = types_v[i];
		indexes.insert(index);
		i++;
	}

	for (int i = 0; i < m_pData->size; i++) {
		if (indexes.find(i) != indexes.end())
			continue;
		m_pData->data[i] = types_v[(rand() % m_pData->card_types)];
	}
	return true;
}
