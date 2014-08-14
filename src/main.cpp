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
#include "itv_config.h"

int use_char_itv(std::string data) {
	ITV_ASCII *caller = new ITV_ASCII();
	caller->load(48, 57);
	caller->load(65, 90);
	caller->load(97, 122);

	std::string str = ""; //"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	//cout << "Sender ITV Table before initialization: " << endl << caller->to_string() << endl;
	std::string enc = caller->encode(str);
	//cout << "Sender ITV Table after initialization: " << endl << caller->to_string() << endl;

	//caller->write("/tmp/callee.txt");

	std::string key = caller->dump(':');
	enc = caller->encode(data);

	//ITV_ASCII *callee = new ITV_ASCII();
	//callee->read("/tmp/callee.txt");

	cout << "Key: " << key << endl;
	ITV_ASCII *callee = new ITV_ASCII(key);

	//cout << "Receiver ITV Table after initialization: " << endl << callee->to_string() << endl;
	std::string dcr = callee->decode(enc);

	cout << "Plaintext: " << data << endl;
	cout << "Encrypted Text: " << enc << endl;
	cout << "Decrypted Text: " << dcr << endl;
	cout << endl;

	return 0;
};

int use_word_itv(std::string data) {
	ITV_Words *caller = new ITV_Words("./wordsEn.txt", 0);

	std::string str = "a quick brown fox jumps over the lazy dog";
	std::string enc = caller->encode(str);

	caller->write("/tmp/caller.txt");
	//size_t enc_size = caller->get_expected_length(str, 0);
	enc = caller->encode(data);

	ITV_Words *callee = new ITV_Words("/tmp/caller.txt", 0);
	//size_t dcr_size = callee->get_expected_length(enc, 1);
	std::string dcr = callee->decode(enc);

	cout << "Plaintext: " << data << endl;
	cout << "Encrypted Text: " << enc << endl;
	cout << "Decrypted Text: " << dcr << endl;
	//cout << "Expected size of encrypted text: " << enc_size << endl;
	//cout << "Actual size of encrypted text: " << enc.length() << endl;
	//cout << "Expected size of decrypted text: " << dcr_size << endl;
	//cout << "Actual size of decrypted text: " << dcr.length() << endl;
	cout << endl;

	return 0;
};


int main() {
	std::string str = "a quick brown fox jumps over the lazy dog.";

	use_char_itv(str);
	use_word_itv(str);

	std::string def = compress(str, 1);
	std::string inf = decompress(def, 1);
	cout << "Compressed Text: " << def << endl;
	cout << "Decompressed Text: " << inf << endl;
	cout << endl;

	//cout << "Enter data to encrypt: ";
	//getline(cin, str);

	//cout << endl << endl;
	//use_char_itv(str);
	//use_word_itv(str);

	return 0;
};


