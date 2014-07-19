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
#include <sys/time.h>
#include "itv_ascii.h"
#include "itv_words.h"
#include "itv_utils.h"

int use_char_itv(std::string data) {
	ITV_ASCII *caller = new ITV_ASCII(ITV_ASCII::ASCII_ALPHANUMERIC);
	if (caller == NULL) { return 1; }

	std::string str = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	//cout << "Sender ITV Table before initialization: " << endl << caller->to_string() << endl;
	std::string enc = caller->encode(str);
	//cout << "Sender ITV Table after initialization: " << endl << caller->to_string() << endl;

	//ofstream ofcaller("/tmp/callee.txt");
	//caller->save(ofcaller);
	//ofcaller.close();

	std::string key = caller->dump();
	enc = caller->encode(data);

	//ifstream ifcallee("/tmp/callee.txt");
	//ITV_ASCII *callee = new ITV_ASCII(ifcallee);
	//ifcallee.close();

	cout << "Key: " << key << endl;
	ITV_ASCII *callee = new ITV_ASCII(key);

	if (callee == NULL) { return 1; }

	//cout << "Receiver ITV Table after initialization: " << endl << callee->to_string() << endl;
	std::string dcr = callee->decode(enc);

	cout << "Plaintext: " << data << endl;
	cout << "Encrypted Text: " << enc << endl;
	cout << "Decrypted Text: " << dcr << endl;
	cout << endl;
	return 0;
};

int use_word_itv(std::string data) {
	ifstream ifcaller("./wordsEn.txt");
	ITV_Words *caller = new ITV_Words(ifcaller, 0);
	ifcaller.close();
	if (caller == NULL) { return 1; }

	std::string str = "a quick brown fox jumps over the lazy dog";
	std::string enc = caller->encode(str);

	ofstream ofcaller("/tmp/caller.txt");
	caller->save(ofcaller);
	ofcaller.close();

	enc = caller->encode(data);

	ifstream ifcallee("/tmp/caller.txt");
	ITV_Words *callee = new ITV_Words(ifcallee, 0);
	ifcallee.close();

	std::string dcr = callee->decode(enc);

	cout << "Plaintext: " << data << endl;
	cout << "Encrypted Text: " << enc << endl;
	cout << "Decrypted Text: " << dcr << endl;
	cout << endl;
	return 0;
};


int main() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srandom(tv.tv_usec);

	std::string str = "a quick brown fox jumps over the lazy dog.";

	use_char_itv(str);
	use_word_itv(str);

	//cout << "Enter data to encrypt: ";
	//getline(cin, str);

	//cout << endl << endl;
	//use_char_itv(str);
	//use_word_itv(str);

	return 0;
};


