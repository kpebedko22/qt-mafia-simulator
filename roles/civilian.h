#ifndef CIVILIAN_H
#define CIVILIAN_H

#include <role.h>

class Civilian : public Role {
public:
    Civilian();

    ~Civilian() override;

    Type getType() override;

    Player *dayChoice(Player *player, QList<Player *> players) override;

    Player *nightChoice(Player *player, QList<Player *> players) override;
};

#endif // CIVILIAN_H
