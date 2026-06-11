module;

#include <windows.h>
#include <sdkddkver.h>
#include <inspectable.h>

export module winrtplus.Microsoft.UI.Input.InputCursor.Interop;

#if __has_include("winrt/Microsoft.UI.Input.InputCursor.Interop.h")
import winrt.Microsoft.UI.Input;

#define WINRT_IMPORT_MODULE

using winrt::Microsoft::UI::Input::IInputCursor;
extern "C++"
{
#include "winrt/Microsoft.UI.Input.InputCursor.Interop.h"

    namespace winrt::Microsoft::UI::Input
    {
    export using Input::IInputCursorStaticsInterop;
    }
}
#endif
