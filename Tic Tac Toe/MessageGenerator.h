#pragma once

#include "pch.h"

using json = nlohmann::json;

class MessageGenerator
{
public:
	MessageGenerator();
	~MessageGenerator();
	std::string GenerateWinResult(bool result);
	std::string GenerateCoordinate(int x, int y);
	json GetClientMessage() { return m_Message; };


private:
	json m_Message;

};

