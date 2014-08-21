import java.nio.*;
import javax.sound.sampled.*;

// One note about this class
// It may be required to use ShortBuffer
// It seems everyone else does
// I suspect this is due to stereo
// The future will tell
class JVorbisFile
{
    // instance variables
    public ByteBuffer sampleBuffer;
    public long filePointer;	     	// pointer to the OggVorbis_File

    // file information
    public AudioFormat format;		// convenience wrapper for java

    public int sampleRate;		// in hz
    public int bitRate;			// in hz
    public int channels;		// mono or stereo (OR 5.1?!)
    public long duration;		// in milliseconds
    public int version;			// probably won't be used, but hey why not.

    //
    public native void jvorbOpen(String path);
    public native int  jvorbRead(ByteBuffer samplesBuffer);
    public native void jvorbClose();
    
    //
    public JVorbisFile(String file)
    {
	this(file, 2048); //2k buffer default
    }
    
    public JVorbisFile(String file, int bufferSize)
    {
	sampleBuffer = ByteBuffer.allocateDirect(bufferSize).order(ByteOrder.nativeOrder());
	jvorbOpen(file);

	// raw instance variables set, time to construct an audioformat.
	format = new AudioFormat((float)sampleRate, bitRate, channels, true, false);
    }

    public int read()
    {
	int ret;

	ret = jvorbRead(sampleBuffer);
	sampleBuffer.position(0);

	return ret;
    }

    public void close()
    {
	jvorbClose();
    }

    static
    {
	System.loadLibrary("jvorb");
    }
}