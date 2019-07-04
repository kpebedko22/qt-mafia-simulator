#ifndef DOCTOR_H
#define DOCTOR_H

#include <role.h>

class Doctor : public Role {
public:
	Doctor();
	~Doctor();

	Type get_type();
	Player* day_choice(QList<Player*> list_, int index_);
	Player* night_choice(QList<Player*> list_, int index_);
};

#endif // DOCTOR_H
