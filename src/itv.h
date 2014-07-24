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
#ifndef ITV_H
#define ITV_H

#include "itv_config.h"

using namespace std;

class ITV {
	friend ostream &operator << (ostream &, const ITV &);
	friend istream &operator >> (istream &, ITV &);

	protected:
		size_t id;
		size_t tag;
		std::string value;

	public:
		ITV();
		ITV(const ITV &);
		ITV(size_t, std::string);
		ITV(size_t, size_t, std::string);
		~ITV();

		ITV &operator = (const ITV &);
		bool operator == (const ITV &) const;
		bool operator != (const ITV &) const;
		bool operator <= (const ITV &) const;
		bool operator >= (const ITV &) const;
		bool operator  < (const ITV &) const;
		bool operator  > (const ITV &) const;

		size_t replace(size_t);

		size_t get_id();
		void set_id(size_t);

		size_t get_tag();
		void set_tag(size_t);

		std::string get_value();
		void set_value(std::string);

		void clear();
		void restore();

		std::string to_string();
};

#endif
