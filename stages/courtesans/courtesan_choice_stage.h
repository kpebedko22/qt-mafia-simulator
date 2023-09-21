#ifndef COURTESANCHOICESTAGE_H
#define COURTESANCHOICESTAGE_H

#include <stage.h>

class CourtesanChoiceStage : public Stage {
public:
    CourtesanChoiceStage();

    void run(QList<Player *> players) override;

    bool isExecutable(QList<Player *> players) override;
};

#endif // COURTESANCHOICESTAGE_H
