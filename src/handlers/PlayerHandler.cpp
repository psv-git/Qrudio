// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "PlayerHandler.hpp"


PlayerHandler::PlayerHandler(QObject *parent) : QObject(parent) {
  m_dataBaseHandler = new DataBaseHandler();

  QList<StationRecord*>* stationsList = m_dataBaseHandler->getRecordsList();
  for (auto it = stationsList->begin(); it != stationsList->end(); it++) {
    if ((*it)->isValid()) this->addStationToPlaylist(**it);
  }

  m_player = new QMediaPlayer(nullptr, QMediaPlayer::StreamPlayback);
  this->setVolume(0);
}


PlayerHandler::~PlayerHandler() {
  if (m_dataBaseHandler) delete m_dataBaseHandler;
  if (m_player) delete m_player;
}

// public methods =============================================================

bool PlayerHandler::addStation(const StationRecord &record) {
  if (!record.isValid()) return false;
  int id = m_dataBaseHandler->addRecord(record);
  if (id > 0) {
    const_cast<StationRecord&>(record).setId(id);
    this->addStationToPlaylist(record);
    return true;
  }
  return false;
}


bool PlayerHandler::deleteStation(const QModelIndex &itemIndex) {
  PlaylistItem *item = m_playlistModel.item(itemIndex);
  QModelIndex parentIndex = m_playlistModel.parent(itemIndex);

  if (item->isCategory()) {
    for (int row = 0; row < item->getChildCount(); row++) {
      PlaylistItem *childItem = item->getChild(row);
      deleteStationFromPlaylist(childItem->getData(2).toInt(), row, itemIndex);
    }
    m_categoriesMap.remove(item);
    return m_playlistModel.deleteRow(itemIndex.row(), parentIndex);
  }

  deleteStationFromPlaylist(item->getData(2).toInt(), itemIndex.row(), parentIndex);
  return true;
}


bool PlayerHandler::updateStation(const QModelIndex &itemIndex) {
//  m_playlistModel.itemFromIndex(index)->child(0, 0)->text(); // get station name
  return false;
}


PlaylistModel* PlayerHandler::getPlaylistModel() const {
  return const_cast<PlaylistModel*>(&m_playlistModel);
}


bool PlayerHandler::isPlaylistEmpty() const {
  return m_playlistRowsCount < 1;
}


const QModelIndex& PlayerHandler::getSelectedIndex() const {
  return m_currentSelectedIndex;
}


const QModelIndex& PlayerHandler::getPlayedIndex() const {
  return m_currentPlayedIndex;
}


void PlayerHandler::setSelectedIndex(const QModelIndex &index) {
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

QModelIndex PlayerHandler::getCategoryIndex(const QVariant &categoryTitle) {
  for (auto it = m_categoriesMap.begin(); it != m_categoriesMap.end(); it++) {
    if (it.key()->getData(0) == categoryTitle) return m_categoriesMap.value(it.key(), QModelIndex());
  }

  PlaylistItem *category = new PlaylistItem(categoryTitle);
  QModelIndex categoryIndex = m_playlistModel.addRow(category);
  if (categoryIndex.isValid()) m_categoriesMap.insert(category, categoryIndex);
  else delete category;

  return categoryIndex;
}


bool PlayerHandler::addStationToPlaylist(const StationRecord &record) {
  QModelIndex categoryIndex = getCategoryIndex(record.getCategoryTitle());
  if (categoryIndex.isValid()) {
    if (m_playlistModel.addRow(PlaylistItem(record), categoryIndex).isValid()) {
      m_playlistRowsCount++;
      return true;
    }
  }
  return false;
}


bool PlayerHandler::deleteStationFromPlaylist(int id, int row, const QModelIndex &parentIndex) {
  if (m_playlistModel.deleteRow(row, parentIndex)) {
    m_playlistRowsCount--;
    return m_dataBaseHandler->deleteRecord(id);
  }
  return false;
}
