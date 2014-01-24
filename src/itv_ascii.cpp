#include "itv_ascii.h"

ITV_ASCII::ITV_ASCII() {
	t = ASCII_PRINTABLE;
	load_ascii_table(t);
};

ITV_ASCII::ITV_ASCII(enum type t) {
	this->t = t;
	load_ascii_table(t);
};

ITV_ASCII::ITV_ASCII(ifstream &ifs) {
	this->t = ASCII_OTHER;
	this->load(ifs);
};

ITV_ASCII::~ITV_ASCII() {
	// nothing todo here
};

void ITV_ASCII::load(ifstream &ifs) {
	if (!ifs.is_open()) { return; };

	this->table->clear();
	std::string line = string();

	while(getline(ifs, line)) {
		line = trim(line);
		if (line.size() != 2) { continue; };
		this->add(new ITV(line.at(0), line.substr(1,1)));
	};

	if (this->table->size() > 0) {
		this->table->sort();
		this->table->unique();
		min_id = this->table->front().get_id();
	};
};

void ITV_ASCII::save(ofstream &ofs) {
	if (!ofs.is_open()) { return; };
	this->table->sort(compare_tags);

	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		ofs << std::string(1, (*i).get_id()) << (*i).get_value() << endl;
	};
};

void ITV_ASCII::load_ascii_table(enum type t) {
	ITV *itv;
	unsigned int max_id;
	this->table->clear();

	switch(t) {
		case ASCII_ALPHABET:
			min_id = 65;
			for(int x=65; x<=90; x++) {
				this->add(new ITV(x, std::string(1, x)));
			};
			for(int x=97; x<=122; x++) {
				this->add(new ITV(x, std::string(1, x)));
			};
			break;
		case ASCII_ALPHANUMERIC:
			min_id = 48;
			for(int x=48; x<=57; x++) {
				this->add(new ITV(x, std::string(1, x)));
			};
			for(int x=65; x<=90; x++) {
				this->add(new ITV(x, std::string(1, x)));
			};
			for(int x=97; x<=122; x++) {
				this->add(new ITV(x, std::string(1, x)));
			};
			break;
		case ASCII_NUMERIC:
			min_id = 48;
			for(int x=48; x<=57; x++) {
				this->add(new ITV(x, std::string(1, x)));
			};
			break;
		case ASCII_PRINTABLE:
			min_id = 33;
			for(int x=33; x<=126; x++) {
				this->add(new ITV(x, std::string(1, x)));
			};
			break;
		default:
			min_id = 0;
	};
};

std::string ITV_ASCII::encode(std::string str) {
	unsigned int *data, last;
	std::string enc = std::string();
	std::string::const_iterator i;

	for(i=str.begin(); i!=str.end(); i++) {
		if (*i == WORD_SEPARATOR && last) {
			if (get_random(0, 2)) {
				enc += std::string(1, get_random_id());
			};

			enc += *i;
			continue;
		};

		data = this->convert(std::string(1,*i), get_random_id());

		if (data == NULL) {
			enc += *i;
			last = 0;
			continue;
		} else {
			enc += std::string(1, data[0]) + std::string(1, data[1]);
			last = *i;
		};
	};

	return enc;
};

std::string ITV_ASCII::decode(std::string enc) {
	unsigned int x, y;
	std::string data;
	std::string str = std::string();
	std::string::const_iterator i;

	for(i=enc.begin(); i!=enc.end(); i++) {
		if (this->find_by_id(*i, 0) == NULL) {
			str += *i;
			continue;
		} else if (*(i + 1) == WORD_SEPARATOR) {
			continue;
		};

		x = *i++; y = *i;
		data = this->revert(x, y);

		if (data.empty()) {
			str += *(--i);
			continue;
		};

		str += data;
	};

	return str;
};

std::string ITV_ASCII::to_string() {
	std::string str = std::string();
	this->table->sort(compare_tags);

	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		str += (*i).to_string();
	};
	return str;
};

