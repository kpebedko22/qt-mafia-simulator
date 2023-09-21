#include "doctor.h"
#include "player.h"
#include <QRandomGenerator>

Doctor::Doctor() = default;

Doctor::~Doctor() = default;

Role::Type Doctor::getType() {
    return Role::Type::DOCTOR;
}

Player *Doctor::dayChoice(Player *player, QList<Player *> players) {
    int rnd = QRandomGenerator::global()->bounded(0, 100);

    if ((((COEF_INT - player->get_intuition()) + (COEF_INT - player->get_attentiveness())) * 5) <= rnd) {
        // если прокнула интуиция и внимательность
        // выдать мафию, живую
        for (int i = 0; i < players.count(); i++)
            if (players[i]->role->is(Role::Type::MAFIA) && players[i]->is_alive()) return players[i];
    }

    int min_sympathy = 101;
    int index_to_return = -1;
    for (int i = 0; i < player->sympathy.count(); i++)
        if (min_sympathy > player->sympathy[i]->points
            && player->sympathy[i]->cur_player->is_alive()) {
            min_sympathy = player->sympathy[i]->points;
            index_to_return = i;
        }
    return player->sympathy[index_to_return]->cur_player;
}


Player *Doctor::nightChoice(Player *player, QList<Player *> players) {
    int rnd = QRandomGenerator::global()->bounded(0, 100);

/*	if ( (((11 - player->get_intuition()) + (11 - player->get_attentiveness())) * 5) <= rnd){
		// если прокнула интуиция и внимательность
		// доктору надо вылечить жертву мафии - mafia_choice[0]->elected
		for (int i = 0; i < players.count(); i++)
			if (players[i] == mafia_choice[0].elected) return players[i];
	}*/

    // если не прокнула интуиция, посмотрим на эгоизм врача
    // selfishness = 10, 13-10 * 10 = 30, 30 <= rnd.... 70%
    if (((COEF_INT - player->get_selfishness()) * 10) <= rnd && player->get_counter_doctor() < 2) {
        player->increase_counter_doctor();
        return player;
    }

    // выбираем самого симпатичного из живых для нашего доктора
    int max_sympathy = -1;
    int index_to_return = -1;
    for (int i = 0; i < player->sympathy.count(); i++)
        if (max_sympathy < player->sympathy[i]->points
            && player->sympathy[i]->cur_player->get_counter_doctor() < 2
            && player->sympathy[i]->cur_player->is_alive()) {
            max_sympathy = player->sympathy[i]->points;
            index_to_return = i;
        }

    player->sympathy[index_to_return]->cur_player->increase_counter_doctor();
    return player->sympathy[index_to_return]->cur_player;
}
