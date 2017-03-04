#include "voice_effect.h"
#undef _VOICE_EFFECT_H_
#include "kernel/meta/macros/meta_macros_enum_cpp.h"
#include "voice_effect.h"
#include "kernel/meta/macros/meta_macros_enum_h.h"

namespace voice_synthesizer
{

    const char* VOICE_EFFECT_GetString(VOICE_EFFECT effect, bool it_is_female)
    {
        static const char* male_strings[] = {
            "whisper",
            "croak",
            "klatt3"
            };

        static const char* female_strings[] = {
            "whisperf",
            "croak",
            "klatt3"
            };

        if (effect==VOICE_EFFECT_None)
            return "";

        if (it_is_female)
            return female_strings[(uint32)effect];
        return male_strings[(uint32)effect];
    }

}
