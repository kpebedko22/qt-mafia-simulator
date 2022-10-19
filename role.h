#ifndef ROLE_H
#define ROLE_H

#include <QList>

class Player;

class Role {
public:
    Role();

    virtual ~Role();

    enum Type {
        MAFIA = 1,
        CIVILIAN = 2,
        DETECTIVE = 3,
        DOCTOR = 4,
        COURTESAN = 5
    };

    virtual Type getType() = 0;

    bool is(Type type);

    virtual Player *dayChoice(Player *player, QList<Player *> players) = 0;

    virtual Player *nightChoice(Player *player, QList<Player *> players) = 0;

protected:
    // коэффициент для расчета шанса прока интуиции и внимательности
    const int COEF_INT = 14;
};

#endif // ROLE_H
