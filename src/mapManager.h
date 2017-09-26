#pragma once

#include "constParameter.h"
#include "ofxAnimatableFloat.h"
enum eTileType : int
{
	eTileEmpty = 0
	,eTilePath
	//Main
	,eTileMain

	//Background
	,eTileStar
	
	//Obstacle
	, eTileMeteorite1
	, eTileMeteorite2
	
	//Object
	, eTileTreasureReady
	, eTileTreasure

	, eTileArtgitalJackie
	, eTileArtgitalAlvin
	, eTileArtgitalLeoH
	, eTileArtgitalJames
	, eTileArtgitalNora
	, eTileArtgitalJerry
	, eTileArtgitalWill
	, eTileArtgitalJonathan
	, eTileArtgitalJoey
	, eTileArtgitalLeoC
	, eTileArtgitalIan
	, eTileArtgitalStan
	, eTileArtgitalCater
	, eTileArtgitalTina
	, eTileArtgitalVader
	, eTileArtgitalYoncky
	, eTileArtgitalAka
	, eTileArtgitalMing

	
	
};

class mapManager
{
#pragma region Tile Assets
private:
	class tileAssets
	{
	public:
		tileAssets() {};
		tileAssets(string path, bool canPass);
		void draw(int x, int y, int unitW, int unitH);
		
		bool canPass();
	private:
		bool _canPass;
		ofImage _img;
	};

	struct tile
	{
		tile()
			:_tileID(-1)
			,_type(eTileEmpty)
		{}

		tile(eTileType type, int id = -1)
			:_tileID(id)
			, _type(type)
		{}
		int _tileID;
		eTileType _type;
	};

#pragma endregion

private:
	struct treasure
	{
		treasure()
			:pos(0)
			,isShow(false)
			, whoFound("")
		{}
		treasure(ofVec2f p)
			:pos(p)
			,isShow(false)
			,whoFound("")
		{}
		ofVec2f pos;
		bool isShow;
		string whoFound;
	};

public:
	mapManager();
	void setup();
	void update(float delta);
	void draw(int x, int y, int width, int height);
	void drawMini(int x, int y, int width, int height);
	void drawInfo(int x, int y);
	void reset();
	void moveMain(int moveX, int moveY);
	
	ofVec2f getPos();
	void displayTreature(int id);
	void goback();

private:
	void moveCenter(int tx, int ty);
	void setupTileAssets();
	void generateNewMaps();
	bool checkMove(ofVec2f newPos);
	void backtoCenter();
	ofVec2f putObject(tile type, int dist);

private:
	bool _triggerGoBack;
	ofVec2f _mainIndex, _mainIndexTemp;
	ofVec2f _centerIndex;
	map<eTileType, tileAssets> _tileAssets;
	map<int, treasure> _treasure;
	tile _map[cMapRows][cMapCols];


#pragma region Cover
public:
	void drawCover(int x, int y, int width, int height);
private:
	void setupCover();
	void updateCover(float delta);
	
	void show();
	void hide();

private:
	bool _isShow;
	ofxAnimatableFloat	_animCoverAlpha;
#pragma endregion

	

#pragma region MiniMap
private:
	void setupMiniMap();
	void updateMiniMap();
	void updateMiniMapMain();
	ofColor getMiniMapColor(eTileType type);

private:
	ofImage		_miniMap;
#pragma endregion
	
#pragma region Event
private:
	void eventCheck(ofVec2f pos);
public:
	ofEvent<int> artgitalEvent;
	ofEvent<int> treasureEvent;
#pragma endregion

	
};