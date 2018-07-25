// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "PlayerHandler.hpp"


PlayerHandler::PlayerHandler(QObject *parent) : QObject(parent) {
  m_dataBaseHandler = new DataBaseHandler();
  // get stations from database
  QVector<DataRecord*>* recordsList = m_dataBaseHandler->getRecordsList(DEFAULT_SETTINGS.stationsTableName);
  for (auto it = recordsList->begin(); it != recordsList->end(); it++) {
    if ((*it)->isValid()) this->addRowToPlaylist(**it);
  }
  m_player = new QMediaPlayer(nullptr, QMediaPlayer::StreamPlayback);
  this->setVolume(0);
}


PlayerHandler::~PlayerHandler() {
  if (m_dataBaseHandler) delete m_dataBaseHandler;
  if (m_player) delete m_player;
}

// public methods =============================================================

void PlayerHandler::addStation(const DataRecord &dataRecord) {
  if (!dataRecord.isValid()) return;
  if (m_dataBaseHandler->addRecord(DEFAULT_SETTINGS.stationsTableName, dataRecord)) {
    this->addRowToPlaylist(dataRecord);
  }
}


void PlayerHandler::deleteStation(const QModelIndex &index) {
  QString field = m_playlistModel.itemFromIndex(index.siblingAtColumn(0))->text();
  if (m_dataBaseHandler->deleteRecord(DEFAULT_SETTINGS.stationsTableName, DataRecord(field, ""))) {
    m_playlistModel.removeRow(index.row());
    m_playlistRowsCount--;
    m_currentSelectedIndex--;
  }
}


void PlayerHandler::updateStation(const QModelIndex &index) {
//  m_playlistModel.itemFromIndex(index)->child(0, 0)->text(); // get station name
}


QStandardItemModel* PlayerHandler::getPlaylistModel() {
  return &m_playlistModel;
}

// private slots ==============================================================

int PlayerHandler::getSelectedIndex() {
  return m_currentSelectedIndex;
}


int PlayerHandler::getPlayedIndex() {
  return m_currentPlayedIndex;
}


void PlayerHandler::setSelectedIndex(int index) {
  if (index >= 0 && index < m_playlistRowsCount) {
    m_currentSelectedIndex = index;
    m_isPlaylistIndexChanged = true;
  }
}


bool PlayerHandler::isPlaylistEmpty() {
  return m_playlistRowsCount < 1;
}

// playback -------------------------------------------------------------------

void PlayerHandler::play() {
  if (!m_isPlaying || m_isPlaylistIndexChanged) {
    if (!isPlaylistEmpty()) {
      m_isPlaying = true;
      m_isPlaylistIndexChanged = false;
      m_currentPlayedIndex = m_currentSelectedIndex;
      QUrl url(m_playlistModel.item(m_currentSelectedIndex, 1)->text());
      m_player->setMedia(QMediaContent(url));
      m_player->play();
    }
  }
}


void PlayerHandler::playPrev() {
  m_isPlaying = false;
  m_currentSelectedIndex--;
  if (m_currentSelectedIndex < 0) m_currentSelectedIndex = m_playlistRowsCount - 1;
  this->play();
}


void PlayerHandler::playNext() {
  m_isPlaying = false;
  m_currentSelectedIndex++;
  if (m_currentSelectedIndex == m_playlistRowsCount) m_currentSelectedIndex = 0;
  this->play();
}


void PlayerHandler::stop() {
  if (m_isPlaying) {
    m_isPlaying = false;
    m_player->stop();
  }
}


void PlayerHandler::record() {}


void PlayerHandler::setVolume(int value) {
  m_volume = value;
  m_player->setVolume(m_volume);
}

// private methods ============================================================

void PlayerHandler::addRowToPlaylist(const DataRecord &dataRecord) {
  QList<QStandardItem*> row = { new QStandardItem(dataRecord.getField()), new QStandardItem(dataRecord.getValue().toString()) };
  m_playlistModel.appendRow(row);
  m_playlistRowsCount++;
}

