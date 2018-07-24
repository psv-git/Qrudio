// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef GLOBALVARIABLES_HPP
#define GLOBALVARIABLES_HPP

#include "headers.hpp"


enum class PLAYBACK : int { NONE, PLAY, BACKWARD, FORWARD, STOP };
enum class EDIT : int { NONE, ADD, EDIT, DELETE };
enum THEME : int { NONE = 0, LIGHT = 1, DARK = 2 };
Q_DECLARE_METATYPE(THEME) // for enable qvariant_cast<THEME>

struct DefaultSettings {
  QString applicationDirectoryName;
  QString dataBasePath;
  QString configFilePath;
  QString logFilePath;
  QString stationsTableName;
} const DEFAULT_SETTINGS {
  ".qrudio",
  "/.qrudio/db.sqlite",
  "/.qrudio/config.ini",
  "/.qrudio/log.txt",
  "stations"
};


#endif // GLOBALVARIABLES_HPP
