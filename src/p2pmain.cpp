#include "Interface.hpp"
#include "P2PServer.hpp"
#include "P2PTest.hpp"

int main(int argc, char *argv[])
{
	P2PTest *t = new P2PTest;
	P2PServer* c = new P2PServer;
	// instaluje obserwatora w serwerze
	c->addObserver(t);
	c->start();

	// nawiazuje polaczenie i wysyla wiadomosc
	// P2PConnection* c = new P2PConnection("127.0.0.1");
	// Message m;
	// m.type = Message::MESSAGE;
	// m.content = "TESTUJE SERWER!";
	// c->send(m);
	// c->send(m);
	// //c->closeSocket()
	return 0;
}
