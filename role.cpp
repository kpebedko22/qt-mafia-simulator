#include "role.h"

Role::Role() {}

Role::~Role() {}

bool Role::is(Type type) {
    return this->getType() == type;
}
