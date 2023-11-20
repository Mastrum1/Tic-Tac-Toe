#pragma once
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class MessageGenerator
{
public:
	MessageGenerator();
	virtual ~MessageGenerator();
	json& CreateNewMessage(int id, int cmd);
	std::string& FinalizeMessage(json message);


	json GetClientMessage() { return m_Message; };


private:
	json m_Message;
	std::string m_FinalMessage;

};

