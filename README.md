Libopencm3 Example Project
==========================

People often ask me how to create a project with libopencm3. They have an ARM 
Cortex-M board, and they want to use libopencm3 to write some embedded programs.
This repo provides a skeleton for that sort of project. If you would like to
clone it to play with it feel free, to do so use the command:

`git clone --recursive git@github.com:/ChuckM/nucleo446`

Here at the top level of the project there are two files and two directories.

The files are `Makefile.include` and `rules.mk`. These were borrowed from the
libopencm3-examples repo because they encapsulate a lot of what is necessary to
build a libopencm3 based application. The `Makefile.include` has in it the
specific instructions to build an application based on the STM32F4 (which the
Nucleo F446 has). The `rules.mk` file contains generic rules for **all** targets
so it gets after the included makefile. They have been modified from the example
repository by fixing up some relative paths that work repositories that are
structured like this one.

The directories are `libopencm3` and `apps`. The `libopencm3` directory is
special, it is actually a git sub-module and is associated with the master
respository for libopencm3. The reason you create your repo this way is so that
you can use libopencm3 at the exact commit point where all your code works, and
if the library changes, you won't have your repository broken. You can upgrade
your repository at your leisure.  Additionally, if libopencm3 isn't moving fast
enough for you, it is possible to create a branch of the library in your
repository and then add your fixes locally. Anyone who checks out your
application repository will get your fixes as well and so everything will still
just work. The other directory is much more boring, its the `apps` directory.
We'll describe that next.

`apps` are the various standalone applications that you can run on your board.
If you are familiar with the libopencm3 examples repository these are like the
individual examples for a specific board. At this writing I am not sure how many
apps will be in this repository but one I know that will be there is `blink`
which helps show off the next layer.

## Individual Applications

An individual application directory (like `blink`) will have at least two files,
one called `Makefile` and one which is the C source file that contains the
`main()` function. For `blink` these are `Makefile` and `blink.c`.

Makefile contains the following:
```
BINARY = blink

DEVICE = STM32F446RE

include ../../Makefile.include
```

That is it. Just the three non-blank lines. The first says our binary will be
called `blink`, the second identified what chip we are using (this is important
for generating a linker script that identifies where flash memory and RAM are on
this particular chip), and the last line invokes the `Makefile.include` file
from the top directory. That file will then include `rules.mk` and build all the
files you need to load `blink.elf` onto your board and debug it.

## Using multiple object files

Sometimes you will have some code that is common to all of the applications you
are running that you will want to use. We have an example of such code in this
repository which sets up the clock tree
for the chip and sets up the SysTick timer to interrupt every millesecond and to
count the current number of milleseconds since the code started. This code is in
the file `clock.c` in the directory `util`. It also has an include file which
describes its functions and this is named `clock.h` and also in the `util`
directory. You can see how we use it in the `blink_tick` application directory. 

In the `blink_tick` directory look at the `Makefile`. It adds an additional line
so it now looks like this:

```
OBJS = ../util/clock.o

BINARY = blink_tick

DEVICE = STM32F446RE

include ../../Makefile.include
```

The make variable `OBJS` will tell make that it should compile the `clock.c`
file that is in the sibling directory named `util` and add the resulting object
to the link line for the application `blink_tick`.  In the source code for
`blink_tick` we add an additional include of the form `#include "../util/clock.h"`
which tells the compiler to include the header file from the sibling utility
directory when it is compiling `blink_tick.c`. 
