#pragma once
#include <windows.h>
#include <d3d11.h>

class Renderer {
public:
    Renderer(HWND hwnd);
    ~Renderer();

    void Clear();
    void Present();
    void Resize(UINT width, UINT height);

private:
    void InitD3D(HWND hwnd);
    void CreateRenderTarget();
    void CleanupRenderTarget();

private:
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* renderTargetView = nullptr;
};
