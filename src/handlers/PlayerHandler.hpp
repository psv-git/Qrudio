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

  void addStation(const QString &stationName, const QString &stationUrl);
  void updateStation(const QModelIndex &index);
  void deleteStation(const QModelIndex &index);
  QStandardItemModel* getPlaylistModel();

  int getPlaylistIndex();
  void setPlaylistIndex(int index);
  bool isPlaylistEmpty();

  void play();
  void playPrev();
  void playNext();
  void stop();
  void record();
  void setVolume(int volume);

signals:
//  void trackMetaDataChanged(TrackMetaData *trackMetaData);

public slots:
//  void onTrackMetaDataChange();

private:
  DataBaseHandler *m_dataBaseHandler = nullptr; // must be instantiate in runtime

//  QNetworkAccessManager m_webManager;
//  QByteArray m_downloadedData;
//  TrackMetaData m_trackMetaData;
  QMediaPlayer *m_player = nullptr;

  bool m_isPlaying = false;
  bool m_isPlaylistIndexChanged = false;
  int m_volume = 0;

  QStandardItemModel m_playlistModel;
  int m_playlistRowsCount = 0;
  int m_currentPlaylistIndex = 0;

  QUrl getCurrentUrl();
  void addRowToPlaylist(const QString &stationName, const QString &stationUrl);

};


#endif // PLAYERHANDLER_HPP
