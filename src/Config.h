#pragma once

#ifdef WIN32

    #ifdef RBPCOM_STATIC
        #define RBP_DLL 
    #elif defined(RBPCOM_EXPORTS)
	#define RBP_DLL __declspec(dllexport)
    #else
	#define RBP_DLL __declspec(dllimport)
    #endif

#else
    #define RBP_DLL 
#endif

