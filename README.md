Simsigdec
=========================
Simple signature detector - an application to find a malware in target files, using predefined byte sequences that stored in text file in format:

    HexString.{id}

or

    69662840245f504f5354.{1}

The main point of this solution - an example of how to search signatures in linear time. The complexity is related only to number of bytes in target array. So checking byte sequences for malware signatures takes linear time in average.

Also thread pool is used to split scanning. Each thread takes a batch of files to proceed and returns result to main thread using Qt signal/slots.

Structure
*********

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
