#include "itv_words.h"

ITV_Words::ITV_Words() {
	min_id = 0;
};

ITV_Words::ITV_Words(ifstream &ifs, unsigned int min) {
	min_id = min;
	this->load(ifs);
};

ITV_Words::~ITV_Words() {
	// nothing todo here
};

list<string> ITV_Words::get_words(std::string sentence) {
	list<string> words;
	istringstream iss(sentence);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<list<string> >(words));
	return words;
};

std::string ITV_Words::encode(std::string str) {
	unsigned int *data;
	list<string> words = this->get_words(str);

	std::stringstream enc;
	list<string>::iterator i;

	for(i=words.begin(); i!=words.end(); i++) {
		char first = 0, last = 0;
		std::string word = *i;
		int len = word.length();

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
	unsigned int x, y;
	std::string data;
	list<string> words = this->get_words(enc);

	std::string str = std::string();
	list<string>::iterator i;

	for(i=words.begin(); i!=words.end(); i++) {
		char first = 0, last = 0;
		std::string word = *i, next = *(++i);
		int len = word.length();

		if (is_symbol(first = word.at(0))) {
			word = word.substr(1);
			len = word.length();
		} else { first = 0; };

		len = next.length();

		if (is_symbol(last = next.at(len - 1))) {
			next = next.substr(0, len - 1);
		} else { last = 0; };

		x = atoi((word).c_str());
		y = atoi((next).c_str());
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

