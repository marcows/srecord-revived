/*
 *	srecord - manipulate eprom load files
 *	Copyright (C) 1998 Peter Miller;
 *	All rights reserved.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * MANIFEST: interface definition for include/srec/input/filter/xor.cc
 */

#ifndef INCLUDE_SREC_INPUT_FILTER_XOR_H
#define INCLUDE_SREC_INPUT_FILTER_XOR_H

#pragma interface "srec_input_filter_xor"

#include <srec/input/filter.h>

class srec_input_filter_xor: public srec_input_filter
{
public:
	virtual ~srec_input_filter_xor();
	srec_input_filter_xor(srec_input *, int);
	virtual int read(srec_record &);

private:
	int value;
	srec_input_filter_xor();
	srec_input_filter_xor(const srec_input_filter_xor &);
	srec_input_filter_xor &operator=(const srec_input_filter_xor &);
};

#endif /* INCLUDE_SREC_INPUT_FILTER_XOR_H */