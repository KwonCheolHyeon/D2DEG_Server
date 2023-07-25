#pragma once
#include "chDebugObject.h"
#include "chEditorObject.h"
#include "chWidget.h"
#include "chGraphics.h"

namespace ch
{
	class Editor
	{
	public:
		void Initalize();
		void Run();

		void Update();
		void FixedUpdate();
		void Render();
		void Release();
		void DebugRender(graphics::DebugMesh& mehs);

		void ImGui_Initialize();
		void ImGui_Run();
		void ImGui_Release();

	private:
		std::vector<Widget*> mWidgets;
		std::vector<EditorObject*> mEditorObjects;
		std::vector<DebugObject*> mDebugObjects;
	};
}
