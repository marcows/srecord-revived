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
 * MANIFEST: functions to impliment the srec_input_filter_or class
 */

#pragma implementation "srec_input_filter_or"

#include <srec/input/filter/or.h>
#include <srec/record.h>


srec_input_filter_or::srec_input_filter_or()
	: srec_input_filter(), value(0)
{
}


srec_input_filter_or::srec_input_filter_or(srec_input *a1, int a2)
	: srec_input_filter(a1), value(a2)
{
}


srec_input_filter_or::srec_input_filter_or(const srec_input_filter_or &arg)
	: srec_input_filter(arg), value(arg.value)
{
}


srec_input_filter_or &
srec_input_filter_or::operator=(const srec_input_filter_or &arg)
{
	srec_input_filter::operator=(arg);
	value = arg.value;
	return *this;
}


srec_input_filter_or::~srec_input_filter_or()
{
}


int
srec_input_filter_or::read(srec_record &record)
{
	if (!srec_input_filter::read(record))
		return 0;
	if (record.get_type() == srec_record::type_data)
	{
		for (int j = 0; j < record.get_length(); ++j)
			record.set_data(j, record.get_data(j) | value);
	}
	return 1;
}