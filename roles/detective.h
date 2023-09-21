#ifndef DETECTIVE_H
#define DETECTIVE_H

#include <role.h>

class Detective : public Role {
public:
    Detective();

    ~Detective() override;

    Type getType() override;

    Player *dayChoice(Player *player, QList<Player *> players) override;

    Player *nightChoice(Player *player, QList<Player *> players) override;
};

#endif // DETECTIVE_H
