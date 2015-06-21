/*
 * Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted per Mozilla Public License v2.0.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <iostream>
#include <string>

#include "itv_utils.h"
#include "itv_characters.h"

using namespace std;

int main() {
	/* create ITV Table,
	 * One can use any text encoding. Here we use UTF8.
	 * IDs use Hebrew, thus encrypted text will be in Hebrew
	 * Values use Arabic, thus plain text will be in Arabic
	 */
	ITV_Characters sender = ITV_Characters(0x500, 0x600, 0x6FF - 0x600);
	sender.load(0x20, 0x20, 1); /* Add space character */

	/* randomly shuffle IDs */
	sender.shuffle();

	/* define a separator for ITV Table dump */
	std::string seperator = std::string(1, (const char)126); 

	/* ITV Table that receiver needs to decrypt data */
	std::string itv_table = sender.dump(seperator);

	/* sample text to encrypt, we are using UTF8 encoding here */
	std::string str = u8"أزمة اليمن: الحوثيون يتقدمون في عدن رغم الغارات الجوية";
	std::list<size_t>* msg = from_utf8(str);

	cout << "Original: " << str << endl;

	/* encrypt the text */
	std::list<size_t> *encrypted_text = sender.encode(*msg);

	/* convert encrypted text to UTF8 and send it, here we just print it */
	cout << "Encrypted: " << to_utf8(*encrypted_text) << endl;


	/* On Receiver side, 
	 * the ITV Table is initialised with table dump from sender side
	 */
	ITV_Characters receiver = ITV_Characters(itv_table, seperator);
	std::list<size_t> *decrypted_text = receiver.decode(*encrypted_text);
	std::string plain = to_utf8(*decrypted_text);

	if (str == plain) {
		cout << "Decrypted: " << plain << endl;
	} else {
		cout << "Failure: " << plain << endl;
	};

	return 0;
};


