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
#include <algorithm>

#include "itv_table.h"
#include "itv_utils.h"

ITV_Table::ITV_Table() {
	this->table = new std::list<ITV>();
};

ITV_Table::ITV_Table(std::list<ITV> &table) {
	this->table = &table;
};

ITV_Table::~ITV_Table() {
	// nothing todo here
	if (this->table) { delete this->table; }
};

ITV_Table& ITV_Table::operator=(const ITV_Table &rhs) {
	this->table = rhs.table;
	return *this;
};

bool ITV_Table::operator==(const ITV_Table &rhs) const {
	return (this->table == rhs.table);
};

bool ITV_Table::operator!=(const ITV_Table &rhs) const {
	return (this->table != rhs.table);
};

bool ITV_Table::operator<=(const ITV_Table &rhs) const {
	return (this->table <= rhs.table);
};

bool ITV_Table::operator>=(const ITV_Table &rhs) const {
	return (this->table >= rhs.table);
};

bool ITV_Table::operator<(const ITV_Table &rhs) const {
	return (this->table < rhs.table);
};

bool ITV_Table::operator>(const ITV_Table &rhs) const {
	return (this->table > rhs.table);
};

const std::list<ITV>* ITV_Table::get_table() {
	return this->table;
};

void ITV_Table::set_table(const std::list<ITV> &table) {
	this->table = (std::list<ITV>*)&table;
};

bool ITV_Table::add(const ITV &element) {
	if (&element && !this->exists(element)) {
		this->table->push_back(element);
		return true;
	};
	return false;
};

void ITV_Table::remove(const ITV &element) {
	if (&element) {
		this->table->remove(element);
	};
};

bool ITV_Table::exists(const ITV &element) {
	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		if ((*i) == element) { return true; };
	};
	return false;
};

ITV* ITV_Table::find_by_id(size_t id) {
	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		if ((*i).get_id() == id) {
			return &(*i);
		};
	};
	return NULL;
};

ITV* ITV_Table::find_by_tag(size_t tag) {
	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		if ((*i).get_tag() == tag) {
			return &(*i);
		};
	};
	return NULL;
};

ITV* ITV_Table::find_by_value(size_t value) {
	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		if ((*i).get_value() == value) {
			return &(*i);
		};
	};
	return NULL;
}

size_t* ITV_Table::convert(size_t value, size_t next) {
	size_t *retval = new size_t[2];
	ITV *itv_current = NULL, *itv_next = NULL;

	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		if ((*i).get_value() == value) { itv_current = &(*i); };
		if ((*i).get_id() == next) { itv_next = &(*i); };
		if (itv_current != NULL && itv_next != NULL) { break; };
	};

	if (itv_current == NULL || itv_next == NULL) { return NULL; }
	itv_next->replace(itv_current->get_id());
	itv_current->replace(next);

	retval[0] = itv_current->get_tag();
	retval[1] = itv_next->get_tag();
	return retval;
};

size_t* ITV_Table::revert(size_t current, size_t next) {
	ITV *itv_current = NULL, *itv_next = NULL;
	size_t *retval = new size_t[1];

	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		if ((*i).get_id() == current) { itv_current = &(*i); };
		if ((*i).get_id() == next) { itv_next = &(*i); };
		if (itv_current != NULL && itv_next != NULL) { break; };
	};

	if (itv_current == NULL || itv_next == NULL) { return NULL; }
	itv_current->replace(next);
	itv_next->replace(current);

	retval[0] = itv_current->get_value();
	return retval;
}

void ITV_Table::clear() {
	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		(*i).clear();
	};
};

void ITV_Table::restore() {
	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		(*i).restore();
	};
};

void ITV_Table::shuffle() {
	std::list<size_t>* msg = new std::list<size_t>();
	for (auto i=this->table->begin(); i!=this->table->end(); i++) {
		msg->push_back((*i).get_value());
	};
	this->encode(*msg);
};

size_t ITV_Table::get_random_id() {
	if (this->table->empty()) { return 0; };

	size_t id = get_random(0, this->table->size() - 1);
	auto i = this->table->begin();
	std::advance(i, id);
	return (*i).get_id();
};

std::list<size_t>* ITV_Table::encode(std::list<size_t>& msg) {
	std::list<size_t> *ret = new std::list<size_t>();
	size_t *data;

	for (auto i=msg.begin(); i!= msg.end(); i++) {
		data = this->convert(*i, get_random_id());
		if (data == NULL) {
			ret->push_back(*i);
		} else {
			ret->push_back(data[0]);
			ret->push_back(data[1]);
		};
	};

	return ret;
};

std::list<size_t>* ITV_Table::decode(std::list<size_t>& msg) {
	std::list<size_t> *ret = new std::list<size_t>();
	size_t x, y, *z;

	for (auto i=msg.begin(); i!= msg.end(); i++) {
		x = *i++; y = *i;
		z = this->revert(x, y);
		if (z == NULL) {
			ret->push_back(*(--i));
			continue;
		};
		ret->push_back(z[0]);
	};

	return ret;
};


