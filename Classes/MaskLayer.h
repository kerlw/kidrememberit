/*
 * MaskLayer.h
 *
 *  Created on: 2015.09.14
 *      Author: kerlw
 */

#ifndef MASKLAYER_H_
#define MASKLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class MaskLayer : public LayerColor {
public:
	virtual ~MaskLayer();

	static MaskLayer* create(Color4B bkColor);

protected:
	MaskLayer();
};

class CountingDownMaskLayer : public MaskLayer {

};

#endif /* MASKLAYER_H_ */
