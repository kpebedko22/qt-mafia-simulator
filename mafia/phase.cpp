#include "phase.h"

Phase::Phase() {}

Phase::~Phase() {}

QString Phase::get_narrator_speech(){
	return narrator_speech;
}

QString Phase::get_log_text(){
	return log_text;
}

bool Phase::get_can_execute(){
	return can_execute;
}

void Phase::new_round(){
	stage = 0;
	choices.clear();
	log_text = "";
}

Voting* Phase::get_choice(){
	return choices[0];
}

int Phase::get_count_choices(){
	return choices.count();
}

void Phase::set_choices(QList<Voting*> list_){
	choices = list_;
}

bool Phase::is_courtesan_phase(){
	return get_type() == COURTESAN_PHASE;
}

bool Phase::is_mafia_phase(){
	return get_type() == MAFIA_PHASE;
}

bool Phase::is_doctor_phase(){
	return get_type() == DOCTOR_PHASE;
}

bool Phase::is_detective_phase(){
	return get_type() == DETECTIVE_PHASE;
}

bool Phase::is_day_phase(){
	return get_type() == DAY_PHASE;
}

bool Phase::is_borderline_phase(){
	return get_type() == BORDERLINE_PHASE;
}

QList<Voting*> Phase::join_choices(QList<Voting*> list_){
	// объединяем одиночек, если есть кого объединять

	for (int i = 0; i < list_.count() - 1; i++)
		for (int j = i + 1; j < list_.count(); j++)
			if (list_[i]->elected == list_[j]->elected
					&& list_[i]->votes != 0
					&& list_[j]->votes != 0)
				list_[i]->join(list_[j]);

	//очистим список от пустых ячеек
	while (zero_votes(list_)){
		int index = get_zero_votes_index(list_);
		if (index != -1) list_.removeAt(index);
	}
/*
	// пока у на не один элемент с максимальным числом голосов за одного игрока
	while(!is_one_max_votes(list_)){
		//очистим список от пустых ячеек
		while (zero_votes(list_)){
			int index = get_zero_votes_index(list_);
			if (index != -1) list_.removeAt(index);
		}
		// расформировываем наименьшую группу на составляющие
		// получаем одиночек-голосующих, которые присоединяются
		// к тем группам, к которым могут, отнносительно красноречия
		// и логики - нельзя присоединиться к группе, если она голосует против тебя
		//
		// рассматриваемые группы, например: 3 3 2
		// распустить группу 2: 3 3 1 1
		// произвести объединение: худший вариант: 4 4
		// распускаем группу с наименьшим красноречием: 1 1 1 1 4
		// производим объединение
		// 2 1 5

		list_ = disband_smallest_group(list_);

		//очистим список от пустых ячеек
		while (zero_votes(list_)){
			int index = get_zero_votes_index(list_);
			if (index != -1) list_.removeAt(index);
		}


		QList<int> tmp_list;

		for (int i = 0; i < list_.count(); i++)
			if (list_[i]->votes == 1){
				for (int j = 0; j < list_.count(); j++)
					if (list_[i]->voters[0] != list_[j]->elected && list_[j]->votes != 0)
						tmp_list << j;
				if (tmp_list.count() != 0) {
					//найти среди групп с макс. красноречием
					int max_oratory = list_[tmp_list[0]]->get_sum_oratory();
					int index = 0;
					for (int j = 0; j < tmp_list.count(); j++)
						if (list_[tmp_list[j]]->get_sum_oratory() > max_oratory){
							max_oratory = list_[tmp_list[j]]->get_sum_oratory();
							index = j;
						}
					index = tmp_list[index];

					tmp_list.clear();

					list_[index]->join(list_[i]);
				}
			}
		tmp_list.clear();
	}

	//очистим список от пустых ячеек
	while (zero_votes(list_)){
		int index = get_zero_votes_index(list_);
		if (index != -1) list_.removeAt(index);
	}
*/
	int max_votes = list_[0]->votes;
	int index = 0;

	for (int i = 1; i < list_.count(); i++)
		if (max_votes < list_[i]->votes){
			max_votes = list_[i]->votes;
			index = i;
		}

	Voting* max = list_[index];
	list_.removeAt(index);
	list_.prepend(max);

	return list_;
}

bool Phase::zero_votes(QList<Voting*> list_){
	for (int i = 0; i < list_.count(); i++)
		if (list_[i]->votes == 0) return true;
	return false;
}

int Phase::get_zero_votes_index(QList<Voting*> list_){
	for (int i = 0; i < list_.count(); i++)
		if (list_[i]->votes == 0) return i;
	return -1;
}

bool Phase::is_one_max_votes(QList<Voting*> list_){
	//если в списке один элемент с максимальным кол-вом голосов, то вернуть true
	if (list_.count() > 1){
		int max_votes = list_[0]->votes;

		for (int i = 1; i < list_.count(); i++)
			if (max_votes < list_[i]->votes)
				max_votes = list_[i]->votes;

		int num = 0;

		for (int i = 0; i < list_.count(); i++)
			if (max_votes == list_[i]->votes)
				num++;

		if (num == 1) return true; else return false;
	}
	// если в списке был лишь один элемент, следовательно, он и есть максимальный
	return true;
}

QList<Voting*> Phase::disband_smallest_group(QList<Voting*> list_){
	// понять какой случай
	// 1. 3 3		смотрим по красноречию
	// 2. 3 3 2		смотрим по голосам
	// пусть случай 1 1, по сути, просто заново забъет в список с наименьшим красноречием

	int max_votes = list_[0]->votes;
	for (int i = 1; i < list_.count(); i++)
		if (max_votes < list_[i]->votes)
			max_votes = list_[i]->votes;

	QList<Voting*> tmp_list;

	// 1.
	for (int i = 0; i < list_.count(); i++)
		if (list_[i]->votes < max_votes && list_[i]->votes != 1){
			// разбить list[i] на составляющие
			for (int j = 0; j < list_[i]->voters.count(); j++)
				tmp_list << new Voting(list_[i]->elected, list_[i]->voters[j], 1);
			for (int j = 0; j < tmp_list.count(); j++)
				list_ << tmp_list[j];

			list_[i]->votes = 0;

			return list_;
		}

	// 2.
	int min_oratory = list_[0]->get_sum_oratory();
	int index = 0;
	for (int i = 1; i < list_.count(); i++)
		if (list_[i]->get_sum_oratory() < min_oratory){
			min_oratory = list_[i]->get_sum_oratory();
			index = i;
		}

	for (int i = 0; i < list_[index]->voters.count(); i++)
		tmp_list << new Voting(list_[index]->elected, list_[index]->voters[i], 1);

	for (int i = 0; i < tmp_list.count(); i++)
		list_ << tmp_list[i];

	list_.removeAt(index);

	return list_;
}

