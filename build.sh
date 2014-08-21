#!/bin/bash

# Note that this script requires JAVA_HOME to be set.

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

rm -f libjvorb.so
rm -f *.java~
rm -f *.c~
rm -f *.h~
rm -f *.sh~
rm -f *.log

echo "===="
echo "Java stage"
echo "===="
echo ""
echo ""

javac ./JVorbisFile.java
javah -jni JVorbisFile 

echo "===="
echo "Native stage"
echo "===="
echo ""
echo ""

pushd vorbis >> /dev/null
gcc -shared *.c -o ../libjvorb.so -I$JAVA_HOME/include -I$JAVA_HOME/include/linux -w -fPIC
popd >> /dev/null

echo ""
echo ""
echo "done."
echo ""
