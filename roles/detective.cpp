#include "detective.h"
#include "player.h"
#include <QRandomGenerator>

Detective::Detective() {}

Detective::~Detective() {}

Role::Type Detective::getType() {
    return Role::Type::DETECTIVE;
}

Player *Detective::dayChoice(Player *player, QList<Player *> players) {
    int rnd = QRandomGenerator::global()->bounded(0, 100);

    if ((((COEF_INT - player->get_intuition()) + (COEF_INT - player->get_attentiveness())) * 5) <= rnd) {
        // если прокнула интуиция и внимательность
        // выдать мафию, живую
        for (int i = 0; i < players.count(); i++) {
            if (players[i]->role->is(Role::Type::MAFIA) && players[i]->is_alive()) {
                return players[i];
            }
        }
    }

    int min_sympathy = 101;
    int index_to_return = -1;
    for (int i = 0; i < player->sympathy.count(); i++) {
        if (min_sympathy > player->sympathy[i]->points &&
            player->sympathy[i]->cur_player->is_alive()) {
            min_sympathy = player->sympathy[i]->points;
            index_to_return = i;
        }
    }
    return player->sympathy[index_to_return]->cur_player;
}

Player *Detective::nightChoice(Player *player, QList<Player *> players) {
    int rnd = QRandomGenerator::global()->bounded(0, 100);

    if ((((COEF_INT - player->get_intuition()) + (COEF_INT - player->get_attentiveness())) * 5) <= rnd) {
        // если прокнула интуиция и внимательность
        // выдать мафию, живую
        for (int i = 0; i < players.count(); i++) {
            if (players[i]->role->is(Role::Type::MAFIA) && players[i]->is_alive()) {
                return players[i];
            }
        }
    }

    int min_sympathy = 101;
    int index_to_return = -1;
    for (int i = 0; i < player->sympathy.count(); i++) {
        if (min_sympathy > player->sympathy[i]->points &&
            player->sympathy[i]->cur_player->is_alive()) {
            min_sympathy = player->sympathy[i]->points;
            index_to_return = i;
        }
    }
    return player->sympathy[index_to_return]->cur_player;
}
