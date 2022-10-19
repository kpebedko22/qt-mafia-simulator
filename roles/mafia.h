#ifndef MAFIA_H
#define MAFIA_H

#include <role.h>

class Mafia : public Role {
public:
    Mafia();

    ~Mafia();

    Type getType();

    Player *dayChoice(Player *player, QList<Player *> players);

    Player *nightChoice(Player *player, QList<Player *> players);
};

#endif // MAFIA_H
