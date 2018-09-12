// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "PlayerWindow.hpp"
#include "ui_PlayerWindow.h"


PlayerWindow::PlayerWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::PlayerWindow) {
  m_playerHandler = new PlayerHandler();

  // get settings -------------------------------------------------------------

  m_isPlay = SettingsHandler::getInstance().getSetting("", "is_play", false).toBool();
  m_themeColor = qvariant_cast<THEME>(SettingsHandler::getInstance().getSetting("", "theme_color", THEME::NONE));
  m_isRunOnTray = SettingsHandler::getInstance().getSetting("", "run_on_tray", false).toBool();
  m_volume = SettingsHandler::getInstance().getSetting("", "volume", 0).toInt();
  if (m_volume < 0 || m_volume > 100) m_volume = 0;
  if (m_themeColor == THEME::NONE) m_themeColor = THEME::LIGHT;

  // setup --------------------------------------------------------------------

  m_ui->setupUi(this);
  m_trayIcon = new QSystemTrayIcon(this);
  m_trayContextMenu = new QMenu("Menu");
  m_trayContextMenu->addAction("About", this, SLOT(muteAction()));
  m_trayContextMenu->addSeparator();
  m_trayContextMenu->addAction("Show/Hide", this, SLOT(toggleWindowVisibleAction()));
  m_trayContextMenu->addAction("Mute/Unmute", this, SLOT(muteAction()));
  m_trayContextMenu->addSeparator();
  m_trayContextMenu->addAction("Exit", this, SLOT(exitAction()));
  m_trayIcon->setContextMenu(m_trayContextMenu);

  setThemeColor(m_themeColor);
  m_ui->runOnTrayCheckBox->setChecked(m_isRunOnTray);
  m_ui->stationsTreeView->setModel(m_playerHandler->getPlaylistModel());
  m_ui->stationsTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  m_ui->stopButton->hide();

  // signals ------------------------------------------------------------------

  connect(m_ui->playButton, SIGNAL(released()), this, SLOT(onPlaybackButtonRelease()));
  connect(m_ui->prevPlayButton, SIGNAL(released()), this, SLOT(onPlaybackButtonRelease()));
  connect(m_ui->nextPlayButton, SIGNAL(released()), this, SLOT(onPlaybackButtonRelease()));
  connect(m_ui->stopButton, SIGNAL(released()), this, SLOT(onStopButtonRelease()));
  connect(m_ui->recordButton, SIGNAL(released()), this, SLOT(onRecordButtonRelease()));
  connect(m_ui->searchButton, SIGNAL(released()), this, SLOT(onSearchButtonRelease()));
  connect(m_ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeSliderChange(int)));

  connect(m_ui->addPlaylistButton, SIGNAL(released()), this, SLOT(onEditButtonRelease()));
  connect(m_ui->addStationButton, SIGNAL(released()), this, SLOT(onEditButtonRelease()));
  connect(m_ui->deleteStationButton, SIGNAL(released()), this, SLOT(onEditButtonRelease()));
  connect(m_ui->editStationButton, SIGNAL(released()), this, SLOT(onEditButtonRelease()));
  connect(m_ui->saveStationButton, SIGNAL(released()), this, SLOT(onSaveStationButtonRelease()));

  connect(m_ui->lightThemeRadioButton, SIGNAL(released()), this, SLOT(onThemeButtonRelease()));
  connect(m_ui->darkThemeRadioButton, SIGNAL(released()), this, SLOT(onThemeButtonRelease()));
  connect(m_ui->runOnTrayCheckBox, SIGNAL(toggled(bool)), this, SLOT(onRunOnTrayBoxClick(bool)));

  connect(m_ui->stationsTreeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onPlaylistRowClick(QModelIndex)));
  connect(m_ui->stationsTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onPlaylistRowDoubleClick()));

  connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onTrayIconClick(QSystemTrayIcon::ActivationReason)));
}


PlayerWindow::~PlayerWindow() {
  SettingsHandler::getInstance().setSetting("", "volume", m_volume);
  SettingsHandler::getInstance().setSetting("", "is_play", m_isPlay);
  if (m_playerHandler) delete m_playerHandler;
  if (m_trayIcon) delete m_trayIcon;
  if (m_trayContextMenu) delete m_trayContextMenu;
  delete m_ui;
}

