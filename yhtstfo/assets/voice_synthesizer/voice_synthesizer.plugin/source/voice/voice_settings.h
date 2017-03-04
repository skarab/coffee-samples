#ifndef _VOICE_SETTINGS_H_
#define _VOICE_SETTINGS_H_

#include "plugin_includes.h"
#include "voice_gender.h"
#include "voice_language.h"
#include "voice_effect.h"

namespace voice_synthesizer
{
    //--------------------------------------------------------------------------------------------//
    /// Voice settings
    //--------------------------------------------------------------------------------------------//
    class VOICE_SYNTHESIZER_API VoiceSettings : public meta::Object
    {
        COFFEE_Type(VoiceSettings);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        VoiceSettings() :
            ItIs3D(false),
            Pitch(1.0f),
            Gain(1.0f),
            Gender(VOICE_GENDER_Male),
            Language(VOICE_LANGUAGE_English),
            Age(0),
            Variant(0),
            Effect(VOICE_EFFECT_None)
        {
            static uint32 _ID = 0;
            ID = _ID++;
        }

        ~VoiceSettings() {}

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 ID;
        bool ItIs3D;
        real Pitch;
        real Gain;
        VOICE_GENDER Gender;
        VOICE_LANGUAGE Language;
        uint32 Age;
        uint32 Variant;
        VOICE_EFFECT Effect;
    };

    COFFEE_RegisterType(VOICE_SYNTHESIZER_EXPORT_STATICS, VoiceSettings);
}
#endif
