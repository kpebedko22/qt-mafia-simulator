#ifndef ROLE_H
#define ROLE_H

#include <QList>
class Player;

class Role {
public:
	Role();
	virtual ~Role();

	enum Type {						//для удобства чтения кода
		MAFIA = 0,
		CIVILIAN = 1,
		DETECTIVE = 2,
		DOCTOR = 3,
		COURTESAN = 4
	};

	virtual Type get_type() = 0;	// вызывается в функциях ниже

	bool is_mafia();				// для Player::role возвращает true/false
	bool is_civilian();				// относительно того, какая роль записана
	bool is_detective();			// в Player::role
	bool is_doctor();				//
	bool is_courtesan();			//

	// функции, отвечающие за выбор днем и ночью соответственно
	//
	virtual Player* day_choice(QList<Player*> list_, int index_) = 0;
	virtual Player* night_choice(QList<Player*> list_, int index_) = 0;

protected:
	// коэффициент для расчета шанса прока интуиции и внимательности
	const int COEF_INT = 14;
};

#endif // ROLE_H
