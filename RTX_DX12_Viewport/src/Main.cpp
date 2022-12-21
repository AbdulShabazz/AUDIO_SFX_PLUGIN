#include <chrono>
#include <functional>
#include <thread>

#include "DXRApplication.h"

struct ParamSTRUCT
{
    MSG msg = { 0 };
    DXRApplication app;
};

void set_interval(
    std::function<void(ParamSTRUCT&)> callback,
    ParamSTRUCT& ParamStruct,
    std::chrono::milliseconds intervalInt64
)
{
    // Set Timer
    while (WM_QUIT != ParamStruct.msg.message)
    {
        callback(ParamStruct);
        std::this_thread::sleep_for(intervalInt64);
    }
    ParamStruct.app.Cleanup();
}

void RenderCallback(ParamSTRUCT& ParamStruct)
{
    if (PeekMessage(&ParamStruct.msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&ParamStruct.msg);
        DispatchMessage(&ParamStruct.msg);
    }

    ParamStruct.app.Update();
    ParamStruct.app.Render();
}

/**
 * Program entry point.
 */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);

    // Tell Windows that we're DPI aware (we handle scaling ourselves, e.g. the scaling of GUI)
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

    HRESULT hr = EXIT_SUCCESS;
    {
        MSG msg = { 0 };

        // Get the application configuration
        ConfigInfo config;
        hr = Utils::ParseCommandLine(lpCmdLine, config);
        if (hr != EXIT_SUCCESS) return hr;

        // Initialize
        ParamSTRUCT ParamStruct;
        ParamStruct.msg = msg;
        ParamStruct.app.Init(config);

        // Main loop
        set_interval(
            RenderCallback,
            ParamStruct,
            std::chrono::milliseconds(1000 / 2000) // eg. 1000/60 = 60fps
        );
    }

#if defined _CRTDBG_MAP_ALLOC
    _CrtDumpMemoryLeaks();
#endif

    return hr;
}