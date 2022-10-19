#ifndef PHASE_MAFIA_H
#define PHASE_MAFIA_H

#include <phase.h>

class Phase_Mafia : public Phase {
public:
	Phase_Mafia();
	~Phase_Mafia();

	void execute(QList<Player*> players_);
	void update_can_execute(QList<Player*> players_);

	Type get_type();
	void phase_1(QList<Player*> players_);
	void phase_2(QList<Player*> players_);
	void phase_3(QList<Player*> players_);
	void phase_4(QList<Player*> players_);
};

#endif // PHASE_MAFIA_H
