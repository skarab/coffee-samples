#include "module.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(voice_synthesizer::Module);
    COFFEE_Ancestor(shell::Module);
COFFEE_EndType();

namespace voice_synthesizer
{
    COFFEE_ImplementModuleSingleton(Module);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Module::Module() :
        shell::Module(shell::MODULE_ATTRIBUTE_Automatic)
    {
        COFFEE_CreateModuleSingleton(Module);
    }

    //--------------------------------------------------------------------------------------------//

    Module::~Module()
    {
        COFFEE_DestroyModuleSingleton(Module);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Module::OnInitialize()
    {
        Register<Synthesizer>();
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnFinalize()
    {
        Unregister<Synthesizer>();
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnUpdate(const basic::Time& time_step)
    {
        if (Synthesizer::Get().IsAvailable())
            Synthesizer::Get().OnMainThreadUpdate(time_step);
    }

}
