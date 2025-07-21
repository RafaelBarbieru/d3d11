#include "renderer.hpp"
#include <dxgi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

Renderer::Renderer(HWND hwnd) {
    InitD3D(hwnd);
}

Renderer::~Renderer() {
    CleanupRenderTarget();
    if (swapChain) swapChain->Release();
    if (context) context->Release();
    if (device) device->Release();
}

void Renderer::InitD3D(HWND hwnd) {
    DXGI_SWAP_CHAIN_DESC scDesc = {};
    scDesc.BufferCount = 1;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow = hwnd;
    scDesc.SampleDesc.Count = 1;
    scDesc.Windowed = TRUE;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr, 0,
        D3D11_SDK_VERSION,
        &scDesc,
        &swapChain,
        &device,
        nullptr,
        &context
    );

    if (FAILED(hr)) {
        MessageBox(hwnd, L"Failed to initialize Direct3D 11.", L"Error", MB_OK);
        exit(-1);
    }

    CreateRenderTarget();
}

void Renderer::CreateRenderTarget() {
    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    context->OMSetRenderTargets(1, &renderTargetView, nullptr);

    D3D11_VIEWPORT vp = { 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f }; // hardcoded 720p viewport
    context->RSSetViewports(1, &vp);
}

void Renderer::CleanupRenderTarget() {
    if (renderTargetView) {
        renderTargetView->Release();
        renderTargetView = nullptr;
    }
}

void Renderer::Clear() {
    float clearColor[4] = { 0.392f, 0.584f, 0.929f, 1.0f };
    context->ClearRenderTargetView(renderTargetView, clearColor);
}

void Renderer::Present() {
    swapChain->Present(1, 0);
}

void Renderer::Resize(UINT width, UINT height) {
    CleanupRenderTarget();
    swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    CreateRenderTarget();
}
