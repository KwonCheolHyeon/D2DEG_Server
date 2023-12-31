#include "chGenericAnimator.h"

GenericAnimator::GenericAnimator()
	: Param(AnimatorParam())
	, StartValue(0.f)
	, CurValue(0.f)
	, EndValue(0.f)
	, AccTime(0.f)
	, EndTime(0.f)
{

}

GenericAnimator::~GenericAnimator()
{

}

bool GenericAnimator::Start(const AnimatorParam& InParam)
{
	// 애니메이션타입이 아직 구현안된거면 중지
	if (InParam.AnimType == EAnimType::Max)
	{
		return false;
	}

	Param = InParam;
	Param.Handle = ++HandleId;

	StartValue = InParam.StartValue;
	CurValue = InParam.StartValue;
	EndValue = InParam.EndValue;

	AccTime = 0.f;
	EndTime = InParam.DurationTime;

	return true;
}

void GenericAnimator::Update(float InDeltaTime)
{
	if (!IsRunning())
		return;

	AccTime += InDeltaTime;

	if (AccTime >= EndTime)
	{
		Stop(true);
		return;
	}

	if (Param.AnimType == EAnimType::Linear)
	{
		CurValue = ((StartValue * (EndTime - AccTime)) + (EndValue * AccTime)) / EndTime;
	}

	if (Param.DurationFunc)
		Param.DurationFunc(CurValue);
}

bool GenericAnimator::IsRunning()
{
	return Param.Handle != InvalidHandleId;
}

void GenericAnimator::Stop(bool InCompleteEvent)
{
	if (InCompleteEvent)
	{
		if (Param.CompleteFunc)
		{
			Param.CompleteFunc(EndValue);
			Param.CompleteFunc = nullptr;
			return;
		}
	}

	Param = AnimatorParam();
	StartValue = 0.f;
	CurValue = 0.f;
	EndValue = 0.f;

	AccTime = 0.f;
	EndTime = 0.f;
}

