#include "phase_doctor.h"
#include "role.h"

Phase_Doctor::Phase_Doctor() {
    stage = 0;
    choices.clear();
}

Phase_Doctor::~Phase_Doctor() {}

Phase::Type Phase_Doctor::get_type() { return COURTESAN_PHASE; }

void Phase_Doctor::update_can_execute(QList<Player *> players_) {
    int num_doctors = 0;
    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::DOCTOR) && players_[i]->is_alive()) num_doctors++;

    if (num_doctors == 0) {
        can_execute = false;
        return;
    }
    if (stage <= 4) {
        can_execute = true;
        stage++;
    }
    if (stage == 3) { stage++; }
    if (stage == 5) {
        can_execute = false;
        return;
    }
}

void Phase_Doctor::execute(QList<Player *> players_) {
    switch (stage) {
        case 1:
            phase_1(players_);
            break;
        case 2:
            phase_2(players_);
            break;
        case 3:
            break;
        case 4:
            phase_4(players_);
            break;
        default:
            break;
    }
}

void Phase_Doctor::phase_1(QList<Player *> players_) {
    narrator_speech = "Просыпается доктор и выходит на ночную смену...";
    log_text = "";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::DOCTOR) && players_[i]->is_alive()) {
            players_[i]->set_conscious_awake();
            players_[i]->set_conscious_awake_string();
        }
}

void Phase_Doctor::phase_2(QList<Player *> players_) {
    narrator_speech = "Поступает вызов и доктор мчится к игроку?...";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::DOCTOR) && players_[i]->is_alive())
            choices << new Voting(players_[i]->role->nightChoice(players_[i], players_), players_[i], 1);

    for (int i = 0; i < choices.count(); i++)
        choices[i]->voters[0]->set_choice_string(choices[i]->elected);

    log_text =
            "Доктор (" + choices[0]->voters[0]->get_name() + ")" + " выбрал " + choices[0]->elected->get_name() + "\n";
}

void Phase_Doctor::phase_3(QList<Player *> players_) {
    // nothing to do, coz we have only one doctor in game

}

void Phase_Doctor::phase_4(QList<Player *> players_) {
    narrator_speech = "Доктор съездил к пациенту. Доктор засыпает...";
    log_text = "";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::DOCTOR) && players_[i]->is_alive()) {
            players_[i]->set_conscious_sleep();
            players_[i]->set_conscious_sleep_string();
        }
    choices.clear();
}

