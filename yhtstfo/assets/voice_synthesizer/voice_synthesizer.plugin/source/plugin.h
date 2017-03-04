#ifndef _VOICE_SYNTHESIZER_H_
#define _VOICE_SYNTHESIZER_H_

#include "plugin_includes.h"
#include "voice/voice_synthesizer.h"

namespace voice_synthesizer
{
    //--------------------------------------------------------------------------------------------//
    /// voice_synthesizer::Library
    //--------------------------------------------------------------------------------------------//
    class VOICE_SYNTHESIZER_API Library : public plugins::Library
    {
        COFFEE_Type(Library);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Library();
        ~Library();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize();
        void Finalize();
        void Update(const basic::Time& time_step);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//


    };

    COFFEE_RegisterType(VOICE_SYNTHESIZER_EXPORT_STATICS, Library);
}

COFFEE_RegisterPlugin(voice_synthesizer::Library);

#endif
