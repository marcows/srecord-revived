#!/bin/sh
#
#	srecord - manipulate eprom load files
#	Copyright (C) 2006 Peter Miller;
#	All rights reserved.
#
#	This program is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 2 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program; if not, write to the Free Software
#	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
#
# MANIFEST: Test the intel hex functionality
#
here=`pwd`
if test $? -ne 0 ; then exit 2; fi
work=${TMP_DIR-/tmp}/$$

pass()
{
	cd $here
	rm -rf $work
	echo PASSED
	exit 0
}

fail()
{
	cd $here
	rm -rf $work
	echo 'FAILED test of the intel hex functionality'
	exit 1
}

no_result()
{
	cd $here
	rm -rf $work
	echo 'NO RESULT for test of the intel hex functionality'
	exit 2
}

trap "no_result" 1 2 3 15

bin=$here/${1-.}/bin
mkdir $work
if test $? -ne 0; then no_result; fi
cd $work
if test $? -ne 0; then no_result; fi

cat > test.in << 'fubar'
:200000000000C0C1C1810140C30103C00280C241C60106C00780C7410500C5C1C4810440A0
:20002000CC010CC00D80CD410F00CFC1CE810E400A00CAC1CB810B40C90109C00880C84100
:20004000D80118C01980D9411B00DBC1DA811A401E00DEC1DF811F40DD011DC01C80DC41E0
:200060001400D4C1D5811540D70117C01680D641D20112C01380D3411100D1C1D081104040
:20008000F00130C03180F1413300F3C1F28132403600F6C1F7813740F50135C03480F44120
:2000A0003C00FCC1FD813D40FF013FC03E80FE41FA013AC03B80FB413900F9C1F881384080
:2000C0002800E8C1E9812940EB012BC02A80EA41EE012EC02F80EF412D00EDC1EC812C4060
:2000E000E40124C02580E5412700E7C1E68126402200E2C1E3812340E10121C02080E041C0
:20010000A00160C06180A1416300A3C1A28162406600A6C1A7816740A50165C06480A4419F
:200120006C00ACC1AD816D40AF016FC06E80AE41AA016AC06B80AB416900A9C1A8816840FF
:200140007800B8C1B9817940BB017BC07A80BA41BE017EC07F80BF417D00BDC1BC817C40DF
:20016000B40174C07580B5417700B7C1B68176407200B2C1B3817340B10171C07080B0413F
:20018000500090C191815140930153C052809241960156C057809741550095C1948154401F
:2001A0009C015CC05D809D415F009FC19E815E405A009AC19B815B40990159C0588098417F
:2001C000880148C0498089414B008BC18A814A404E008EC18F814F408D014DC04C808C415F
:2001E000440084C185814540870147C046808641820142C043808341410081C180814040BF
:00000001FF
fubar
if test $? -ne 0; then no_result; fi

cat > test.ok << 'fubar'
:020000040020DA
:200000000000C0C1C1810140C30103C00280C241C60106C00780C7410500C5C1C4810440A0
:20002000CC010CC00D80CD410F00CFC1CE810E400A00CAC1CB810B40C90109C00880C84100
:20004000D80118C01980D9411B00DBC1DA811A401E00DEC1DF811F40DD011DC01C80DC41E0
:200060001400D4C1D5811540D70117C01680D641D20112C01380D3411100D1C1D081104040
:20008000F00130C03180F1413300F3C1F28132403600F6C1F7813740F50135C03480F44120
:2000A0003C00FCC1FD813D40FF013FC03E80FE41FA013AC03B80FB413900F9C1F881384080
:2000C0002800E8C1E9812940EB012BC02A80EA41EE012EC02F80EF412D00EDC1EC812C4060
:2000E000E40124C02580E5412700E7C1E68126402200E2C1E3812340E10121C02080E041C0
:20010000A00160C06180A1416300A3C1A28162406600A6C1A7816740A50165C06480A4419F
:200120006C00ACC1AD816D40AF016FC06E80AE41AA016AC06B80AB416900A9C1A8816840FF
:200140007800B8C1B9817940BB017BC07A80BA41BE017EC07F80BF417D00BDC1BC817C40DF
:20016000B40174C07580B5417700B7C1B68176407200B2C1B3817340B10171C07080B0413F
:20018000500090C191815140930153C052809241960156C057809741550095C1948154401F
:2001A0009C015CC05D809D415F009FC19E815E405A009AC19B815B40990159C0588098417F
:2001C000880148C0498089414B008BC18A814A404E008EC18F814F408D014DC04C808C415F
:2001E000440084C185814540870147C046808641820142C043808341410081C180814040BF
:00000001FF
fubar
if test $? -ne 0; then no_result; fi

$bin/srec_cat test.in -intel -offset 0x200000 -o test.out -inte > LOG 2>&1
if test $? -ne 0; then cat LOG; fail; fi

diff test.ok test.out
if test $? -ne 0; then fail; fi

#
# The things tested here, worked.
# No other guarantees are made.
#
pass