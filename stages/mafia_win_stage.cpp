#include "mafia_win_stage.h"
#include <player.h>
#include <role.h>

MafiaWinStage::MafiaWinStage() = default;

void MafiaWinStage::run(QList<Player *> players) {
    this->narratorSpeech = "Поздравляем мафию с победой, она смогла расправиться с мирными жителями и установить свои правила в этом городе!";
    this->logText = "Победа мафии";

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->is_alive()) {
            if (players[i]->role->is(Role::Type::MAFIA)) {
                players[i]->set_emotion_happy_string();
            } else {
                players[i]->set_emotion_sad_string();
            }
        }
    }
}

bool MafiaWinStage::isExecutable(QList<Player *> players) {

    int numMafias = 0;
    int numCivilians = 0;

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->role && players[i]->is_alive()) {
            if (players[i]->role->is(Role::Type::MAFIA)) {
                numMafias++;
            } else {
                numCivilians++;
            }
        }
    }

    return numMafias >= numCivilians;
}
