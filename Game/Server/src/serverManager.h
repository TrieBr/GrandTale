#include "abstractServer.h"
#include "threadRunnable.h"
#include <vector>

class serverManager : public threadRunnable{
public:
	serverManager();
	virtual void initialize();
	virtual void run();
	virtual void shutdown();
	void addServer(abstractServer *server);
private:
	std::vector<abstractServer*> serverList;
};