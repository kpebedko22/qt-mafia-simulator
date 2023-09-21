#ifndef MAFIA_H
#define MAFIA_H

#include <role.h>

class Mafia : public Role {
public:
    Mafia();

    ~Mafia() override;

    Type getType() override;

    Player *dayChoice(Player *player, QList<Player *> players) override;

    Player *nightChoice(Player *player, QList<Player *> players) override;
};

#endif // MAFIA_H
