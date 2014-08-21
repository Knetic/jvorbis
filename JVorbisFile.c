#include "JVorbisFile.h"
#include "ivorbiscodec.h"
#include "ivorbisfile.h"
#include <stdlib.h>


// Used as a convenience structure to hold all of our native vorbis information
typedef struct
{
    OggVorbis_File* vorbisFile;
    vorbis_info* vorbisInfo;
    FILE* fileHandler;
    
} OggVorbisWrapper;


JNIEXPORT void JNICALL Java_JVorbisFile_jvorbOpen(JNIEnv* environment, jobject caller, jstring path)
{
    jfieldID filePointerID;
    jfieldID bitRateID;
    jfieldID sampleRateID;
    jfieldID durationID;
    jfieldID channelsID;
    jfieldID versionID;
    jfieldID versionInfo;
    jclass callerClass;
    jdouble duration;
    OggVorbisWrapper* vorbisWrapper;
    OggVorbis_File* vorbisFile;
    vorbis_info* vorbisInfo;
    FILE* file;
    
    //
    callerClass       = (*environment)->GetObjectClass(environment, caller);
    filePointerID     = (*environment)->GetFieldID(environment, callerClass, "filePointer", "J");
    bitRateID         = (*environment)->GetFieldID(environment, callerClass, "bitRate", "I");
    sampleRateID      = (*environment)->GetFieldID(environment, callerClass, "sampleRate", "I");
    versionID         = (*environment)->GetFieldID(environment, callerClass, "version", "I");
    durationID	      = (*environment)->GetFieldID(environment, callerClass, "duration", "J");
    channelsID	      = (*environment)->GetFieldID(environment, callerClass, "channels", "I");
    
    // actually do the vorbing
    vorbisWrapper = (OggVorbisWrapper*)malloc(sizeof(OggVorbisWrapper));
    vorbisFile = (OggVorbis_File*)malloc(sizeof(OggVorbis_File));
    
    file = fopen((*environment)->GetStringUTFChars(environment, path, 0), "rb");
    if(ov_open(file, vorbisFile, NULL, 0) == 0)
    {
	// get information
	vorbisInfo = ov_info(vorbisFile, -1);
	duration = (long)ov_time_total(vorbisFile, -1);
	
	(*environment)->SetIntField(environment, caller, bitRateID, vorbisInfo->bitrate_nominal);
	(*environment)->SetIntField(environment, caller, sampleRateID, vorbisInfo->rate);
	(*environment)->SetIntField(environment, caller, versionID, vorbisInfo->version);
	(*environment)->SetIntField(environment, caller, channelsID, vorbisInfo->channels);
	(*environment)->SetLongField(environment, caller, durationID, duration);
    }
    
    // set into structure and save to object    
    vorbisWrapper->vorbisFile = vorbisFile;
    vorbisWrapper->vorbisInfo = vorbisInfo;
    vorbisWrapper->fileHandler = file;
  
    (*environment)->SetLongField(environment, caller, filePointerID, (jlong)vorbisWrapper);
}

JNIEXPORT jint JNICALL Java_JVorbisFile_jvorbRead(JNIEnv* environment, jobject caller, jobject sampleBuffer)
{
    jfieldID filePointerID;
    jfieldID bufferPointerID;
    jmethodID capacityMethodID;
    jclass callerClass;
    jint samplesToRead;
    OggVorbisWrapper* vorbisWrapper;
    char* samples;
    int samplesRead;
    int ret;
    
    // caller
    callerClass       = (*environment)->GetObjectClass(environment, caller);
    filePointerID     = (*environment)->GetFieldID(environment, callerClass, "filePointer", "J");
    
    // buffer
    samples           = (char*)((*environment)->GetDirectBufferAddress(environment, sampleBuffer));
    samplesToRead     = (*environment)->GetDirectBufferCapacity(environment, sampleBuffer);
    vorbisWrapper     = (OggVorbisWrapper*)((*environment)->GetLongField(environment, caller, filePointerID));
    
    //
    samplesRead = 0;
    
    while(samplesRead < samplesToRead)
    {
	// should do error handling here somewhere
	ret = ov_read( vorbisWrapper->vorbisFile, (samples + samplesRead), (samplesToRead - samplesRead), 0);
	
	if(ret == 0)
	  return samplesRead;
	
	samplesRead += ret;
    }

    return samplesRead;
}

JNIEXPORT void JNICALL Java_JVorbisFile_jvorbClose(JNIEnv* environment, jobject caller)
{
    jfieldID filePointerID;
    jclass callerClass;
    OggVorbisWrapper* vorbisWrapper;
    
    callerClass       = (*environment)->GetObjectClass(environment, caller);
    filePointerID     = (*environment)->GetFieldID(environment, callerClass, "filePointer", "J");
    
    vorbisWrapper = (OggVorbisWrapper*)((*environment)->GetLongField(environment, caller, filePointerID));
    
    // cleanup
    ov_clear(vorbisWrapper->vorbisFile);
    free(vorbisWrapper->vorbisFile);
    free(vorbisWrapper);
}