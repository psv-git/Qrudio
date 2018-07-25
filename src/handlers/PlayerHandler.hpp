// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef PLAYERHANDLER_HPP
#define PLAYERHANDLER_HPP

#include <QStandardItemModel>
#include "GlobalClasses.hpp"
#include "DataBaseHandler.hpp"
#include "TrackMetaData.hpp"

//#include <QObject>
//#include <QByteArray>
//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QNetworkReply>
#include <QMediaPlayer>


class PlayerHandler : QObject {
Q_OBJECT

public:
  explicit PlayerHandler(QObject *parent = nullptr);
  ~PlayerHandler();

  void addStation(const DataRecord &dataRecord);
  void deleteStation(const QModelIndex &index);
  void updateStation(const QModelIndex &index);
  QStandardItemModel* getPlaylistModel();

  int getSelectedIndex();
  int getPlayedIndex();
  void setSelectedIndex(int index);
  bool isPlaylistEmpty();

  void play();
  void playPrev();
  void playNext();
  void stop();
  void record();
  void setVolume(int volume);

private:
  DataBaseHandler *m_dataBaseHandler = nullptr; // must be instantiate in runtime
  QMediaPlayer *m_player = nullptr;

  bool m_isPlaying = false;
  bool m_isPlaylistIndexChanged = false;
  int m_volume = 0;

  QStandardItemModel m_playlistModel;
  int m_playlistRowsCount = 0;
  int m_currentSelectedIndex = 0;
  int m_currentPlayedIndex = 0;

  void addRowToPlaylist(const DataRecord &dataRecord);

};


#endif // PLAYERHANDLER_HPP
