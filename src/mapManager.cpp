#include "mapManager.h"

#pragma region Tile Assets
//-------------------------------
mapManager::tileAssets::tileAssets(string path, bool canPass)
	:_canPass(canPass)
{
	if (!_img.load(path))
	{
		ofLog(OF_LOG_ERROR, "[tileAssets::tileAssets]load image failed");
		return;
	}
	
}


//-------------------------------
void mapManager::tileAssets::draw(int x, int y, int unitW, int unitH)
{
	if (!_img.bAllocated())
	{
		return;
	}

	ofPushStyle();
	{
		ofSetColor(255);
		_img.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		_img.draw(x, y, unitW, unitH);
	}
	ofPopStyle();
}

//-------------------------------
bool mapManager::tileAssets::canPass()
{
	return _canPass;
}
#pragma endregion

#pragma region mapManager
//-------------------------------
mapManager::mapManager()
	:_centerIndex(cMapColsHalf, cMapRowsHalf)
	, _mainIndex(cMapColsHalf, cMapRowsHalf)
{
}

//-------------------------------
void mapManager::setup()
{
	_triggerGoBack = false;
	setupTileAssets();
	setupMiniMap(); 
	setupCover();
	reset();
}

//-------------------------------
void mapManager::update(float delta)
{
	updateCover(delta);
}

//-------------------------------
void mapManager::draw(int x, int y, int width, int height)
{
	int unitW = static_cast<int>(width / (float)cMapDisplayCols + 0.5f);
	int unitH = static_cast<int>(height / (float)cMapDisplayRows + 0.5f);
	ofPushMatrix();
	ofTranslate(x, y);
	ofPushStyle();
	ofSetMinMagFilters(GL_NEAREST, GL_NEAREST);
	ofSetColor(46, 49, 146);
	ofDrawRectangle(0, 0, width, height);

	ofVec2f pos(0);
	ofVec2f mapPos = _centerIndex;
	mapPos.x -= cMapDisplayColsHalf;
	mapPos.y -= cMapDisplayRowsHalf;

	for (int idY = 0; idY < cMapDisplayRows; idY++)
	{
		pos.x = 0;
		mapPos.x = _centerIndex.x - cMapDisplayColsHalf;
		for (int idX = 0; idX < cMapDisplayCols; idX++)
		{
			auto tile = _map[(int)mapPos.y][(int)mapPos.x];
			if (tile._type != eTileEmpty && tile._type != eTileTreasureReady)
			{
				_tileAssets[tile._type].draw(pos.x, pos.y, unitW, unitH);
			}

			//Main
			if (mapPos.x == _mainIndex.x && mapPos.y == _mainIndex.y)
			{
				_tileAssets[eTileMain].draw(pos.x, pos.y, unitW, unitH);
			}

			mapPos.x += 1;
			pos.x += unitW;
		}
		mapPos.y += 1;
		pos.y += unitH;
	}


	ofPopStyle();
	ofPopMatrix();
}

//-------------------------------
void mapManager::drawMini(int x, int y, int width, int height)
{
	ofPushStyle();
	ofSetColor(255);
	{
		_miniMap.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		_miniMap.draw(x, y, width, height);
	}
	ofPopStyle();
}

//-------------------------------
void mapManager::drawInfo(int x, int y)
{
	
	ofDrawBitmapStringHighlight("Main Position:(" + ofToString(_mainIndex.x) + "," + ofToString(_mainIndex.y) + ")", x, y);
}

//-------------------------------
void mapManager::reset()
{
	_centerIndex.set(cMapColsHalf, cMapRowsHalf);
	_mainIndex = _mainIndexTemp = _centerIndex;
	generateNewMaps();
	updateMiniMap();
	updateMiniMapMain();
}

//-------------------------------
void mapManager::moveMain(int moveX, int moveY)
{
	_mainIndexTemp = _mainIndex;
	ofVec2f newPos = _mainIndex;
	newPos.x += moveX;
	newPos.y += moveY;

	bool isUpdate = false;
	if (newPos.x < 0)
	{
		newPos.x = 0;
	}
	else if (newPos.x >= cMapCols)
	{
		newPos.x = cMapCols - 1;
	}
	else
	{
		isUpdate = true;
	}
	if (newPos.y < 0)
	{
		newPos.y = 0;
	}
	else if (newPos.y >= cMapRows)
	{
		newPos.y = cMapRows - 1;
	}
	else
	{
		isUpdate = true;
	}

	if (isUpdate)
	{
		if (checkMove(newPos))
		{
			_mainIndex = newPos;
			moveCenter(_mainIndex.x, _mainIndex.y);
			updateMiniMapMain();
		}
		else
		{
			eventCheck(newPos);
		}
		
	}
}

