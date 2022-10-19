#ifndef PHASE_H
#define PHASE_H

#include <QList>
#include <player.h>

struct Voting{
	Voting(Player* elected_, Player* voter_, int votes_){
		elected = elected_;
		voters << voter_;
		votes = votes_;
	}

	Player* elected;
	QList<Player*> voters;
	int votes;

	void join(Voting* to_join_){
		votes += to_join_->votes;
		to_join_->votes = 0;
		for (int i = 0; i < to_join_->voters.count(); i++)
			voters << to_join_->voters[i];
		to_join_->voters.clear();
	}

	int get_sum_oratory(){
		int sum_oratory = 0;
		for (int i = 0; i < voters.count(); i++)
			sum_oratory += voters[i]->get_oratory();
		return sum_oratory;
	}
};

class Phase {
public:
	Phase();
	virtual ~Phase();

	virtual void update_can_execute(QList<Player*> players_) = 0;
	bool get_can_execute();

	virtual void execute(QList<Player*> players_) = 0;

	void new_round();

	enum Type {
		COURTESAN_PHASE= 0,
		MAFIA_PHASE = 1,
		DOCTOR_PHASE = 2,
		DETECTIVE_PHASE = 3,
		DAY_PHASE  = 4,
		BORDERLINE_PHASE = 5
	};

	virtual Type get_type() = 0;

	bool is_courtesan_phase();
	bool is_mafia_phase();
	bool is_doctor_phase();
	bool is_detective_phase();
	bool is_day_phase();
	bool is_borderline_phase();

	virtual void phase_1(QList<Player*> players_) = 0;
	virtual void phase_2(QList<Player*> players_) = 0;
	virtual void phase_3(QList<Player*> players_) = 0;
	virtual void phase_4(QList<Player*> players_) = 0;

	QString get_narrator_speech();
	QString get_log_text();
	Voting* get_choice();
	int get_count_choices();
	void set_choices(QList<Voting*> list_);

protected:
	QString narrator_speech;
	QString log_text;

	bool can_execute;
	int stage;
	QList<Voting*> choices;

	QList<Voting*> join_choices(QList<Voting*> list_);
	bool zero_votes(QList<Voting*> list_);
	int get_zero_votes_index(QList<Voting*> list_);
	bool is_one_max_votes(QList<Voting*> list_);
	QList<Voting*> disband_smallest_group(QList<Voting*> list_);
};

#endif // PHASE_H
