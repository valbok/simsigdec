Simsigdec
=========================
Simple signature detector - an application to find a malware in target files, using predefined byte sequences that stored in text file in format:

    HexString.{id}

or

    69662840245f504f5354.{1}

The main point of this solution - an example of how to search signatures in linear time. The complexity is related only to number of bytes in target array. So checking byte sequences for malware signatures takes linear time in average.

Also created a separate server that handles requests from gui users like cheching files and sends result back as JSON string.

Structure
*********

The application is splitted out by few layers.

* Core - is a scanner through sequences. And some utilities.
* Server - gets connection from gui users. Each connection is a list of file that need to proccess. The server splits the files to batches and creats few tasks that will be executed in separate threads using thread pool. Result will be sent as a JSON to client.
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
