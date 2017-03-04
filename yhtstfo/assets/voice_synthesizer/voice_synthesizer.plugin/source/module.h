#ifndef _VOICE_SYNTHESIZER_MODULE_H_
#define _VOICE_SYNTHESIZER_MODULE_H_

#include "plugin_includes.h"
#include "voice/voice_synthesizer.h"

namespace voice_synthesizer
{
    //--------------------------------------------------------------------------------------------//
    /// Module
    //--------------------------------------------------------------------------------------------//
    class VOICE_SYNTHESIZER_API Module : public shell::Module
    {
        COFFEE_Type(Module);
        COFFEE_DeclareModuleSingleton(Module);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Module();
        ~Module();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnUpdate(const basic::Time& time_step);
    };

    COFFEE_RegisterType(VOICE_SYNTHESIZER_EXPORT_STATICS, Module);
}
#endif
