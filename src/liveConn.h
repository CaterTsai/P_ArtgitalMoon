#pragma once

#include <locale>         // std::wstring_convert
#include <codecvt>        // std::codecvt_utf8
#include <cstdint>        // std::uint_least32_t
#include "ofxHttpUtils.h"
#include "json.h"

#include "constParameter.h"
#include "command.h"

class liveConn
{
public:
	liveConn();
	~liveConn();
	void update(float delta);
	command getCommand();

	void start();
	void stop();
	
private:
	void decodeCommand(Json::Value& value);
	eCommand getType(string& msg);

private:
	bool _isStart;
	float _timer;
	list<command> _commList;
	map<string, eCommand> _commMgr;
	string _lastTime;

//-------------------------------
//Http Request
public:
	void getNewComm();

private:
	void httpRespone(ofxHttpResponse& e);

private:
	ofxHttpUtils _fbConn;
};