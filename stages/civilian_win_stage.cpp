#include "civilian_win_stage.h"
#include <player.h>
#include <role.h>

CivilianWinStage::CivilianWinStage() = default;

void CivilianWinStage::run(QList<Player *> players) {
    this->narratorSpeech =
            "Поздравляем мирных жителей города N с победой над злобной мафией!";
    this->logText = "Победа мирных жителей";

    for (int i = 0; i < players.count(); i++) {

        if (players[i]->is_alive() && !players[i]->role->is(Role::Type::MAFIA)) {
            players[i]->set_emotion_happy_string();
        }
    }
}

bool CivilianWinStage::isExecutable(QList<Player *> players) {
    int numMafias = 0;

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->role && players[i]->role->is(Role::Type::MAFIA) && players[i]->is_alive()) {
            numMafias++;
        }
    }

    return numMafias == 0;
}
