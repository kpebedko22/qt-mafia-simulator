#include "phase_borderline.h"

#include "role.h"
#include <QRandomGenerator>

Phase_Borderline::Phase_Borderline(){
	stage = 0;
}
Phase_Borderline::~Phase_Borderline(){}

Phase::Type Phase_Borderline::get_type(){ return BORDERLINE_PHASE; }

void Phase_Borderline::update_can_execute(QList<Player*> players_){
	int without_role = 0;
	int num_mafia = 0;
	int num_civilians = 0;

	for (int i = 0; i < players_.count(); i++)
		if (! players_[i]->role) without_role++; else{
			if (players_[i]->role->is(Role::Type::MAFIA) && players_[i]->is_alive()) num_mafia++;
			if (!players_[i]->role->is(Role::Type::MAFIA) && players_[i]->is_alive()) num_civilians++;
		}

	if (without_role != 0){ stage++; can_execute = true; return; }
	if (stage == 1){ stage++; can_execute = true; return; }

	bool mafia_win = false;
	bool civilians_win = false;

	if (num_mafia >= num_civilians) mafia_win = true;
	if (num_mafia == 0) civilians_win = true;

	if (mafia_win){ stage = 3; can_execute = true; return; }
	if (civilians_win){ stage = 4; can_execute = true; return; }

	can_execute = false;
}

void Phase_Borderline::execute(QList<Player*> players_){
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

void Phase_Borderline::phase_1(QList<Player*> players_){
	narrator_speech = "*ведущий перемешивает карты*\n*карты раздаются игрокам*\n*игра начинается*";
	log_text = "Раздача карт\n";

	int num_players = players_.count();
	int num_mafia = 0;
	int num_civilians = 0;
	int num_detectives = 1;
	int num_doctors = 1;
	int num_courtesans = 1;

	// кол-во мафии = 1/3 от всех игроков
	num_mafia = num_players / 3;
	if (num_mafia == 1) num_courtesans = 0;
	num_civilians = num_players - num_mafia - num_doctors - num_detectives - num_courtesans;

	QList<Player*> list = players_;

	for (int i = 0; i < num_mafia; i++){
		int rnd = QRandomGenerator::global()->bounded(0, list.count());
		list[rnd]->set_role_mafia();
		list.removeAt(rnd);
	}
	for (int i = 0; i < num_detectives; i++){
		int rnd = QRandomGenerator::global()->bounded(0, list.count());
		list[rnd]->set_role_detective();
		list.removeAt(rnd);
	}
	for (int i = 0; i < num_doctors; i++){
		int rnd = QRandomGenerator::global()->bounded(0, list.count());
		list[rnd]->set_role_doctor();
		list.removeAt(rnd);
	}
	for (int i = 0; i < num_courtesans; i++){
		int rnd = QRandomGenerator::global()->bounded(0, list.count());
		list[rnd]->set_role_courtesan();
		list.removeAt(rnd);
	}
	for (int i = 0; i < num_civilians; i++){
		int rnd = QRandomGenerator::global()->bounded(0, list.count());
		list[rnd]->set_role_civilian();
		list.removeAt(rnd);
	}

	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->is_alive()) players_[i]->set_greeting_phrase();
}

void Phase_Borderline::phase_2(QList<Player*> players_){
	narrator_speech = "Приветствую в игре Мафия. "
					  "Сегодня мы собрались в дружной компании, "
					  "у каждого своя роль. Правила игры знакомы каждому. "
					  "Итак, наступает ночь... Все засыпают...";
	log_text = "Наступила ночь\n";

	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->is_alive()){
			players_[i]->set_conscious_sleep();
			players_[i]->set_conscious_sleep_string();
		}
}

void Phase_Borderline::phase_3(QList<Player*> players_){
	narrator_speech = "Поздравляем мафию с победой, она смогла расправиться с мирными жителями и установить свои правила в этом городе!";
	log_text = "";

	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->is_alive()){
			if (players_[i]->role->is(Role::Type::MAFIA))
				players_[i]->set_emotion_happy_string();
			else
				players_[i]->set_emotion_sad_string();
		}
}

void Phase_Borderline::phase_4(QList<Player*> players_){
	narrator_speech = "Поздравляем мирных жителей города N с победой над злобной мафией!";
	log_text = "";

	for (int i = 0; i < players_.count(); i++)
		if (players_[i]->is_alive() && !players_[i]->role->is(Role::Type::MAFIA))
			players_[i]->set_emotion_happy_string();
}

