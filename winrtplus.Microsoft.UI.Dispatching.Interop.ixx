module;

#include <wtypes.h>

export module winrtplus.Microsoft.UI.Dispatching.Interop;

#if __has_include("winrt/Microsoft.UI.Dispatching.Interop.h")
export extern "C" BOOL __stdcall ContentPreTranslateMessage(const MSG *pmsg);
#endif