//-------------------------------
ofVec2f mapManager::getPos()
{
	return _centerIndex;
}

//-------------------------------
void mapManager::displayTreature(int id)
{
	auto iter = _treasure.find(id);
	if (iter != _treasure.end())
	{
		iter->second.isShow = true;
		_map[(int)iter->second.pos.y][(int)iter->second.pos.x]._type = eTileTreasure;
		updateMiniMap();
	}
}

//-------------------------------
void mapManager::goback()
{
	hide();
	_triggerGoBack = true;
}

//-------------------------------
void mapManager::moveCenter(int tx, int ty)
{
	if (ty - cMapDisplayRowsHalf < 0)
	{
		_centerIndex.y = cMapDisplayRowsHalf;
	}
	else if (ty + cMapDisplayRowsHalf >= cMapRows)
	{
		_centerIndex.y = cMapRows - cMapDisplayRowsHalf;
	}
	else
	{
		_centerIndex.y = ty;
	}

	if (tx - cMapDisplayColsHalf < 0)
	{
		_centerIndex.x = cMapDisplayColsHalf;
	}
	else if (tx + cMapDisplayColsHalf >= cMapCols)
	{
		_centerIndex.x = cMapCols - cMapDisplayColsHalf - 1;
	}
	else
	{
		_centerIndex.x = tx;
	}
}

//-------------------------------
void mapManager::setupTileAssets()
{
	
	tileAssets main("images/long.png", true);
	tileAssets star("images/bg.png", true);
	
	tileAssets meteorite1("images/stone01.png", false);
	tileAssets meteorite2("images/stone02.png", false);
	tileAssets treasure("images/chest.png", false);

	tileAssets artgital1("images/ian.png", false);
	tileAssets artgital2("images/stan.png", false);
	tileAssets artgital3("images/cater.png", false);
	tileAssets artgital4("images/tina.png", false);
	tileAssets artgital5("images/vader.png", false);
	tileAssets artgital6("images/yoncky.png", false);
	tileAssets artgital7("images/aka.png", false);
	tileAssets artgital8("images/ming.png", false);
	tileAssets artgital9("images/jackie.png", false);
	tileAssets artgital10("images/alvin.png", false);
	tileAssets artgital11("images/leoH.png", false);
	tileAssets artgital12("images/james.png", false);
	tileAssets artgital13("images/nora.png", false);
	tileAssets artgital14("images/jerry.png", false);
	tileAssets artgital15("images/will.png", false);
	tileAssets artgital16("images/jonathan.png", false);
	tileAssets artgital17("images/joey.png", false);
	tileAssets artgital18("images/leoC.png", false);

	_tileAssets[eTileStar] = star;
	_tileAssets[eTileMeteorite1] = meteorite1;
	_tileAssets[eTileMeteorite2] = meteorite2;
	_tileAssets[eTileTreasure] = treasure;
	_tileAssets[eTileArtgitalIan] = artgital1;
	_tileAssets[eTileArtgitalStan] = artgital2;
	_tileAssets[eTileArtgitalCater] = artgital3;
	_tileAssets[eTileArtgitalTina] = artgital4;
	_tileAssets[eTileArtgitalVader] = artgital5;
	_tileAssets[eTileArtgitalYoncky] = artgital6;
	_tileAssets[eTileArtgitalAka] = artgital7;
	_tileAssets[eTileArtgitalMing] = artgital8;
	_tileAssets[eTileArtgitalJackie] = artgital9;
	_tileAssets[eTileArtgitalAlvin] = artgital10;
	_tileAssets[eTileArtgitalLeoH] = artgital11;
	_tileAssets[eTileArtgitalJames] = artgital12;
	_tileAssets[eTileArtgitalNora] = artgital13;
	_tileAssets[eTileArtgitalJerry] = artgital14;
	_tileAssets[eTileArtgitalWill] = artgital15;
	_tileAssets[eTileArtgitalJonathan] = artgital16;
	_tileAssets[eTileArtgitalJoey] = artgital17;
	_tileAssets[eTileArtgitalLeoC] = artgital18;
	_tileAssets[eTileMain] = main;
}

