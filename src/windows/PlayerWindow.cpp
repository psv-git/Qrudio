// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "PlayerWindow.hpp"
#include "ui_PlayerWindow.h"


PlayerWindow::PlayerWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::PlayerWindow) {
  m_playerHandler = new PlayerHandler();

  // get settings -------------------------------------------------------------

  m_isPlay = SettingsHandler::getInstance().getSetting("", "is_play", false).toBool();
  m_themeColor = qvariant_cast<THEME>(SettingsHandler::getInstance().getSetting("", "theme_color", LIGHT));
  m_isRunOnTray = SettingsHandler::getInstance().getSetting("", "run_on_tray", false).toBool();
  m_volume = SettingsHandler::getInstance().getSetting("", "volume", 0).toInt();
  if (m_volume < 0 || m_volume > 100) m_volume = 0;

  // setup --------------------------------------------------------------------

  m_ui->setupUi(this);
  m_trayIcon = new QSystemTrayIcon(this);
  m_trayContextMenu = new QMenu("&Menu");
  m_trayContextMenu->addAction("&Show/Hide", this, SLOT(toggleWindowVisibleAction()));
  m_trayContextMenu->addAction("&Mute/Unmute", this, SLOT(muteAction()));
  m_trayContextMenu->addAction("&Exit", this, SLOT(exitAction()));
  m_trayIcon->setContextMenu(m_trayContextMenu);

  setThemeColor(m_themeColor);
  m_ui->runOnTrayCheckBox->setChecked(m_isRunOnTray);
  m_ui->stationsTableView->setModel(m_playerHandler->getPlaylistModel()); // set playlist model to table view model
  m_ui->stationsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//  m_playerHandler->addStation("Nashe", "http://nashe1.hostingradio.ru/nashe-128.mp3");
//  m_playerHandler->addStation("Europa+", "http://ep128.streamr.ru");
  m_ui->stationsTableView->hideColumn(1); // hide url column
  m_ui->stopButton->hide();

  // signals ------------------------------------------------------------------

  connect(m_ui->playButton, SIGNAL(released()), this, SLOT(onPlayButtonRelease()));
  connect(m_ui->prevPlayButton, SIGNAL(released()), this, SLOT(onPlayButtonRelease()));
  connect(m_ui->nextPlayButton, SIGNAL(released()), this, SLOT(onPlayButtonRelease()));
  connect(m_ui->stopButton, SIGNAL(released()), this, SLOT(onStopButtonRelease()));
  connect(m_ui->recordButton, SIGNAL(released()), this, SLOT(onRecordButtonRelease()));
  connect(m_ui->searchButton, SIGNAL(released()), this, SLOT(onSearchButtonRelease()));
  connect(m_ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeSliderChange(int)));

  connect(m_ui->addButton, SIGNAL(released()), this, SLOT(onAddButtonRelease()));
  connect(m_ui->deleteButton, SIGNAL(released()), this, SLOT(onDeleteButtonRelease()));
  connect(m_ui->editButton, SIGNAL(released()), this, SLOT(onEditButtonRelease()));
  connect(m_ui->saveButton, SIGNAL(released()), this, SLOT(onSaveButtonRelease()));

  connect(m_ui->lightThemeRadioButton, SIGNAL(released()), this, SLOT(onThemeButtonRelease()));
  connect(m_ui->darkThemeRadioButton, SIGNAL(released()), this, SLOT(onThemeButtonRelease()));
  connect(m_ui->runOnTrayCheckBox, SIGNAL(toggled(bool)), this, SLOT(onRunOnTrayBoxClick(bool)));

  connect(m_ui->stationsTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onStationRowClick(QModelIndex)));
  connect(m_ui->stationsTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onStationRowDoubleClick(QModelIndex)));

  connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onTrayIconClick(QSystemTrayIcon::ActivationReason)));

//  connect(m_playerHandler, SIGNAL(trackMetaDataChanged(TrackMetaData*)), this, SLOT(setTrackMetaData(TrackMetaData*)));
//  connect(m_playerHandler, SIGNAL(buffered()), this, SLOT(onBuffered()));
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
  if (m_isPlay) playback(STATE::PLAY);
  if (!m_isRunOnTray) this->show();
  m_trayIcon->show();
}

// events =====================================================================

void PlayerWindow::closeEvent(QCloseEvent *ev) {
  if (m_isExit) { // close application by system tray
    m_trayIcon->hide();
    SettingsHandler::getInstance().saveSettings();
    QApplication::quit();
  } else { // hide/show window
    ev->ignore();
    toggleWindowVisibleAction();
  }
}

// private slots ==============================================================

void PlayerWindow::toggleWindowVisibleAction() {
  if (this->isVisible()) this->hide();
  else this->show();
}


// close application by system tray
void PlayerWindow::exitAction() {
  m_isExit = true;
  this->close(); // invoke close event
}


void PlayerWindow::muteAction() {
  if (!m_isPlay) return;
  if (m_isMuted) m_ui->volumeSlider->setValue(m_volume);
  else m_ui->volumeSlider->setValue(0);
}


