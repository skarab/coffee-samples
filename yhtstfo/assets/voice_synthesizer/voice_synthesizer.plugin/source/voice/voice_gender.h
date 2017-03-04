#ifndef _VOICE_GENDER_H_
#define _VOICE_GENDER_H_

#include "plugin_includes.h"
#include "kernel/meta/meta_enum.h"

namespace voice_synthesizer
{
    //--------------------------------------------------------------------------------------------//
    /// Voice settings: Gender
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(voice_synthesizer, VOICE_GENDER, "Gender", Single)
        COFFEE_EnumValue(VOICE_GENDER, Male, 0)
        COFFEE_EnumValue(VOICE_GENDER, Female, 1)
    COFFEE_EndEnum(VOICE_SYNTHESIZER_API, VOICE_SYNTHESIZER_EXPORT_STATICS, VOICE_GENDER)
}
#endif
