#include "role.h"

Role::Role() = default;

Role::~Role() = default;

bool Role::is(Type type) {
    return this->getType() == type;
}
