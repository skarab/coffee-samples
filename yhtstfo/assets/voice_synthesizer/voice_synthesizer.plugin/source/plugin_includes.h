#ifndef _VOICE_SYNTHESIZER_INCLUDES_H_
#define _VOICE_SYNTHESIZER_INCLUDES_H_

    #include "coffee.h"
    using namespace coffee;

    #include "speak_lib.h"
        
    //-IMPORT-EXPORT----------------------------------------------------------------------------------//
    #ifndef USE_VOICE_SYNTHESIZER
        #define VOICE_SYNTHESIZER_API __declspec(dllexport)
        #define VOICE_SYNTHESIZER_TEMPLATE_API __declspec(dllexport)
    #else
        #define VOICE_SYNTHESIZER_API __declspec(dllimport)
        #define VOICE_SYNTHESIZER_TEMPLATE_API
    #endif

    #ifdef USE_VOICE_SYNTHESIZER
        #define VOICE_SYNTHESIZER_EXPORT_STATICS false
    #else
        #define VOICE_SYNTHESIZER_EXPORT_STATICS true
    #endif
    //------------------------------------------------------------------------------------------------//

#endif
