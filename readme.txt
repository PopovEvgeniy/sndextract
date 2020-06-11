                              SND EXTRACT

                    Mugen sound extractor by Popov Evgeniy Alekseyevich

                             Version 2.3.9


System requirement

52 kilobytes free space on storage media.

Description and usage

This program is created for extract a sound from games that built on MUGEN game engine.
This program takes a target file name as command line argument. 

Exit codes

0 - Operation successfully complete.
1 - Can't open input file.
2 - Can't create output file.
3 - Can't jump to target offset.
4 - Can't allocate memory.
5 - Invalid format.

License

This program distributed under GNU GENERAL PUBLIC LICENSE.

Source code

The program source code was compiled under Open Watcom.
But you can do it under any modern C compiler.
Source code can be compiled for wide range operation systems, but you need create makefile or build script by yourself.
I provide only two things: compiled binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow this steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.
Run as root for install: make install
Run as root for uninstall: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

1.0 — 1.9.2.5 — Internal unstable build.
1.9.2.6 — First stable version.
1.9.2.7 — First public version.
1.9.2.8 — Experimental build.
1.9.2.9 — 2.2.3 - Stable branch builds.
2.2.4 - 2.3 - Small changes.
2.3.1 - Source code was improved. Linux support has been added.
2.3.1.0.1 – Documentation was updated.
2.3.2 - 2.3.5 - Small changes.
2.3.5.1 - Makefile was updated.
2.3.6 - 2.3.9 - Small changes.