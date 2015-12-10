/*
 * Puzzle.h
 *
 *  Created on: 2015.09.14
 *      Author: kerlw
 */

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include "cocos2d.h"

#include <stdint.h>

USING_NS_CC;

class UserData;

enum class PuzzleType {
	PT_REMEMBER_AND_REPRESENT = 0,
	PT_REMEMBER_AND_PAIREFLIP = 1,
};

class PuzzleData : public Ref {
public:
	virtual ~PuzzleData() {
		if (data)
			delete data;
	}

	static PuzzleData* create(const UserData* usr);
	void resetUserData(const UserData* usr);

	uint16_t getCardBitMask() {
		uint16_t ret = 0;
		for (int i = 0; i < size; i++) {
			ret |= (1 << data[i]);
		}
		return ret;
	}

private:
	bool init(const UserData* usr);
	PuzzleData() : data(nullptr) {}

public:
	PuzzleType type;
	uint8_t size;
	uint8_t card_types;
	uint8_t *data;
	float rem_time;
	float rep_time;
	const UserData* usr;
};


class Puzzle : public Ref {
public:

	virtual ~Puzzle();

	CREATE_FUNC(Puzzle);
	bool init() {
		return true;
	}

	void setPuzzleData(PuzzleData *data) {
		m_pData = data;
		CC_SAFE_RETAIN(m_pData);
	}

	PuzzleData* getPuzzleData() {
		return m_pData;
	}

	bool generate();

private:
	Puzzle();

private:
	PuzzleData* m_pData;

};

#endif /* PUZZLE_H_ */
