#include "phase_day.h"
#include "role.h"

Phase_Day::Phase_Day(){
	stage = 0;
	choices.clear();
}
Phase_Day::~Phase_Day(){}

Phase::Type Phase_Day::get_type(){ return DAY_PHASE; }

void Phase_Day::update_can_execute(QList<Player*> players_){
	int num_mafia = 0;
	int num_civilians = 0;

	for (int i = 0; i < players_.count(); i++){
		if (players_[i]->role->is_mafia() && players_[i]->is_alive()) num_mafia++;
		if (!players_[i]->role->is_mafia() && players_[i]->is_alive()) num_civilians++;
	}

	bool mafia_win = false;
	bool civilians_win = false;

	if (num_mafia >= num_civilians) mafia_win = true;
	if (num_mafia == 0) civilians_win = true;

	if (mafia_win){ stage = -1; can_execute = false; return; }
	if (civilians_win){ stage = -1; can_execute = false; return; }

	if (stage <= 4){ stage++; can_execute = true; }
	if (stage == 5){ can_execute = false; return; }
}

void Phase_Day::execute(QList<Player*> players_){
	switch (stage) {
		case 1:
			phase_1(players_);
			break;
		case 2:
			phase_2(players_);
			break;
		case 3:
			phase_3(players_);
			break;
		case 4:
			phase_4(players_);
			break;
		default: break;
	}
}


void Phase_Day::phase_1(QList<Player*> players_){
	Voting* courtesan_choice = nullptr;
	Voting* mafia_choice = nullptr;
	Voting* doctor_choice = nullptr;
	Voting* detective_choice = nullptr;

	int index_courtesan = 0;
	int index_mafia = 1;
	int index_doctor = 2;
	int index_detective = 3;

	int num_courtesans = 0;
	int num_mafia = 0;
	int num_doctors = 0;
	int num_detectives = 0;

	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->is_alive()){
			if (players_[i]->role->is_courtesan()) num_courtesans++;
			if (players_[i]->role->is_mafia()) num_mafia++;
			if (players_[i]->role->is_doctor()) num_doctors++;
			if (players_[i]->role->is_detective()) num_detectives++;
		}

	if (num_courtesans == 0){ index_courtesan = -1; index_mafia--; index_doctor--; index_detective--; }
	if (num_doctors == 0){ index_doctor = -1; index_detective--; }
	if (num_detectives == 0){ index_detective = -1; }


	log_text = "Утром имеем:\n";

	if (index_courtesan != -1){ courtesan_choice = choices[index_courtesan]; log_text += "Куртизанка " + courtesan_choice->voters[0]->get_name() +": " + courtesan_choice->elected->get_name() + "\n"; }
	if (index_mafia != -1){ mafia_choice = choices[index_mafia]; log_text += "Мафия " + mafia_choice->voters[0]->get_name() +": " + mafia_choice->elected->get_name() + "\n";}
	if (index_doctor != -1) {doctor_choice = choices[index_doctor]; log_text += "Доктор " + doctor_choice->voters[0]->get_name() +": " + doctor_choice->elected->get_name() + "\n";}
	if (index_detective != -1){ detective_choice = choices[index_detective]; log_text += "Детектив " + detective_choice->voters[0]->get_name() +": " + detective_choice->elected->get_name() + "\n";}


	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->is_alive()){
			players_[i]->set_conscious_awake();
			players_[i]->set_conscious_awake_string();
		}

	bool mafia_choice_will_die = true;
	bool detective_choice_will_die = false;
	bool courtesan_choice_will_die = false;

	if (num_doctors > 0) if (mafia_choice->elected == doctor_choice->elected) mafia_choice_will_die = false;
	if (num_courtesans > 0) if (mafia_choice->elected == courtesan_choice->elected) mafia_choice_will_die = false;
	if (num_courtesans > 0) if (courtesan_choice->elected->role->is_mafia() && num_mafia == 1) mafia_choice_will_die = false;

	if (num_detectives > 0){
		if (detective_choice->elected->role->is_mafia()) detective_choice_will_die = true;
		if (num_doctors > 0) if (detective_choice->elected == doctor_choice->elected) detective_choice_will_die = false;
		if (num_courtesans > 0) if (detective_choice->elected == courtesan_choice->elected || courtesan_choice->elected->role->is_detective()) detective_choice_will_die = false;
	}

	if (num_courtesans > 0) if (courtesan_choice->elected->get_counter_courtesan() == 2) courtesan_choice_will_die = true;

	QString text = "Наступает день и все жители города просыпаются, за исключением... ";

	if (mafia_choice_will_die){
		text += mafia_choice->elected->get_name() + "- его таки посетила мафия, светлая память ему\n";
		mafia_choice->elected->set_alive_dead();
		mafia_choice->elected->set_alive_dead_string();
		log_text += "Убит мафией " + mafia_choice->elected->get_name() + "\n";
	}

	if (detective_choice_will_die){
		text += detective_choice->elected->get_name() + " - детектив вышел на мафию и разобрался с ней";
		detective_choice->elected->set_alive_dead();
		detective_choice->elected->set_alive_dead_string();
		log_text += "Убит детективом " + detective_choice->elected->get_name() + "\n";
	}

	if (courtesan_choice_will_die){
		text += courtesan_choice->elected->get_name() + " - куртизанка затр..., в общем, всем такой смерти";
		courtesan_choice->elected->set_alive_dead();
		courtesan_choice->elected->set_alive_dead_string();
		log_text += "Убит куртизанкой " + courtesan_choice->elected->get_name() + "\n";
	}

	if (!mafia_choice_will_die && !detective_choice_will_die && !courtesan_choice_will_die){
		log_text += "Никто не умер ночью";
		text += "все, в смысле все выжили этой ночью, никто не пострадал";
	}

	narrator_speech = text;
}

