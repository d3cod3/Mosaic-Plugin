#include "Kernel.h"

#include "AudioObject.h"
#include "NumberObject.h"
#include "StringObject.h"
#include "VideoObject.h"

#ifdef _WIN32
#  define EXPORTIT __declspec( dllexport )
#else
#  define EXPORTIT
#endif

extern "C" EXPORTIT void register_pugg_plugin(pugg::Kernel* kernel)
{
    kernel->add_driver(new AudioObjectDriver());
    kernel->add_driver(new NumberObjectDriver());
    kernel->add_driver(new StringObjectDriver());
    kernel->add_driver(new VideoObjectDriver());
}
