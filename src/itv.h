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
#ifndef ITV_H
#define ITV_H

#include <iostream>

using namespace std;

class ITV {
	protected:
		size_t id;
		size_t tag;
		size_t value;

	public:
		ITV();
		ITV(const ITV &);
		ITV(size_t, size_t);
		ITV(size_t, size_t, size_t);
		~ITV();

		ITV &operator = (const ITV &);
		bool operator == (const ITV &) const;
		bool operator != (const ITV &) const;
		bool operator <= (const ITV &) const;
		bool operator >= (const ITV &) const;
		bool operator  < (const ITV &) const;
		bool operator  > (const ITV &) const;

		void clear();
		void restore();
		size_t replace(size_t);

		size_t get_id() const;
		void set_id(size_t);

		size_t get_tag() const;
		void set_tag(size_t);

		size_t get_value() const;
		void set_value(size_t);
};

bool compare_ids(ITV &first, ITV &second);
bool compare_tags(ITV &first, ITV &second);

#endif
