#ifndef PHASE_BORDERLINE_H
#define PHASE_BORDERLINE_H

#include <phase.h>

class Phase_Borderline : public Phase {
public:
	Phase_Borderline();
	~Phase_Borderline();

	void execute(QList<Player*> players_);
	void update_can_execute(QList<Player*> players_);

	Type get_type();
	void phase_1(QList<Player*> players_);
	void phase_2(QList<Player*> players_);
	void phase_3(QList<Player*> players_);
	void phase_4(QList<Player*> players_);
};

#endif // PHASE_BORDERLINE_H
