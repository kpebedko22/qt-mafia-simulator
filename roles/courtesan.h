#ifndef COURTESAN_H
#define COURTESAN_H

#include <role.h>

class Courtesan : public Role {
public:
    Courtesan();

    ~Courtesan();

    Type getType();

    Player *dayChoice(Player *player, QList<Player *> players);

    Player *nightChoice(Player *player, QList<Player *> players);
};

#endif // COURTESAN_H
