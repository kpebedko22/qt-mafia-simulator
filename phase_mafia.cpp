#include "phase_mafia.h"
#include "role.h"

Phase_Mafia::Phase_Mafia() {
    stage = 0;
    choices.clear();
}

Phase_Mafia::~Phase_Mafia() {}

Phase::Type Phase_Mafia::get_type() { return MAFIA_PHASE; }

void Phase_Mafia::update_can_execute(QList<Player *> players_) {
    int num_mafia = 0;
    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::MAFIA) && players_[i]->is_alive()) num_mafia++;

    if (num_mafia == 0) {
        can_execute = false;
        return;
    }
    if (stage <= 4) {
        can_execute = true;
        stage++;
    }
    if (stage == 3 && num_mafia == 1) { stage++; }
    if (stage == 5) {
        can_execute = false;
        return;
    }
}

void Phase_Mafia::execute(QList<Player *> players_) {
    switch (stage) {
        case 1:
            phase_1(players_);
            break;
        case 2:
            phase_2(players_);
            break;
        case 3:
            phase_3(players_);
            break;
        case 4:
            phase_4(players_);
            break;
        default:
            break;
    }
}

void Phase_Mafia::phase_1(QList<Player *> players_) {
    narrator_speech = "Просыпается мафия...";
    log_text = "";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::MAFIA) && players_[i]->is_alive()) {
            players_[i]->set_conscious_awake();
            players_[i]->set_conscious_awake_string();
        }
}

void Phase_Mafia::phase_2(QList<Player *> players_) {
    narrator_speech = "Мафия решает, кто не проснется утром...";
    log_text = "";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::MAFIA) && players_[i]->is_alive())
            choices << new Voting(players_[i]->role->nightChoice(players_[i], players_), players_[i], 1);

    for (int i = 0; i < choices.count(); i++) {
        choices[i]->voters[0]->set_choice_string(choices[i]->elected);
        log_text +=
                "Мафия (" + choices[i]->voters[0]->get_name() + ")" + " выбрала " + choices[i]->elected->get_name() +
                "\n";
    }
}

void Phase_Mafia::phase_3(QList<Player *> players_) {
    narrator_speech = "После недолгих дискуссий Мафия, может быть не единогласно, но делается выбор...";

    // если одна мафия, следовательно нет смысла делать объедение голосов
    // в таком случае в mafia_choice только один объект
    // иначе, делаем объединение
    choices = join_choices(choices);

    for (int i = 0; i < choices.count(); i++)
        for (int j = 0; j < choices[i]->voters.count(); j++)
            choices[i]->voters[j]->set_choice_string(choices[i]->elected);

    Voting *tmp = choices[0];

    log_text = "Окончательный выбор мафии: " + choices[0]->elected->get_name() + "\n";;

    choices.clear();
    choices.prepend(tmp);
}

void Phase_Mafia::phase_4(QList<Player *> players_) {
    narrator_speech = "Мафия сделала свой выбор и засыпает...";
    log_text = "";

    for (int i = 0; i < players_.count(); i++)
        if (players_[i]->role->is(Role::Type::MAFIA) && players_[i]->is_alive()) {
            players_[i]->set_conscious_sleep();
            players_[i]->set_conscious_sleep_string();
        }
    choices.clear();
}

