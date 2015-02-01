/**
 * boomblaster
 *
 * Copyright (C) 2012-2015 Woima Solutions Oy
 *
 * @author antti.peuhkurinen@woimasolutions.com
 */

#ifndef BB_TRACKERSAMPLE
#define BB_TRACKERSAMPLE

#include "AudioResource.hpp"
#include "helpers/ReferencedPointer.hpp"
#include "helpers/Mutex.hpp"
#include <sigc++/connection.h>
#include <stdint.h>

namespace bb
{
    class TrackerSample: public Referenced
    {
    public:
        static unsigned int const BytesPerSample = 2;

        sigc::signal<void, unsigned int /* Referenced::id */> ended;
        sigc::connection audioAssetInterestedFromEnd;

        TrackerSample(const ReferencedPointer<AudioResource>& resource, float volume, bool looping);
        ~TrackerSample();
        float volume();
        void setVolume(float volume);
        int16_t sampleForTracker(bool& end);
        void audioAssetSetNotInterested();
        void fadeOut(unsigned int fadeTimeMilliseconds);

    private:
        // Mutex is to used to control the "ended" signal connection to parent AudioAssetPrivate
        Mutex mutex_;
        float volume_;
        ReferencedPointer<AudioResource> resource_;
        unsigned int byteSize_;
        unsigned int byteLocation_;
        bool looping_;

        struct FadeOut
        {
            bool on_;
            unsigned int start_;
            float ramp_; // applied every sample() call to volume_ during fadeout
        } fadeOut_;
    };
}

#endif