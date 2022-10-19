#ifndef DOCTOR_H
#define DOCTOR_H

#include <role.h>

class Doctor : public Role {
public:
    Doctor();

    ~Doctor();

    Type getType();

    Player *dayChoice(Player *player, QList<Player *> players);

    Player *nightChoice(Player *player, QList<Player *> players);
};

#endif // DOCTOR_H
