#!/bin/bash

# builds and runs the "VorbTest" sample.

javac ./VorbTest.java
java VorbTest -Djava.library.path=.
