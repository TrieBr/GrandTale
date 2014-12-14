#include "serverManager.h"

serverManager::serverManager() {

}

void serverManager::addServer(abstractServer *server) {
	serverList.push_back(server);
}

void serverManager::initialize() {
	for (unsigned int i = 0; i < serverList.size(); i++) {
		serverList[i]->initialize();
	}
}

void serverManager::run() {
	for (unsigned int i = 0; i < serverList.size(); i++) {
		serverList[i]->handle();
	}
}

void serverManager::shutdown() {
	for (unsigned int i = 0; i < serverList.size(); i++) {
		serverList[i]->shutdown();
	}
}
