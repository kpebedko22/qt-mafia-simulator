#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include "game.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	QList<QLabel*> labels_players_names;
	QList<QLabel*> labels_info;
	QList<QLabel*> labels_players_speech;
	QTimer* timer;
	Game* current_game;
	QScrollArea* scrl_area;
	QWidget* wgt_scrl_area;

	void update_speeches();
	void update_info_game();
	void set_names();
	void make_labels_for_info_about_players(int num_);
	void make_labels_for_players_speech(int num_);

private slots:
	void update_time();
	void on_pushButton_start_game_clicked();
	void on_pushButton_stop_game_clicked();
	void on_pushButton_shut_down_game_clicked();
	void on_pushButton_exit_clicked();
	void on_pushButton_continue_game_clicked();
};

#endif // MAINWINDOW_H