// public methods =============================================================

void PlayerWindow::run() {
  m_ui->volumeSlider->setValue(m_volume);
  if (m_isPlay) playback(PLAYBACK::PLAY);
  if (!m_isRunOnTray) this->show();
  m_trayIcon->show();
}

// events =====================================================================

bool PlayerWindow::event(QEvent *event) {
  if (event->type() == QEvent::Close) {
    if (m_isExit) { // close application by system tray
      m_trayIcon->hide();
      SettingsHandler::getInstance().saveSettings();
      QApplication::quit();
    } else { // hide/show window
      toggleWindowVisibleAction();
    }
  } else if (event->type() == QEvent::WindowStateChange) {
    if (this->isMinimized()) this->close();
  }
  event->ignore();
  return true;
}

// private slots ==============================================================

void PlayerWindow::toggleWindowVisibleAction() {
  if (this->isVisible()) this->hide();
  else {
    this->showNormal();
    this->activateWindow();
  }
}


void PlayerWindow::exitAction() {
  m_isExit = true;
  this->close(); // invoke close event
}


void PlayerWindow::muteAction() {
  if (!m_isPlay) return;
  if (m_isMuted) m_ui->volumeSlider->setValue(m_volume);
  else m_ui->volumeSlider->setValue(0);
}


void PlayerWindow::onPlaybackButtonRelease() {
  if (sender() == m_ui->playButton) {
    if (!m_isPlay) playback(PLAYBACK::PLAY);
  } else if (sender() == m_ui->prevPlayButton) {
    playback(PLAYBACK::BACKWARD);
  } else if (sender() == m_ui->nextPlayButton) {
    playback(PLAYBACK::FORWARD);
  }
}


void PlayerWindow::onStopButtonRelease() {
  if (m_isPlay) playback(PLAYBACK::STOP);
}


void PlayerWindow::onRecordButtonRelease() {}


void PlayerWindow::onSearchButtonRelease() {
  QString trackTitle = m_ui->trackLabel->text();
  if (!trackTitle.isEmpty()) OpenUrl("https://www.google.ru/search?q=" + trackTitle);
}


void PlayerWindow::onEditButtonRelease() {
  if (sender() == m_ui->addPlaylistButton) {
    QString plylistPath = GetFilePath(tr("Choose file"), tr("Playlist extensions (*.m3u *.m3u8)"));
    // m_playerHandler->addPlaylist(playlistPath);
  } else {
    if (sender() == m_ui->addStationButton) {
      (m_editState == EDIT::ADD) ? m_editState = EDIT::NONE : m_editState = EDIT::ADD;
    } else if (sender() == m_ui->editStationButton) {
      (m_editState == EDIT::EDIT) ? m_editState = EDIT::NONE : m_editState = EDIT::EDIT;
    } else if (sender() == m_ui->deleteStationButton) {
      m_playerHandler->deleteStation(m_ui->stationsTreeView->currentIndex());
    }
    toggleEditState();
  }
}


void PlayerWindow::onSaveStationButtonRelease() {
  if (m_editState == EDIT::ADD) m_playerHandler->addStation(StationRecord(m_ui->categoryEdit->text(), m_ui->stationNameEdit->text(), m_ui->stationUrlEdit->text()));

  m_editState = EDIT::NONE;
  toggleEditState();
}


void PlayerWindow::onThemeButtonRelease() {
  QObject *obj = sender();
  if (obj == m_ui->lightThemeRadioButton) setThemeColor(THEME::LIGHT);
  else setThemeColor(THEME::DARK);
}


void PlayerWindow::onRunOnTrayBoxClick(bool checked) {
  if (checked == m_isRunOnTray) return;
  m_isRunOnTray = checked;
  SettingsHandler::getInstance().setSetting("", "run_on_tray", m_isRunOnTray);
}


void PlayerWindow::onPlaylistRowClick(const QModelIndex &index) {
  m_playerHandler->setSelectedIndex(index);
  if (m_ui->editTab->isVisible()) {
    if (m_editState == EDIT::NONE) m_ui->deleteStationButton->setEnabled(true);
    fillEditFields();
  }
}


