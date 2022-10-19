#include "courtesan.h"
#include "player.h"
#include <QRandomGenerator>

Courtesan::Courtesan() {}

Courtesan::~Courtesan() {}

Role::Type Courtesan::getType() {
    return Role::Type::COURTESAN;
}

Player *Courtesan::dayChoice(Player *player, QList<Player *> players) {
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

Player *Courtesan::nightChoice(Player *player, QList<Player *> players) {
    int rnd = QRandomGenerator::global()->bounded(0, players.count());

    // у куртизанки нет определенной цели, как, например, у детектива
    // поэтому для разнообразия можно сделать два варианта выбора
    // 1. по симпатии выбирать максимального
    // 2. рандом

    if (rnd % 2 == 0) {
        // 1. надо в списке симпатий для куртизанки найти с максимальным
        // числом и запомнить индекс, а потом вернуть указатель на этого игрока
        // главное - выбранный игрок должен быть жив, иначе получается некрофилия
        int max_sympathy = -1;
        int index_to_return = -1;
        for (int i = 0; i < player->sympathy.count(); i++)
            if (max_sympathy < player->sympathy[i]->points && player->sympathy[i]->cur_player->is_alive()) {
                max_sympathy = player->sympathy[i]->points;
                index_to_return = i;
            }
        player->sympathy[index_to_return]->cur_player->increase_counter_courtesan();

        return player->sympathy[index_to_return]->cur_player;
    } else {
        // 2. создадим доп список с живыми, и без куртизанки
        // и в нем выберем рандомного

        QList < Player * > tmp_list;

        for (int i = 0; i < players.count(); i++)
            if (players[i] != player && players[i]->is_alive())
                tmp_list << players[i];

        rnd = QRandomGenerator::global()->bounded(0, tmp_list.count());

        tmp_list[rnd]->increase_counter_courtesan();

        return tmp_list[rnd];
    }
}
