#include "mapManager.h"

#pragma region Tile
//-------------------------------
mapManager::tile::tile()
	:_isRotate(false)
	, _canPass(true)
	, _cols(1)
	, _rows(1)
{
}

//-------------------------------
void mapManager::tile::load(string path, bool isRotate, bool canPass)
{
	_isRotate = isRotate;
	_canPass = canPass;
	if (_img.load(path))
	{
		ofLog(OF_LOG_ERROR, "[tile::load]load image failed");
		return;
	}


}

//-------------------------------
void mapManager::tile::draw(int x, int y, int unitSize)
{
	if (_img.bAllocated())
	{

	}
}
#pragma endregion

#pragma region mapManager
//-------------------------------
mapManager::mapManager()
{
}

//-------------------------------
void mapManager::setup()
{
}

//-------------------------------
void mapManager::draw(int x, int y, int width, int height)
{
}

//-------------------------------
void mapManager::reset()
{
}

//-------------------------------
void mapManager::moveCenter(int x, int y)
{
}

//-------------------------------
void mapManager::loadTiles()
{
}

//-------------------------------
void mapManager::generateNewMaps()
{
}
#pragma endregion