void PlayerWindow::onPlaylistRowDoubleClick() {
  playback(PLAYBACK::PLAY); // clicked station index was be set from single click slot
}


// this function have qt bug (emite signal activated)
void PlayerWindow::onTrayIconClick(QSystemTrayIcon::ActivationReason r) {
  if (r != QSystemTrayIcon::Trigger && r != QSystemTrayIcon::DoubleClick) return;

  if (!m_isTrayWasClicked) { // first click on tray icon
    m_isTrayWasClicked = true;
    Delay(300); // delay after first click on tray icon
  } else { // second click on tray icon
    m_isTrayWasClicked = false;
    toggleWindowVisibleAction();
  }
  if (m_isTrayWasClicked) {
    m_isTrayWasClicked = false;
    if (m_isPlay) playback(PLAYBACK::STOP);
    else playback(PLAYBACK::PLAY);
  }
}


void PlayerWindow::onVolumeSliderChange(int value) {
  (value == 0) ? m_isMuted = true : m_isMuted = false;
  m_playerHandler->setVolume(value);
  setTrayIcon();
  if (!m_isMuted && value != m_volume) m_volume = value;
}

// private methods ============================================================

void PlayerWindow::setThemeColor(THEME themeColor) {
  m_themeColor = themeColor;

  if (m_themeColor == THEME::LIGHT) {
    m_iconsPath = ":/icons/light-theme/"; // path to icons from Resources.qrc
    m_ui->lightThemeRadioButton->setChecked(true);
    m_ui->darkThemeRadioButton->setChecked(false);
  } else {
    m_iconsPath = ":/icons/dark-theme/";
    m_ui->lightThemeRadioButton->setChecked(false);
    m_ui->darkThemeRadioButton->setChecked(true);
  }

  // tabs icons
  QIcon icon = QIcon::fromTheme("media-playback-start", QIcon(m_iconsPath + "radio.svg"));
  m_ui->tabWidget->setTabIcon(0, TransformIcon(icon, 22, 22, 90));
  icon = QIcon::fromTheme("document-edit", QIcon(m_iconsPath + "edit.svg"));
  m_ui->tabWidget->setTabIcon(1, TransformIcon(icon, 22, 22, 90));
  icon = QIcon::fromTheme("configure", QIcon(m_iconsPath + "config.svg"));
  m_ui->tabWidget->setTabIcon(2, TransformIcon(icon, 22, 22, 90));

  // buttons icons
  m_ui->playButton->setIcon(QIcon::fromTheme("media-playback-start", QIcon(m_iconsPath + "play.svg")));
  m_ui->prevPlayButton->setIcon(QIcon::fromTheme("media-skip-backward", QIcon(m_iconsPath + "backward.svg")));
  m_ui->nextPlayButton->setIcon(QIcon::fromTheme("media-skip-forward", QIcon(m_iconsPath + "forward.svg")));
  m_ui->stopButton->setIcon(QIcon::fromTheme("media-playback-stop", QIcon(m_iconsPath + "stop.svg")));
  m_ui->recordButton->setIcon(QIcon::fromTheme("media-record", QIcon(m_iconsPath + "record.svg")));
  m_ui->searchButton->setIcon(QIcon::fromTheme("search", QIcon(m_iconsPath + "search.svg")));
  m_ui->addPlaylistButton->setIcon(QIcon::fromTheme("list-add", QIcon(m_iconsPath + "add-playlist.svg")));
  m_ui->addStationButton->setIcon(QIcon::fromTheme("add", QIcon(m_iconsPath + "add-station.svg")));
  m_ui->deleteStationButton->setIcon(QIcon::fromTheme("edit-delete", QIcon(m_iconsPath + "delete.svg")));
  m_ui->editStationButton->setIcon(QIcon::fromTheme("document-edit", QIcon(m_iconsPath + "edit-row.svg")));
  m_ui->saveStationButton->setIcon(QIcon::fromTheme("document-save", QIcon(m_iconsPath + "save.svg")));

  setTrayIcon();
  setWindowIcon(QIcon(m_iconsPath + "qrudio.svg"));

  SettingsHandler::getInstance().setSetting("", "theme_color", m_themeColor);
}


