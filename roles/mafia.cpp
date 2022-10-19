#include "mafia.h"
#include "player.h"
#include <QRandomGenerator>

Mafia::Mafia() {}

Mafia::~Mafia() {}

Role::Type Mafia::getType() {
    return Role::Type::MAFIA;
}

Player *Mafia::dayChoice(Player *player, QList<Player *> players) {
    int rnd = QRandomGenerator::global()->bounded(0, 100);

    if ((((COEF_INT - player->get_intuition()) + (COEF_INT - player->get_attentiveness())) * 5) <= rnd) {
        // если прокнула интуиция и внимательность
        // выдать детектива, если он живой
        for (int i = 0; i < players.count(); i++)
            if (players[i]->role->is(Role::Type::DETECTIVE) && players[i]->is_alive()) return players[i];
        // если детектив мертв, ищем доктора
        for (int i = 0; i < players.count(); i++)
            if (players[i]->role->is(Role::Type::DOCTOR) && players[i]->is_alive()) return players[i];
        // если доктор мертв, ищем куртизанку
        for (int i = 0; i < players.count(); i++)
            if (players[i]->role->is(Role::Type::COURTESAN) && players[i]->is_alive()) return players[i];
        // если никого нет, то интуиция нахер не нужна и просто выбираем самого неугодного мирного
    }

    int min_sympathy = 101;
    int index_to_return = -1;
    for (int i = 0; i < player->sympathy.count(); i++)
        if (min_sympathy > player->sympathy[i]->points
            && player->sympathy[i]->cur_player->is_alive()
            && !player->sympathy[i]->cur_player->role->is(Role::Type::MAFIA)) {
            min_sympathy = player->sympathy[i]->points;
            index_to_return = i;
        }
    return player->sympathy[index_to_return]->cur_player;
}

Player *Mafia::nightChoice(Player *player, QList<Player *> players) {
    int rnd = QRandomGenerator::global()->bounded(0, 100);

    if ((((COEF_INT - player->get_intuition()) + (COEF_INT - player->get_attentiveness())) * 5) <= rnd) {
        // если прокнула интуиция и внимательность
        // выдать детектива, если он живой
        for (int i = 0; i < players.count(); i++)
            if (players[i]->role->is(Role::Type::DETECTIVE) && players[i]->is_alive()) return players[i];
        // если детектив мертв, ищем доктора
        for (int i = 0; i < players.count(); i++)
            if (players[i]->role->is(Role::Type::DOCTOR) && players[i]->is_alive()) return players[i];
        // если доктор мертв, ищем куртизанку
        for (int i = 0; i < players.count(); i++)
            if (players[i]->role->is(Role::Type::COURTESAN) && players[i]->is_alive()) return players[i];
        // если никого нет, то интуиция нахер не нужна и просто выбираем самого неугодного мирного
    }

    int min_sympathy = 101;
    int index_to_return = -1;
    for (int i = 0; i < player->sympathy.count(); i++)
        if (min_sympathy > player->sympathy[i]->points
            && player->sympathy[i]->cur_player->is_alive()
            && !player->sympathy[i]->cur_player->role->is(Role::Type::MAFIA)) {
            min_sympathy = player->sympathy[i]->points;
            index_to_return = i;
        }
    return player->sympathy[index_to_return]->cur_player;
}
