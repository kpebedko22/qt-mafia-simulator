#ifndef PHASE_DETECTIVE_H
#define PHASE_DETECTIVE_H

#include <phase.h>

class Phase_Detective : public Phase{
public:
	Phase_Detective();
	~Phase_Detective();

	void execute(QList<Player*> players_);
	void update_can_execute(QList<Player*> players_);

	Type get_type();
	void phase_1(QList<Player*> players_);
	void phase_2(QList<Player*> players_);
	void phase_3(QList<Player*> players_);
	void phase_4(QList<Player*> players_);
};

#endif // PHASE_DETECTIVE_H
