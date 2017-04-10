#include "HoldMethod.h"

void HoldMethod::pay(Paycheck &pc) const
{
    pc.setField("Disposition", "Hold");
}
