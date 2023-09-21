#-------------------------------------------------
#
# Project created by QtCreator 2019-06-25T22:24:20
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = mafia
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    player.cpp \
    role.cpp \
    game.cpp \
    phase.cpp \
    phase_courtesan.cpp \
    phase_borderline.cpp \
    phase_mafia.cpp \
    phase_doctor.cpp \
    phase_detective.cpp \
    phase_day.cpp \
    roles/civilian.cpp \
    roles/courtesan.cpp \
    roles/detective.cpp \
    roles/doctor.cpp \
    roles/mafia.cpp \
    stage.cpp \
    stages/civilian_win_stage.cpp \
    stages/courtesans/courtesan_asleep_stage.cpp \
    stages/courtesans/courtesan_awake_stage.cpp \
    stages/courtesans/courtesan_choice_stage.cpp \
    stages/mafia_win_stage.cpp \
    stages/role_assignment_stage.cpp \
    stages/welcome_game_stage.cpp

HEADERS += \
        mainwindow.h \
    player.h \
    role.h \
    game.h \
    phase.h \
    phase_courtesan.h \
    phase_borderline.h \
    phase_mafia.h \
    phase_doctor.h \
    phase_detective.h \
    phase_day.h \
    roles/civilian.h \
    roles/courtesan.h \
    roles/detective.h \
    roles/doctor.h \
    roles/mafia.h \
    stage.h \
    stages/civilian_win_stage.h \
    stages/courtesans/courtesan_asleep_stage.h \
    stages/courtesans/courtesan_awake_stage.h \
    stages/courtesans/courtesan_choice_stage.h \
    stages/mafia_win_stage.h \
    stages/role_assignment_stage.h \
    stages/welcome_game_stage.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
