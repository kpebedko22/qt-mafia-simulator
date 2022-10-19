#ifndef CIVILIAN_H
#define CIVILIAN_H

#include <role.h>

class Civilian : public Role {
public:
    Civilian();

    ~Civilian();

    Type getType();

    Player *dayChoice(Player *player, QList<Player *> players);

    Player *nightChoice(Player *player, QList<Player *> players);
};

#endif // CIVILIAN_H
