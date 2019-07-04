#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <role.h>
#include <QThread>
#include <QTimer>
#include <QtCore/qmath.h>
#include <QRandomGenerator>
#include <QtDebug>
#include <QLayout>

QList<Player_info> generate_info(int num);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	ui->label_info_game->setText("");
	ui->label_narrator_speech->setText("Приветствуем в игре Мафия. Для начала игры нажмите кнопку \"Начать игру\"");

	timer = new QTimer();
	timer->setInterval(1* 1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_time()));




	ui->pushButton_start_game->setEnabled(true);
	ui->pushButton_stop_game->setEnabled(false);
	ui->pushButton_continue_game->setEnabled(false);
	ui->pushButton_shut_down_game->setEnabled(false);
	ui->pushButton_exit->setEnabled(true);
}

MainWindow::~MainWindow() {	delete ui;}

void MainWindow::on_pushButton_start_game_clicked(){
	int rnd = 12;//QRandomGenerator::global()->bounded(static_cast<int>(3), static_cast<int>(13));

	QList<Player_info> list_of_info = generate_info(rnd);
	current_game = new Game(rnd, list_of_info);

	make_labels_for_info_about_players(rnd);
	make_labels_for_players_speech(rnd);

	update_info_game();
	update_speeches();
	set_names();

	timer->start();
	ui->pushButton_start_game->setEnabled(false);
	ui->pushButton_stop_game->setEnabled(true);
	ui->pushButton_continue_game->setEnabled(false);
	ui->pushButton_shut_down_game->setEnabled(false);
	ui->pushButton_exit->setEnabled(false);
}

void MainWindow::on_pushButton_stop_game_clicked(){
	if (timer->isActive()){
		ui->pushButton_stop_game->setText("Возобновить игру");
		timer->stop();

		if (current_game->is_game_over())
			ui->pushButton_continue_game->setEnabled(true);

		ui->pushButton_exit->setEnabled(true);
		ui->pushButton_shut_down_game->setEnabled(true);
	}
	else{
		ui->pushButton_stop_game->setText("Приостановить игру");
		timer->start();

		ui->pushButton_exit->setEnabled(false);
		ui->pushButton_shut_down_game->setEnabled(false);
	}
}

void MainWindow::on_pushButton_continue_game_clicked(){
	current_game->next_round();
	timer->start();

	ui->textEdit_log->append("\nНовый раунд\n");
	ui->pushButton_stop_game->setText("Приостановить игру");

	ui->pushButton_start_game->setEnabled(false);
	ui->pushButton_continue_game->setEnabled(false);
	ui->pushButton_exit->setEnabled(false);
	ui->pushButton_shut_down_game->setEnabled(false);
}

void MainWindow::on_pushButton_shut_down_game_clicked(){

	delete current_game;

	qDeleteAll(labels_info);
	qDeleteAll(labels_players_names);
	qDeleteAll(labels_players_speech);
	delete scrl_area;


	labels_players_names.clear();
	labels_info.clear();
	labels_players_speech.clear();
	ui->label_info_game->clear();
	ui->label_narrator_speech->setText("Для начала игры нажмите кнопку \"Начать игру\"");
	ui->textEdit_log->clear();

	ui->pushButton_stop_game->setText("Приостановить игру");
	ui->pushButton_start_game->setEnabled(true);
	ui->pushButton_stop_game->setEnabled(false);
	ui->pushButton_continue_game->setEnabled(false);
	ui->pushButton_shut_down_game->setEnabled(false);
	ui->pushButton_exit->setEnabled(true);
}

void MainWindow::on_pushButton_exit_clicked(){
	this->close();
}


void MainWindow::update_time(){
	current_game->step();
	update_speeches();
	update_info_game();
}

void MainWindow::update_speeches(){
	for (int i = 0; i < current_game->get_num_players(); i++)
		labels_players_speech[i]->setText(current_game->players[i]->get_speech());
	ui->label_narrator_speech->setText(current_game->get_narrator_speech());
}

