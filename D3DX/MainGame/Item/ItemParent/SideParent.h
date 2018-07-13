#pragma once
#include "../ItemParent.h"
class SideParent : public ItemParent
{
public:
	SideParent();
	~SideParent();

	virtual SideParent* Clone() override;

};

