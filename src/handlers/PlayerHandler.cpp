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

  PlaylistItem *category = addCategory("test1");
//  StationRecord *record = new StationRecord("", "station", "url");
//  PlaylistItem *station = new PlaylistItem(record, category);
//  category->addChild(station);
  if (category) category->addChild(PlaylistItem(StationRecord("", "station", "url"), category));

  addCategory("test2");
  addCategory("test3");
}


PlayerHandler::~PlayerHandler() {
  if (m_dataBaseHandler) delete m_dataBaseHandler;
  if (m_player) delete m_player;
}

// public methods =============================================================

bool PlayerHandler::addStation(const StationRecord &stationRecord) {
//  if (!stationRecord.isValid()) return;
//  if (m_dataBaseHandler->addRecord(dataRecord)) {
//    this->addRowToPlaylist(dataRecord);
//  }

  return false;
}


bool PlayerHandler::deleteStation(const QModelIndex &index) {
//  QString field = m_playlistModel.itemFromIndex(index.siblingAtColumn(0))->text();
//  if (m_dataBaseHandler->deleteRecord(DataRecord(field, ""))) {
//    this->deleteRowFromPlaylist(index.row());
//  }
  return false;
}


bool PlayerHandler::updateStation(const QModelIndex &index) {
//  m_playlistModel.itemFromIndex(index)->child(0, 0)->text(); // get station name
  return false;
}


PlaylistModel* PlayerHandler::getPlaylistModel() const {
  return const_cast<PlaylistModel*>(&m_playlistModel);
}


bool PlayerHandler::isPlaylistEmpty() const {
  return m_playlistRowsCount < 1;
}


int PlayerHandler::getSelectedIndex() const {
  return m_currentSelectedIndex;
}


int PlayerHandler::getPlayedIndex() const {
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

PlaylistItem* PlayerHandler::addCategory(const QString &categoryTitle) {
  PlaylistItem *category = new PlaylistItem(categoryTitle);
  if (m_playlistModel.addRow(category)) {
    m_categoriesList.push_back(category);
    return category;
  } else {
    return nullptr;
  }
}


void PlayerHandler::addRowToPlaylist(const StationRecord &dataRecord) {
//  m_playlistModel.appendRow(row);
//  m_playlistRowsCount++;

//  PlaylistItem *station = new PlaylistItem(StationRecord(categoryTitle, "st", "url"), category);
//  category->addChild(station);
}


//void PlayerHandler::deleteRowFromPlaylist(int index) {
//  m_playlistModel.removeRow(index);
//  m_playlistRowsCount--;
//  if (m_playlistRowsCount > 0) {
//    if (m_currentSelectedIndex == m_playlistRowsCount) m_currentSelectedIndex--;
//  }
//}

