#ifndef DETECTIVE_H
#define DETECTIVE_H

#include <role.h>

class Detective : public Role {
public:
	Detective();
	~Detective();

	Type get_type();
	Player* day_choice(QList<Player*> list_, int index_);
	Player* night_choice(QList<Player*> list_, int index_);
};

#endif // DETECTIVE_H
