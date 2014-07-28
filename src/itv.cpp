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

ITV::ITV() {
	id = 0;
	tag = 0;
	value = "";
};

ITV::ITV(const ITV &src) {
	id = src.id;
	tag = src.tag;
	value = src.value;
};

ITV::ITV(size_t id, const std::string &value) {
	this->id = id;
	this->tag = id;
	this->value = value;
};

ITV::ITV(size_t id, size_t tag, const std::string &value) {
	this->id = id;
	this->tag = tag;
	this->value = value;
};

ITV::~ITV() {
	// nothing todo
};

ostream &operator << (ostream &output, const ITV &itv) {
	output << itv.id << ITV_SEPARATOR << itv.tag << ITV_SEPARATOR << itv.value << ITV_TERMINATOR;
	return output;
};

istream &operator >> (istream &input, ITV &itv) {
	size_t id, tag;
	std::string value;
	input >> id >> tag >> value;
	itv = ITV(id, tag, value);
	return input;
};

ITV& ITV::operator=(const ITV &rhs) {
	this->id = rhs.id;
	this->tag = rhs.tag;
	this->value = rhs.tag;
	return *this;
};

bool ITV::operator==(const ITV &rhs) const {
	return (!this->value.compare(rhs.value));
};

bool ITV::operator!=(const ITV &rhs) const {
	return (this->value.compare(rhs.value));
};

bool ITV::operator<=(const ITV &rhs) const {
	return (this->value.compare(rhs.value) <= 0);
};

bool ITV::operator>=(const ITV &rhs) const {
	return (this->value.compare(rhs.value) >= 0);
};

bool ITV::operator<(const ITV &rhs) const {
	return (this->value.compare(rhs.value) < 0);
};

bool ITV::operator>(const ITV &rhs) const {
	return (this->value.compare(rhs.value) > 0);
};

size_t ITV::replace(size_t id) {
	size_t retval = this->tag;
	this->tag = this->id;
	this->id = id;
	return retval;
};

size_t ITV::get_id() {
	return this->id;
};

void ITV::set_id(size_t id) {
	this->id = id;
};

size_t ITV::get_tag() {
	return this->tag;
};

void ITV::set_tag(size_t tag) {
	this->tag = tag;
};

const std::string ITV::get_value() {
	return this->value;
};

void ITV::set_value(const std::string &value) {
	this->value = value;
};

void ITV::clear() {
	this->tag = this->id;
};

void ITV::restore() {
	this->id = this->tag;
};

const std::string ITV::to_string() {
	std::stringstream ss;
	ss << this->id << ITV_SEPARATOR << this->value << ITV_TERMINATOR;
	return ss.str();
};