void PlayerWindow::setTrayIcon() {
  if (!m_isPlay) m_trayIcon->setIcon(QIcon(m_iconsPath + "tray-off.svg")); // order is important
  else if (m_isMuted) m_trayIcon->setIcon(QIcon(m_iconsPath + "tray-mute.svg"));
  else if (m_isPlay) m_trayIcon->setIcon(QIcon(m_iconsPath + "tray-on.svg"));
}

// playback -------------------------------------------------------------------

void PlayerWindow::playback(PLAYBACK playbackState) {
  switch (playbackState) {
    case PLAYBACK::PLAY:
    case PLAYBACK::FORWARD:
    case PLAYBACK::BACKWARD:
      if (m_playerHandler->isPlaylistEmpty()) break; // dont change state if playlist is empty
      if (playbackState == PLAYBACK::PLAY) m_playerHandler->play();
      if (playbackState == PLAYBACK::BACKWARD) m_playerHandler->playPrev();
      if (playbackState == PLAYBACK::FORWARD) m_playerHandler->playNext();
      m_isPlay = true;
      m_ui->playButton->hide();
      m_ui->stopButton->show();
//      m_ui->stationsTreeView->selectRow(m_playerHandler->getSelectedIndex());
      setTrayIcon();
      break;
    case PLAYBACK::STOP:
      m_playerHandler->stop();
      m_isPlay = false;
      m_ui->stopButton->hide();
      m_ui->playButton->show();
      setTrayIcon();
    default:
      break;
  }
}

// ----------------------------------------------------------------------------

void PlayerWindow::toggleEditState() {
  fillEditFields();
  if (m_editState == EDIT::ADD || m_editState == EDIT::NONE) {
    m_ui->categoryEdit->setEnabled(m_editState == EDIT::ADD);
    m_ui->stationNameEdit->setEnabled(m_editState == EDIT::ADD);
    m_ui->stationUrlEdit->setEnabled(m_editState == EDIT::ADD);
  }
  m_ui->addPlaylistButton->setEnabled(m_editState == EDIT::NONE);
  m_ui->addStationButton->setEnabled(m_editState == EDIT::ADD || m_editState == EDIT::NONE);
  m_ui->editStationButton->setEnabled(m_editState == EDIT::EDIT || m_editState == EDIT::NONE);
  m_ui->saveStationButton->setEnabled(m_editState == EDIT::ADD || m_editState == EDIT::EDIT);
  m_ui->deleteStationButton->setEnabled(false);
}


void PlayerWindow::fillEditFields() {
  if (m_editState != EDIT::NONE) {
    QModelIndex index = m_ui->stationsTreeView->currentIndex();
    if (index.isValid()) {
      bool isCategory = static_cast<PlaylistItem*>(index.internalPointer())->isCategory();
      if (isCategory) {
        m_ui->categoryEdit->setText(m_ui->stationsTreeView->model()->data(index.siblingAtColumn(0)).toString());
      } else {
        m_ui->categoryEdit->setText(m_ui->stationsTreeView->model()->data(m_ui->stationsTreeView->model()->parent(index).siblingAtColumn(0)).toString());
      }
      if (m_editState == EDIT::EDIT) {
        if (isCategory) {
          m_ui->stationNameEdit->clear();
          m_ui->stationUrlEdit->clear();
        } else {
          m_ui->stationNameEdit->setText(m_ui->stationsTreeView->model()->data(index.siblingAtColumn(0)).toString());
          m_ui->stationUrlEdit->setText(m_ui->stationsTreeView->model()->data(index.siblingAtColumn(1)).toString());
        }
        m_ui->categoryEdit->setEnabled(true);
        m_ui->stationNameEdit->setEnabled(!isCategory);
        m_ui->stationUrlEdit->setEnabled(!isCategory);
      }
    }
  } else {
    m_ui->categoryEdit->clear();
    m_ui->stationNameEdit->clear();
    m_ui->stationUrlEdit->clear();
  }
}
