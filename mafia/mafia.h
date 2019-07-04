#ifndef MAFIA_H
#define MAFIA_H

#include <role.h>

class Mafia : public Role {
public:
	Mafia();
	~Mafia();

	Type get_type();
	Player* day_choice(QList<Player*> list_, int index_);
	Player* night_choice(QList<Player*> list_, int index_);
};

#endif // MAFIA_H
