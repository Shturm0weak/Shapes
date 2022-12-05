#include "EntryPoint.h"

#include "Time.h"
#include "Window.h"

int EntryPoint::Run(Application* application)
{
	Window& window = Window::GetInstance();

	// Need to calculate delta time before the main loop, 
	// otherwise delta time will be too big at the first frame.
	Time::CalculateDeltaTime();

	application->OnStart();
	while (window.IsRunning())
	{
		window.NewFrame();

		application->OnUpdate();

		window.Clear(glm::vec4(1.0f));

		if (Camera* camera = application->m_Scene.GetBindedCamera())
		{
			application->m_Scene.Render(*camera);
		}

		window.EndFrame();
	}

	application->OnClose();
	application->m_Scene.ShutDown();

	return 0;
}