void Phase_Day::phase_2(QList<Player*> players_){
	narrator_speech = "Итак, голосование. Каждый предлагает, кого мы вздёрнем на вис... эээ, в смысле, казним... да, точно, казним";
	log_text = "";

	choices.clear();

	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->is_alive())
			choices << new Voting(players_[i]->role->day_choice(players_, i), players_[i], 1);

	for (int i = 0; i < choices.count(); i++){
		choices[i]->voters[0]->set_choice_string(choices[i]->elected);
		log_text += choices[i]->voters[0]->get_name() + " против " + choices[i]->elected->get_name() + "\n";
	}
}

void Phase_Day::phase_3(QList<Player*> players_){
	QString text = "Немного подискутировав, принимается решение, казнить ";
	log_text = "Объединяем голоса:\n";
	// производим объединение голосов на группы, в day_choice[0] будет лежать с макс.кол-вом голосов
	choices = join_choices(choices);

	for (int i = 0; i < choices.count(); i++)
		for (int j = 0; j < choices[i]->voters.count(); j++){
			choices[i]->voters[j]->set_choice_string(choices[i]->elected);
			log_text += choices[i]->voters[j]->get_name() + " против " + choices[i]->elected->get_name() + "\n";
		}

	for (int i = 0; i < choices.count(); i++){
		// 1. выбранному уменьшить симпатию к тем, кто выбрал
		for (int j = 0; j < choices[i]->voters.count(); j++)
			choices[i]->elected->decrease_sympathy_to(choices[i]->voters[j]);
		// 2. игрокам из одной группы увеличить симпатию к каждому
		for (int j = 0; j < choices[i]->voters.count(); j++)
			for (int k = 0; k < choices[i]->voters.count(); k++)
				if (j != k) choices[i]->voters[j]->increase_sympathy_to(choices[i]->voters[k]);
	}

	text += choices[0]->elected->get_name() + "т.к. за него проголосовало " + QString::number(choices[0]->votes) + " игроков. Прощай.";
	text += "Кстати, " + choices[0]->elected->get_name();

	if (choices[0]->elected->get_sex() == 0) text += " был *барабанная дробь*"; else text += " была *барабанная дробь*";
	if (choices[0]->elected->role->is_mafia()) {text += " МАФИЕЙ"; }
	if (choices[0]->elected->role->is_civilian()) {text += " МИРНЫМ"; }
	if (choices[0]->elected->role->is_courtesan()) {text += " КУРТИЗАНКОЙ"; }
	if (choices[0]->elected->role->is_doctor()) {text += " ДОКТОРОМ"; }
	if (choices[0]->elected->role->is_detective()) {text += " ДЕТЕКТИВОМ"; }

	choices[0]->elected->set_alive_dead();
	choices[0]->elected->set_alive_dead_string();

	log_text += "Казнили: " + choices[0]->elected->get_name() + "\n";
	narrator_speech = text;
}

void Phase_Day::phase_4(QList<Player*> players_){
	narrator_speech = "Наступает очередная беспокойная ночь над городом N, и все ложаться спать...";
	log_text = "Ночь";
	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->is_alive()){
			players_[i]->set_conscious_sleep();
			players_[i]->set_conscious_sleep_string();
		}

	choices.clear();
}