void MainWindow::update_info_game() {

	ui->label_info_game->setText("Игроков: " + QString::number(current_game->get_num_players()) +\
								 "\nМафия: " + QString::number(current_game->get_num_mafia()) +\
								 "\nМирные жители: " + QString::number(current_game->get_num_civilians()) +\
								 "\nДетективы: " + QString::number(current_game->get_num_detectives()) +\
								 "\nДоктора: " + QString::number(current_game->get_num_doctors()) +\
								 "\nКуртизанки: " + QString::number(current_game->get_num_courtesans())+\
								 "\nСчет (Maf:Civ): " + QString::number(current_game->get_mafia_win()) + " : " + QString::number(current_game->get_civilians_win()));

	for (int i = 0; i < current_game->players.count(); i++){
		Player_info cur_info = current_game->players[i]->get_info();
		QString string = "";
		string += cur_info.name + "\n";

		if (! current_game->players[i]->role) string += "Роль: не назначена\n"; else{
			if ( current_game->players[i]->role->is_courtesan()) string += "Роль: куртизанка\n";
			if ( current_game->players[i]->role->is_mafia()) string += "Роль: мафия\n";
			if ( current_game->players[i]->role->is_civilian()) string += "Роль: мирный\n";
			if ( current_game->players[i]->role->is_detective()) string += "Роль: детектив\n";
			if ( current_game->players[i]->role->is_doctor()) string += "Роль: доктор\n";
		}

		if (cur_info.alive) string += "Жив: да\n"; else string += "Жив: нет\n";
		if (!cur_info.conscious) string += "Спит: да\n"; else string += "Спит: нет\n";

		string += "Красноречие: " + QString::number(cur_info.oratory) + "\n";
		string += "Дружелюбность: " + QString::number(cur_info.friendliness) + "\n";
		string += "Токсичность: " + QString::number(cur_info.toxicity) + "\n";
		string += "Эгоизм: " + QString::number(cur_info.selfishness) + "\n";
		string += "Хитрость: " + QString::number(cur_info.cunning) + "\n";

		if (cur_info.sex == 0) string += "Пол: М\n"; else string += "Пол: Ж\n";
		string += "Возраст: " + QString::number(cur_info.age) + "\n";

		string += "Интуиция: " + QString::number(cur_info.intuition) + "\n";
		string += "Внимательность: " + QString::number(cur_info.attentiveness) + "\n";

		string += "\nСимпатия: \n";
		for (int j = 0; j < current_game->players[i]->sympathy.count(); j++){
			string += current_game->players[i]->sympathy[j]->cur_player->get_name() + ": ";
			string += QString::number(current_game->players[i]->sympathy[j]->points) + "\n";
		}

		labels_info[i]->setText(string);
	}

	if (current_game->get_log_text() != "") ui->textEdit_log->append(current_game->get_log_text());
}

void MainWindow::make_labels_for_info_about_players(int num_){
	scrl_area = new QScrollArea(this);
	scrl_area->setGeometry(10, 400, 1190, 600);
	scrl_area->setFixedSize(930, 190);

	wgt_scrl_area = new QWidget();
	QHBoxLayout* layout = new QHBoxLayout(wgt_scrl_area);


	for (int i = 0; i < num_; i++){
		labels_info << new QLabel("");

		layout->addWidget(labels_info[i]);

		labels_info[i]->setFixedSize(150, 500);
		labels_info[i]->setFrameShape(QFrame::StyledPanel);
		labels_info[i]->setFrameShadow(QFrame::Plain);
		labels_info[i]->setLineWidth(5);
		QFont font = labels_info[i]->font();
		font.setPixelSize(14);
		labels_info[i]->setFont(font);
		labels_info[i]->setAlignment(Qt::AlignTop);
		labels_info[i]->setAlignment(Qt::AlignLeft);

	}

	scrl_area->setWidget(wgt_scrl_area);
	scrl_area->show();
}

