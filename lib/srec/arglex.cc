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
 * MANIFEST: functions to impliment the srec_arglex class
 */

#pragma implementation

#include <iostream.h>

#include <srec/arglex.h>
#include <srec/input/file/intel.h>
#include <srec/input/file/srecord.h>
#include <srec/input/filter/offset.h>
#include <srec/output/file/intel.h>
#include <srec/output/file/srecord.h>


srec_arglex::srec_arglex()
{
	/* bug */
}


srec_arglex::srec_arglex(int argc, char **argv)
	: arglex(argc, argv)
{
	static table_ty table[] =
	{
		{ "-Intel",	token_intel,	},
		{ "-Motorola",	token_motorola,	},
		{ "-OFfset",	token_offset,	},
		{ "-Output",	token_output,	},
		{ "-S_record",	token_motorola,	},
		ARGLEX_END_MARKER
	};

	table_set(table);
}


srec_arglex::srec_arglex(const srec_arglex &)
{
	/* bug */
}


srec_arglex &
srec_arglex::operator=(const srec_arglex &)
{
	/* bug */
	return *this;
}


srec_arglex::~srec_arglex()
{
	/* bug */
}


srec_input *
srec_arglex::get_input()
{
	/*
	 * determine the file name
	 */
	const char *fn = "-";
	switch (token_cur())
	{
	default:
		assert(0);
		break;

	case token_string:
		fn = value_string();
		token_next();
		break;

	case token_stdio:
		token_next();
		break;
	}

	/*
	 * determine the file format
	 * and open the input file
	 */
	srec_input *ifp;
	switch (token_cur())
	{
	case token_motorola:
		token_next();
		/* fall through... */

	default:
		ifp = new srec_input_file_srecord(fn);
		break;

	case token_intel:
		token_next();
		ifp = new srec_input_file_intel(fn);
		break;
	}

	/*
	 * apply any filters specified
	 */
	for (;;)
	{
		switch (token_cur())
		{
		case token_offset:
			if (token_next() != token_number)
			{
				cerr << "the -offset option requires a numeric argument" << endl;
				exit(1);
			}
			ifp = new srec_input_filter_offset(ifp, value_number());
			token_next();
			continue;

		default:
			break;
		}
		break;
	}

	/*
	 * return the input stream determined
	 */
	return ifp;
}


srec_output *
srec_arglex::get_output()
{
	/*
	 * skip the -output token
	 */
	if (token_cur() == token_output)
		token_next();

	/*
	 * determine the file name
	 */
	const char *fn = "-";
	switch (token_cur())
	{
	default:
		break;

	case token_stdio:
		token_next();
		break;

	case token_string:
		fn = value_string();
		token_next();
		break;
	}

	/*
	 * determine the file format
	 */
	srec_output *ofp;
	switch (token_cur())
	{
	case token_motorola:
		token_next();
		/* fall through... */

	default:
		ofp = new srec_output_file_srecord(fn);
		break;

	case token_intel:
		token_next();
		ofp = new srec_output_file_intel(fn);
		break;
	}

	/*
	 * return the stream determined
	 */
	return ofp;
}
