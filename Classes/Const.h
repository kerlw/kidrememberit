/*
 * Const.h
 *
 *  Created on: 2015年5月22日
 *      Author: kerlw
 */

#ifndef CONST_H_
#define CONST_H_

static const char* KEYNAME_EXTERNAL_DATA_PATH = "external_data_path";

static const float RESOLUTION_WIDTH = 1280.0f;

static const float RESOLUTION_HEIGHT = 720.0f;

static const char* RES_FILE_PLIST = "rememberit.plist";

static const char* RES_FILE_PNG = "rememberit.png";

static const char* const FRAME_NAME[] = {
		"1.png", "2.png", "3.png", "4.png", "5.png", "6.png", "7.png", "8.png",
		"9.png", "card0.png", "card1.png"
	};

static const int FRAME_INDEX_CARD0 = 9;
static const int FRAME_INDEX_CARD1 = 10;

static const int CARD_TYPE_COUNT = 9;

#endif /* CONST_H_ */
