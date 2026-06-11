module;

#include <sdkddkver.h>
#include <windows.h>

export module winrtplus.Microsoft.UI.Designer.Interop;
#if __has_include("winrt/Microsoft.UI.Designer.Interop.h")

extern "C++"
{
// Workaround
#undef INTERFACE
#include "winrt/Microsoft.UI.Designer.Interop.h"

    namespace winrt::Microsoft::UI::Designer
    {
    export using Designer::IDesignerOutputHostInterop;
    }
}
#endif
