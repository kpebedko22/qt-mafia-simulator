#include "role.h"

Role::Role(){}
Role::~Role() {}

bool Role::is_mafia(){
	return this->get_type() == MAFIA;
}

bool Role::is_civilian(){
	return this->get_type() == CIVILIAN;
}

bool Role::is_detective(){
	return this->get_type() == DETECTIVE;
}

bool Role::is_doctor(){
	return this->get_type() == DOCTOR;
}

bool Role::is_courtesan(){
	return this->get_type() == COURTESAN;
}
