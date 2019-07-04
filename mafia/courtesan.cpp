#include "courtesan.h"
#include "player.h"
#include <QRandomGenerator>

Courtesan::Courtesan(){}

Courtesan::~Courtesan(){}

Role::Type Courtesan::get_type(){
	return COURTESAN;
}

Player* Courtesan::day_choice(QList<Player*> list_, int index_){
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

Player* Courtesan::night_choice(QList<Player*> list_, int index_){
	int rnd = QRandomGenerator::global()->bounded(0, list_.count());

	// у куртизанки нет определенной цели, как, например, у детектива
	// поэтому для разнообразия можно сделать два варианта выбора
	// 1. по симпатии выбирать максимального
	// 2. рандом

	if (rnd % 2 == 0){
		// 1. надо в списке симпатий для куртизанки найти с максимальным
		// числом и запомнить индекс, а потом вернуть указатель на этого игрока
		// главное - выбранный игрок должен быть жив, иначе получается некрофилия
		int max_sympathy = -1;
		int index_to_return = -1;
		for (int i = 0; i < list_[index_]->sympathy.count(); i++)
			if (max_sympathy < list_[index_]->sympathy[i]->points && list_[index_]->sympathy[i]->cur_player->is_alive()){
				max_sympathy = list_[index_]->sympathy[i]->points;
				index_to_return = i;
			}
		list_[index_]->sympathy[index_to_return]->cur_player->increase_counter_courtesan();

		return list_[index_]->sympathy[index_to_return]->cur_player;
	}
	else{
		// 2. создадим доп список с живыми, и без куртизанки
		// и в нем выберем рандомного

		QList<Player*> tmp_list;

		for (int i = 0; i < list_.count(); i++)
			if (i != index_ && list_[i]->is_alive())
				tmp_list << list_[i];

		rnd = QRandomGenerator::global()->bounded(0, tmp_list.count());

		tmp_list[rnd]->increase_counter_courtesan();

		return tmp_list[rnd];
	}
}
