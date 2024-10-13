                              SND EXTRACT

                    Mugen sound extractor by Popov Evgeniy Alekseyevich

                             Version 2.5.6


System requirements

68 kilobytes of free space on storage media.

Description and usage

This program lets you extract sounds from games that are built on the MUGEN game engine.
This program takes a target file name as the command-line argument.

Exit codes

0 - Operation was successfully completed.
1 - Can't open the input file.
2 - Can't create the output file.
3 - Can't jump to the target offset.
4 - Can't allocate memory.
5 - Invalid format.

License

This program is distributed under GNU GENERAL PUBLIC LICENSE.

Source code

The code was compiled under Open Watcom.
But you can do it under any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Contact

You can send me a letter at tuzik87@inbox.ru.

Version history

1.0 — 1.9.2.5: The internal unstable builds.
1.9.2.6: The first stable version.
1.9.2.7: The first public version.
1.9.2.8: The experimental build.
1.9.2.9 — 2.2.3: The stable branch.
2.2.4 — 2.3: Small changes.
2.3.1: The source code improved. Linux support has been added.
2.3.1.0.1: Documentation updated.
2.3.2 — 2.3.5: Small changes.
2.3.5.1: The makefile updated.
2.3.6 — 2.3.9: Small changes.
2.4: A small bug is fixed.
2.4.0.1 — 2.4.0.2: The makefile updated.
2.5 — 2.5.4: Small changes.
2.5.5: Visual C++ support improved.
2.5.5.1: Documentation updated.
2.5.6: Small changes.