#ifndef DOCTOR_H
#define DOCTOR_H

#include <role.h>

class Doctor : public Role {
public:
    Doctor();

    ~Doctor() override;

    Type getType() override;

    Player *dayChoice(Player *player, QList<Player *> players) override;

    Player *nightChoice(Player *player, QList<Player *> players) override;
};

#endif // DOCTOR_H