//-------------------------------
void mapManager::generateNewMaps()
{
	ZeroMemory(_map, sizeof(tile) * cMapSize);

	//Create Border
	//Rows
	for (int ty = 0; ty < cMapRows; ty++)
	{
		_map[ty][0] = tile(eTileMeteorite1);
		_map[ty][cMapCols - 1] = tile(eTileMeteorite2);
	}

	//Cols
	for (int tx = 0; tx < cMapCols; tx++)
	{
		_map[0][tx] = tile(eTileMeteorite1);
		_map[cMapRows - 1][tx] = tile(eTileMeteorite2);
	}

	//Put Treasure And Artgital Man
	for (int i = 0; i < cMapTreasureType; i++)
	{
		auto pos1 = putObject(tile(eTileTreasureReady, i), ofRandom(cMapRandomMin, cMapRandomMax));
		auto pos2 = putObject(tile(eTileTreasureReady, i), ofRandom(cMapRandomMin, cMapRandomMax));
		_treasure[i] = treasure(pos1);
		_treasure[i + cMapTreasureType] = treasure(pos2);
	}

	putObject(tile(eTileArtgitalJackie, 0), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalAlvin, 1), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalLeoH, 2), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalJames, 3), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalNora, 4), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalJerry, 5), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalWill, 6), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalJonathan, 7), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalJoey, 8), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalLeoC, 9), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalIan, 10), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalStan, 11), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalCater, 12), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalTina, 13), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalVader, 14), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalYoncky, 15), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalAka, 16), ofRandom(cMapRandomMin, cMapRandomMax));
	putObject(tile(eTileArtgitalMing, 17), ofRandom(cMapRandomMin, cMapRandomMax));

	
	_map[(int)_centerIndex.y][(int)_centerIndex.x] = tile(eTilePath);
	//
	for (int ty = 1; ty < cMapRows - 1; ty++)
	{
		for (int tx = 1; tx < cMapCols - 1; tx++)
		{
			if (_map[ty][tx]._type != eTileEmpty && _map[ty][tx]._type != eTilePath)
			{
				continue;
			}

			int val;
			if (_map[ty][tx]._type == eTilePath)
			{
				val = rand() % 80;
			}
			else
			{
				val = rand() % 100;
			}
			
			if (val >= 0 && val < 40)
			{
				
				_map[ty][tx] = tile(eTileEmpty);
			}
			else if (val >= 40 && val < 80)
			{
				_map[ty][tx] = tile(eTileStar);
			}
			else if (val >= 80 && val < 90)
			{
				_map[ty][tx] = tile(eTileMeteorite1);
			}
			else if (val >= 90 && val < 100)
			{
				_map[ty][tx] = tile(eTileMeteorite2);
			}
		}
	}

	
}

//-------------------------------
bool mapManager::checkMove(ofVec2f newPos)
{
	auto type = _map[(int)newPos.y][(int)newPos.x]._type;
	
	return _tileAssets[type].canPass();
}

//-------------------------------
void mapManager::backtoCenter()
{
	_centerIndex.set(cMapColsHalf, cMapRowsHalf);
	_mainIndex = _mainIndexTemp = _centerIndex;
	updateMiniMap();
	updateMiniMapMain();
}

//-------------------------------
ofVec2f mapManager::putObject(tile obj, int dist)
{
	ofVec2f target(0, dist);
	bool isfound = false;
	while (true)
	{
		target.set(0, dist);
		target.rotate(ofRandom(0, 360));
		target += _centerIndex;
		target.x = static_cast<int>(target.x + 0.5f);
		target.y = static_cast<int>(target.y + 0.5f);

		if (_map[(int)target.y][(int)target.x]._type == eTileEmpty)
		{
			break;
		}
	}
	
	//Find path
	ofVec2f diff = target - _centerIndex;
	int deltaX = (diff.x >= 0 ? 1 : -1);
	int deltaY = (diff.y >= 0 ? 1 : -1);
	int count = abs(diff.x) + abs(diff.y);
	
	ofVec2f pos = _centerIndex;
	for (int i = 0; i < count; i++)
	{
		if (pos.x == target.x)
		{
			pos.y += deltaY;
		}
		else if (pos.y == target.y)
		{
			pos.x += deltaX;
		}
		else
		{
			if (rand() % 2 == 0)
			{
				pos.x += deltaX;
			}
			else
			{
				pos.y += deltaY;
			}
		}
		_map[(int)pos.y][(int)pos.x] = tile(eTilePath);
	}
	_map[(int)target.y][(int)target.x] = obj;
	return target;
}

#pragma endregion

#pragma region Cover
//-------------------------------
void mapManager::setupCover()
{
	_animCoverAlpha.setDuration(2.5);
	_animCoverAlpha.setRepeatType(AnimRepeat::PLAY_ONCE);
	_animCoverAlpha.reset(0);
	_isShow = true;
}

