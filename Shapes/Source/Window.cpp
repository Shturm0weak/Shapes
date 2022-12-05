#include "Window.h"

#include "Time.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            {
                DestroyWindow(hWnd);
            }
            break;
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
        case WM_SIZE:
            {
                Window& window = Window::GetInstance();
                window.Resize(window.GetSize(hWnd));
            }
            break;
        default:
            {
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
            break;
    }
}

bool Window::ProcessMessages()
{
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) return false;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

void Window::Update()
{
    HDC DeviceContext = GetDC(m_HWnd);
    RECT rect = {};
    GetClientRect(m_HWnd, &rect);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;
    SetStretchBltMode(DeviceContext, BLACKONWHITE);
    StretchDIBits(
        DeviceContext,
        0, 0, windowWidth, windowHeight,
        0, 0, m_BitMapSize.x, m_BitMapSize.y,
        m_BitMapMemory,
        &m_BitMapInfo,
        DIB_RGB_COLORS, SRCCOPY
    );
    ReleaseDC(m_HWnd, DeviceContext);
}

void Window::Init(const std::wstring& title, const glm::ivec2& size, const glm::vec2& screenPixelsInBitMapPixels)
{
    m_Title = title;
    m_HInstance = GetModuleHandle(nullptr);
    m_ScreenPixelsInBitMapPixels = screenPixelsInBitMapPixels;
    const wchar_t* className = L"WINDOWCLASS";

    WNDCLASS wndClass = {};
    wndClass.lpszClassName = className;
    wndClass.hInstance = m_HInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.style = CS_DBLCLKS;
    wndClass.lpfnWndProc = WindowProc;
    RegisterClass(&wndClass);

    DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + size.x;
    rect.bottom = rect.top + size.y;

    AdjustWindowRect(&rect, style, false);

    m_HWnd = CreateWindowEx(
        0,
        className,
        m_Title.c_str(),
        style,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        m_HInstance,
        NULL
    );

    ShowWindow(m_HWnd, SW_SHOW);
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    m_BlendFunction.BlendOp = AC_SRC_OVER;
    m_BlendFunction.BlendFlags = 0;
    m_BlendFunction.SourceConstantAlpha = 0xff;
    m_BlendFunction.AlphaFormat = AC_SRC_ALPHA;
}

Window::~Window()
{
    if (m_BitMapMemory)
    {
        VirtualFree(m_BitMapMemory, 0, MEM_RELEASE);
    }

    const wchar_t* className = L"WINDOWCLASS";
    UnregisterClass(className, m_HInstance);

    for (auto& camera : m_Cameras)
    {
        delete camera;
    }
}

inline Window& Window::GetInstance()
{
    static Window window;
    return window;
}

glm::ivec2 Window::GetSize(HWND hWnd)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    return { rect.right - rect.left, rect.bottom - rect.top };
}

void Window::Resize(const glm::ivec2& size)
{
    if (m_BitMapMemory)
    {
        VirtualFree(m_BitMapMemory, 0, MEM_RELEASE);
    }

    m_BitMapSize = (glm::vec2)size / m_ScreenPixelsInBitMapPixels;

    m_BitMapInfo.bmiHeader.biSize = sizeof(m_BitMapInfo.bmiHeader);
    m_BitMapInfo.bmiHeader.biWidth = m_BitMapSize.x;
    m_BitMapInfo.bmiHeader.biHeight = m_BitMapSize.y;
    m_BitMapInfo.bmiHeader.biPlanes = 1;
    m_BitMapInfo.bmiHeader.biBitCount = 32;
    m_BitMapInfo.bmiHeader.biCompression = BI_RGB;
    m_BitMapInfo.bmiHeader.biSizeImage = m_BitMapSize.x * m_BitMapSize.y * 4;

    const int m_BitMapMemorySize = m_BitMapSize.x * m_BitMapSize.y * 4;
    m_BitMapMemory = VirtualAlloc(0, m_BitMapMemorySize, MEM_COMMIT, PAGE_READWRITE);

    for (auto& camera : m_Cameras)
    {
        camera->SetOrthographic(m_BitMapSize);
    }
}

