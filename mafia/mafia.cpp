#include "mafia.h"
#include "player.h"
#include <QRandomGenerator>

Mafia::Mafia(){}
Mafia::~Mafia(){}

Role::Type Mafia::get_type(){
	return MAFIA;
}

Player* Mafia::day_choice(QList<Player*> list_, int index_){
	int rnd = QRandomGenerator::global()->bounded(0, 100);

	if ( (((COEF_INT - list_[index_]->get_intuition()) + (COEF_INT - list_[index_]->get_attentiveness())) * 5) <= rnd){
		// если прокнула интуиция и внимательность
		// выдать детектива, если он живой
		for (int i = 0; i < list_.count(); i++)
			if (list_[i]->role->is_detective() && list_[i]->is_alive()) return list_[i];
		// если детектив мертв, ищем доктора
		for (int i = 0; i < list_.count(); i++)
			if (list_[i]->role->is_doctor() && list_[i]->is_alive()) return list_[i];
		// если доктор мертв, ищем куртизанку
		for (int i = 0; i < list_.count(); i++)
			if (list_[i]->role->is_courtesan() && list_[i]->is_alive()) return list_[i];
		// если никого нет, то интуиция нахер не нужна и просто выбираем самого неугодного мирного
	}

	int min_sympathy = 101;
	int index_to_return = -1;
	for (int i = 0; i < list_[index_]->sympathy.count(); i++)
		if (min_sympathy > list_[index_]->sympathy[i]->points
				&& list_[index_]->sympathy[i]->cur_player->is_alive()
				&& !list_[index_]->sympathy[i]->cur_player->role->is_mafia()){
			min_sympathy = list_[index_]->sympathy[i]->points;
			index_to_return = i;
		}
	return list_[index_]->sympathy[index_to_return]->cur_player;
}

Player* Mafia::night_choice(QList<Player*> list_, int index_){
	int rnd = QRandomGenerator::global()->bounded(0, 100);

	if ( (((COEF_INT - list_[index_]->get_intuition()) + (COEF_INT - list_[index_]->get_attentiveness())) * 5) <= rnd){
		// если прокнула интуиция и внимательность
		// выдать детектива, если он живой
		for (int i = 0; i < list_.count(); i++)
			if (list_[i]->role->is_detective() && list_[i]->is_alive()) return list_[i];
		// если детектив мертв, ищем доктора
		for (int i = 0; i < list_.count(); i++)
			if (list_[i]->role->is_doctor() && list_[i]->is_alive()) return list_[i];
		// если доктор мертв, ищем куртизанку
		for (int i = 0; i < list_.count(); i++)
			if (list_[i]->role->is_courtesan() && list_[i]->is_alive()) return list_[i];
		// если никого нет, то интуиция нахер не нужна и просто выбираем самого неугодного мирного
	}

	int min_sympathy = 101;
	int index_to_return = -1;
	for (int i = 0; i < list_[index_]->sympathy.count(); i++)
		if (min_sympathy > list_[index_]->sympathy[i]->points
				&& list_[index_]->sympathy[i]->cur_player->is_alive()
				&& !list_[index_]->sympathy[i]->cur_player->role->is_mafia()){
			min_sympathy = list_[index_]->sympathy[i]->points;
			index_to_return = i;
		}
	return list_[index_]->sympathy[index_to_return]->cur_player;
}
