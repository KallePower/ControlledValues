/*///////////////////////////////////////////////////////////*\
||                                                           ||
||     File:      FloatAudioCompressor.hpp                   ||
||     Author:    Kalle                                      ||
||     Generated: 05.10.2016                                 ||
||                                                           ||
\*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
#ifndef _FloatAudioCompressor_hpp_
#define _FloatAudioCompressor_hpp_
#include <../inc/ControlledValues.h>

namespace stepflow{
namespace Tests{
    class FloatAudioCompressor
    : public UserModeControl<float>
    {
    protected:
        float TIMER;
        virtual void Init(void)
        {
            TIMER = 100;
            controller->MAX = 1.-controller->MOVE;
            controller->SetCheckAtGet(false);
            controller->ControllerActive = true;
        }
    public:
        void SetAttackRelease(float samplesCount)
        {
            TIMER = samplesCount;
        }
        virtual float checkVALUE(float* pVALUE)
        {
            return *pVALUE = (*pVALUE > controller->MIN) || (*pVALUE < -controller->MIN)

                   ?  *pVALUE * (controller->MOVE + ((controller->MAX>0)
                    ? (controller->MAX -= (1.f - controller->MOVE) / TIMER)
                    : (controller->MAX = 0)))

                   :  *pVALUE * (controller->MOVE + ((controller->MAX < 1.f - controller->MOVE)
                    ? (controller->MAX += ((1.f - controller->MOVE) / TIMER))
                    : (controller->MAX = (1.f - controller->MOVE))));
        }
    };// end of FloatAudioCompressor
}}//end of stepflow::Tests
#endif
