// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "PlayerHandler.hpp"


PlayerHandler::PlayerHandler(QObject *parent) : QObject(parent) {
  m_dataBaseHandler = new DataBaseHandler();

  // get stations from database
  QVector<DataRecord*>* recordsList = m_dataBaseHandler->getRecordsList(DEFAULT_SETTINGS.stationsTableName);
  for (auto it = recordsList->begin(); it != recordsList->end(); it++) {
    if ((*it)->isValid()) addRowToPlaylist((*it)->getField(), (*it)->getValue().toString());
  }

  m_player = new QMediaPlayer(nullptr, QMediaPlayer::StreamPlayback); // PLAYER
  setVolume(0);
}


PlayerHandler::~PlayerHandler() {
  if (m_dataBaseHandler) delete m_dataBaseHandler;
  if (m_player) delete m_player; // PLAYER
}

// public methods =============================================================

void PlayerHandler::addStation(const QString &stationName, const QString &stationUrl) {
  addRowToPlaylist(stationName, stationUrl);
  m_dataBaseHandler->addRecord(DEFAULT_SETTINGS.stationsTableName, DataRecord(stationName, stationUrl));
}


void PlayerHandler::updateStation(const QModelIndex &index) {
//  m_playlistModel.itemFromIndex(index)->child(0, 0)->text(); // get station name
}


void PlayerHandler::deleteStation(const QModelIndex &index) {
//  m_playlistModel.itemFromIndex(index)->child(0, 0)->text(); // get station name
}


QStandardItemModel* PlayerHandler::getPlaylistModel() {
  return &m_playlistModel;
}

// private slots ==============================================================

int PlayerHandler::getPlaylistIndex() {
  return m_currentPlaylistIndex;
}


void PlayerHandler::setPlaylistIndex(int index) {
  if (index >= 0 && index < m_playlistRowsCount) {
    m_currentPlaylistIndex = index;
    m_isPlaylistIndexChanged = true;
  }
}


bool PlayerHandler::isPlaylistEmpty() {
  return m_playlistRowsCount == 0;
}


void PlayerHandler::play() {
  if (!m_isPlaying || m_isPlaylistIndexChanged) {
    m_isPlaying = true;
    m_isPlaylistIndexChanged = false;
    QUrl url = getCurrentUrl();
    if (!url.isEmpty()) {
      m_player->setMedia(QMediaContent(url));
      m_player->play();
    }
  }
}


void PlayerHandler::playPrev() {
  m_isPlaying = false;
  m_currentPlaylistIndex--;
  if (m_currentPlaylistIndex < 0) {
    m_currentPlaylistIndex = m_playlistRowsCount - 1;
  }
  play();
}


void PlayerHandler::playNext() {
  m_isPlaying = false;
  m_currentPlaylistIndex++;
  if (m_currentPlaylistIndex == m_playlistRowsCount) {
    m_currentPlaylistIndex = 0;
  }
  play();
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


//void PlayerHandlerHandler::onTrackMetaDataChange() {
//  m_trackMetaData.trackTitle = "unknown";
//  m_trackMetaData.sample = 0;
//  m_trackMetaData.bitrate = 0;

//  if (m_PlayerHandler->isMetaDataAvailable()) {
//    QString trackTitle = m_PlayerHandler->metaData(QMediaMetaData::Title).toString();
//    int sample = m_PlayerHandler->metaData(QMediaMetaData::SampleRate).toInt();
//    int bitrate = m_PlayerHandler->metaData(QMediaMetaData::AudioBitRate).toInt();

//    if (!trackTitle.isEmpty()) m_trackMetaData.trackTitle = trackTitle;
//    if (sample != 0) m_trackMetaData.sample = sample;
//    if (bitrate != 0) m_trackMetaData.bitrate = bitrate;

//    qDebug() << "md ";
//  }
//  emit trackMetaDataChanged(&m_trackMetaData);
//}

// private methods ============================================================

QUrl PlayerHandler::getCurrentUrl() {
  if (!isPlaylistEmpty()) return QUrl(m_playlistModel.item(m_currentPlaylistIndex, 1)->text());
  return QUrl();
}


void PlayerHandler::addRowToPlaylist(const QString &stationName, const QString &stationUrl) {
  QList<QStandardItem*> row = { new QStandardItem(stationName), new QStandardItem(stationUrl) };
  m_playlistModel.appendRow(row);
  m_playlistRowsCount++;
}

