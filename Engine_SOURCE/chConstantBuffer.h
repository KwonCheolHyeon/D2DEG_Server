#pragma once

#include "chGraphics.h"

using namespace ch::enums;

namespace ch::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer(eCBType type);
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void SetData(void* data);
		void Bind(eShaderStage stage);

		//void SetType(eCBType type) { mType = type; }


	private:
		const eCBType mType;
	};
}
