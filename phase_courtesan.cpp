#include "phase_courtesan.h"
#include "role.h"

Phase_Courtesan::Phase_Courtesan() {
    stage = 0;
    choices.clear();
}

Phase_Courtesan::~Phase_Courtesan() {}

Phase::Type Phase_Courtesan::get_type() { return COURTESAN_PHASE; }

void Phase_Courtesan::update_can_execute(QList<Player *> players_) {
    int num_courtesan = 0;
    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::COURTESAN) && players_[i]->is_alive()) num_courtesan++;

    if (num_courtesan == 0) {
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

void Phase_Courtesan::execute(QList<Player *> players_) {
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

void Phase_Courtesan::phase_1(QList<Player *> players_) {
    narrator_speech = "Ночь - время плотских утех и на свою работу "
                      "просыпается она... или он))";
    log_text = "";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::COURTESAN) && players_[i]->is_alive()) {
            players_[i]->set_conscious_awake();
            players_[i]->set_conscious_awake_string();
        }
}

void Phase_Courtesan::phase_2(QList<Player *> players_) {
    narrator_speech = "Едет к клиенту...";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::COURTESAN) && players_[i]->is_alive())
            choices << new Voting(players_[i]->role->nightChoice(players_[i], players_), players_[i], 1);

    for (int i = 0; i < choices.count(); i++)
        choices[i]->voters[0]->set_choice_string(choices[i]->elected);

    log_text =
            "Куртизанка (" + choices[0]->voters[0]->get_name() + ")" + " выбрала " + choices[0]->elected->get_name() +
            "\n";
}

void Phase_Courtesan::phase_3(QList<Player *> players_) {
    // nothing to do, coz we have only one courtesan in game

}

void Phase_Courtesan::phase_4(QList<Player *> players_) {
    narrator_speech = "Клиент прекрасно провел время в компании нашей куртизанки, "
                      "которая уже вернулась к себе и легла спать...";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::COURTESAN) && players_[i]->is_alive()) {
            players_[i]->set_conscious_sleep();
            players_[i]->set_conscious_sleep_string();
        }

    log_text = "";
    choices.clear();
}

