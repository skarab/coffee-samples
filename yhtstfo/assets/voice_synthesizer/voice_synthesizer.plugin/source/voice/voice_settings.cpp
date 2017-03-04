#include "voice_settings.h"

//-META---------------------------------------------------------------------------------------//

COFFEE_BeginType(voice_synthesizer::VoiceSettings);
    COFFEE_Attribute(bool, ItIs3D, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(real, Pitch, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(real, Gain, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(voice_synthesizer::VOICE_GENDER, Gender, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(voice_synthesizer::VOICE_LANGUAGE, Language, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(uint32, Age, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(uint32, Variant, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(voice_synthesizer::VOICE_EFFECT, Effect, meta::MODE_Serializeable | meta::MODE_Editable);
COFFEE_EndType();

