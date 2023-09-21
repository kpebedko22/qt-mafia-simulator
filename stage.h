#ifndef STAGE_H
#define STAGE_H

#include <QList>
#include <player.h>

class Stage {
public:
    Stage();

    virtual void run(QList<Player *> players) = 0;

    virtual bool isExecutable(QList<Player *> players) = 0;

    QString getNarratorSpeech();

    QString getLogText();

    bool getIsRequired();

protected:
    QString narratorSpeech;
    QString logText;

    bool isRequired{};
};

#endif // STAGE_H
