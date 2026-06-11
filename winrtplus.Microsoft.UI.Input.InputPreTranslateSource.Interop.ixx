module;

#include <sdkddkver.h>
#include <windows.h>

export module winrtplus.Microsoft.UI.Input.InputPreTranslateSource.Interop;

#if __has_include("winrt/Microsoft.UI.Input.InputPreTranslateSource.Interop.h")
extern "C++"
{
#include "winrt/Microsoft.UI.Input.InputPreTranslateSource.Interop.h"

    namespace winrt::Microsoft::UI::Input
    {
    export using Input::IInputPreTranslateKeyboardSourceHandler;
    export using Input::IInputPreTranslateKeyboardSourceInterop;
    export using Input::IInputPreTranslateKeyboardSourceHandler;
    } // namespace winrt::Microsoft::UI::Input
}
#endif
