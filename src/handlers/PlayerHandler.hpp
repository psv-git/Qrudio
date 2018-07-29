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

  bool addStation(const StationRecord &record);
  bool deleteStation(const QModelIndex &itemIndex);
  bool updateStation(const QModelIndex &itemindex);

  PlaylistModel* getPlaylistModel() const;
  bool isPlaylistEmpty() const;

  const QModelIndex& getSelectedIndex() const;
  const QModelIndex& getPlayedIndex() const;
  void setSelectedIndex(const QModelIndex &index);

  void play();
  void playPrev();
  void playNext();
  void stop();
  void record();
  void setVolume(int volume);

private:
  DataBaseHandler *m_dataBaseHandler = nullptr; // must be instantiate in runtime
  PlaylistModel m_playlistModel;
  QMap<PlaylistItem*, QModelIndex> m_categoriesMap;

  QMediaPlayer *m_player = nullptr;

  bool m_isPlaying = false;
  bool m_isPlaylistIndexChanged = false;
  int m_volume = 0;
  int m_playlistRowsCount = 0;
  QModelIndex m_currentSelectedIndex;
  QModelIndex m_currentPlayedIndex;

  QModelIndex getCategoryIndex(const QVariant &categoryTitle);
  bool addStationToPlaylist(const StationRecord &record);
  bool deleteStationFromPlaylist(int id, int row, const QModelIndex &parentIndex);

};


#endif // PLAYERHANDLER_HPP
