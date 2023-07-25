#include "chPaintShader.h"


namespace ch::graphics
{
	PaintShader::PaintShader()
		: ComputeShader()
		, mTarget(nullptr)
	{
	}

	PaintShader::~PaintShader()
	{
	}

	void PaintShader::Binds()
	{
		mTarget->BindUnorderedAccessView(0);

		mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1;//mTarget->GetWidth값을 조절하면 절반정보 지울 수 도 있다.
		mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}

	void PaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessView(0);
	}

}
