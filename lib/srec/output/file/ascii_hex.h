//
//      srecord - manipulate eprom load files
//      Copyright (C) 2000-2003, 2006, 2007 Peter Miller
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
//

#ifndef INCLUDE_SREC_OUTPUT_FILE_ASCII_HEX_H
#define INCLUDE_SREC_OUTPUT_FILE_ASCII_HEX_H


#include <lib/srec/output/file.h>

/**
  * The srec_output_file_ascii_hex class is used to write a file in
  * Ascii-Hex-Space format.
  */
class srec_output_file_ascii_hex:
    public srec_output_file
{
public:
    /**
      * The destrutcor.
      */
    virtual ~srec_output_file_ascii_hex();

    /**
      * The constructor.
      *
      * @param file_name
      *     The name of the file to be written.
      */
    srec_output_file_ascii_hex(const std::string &file_name);

protected:
    // See base class for documentation.
    void write(const srec_record &);

    // See base class for documentation.
    void line_length_set(int);

    // See base class for documentation.
    void address_length_set(int);

    // See base class for documentation.
    int preferred_block_size_get() const;

    // See base class for documentation.
    const char *format_name() const;

private:
    /**
      * The address instance variable is used to remember where we are
      * up to in the output.  Used to limit the number of $A line emitted.
      */
    unsigned long address;

    /**
      * The column instance variable is used to remember which column
      * we are up to in the output.  Used to limit the length of lines
      * in the output.
      */
    int column;

    /**
      * The pref_block_size instance variable is used to remember the
      * number of bytes in the preferred block size.
      */
    int pref_block_size;

    /**
      * The line_length instance variable is used to remember the
      * maximum length of text lines.
      */
    int line_length;

    /**
      * The address_length instance variable is used to remember
      * how many bytes of addresses are are to emit.
      */
    int address_length;

    /**
      * The start_code_emitted instance variable is used to remember
      * whether or not the start code (Ctrl-B) has been emitted.
      */
    bool start_code_emitted;

    /**
      * The end_code_emitted instance variable is used to remember
      * whether or not the end code (Ctrl-C) has been emitted.
      */
    bool end_code_emitted;

    /**
      * The emit_end_of_file method is used to write the ETX and
      * checksum out to the file.  It is safe top call this method more
      * than once, only one ETX will be written.
      */
    void emit_end_of_file();

    /**
      * The default constructor.  Do not use.
      */
    srec_output_file_ascii_hex();

    /**
      * The copy constructor.  Do not use.
      */
    srec_output_file_ascii_hex(const srec_output_file_ascii_hex &);

    /**
      * The assignment operator.  Do not use.
      */
    srec_output_file_ascii_hex &operator=(const srec_output_file_ascii_hex &);
};

#endif // INCLUDE_SREC_OUTPUT_FILE_ASCII_HEX_H
