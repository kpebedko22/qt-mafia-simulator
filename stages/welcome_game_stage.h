#ifndef WELCOMEGAMESTAGE_H
#define WELCOMEGAMESTAGE_H

#include <stage.h>

class WelcomeGameStage : public Stage {
public:
    WelcomeGameStage();

    void run(QList<Player *> players) override;

    bool isExecutable(QList<Player *> players) override;
};

#endif // WELCOMEGAMESTAGE_H
