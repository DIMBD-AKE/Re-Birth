#pragma once
#include "../ItemParent.h"

class ArmorParent : public ItemParent
{
public:
	ArmorParent();
	~ArmorParent();
	virtual ArmorParent* Clone() override;

};

