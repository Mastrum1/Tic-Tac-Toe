#include "MessageGenerator.h"

MessageGenerator::MessageGenerator()
{
	//m_Message["Coordinate"];// = NULL;
	//m_Message["WinResult"] = NULL;
}

MessageGenerator::~MessageGenerator()
{
}

std::string MessageGenerator::GenerateWinResult(bool result)
{
	m_Message["WinResult"] = result;
	std::string message = m_Message.dump(); //convert json to string
	return message;
}

std::string MessageGenerator::GenerateCoordinate(int x, int y)
{
	m_Message["Coordinate"] = { x, y };
	std::string message = m_Message.dump(); //convert json to string
	return message;
}

