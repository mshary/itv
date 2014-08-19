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

ITV_Table::ITV_Table() {
	min_id = 0;
	table = new list<ITV>();
};

ITV_Table::ITV_Table(list<ITV> &table) {
	min_id = 0;
	this->table = &table;
};

ITV_Table::~ITV_Table() {
	// nothing todo here
	if (this->table) { delete this->table; }
};

ostream &operator << (ostream &output, const ITV_Table &ptr) {
	list<ITV>::iterator i;
	for (i=ptr.table->begin(); i!=ptr.table->end(); i++) {
			output << *i;
	};
	return output;
};

ITV_Table& ITV_Table::operator=(const ITV_Table &rhs) {
	table = rhs.table;
	return *this;
};

bool ITV_Table::operator==(const ITV_Table &rhs) const {
	return (table == rhs.table);
};

bool ITV_Table::operator!=(const ITV_Table &rhs) const {
	return !(table == rhs.table);
};

bool ITV_Table::operator<=(const ITV_Table &rhs) const {
	return ((table < rhs.table) || (table == rhs.table));
};

bool ITV_Table::operator>=(const ITV_Table &rhs) const {
	return ((rhs.table < table) || (table == rhs.table));
};

bool ITV_Table::operator<(const ITV_Table &rhs) const {
	return (table < rhs.table);
};

bool ITV_Table::operator>(const ITV_Table &rhs) const {
	return (rhs.table < table);
};

const list<ITV>* ITV_Table::get_table() {
	return this->table;
};

void ITV_Table::set_table(const list<ITV> &table) {
	if (this->table) { delete this->table; };
	this->table = (list<ITV>*)&table;
};

bool ITV_Table::add(const ITV &element) {
	if (&element) {
		this->table->push_back(element);
		return true;
	};
	return false;
};

bool ITV_Table::remove(const ITV &element) {
	if (this->exists(element)) {
		this->table->remove(element);
		return true;
	};
	return false;
};

bool ITV_Table::exists(const ITV &element) {
	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); i++) {
		if (*i == element) {
			return true;
		};
	};
	return false;
};

ITV* ITV_Table::find_by_id(size_t id, bool reverse_direction) {
	if(this->table->empty()) { return NULL; };

	list<ITV>::iterator i;
	if (reverse_direction) {
		for (i=this->table->end(); i!=this->table->begin(); i--) {
			if ((*i).get_id() == id) {
				return &(*i);
			};
		};
	} else {
		for (i=this->table->begin(); i!=this->table->end(); i++) {
			if ((*i).get_id() == id) {
				return &(*i);
			};
		};
	};
	return NULL;
};

ITV* ITV_Table::find_by_tag(size_t tag, bool reverse_direction) {
	if(this->table->empty()) { return NULL; };

	list<ITV>::iterator i;
	if (reverse_direction) {
		for (i=this->table->end(); i!=this->table->begin(); i--) {
			if ((*i).get_tag() == tag) {
				return &(*i);
			};
		};
	} else {
		for (i=this->table->begin(); i!=this->table->end(); i++) {
			if ((*i).get_tag() == tag) {
				return &(*i);
			};
		};
	};
	return NULL;
};

ITV* ITV_Table::find_by_value(const std::string &value, bool reverse_direction) {
	if(this->table->empty()) { return NULL; };

	list<ITV>::iterator i;
	if (reverse_direction) {
		for (i=this->table->end(); i!=this->table->begin(); i--) {
			if (!value.compare((*i).get_value())) {
				return &(*i);
			};
		};
	} else {
		for (i=this->table->begin(); i!=this->table->end(); i++) {
			if (!value.compare((*i).get_value())) {
				return &(*i);
			};
		};
	};
	return NULL;
}

size_t* ITV_Table::convert(const std::string &value, size_t next) {
	size_t *retval = new size_t[2];
	ITV *itv_current = this->find_by_value(value, 0);
	ITV *itv_next = this->find_by_id(next, 0);

	if (itv_current == NULL || itv_next == NULL) { return NULL; }
	itv_next->replace(itv_current->get_id());
	itv_current->replace(next);

	retval[0] = itv_current->get_tag();
	retval[1] = itv_next->get_tag();

	return retval;
};

const std::string ITV_Table::revert(size_t current, size_t next) {
	ITV *itv_current = this->find_by_id(current, 0);
	ITV *itv_next = this->find_by_id(next, 0);

	if (itv_current == NULL || itv_next == NULL) { return ""; }
	itv_current->replace(next);
	itv_next->replace(current);

	return itv_current->get_value();
}

void ITV_Table::clear() {
	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); i++) {
		(*i).clear();
	};
};

void ITV_Table::restore() {
	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); i++) {
		(*i).restore();
	};
};

size_t ITV_Table::get_random_id() {
	if (this->table->empty()) { return 0; };

	size_t id = get_random(0, this->table->size() - 1);
	list<ITV>::iterator i = this->table->begin();
	std::advance(i, id);
	return (*i).get_id();
};

size_t ITV_Table::get_random(size_t min, size_t max) {
	std::random_device generator;
	std::uniform_int_distribution<size_t> distribution(min, max);
	return distribution(generator);
};

