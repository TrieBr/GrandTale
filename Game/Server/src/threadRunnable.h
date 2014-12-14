#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif
#include <allegro5/threads.h>

class threadRunnable {
public:
	threadRunnable() {}
	~threadRunnable();
	void start();
	void stop();
	virtual void initialize() {}
	virtual void run() {}
	virtual void shutdown() {}
	ALLEGRO_THREAD* threadHandle;
};