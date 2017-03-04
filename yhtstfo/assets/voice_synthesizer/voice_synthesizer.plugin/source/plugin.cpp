#include "plugin.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(voice_synthesizer::Library);
    COFFEE_Ancestor(plugins::Library);
COFFEE_EndType();

namespace voice_synthesizer
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Library::Library()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Library::~Library()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Library::Initialize()
    {
        audio::Module::Get().Register<Synthesizer>();
    }
    
    //--------------------------------------------------------------------------------------------//

    void Library::Finalize()
    {
        audio::Module::Get().Unregister<Synthesizer>();
    }
    
    //--------------------------------------------------------------------------------------------//

    void Library::Update(const basic::Time& time_step)
    {
    }
        
}