void Window::SetTitle(const std::wstring& title)
{
    m_Title = title;
    SetWindowTextW(m_HWnd, m_Title.c_str());
}

void Window::Clear(const glm::vec3& color)
{
    for (size_t i = 0; i < m_BitMapSize.x; i++)
    {
        for (size_t j = 0; j < m_BitMapSize.y; j++)
        {
            FillPixel(glm::ivec2(i, j), color);
        }
    }
}

void Window::NewFrame()
{
    if (ProcessMessages() == false)
    {
        m_IsRunning = false;
    }

    Time::CalculateDeltaTime();
}

void Window::EndFrame()
{
    Update();
}

uint8_t* Window::GetPixel(const glm::ivec2& position)
{
    if (0 <= position.x && position.x < m_BitMapSize.x && 0 <= position.y && position.y < m_BitMapSize.y)
    {
        const int index = (position.x + position.y * m_BitMapSize.x) * 4;
        return &((uint8_t*)m_BitMapMemory)[index];
    }

    return nullptr;
}

void Window::FillPixel(const glm::ivec2& position, const glm::vec3& color)
{
    uint8_t* pixel = GetPixel(position);
    if (pixel)
    {
        pixel[0] = (uint8_t)(color[2] * 255);
        pixel[1] = (uint8_t)(color[1] * 255);
        pixel[2] = (uint8_t)(color[0] * 255);
        pixel[3] = (uint8_t)(255);
    }
}

void Window::DrawLine(const glm::ivec2& start, const glm::ivec2& end, const glm::vec3& color)
{
    glm::vec2 distance = { (end.x - start.x), (end.y - start.y) };
    
    int steps = glm::abs(distance.x) > glm::abs(distance.y) ? glm::abs(distance.x) : glm::abs(distance.y);
    if (steps == 0)
    {
        return;
    }

    glm::vec2 increment = { distance.x / (float)steps, distance.y / (float)steps };

    glm::vec2 newStart = start;
    for (int i = 0; i < steps; i++)
    {
        float scale1 = ((float)(steps - i) / (float)steps);
        float scale2 = 1.0f - scale1;
        newStart += increment;
        FillPixel(glm::ivec2(glm::round(newStart.x), glm::round(newStart.y)), color);
    }
}

void Window::DrawRectangle(const glm::ivec2& min, const glm::ivec2& max, const glm::vec3& color)
{
    DrawLine(min, { min.x, max.y }, color);
    DrawLine(min, { max.x, min.y }, color);
    DrawLine({ min.x, max.y }, max, color);
    DrawLine(max, { max.x, min.y }, color);
}

void Window::DrawRectangle(const glm::ivec2& v0, const glm::ivec2& v1, const glm::ivec2& v2, const glm::ivec2& v3, const glm::vec3& color)
{
    DrawLine(v0, v1, color);
    DrawLine(v1, v2, color);
    DrawLine(v2, v3, color);
    DrawLine(v3, v0, color);
}

void Window::DrawCircle(const glm::ivec2& position, int radius, const glm::vec3& color, int thinkness)
{
    glm::ivec2 min = position - glm::ivec2(radius, radius);
    glm::ivec2 max = position + glm::ivec2(radius, radius);

    for (int i = min.x; i < max.x; i++)
    {
        for (int j = min.y; j < max.y; j++)
        {
            float distance = glm::distance(glm::vec2(i, j), glm::vec2(position));
            if (distance <= radius && distance >= radius - thinkness)
            {
                FillPixel({ i, j }, color);
            }
        }
    }
}

void Window::DrawTriangle(const glm::ivec2& v0, const glm::ivec2& v1, const glm::ivec2& v2, const glm::vec3& color)
{
    DrawLine(v0, v1, color);
    DrawLine(v1, v2, color);
    DrawLine(v2, v0, color);
}

Camera* Window::CreateCamera()
{
    m_Cameras.emplace_back(new Camera());
    return *(m_Cameras.rbegin());
}
