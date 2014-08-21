#!/bin/bash

LD_LIBRARY_PATH=.
export LD_LIBRARY_PATH

echo "---------------------------------"
echo ""
echo ""
echo ""
echo "===="
echo "Cleaning stage"
echo "===="
echo ""
echo ""

rm libjvorb.so
rm *.java~
rm *.c~
rm *.h~
rm *.sh~
rm *.log

echo "===="
echo "Java stage"
echo "===="
echo ""
echo ""

javac ./JVorbisFile.java
javac ./VorbTest.java
javah -jni JVorbisFile 

echo "===="
echo "Native stage"
echo "===="
echo ""
echo ""

gcc -shared *.c -o libjvorb.so -I /usr/lib/jvm/java-6-openjdk/include/ -w

echo ""
echo ""
echo "done."
echo ""

java VorbTest -Djava.library.path=.