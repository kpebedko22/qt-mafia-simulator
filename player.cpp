#include "player.h"
#include "roles/mafia.h"
#include "roles/civilian.h"
#include "roles/courtesan.h"
#include "roles/detective.h"
#include "roles/doctor.h"
#include <QRandomGenerator>
#include <QtCore/qmath.h>

Player::Player(){}

Player::Player(Player_info info_){
	info = info_;
	role = nullptr;
}

Player::~Player(){};

void Player::set_role_mafia(){
	role = new Mafia();
}

void Player::set_role_civilian(){
	role = new Civilian();
}

void Player::set_role_courtesan(){
	role = new Courtesan();
}

void Player::set_role_doctor(){
	role = new Doctor();
}

void Player::set_role_detective(){
	role = new Detective();
}

void Player::make_list_of_sympathy(QList<Player*> list_){
	for (int i = 0; i < list_.count(); i++)
		if (list_[i] != this){
			int points = 50;

			// ПОЛОЖИТЕЛЬНЫЕ качества
			points += list_[i]->get_oratory() - 5;
			points += list_[i]->get_friendliness() - 5;

			// ОТРИЦАТЕЛЬНЫЕ качества
			points -= list_[i]->get_toxicity() - 5;
			points -= list_[i]->get_selfishness() - 5;
			points -= list_[i]->get_cunning() - 5;

			// ОТНОСИТЕЛЬНЫЕ качества
			if (this->get_sex() != list_[i]->get_sex()) points += 5;
			if (qFabs(this->get_age() - list_[i]->get_age()) < 5) points += 5;

			int rnd = QRandomGenerator::global()->bounded(static_cast<int>(1),static_cast<int>(10));
			if (rnd % 2) points += rnd; else points -= rnd;


			if (points < 0) points = 0;
			if (points > 100) points = 100;

			sympathy << new Sympathy(list_[i], points);
		}
}

void Player::set_greeting_phrase(){
	int rnd = QRandomGenerator::global()->bounded(static_cast<int>(7));
	switch (rnd) {
		case 0: {info.speech = "Приуэт"; break;}
		case 1: {info.speech = "Привет всем!"; break;}
		case 2: {info.speech = "Привет"; break;}
		case 3: {info.speech = "Приветики-пистолетики"; break;}
		case 4: {info.speech = "Приветик"; break;}
		case 5: {info.speech = "Здарова!"; break;}
		case 6: {info.speech = "Здравствуйте"; break;}
		default: {info.speech = "Хеллоу"; break;}
	}
}

void Player::set_conscious_sleep(){
	info.conscious = false;
}

void Player::set_conscious_sleep_string(){
	info.speech = "(-_-) zzZ";
}

void Player::set_conscious_awake(){
	info.conscious = true;
}

void Player::set_conscious_awake_string(){
	info.speech = "(o_o)";
}

void Player::set_alive_dead(){
	info.alive = false;
}

void Player::set_alive_dead_string(){
	info.speech = "(x_x)";
}

void Player::set_alive(){
	info.alive = true;
}

void Player::set_choice_string(Player* chosen){
	info.speech = chosen->get_name();
}

void Player::set_emotion_sad_string(){
	int rnd = QRandomGenerator::global()->bounded(static_cast<int>(1),static_cast<int>(5));
	QString text;
	switch (rnd) {
		case 1:{ text = "(>_<)"; break;}
		case 2:{ text = "(｡•́︿•̀｡)"; break;}
		case 3:{ text = "(╥_╥)"; break;}
		case 4:{ text = "(」°ロ°)」"; break;}
		default:{ text = "(>_<)"; break;}
	}
	info.speech = text;
}

void Player::set_emotion_happy_string(){
	int rnd = QRandomGenerator::global()->bounded(static_cast<int>(1),static_cast<int>(4));
	QString text;
	switch (rnd) {
		case 1:{ text = "ヽ(*・ω・)ﾉ"; break;}
		case 2:{ text = "＼(＾▽＾)／"; break;}
		case 3:{ text = "ヽ(・∀・)ﾉ"; break;}
		default:{ text = "(◕‿◕)"; break;}
	}
	info.speech = text;
}

void Player::increase_sympathy_to(Player* player_){
	for (int i = 0; i < sympathy.count(); i++)
		if (sympathy[i]->cur_player == player_){ sympathy[i]->points += 3; if (sympathy[i]->points > 100) sympathy[i]->points = 100; return; }
}


void Player::decrease_sympathy_to(Player* player_){
	for (int i = 0; i < sympathy.count(); i++)
		if (sympathy[i]->cur_player == player_){ sympathy[i]->points -= 5; if (sympathy[i]->points < 0) sympathy[i]->points = 0; return; }
}

int Player::get_counter_doctor(){
	return counter_doctor;
}

int Player::get_counter_courtesan(){
	return counter_courtesan;
}

void Player::increase_counter_doctor(){
	counter_doctor++;
}

void Player::increase_counter_courtesan(){
	counter_courtesan++;
}

void Player::set_counters_null(){
	counter_courtesan = 0;
	counter_doctor = 0;
}

Player_info Player::get_info(){
	return info;
}

QString Player::get_name(){
	return info.name;
}

QString Player::get_speech(){
	return info.speech;
}

bool Player::is_alive(){
	return info.alive;
}

bool Player::is_conscious(){
	return info.conscious;
}

int Player::get_oratory(){
	return info.oratory;
}

int Player::get_friendliness(){
	return info.friendliness;
}

int Player::get_toxicity(){
	return info.toxicity;
}

int Player::get_selfishness(){
	return info.selfishness;
}

int Player::get_cunning(){
	return info.cunning;
}

int Player::get_sex(){
	return info.sex;
}

int Player::get_age(){
	return info.age;
}

int Player::get_intuition(){
	return info.intuition;
}

int Player::get_attentiveness(){
	return info.attentiveness;
}
