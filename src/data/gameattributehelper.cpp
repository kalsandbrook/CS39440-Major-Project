
#include "gameattributehelper.h"

QString GameAttributeHelper::getDbTableName(Game::Attribute attribute)
{
    switch (attribute) {
    case Game::Attribute::GENRES:
        return "genres";
    case Game::Attribute::DEVELOPERS:
        return "developers";
    case Game::Attribute::PUBLISHERS:
        return "publishers";
    case Game::Attribute::PLATFORMS:
        return "platforms";
    case Game::Attribute::USERTAGS:
        return "user_tags";
    default:
        return {};
    }
}

QString GameAttributeHelper::getDbRelationTableName(Game::Attribute attribute)
{
    switch (attribute) {
    case Game::Attribute::GENRES:
        return "game_genres";
    case Game::Attribute::DEVELOPERS:
        return "game_developers";
    case Game::Attribute::PUBLISHERS:
        return "game_publishers";
    case Game::Attribute::PLATFORMS:
        return "game_platforms";
    case Game::Attribute::USERTAGS:
        return "game_user_tags";
    default:
        return {};
    }
}

QString GameAttributeHelper::getIdField(Game::Attribute attribute)
{
    switch (attribute) {
    case Game::Attribute::GENRES:
        return "genreId";
    case Game::Attribute::DEVELOPERS:
        return "developerId";
    case Game::Attribute::PUBLISHERS:
        return "publisherId";
    case Game::Attribute::PLATFORMS:
        return "platformId";
    case Game::Attribute::USERTAGS:
        return "userTagId";
    default:
        return {};
    }
}

QStringList GameAttributeHelper::getDbInfo(Game::Attribute attribute)
{
    return { getIdField(attribute), getDbTableName(attribute), getDbRelationTableName(attribute) };
}
