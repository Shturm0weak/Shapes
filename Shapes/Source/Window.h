#pragma once

#include "Camera.h"

#include "../../Vendor/glm/glm.hpp"

#include <Windows.h>
#include <string>
#include <vector>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
private:

	std::wstring m_Title;

	std::vector<Camera*> m_Cameras;

	glm::vec2 m_ScreenPixelsInBitMapPixels;

	glm::ivec2 m_BitMapSize;

	void* m_BitMapMemory = nullptr;

	HINSTANCE m_HInstance;
	HWND m_HWnd;
	BITMAPINFO m_BitMapInfo;
	HBITMAP m_HBitMap;
	BLENDFUNCTION m_BlendFunction;

	bool m_IsRunning = true;

	Window() = default;
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void Update();
public:

	static Window& GetInstance();

	glm::ivec2 GetSize(HWND hWnd = GetInstance().m_HWnd);

	glm::ivec2 GetBitMapSize() const { return m_BitMapSize; }

	void Init(
		const std::wstring& title = L"Window",
		const glm::ivec2& size = { 600, 600 },
		const glm::vec2& screenPixelsInBitMapPixels = { 1.0f, 1.0f }
	);

	void SetTitle(const std::wstring& title);

	std::wstring GetTitle() const { return m_Title; }

	bool IsRunning() const { return m_IsRunning; }

	void Resize(const glm::ivec2& size);

	void Clear(const glm::vec3& color);

	void NewFrame();

	void EndFrame();

	uint8_t* GetPixel(const glm::ivec2& position);

	/**
	 * @param position in pixels.
	 */
	void FillPixel(const glm::ivec2& position, const glm::vec3& color);

	/**
	 * @param start in pixels.
	 * @param end in pixels.
	 */
	void DrawLine(const glm::ivec2& start, const glm::ivec2& end, const glm::vec3& color);

	/**
	 * Draws a rectangle by min and max positions of the bounding box.
	 * @param min in pixels.
	 * @param max in pixels.
	 */
	void DrawRectangle(const glm::ivec2& min, const glm::ivec2& max, const glm::vec3& color);

	/**
	 * Draws a rectangle by the positions of 4 vertices.
	 * @param v0 in pixels.
	 * @param v1 in pixels.
	 * @param v2 in pixels.
	 * @param v3 in pixels.
	 */
	void DrawRectangle(const glm::ivec2& v0, const glm::ivec2& v1, const glm::ivec2& v2, const glm::ivec2& v3, const glm::vec3& color);

	/**
	 * @param position in pixels.
	 * @param radius in pixels.
	 * @param thinkness in pixels.
	 */
	void DrawCircle(const glm::ivec2& position, int radius, const glm::vec3& color, int thinkness = 1);

	/**
	 * Draws a triangle by the positions of 3 vertices.
	 * @param v0 in pixels.
	 * @param v1 in pixels.
	 * @param v2 in pixels.
	 */
	void DrawTriangle(const glm::ivec2& v0, const glm::ivec2& v1, const glm::ivec2& v2, const glm::vec3& color);

	Camera* CreateCamera();
};