// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef SETTINGSHANDLER_HPP
#define SETTINGSHANDLER_HPP

#include <QSettings>
#include <QFontDatabase>

#include "GlobalFunctions.hpp"
#include "GlobalVariables.hpp"


class SettingsHandler {

public:
  static SettingsHandler& getInstance() {
    static SettingsHandler m_instance;
    return m_instance;
  }

  SettingsHandler(SettingsHandler const&) = delete;
  SettingsHandler& operator = (SettingsHandler const&) = delete;

  QStringList getGroups();

  QVariant getSetting(const QString &group, const QString &key, const QVariant &defaultValue);
  void setSetting(const QString &group, const QString &key, const QVariant &value);
  void removeSetting(const QString &key);

  QFont getFont(const QString &family, const QString &style, int pointSize);
  void setFonts();

  void saveSettings();

private:
  SettingsHandler();
  ~SettingsHandler();

  QSettings *m_settings = nullptr;
  QFontDatabase m_fontsList;

};


#endif // SETTINGSHANDLER_HPP
