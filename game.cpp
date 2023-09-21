#include "game.h"
#include "role.h"
#include "phase_courtesan.h"
#include "phase_borderline.h"
#include "phase_mafia.h"
#include "phase_doctor.h"
#include "phase_detective.h"
#include "phase_day.h"
#include <QRandomGenerator>
#include "stages/role_assignment_stage.h"
#include "stages/welcome_game_stage.h"
#include "stages/civilian_win_stage.h"
#include "stages/mafia_win_stage.h"
#include "stages/courtesans/courtesan_awake_stage.h"

Game::Game() {}

Game::~Game() = default;

Game::Game(QList<Player_info> players_info_) {
    num_players = players_info_.count();
    num_mafia = 0;
    num_civilians = 0;
    num_detectives = 0;
    num_doctors = 0;
    num_courtesans = 0;
    mafia_win = 0;
    civilians_win = 0;
    narrator_speech = "";
    log_text = "";
    game_over = false;
    fill_stages();
    generate_players(players_info_);
}

void Game::fill_stages() {
    this->stagesList << new RoleAssignmentStage();
    this->stagesList << new WelcomeGameStage();
    this->stagesList << new CourtesanAwakeStage();

//    stages << new Phase_Borderline();
//    stages << new Phase_Courtesan();
//    stages << new Phase_Mafia();
//    stages << new Phase_Doctor();
//    stages << new Phase_Detective();
//    stages << new Phase_Day();
}

void Game::generate_players(QList<Player_info> players_info) {
    // создаем игроков с заданными характеристиками
    for (int i = 0; i < num_players; i++) {
        players << new Player(players_info[i]);
    }
    // список игроков готов
    // сделаем для каждого игрока его собственный список симпатии
    for (int i = 0; i < players.count(); i++) {
        players[i]->make_list_of_sympathy(players);
    }
}

QString Game::get_narrator_speech() { return narrator_speech; }

QString Game::get_log_text() { return log_text; }

void Game::step() {

    // берем первый элемент из списка - old
//    Phase *current_stage = stages.takeFirst();
    // new
    if (!this->stagesList.count()) {
        return;
    }
    Stage *currentStage = this->stagesList.takeFirst();

    // обновляем can_execute
//    current_stage->update_can_execute(players);

    // пока мы не можем исполнить данный элемент, перебираем по очереди
//    while (!current_stage->get_can_execute()) {
//        current_stage->new_round();
//        stages.append(current_stage);
//        current_stage = stages.takeFirst();
//        current_stage->update_can_execute(players);
//    }
    // new
    while (!currentStage->isExecutable(this->players)) {

        this->stagesList.append(currentStage);

        currentStage = stagesList.takeFirst();
    }

    // now skip in new
//    if (current_stage->is_day_phase() && current_stage->get_count_choices() == 0) {
//        current_stage->set_choices(list_of_choices);
//        list_of_choices.clear();
//    }

    // исполняем объект, получаем данные от него
//    current_stage->execute(players);
    currentStage->run(players);

    if (currentStage->getIsRequired()) {
        this->stagesList.append(currentStage);
    }

//    narrator_speech = current_stage->get_narrator_speech();
//    log_text = current_stage->get_log_text();

    this->narrator_speech = currentStage->getNarratorSpeech();
    this->log_text = currentStage->getLogText();

    // если в current_stage был сделан выбор, например, куртизанки, то мы сохраняем его в наш список
//    if (current_stage->get_count_choices() == 1) {
//        list_of_choices.append(current_stage->get_choice());
//    }

    // обновляем кол-во живых
    this->update_numbers();

    // возвращаем объект в начало списка
//    stages.prepend(current_stage);
    // new
//    this->stagesList.prepend(currentStage);
}

void Game::update_numbers() {
    num_courtesans = num_mafia = num_doctors = num_detectives = num_civilians = 0;

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->is_alive()) {
            if (players[i]->role->is(Role::Type::COURTESAN)) {
                num_courtesans++;
            }
            if (players[i]->role->is(Role::Type::MAFIA)) {
                num_mafia++;
            }
            if (players[i]->role->is(Role::Type::DOCTOR)) {
                num_doctors++;
            }
            if (players[i]->role->is(Role::Type::DETECTIVE)) {
                num_detectives++;
            }
            if (players[i]->role->is(Role::Type::CIVILIAN)) {
                num_civilians++;
            }
        }
    }


    if (num_mafia >= num_civilians + num_courtesans + num_doctors + num_detectives) {
        this->stagesList.clear();
        this->stagesList << new MafiaWinStage();
        game_over = true;
        return;
    }

    if (num_mafia == 0) {
        this->stagesList.clear();
        this->stagesList << new CivilianWinStage();
        game_over = true;
        return;
    }
}

void Game::next_round() {

//    qDeleteAll(stages);
//    stages.clear();

    qDeleteAll(this->stagesList);
    this->stagesList.clear();

    if (num_mafia == 0) {
        civilians_win++;
    }

    if (num_mafia >= num_civilians + num_courtesans + num_doctors + num_detectives) {
        mafia_win++;
    }


    for (int i = 0; i < players.count(); i++) {
        players[i]->set_conscious_awake();
        players[i]->set_conscious_awake_string();
        players[i]->set_alive();
        players[i]->set_counters_null();
        players[i]->role = nullptr;
    }

    fill_stages();
    game_over = false;

    narrator_speech = "";
    log_text = "";
}

int Game::get_num_players() { return num_players; }

int Game::get_num_mafia() { return num_mafia; }

int Game::get_num_civilians() { return num_civilians; }

int Game::get_num_detectives() { return num_detectives; }

int Game::get_num_doctors() { return num_doctors; }

int Game::get_num_courtesans() { return num_courtesans; }

bool Game::is_game_over() { return game_over; }

int Game::get_mafia_win() { return mafia_win; }

int Game::get_civilians_win() { return civilians_win; }
