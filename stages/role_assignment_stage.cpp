#include "role_assignment_stage.h"

#include <player.h>
#include <QRandomGenerator>

RoleAssignmentStage::RoleAssignmentStage() = default;

void RoleAssignmentStage::run(QList<Player *> players) {

    this->narratorSpeech = "*ведущий перемешивает карты*\n*карты раздаются игрокам*\n*игра начинается*";
    this->logText = "Раздача карт\n";

    int numPlayers = players.count();
    int numMafias = numPlayers / 3;
    int numCivilians = 0;
    int numDetectives = 1;
    int numDoctors = 1;
    int numCourtesans = 1;

    if (numMafias == 1) {
        numCourtesans = 0;
    }

    numCivilians = numPlayers - numMafias - numDoctors - numDetectives - numCourtesans;

    QList < Player * > list = players;

    for (int i = 0; i < numMafias; i++) {
        int rnd = QRandomGenerator::global()->bounded(0, list.count());
        list[rnd]->set_role_mafia();
        list.removeAt(rnd);
    }
    for (int i = 0; i < numDetectives; i++) {
        int rnd = QRandomGenerator::global()->bounded(0, list.count());
        list[rnd]->set_role_detective();
        list.removeAt(rnd);
    }
    for (int i = 0; i < numDoctors; i++) {
        int rnd = QRandomGenerator::global()->bounded(0, list.count());
        list[rnd]->set_role_doctor();
        list.removeAt(rnd);
    }
    for (int i = 0; i < numCourtesans; i++) {
        int rnd = QRandomGenerator::global()->bounded(0, list.count());
        list[rnd]->set_role_courtesan();
        list.removeAt(rnd);
    }
    for (int i = 0; i < numCivilians; i++) {
        int rnd = QRandomGenerator::global()->bounded(0, list.count());
        list[rnd]->set_role_civilian();
        list.removeAt(rnd);
    }

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->is_alive()) {
            players[i]->set_greeting_phrase();
        }
    }

    this->isRequired = false;
}

bool RoleAssignmentStage::isExecutable(QList<Player *> players) {
    bool isWithoutRole = false;

    for (int i = 0; i < players.count(); i++) {
        if (!players[i]->role) {
            isWithoutRole = true;
            break;
        }
    }

    return isWithoutRole;
}
