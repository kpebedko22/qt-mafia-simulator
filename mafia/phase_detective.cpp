#include "phase_detective.h"
#include "role.h"

Phase_Detective::Phase_Detective(){
	stage = 0;
	choices.clear();
}

Phase_Detective::~Phase_Detective(){}

Phase::Type Phase_Detective::get_type(){ return DETECTIVE_PHASE; }

void Phase_Detective::update_can_execute(QList<Player*> players_){
	int num_detective = 0;
	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->role->is_detective() && players_[i]->is_alive()) num_detective++;

	if (num_detective == 0){ can_execute = false; return;}
	if (stage <= 4){ can_execute = true; stage++; }
	if (stage == 3){ stage++; }
	if (stage == 5){ can_execute = false; return; }
}

void Phase_Detective::execute(QList<Player*> players_){
	switch (stage) {
		case 1:
			phase_1(players_);
			break;
		case 2:
			phase_2(players_);
			break;
		case 3:
			break;
		case 4:
			phase_4(players_);
			break;
		default: break;
	}
}

void Phase_Detective::phase_1(QList<Player*> players_){
	narrator_speech = "Просыпается детектив...";
	log_text = "";

	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->role->is_detective() && players_[i]->is_alive()){
			players_[i]->set_conscious_awake();
			players_[i]->set_conscious_awake_string();
		}
}

void Phase_Detective::phase_2(QList<Player*> players_){
	narrator_speech = "Детектив внимательно рассматривает дела горожан и делает выбор...";

	for (int i = 0; i < players_.count(); i++)
			if (players_[i]->role->is_detective() && players_[i]->is_alive())
				choices << new Voting(players_[i]->role->night_choice(players_, i), players_[i], 1);

	for (int i = 0; i < choices.count(); i++)
		choices[i]->voters[0]->set_choice_string(choices[i]->elected);

	log_text = "Детектив (" + choices[0]->voters[0]->get_name() + ")" + " выбрал " + choices[0]->elected->get_name() + "\n";
}

void Phase_Detective::phase_3(QList<Player*> players_){
	// nothing to do, coz we have only one courtesan in game

}

void Phase_Detective::phase_4(QList<Player*> players_){
	narrator_speech = "Детектив навестил выбранного горожанина и, вернувшись, засыпает...";
	log_text = "";

	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->role->is_detective() && players_[i]->is_alive()){
			players_[i]->set_conscious_sleep();
			players_[i]->set_conscious_sleep_string();
		}
	choices.clear();
}

