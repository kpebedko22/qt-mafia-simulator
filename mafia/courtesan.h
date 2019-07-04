#ifndef COURTESAN_H
#define COURTESAN_H

#include <role.h>

class Courtesan : public Role {
public:
	Courtesan();
	~Courtesan();

	Type get_type();
	Player* day_choice(QList<Player*> list_, int index_);
	Player* night_choice(QList<Player*> list_, int index_);
};

#endif // COURTESAN_H
