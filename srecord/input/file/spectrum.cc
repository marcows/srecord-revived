//
//      srecord - manipulate eprom load files
//      Copyright (C) 2003, 2006-2008, 2010 Peter Miller
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program. If not, see
//      <http://www.gnu.org/licenses/>.
//

#include <cctype>

#include <srecord/input/file/spectrum.h>
#include <srecord/record.h>


srec_input_file_spectrum::~srec_input_file_spectrum()
{
}


srec_input_file_spectrum::srec_input_file_spectrum(
        const std::string &a_file_name) :
    srec_input_file(a_file_name),
    header_seen(false),
    trailer_seen(false),
    file_contains_data(false)
{
}


srec_input::pointer
srec_input_file_spectrum::create(const std::string &a_file_name)
{
    return pointer(new srec_input_file_spectrum(a_file_name));
}


int
srec_input_file_spectrum::get_decimal()
{
    int c;
    for (;;)
    {
        c = get_char();
        if (c < 0)
        {
            format_error:
            fatal_error("decimal number expected");
        }
        if (isspace((unsigned char)c))
            continue;
        if (!isdigit((unsigned char)c))
            goto format_error;
        break;
    }
    int result = c - '0';
    for (;;)
    {
        c = get_char();
        if (c < 0)
            break;
        if (!isdigit((unsigned char)c))
        {
            get_char_undo(c);
            break;
        }
        result = (result * 10) + (c - '0');
    }
    return result;
}


static inline bool
is_binary_digit(int c)
{
    return ((c == '0' || c == '1'));
}


int
srec_input_file_spectrum::get_binary()
{
    int c;
    for (;;)
    {
        c = get_char();
        if (c < 0)
        {
            format_error:
            fatal_error("binary number expected");
        }
        if (isspace((unsigned char)c))
            continue;
        if (!is_binary_digit((unsigned char)c))
            goto format_error;
        break;
    }
    int result = c - '0';
    for (;;)
    {
        c = get_char();
        if (!is_binary_digit(c))
        {
            get_char_undo(c);
            break;
        }
        result = (result << 1) + (c - '0');
    }
    return result;
}


bool
srec_input_file_spectrum::read(srec_record &record)
{
    //
    // Check for the file header
    //
    if (!header_seen)
    {
        bool garbage_warning = false;
        for (;;)
        {
            int c = get_char();
            if (c < 0)
                fatal_error("no start character");
            if (c == 2)
            {
                header_seen = true;
                break;
            }
            if (!garbage_warning)
            {
                warning("ignoring garbage lines");
                garbage_warning = true;
            }
        }
    }

    //
    // Check for the file trailer.
    //
    if (trailer_seen)
        return false;
    for (;;)
    {
        int c = get_char();
        if (c < 0 || c == 3)
        {
            if (!file_contains_data)
                fatal_error("file contains no data");
            trailer_seen = true;
            return false;
        }
        if (isspace((unsigned char)c))
            continue;
        get_char_undo(c);
        break;
    }

    unsigned long address = get_decimal();
    unsigned char data = get_binary();
    record = srec_record(srec_record::type_data, address, &data, 1);
    file_contains_data = true;
    return true;
}

const char *
srec_input_file_spectrum::get_file_format_name ()
    const
{
    return "Spectrum";
}