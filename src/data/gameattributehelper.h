#pragma once

#include "game.h"

namespace GameAttributeHelper{

    QString getDbTableName(Game::Attribute attribute);

    QString getDbRelationTableName(Game::Attribute attribute);

    QString getIdField(Game::Attribute attribute);

};
