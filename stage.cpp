#include "stage.h"

Stage::Stage() {
    this->isRequired = true;
}

QString Stage::getNarratorSpeech() {
    return this->narratorSpeech;
}

QString Stage::getLogText() {
    return this->logText;
}

bool Stage::getIsRequired() {
    return this->isRequired;
}
