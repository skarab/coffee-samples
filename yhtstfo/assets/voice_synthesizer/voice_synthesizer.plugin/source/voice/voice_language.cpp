#include "voice_language.h"
#undef _VOICE_LANGUAGE_H_
#include "kernel/meta/macros/meta_macros_enum_cpp.h"
#include "voice_language.h"
#include "kernel/meta/macros/meta_macros_enum_h.h"

namespace voice_synthesizer
{
    const char* VOICE_LANGUAGE_GetString(VOICE_LANGUAGE language)
    {
        static const char* strings[] = {
            "af",
            "sq",
            "en-us",
            "grc",
            "hy",
            "bs",
            "en-n",
            "en-rp",
            "en-wm",
            "ca",
            "zh-yue",
            "zh",
            "hr",
            "cs",
            "da",
            "nl",
            "en",
            "eo",
            "fi",
            "fr",
            "de",
            "ka",
            "el",
            "hi",
            "hu",
            "is",
            "id",
            "it",
            "kn",
            "ku",
            "la",
            "lv",
            "jbo",
            "mk",
            "no",
            "pl",
            "pt",
            "pt-pt",
            "ro",
            "ru",
            "en-sc",
            "sr",
            "sk",
            "es",
            "es-la",
            "sw",
            "sv",
            "ta",
            "tr",
            "vi",
            "cy"
            };

        return strings[(uint32)language];
    }

}

