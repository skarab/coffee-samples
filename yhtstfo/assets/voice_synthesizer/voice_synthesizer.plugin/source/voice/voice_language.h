#ifndef _VOICE_LANGUAGE_H_
#define _VOICE_LANGUAGE_H_

#include "plugin_includes.h"
#include "kernel/meta/meta_enum.h"

namespace voice_synthesizer
{
    //--------------------------------------------------------------------------------------------//
    /// Voice settings: Language
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(voice_synthesizer, VOICE_LANGUAGE, "Language", Single)
        COFFEE_EnumValue(VOICE_LANGUAGE, Afrikaans, 0)              // af
        COFFEE_EnumValue(VOICE_LANGUAGE, Albanian, 1)               // sq
        COFFEE_EnumValue(VOICE_LANGUAGE, American, 2)               // en-us
        COFFEE_EnumValue(VOICE_LANGUAGE, AncientGreek, 3)           // grc
        COFFEE_EnumValue(VOICE_LANGUAGE, Armenian, 4)               // hy
        COFFEE_EnumValue(VOICE_LANGUAGE, Bosnian, 5)                // bs
        COFFEE_EnumValue(VOICE_LANGUAGE, BritishNorthern, 6)        // en-n
        COFFEE_EnumValue(VOICE_LANGUAGE, BritishRecPro, 7)          // en-rp
        COFFEE_EnumValue(VOICE_LANGUAGE, BritishWestMidlands, 8)    // en-wm
        COFFEE_EnumValue(VOICE_LANGUAGE, Catalan, 9)                // ca
        COFFEE_EnumValue(VOICE_LANGUAGE, ChineseCantonese, 10)      // zh-yue
        COFFEE_EnumValue(VOICE_LANGUAGE, ChineseMandarin, 11)       // zh
        COFFEE_EnumValue(VOICE_LANGUAGE, Croatian, 12)              // hr
        COFFEE_EnumValue(VOICE_LANGUAGE, Czech, 13)                 // cs
        COFFEE_EnumValue(VOICE_LANGUAGE, Danish, 14)                // da
        COFFEE_EnumValue(VOICE_LANGUAGE, Dutch, 15)                 // nl
        COFFEE_EnumValue(VOICE_LANGUAGE, English, 16)               // en
        COFFEE_EnumValue(VOICE_LANGUAGE, Esperanto, 17)             // eo
        COFFEE_EnumValue(VOICE_LANGUAGE, Finnish, 18)               // fi
        COFFEE_EnumValue(VOICE_LANGUAGE, French, 19)                // fr
        COFFEE_EnumValue(VOICE_LANGUAGE, German, 20)                // de
        COFFEE_EnumValue(VOICE_LANGUAGE, Georgian, 21)              // ka
        COFFEE_EnumValue(VOICE_LANGUAGE, Greek, 22)                 // el
        COFFEE_EnumValue(VOICE_LANGUAGE, Hindi, 23)                 // hi
        COFFEE_EnumValue(VOICE_LANGUAGE, Hungarian, 24)             // hu
        COFFEE_EnumValue(VOICE_LANGUAGE, Icelandic, 25)             // is
        COFFEE_EnumValue(VOICE_LANGUAGE, Indonesian, 26)            // id
        COFFEE_EnumValue(VOICE_LANGUAGE, Italian, 27)               // it
        COFFEE_EnumValue(VOICE_LANGUAGE, Kannada, 28)               // kn
        COFFEE_EnumValue(VOICE_LANGUAGE, Kurdish, 29)               // ku
        COFFEE_EnumValue(VOICE_LANGUAGE, Latin, 30)                 // la
        COFFEE_EnumValue(VOICE_LANGUAGE, Latvian, 31)               // lv
        COFFEE_EnumValue(VOICE_LANGUAGE, Lojban, 32)                // jbo
        COFFEE_EnumValue(VOICE_LANGUAGE, Macedonian, 33)            // mk
        COFFEE_EnumValue(VOICE_LANGUAGE, Norwegian, 34)             // no
        COFFEE_EnumValue(VOICE_LANGUAGE, Polish, 35)                // pl
        COFFEE_EnumValue(VOICE_LANGUAGE, PortugueseBrazil, 36)      // pt
        COFFEE_EnumValue(VOICE_LANGUAGE, PortugueseEuropean, 37)    // pt-pt
        COFFEE_EnumValue(VOICE_LANGUAGE, Romanian, 38)              // ro
        COFFEE_EnumValue(VOICE_LANGUAGE, Russian, 39)               // ru
        COFFEE_EnumValue(VOICE_LANGUAGE, Scottish, 40)               // en-sc
        COFFEE_EnumValue(VOICE_LANGUAGE, Serbian, 41)               // sr
        COFFEE_EnumValue(VOICE_LANGUAGE, Slovak, 42)                // sk
        COFFEE_EnumValue(VOICE_LANGUAGE, Spanish, 43)               // es
        COFFEE_EnumValue(VOICE_LANGUAGE, SpanishAmerican, 44)       // es-la
        COFFEE_EnumValue(VOICE_LANGUAGE, Swahihi, 45)               // sw
        COFFEE_EnumValue(VOICE_LANGUAGE, Swedish, 46)               // sv
        COFFEE_EnumValue(VOICE_LANGUAGE, Tamil, 47)                 // ta
        COFFEE_EnumValue(VOICE_LANGUAGE, Turkish, 48)               // tr
        COFFEE_EnumValue(VOICE_LANGUAGE, Vietnamese, 49)            // vi
        COFFEE_EnumValue(VOICE_LANGUAGE, Welsh, 50)                 // cy
    COFFEE_EndEnum(VOICE_SYNTHESIZER_API, VOICE_SYNTHESIZER_EXPORT_STATICS, VOICE_LANGUAGE)

    VOICE_SYNTHESIZER_API const char* VOICE_LANGUAGE_GetString(VOICE_LANGUAGE language);
}
#endif
