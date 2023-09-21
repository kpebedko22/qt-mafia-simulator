#ifndef COURTESANAWAKESTAGE_H
#define COURTESANAWAKESTAGE_H

#include <stage.h>

class CourtesanAwakeStage : public Stage {
public:
    CourtesanAwakeStage();

    void run(QList<Player *> players) override;

    bool isExecutable(QList<Player *> players) override;
};

#endif // COURTESANAWAKESTAGE_H
