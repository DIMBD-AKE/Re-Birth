#include "../../../stdafx.h"
#include "ArmorParent.h"
#include "../../Status.h"



ArmorParent::ArmorParent()
{
}


ArmorParent::~ArmorParent()
{
}

ArmorParent * ArmorParent::Clone()
{
	return new ArmorParent(*this);
}