void PlayerWindow::onPlayButtonRelease() {
  if (sender() == m_ui->playButton) {
    if (!m_isPlay) playback(STATE::PLAY);
  } else if (sender() == m_ui->prevPlayButton) {
    playback(STATE::BACKWARD);
  } else if (sender() == m_ui->nextPlayButton) {
    playback(STATE::FORWARD);
  }
}


void PlayerWindow::onStopButtonRelease() {
  if (m_isPlay) playback(STATE::STOP);
}


void PlayerWindow::onRecordButtonRelease() {}


void PlayerWindow::onSearchButtonRelease() {
  QString trackTitle = m_ui->trackLabel->text();
  if (!trackTitle.isEmpty()) OpenUrl("https://www.google.ru/search?q=" + trackTitle);
}


void PlayerWindow::onAddButtonRelease() {
  if (!m_ui->stationNameEdit->text().isEmpty() && !m_ui->stationUrlEdit->text().isEmpty()) {
    // TODO: check to exist
    m_playerHandler->addStation(m_ui->stationNameEdit->text(), m_ui->stationUrlEdit->text());
  }
}


void PlayerWindow::onDeleteButtonRelease() {
  deleteStation(); // !!!!
  m_ui->editButton->setDisabled(true);
  m_ui->deleteButton->setDisabled(true);
}


void PlayerWindow::onEditButtonRelease() {
  QModelIndex currentIndex = m_ui->stationsTableView->currentIndex();
  m_ui->stationNameEdit->setText(m_ui->stationsTableView->model()->data(currentIndex.siblingAtColumn(0)).toString());
  m_ui->stationUrlEdit->setText(m_ui->stationsTableView->model()->data(currentIndex.siblingAtColumn(1)).toString());
  m_ui->saveButton->setEnabled(true);
  m_ui->deleteButton->setDisabled(true);
}


void PlayerWindow::onSaveButtonRelease() {
  updateStation(m_ui->stationNameEdit->text(), m_ui->stationUrlEdit->text());
  m_ui->stationNameEdit->clear();
  m_ui->stationUrlEdit->clear();
  m_ui->saveButton->setDisabled(true);
  m_ui->editButton->setDisabled(true);
}


void PlayerWindow::onStationRowClick(const QModelIndex &index) {
  m_playerHandler->setPlaylistIndex(index.row());
  if (m_ui->editTab->isVisible()) {
    m_ui->editButton->setEnabled(true);
    m_ui->deleteButton->setEnabled(true);
  }
}


void PlayerWindow::onStationRowDoubleClick(const QModelIndex &index) {
  playback(STATE::PLAY); // clicked station index was setted from single click slot
}


void PlayerWindow::onThemeButtonRelease() {
  QObject *obj = sender();
  if (obj == m_ui->lightThemeRadioButton) {
    if (m_themeColor != THEME::LIGHT) setThemeColor(LIGHT);
  } else {
    if (m_themeColor != THEME::DARK) setThemeColor(DARK);
  }
}


void PlayerWindow::onVolumeSliderChange(int value) {
  (value == 0) ? m_isMuted = true : m_isMuted = false;
  m_playerHandler->setVolume(value);
  setTrayIcon();
  if (!m_isMuted && value != m_volume) m_volume = value;
}


void PlayerWindow::onRunOnTrayBoxClick(bool checked) {
  if (checked == m_isRunOnTray) return;
  m_isRunOnTray = checked;
  SettingsHandler::getInstance().setSetting("", "run_on_tray", m_isRunOnTray);
}


void PlayerWindow::onTrayIconClick(QSystemTrayIcon::ActivationReason r) {
  if (r != QSystemTrayIcon::Trigger && r != QSystemTrayIcon::DoubleClick) return;
  if (!m_isTrayWasClicked) { // first click on tray icon
    m_isTrayWasClicked = true;
    Delay(200); // delay after first click on tray icon
  } else { // second click on tray icon
    m_isTrayWasClicked = false;
    toggleWindowVisibleAction();
  }
  if (m_isTrayWasClicked) {
    m_isTrayWasClicked = false;
    if (m_isPlay) playback(STATE::STOP);
    else playback(STATE::PLAY);
  }
}


//void PlayerWindow::setTrackMetaData(TrackMetaData *trackMetaData) {
//  m_ui->trackLabel->setText(trackMetaData->getTrackTitle());
//  m_ui->sampleValueLabel->setText(trackMetaData->getSampleRate());
//  m_ui->bitrateValueLabel->setText(trackMetaData->getBitRate());
//}

// private methods ============================================================

