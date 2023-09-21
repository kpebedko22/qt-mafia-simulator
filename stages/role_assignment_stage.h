#ifndef ROLEASSIGNMENTSTAGE_H
#define ROLEASSIGNMENTSTAGE_H

#include <stage.h>

class RoleAssignmentStage : public Stage {
public:
    RoleAssignmentStage();

    void run(QList<Player*> players);
    bool isExecutable(QList<Player *> players);
};

#endif // ROLEASSIGNMENTSTAGE_H
