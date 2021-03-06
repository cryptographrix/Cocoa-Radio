//
//  CSDRAudioDevice.h
//  Cocoa Radio
//
//  Created by William Dillon on 8/30/12.
//  Copyright (c) 2012. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreAudio/AudioHardware.h>
#import <AudioUnit/AudioUnit.h>

@class CSDRRingBuffer;

@interface CSDRAudioDevice : NSObject
{
    bool _running;
    bool _prepared;
    
    AudioUnit unit;

    AudioComponent comp;
    AudioComponentDescription desc;
    AudioComponentInstance auHAL;
    
    CSDRRingBuffer *ringBuffer;

}

+ (NSArray *)deviceDict;

- (id)initWithRate:(float)sampleRate;

- (CSDRRingBuffer *)ringBuffer;

- (bool)prepare;
- (void)unprepare;

- (bool)start;
- (void)stop;

@property (readwrite) int sampleRate;
@property (readwrite) int blockSize;
@property (readonly) bool running;
@property (readwrite) int deviceID;
@property (readwrite) bool mute;

@end

@interface CSDRAudioOutput : CSDRAudioDevice
{
    bool discontinuity;
}

- (void)bufferData:(NSData *)data;

// This is used to mark a discontinuity, such as frequency change
// It's purpose is to discard packets in the buffer before the
// frequency change, then, when the buffer re-fills to 1/2 full,
// playing will resume.
- (void)markDiscontinuity;
- (bool)discontinuity;


@end