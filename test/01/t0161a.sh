#!/bin/sh
#
#       srecord - Manipulate EPROM load files
#       Copyright (C) 2008 Peter Miller
#
#       This program is free software; you can redistribute it and/or modify
#       it under the terms of the GNU General Public License as published by
#       the Free Software Foundation; either version 3 of the License, or
#       (at your option) any later version.
#
#       This program is distributed in the hope that it will be useful,
#       but WITHOUT ANY WARRANTY; without even the implied warranty of
#       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#       GNU General Public License for more details.
#
#       You should have received a copy of the GNU General Public License
#       along with this program. If not, see
#       <http://www.gnu.org/licenses/>.
#

TEST_SUBJECT="exclusive filters"
. test_prelude

cat > test.in << 'fubar'
S00600004844521B
S111000448656C6C6F2C20576F726C64210A77
S111010048656C6C6F2C20576F726C64210A7A
S5030002FA
S9030000FC
fubar
if test $? -ne 0; then no_result; fi

# ---------- be-excl-len ---------------------------------------------------

cat > test.ok << 'fubar'
S00600004844521B
S111000448656C6C6F2C20576F726C64210A77
S111010048656C6C6F2C20576F726C64210A7A
S10702000000010AEB
S5030003F9
S9030000FC
fubar
if test $? -ne 0; then no_result; fi

srec_cat test.in -beelen 0x200 -o test.out
if test $? -ne 0; then fail; fi

diff test.ok test.out
if test $? -ne 0; then fail; fi

# ---------- le-excl-len ---------------------------------------------------

cat > test.ok << 'fubar'
S00600004844521B
S111000448656C6C6F2C20576F726C64210A77
S111010048656C6C6F2C20576F726C64210A7A
S10702000A010000EB
S5030003F9
S9030000FC
fubar
if test $? -ne 0; then no_result; fi

srec_cat test.in -leelen 0x200 -o test.out
if test $? -ne 0; then fail; fi

diff test.ok test.out
if test $? -ne 0; then fail; fi

# ---------- be-excl-max ---------------------------------------------------

cat > test.ok << 'fubar'
S00600004844521B
S111000448656C6C6F2C20576F726C64210A77
S111010048656C6C6F2C20576F726C64210A7A
S10702000000010EE7
S5030003F9
S9030000FC
fubar
if test $? -ne 0; then no_result; fi

srec_cat test.in -beemax 0x200 -o test.out
if test $? -ne 0; then fail; fi

diff test.ok test.out
if test $? -ne 0; then fail; fi

# ---------- le-excl-max ---------------------------------------------------

cat > test.ok << 'fubar'
S00600004844521B
S111000448656C6C6F2C20576F726C64210A77
S111010048656C6C6F2C20576F726C64210A7A
S10702000E010000E7
S5030003F9
S9030000FC
fubar
if test $? -ne 0; then no_result; fi

srec_cat test.in -leemax 0x200 -o test.out
if test $? -ne 0; then fail; fi

diff test.ok test.out
if test $? -ne 0; then fail; fi

# ---------- be-excl-min ---------------------------------------------------

cat > test.ok << 'fubar'
S00600004844521B
S111000448656C6C6F2C20576F726C64210A77
S111010048656C6C6F2C20576F726C64210A7A
S107020000000004F2
S5030003F9
S9030000FC
fubar
if test $? -ne 0; then no_result; fi

srec_cat test.in -beemin 0x200 -o test.out
if test $? -ne 0; then fail; fi

diff test.ok test.out
if test $? -ne 0; then fail; fi

# ---------- le-excl-min ---------------------------------------------------

cat > test.ok << 'fubar'
S00600004844521B
S111000448656C6C6F2C20576F726C64210A77
S111010048656C6C6F2C20576F726C64210A7A
S107020004000000F2
S5030003F9
S9030000FC
fubar
if test $? -ne 0; then no_result; fi

srec_cat test.in -leemin 0x200 -o test.out
if test $? -ne 0; then fail; fi

diff test.ok test.out
if test $? -ne 0; then fail; fi

#
# The things tested here, worked.
# No other guarantees are made.
#
pass

# vim:ts=8:sw=4:et