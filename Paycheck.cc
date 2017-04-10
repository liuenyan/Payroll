#include "Paycheck.h"

using namespace std;

static const string emptyString("");

const string &Paycheck::getField(const string &key) const
{
    auto it = itsFields.find(key);
    if (it != itsFields.end()) {
        return it->second;
    }
    return emptyString;
}

void Paycheck::setField(const std::string &key, const std::string &value)
{
    itsFields[key] = value;
}
