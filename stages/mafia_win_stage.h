#ifndef MAFIAWINSTAGE_H
#define MAFIAWINSTAGE_H

#include <stage.h>

class MafiaWinStage : public Stage {
public:
    MafiaWinStage();

    void run(QList<Player *> players) override;

    bool isExecutable(QList<Player *> players) override;
};

#endif // MAFIAWINSTAGE_H
