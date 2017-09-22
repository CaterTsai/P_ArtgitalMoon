#pragma once

#include "constParameter.h"

enum eTileType : int
{
	eTileBackground = 0
	, eTileStar
	, eTileBackgroundMax

	, eTileObstacle = 50
	, eTileMeteorite
	, eTileObstacleMax

	, eTileObject = 100
	, eTileTreasure1
	, eTileTreasure2
	, eTileTreasure3
	, eTileTreasure4
	, eTileTreasure5
	, eTileTreasure6
	, eTileTreasure7
	, eTileTreasure8
	, eTileTreasure9
	, eTileTreasure10
	, eTileArtgital1
	, eTileArtgital2
	, eTileArtgital3
	, eTileArtgital4
	, eTileArtgital5
	, eTileArtgital6
	, eTileArtgital7
	, eTileArtgital8
	, eTileArtgital9
	, eTileArtgital10
	, eTileArtgital11
	, eTileArtgital12
	, eTileArtgital13
	, eTileArtgital14
	, eTileArtgital15
	, eTileArtgital16
	, eTileObjectMax
};

class mapManager
{
#pragma region Tile
private:
	class tile
	{
	public:
		tile();
		void load(string path, bool isRotate, bool canPass);
		void draw(int x, int y, int unitSize);

	private:
		bool _isRotate, _canPass;
		int _cols, _rows;
		ofImage _img;
	};
#pragma endregion

public:
	mapManager();
	void setup();
	void draw(int x, int y, int width, int height);
	void reset();
	void moveCenter(int x, int y);

private:
	void loadTiles();
	void generateNewMaps();

private:
	ofVec2f _centerIndex;
	map<eTileType, tile> _tiles;
	array<tile, cMapSize> _map;
};