import javax.sound.sampled.*;

public class VorbTest
{
    private static Mixer mixer;
    private static SourceDataLine line;
    private static JVorbisFile vorb;

    public static void main(String[] args)
    {
	vorb = new JVorbisFile("test.ogg");

	// play what we got
	selectLine();
//	play();

	vorb.close();
    }
    
    public static void selectLine()
    {
	Line.Info[] sources;
	Mixer.Info[] mixs;
	DataLine.Info info;
	Mixer mix;

	try
	{
	    mixs = AudioSystem.getMixerInfo();

	    for(int i = 0; i < mixs.length; i++)
	    {
		System.out.println("\n\nMixer "+i);
		System.out.println(mixs[i].getName());
		System.out.println(mixs[i].getVendor());
		System.out.println(mixs[i].getVersion());
		System.out.println(mixs[i].getDescription());
  
		mix = AudioSystem.getMixer(mixs[i]);
		sources = mix.getSourceLineInfo();

		for(int z = 0; z < sources.length; z++)
		{
		    System.out.println(sources[z].toString());
		}
	    }
	    //line = (SourceDataLine)AudioSystem.getSourceDataLine(vorb.format);
	    //

	  info = new DataLine.Info(SourceDataLine.class, vorb.format);

	  if(AudioSystem.isLineSupported(info))
	  {
	      System.out.println("Found a line");
	      line = (SourceDataLine)AudioSystem.getLine(info);
	      line.open(vorb.format, vorb.sampleBuffer.capacity());
	      line.start();
	  }
	  else
	    System.out.println("No line found");	    

	}
        catch (Exception ex) 
        {
            ex.printStackTrace();
            return;
        }
    }

    public static void play()
    {
	byte[] backingBuffer;
	int ret;

	while(true)
	{
	    ret = vorb.read();

	    if(ret == 0)
	      break;

	    
	    backingBuffer = vorb.sampleBuffer.array();
	    line.write(backingBuffer, 0, ret);
	}
    }
}