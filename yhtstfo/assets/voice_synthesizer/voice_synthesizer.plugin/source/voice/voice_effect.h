#ifndef _VOICE_EFFECT_H_
#define _VOICE_EFFECT_H_

#include "plugin_includes.h"
#include "kernel/meta/meta_enum.h"

namespace voice_synthesizer
{
    //--------------------------------------------------------------------------------------------//
    /// Voice settings: Effect
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(voice_synthesizer, VOICE_EFFECT, "Effect", SingleNone)
        COFFEE_EnumValue(VOICE_EFFECT, Whisper, 0)
        COFFEE_EnumValue(VOICE_EFFECT, Croak, 1)
        COFFEE_EnumValue(VOICE_EFFECT, Klatt, 2)
    COFFEE_EndEnum(VOICE_SYNTHESIZER_API, VOICE_SYNTHESIZER_EXPORT_STATICS, VOICE_EFFECT)

    VOICE_SYNTHESIZER_API const char* VOICE_EFFECT_GetString(VOICE_EFFECT effect, bool it_is_female);
}
#endif
