#include "civilian.h"
#include "player.h"
#include <QRandomGenerator>

Civilian::Civilian() {}

Civilian::~Civilian() {}

Role::Type Civilian::getType() {
    return Role::Type::CIVILIAN;
}

Player *Civilian::dayChoice(Player *player, QList<Player *> players) {
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

    int minSympathy = 101;
    int returnIndex = -1;
    for (int i = 0; i < player->sympathy.count(); i++)
        if (minSympathy > player->sympathy[i]->points &&
            player->sympathy[i]->cur_player->is_alive()) {

            minSympathy = player->sympathy[i]->points;
            returnIndex = i;
        }
    return player->sympathy[returnIndex]->cur_player;
}

Player *Civilian::nightChoice(Player *player, QList<Player *> players) {
    return nullptr;
}
