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

ITV_Words::ITV_Words() {
	min_id = 0;
	table = new list<ITV>();
};

ITV_Words::ITV_Words(std::string file, size_t min) {
	min_id = min;
	table = new list<ITV>();
	this->read(file);
};

ITV_Words::~ITV_Words() {
	// nothing todo here
	if (this->table) { delete this->table; }
};

list<string> ITV_Words::get_words(std::string sentence) {
	list<string> words;
	istringstream iss(sentence);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<list<string> >(words));
	return words;
};

size_t ITV_Words::read(std::string file) {
	ifstream ifs(file);
	if (!ifs.is_open()) { return 0; };

	size_t x = this->min_id;
	std::string line = string();

	while(getline(ifs, line)) {
		this->add(new ITV(x++, trim(line)));
	};

	ifs.close();
	return this->table->size();
};

size_t ITV_Words::write(std::string file) {
	ofstream ofs(file);
	if (!ofs.is_open()) { return 0; };
	this->table->sort(compare_ids);

	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		ofs << (*i).get_value() << endl;
	};

	ofs.close();
	return this->table->size();
};

std::string ITV_Words::encode(std::string str) {
	size_t *data;
	list<string> words = this->get_words(str);

	std::stringstream enc;
	list<string>::iterator i;

	enc << std::hex;
	enc << std::setiosflags(std::ios::showbase);

	for(i=words.begin(); i!=words.end(); i++) {
		char first = 0, last = 0;
		std::string word = *i;
		size_t len = word.length();

		if (is_symbol(first = word.at(0))) {
			word = word.substr(1);
			len = word.length();
		} else { first = 0; };

		if (is_symbol(last = word.at(len - 1))) {
			word = word.substr(0, len - 1);
		} else { last = 0; };

		data = this->convert(word, get_random_id());
		if (data == NULL) { continue; };

		if (first) { enc << first; };
		enc << data[0] << " " << data[1];
		if (last) { enc << last; };

		enc << " ";
	};

	return enc.str();
};

std::string ITV_Words::decode(std::string enc) {
	size_t x, y;
	std::string data;
	list<string> words = this->get_words(enc);

	std::string str = std::string();
	list<string>::iterator i;

	for(i=words.begin(); i!=words.end(); i++) {
		char first = 0, last = 0;
		std::string word = *i, next = *(++i);
		size_t len = word.length();

		if (is_symbol(first = word.at(0))) {
			word = word.substr(1);
			len = word.length();
		} else { first = 0; };

		len = next.length();

		if (is_symbol(last = next.at(len - 1))) {
			next = next.substr(0, len - 1);
		} else { last = 0; };

		x = strtoul ((word).c_str(), NULL, 0);
		y = strtoul ((next).c_str(), NULL, 0);
		data = this->revert(x, y);

		if (data.empty()) { continue; };

		if (first) { str += first; };
		str += data;
		if (last) { str += last; };

		str	+= " ";
	};

	return str;
};

std::string ITV_Words::to_string() {
	std::string str = std::string();
	this->table->sort();

	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		str += (*i).to_string();
	};
	return str;
};

