#include "courtesan_choice_stage.h"

CourtesanChoiceStage::CourtesanChoiceStage() = default;

void CourtesanChoiceStage::run(QList<Player *> players) {
    this->narratorSpeech = "Едет к клиенту...";

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->role->is(Role::Type::COURTESAN) && players[i]->is_alive()) {
            choices << new Voting(players[i]->role->nightChoice(players[i], players), players[i], 1);
        }
    }

    for (int i = 0; i < choices.count(); i++) {
        choices[i]->voters[0]->set_choice_string(choices[i]->elected);
    }

    this->logText = "Куртизанка (" +
                    choices[0]->voters[0]->get_name() +
                    ")" +
                    " выбрала " +
                    choices[0]->elected->get_name() +
                    "\n";
}

bool CourtesanChoiceStage::isExecutable(QList<Player *> players) {
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