#pragma once

#include "pch.h"

using json = nlohmann::json;

class MessageGenerator
{
public:
	MessageGenerator();
	virtual ~MessageGenerator();
	json& CreateMessage(int id, int cmd);
	std::string& FinalizeMessage(json message);


	json GetClientMessage() { return m_Message; };


private:
	json m_Message;
	std::string m_FinalMessage;

};

