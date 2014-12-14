#include "abstractServer.h"
#include "GTLoginClient.h"
#include "GTGameWorldClient.h"
#include "database.h"
#include <iostream>

class GTLoginServer : public abstractServer {
public:
	virtual void initialize();
	virtual void handle();
	virtual void shutdown();
	
	clientManager<GTLoginClient> publicAcceptor;
	clientManager<GTGameWorldClient> gameWorldAcceptor;
private:
	
	
};