void PlayerWindow::setThemeColor(THEME themeColor) {
  m_themeColor = themeColor;

  if (themeColor == LIGHT) {
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
  icon = QIcon::fromTheme("document-edit", QIcon(m_iconsPath + "edit-2.svg"));
  m_ui->tabWidget->setTabIcon(1, TransformIcon(icon, 22, 22, 90));
  icon = QIcon::fromTheme("configure", QIcon(m_iconsPath + "settings.svg"));
  m_ui->tabWidget->setTabIcon(2, TransformIcon(icon, 22, 22, 90));

  // buttons icons
  m_ui->playButton->setIcon(QIcon::fromTheme("media-playback-start", QIcon(m_iconsPath + "play.svg")));
  m_ui->prevPlayButton->setIcon(QIcon::fromTheme("media-skip-backward", QIcon(m_iconsPath + "backward.svg")));
  m_ui->nextPlayButton->setIcon(QIcon::fromTheme("media-skip-forward", QIcon(m_iconsPath + "forward.svg")));
  m_ui->stopButton->setIcon(QIcon::fromTheme("media-playback-stop", QIcon(m_iconsPath + "stop.svg")));
  m_ui->recordButton->setIcon(QIcon::fromTheme("media-record", QIcon(m_iconsPath + "record.svg")));
  m_ui->searchButton->setIcon(QIcon::fromTheme("search", QIcon(m_iconsPath + "search.svg")));
  m_ui->addButton->setIcon(QIcon::fromTheme("list-add", QIcon(m_iconsPath + "add.svg")));
  m_ui->deleteButton->setIcon(QIcon::fromTheme("edit-delete", QIcon(m_iconsPath + "delete.svg")));
  m_ui->editButton->setIcon(QIcon::fromTheme("document-edit", QIcon(m_iconsPath + "edit-1.svg")));
  m_ui->saveButton->setIcon(QIcon::fromTheme("document-save", QIcon(m_iconsPath + "save.svg")));

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

void PlayerWindow::playback(STATE state) {
  switch (state) {
    case STATE::PLAY:
    case STATE::FORWARD:
    case STATE::BACKWARD:
      if (m_playerHandler->isPlaylistEmpty()) break; // dont change state if playlist is empty
      if (state == STATE::PLAY) m_playerHandler->play();
      if (state == STATE::BACKWARD) m_playerHandler->playPrev();
      if (state == STATE::FORWARD) m_playerHandler->playNext();
      m_isPlay = true;
      m_ui->playButton->hide();
      m_ui->stopButton->show();
      m_ui->stationsTableView->selectRow(m_playerHandler->getPlaylistIndex());
      setTrayIcon();
      break;
    case STATE::STOP:
      m_playerHandler->stop();
      m_isPlay = false;
      m_ui->stopButton->hide();
      m_ui->playButton->show();
      setTrayIcon();
    default:
      break;
  }
}

// stations -------------------------------------------------------------------

//void PlayerWindow::refreshStationsTable() {
//  m_ui->stationsTableWidget->clear();

//  // Создаем столбцы в представлении
//  m_ui->stationsTableWidget->insertColumn(0);
//  m_ui->stationsTableWidget->insertColumn(1);
//  m_ui->stationsTableWidget->insertColumn(2);
//  m_ui->stationsTableWidget->hideColumn(0); // hide stations id
//  m_ui->stationsTableWidget->hideColumn(2); // hide stations url
//  m_ui->stationsTableWidget->horizontalHeader()->setStretchLastSection(true);
//  m_ui->stationsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

//  QVector<DataRecord*> *recordsList = m_dataBaseHandler->getRecordsList(DEFAULT_SETTINGS.stationsTableName);
//  QString stationId, stationName, stationUrl;
//  for (int i = 0; i < recordsList->size(); i++) {
//    stationId = QString::number(recordsList->at(i)->getId());
//    stationName = recordsList->at(i)->getField();
//    stationUrl = recordsList->at(i)->getValue().toString();

//    m_ui->stationsTableWidget->insertRow(i);
//    m_ui->stationsTableWidget->setVerticalHeaderItem(i, QTableWidgetItem());
//    m_ui->stationsTableWidget->setItem(i, 0, QTableWidgetItem(stationId));
//    m_ui->stationsTableWidget->setItem(i, 1, QTableWidgetItem(stationName));
//    m_ui->stationsTableWidget->setItem(i, 2, QTableWidgetItem(stationUrl));
//  }

//  // Визуальная часть текущего трека
//  for (int i = 0; i < m_ui->stationsTableWidget->rowCount(); i++) {
//    m_ui->stationsTableWidget->setVerticalHeaderItem(i, QTableWidgetItem());
//  }

//  // Стобец на всю ширину таблицы
//  m_ui->stationsTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
//  if (currentPlay < countRow) { // !!!!
//    if (m_isPlay) {
//      QTableWidgetItem *rowItem = new QTableWidgetItem();
//      rowItem->setIcon(QIcon::fromTheme("media-playback-start", QIcon(":/icons/icons/16x16/play.svg"));
//      m_ui->stationsTableWidget->setVerticalHeaderItem(currentPlay, rowItem);
//    }else {
//      QTableWidgetItem *rowItem = new QTableWidgetItem();
//      rowItem->setSizeHint(QSize(24, 24));
//      m_ui->stationsTableWidget->setVerticalHeaderItem(currentPlay, rowItem);
//    }
//  }
//}


bool PlayerWindow::addStation(const QString &stationName, const QString &stationUrl) {
  return false;
}


bool PlayerWindow::deleteStation() {
  return false;
}


bool PlayerWindow::updateStation(const QString &stationName, const QString &stationUrl) {
  return false;
}
