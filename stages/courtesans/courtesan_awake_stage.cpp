#include "courtesan_awake_stage.h"
#include <player.h>
#include <role.h>

CourtesanAwakeStage::CourtesanAwakeStage() = default;

void CourtesanAwakeStage::run(QList<Player *> players) {
    this->narratorSpeech = "Ночь - время плотских утех и на свою работу "
                           "просыпается она... или он))";
    this->logText = "Шлюха просыпается";

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->role->is(Role::Type::COURTESAN) && players[i]->is_alive()) {
            players[i]->set_conscious_awake();
            players[i]->set_conscious_awake_string();
        }
    }
}

bool CourtesanAwakeStage::isExecutable(QList<Player *> players) {
    int numCourtesans = 0;

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->role && players[i]->role->is(Role::Type::COURTESAN) && players[i]->is_alive()) {
            numCourtesans++;
        }
    }

    this->isRequired = numCourtesans != 0;

    return this->isRequired;
}