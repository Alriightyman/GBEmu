# Blargg's Gameboy hardware test ROMs

# Table of contents
1. [Game Boy Sound Hardware Tests](#sound)
2. [Game Boy CPU Instruction Behavior Test](#instr)
3. [Game Boy CPU Instruction Timing Test](#inst_timeing)
4. [Game Boy CPU Memory Access Timing Test](#memory)
5. [OAM Corruption Test](#oam)
6. 
## 1. Game Boy Sound Hardware Tests <a name="sound"></a>
These tests verify aspects of the sound hardware that the CPU can
observe. The ROMs and GBSs are either for DMG or CGB hardware, as there
are several differences.


### Multi-ROM
---------
In the main directory is a single ROM/GBS which runs all the tests. It
prints a test's number, runs the test, then "ok" if it passes, otherwise
a failure code. Once all tests have completed it either reports that all
tests passed, or reports the number of the first failed test as the
result code (1 = first). Finally, it makes several beeps. If a test
fails, it can be run on its own by finding the corresponding ROM/GBS in
the singles directories.

Ths compact format on screen is to avoid having the results scroll off
the top, so the test can be started and allowed to run without having to
constantly monitor the display. 


### Failure information
-------------------
For more information about a failure code or information printed, see
the test's source code in source/. To find failure code N, search for
"set_test N", which will usually be before the subtest which failed.


### Flashes, clicks, other glitches
-------------------------------
Some tests might need to turn the screen off and on, or cause slight
audio clicks. This does not indicate failure, and should be ignored.
Only the test result reported at the end is important, unless stated
otherwise.


### LCD support
-----------
Tests generally print information on screen. The tests will work fine if
run on an emulator with NO LCD support, or as an GBS which has no
inherent screen; in particular, the VBL wait routine has a timeout in
case LY doesn't reflect the current LCD line. The text printing will
also work if the LCD doesn't support scrolling.


### Output to memory
----------------
Text output and the final result are also written to memory at $A000,
allowing testing a very minimal emulator that supports little more than
CPU and RAM. To reliably indicate that the data is from a test and not
random data, $A001-$A003 are written with a signature: $DE,$B0,$61. If
this is present, then the text string and final result status are valid.

$A000 holds the overall status. If the test is still running, it holds
$80, otherwise it holds the final result code.

All text output is appended to a zero-terminated string at $A004. An
emulator could regularly check this string for any additional
characters, and output them, allowing real-time text output, rather than
just printing the final output at the end.


### GBS versions
------------
Many GBS-based tests require that the GBS player either not interrupt
the init routine with the play routine, or if they do, not interrupt the
play routine again if it hasn't returned yet. This is because many tests
need to run for a while without returning.

In addition to the other text output methods described above, GBS builds
report essential information bytes audibly, including the final result.
A byte is reported as a series of tones. The code is in binary, with a
low tone for 0 and a high tone for 1. The first tone is always a zero. A
final code of 0 means passed, 1 means failure, and 2 or higher indicates
a specific reason as listed in the source code by the corresponding
set_code line. Examples:

Tones         Binary  Decimal  Meaning
- - - - - - - - - - - - - - - - - - - - 
low             0       0      passed
low high        01      1      failed
low high low   010      2      error 2

### ROMS for Sound Testion
----------------
- cgb_sound.gb
- dmg_sound.gb

## 2. Game Boy CPU Instruction Behavior Test <a name="instr"></a>
This ROM tests the behavior of all CPU instructions except STOP and the
11 illegal opcodes. The tests are fairly thorough, running instructions
with boundary data and verifying both the result and that other
registers are not modified. Instructions which perform the same
operation on different registers are each tested just as thoroughly, in
case an emulator implements each independently. Some sub-tests take half
minute to complete.

Failed instructions are listed as

	[CB] opcode

Some errors cannot of course be diagnosed properly, since the test
framework itself relies on basic instruction behavior being correct.


### Internal operation
------------------
The main tests use a framework that runs each instruction in a loop,
varying the register values on input and examining them on output.
Rather than keep a table of correct values, it simply calculates a
CRC-32 checksum of all the output, then compares this with the correct
value. Instructions are divided into several groups, each with a
different set of input values suited for their behavior; for example,
the bit test instructions are fed $01, $02, $04 ... $40, $80, to ensure
each bit is handled properly, while the arithmetic instructions are fed
$01, $0F, $10, $7F, $FF, to exercise carry and half-carry. A few
instructions require a custom test due to their uniqueness.


### Multi-ROM
---------
In the main directory is a single ROM which runs all the tests. It
prints a test's number, runs the test, then "ok" if it passes, otherwise
a failure code. Once all tests have completed it either reports that all
tests passed, or prints the number of failed tests. Finally, it makes
several beeps. If a test fails, it can be run on its own by finding the
corresponding ROM in individual/.

Ths compact format on screen is to avoid having the results scroll off
the top, so the test can be started and allowed to run without having to
constantly monitor the display. 

Currently there is no well-defined way for an emulator test rig to
programatically find the result of the test; contact me if you're trying
to do completely automated testing of your emulator. One simple approach
is to take a screenshot after all tests have run, or even just a
checksum of one, and compare this with a previous run.


### Failure codes
-------------
Failed tests may print a failure code, and also short description of the
problem. For more information about a failure code, look in the
corresponding source file in source/; the point in the code where
"set_test n" occurs is where that failure code will be generated.
Failure code 1 is a general failure of the test; any further information
will be printed.

Note that once a sub-test fails, no further tests for that file are run.


### Console output
--------------
Information is printed on screen in a way that needs only minimum LCD
support, and won't hang if LCD output isn't supported at all.
Specifically, while polling LY to wait for vblank, it will time out if
it takes too long, so LY always reading back as the same value won't
hang the test. It's also OK if scrolling isn't supported; in this case,
text will appear starting at the top of the screen.

Everything printed on screen is also sent to the game link port by
writing the character to SB, then writing $81 to SC. This is useful for
tests which print lots of information that scrolls off screen.

### Internal framework operation
----------------------------
Tests use a common framework for setting things up, reporting results,
and ending. All files first include "shell.inc", which sets up the ROM
header and shell code, and includes other commonly-used modules.

One oddity is that test code is first copied to internal RAM at $D000,
then executed there. This allows self-modification, and ensures the code
is executed the same way it is on my devcart, which doesn't have a
rewritable ROM as most do.

Some macros are used to simplify common tasks:

	Macro               Behavior
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	wreg addr,data      Writes data to addr using LDH
	lda  addr           Loads byte from addr into A using LDH
	sta  addr           Stores A at addr using LDH
	delay n             Delays n cycles, where NOP = 1 cycle
	delay_msec n        Delays n milliseconds
	set_test n,"Cause"  Sets failure code and optional string

Routines and macros are documented where they are defined.

## 3. Game Boy CPU Instruction Timing Test <a name="inst_timeing"></a>
This ROM tests the timings of all CPU instructions except HALT, STOP,
and the 11 illegal opcodes. For conditional instructions, it tests taken
and not taken timings. This test requires proper timer operation (TAC,
TIMA, TMA).

Failed instructions are listed as

	[CB] opcode:measured time-correct time

Times are in terms of instruction cycles, where NOP takes one cycle.


### Verified cycle timing tables
----------------------------
The test internally uses a table of proper cycle times, which can be
used in an emulator to ensure proper timing. The only changes below are
removal of the .byte prefixes, and addition of commas at the ends, so
that they can be used without changes in most programming languages. For
added correctness assurance, the original tables can be found at the end
of the source code.

Normal instructions:

	1,3,2,2,1,1,2,1,5,2,2,2,1,1,2,1,
	0,3,2,2,1,1,2,1,3,2,2,2,1,1,2,1,
	2,3,2,2,1,1,2,1,2,2,2,2,1,1,2,1,
	2,3,2,2,3,3,3,1,2,2,2,2,1,1,2,1,
	1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
	1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
	1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
	2,2,2,2,2,2,0,2,1,1,1,1,1,1,2,1,
	1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
	1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
	1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
	1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,
	2,3,3,4,3,4,2,4,2,4,3,0,3,6,2,4,
	2,3,3,0,3,4,2,4,2,4,3,0,3,0,2,4,
	3,3,2,0,0,4,2,4,4,1,4,0,0,0,2,4,
	3,3,2,1,0,4,2,4,3,2,4,1,0,0,2,4

CB-prefixed instructions:

	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,3,2,2,2,2,2,2,2,3,2,
	2,2,2,2,2,2,3,2,2,2,2,2,2,2,3,2,
	2,2,2,2,2,2,3,2,2,2,2,2,2,2,3,2,
	2,2,2,2,2,2,3,2,2,2,2,2,2,2,3,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2,
	2,2,2,2,2,2,4,2,2,2,2,2,2,2,4,2


### Internal operation
------------------
Before each instruction is executed, the test sets up registers and
memory in such a way that the instruction will cleanly execute and then
end up at a common destination, without trashing anything important. The
timing itself is done by first synchronizing to the timer via a loop,
executing the instruction, then using a similar loop to determine how
many clocks elapsed.


### Failure codes
-------------
Failed tests may print a failure code, and also short description of the
problem. For more information about a failure code, look in the
corresponding source file in source/; the point in the code where
"set_test n" occurs is where that failure code will be generated.
Failure code 1 is a general failure of the test; any further information
will be printed.

Note that once a sub-test fails, no further tests for that file are run.


### Console output
--------------
Information is printed on screen in a way that needs only minimum LCD
support, and won't hang if LCD output isn't supported at all.
Specifically, while polling LY to wait for vblank, it will time out if
it takes too long, so LY always reading back as the same value won't
hang the test. It's also OK if scrolling isn't supported; in this case,
text will appear starting at the top of the screen.

Everything printed on screen is also sent to the game link port by
writing the character to SB, then writing $81 to SC. This is useful for
tests which print lots of information that scrolls off screen.


### Internal framework operation
----------------------------
Tests use a common framework for setting things up, reporting results,
and ending. All files first include "shell.inc", which sets up the ROM
header and shell code, and includes other commonly-used modules.

One oddity is that test code is first copied to internal RAM at $D000,
then executed there. This allows self-modification, and ensures the code
is executed the same way it is on my devcart, which doesn't have a
rewritable ROM as most do.

Some macros are used to simplify common tasks:

	Macro               Behavior
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	wreg addr,data      Writes data to addr using LDH
	lda  addr           Loads byte from addr into A using LDH
	sta  addr           Stores A at addr using LDH
	delay n             Delays n cycles, where NOP = 1 cycle
	delay_msec n        Delays n milliseconds
	set_test n,"Cause"  Sets failure code and optional string

Routines and macros are documented where they are defined.

## 4. Game Boy CPU Memory Access Timing Test <a name="memory"></a>

This ROM tests the timing of memory reads and writes made by
instructions, except stack and program counter accesses. These tests
require correct instruction timing and proper timer operation (TAC,
TIMA, TMA).

The read and write tests list failing instructions as

	[CB] opcode:tested-correct

The read-modify-write test lists failing instructions as 

	[CB] opcode:tested read/tested write-correct read/correct write

The values after the opcode refer to which instruction cycle the access
occurs on, with 1 being the first. If a time couldn't be determined due
to some other problem, it prints 0.

For instructions which either read or write, but not both, the CPU makes
the access on the last cycle. For instructions which read, modify, then
write back, the CPU reads on the next-to-last cycle, and writes on the
last cycle.


### Internal operation
------------------
The tests have the timer increment TIMA every 64 cycles, synchronize
with this, delay a variable amount, then have the instruction under test
access the timer. By varying the delay in one-cycle increments, the
memory access made by the instruction can be made to fall before and
after a TIMA increment. By then examining the registers and value in
TIMA, it can be determined which occurred.


### Multi-ROM
---------
In the main directory is a single ROM which runs all the tests. It
prints a test's number, runs the test, then "ok" if it passes, otherwise
a failure code. Once all tests have completed it either reports that all
tests passed, or prints the number of failed tests. Finally, it makes
several beeps. If a test fails, it can be run on its own by finding the
corresponding ROM in individual/.

Ths compact format on screen is to avoid having the results scroll off
the top, so the test can be started and allowed to run without having to
constantly monitor the display. 

Currently there is no well-defined way for an emulator test rig to
programatically find the result of the test; contact me if you're trying
to do completely automated testing of your emulator. One simple approach
is to take a screenshot after all tests have run, or even just a
checksum of one, and compare this with a previous run.


### Failure codes
-------------
Failed tests may print a failure code, and also short description of the
problem. For more information about a failure code, look in the
corresponding source file in source/; the point in the code where
"set_test n" occurs is where that failure code will be generated.
Failure code 1 is a general failure of the test; any further information
will be printed.

Note that once a sub-test fails, no further tests for that file are run.


### Console output
--------------
Information is printed on screen in a way that needs only minimum LCD
support, and won't hang if LCD output isn't supported at all.
Specifically, while polling LY to wait for vblank, it will time out if
it takes too long, so LY always reading back as the same value won't
hang the test. It's also OK if scrolling isn't supported; in this case,
text will appear starting at the top of the screen.

Everything printed on screen is also sent to the game link port by
writing the character to SB, then writing $81 to SC. This is useful for
tests which print lots of information that scrolls off screen.

### Internal framework operation
----------------------------
Tests use a common framework for setting things up, reporting results,
and ending. All files first include "shell.inc", which sets up the ROM
header and shell code, and includes other commonly-used modules.

One oddity is that test code is first copied to internal RAM at $D000,
then executed there. This allows self-modification, and ensures the code
is executed the same way it is on my devcart, which doesn't have a
rewritable ROM as most do.

Some macros are used to simplify common tasks:

	Macro               Behavior
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	wreg addr,data      Writes data to addr using LDH
	lda  addr           Loads byte from addr into A using LDH
	sta  addr           Stores A at addr using LDH
	delay n             Delays n cycles, where NOP = 1 cycle
	delay_msec n        Delays n milliseconds
	set_test n,"Cause"  Sets failure code and optional string

Routines and macros are documented where they are defined.

## 5. OAM Corruption Test <a name="oam"></a>

* Verifies OAM corruption bug on DMG.

* Occurs when 16-bit increment/decrement is made of value in range $FE00
to $FEFF, during around the first 20 cycles of a visible scanline while
LCD is on, where 114 cycles = 1 scanline.

* Causes several bytes of OAM to be copied from one place to another.

* Occurs with instructions that do increment:
	INC rp (including SP)
	DEC rp
	POP rp      counts as two increments
	PUSH rp     counts as two increments
	LD A,(HL+)
	LD A,(HL-)

* Doesn't occur with instructions that do 16-bit add:
	LD HL,SP+n
	ADD HL,rp
	ADD SP,n

* Doesn't occur anytime during the 10 vblank scanlines.

* Doesn't occur when LCD is off, no matter when it happens.

* Corruption depends on when it occurs.


### Multi-ROM
---------
In the main directory is a single ROM/GBS which runs all the tests. It
prints a test's number, runs the test, then "ok" if it passes, otherwise
a failure code. Once all tests have completed it either reports that all
tests passed, or reports the number of the first failed test as the
result code (1 = first). Finally, it makes several beeps. If a test
fails, it can be run on its own by finding the corresponding ROM/GBS in
the singles directories.

Ths compact format on screen is to avoid having the results scroll off
the top, so the test can be started and allowed to run without having to
constantly monitor the display. 


### Failure information
-------------------
For more information about a failure code or information printed, see
the test's source code in source/. To find failure code N, search for
"set_test N", which will usually be before the subtest which failed.


### Flashes, clicks, other glitches
-------------------------------
Some tests might need to turn the screen off and on, or cause slight
audio clicks. This does not indicate failure, and should be ignored.
Only the test result reported at the end is important, unless stated
otherwise.


### LCD support
-----------
Tests generally print information on screen. The tests will work fine if
run on an emulator with NO LCD support, or as an GBS which has no
inherent screen; in particular, the VBL wait routine has a timeout in
case LY doesn't reflect the current LCD line. The text printing will
also work if the LCD doesn't support scrolling.


### Output to memory
----------------
Text output and the final result are also written to memory at $A000,
allowing testing a very minimal emulator that supports little more than
CPU and RAM. To reliably indicate that the data is from a test and not
random data, $A001-$A003 are written with a signature: $DE,$B0,$61. If
this is present, then the text string and final result status are valid.

$A000 holds the overall status. If the test is still running, it holds
$80, otherwise it holds the final result code.

All text output is appended to a zero-terminated string at $A004. An
emulator could regularly check this string for any additional
characters, and output them, allowing real-time text output, rather than
just printing the final output at the end.


### GBS versions
------------
Many GBS-based tests require that the GBS player either not interrupt
the init routine with the play routine, or if they do, not interrupt the
play routine again if it hasn't returned yet. This is because many tests
need to run for a while without returning.

In addition to the other text output methods described above, GBS builds
report essential information bytes audibly, including the final result.
A byte is reported as a series of tones. The code is in binary, with a
low tone for 0 and a high tone for 1. The first tone is always a zero. A
final code of 0 means passed, 1 means failure, and 2 or higher indicates
a specific reason as listed in the source code by the corresponding
set_code line. Examples:

Tones         Binary  Decimal  Meaning
- - - - - - - - - - - - - - - - - - - - 
low             0       0      passed
low high        01      1      failed
low high low   010      2      error 2

