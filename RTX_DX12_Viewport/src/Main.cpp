#include "DXRApplication.h"

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
        DXRApplication app;
        app.Init(config);

        // Main loop
        while (WM_QUIT != msg.message)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            app.Update();
            app.Render();
        }

        app.Cleanup();
    }

#if defined _CRTDBG_MAP_ALLOC
    _CrtDumpMemoryLeaks();
#endif

    return hr;
}