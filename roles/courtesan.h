#ifndef COURTESAN_H
#define COURTESAN_H

#include <role.h>

class Courtesan : public Role {
public:
    Courtesan();

    ~Courtesan() override;

    Type getType() override;

    Player *dayChoice(Player *player, QList<Player *> players) override;

    Player *nightChoice(Player *player, QList<Player *> players) override;
};

#endif // COURTESAN_H
