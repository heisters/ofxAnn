ofxAnn
======

Simple approximate nearest neighbor (KNN) search for OpenFrameworks.

After writing a couple (shitty) KNN implmentations from scratch, I figured I'd
leverage some smarter people's work for an easier and faster implementation.
The goal of this library is to provide a simple, easy-to-use interface, by
favoring convention over configuration. Therefore, it currently uses the most
basic algorithms provided by nanoflann, but could easily be extended to allow
more advanced functionality (hopefully without sacrificing ease of use).

Getting Started
---------------

Copy examples/ofxAnnBasicExample to your OF apps directory and build and run
it. Read the source.
