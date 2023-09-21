#ifndef GAME_H
#define GAME_H

#include <player.h>

class Phase;
class Stage;
struct Voting;

class Game {
public:
	Game();
	~Game();
	Game(QList<Player_info> players_info_);

	void step();
	void next_round();

	int get_num_players();				// возвращают кол-во
	int get_num_mafia();				// тех/иных фракций
	int get_num_civilians();			// на форму, для вывода в лейбл
	int get_num_detectives();			//
	int get_num_doctors();				//
	int get_num_courtesans();			//
	bool is_game_over();
	int get_mafia_win();
	int get_civilians_win();

	QString get_narrator_speech();		// возвращает текущую фразу ведущего
	QString get_log_text();				// возвращает текущую фразу лога

	QList<Player*> players;				// список указателей на игроков

private:
	int num_players{};					// кол-во тех или иных фракций
	int num_mafia{};						// и так всё понятно
	int num_civilians{};					//
	int num_detectives{};					//
	int num_doctors{};					//
	int num_courtesans{};					//
	int mafia_win{};						// кол-во выигрышей мафии
	int civilians_win{};					// кол-во выигрышей мирных

	bool game_over{};

	QList<Phase*> stages;				// список наследников Phase, хранит всех наследников
										// в step() при каждом заходе берет из начала элемент
										// и если можно обработать этот элемент, то обрабатывает его до тех пор
										// пока не наступит момент, когда его надо вернуть в конец списка
										// и взять новый элемент

	void update_numbers();				// обновить кол-во живых "ролей"
	void fill_stages();

	QList<Voting*> list_of_choices;
	QString narrator_speech;
	QString log_text;

	void generate_players(QList<Player_info> players_info_);

    QList<Stage*> stagesList;
};

#endif // GAME_H
