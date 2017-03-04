#ifndef _VOICE_H_
#define _VOICE_H_

#include "plugin_includes.h"
#include "voice_settings.h"

namespace voice_synthesizer
{
    //--------------------------------------------------------------------------------------------//
    /// Voice to synthetize
    //--------------------------------------------------------------------------------------------//
    class Voice
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Voice() {}
        ~Voice() {}

        //-OPERATORS------------------------------------------------------------------------------//

        bool operator ==(const Voice& other) const { return false; }
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String Speach;
        VoiceSettings Settings;
        basic::Vector<uint8> Buffer;
        basic::Vector3 Position;
    };

}
#endif
