/*
 * Puzzle.cpp
 *
 *  Created on: 2015.09.14
 *      Author: kerlw
 */

#include "Puzzle.h"

#include <stdlib.h>
#include <algorithm>
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
	init(usr);
}

bool PuzzleData::init(const UserData* usr) {
	type = PuzzleType::PT_REMEMBER_AND_REPRESENT; //(PuzzleType) (usr->score / SCORE_RANK);

	size = 5 + usr->score / 8;
	card_types = 2 + usr->score % 8;
	card_types = std::min(std::max(card_types, (uint8_t)(size / 3)), size);
	if (size > 0) {
		data = new uint8_t[size];
		memset(data, 0, size);
	}

	rem_time = std::min(5.0f * size, size * (1 + 8 * ((float)(255 - usr->remember_time_factor)) / 255));
	rep_time = std::min(5.0f * size, size * (1 + 8 * ((float)(255 - usr->represent_time_factor)) / 255));

//	log("PuzzleData initialized : type %d, size %d, card_types %d, rem_time %f, rep_time %f",
//			type, size, card_types, rem_time, rep_time);
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

		m_pData->data[index] = types_v[i];
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
