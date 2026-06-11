module;

#include <windows.h>
#include <winerror.h>
#include <cassert>

export module winrtplus.Microsoft.UI.Interop;

#if __has_include("winrt/Microsoft.UI.Interop.h")
import winrt.Microsoft.UI;

// https://github.com/microsoft/WindowsAppSDK/issues/6563
// "extern 'C++'" is not used, as the original version uses internal linkage.

namespace winrt::Microsoft::UI
{
using GetWindowIdFromWindow_t = HRESULT(STDAPICALLTYPE *)(_In_ HWND, _Out_ winrt::Microsoft::UI::WindowId *);
using GetWindowFromWindowId_t = HRESULT(STDAPICALLTYPE *)(_In_ winrt::Microsoft::UI::WindowId, _Out_ HWND *);
using GetDisplayIdFromMonitor_t = HRESULT(STDAPICALLTYPE *)(_In_ HMONITOR, _Out_ winrt::Microsoft::UI::DisplayId *);
using GetMonitorFromDisplayId_t = HRESULT(STDAPICALLTYPE *)(_In_ winrt::Microsoft::UI::DisplayId, _Out_ HMONITOR *);
using GetIconIdFromIcon_t = HRESULT(STDAPICALLTYPE *)(_In_ HICON, _Out_ winrt::Microsoft::UI::IconId *);
using GetIconFromIconId_t = HRESULT(STDAPICALLTYPE *)(_In_ winrt::Microsoft::UI::IconId, _Out_ HICON *);

GetWindowIdFromWindow_t GetWindowIdFromWindowInternal;
GetWindowFromWindowId_t GetWindowFromWindowIdInternal;
GetDisplayIdFromMonitor_t GetDisplayIdFromMonitorInternal;
GetMonitorFromDisplayId_t GetMonitorFromDisplayIdInternal;
GetIconIdFromIcon_t GetIconIdFromIconInternal;
GetIconFromIconId_t GetIconFromIconIdInternal;

std::atomic<HMODULE> FrameworkUdk{};

void PrepareDLL()
{
    if (FrameworkUdk.load() != nullptr)
        return;

    HMODULE hmod = ::LoadLibrary(L"Microsoft.Internal.FrameworkUdk.dll");

    assert(hmod != nullptr);

    GetWindowIdFromWindowInternal =
        reinterpret_cast<GetWindowIdFromWindow_t>(::GetProcAddress(hmod, "Windowing_GetWindowIdFromWindow"));
    GetWindowFromWindowIdInternal =
        reinterpret_cast<GetWindowFromWindowId_t>(::GetProcAddress(hmod, "Windowing_GetWindowFromWindowId"));
    GetDisplayIdFromMonitorInternal =
        reinterpret_cast<GetDisplayIdFromMonitor_t>(::GetProcAddress(hmod, "Windowing_GetDisplayIdFromMonitor"));
    GetMonitorFromDisplayIdInternal =
        reinterpret_cast<GetMonitorFromDisplayId_t>(::GetProcAddress(hmod, "Windowing_GetMonitorFromDisplayId"));
    GetIconIdFromIconInternal =
        reinterpret_cast<GetIconIdFromIcon_t>(::GetProcAddress(hmod, "Windowing_GetIconIdFromIcon"));
    GetIconFromIconIdInternal =
        reinterpret_cast<GetIconFromIconId_t>(::GetProcAddress(hmod, "Windowing_GetIconFromIconId"));

    assert((GetWindowIdFromWindowInternal != nullptr) && (GetWindowFromWindowIdInternal != nullptr) &&
           (GetDisplayIdFromMonitorInternal != nullptr) && (GetMonitorFromDisplayIdInternal != nullptr) &&
           (GetIconIdFromIconInternal != nullptr) && (GetIconFromIconIdInternal != nullptr));

    FrameworkUdk.store(hmod);
}

export winrt::Microsoft::UI::WindowId GetWindowIdFromWindow(_In_ const HWND hWnd)
{
    PrepareDLL();
    winrt::Microsoft::UI::WindowId winrtWindowId{};
    winrt::check_hresult(GetWindowIdFromWindowInternal(hWnd, &winrtWindowId));
    return winrtWindowId;
}

export HWND GetWindowFromWindowId(_In_ const winrt::Microsoft::UI::WindowId windowId)
{
    PrepareDLL();
    HWND hWnd{};
    winrt::check_hresult(GetWindowFromWindowIdInternal(windowId, &hWnd));
    return hWnd;
}

export winrt::Microsoft::UI::DisplayId GetDisplayIdFromMonitor(_In_ const HMONITOR hMonitor)
{
    PrepareDLL();
    winrt::Microsoft::UI::DisplayId winrtDisplayId{};
    winrt::check_hresult(GetDisplayIdFromMonitorInternal(hMonitor, &winrtDisplayId));
    return winrtDisplayId;
}

export HMONITOR GetMonitorFromDisplayId(_In_ const winrt::Microsoft::UI::DisplayId displayId)
{
    PrepareDLL();
    HMONITOR hMonitor{};
    winrt::check_hresult(GetMonitorFromDisplayIdInternal(displayId, &hMonitor));
    return hMonitor;
}

export winrt::Microsoft::UI::IconId GetIconIdFromIcon(_In_ const HICON hIcon)
{
    PrepareDLL();
    winrt::Microsoft::UI::IconId winrtIconId{};
    winrt::check_hresult(GetIconIdFromIconInternal(hIcon, &winrtIconId));
    return winrtIconId;
}

export HICON GetIconFromIconId(_In_ const winrt::Microsoft::UI::IconId iconId)
{
    PrepareDLL();
    HICON hIcon{};
    winrt::check_hresult(GetIconFromIconIdInternal(iconId, &hIcon));
    return hIcon;
}
} // namespace winrt::Microsoft::UI
#endif
