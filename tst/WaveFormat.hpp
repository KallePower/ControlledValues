/*///////////////////////////////////////////////////////////*\
||                                                           ||
||     File:      WaveFormat.hpp                             ||
||     Author:    Kalle                                      ||
||     Generated: 24.09.2016                                 ||
||                                                           ||
\*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
#ifndef _WaveFormat_hpp_
#define _WaveFormat_hpp_

#include "Test.h"

#ifndef EMPTY
#define EMPTY (unsigned)(-1) //(4294967295u)
#endif

namespace stepflow{
    namespace Tests{

#define asWAVEFORMATEX(audiofmt) (*(WAVEFORMATEX*)&audiofmt)
#define asPCMWAVEFORMAT(audiofmt) (*(PCMWAVEFORMAT*)&audiofmt)

        enum CONSTS : i32
        {
            ChunkID = 1179011410,       // Contains the letters "RIFF" in ASCII form //0x52494646,
            ChunkSize = 36,             // size of the entire file in bytes minus 8
            FileFormat = 1163280727,    // Contains the letters "WAVE" (0x57415645 big-endian form).
            Subchunk1ID = 544501094,    // Contains the letters "fmt " (0x666d7420 big-endian form).
            Subchunk1Size = 16,         // 16 for PCM. This is the size of the rest of the Subchunk which follows this number.
            Subchunk2ID = 1635017060,   // Contains the letters "data" (0x64617461 big-endian form).
            HeaderSize = 44,            // Header-size.
            PCMs16 = 1,                 // Values other than 1 indicate some form of compression.
            PCMf32 = 3                  // (or even uncompressed float PCM, which would be 3)
        };

        typedef struct AudioFormat
        {
            i16 Tag;           //2
            i16 NumChannels;   //4
            i32 SampleRate;    //8
            i32 ByteRate;      //12
            i16 BlockAlign;    //14
            i16 BitsPerSample; //16
        };

        typedef struct WaveHeader
        {
            const i32   ChunkID;        //1-4
            i32         ChunkSize;      //5-8
            const i32   FileFormat;     //9-12
            const i32   Subchunk1ID;    //13-16
            i32         Subchunk1Size;  //17-20
            AudioFormat AudioFormat;    //21-36
            i32         Subchunk2ID;    //37-40
            i32         DataSize;       //41-44
            WaveHeader& operator = (WaveHeader that)
                        { return *(WaveHeader*)memcpy(this, &that, 44); }
        } WaveHeader;

        WaveHeader  getInitializedWaveheader(void);
        s32         SetWaveDataSize(WaveHeader*, s32);
        WaveHeader* CreateWaveHeader( i32 samplingFrequency, i16 bitsPerSample,
                                      i16 numberOfChannels, i32 sizeOfWaveData = 0,
                                      WaveHeader* = &getInitializedWaveheader() ); //(WaveHeader*)&WaveHeaderInit);



        struct Audio
        {
            PCMWAVEFORMAT format;
            i32   cbSize;
            void* data;
            i32 frameCount;
            bool own;

            Audio(void);
            Audio(WaveHeader hdr, void* = NULL);
            Audio(PCMWAVEFORMAT fmt, i32 size);
            Audio(i32 sRate, i32 bitDepth, i32 channels, i32 dataSize);
            void  createBuffer(i32 size);
            void* detachBuffer(void);
            Audio& outscope(void);
            Audio(Audio& copy);
            ~Audio(void);
            Audio& operator=(Audio&);
            template<typename sampleType>
            sampleType* buffer(void)
            { return (sampleType*)data; }
        };
    }//end of Tests
}



#endif
