# YexuanXiao.CppWinRTPlus.Ext

CppWinRTPlus.Ext provides a set of C++20 module interface extensions for C++/WinRT and the Windows App SDK.

## Module `winrtplus_coroutine`

Provides coroutine helpers:

- `winrtplus::resume_foreground(dispatcher, priority)`
- `co_await dispatcher`

Supported dispatchers:

- `Windows::System::DispatcherQueue`
- `Microsoft::UI::Dispatching::DispatcherQueue`
- `Windows::UI::Core::CoreDispatcher`

## WinUI Interop Modules

The following module wrapper wraps the WinUI Interop header files from Microsoft.WindowsAppSDK.InteractiveExperiences as C++ modules.

All declarations remain in the original namespace.

### `winrtplus.Microsoft.UI.Interop`

Wraps `winrt/Microsoft.UI.Interop.h`:

- `GetWindowIdFromWindow(HWND)`
- `GetWindowFromWindowId(WindowId)`
- `GetDisplayIdFromMonitor(HMONITOR)`
- `GetMonitorFromDisplayId(DisplayId)`
- `GetIconIdFromIcon(HICON)`
- `GetIconFromIconId(IconId)`

### `winrtplus.Microsoft.UI.Composition.Interop`

Wraps `winrt/Microsoft.UI.Composition.Interop.h`:

- `ICompositionDrawingSurfaceInterop`
- `ICompositionDrawingSurfaceInterop2`
- `ICompositionGraphicsDeviceInterop`
- `ICompositorInterop`
- `ICompositorSwapChainInterop`
- `IVisualInteractionSourceInterop`

### `winrtplus.Microsoft.UI.Designer.Interop`

Wraps `winrt/Microsoft.UI.Designer.Interop.h`:

- `IDesignerOutputHostInterop`

### `winrtplus.Microsoft.UI.Dispatching.Interop`

Wraps `winrt/Microsoft.UI.Dispatching.Interop.h`:

- `ContentPreTranslateMessage(const MSG*)`

### `winrtplus.Microsoft.UI.Input.InputCursor.Interop`

Wraps `winrt/Microsoft.UI.Input.InputCursor.Interop.h`:

- `IInputCursorStaticsInterop`

### `winrtplus.Microsoft.UI.Input.InputPreTranslateSource.Interop`

Wraps `winrt/Microsoft.UI.Input.InputPreTranslateSource.Interop.h`:

- `IInputPreTranslateKeyboardSourceHandler`
- `IInputPreTranslateKeyboardSourceInterop`

## Requirements

- Microsoft.Windows.CppWinRT 3.0.
- Microsoft.WindowsAppSDK.InteractiveExperiences 2.0 (optional).
- Enable C++/WinRT module generation with `CppWinRTBuildModule`.
- Enable STL module support with `BuildStlModules`.
- Define `WINRT_ENABLE_LEGACY_COM` globally.

If Microsoft.WindowsAppSDK.InteractiveExperiences is not installed, the relevant module will still exist, but will not contain any content.

Example project settings:

```xml
<PropertyGroup>
  <CppWinRTBuildModule>true</CppWinRTBuildModule>
</PropertyGroup>

<ItemDefinitionGroup>
  <ClCompile>
    <BuildStlModules>true</BuildStlModules>
    <PreprocessorDefinitions>WINRT_ENABLE_LEGACY_COM;%(PreprocessorDefinitions)</PreprocessorDefinitions>
  </ClCompile>
</ItemDefinitionGroup>
```
