#include "MessageGenerator.h"

MessageGenerator::MessageGenerator()
{
	//m_Message["Coordinate"];// = NULL;
	//m_Message["WinResult"] = NULL;
}

MessageGenerator::~MessageGenerator()
{
}

json& MessageGenerator::CreateMessage(int id, int cmd)
{
	m_Message.clear();
	m_Message["Type"] = id;
	m_Message["Cmd"] = cmd;

	return m_Message;
}

std::string& MessageGenerator::FinalizeMessage(json message)
{
	m_FinalMessage = message.dump();
	return m_FinalMessage;
}


