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

ITV_ASCII::ITV_ASCII() {
	min_id = 0;
	table = new list<ITV>();
};

ITV_ASCII::ITV_ASCII(std::string str) {
	min_id = 0;
	table = new list<ITV>();
	this->load(str);
};

ITV_ASCII::ITV_ASCII(size_t min, size_t max) {
	min_id = 0;
	table = new list<ITV>();
	this->load(min, max);
};

ITV_ASCII::~ITV_ASCII() {
	// nothing todo here
	if (this->table) { delete this->table; }
};

size_t ITV_ASCII::load(std::string str) {
	size_t len = str.length();
	if (len < 3) { return 0; };

	for (size_t x=0; x<len; x++) {
		this->add(new ITV(str.at(x++), std::string(1, str.at(x++))));
	};

	if (this->table->size() > 0) {
		this->table->sort();
		this->table->unique();
		min_id = this->table->front().get_id();
	};

	return this->table->size();
};

size_t ITV_ASCII::load(size_t min, size_t max) {
	if (min > max || max > 255) { return 0; };

	for(size_t x=min; x<=max; x++) {
		this->add(new ITV(x, std::string(1, x)));
	};

	min_id = min;
	return max - min;
};

std::string ITV_ASCII::dump(char sep) {
	std::stringstream ss;
	this->table->sort(compare_tags);

	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		ss << std::string(1, (*i).get_id()) << (*i).get_value() << std::string(1, sep);
	};

	std::string str = ss.str();
	return str.substr(0, str.length() - 1);
};

size_t ITV_ASCII::read(std::string file) {
	ifstream ifs(file);
	if (!ifs.is_open()) { return 0; };

	std::string line = string();
	while(getline(ifs, line)) {
		this->add(new ITV(line.at(0), line.substr(1,1)));
	};

	if (this->table->size() > 0) {
		this->table->sort();
		this->table->unique();
		min_id = this->table->front().get_id();
	};

	ifs.close();
	return this->table->size();
};

size_t ITV_ASCII::write(std::string file) {
	ofstream ofs(file);
	if (!ofs.is_open()) { return 0; };
	this->table->sort(compare_tags);

	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		ofs << std::string(1, (*i).get_id()) << (*i).get_value() << endl;
	};

	ofs.close();
	return this->table->size();
};

std::string ITV_ASCII::encode(std::string str) {
	size_t *data;
	std::string enc = std::string();
	std::string::const_iterator i;

	for(i=str.begin(); i!=str.end(); i++) {
		data = this->convert(std::string(1, *i), get_random_id());
		if (data == NULL) {
#if AUTO_LEARN > 0
			this->add(new ITV(*i, std::string(1, *i)));
#endif
			enc += *i;
		} else {
			enc += std::string(1, data[0]) + std::string(1, data[1]);
		};
	};

	return enc;
};

std::string ITV_ASCII::decode(std::string enc) {
	size_t x, y;
	std::string data;
	std::string str = std::string();
	std::string::const_iterator i;

	for(i=enc.begin(); i!=enc.end(); i++) {
		if (this->find_by_id(*i, 0) == NULL) {
#if AUTO_LEARN > 0
			this->add(new ITV(*i, std::string(1, *i)));
#endif
			str += *i;
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

