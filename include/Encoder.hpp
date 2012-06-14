#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_
#include <openssl/des.h>
#include <iostream>
#include <string>
#include <cstring>

/**
	@brief     Encoder
 	@details   Provides data encryption with 3DES algorithm.
 	@author    Mateusz Galazyn
 	@version   0.1a
 	@date      06.2012
 	@copyright GNU Public License.
    @file	   Encoder.hpp
 */

class Encoder
{
public:
	/**
		Default constructor.
		Generates 3 random keys.
	*/
	Encoder();
	/**
		Constructor which, utilizes already generated keys.
	*/
	Encoder(DES_cblock keys[3]);
	~Encoder(){};
	/**
		Returns keys
		@return keys
	*/
	const DES_cblock* getKeys() const {return _keys;};
	/**
		Encrypts message.
		@param message message
		@param size length of message
		@param encrypted encrypted message
		@param decrypt true to decrypt message
	*/
	void encrypt(const char*, const unsigned int, char*, bool decrypt = false);
	/**
		Decrypts message.
		@param message message
		@param size length of message
		@param encrypted encrypted message
	*/
	void decrypt(const char*, const unsigned int, char*);
private:
	/**
		3 keys used to encrypt messages. Generated each time, the connection is estabilished.
	*/
	DES_cblock _keys[3];
	/**
		Schedules of the keys.
	*/
	DES_key_schedule _schedules[3];
	/**
		Prepares key schedules
	*/
	void prepareKeySchedules();
};

#endif