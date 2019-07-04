#include "civilian.h"
#include "player.h"
#include <QRandomGenerator>

Civilian::Civilian(){}

Civilian::~Civilian(){}

Role::Type Civilian::get_type(){
	return CIVILIAN;
}

Player* Civilian::day_choice(QList<Player*> list_, int index_){
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

Player* Civilian::night_choice(QList<Player*> list_, int index_){
	//мирный никого не выбирает ночью
	return nullptr;
}
