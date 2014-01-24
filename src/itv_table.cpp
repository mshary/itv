#include "itv_table.h"

ITV_Table::ITV_Table() {
	table = new list<ITV>();
};

ITV_Table::ITV_Table(list<ITV> *table) {
	this->table = table;
};

ITV_Table::ITV_Table(ifstream &ifs, unsigned int min) {
	this->min_id = min;
	this->load(ifs);
};

ITV_Table::~ITV_Table() {
	// nothing todo here
};

ostream &operator << (ostream &output, const ITV_Table &ptr) {
	list<ITV>::iterator i;
	for (i=ptr.table->begin(); i!=ptr.table->end(); ++i) {
			output << *i;
	};
	return output;
};

ITV_Table& ITV_Table::operator=(const ITV_Table &rhs) {
	table = rhs.table;
	return *this;
};

int ITV_Table::operator==(const ITV_Table &rhs) const {
	return (table == rhs.table);
};

int ITV_Table::operator!=(const ITV_Table &rhs) const {
	return !(table == rhs.table);
};

int ITV_Table::operator<=(const ITV_Table &rhs) const {
	return ((table < rhs.table) || (table == rhs.table));
};

int ITV_Table::operator>=(const ITV_Table &rhs) const {
	return ((rhs.table < table) || (table == rhs.table));
};

int ITV_Table::operator<(const ITV_Table &rhs) const {
	return (table < rhs.table);
};

int ITV_Table::operator>(const ITV_Table &rhs) const {
	return (rhs.table < table);
};

list<ITV>* ITV_Table::get_table() {
	return this->table;
};

void ITV_Table::set_table(list<ITV> *table) {
	this->table = table;
};

void ITV_Table::add(ITV *element) {
	if (element) {
		this->table->push_back(*element);
	};
};

int ITV_Table::remove(ITV *element) {
	if (this->exists(element)) {
		this->table->remove(*element);
		return 1;
	};

	return 0;
};

int ITV_Table::exists(ITV *element) {
	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		if (*i == *element) {
			return 1;
		};
	};

	return 0;
};

ITV* ITV_Table::find_by_id(unsigned int id, bool reverse_direction) {
	list<ITV>::iterator i;
	if (reverse_direction) {
		for (i=this->table->end(); i!=this->table->begin(); --i) {
			if ((*i).get_id() == id) {
				return &(*i);
			};
		};
	} else {
		for (i=this->table->begin(); i!=this->table->end(); ++i) {
			if ((*i).get_id() == id) {
				return &(*i);
			};
		};
	};

	return NULL;
};

ITV* ITV_Table::find_by_tag(unsigned int tag, bool reverse_direction) {
	list<ITV>::iterator i;
	if (reverse_direction) {
		for (i=this->table->end(); i!=this->table->begin(); --i) {
			if ((*i).get_tag() == tag) {
				return &(*i);
			};
		};
	} else {
		for (i=this->table->begin(); i!=this->table->end(); ++i) {
			if ((*i).get_tag() == tag) {
				return &(*i);
			};
		};
	};

	return NULL;
};

ITV* ITV_Table::find_by_value(std::string value, bool reverse_direction) {
	list<ITV>::iterator i;
	if (reverse_direction) {
		for (i=this->table->end(); i!=this->table->begin(); --i) {
			if (!value.compare((*i).get_value())) {
				return &(*i);
			};
		};
	} else {
		for (i=this->table->begin(); i!=this->table->end(); ++i) {
			if (!value.compare((*i).get_value())) {
				return &(*i);
			};
		};
	};

	return NULL;
}

unsigned int* ITV_Table::convert(std::string value, unsigned int next) {
	unsigned int *retval = new unsigned int[2];
	ITV *itv_current = this->find_by_value(value, 0);
	ITV *itv_next = this->find_by_id(next, 0);

	if (itv_current == NULL || itv_next == NULL) { return NULL; }
	itv_next->replace(itv_current->get_id());
	itv_current->replace(next);

	retval[0] = itv_current->get_tag();
	retval[1] = itv_next->get_tag();

	return retval;
};

std::string ITV_Table::revert(unsigned int current, unsigned int next) {
	ITV *itv_current = this->find_by_id(current, 0);
	ITV *itv_next = this->find_by_id(next, 0);

	if (itv_current == NULL || itv_next == NULL) { return ""; }
	itv_current->replace(next);
	itv_next->replace(current);

	return itv_current->get_value();
}

void ITV_Table::clear() {
	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		(*i).clear();
	};
};

void ITV_Table::restore() {
	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		(*i).restore();
	};
};

unsigned int ITV_Table::get_random_id() {
	unsigned int id = get_random(0, this->table->size());
	list<ITV>::iterator i = this->table->begin();
	std::advance(i, id);
	return (*i).get_id();
};

void ITV_Table::load(ifstream &ifs) {
	if (!ifs.is_open()) { return; };
	this->table->clear();

	unsigned int x = min_id;
	std::string line = string();

	while(getline(ifs, line)) {
		this->add(new ITV(x++, trim(line)));
	};

	if (this->table->size() > 0) {
		this->table->unique();
	};
};

void ITV_Table::save(ofstream &ofs) {
	if (!ofs.is_open()) { return; };
	this->table->sort(compare_ids);

	list<ITV>::iterator i;
	for (i=this->table->begin(); i!=this->table->end(); ++i) {
		ofs << (*i).get_value() << endl;
	};
};

