#pragma once

#include "ofMain.h"

enum eArtgitalCharacter : int
{
	artgitalJackie = 0
	, artgitalAlvin
	, artgitalLeoH
	, artgitalJames
	, artgitalNora
	, artgitalJerry
	, artgitalWill
	, artgitalJonathan
	, artgitalJoey
	, artgitalLeoC
	, artgitalIan
	, artgitalStan
	, artgitalCater
	, artgitalTina
	, artgitalVader
	, artgitalYoncky
	, artgitalAka
	, artgitalMing
	, artgitalDefault
};


//live Connector
const string cFBToken = "EAAEVUYcZAg7EBAB98I5VCk2ZCmt3qqyhxCZBkTKUidPkpN4lOwye7AdyW4ZAaYiRfhZABoEE6LoQHF9m1aC9Usm0jbLP1SokOpSKL3tf9DVy7MnVkOKOUXUlZA0Ka3kiJsnwvaJHl9oFSsH1cm1kFc02l1Q2Gbovqd9XtwgwSUE3b3PSJ8qlK6EZAKIUSpWdY74vLWj13YcUHk2IXXbZBpso5LxCVGaQpgWZAfd2g4z1uYHKxl10HmVKF";
const string cLiveID = "2035897596427733";
const string cFBUrl = "https://graph.facebook.com/v2.10/";
const string cAction = "/comments";

const float cGetNewDataTime = 1.0f; //s

//map
const int cMapWidth = 1320;
const int cMapHeight = 960;
const int cMapMiniWidth = 300;
const int cMapMiniHeight = 300;
const ofVec2f cMapPosition(0, 0);
const ofVec2f cMapMiniPosition(0, cMapHeight - cMapMiniHeight);
const int cMapRows = 101;
const int cMapCols = 101;
const int cMapRowsHalf = (int)floor(cMapRows / 2.0);
const int cMapColsHalf = (int)floor(cMapCols / 2.0);
const int cMapSize = cMapRows * cMapCols;
const int cMapDisplayRows = 8;
const int cMapDisplayCols = 11;
const int cMapDisplayRowsHalf = (int)floor(cMapDisplayRows / 2.0);
const int cMapDisplayColsHalf = (int)floor(cMapDisplayCols / 2.0);

const int cMapRandomMax = MIN(cMapColsHalf, cMapRowsHalf);
const int cMapRandomMin = MAX(cMapDisplayCols, cMapDisplayRows);

const int cMapUnitWidth = (int)((float)cMapWidth / cMapDisplayCols);
const int cMapUnitHeight = (int)((float)cMapHeight / cMapDisplayRows);

const int cMapTreasureType = 5;

//Message
const float cMessageDisplayTime = 5.0;