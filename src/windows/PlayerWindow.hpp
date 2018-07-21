// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef PLAYERWINDOW_HPP
#define PLAYERWINDOW_HPP

#include <QSystemTrayIcon>
#include <QMenu>

#include "GlobalClasses.hpp"
#include "PlayerHandler.hpp"

namespace Ui { class PlayerWindow; }


class PlayerWindow : public QMainWindow {
Q_OBJECT

public:
  explicit PlayerWindow(QWidget *parent = nullptr);
  ~PlayerWindow();

  void run();

  void closeEvent(QCloseEvent *ev);

private slots:
  void toggleWindowVisibleAction();
  void exitAction();
  void onPlayButtonRelease();
  void onStopButtonRelease();
  void onRecordButtonRelease();
  void onSearchButtonRelease();
  void onAddButtonRelease();
  void onDeleteButtonRelease();
  void onEditButtonRelease();
  void onSaveButtonRelease();
  void onStationRowClick(const QModelIndex &index);
  void onStationRowDoubleClick(const QModelIndex &index);
  void onThemeButtonRelease();
  void onVolumeSliderChange(int value);
  void onRunOnTrayBoxClick(bool checked);
  void onTrayIconClick(QSystemTrayIcon::ActivationReason r);

//  void setTrackMetaData(TrackMetaData *trackMetaData);

private:
  Ui::PlayerWindow *m_ui = nullptr;
  PlayerHandler *m_playerHandler = nullptr;

  QSystemTrayIcon *m_trayIcon = nullptr;
  QMenu *m_trayContextMenu = nullptr;

  bool m_isPlaying = false;
  bool m_isExit = false;
  bool m_isTrayWasClicked = false;

  QString m_iconsPath;
  THEME m_themeColor;
  bool m_isRunOnTray;

  void initUi();
  void setThemeColor(THEME themeColor);
  void playback(STATE state);
  bool addStation(const QString &stationName, const QString &url);
  bool deleteStation();
  bool editStation();
  bool saveStation(int id, const QString &stationName, const QString &url);

};


#endif // PLAYERWINDOW_HPP
