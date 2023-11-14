#pragma once
#include "nlohmann/json.hpp"
#include <string>
using json = nlohmann::json;

class MessageGenerator
{
public:
	MessageGenerator();
	~MessageGenerator();
	void GenerateWinResult(bool result);
	void GenerateCoordinate(int x, int y);
	json GetMessage() { return m_Message; };


private:
	json m_Message;

};

