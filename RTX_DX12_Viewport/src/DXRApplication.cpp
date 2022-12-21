#include "DXRApplication.h"

DXRApplication::DXRApplication()
{

}
void DXRApplication::Init(ConfigInfo& config)
{
	// Create a new window
	HRESULT hr = Window::Create(config.width, config.height, config.instance, window, L"Reference Path Tracer Sample", &gui);
	Utils::Validate(hr, L"Error: failed to create window!");

	d3d.width = config.width;
	d3d.height = config.height;
	d3d.vsync = config.vsync;

	// Default to the windmill scene if nothing else was specified
	if (config.sceneFile.empty()) {
		Utils::Validate(E_FAIL, L"Error: you have to specify a GLTF scene to load (via '-scene' cmd. line parameter)!");
	}

	// Extract scene root path from sceneFile if it wasn't specified
	if (config.scenePath.empty()) {
		config.scenePath = Utils::ExtractPath(config.sceneFile);

		// Set scene file to file name only
		config.sceneFile = std::string(config.sceneFile.begin() + config.scenePath.length(), config.sceneFile.end());
	}

	// Load a model
	hr = GLTF::Load(config, resources.scene) ? S_OK : E_FAIL;
	Utils::Validate(hr, L"Error: failed to load GLTF assets!");

	// Initialize camera
	dxr.camera = resources.scene.cameras.empty() ? Camera() : resources.scene.cameras[0];

	// Initialize the shader compiler
	D3DShaders::InitShaderCompiler(shaderCompiler);

	// Initialize D3D12
	D3D12::CreateDevice(d3d);
	D3D12::CreateCommandQueue(d3d);
	D3D12::CreateCommandAllocator(d3d);
	D3D12::CreateFence(d3d);
	D3D12::CreateSwapChain(d3d, window);
	D3D12::CreateCommandList(d3d);
	D3D12::ResetCommandList(d3d);

	// Initialize GUI
	gui.Init(d3d, window);
	gui.SetDpiScaling(Utils::GetDpiScale(window));

	// Create common resources
	D3DResources::CreateDescriptorHeaps(d3d, resources);
	DXR::CreateDescriptorHeaps(d3d, dxr, resources);
	D3DResources::CreateBackBufferRTV(d3d, resources);
	D3DResources::CreateGeometryBuffers(d3d, resources, resources.scene);
	D3DResources::CreateRaytracingDataCB(d3d, resources);

	// Create DXR specific resources
	DXR::CreateDXRResources(d3d, dxr, resources);
	DXR::CreateBottomLevelAS(d3d, dxr, resources, resources.scene);
	DXR::CreateTopLevelAS(d3d, dxr, resources, resources.scene);
	DXR::FillDescriptorHeaps(d3d, dxr, resources);
	D3DResources::CreateTextures(d3d, resources, resources.scene);
	DXR::CreateRTProgram(d3d, dxr, shaderCompiler);
	DXR::CreatePipelineStateObject(d3d, dxr);
	DXR::CreateShaderTable(d3d, dxr, resources);

	// Execute command list to upload GPU resources
	d3d.cmdList->Close();
	ID3D12CommandList* pGraphicsList = { d3d.cmdList };
	d3d.cmdQueue->ExecuteCommandLists(1, &pGraphicsList);

	D3D12::WaitForGPU(d3d);
	D3D12::ResetCommandList(d3d);

	// Release temporary resources once upload to GPU is finished
	D3DResources::ReleaseTemporaryBuffers(d3d, resources);

	// Release GLTF data once it was uploaded to GPU
	GLTF::Cleanup(resources.scene);

	lastFrameTime = std::chrono::steady_clock::now();
}

void DXRApplication::Update()
{
	// Calculate frame time
	float elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastFrameTime).count() * 0.001f;
	lastFrameTime = std::chrono::steady_clock::now();

	// Process input from mouse and keyboard
	input.width = d3d.width;
	input.height = d3d.height;
	dxr.camera.aspect = float(d3d.width) / float(d3d.height);

	bool wasInput = false;
	wasInput |= Input::KeyHandler(input, dxr.camera, dxr.cameraSpeedAdjustment, elapsedTime);

	if (!gui.WantCaptureMouse()) {
					wasInput |= Input::MouseHandler(input, dxr.camera, elapsedTime);
	}

	if (input.toggleGui) d3d.renderGui = !d3d.renderGui;
	input.toggleGui = false;

	// Update GUI
	gui.Update(d3d, elapsedTime);

	// Reload shaders on request
	if (input.reloadShaders) DXR::ReloadShaders(d3d, dxr, resources, shaderCompiler);
	input.reloadShaders = false;

	// Update ray tracing data constant buffer
	D3DResources::UpdateRaytracingDataCB(d3d, dxr, resources, elapsedTime);
}

void DXRApplication::Render()
{
	// Run ray tracing
	DXR::BuildCommandList(d3d, dxr, resources, &gui, &input);

	// Render GUI
	gui.Render(d3d, resources);

	// End the frame and reste command list
	D3D12::Present(d3d);

	if (input.captureScreenshot) D3D12::ScreenCapture(d3d, "screenshot");
	input.captureScreenshot = false;

	D3D12::MoveToNextFrame(d3d);
	D3D12::ResetCommandList(d3d);

	// Cleanup temporary resources
	D3DResources::ReleaseTemporaryBuffers(d3d, resources);
	dxr.scratchBuffersCache.Reset();
}

void DXRApplication::Cleanup()
{
	D3D12::WaitForGPU(d3d);
	CloseHandle(d3d.fenceEvent);

	gui.Destroy();

	DXR::Destroy(dxr);
	D3DResources::Destroy(resources);
	D3DShaders::Destroy(shaderCompiler);
	D3D12::Destroy(d3d);

	DestroyWindow(window);
}