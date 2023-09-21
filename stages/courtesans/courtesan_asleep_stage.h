#ifndef COURTESANASLEEPSTAGE_H
#define COURTESANASLEEPSTAGE_H

#include <stage.h>

class CourtesanAsleepStage : public Stage {
public:
    CourtesanAsleepStage();

    void run(QList<Player *> players) override;

    bool isExecutable(QList<Player *> players) override;
};

#endif // COURTESANASLEEPSTAGE_H
