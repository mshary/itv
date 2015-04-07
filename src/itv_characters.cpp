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
#include <fstream>
#include <sstream>

#include "itv_utils.h"
#include "itv_characters.h"

ITV_Characters::ITV_Characters() {
	table = new list<ITV>();
};

ITV_Characters::~ITV_Characters() {
	// nothing todo here
};

ITV_Characters::ITV_Characters(size_t min, size_t max) {
	table = new list<ITV>();
	this->load(min, max);
};

ITV_Characters::ITV_Characters(size_t id, size_t value, size_t len) {
	table = new list<ITV>();
	this->load(id, value, len);
};

ITV_Characters::ITV_Characters(std::string str, std::string delimiter) {
	table = new list<ITV>();
	this->load(str, delimiter);
};

size_t ITV_Characters::load(size_t min, size_t max) {
	if (min > max) { return 0; };

	for(size_t x=min; x<=max; x++) {
		this->add(ITV(min + (max - x), x));
	};

	return max - min;
};

size_t ITV_Characters::load(size_t id, size_t value, size_t len) {
	for (size_t i=0; i<len; i++) {
		this->add(ITV(id + i, value + i));
	};
	return len;
};

size_t ITV_Characters::load(std::string str, std::string delimiter) {
	std::deque<std::string> *data = split(str, delimiter);
	size_t len = data->size();
	if ((len % 2) != 0) { return 0; };

	for (size_t x=0; x<len; x++) {
		size_t y=x++, z=x;
		this->add(ITV(stoul(data->at(y), NULL, 0), stoul(data->at(z), NULL, 0)));
	};

	return this->table->size();
};

std::string ITV_Characters::dump(std::string delimiter) {
	std::stringstream ss;
	this->table->sort(compare_tags);

	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		ss << (*i).get_id() << delimiter << (*i).get_value() << delimiter;
	};

	std::string str = ss.str();
	return str.substr(0, str.length() - delimiter.length());
};

size_t ITV_Characters::read(const std::string file, std::string delimiter) {
	ifstream ifs(file);
	if (!ifs.is_open()) { return 0; };

	std::string line = string();
	while(getline(ifs, line)) {
		this->load(line, delimiter);
	};

	ifs.close();
	return this->table->size();
};

size_t ITV_Characters::write(const std::string file, std::string delimiter) {
	ofstream ofs(file);
	if (!ofs.is_open()) { return 0; };
	this->table->sort(compare_tags);

	ofs << this->dump(delimiter);
	ofs.close();

	return this->table->size();
};

const std::string ITV_Characters::to_string() {
	std::stringstream ss;
	std::string delimiter = ":";
	this->table->sort(compare_tags);

	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		ss << to_utf8((*i).get_id()) << delimiter << to_utf8((*i).get_value()) << delimiter;
	};

	std::string str = ss.str();
	return str.substr(0, str.length() - delimiter.length());
};