void MainWindow::make_labels_for_players_speech(int num_){
	double a = (2 * M_PI) / num_;
	QList<QPoint*> coord;
	for (int i = 0; i < num_; i++)
		coord << new QPoint(static_cast<int>(430 * qCos(a * i)) + (this->width() / 2) - (this->width() / 7) , static_cast<int>(120 * qSin(a * i) + (this->height() / 2) - (this->height() / 8)));

	int width = 150;
	int height = 45;

	for (int i = 0; i < num_; i++){
		labels_players_speech << new QLabel("", this);
		labels_players_speech[i]->setGeometry(coord[i]->x(), coord[i]->y(), width, height);
		labels_players_speech[i]->setFrameShape(QFrame::StyledPanel);
		labels_players_speech[i]->setFrameShadow(QFrame::Plain);
		labels_players_speech[i]->setLineWidth(5);
		QFont font = labels_players_speech[i]->font();
		font.setPixelSize(14);
		labels_players_speech[i]->setFont(font);
		labels_players_speech[i]->setAlignment(Qt::AlignCenter);
		labels_players_speech[i]->setWordWrap(true);
		labels_players_speech[i]->show();

		labels_players_names << new QLabel("", this);
		labels_players_names[i]->setGeometry(coord[i]->x(), coord[i]->y() - 20, width, 22);
		labels_players_names[i]->show();
	}
}

void MainWindow::set_names(){
	for (int i = 0; i < current_game->players.count(); i++)
		labels_players_names[i]->setText(current_game->players[i]->get_name());
}

QList<Player_info> generate_info(int num){
	QList<Player_info> list;

	QList<QString> names_male = { "alex", "michael", "eugene", "roman", "oleg", "artem", "egor", "maxim" };
	QList<QString> names_female = { "polina", "victoria", "olya", "irina", "liza", "nastya", "yana", "dasha" };

	for (int i = 0; i < num; i++){
		Player_info current_info;

		current_info.alive = true;
		current_info.conscious = true;

		int rnd = QRandomGenerator::global()->bounded(static_cast<int>(0), static_cast<int>(101));

		if (rnd % 2 == 0){
			if (names_male.count() > 0){
				int rnd_male = QRandomGenerator::global()->bounded(static_cast<int>(0), static_cast<int>(names_male.count()));
				current_info.name = names_male[rnd_male];
				current_info.sex = 0;
				names_male.removeAt(rnd_male);
			}
			else{
				if (names_female.count() > 0){
					int rnd_female = QRandomGenerator::global()->bounded(static_cast<int>(0), static_cast<int>(names_female.count()));
					current_info.name = names_female[rnd_female];
					current_info.sex = 1;
					names_female.removeAt(rnd_female);
				}
			}
		}
		else{
			if (names_female.count() > 0){
				int rnd_female = QRandomGenerator::global()->bounded(static_cast<int>(0), static_cast<int>(names_female.count()));
				current_info.name = names_female[rnd_female];
				current_info.sex = 1;
				names_female.removeAt(rnd_female);
			}
			else{
				if (names_male.count() > 0){
					int rnd_male = QRandomGenerator::global()->bounded(static_cast<int>(0), static_cast<int>(names_male.count()));
					current_info.name = names_male[rnd_male];
					current_info.sex = 0;
					names_male.removeAt(rnd_male);
				}
			}


		}

		current_info.age = QRandomGenerator::global()->bounded(static_cast<int>(18), static_cast<int>(41));
		current_info.oratory = QRandomGenerator::global()->bounded(static_cast<int>(1), static_cast<int>(11));
		current_info.friendliness = QRandomGenerator::global()->bounded(static_cast<int>(1), static_cast<int>(11));
		current_info.toxicity = QRandomGenerator::global()->bounded(static_cast<int>(1), static_cast<int>(11));
		current_info.selfishness = QRandomGenerator::global()->bounded(static_cast<int>(1), static_cast<int>(11));
		current_info.cunning = QRandomGenerator::global()->bounded(static_cast<int>(1), static_cast<int>(11));
		current_info.intuition = QRandomGenerator::global()->bounded(static_cast<int>(1), static_cast<int>(11));
		current_info.attentiveness = QRandomGenerator::global()->bounded(static_cast<int>(1), static_cast<int>(11));


		list << current_info;
	}

	return list;
}







