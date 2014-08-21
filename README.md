JVorbis
==

This library enables use of the Tremor branch of Ogg Vorbis in Java applications.

Ogg Vorbis (if you didn't already know) is an audio compression format which is license-free and open-source.
Unfortunately, Vorbis doesn't have any officially-supported wrappers for Java. This library aims to provide support for that.

This library ties itself specifically to the Tremor branch of Ogg Vorbis, which is a faster (fixed-point) implementation of the specification. This makes this library well-suited for embedded applications.

More about Ogg Vorbis:
http://xiph.org/vorbis/

Ogg Vorbis spec:
https://xiph.org/vorbis/doc/

Tremor Branch:
https://wiki.xiph.org/Tremor

Building
==

Just run "build.sh". It will output a libvorbis.so file, as well as a JVorbisFile.class. These two files should be all that's necessary to get support for Vorbis into your system.

Run the sample
==

Included is a "VorbTest.java", which is a sample that shows the basic usage of the library. You can run it from the "sampleTest.sh" file.

Contributing
==

I am not actively maintaining this repository. I built it long ago (2012) in order to add support for some Android games I released. I don't intend to make major changes to it. It is open-source primarily so that so that I can show proof that I implemented such a thing. Plus, it's useful to link this to other people as a quick introduction to both JNI and Ogg Vorbis.

If you want to contribute, contact me. If you want to use this library, go right ahead. 

Disclaimer
==

I don't have any affiliation with Xiph.org, nor the Ogg Vorbis team or spec. I am (as far as I know) totally unrelated to the project. The code in the "vorbis" folder is free and open-source, but I didn't write it. It's taken from the Tremor branch of Ogg Vorbis.
