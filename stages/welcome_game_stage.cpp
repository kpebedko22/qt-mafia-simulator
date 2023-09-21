#include "welcome_game_stage.h"
#include <player.h>

WelcomeGameStage::WelcomeGameStage() = default;

void WelcomeGameStage::run(QList<Player *> players) {
    this->narratorSpeech = "Приветствую в игре Мафия. "
                           "Сегодня мы собрались в дружной компании, "
                           "у каждого своя роль. Правила игры знакомы каждому. "
                           "Итак, наступает ночь... Все засыпают...";
    this->logText = "Наступила ночь\n";

    for (int i = 0; i < players.count(); i++) {
        if (players[i]->is_alive()) {
            players[i]->set_conscious_sleep();
            players[i]->set_conscious_sleep_string();
        }
    }

    this->isRequired = false;
}

bool WelcomeGameStage::isExecutable(QList<Player *> players) {
    return true;
}
