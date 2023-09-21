#include "courtesan_asleep_stage.h"

CourtesanAsleepStage::CourtesanAsleepStage() = default;

void CourtesanAsleepStage::run(QList<Player *> players) {
    this->narratorSpeech = "Клиент прекрасно провел время в компании нашей куртизанки, "
                           "которая уже вернулась к себе и легла спать...";

    for (int i = 0; i < players.count(); i++)
        if (players[i]->role->is(Role::Type::COURTESAN) && players[i]->is_alive()) {
            players[i]->set_conscious_sleep();
            players[i]->set_conscious_sleep_string();
        }

    this->logText = "";
    choices.clear();
}

bool CourtesanAsleepStage::isExecutable(QList<Player *> players) {
//    int num_courtesan = 0;
//    for (int i = 0; i < players.count(); i++)
//        if (players[i]->role->is(Role::Type::COURTESAN) && players[i]->is_alive()) num_courtesan++;
//
//    if (num_courtesan == 0) {
//        can_execute = false;
//        return;
//    }
//    if (stage <= 4) {
//        can_execute = true;
//        stage++;
//    }
//    if (stage == 3) { stage++; }
//    if (stage == 5) {
//        can_execute = false;
//        return;
//    }

    return this->isRequired;
}