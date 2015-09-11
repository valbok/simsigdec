Simsigdec
=========================
Simple signature detector - an application to find malware in target files.
Using predefined byte sequences that stored in text file in format:
    
    HexString.{id} 

The application is splitted out to few layers.

* Core - is a scanner through sequences. And some utilities.
* Objects - handlers to separate jobs between threads, get result from them using Qt signals/slots.
* Gui - visualizations of tasks.

Requirements
************

It requires Qt5 and cmake.

Build
*******

    $ cmake . ; make

Tests
*****
    
    $ cd core/tests; ScannerTest; configTest
