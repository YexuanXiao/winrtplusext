module;

#include <sdkddkver.h>
#include <windows.h>
#include <unknwn.h>
#include <sal.h>

export module winrtplus.Microsoft.UI.Composition.Interop;

#if __has_include("winrt/Microsoft.UI.Composition.Interop.h")
import winrt.Microsoft.UI.Composition;

#define WINRT_IMPORT_MODULE

extern "C++"
{
// Workaround
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 5244)
#endif // _MSC_VER

#include "winrt/Microsoft.UI.Composition.Interop.h"

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

    namespace winrt::Microsoft::UI::Composition
    {
    export using Composition::ICompositionDrawingSurfaceInterop;
    export using Composition::ICompositionDrawingSurfaceInterop2;
    export using Composition::ICompositionGraphicsDeviceInterop;
    export using Composition::ICompositorInterop;
    export using Composition::ICompositorSwapChainInterop;
    } // namespace winrt::Microsoft::UI::Composition

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
    namespace winrt::Microsoft::UI::Composition::Interactions
    {
    export using Interactions::IVisualInteractionSourceInterop;
    }
#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion
}
#endif
