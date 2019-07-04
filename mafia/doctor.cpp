#include "doctor.h"
#include "player.h"
#include <QRandomGenerator>

Doctor::Doctor(){}
Doctor::~Doctor() {}

Role::Type Doctor::get_type(){
	return DOCTOR;
}

Player* Doctor::day_choice(QList<Player*> list_, int index_){
	int rnd = QRandomGenerator::global()->bounded(0, 100);

	if ( (((COEF_INT - list_[index_]->get_intuition()) + (COEF_INT - list_[index_]->get_attentiveness())) * 5) <= rnd){
		// если прокнула интуиция и внимательность
		// выдать мафию, живую
		for (int i = 0; i < list_.count(); i++)
			if (list_[i]->role->is_mafia() && list_[i]->is_alive()) return list_[i];
	}

	int min_sympathy = 101;
	int index_to_return = -1;
	for (int i = 0; i < list_[index_]->sympathy.count(); i++)
		if (min_sympathy > list_[index_]->sympathy[i]->points
				&& list_[index_]->sympathy[i]->cur_player->is_alive()){
			min_sympathy = list_[index_]->sympathy[i]->points;
			index_to_return = i;
		}
	return list_[index_]->sympathy[index_to_return]->cur_player;
}


Player* Doctor::night_choice(QList<Player*> list_, int index_){
	int rnd = QRandomGenerator::global()->bounded(0, 100);

/*	if ( (((11 - list_[index_]->get_intuition()) + (11 - list_[index_]->get_attentiveness())) * 5) <= rnd){
		// если прокнула интуиция и внимательность
		// доктору надо вылечить жертву мафии - mafia_choice[0]->elected
		for (int i = 0; i < list_.count(); i++)
			if (list_[i] == mafia_choice[0].elected) return list_[i];
	}*/

	// если не прокнула интуиция, посмотрим на эгоизм врача
	// selfishness = 10, 13-10 * 10 = 30, 30 <= rnd.... 70%
	if (((COEF_INT - list_[index_]->get_selfishness()) * 10) <= rnd && list_[index_]->get_counter_doctor() < 2){
		list_[index_]->increase_counter_doctor();
		return list_[index_];
	}

	// выбираем самого симпатичного из живых для нашего доктора
	int max_sympathy = -1;
	int index_to_return = -1;
	for (int i = 0; i < list_[index_]->sympathy.count(); i++)
		if (max_sympathy < list_[index_]->sympathy[i]->points
				&& list_[index_]->sympathy[i]->cur_player->get_counter_doctor() < 2
				&& list_[index_]->sympathy[i]->cur_player->is_alive()){
			max_sympathy = list_[index_]->sympathy[i]->points;
			index_to_return = i;
		}

	list_[index_]->sympathy[index_to_return]->cur_player->increase_counter_doctor();
	return list_[index_]->sympathy[index_to_return]->cur_player;
}
