#ifndef DETECTIVE_H
#define DETECTIVE_H

#include <role.h>

class Detective : public Role {
public:
    Detective();

    ~Detective();

    Type getType();

    Player *dayChoice(Player *player, QList<Player *> players);

    Player *nightChoice(Player *player, QList<Player *> players);
};

#endif // DETECTIVE_H
