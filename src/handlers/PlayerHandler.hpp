// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef PLAYERHANDLER_HPP
#define PLAYERHANDLER_HPP

#include "GlobalClasses.hpp"
#include "DataBaseHandler.hpp"
#include "PlaylistModel.hpp"

//#include "TrackMetaData.hpp"

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

  bool addCategory(const QString &title);
  bool deleteCategory(const QModelIndex &index);

  bool addStation(const StationRecord &stationRecord);
  bool deleteStation(const QModelIndex &index);
  bool updateStation(const QModelIndex &index);

  PlaylistModel* getPlaylistModel();
  bool isPlaylistEmpty();

  int getSelectedIndex();
  int getPlayedIndex();
  void setSelectedIndex(int index);

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

  PlaylistModel m_playlistModel;
  int m_playlistRowsCount = 0;
  int m_currentSelectedIndex = 0;
  int m_currentPlayedIndex = 0;

//  void addRowToPlaylist(const StationRecord &stationRecord);
//  void deleteRowFromPlaylist(int index);

};


#endif // PLAYERHANDLER_HPP
