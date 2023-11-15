#include "MessageGenerator.h"

MessageGenerator::MessageGenerator()
{
	//m_Message["Coordinate"];// = NULL;
	//m_Message["WinResult"] = NULL;
}

MessageGenerator::~MessageGenerator()
{
}

void MessageGenerator::GenerateWinResult(bool result)
{
	m_Message["WinResult"] = result;
}

void MessageGenerator::GenerateCoordinate(int x, int y)
{
	m_Message["Coordinate"] = { x, y };
}

