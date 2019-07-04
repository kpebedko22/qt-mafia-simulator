#ifndef CIVILIAN_H
#define CIVILIAN_H

#include <role.h>

class Civilian : public Role {
public:
	Civilian();
	~Civilian();

	Type get_type();
	Player* day_choice(QList<Player*> list_, int index_);
	Player* night_choice(QList<Player*> list_, int index_);
};

#endif // CIVILIAN_H
