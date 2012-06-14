#include "Encoder.hpp"

Encoder::Encoder()
{
	DES_random_key(&_keys[0]);
	DES_random_key(&_keys[1]);
	DES_random_key(&_keys[2]);
	prepareKeySchedules();
}

Encoder::Encoder(DES_cblock keys[3])
{
	memcpy(_keys,keys, sizeof(DES_cblock)*3);
	prepareKeySchedules();
}

void Encoder::prepareKeySchedules()
{
	// preparing schedules
	for(unsigned short int i = 0; i < 3; ++i)
    {
    	DES_set_odd_parity(&_keys[i]);
    	DES_set_key_checked(&_keys[i], &_schedules[i]);
    }
}

void Encoder::encrypt(const char* rawMessage, const unsigned int size, char* encryptedMessage, bool decrypt)
{
	int mode;
	if(decrypt)
		mode = DES_DECRYPT;
	else
		mode = DES_ENCRYPT;

	int n = 0;
	DES_cblock keys[3];
	DES_key_schedule schedules[3];
	// local copies
	memcpy(keys, _keys, sizeof(DES_cblock)*3);
	memcpy(schedules, _schedules, sizeof(DES_key_schedule)*3);

	DES_ede3_cfb64_encrypt(
  				(const unsigned char*) rawMessage, 
  				(unsigned char*) encryptedMessage,
            	size,
           		&schedules[0],
           		&schedules[1],
               	&schedules[2],
               	&keys[1],
               	&n, 
               	mode);
}

void Encoder::decrypt(const char* rawMessage, const unsigned int size, char* encryptedMessage)
{
	encrypt(rawMessage,size,encryptedMessage,true);
}