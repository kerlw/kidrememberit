/*
 * Puzzle.h
 *
 *  Created on: 2015.09.14
 *      Author: kerlw
 */

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include "cocos2d.h"

USING_NS_CC;

class Puzzle : public Ref {
public:
	enum class PuzzleType {

	};

	virtual ~Puzzle();

	bool init();

	CREATE_FUNC(Puzzle);

	void generate(const PuzzleType& type, void* param);

private:
	Puzzle();

private:
	PuzzleType m_type;

	void* m_pData;

};

#endif /* PUZZLE_H_ */