//-------------------------------
void mapManager::updateCover(float delta)
{
	_animCoverAlpha.update(delta);

	if (_animCoverAlpha.hasFinishedAnimating() && _animCoverAlpha.getPercentDone() == 1.0)
	{
		if (_animCoverAlpha.getCurrentValue() == 255.0 && _triggerGoBack)
		{
			backtoCenter();
			_triggerGoBack = false;
			show();
		}
	}
}

//-------------------------------
void mapManager::drawCover(int x, int y, int width, int height)
{
	ofPushStyle();
	ofSetColor(0, _animCoverAlpha.getCurrentValue());
	ofDrawRectangle(x, y, width, height);
	ofPopStyle();
}

//-------------------------------
void mapManager::show()
{
	_animCoverAlpha.animateFromTo(255, 0);
}

//-------------------------------
void mapManager::hide()
{
	_animCoverAlpha.animateFromTo(0, 255);
}
#pragma endregion

#pragma region MiniMap
//-------------------------------
void mapManager::setupMiniMap()
{
	if (!_miniMap.isAllocated())
	{
		_miniMap.allocate(cMapCols, cMapRows, ofImageType::OF_IMAGE_COLOR);
	}
}

//-------------------------------
void mapManager::updateMiniMap()
{
	ofPixelsRef pix = _miniMap.getPixelsRef();
	for (int ty = 0; ty < cMapRows; ty++)
	{
		for (int tx = 0; tx < cMapCols; tx++)
		{
			int index = (tx + ty * cMapCols) * 3;
			ofColor color = getMiniMapColor(_map[ty][tx]._type);
			pix[index] = color.r;
			pix[index + 1] = color.g;
			pix[index + 2] = color.b;
		}
	}
	_miniMap.update();
}

//-------------------------------
void mapManager::updateMiniMapMain()
{
	int preIndex = (_mainIndexTemp.x + _mainIndexTemp.y * cMapCols) * 3;
	int nowIndex = (_mainIndex.x + _mainIndex.y * cMapCols) * 3;
	ofColor preColor = getMiniMapColor(_map[(int)_mainIndexTemp.y][(int)_mainIndexTemp.x]._type);
	ofColor nowColor(255);

	ofPixelsRef pix = _miniMap.getPixelsRef();
	pix[preIndex] = preColor.r;
	pix[preIndex + 1] = preColor.g;
	pix[preIndex + 2] = preColor.b;

	pix[nowIndex] = nowColor.r;
	pix[nowIndex + 1] = nowColor.g;
	pix[nowIndex + 2] = nowColor.b;

	_miniMap.update();
}

//-------------------------------
ofColor mapManager::getMiniMapColor(eTileType type)
{
	ofColor result;
	switch (type)
	{
	case eTileTreasure:
	{
		result = ofColor::yellow;
		break;
	}
	case eTileArtgitalJackie:
	case eTileArtgitalAlvin:
	case eTileArtgitalLeoH:
	case eTileArtgitalJames:
	case eTileArtgitalNora:
	case eTileArtgitalJerry:
	case eTileArtgitalWill:
	case eTileArtgitalJonathan:
	case eTileArtgitalJoey:
	case eTileArtgitalLeoC:
	case eTileArtgitalIan:
	case eTileArtgitalStan:
	case eTileArtgitalCater:
	case eTileArtgitalTina:
	case eTileArtgitalVader:
	case eTileArtgitalYoncky:
	case eTileArtgitalAka:
	case eTileArtgitalMing:
	{
		result = ofColor::red;
		break;
	}
	default:
	{
		result = ofColor::black;
		break;
	}
	}
	return result;
}

//-------------------------------
void mapManager::eventCheck(ofVec2f pos)
{
	auto tile = _map[(int)pos.y][(int)pos.x];
	
	switch (tile._type)
	{
	case eTileTreasure:
	{
		ofNotifyEvent(treasureEvent, tile._tileID, this);
		break;
	}
	case eTileArtgitalJackie:
	case eTileArtgitalAlvin:
	case eTileArtgitalLeoH:
	case eTileArtgitalJames:
	case eTileArtgitalNora:
	case eTileArtgitalJerry:
	case eTileArtgitalWill:
	case eTileArtgitalJonathan:
	case eTileArtgitalJoey:
	case eTileArtgitalLeoC:
	case eTileArtgitalIan:
	case eTileArtgitalStan:
	case eTileArtgitalCater:
	case eTileArtgitalTina:
	case eTileArtgitalVader:
	case eTileArtgitalYoncky:
	case eTileArtgitalAka:
	case eTileArtgitalMing:
	{
		ofNotifyEvent(artgitalEvent, tile._tileID, this);
		break;
	}
	}
}
#pragma endregion
