#pragma once
#include "../ItemParent.h"
class BladeParent : public ItemParent
{
public:
	BladeParent();
	~BladeParent();

	virtual BladeParent* Clone() override;
};

