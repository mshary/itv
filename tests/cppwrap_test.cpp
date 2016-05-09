/*
 * Copyright (c) 2013-2015, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
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

	/* ITV Table that receiver needs to decrypt data */
	std::string itv_table = sender.dump_table();

	/* ITV Table checksum, the receiver can check it to ensure 
	 * whether or not decryption will be successful before actual decryption 
	 */
	size_t sender_checksum = sender.checksum();

	/* sample text to encrypt, we are using UTF8 encoding here */
	std::string msg = "أزمة اليمن: الحوثيون يتقدمون في عدن رغم الغارات الجوية";

	cout << "Original: " << msg << endl;

	/* encrypt the text */
	std::string encrypted_text = sender.encode(msg);

	/* convert encrypted text to UTF8 and send it, here we just print it */
	cout << "Encrypted: " << encrypted_text << endl << endl;


	/* On Receiver side, 
	 * the ITV Table is initialised with table dump from sender side
	 */
	ITV_Characters receiver = ITV_Characters(itv_table);

	/* ITV Table checksum, if this match's sender checksum then ITV Table integrity is verified 
	 * and decryption will be successful
	 */
	size_t receiver_checksum = receiver.checksum();

	if (receiver_checksum != sender_checksum) {
		cout << "Error: checksum mismatch" << endl;
		cout << "Local: 0x" << std::hex << receiver_checksum << endl;
		cout << "Remote: 0x" << std::hex << sender_checksum << endl;
		return 0;
	} else {
		cout << "ITV Table Integrity Verified: 0x" << std::hex << sender_checksum << endl;
	};

	std::string decrypted_text = receiver.decode(encrypted_text);

	if (msg == decrypted_text) {
		cout << "Decrypted: " << decrypted_text << endl;
	} else {
		cout << "Failure: " << decrypted_text << endl;
	};

	return 0;
}


