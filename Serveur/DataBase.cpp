#include "DataBase.h"


DataBase::DataBase()
{
}

DataBase::~DataBase()
{
}


void DataBase::loadClientDB()
{
	std::ifstream DB("DB.json");
	ClientDB = json::parse(DB);
	for (auto c : ClientDB)
	{
		Client* client = new Client();
		client->setID(c["ID"]);
		client->setName(c["Name"]);
		client->setRoundCount(c["RoundCount"]);
		client->setRoundWin(c["RoundWin"]);
		client->setRoundLose(c["RoundLose"]);
		_clientsList[client->getID()] = client;
	}
	ClientDB.clear();
}

void DataBase::updateClientDB(std::map<int, Client*> _clientsList)
{
	std::ofstream DB("DB.json");
	json ClientDB2;

	for (auto& c : _clientsList)
	{
		ClientDB2[c.second->getID()]["ID"] = c.second->getID();
		ClientDB2[c.second->getID()]["Name"] = c.second->getName();
		ClientDB2[c.second->getID()]["RoundCount"] = c.second->getRoundCount();
		ClientDB2[c.second->getID()]["RoundWin"] = c.second->getRoundWin();
		ClientDB2[c.second->getID()]["RoundLose"] = c.second->getRoundLose();
	}
	DB << ClientDB2;
}

Client DataBase::pullClientDB(int index)
{
	std::ifstream DB("DB.json");
	ClientDB = json::parse(DB);

	Client* c = new Client();
	c->setID(ClientDB[index]["ID"]);
	c->setName(ClientDB[index]["Name"]);
	c->setRoundCount(ClientDB[index]["RoundCount"]);
	c->setRoundWin(ClientDB[index]["RoundWin"]);
	c->setRoundLose(ClientDB[index]["RoundLose"]);

	ClientDB.clear();
	return *c;
}

void DataBase::updateClientinDB(Client* c)
{
	std::ofstream DB("DB.json");

	ClientDB[c->getID()]["ID"] = c->getID();
	ClientDB[c->getID()]["Name"] = c->getName();
	ClientDB[c->getID()]["RoundCount"] = c->getRoundCount();
	ClientDB[c->getID()]["RoundWin"] = c->getRoundWin();
	ClientDB[c->getID()]["RoundLose"] = c->getRoundLose();

	DB << ClientDB;

	ClientDB.clear();
}

Client DataBase::createClientinDB(std::string name)
{
	std::ifstream DB("DB.json");
	ClientDB = json::parse(DB);

	Client* c = new Client();
	c->setID(ClientDB.size()+1);
	c->setName(name);
	c->setRoundCount(0);
	c->setRoundWin(0);
	c->setRoundLose(0);

	ClientDB[std::to_string(c->getID())]["ID"] = c->getID();
	ClientDB[std::to_string(c->getID())]["Name"] = c->getName();
	ClientDB[std::to_string(c->getID())]["RoundCount"] = c->getRoundCount();
	ClientDB[std::to_string(c->getID())]["RoundWin"] = c->getRoundWin();
	ClientDB[std::to_string(c->getID())]["RoundLose"] = c->getRoundLose();

	std::ofstream DB2("DB.json");
	DB2 << ClientDB;

	_clientsList[c->getID()] = c;

	ClientDB.clear();
	return *c;	
}



