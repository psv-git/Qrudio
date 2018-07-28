// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "PlayerHandler.hpp"


PlayerHandler::PlayerHandler(QObject *parent) : QObject(parent) {
  m_dataBaseHandler = new DataBaseHandler();

  QList<StationRecord*>* stationsList = m_dataBaseHandler->getRecordsList();
  for (auto it = stationsList->begin(); it != stationsList->end(); it++) {
    if ((*it)->isValid()) this->addStationToPlaylist(**it);
  }

//  addStationToPlaylist(StationRecord("test1", "station11", "url11"));
//  addStation(StationRecord("test2", "station2", "url2"));
//  addStation(StationRecord("test3", "station3", "url3"));


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
  PlaylistItem *item = m_playlistModel.getItemFromIndex(itemIndex);
  QModelIndex parentIndex = m_playlistModel.parent(itemIndex);
  if (m_playlistModel.deleteRow(itemIndex.row(), parentIndex)) {
    if (!item->isRoot() && !item->isCategory()) {
      return m_dataBaseHandler->deleteRecord(item->getData(2).toInt());
    }
  }
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

PlaylistItem* PlayerHandler::getCategory(const QVariant &categoryTitle) {
  for (int i = 0; i < m_categoriesList.size(); i++) {
    if (m_categoriesList.at(i)->getData(0) == categoryTitle) {
      return m_categoriesList.at(i);
    }
  }
  PlaylistItem *category = new PlaylistItem(categoryTitle);
  if (!m_playlistModel.addRow(category)) return nullptr;
  m_categoriesList.push_back(category);
  return category;
}


bool PlayerHandler::addStationToPlaylist(const StationRecord &record) {
  PlaylistItem *category = getCategory(record.getCategoryTitle());
  if (category) return category->addChild(PlaylistItem(record));
  else return false;
}


//void PlayerHandler::deleteRowFromPlaylist(int index) {
//  m_playlistModel.removeRow(index);
//  m_playlistRowsCount--;
//  if (m_playlistRowsCount > 0) {
//    if (m_currentSelectedIndex == m_playlistRowsCount) m_currentSelectedIndex--;
//  }
//}

