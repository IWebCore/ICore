#pragma once

#include <QtCore>
#include <json.hpp>
#include <string>

#ifndef IJSON_REGISTER_INFO
#define IJSON_REGISTER_INFO

using IJson = nlohmann::json;

Q_DECLARE_METATYPE(IJson)

Q_DECLARE_METATYPE(std::string)


#endif
