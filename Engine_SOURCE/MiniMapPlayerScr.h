#pragma once
#include "chScript.h"

namespace ch
{
	class MiniMapPlayerScr : public Script
	{
	public:
		MiniMapPlayerScr();
		virtual ~MiniMapPlayerScr();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;



	};
}


//미니맵 비율 900/ 350		 9 / 3.5   scale만큼 곱해주면 될듯
// 
// 
// 원본 1899/2377픽셀    189.9 / 237.7  * 50 / 62.91f   현재 보이는 크기 =   9495  / 14953.707
// 플레이 씬에서 인게임 맵 스케일 mapTr->SetScale(Vector3(50.0f, 62.91f, 0.1f));
// 카메라 비율 원본에  1/100한 상태 