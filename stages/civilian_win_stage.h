#ifndef CIVILIANWINSTAGE_H
#define CIVILIANWINSTAGE_H

#include <stage.h>

class CivilianWinStage : public Stage {
public:
    CivilianWinStage();

    void run(QList<Player *> players) override;

    bool isExecutable(QList<Player *> players) override;
};

#endif // CIVILIANWINSTAGE_H
