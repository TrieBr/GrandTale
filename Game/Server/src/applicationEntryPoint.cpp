
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include "serverManager.h"
#include "GTLoginServer.h"
#include "GTGameServer.h"
#include "database.h"
#include <allegro5/allegro.h>




int main(int argc, char* argv[]) {
	al_init();
	accountDB.connect("127.0.0.1","triebrco_accounts","root","");
	gameDB.connect("127.0.0.1","triebrco_GTdata","root","");

	serverManager loginServer;
	GTLoginServer *s = new GTLoginServer();
	s->setIdentifier("Login Server");
	loginServer.addServer(s);
	loginServer.start();

    al_rest(2);
	//Sleep(2000); //Wait for login server to initialize, so the game worlds can connect properly

	serverManager worldServer;
	worldServer.addServer(new GTGameServer("Azurai Beta",1339,"gtserver.zapto.org"));
	worldServer.start();
	while (1) {
        al_rest(100);

	}

}