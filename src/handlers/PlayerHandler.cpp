// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "PlayerHandler.hpp"


PlayerHandler::PlayerHandler(QObject *parent) : QObject(parent) {
  m_dataBaseHandler = new DataBaseHandler();

  // get stations from database
//  this->addRowToPlaylist(DataRecord("Radio title", "Radio url"));
//  m_playlistModel.item(0, 0)->setSelectable(false);
//  m_playlistModel.item(0, 0)->setTextAlignment(Qt::AlignHCenter);
//  QVector<DataRecord*>* recordsList = m_dataBaseHandler->getRecordsList(DEFAULT_SETTINGS.stationsTableName);
//  for (auto it = recordsList->begin(); it != recordsList->end(); it++) {
//    if ((*it)->isValid()) this->addRowToPlaylist(**it);
//  }
  // TODO: sorting here

  m_player = new QMediaPlayer(nullptr, QMediaPlayer::StreamPlayback);
  this->setVolume(0);

  addCategory("test1");
  addCategory("test2");
  addCategory("test3");
}


PlayerHandler::~PlayerHandler() {
  if (m_dataBaseHandler) delete m_dataBaseHandler;
  if (m_player) delete m_player;
}

// public methods =============================================================

bool PlayerHandler::addCategory(const QString &categoryTitle) {
  PlaylistItem *category = new PlaylistItem(categoryTitle);
  PlaylistItem *station = new PlaylistItem(StationRecord(categoryTitle, "st", "url"), category);
  category->addChild(station);
  return m_playlistModel.addRow(*category);
}


bool PlayerHandler::deleteCategory(const QModelIndex &index) {
  return false;
}


bool PlayerHandler::addStation(const StationRecord &stationRecord) {
//  if (!stationRecord.isValid()) return;
//  if (m_dataBaseHandler->addRecord(DEFAULT_SETTINGS.stationsTableName, dataRecord)) {
//    this->addRowToPlaylist(dataRecord);
//  }

  return false;
}


bool PlayerHandler::deleteStation(const QModelIndex &index) {
//  QString field = m_playlistModel.itemFromIndex(index.siblingAtColumn(0))->text();
//  if (m_dataBaseHandler->deleteRecord(DEFAULT_SETTINGS.stationsTableName, DataRecord(field, ""))) {
//    this->deleteRowFromPlaylist(index.row());
//  }
  return false;
}


bool PlayerHandler::updateStation(const QModelIndex &index) {
//  m_playlistModel.itemFromIndex(index)->child(0, 0)->text(); // get station name
  return false;
}


PlaylistModel* PlayerHandler::getPlaylistModel() {
  return &m_playlistModel;
}


bool PlayerHandler::isPlaylistEmpty() {
  return m_playlistRowsCount < 1;
}


int PlayerHandler::getSelectedIndex() {
  return m_currentSelectedIndex;
}


int PlayerHandler::getPlayedIndex() {
  return m_currentPlayedIndex;
}


void PlayerHandler::setSelectedIndex(int index) {
//  if (index < 0) {
//    if (m_playlistRowsCount > 0) m_currentSelectedIndex = m_playlistRowsCount - 1;
//    else m_currentSelectedIndex = 0;
//  } else if (index >= m_playlistRowsCount) {
//    m_currentSelectedIndex = 0;
//  } else {
//    m_currentSelectedIndex = index;
//  }
//  m_isPlaylistIndexChanged = true;
}

// playback -------------------------------------------------------------------

void PlayerHandler::play() {
//  if (!m_isPlaying || m_isPlaylistIndexChanged) {
//    if (!isPlaylistEmpty()) {
//      m_isPlaying = true;
//      m_isPlaylistIndexChanged = false;
//      m_currentPlayedIndex = m_currentSelectedIndex;
//      m_player->setMedia(QMediaContent(QUrl(m_playlistModel.item(m_currentPlayedIndex, 1)->text())));
//      m_player->play();
//    }
//  }
}


void PlayerHandler::playPrev() {
//  m_isPlaying = false;
//  this->setSelectedIndex(m_currentSelectedIndex - 1);
//  this->play();
}


void PlayerHandler::playNext() {
//  m_isPlaying = false;
//  this->setSelectedIndex(m_currentSelectedIndex + 1);
//  this->play();
}


void PlayerHandler::stop() {
//  if (m_isPlaying) {
//    m_isPlaying = false;
//    m_player->stop();
//  }
}


void PlayerHandler::record() {}


void PlayerHandler::setVolume(int value) {
//  if (value < 0) m_volume = 0;
//  else if (value > 100) m_volume = 100;
//  else m_volume = value;
//  m_player->setVolume(m_volume);
}

// private methods ============================================================

//void PlayerHandler::addRowToPlaylist(const DataRecord &dataRecord) {
//  QList<QStandardItem*> row = { new QStandardItem(dataRecord.getField()), new QStandardItem(dataRecord.getValue().toString()) };
//  m_playlistModel.appendRow(row);
//  m_playlistRowsCount++;
//}


//void PlayerHandler::deleteRowFromPlaylist(int index) {
//  m_playlistModel.removeRow(index);
//  m_playlistRowsCount--;
//  if (m_playlistRowsCount > 0) {
//    if (m_currentSelectedIndex == m_playlistRowsCount) m_currentSelectedIndex--;
//  }
//}

