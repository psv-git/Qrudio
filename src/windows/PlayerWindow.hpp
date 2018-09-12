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

//  void closeEvent(QCloseEvent *ev);
  bool event(QEvent *event);
  void run();

private slots:
  void toggleWindowVisibleAction();
  void exitAction();
  void muteAction();
  void onPlaybackButtonRelease();
  void onStopButtonRelease();
  void onRecordButtonRelease();
  void onSearchButtonRelease();
  void onEditButtonRelease();
  void onSaveStationButtonRelease();
  void onThemeButtonRelease();
  void onRunOnTrayBoxClick(bool checked);
  void onPlaylistRowClick(const QModelIndex &index);
  void onPlaylistRowDoubleClick();
  void onTrayIconClick(QSystemTrayIcon::ActivationReason r);
  void onVolumeSliderChange(int value);

private:
  Ui::PlayerWindow *m_ui = nullptr;
  PlayerHandler *m_playerHandler = nullptr;
  QSystemTrayIcon *m_trayIcon = nullptr;
  QMenu *m_trayContextMenu = nullptr;

  bool m_isPlay = false;
  bool m_isExit = false;
  bool m_isMuted = true;
  bool m_isRunOnTray = false;
//  bool m_isCategory = false;
  bool m_isTrayWasClicked = false;
  int m_volume = 0;
  QString m_iconsPath;
  THEME m_themeColor = THEME::NONE;
  EDIT m_editState = EDIT::NONE;

  void setThemeColor(THEME themeColor);
  void setTrayIcon();
  void playback(PLAYBACK playbackState);
  void toggleEditState();
  void fillEditFields();

};


#endif // PLAYERWINDOW_HPP
