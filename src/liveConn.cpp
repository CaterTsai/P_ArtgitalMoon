#include "liveConn.h"

liveConn::liveConn()
	:_lastTime("")
	, _timer(0.0)
	, _isStart(false)
{
	ofAddListener(_fbConn.newResponseEvent, this, &liveConn::httpRespone);
	_fbConn.start();
	string up = ws2s(L"¤¤");
	string down = ws2s(L"¬î");
	string left = ws2s(L"§Ö");
	string right = ws2s(L"¼Ö");
	_commMgr.insert(make_pair(up, eCommand::eCommUp));
	_commMgr.insert(make_pair(down, eCommand::eCommDown));
	_commMgr.insert(make_pair(left, eCommand::eCommLeft));
	_commMgr.insert(make_pair(right, eCommand::eCommRight));
	
}

//---------------------------------
liveConn::~liveConn()
{
	ofRemoveListener(_fbConn.newResponseEvent, this, &liveConn::httpRespone);
	_fbConn.stop();
}

//---------------------------------
void liveConn::update(float delta)
{
	if (_isStart)
	{
		_timer -= delta;
		if (_timer <= 0.0f)
		{
			_timer = cGetNewDataTime;
			getNewComm();
		}
	}
	
}

//---------------------------------
command liveConn::getCommand()
{
	command nextCommand;
	if (_commList.size() > 0)
	{
		nextCommand = _commList.front();
		_commList.pop_front();
	}
	
	return nextCommand;
}

//---------------------------------
void liveConn::start()
{
	_isStart = true;	
	_timer = cGetNewDataTime;
	ofLog(OF_LOG_NOTICE, "[liveConn::start]Start");
}

//---------------------------------
void liveConn::stop()
{	
	_isStart = false;
	ofLog(OF_LOG_NOTICE, "[liveConn::start]Stop");
}

//---------------------------------
void liveConn::decodeCommand(Json::Value & value)
{
	Json::Value data = value.get("data", 0);
	for (int i = 0; i < data.size(); i++)
	{
		string time = data[i].get("created_time", 0).asString();
		Json::Value user = data[i].get("from", 0);
		string fbid = user.get("id", 0).asString();
		string msg = data[i].get("message", 0).asString();
		
		command newCmd(getType(msg), fbid);

		if (newCmd._eType != eCommand::eCommUnknow)
		{	
			_commList.push_back(newCmd);
			
		}
	}
	if (data.size() > 0)
	{
		string time = data[data.size() - 1].get("created_time", 0).asString();
		_lastTime = time.substr(0, time.find("+"));
	}
}

//---------------------------------
eCommand liveConn::getType(string& msg)
{
	auto iter = _commMgr.find(msg);
	if (iter != _commMgr.end())
	{
		return iter->second;
	}
	else
	{
		return eCommand::eCommUnknow;
	}
}

//---------------------------------
void liveConn::getNewComm()
{
	ofxHttpForm form;
	form.action = cFBUrl + cLiveID + cAction;
	form.method = OFX_HTTP_GET;

	form.addFormField("access_token", cFBToken);
	form.addFormField("order", "chronological");
	if (_lastTime != "")
	{
		form.addFormField("since", _lastTime);
	}
	_fbConn.addForm(form);
}

//---------------------------------
void liveConn::httpRespone(ofxHttpResponse & e)
{
	if (e.status != 200)
	{
		ofLog(OF_LOG_ERROR, "[liveConn::httpRespone]http error, status:" + e.status);
		return;
	}

	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(e.responseBody.getText(), root))
	{
		ofLog(OF_LOG_ERROR, "[liveConn::httpRespone]Decode json failed");
		return;
	}

	decodeCommand(root);
}

//---------------------------------

