#include "Interface.hpp"
#include "P2PServer.hpp"
#include "P2PTest.hpp"
#include "Encoder.hpp"

char * Encrypt( char *key, char *message, int size)
{
 
        static char*    result;
        int             n=0;
        DES_cblock      ckey;
        DES_key_schedule schedule;
 
        result = ( char * ) malloc( size );
 
        /* Prepare the key for use with DES_cfb64_encrypt */
        memcpy( ckey, key,8);
        DES_set_odd_parity( &ckey );
        DES_set_key_checked( &ckey, &schedule );
 
        /* Encryption occurs here */
        DES_cfb64_encrypt( ( unsigned char * ) message, ( unsigned char * ) result,
                           size, &schedule, &ckey, &n, DES_ENCRYPT );
 
         return (result);
}
 
 
char * Decrypt( char *key, char *message, int size)
{
 
        static char*    result;
        int             n=0;
 
        DES_cblock      ckey;
        DES_key_schedule schedule;
 
        result = ( char * ) malloc( size );
 
        /* Prepare the key for use with DES_cfb64_encrypt */
        memcpy( ckey, key,8);
        DES_set_odd_parity( &ckey );
        DES_set_key_checked( &ckey, &schedule );
 
        /* Decryption occurs here */
        DES_cfb64_encrypt( ( unsigned char * ) message, ( unsigned char * ) result,
                           size, &schedule, &ckey, &n, DES_DECRYPT );
 
        return (result);
 
}

int main(int argc, char *argv[])
{
	// P2PTest *t = new P2PTest;
	// P2PServer* c = new P2PServer;
	// // instaluje obserwatora w serwerze
	// c->addObserver(t);
	// c->start();

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
