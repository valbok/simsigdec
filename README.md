Simsigdec
=========================
Simple signature detector - an application to find a malware in target files, using predefined byte sequences that stored in text file in format:

    HexString.{id}

The application is splitted out by few layers.

* Core - is a scanner through sequences. And some utilities.
* Objects - separates jobs between threads, gets result from them using Qt signals/slots.
* Gui - visualizations of tasks.

Requirements
============

It requires Qt5 and cmake.

Build
=====

    $ cmake . ; make

and run

    $ cd gui; ./Simsigdec

Tests
=====

    $ cd core/tests; ./ScannerTest; ./configTest
