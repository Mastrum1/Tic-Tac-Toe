#pragma once
#include "pch/pch.h"
#include "Client.h"

using json = nlohmann::json;

class DataBase
{
public:
	DataBase();
	~DataBase();

	void loadClientDB(); //Load the local database
	void updateClientDB(std::map<int, Client*> _clientsList); //Update the local database with the list of clients
	Client* pullClientDB(int id); //Pull one client from the local database
	void updateClientinDB(Client* c); //Update one Client in the local database
	Client createClientinDB(std::string name); //Create a new client in the local database
	Client* getClient(int id); //Get a client from the local database

	std::map<int, Client*> _clientsList;
private:
	json ClientDB;
};
