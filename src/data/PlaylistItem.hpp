#ifndef PLAYLISTITEM_HPP
#define PLAYLISTITEM_HPP

#include "GlobalClasses.hpp"
#include "StationRecord.hpp"


class PlaylistItem {

public:
  PlaylistItem();
  PlaylistItem(PlaylistItem *parentItem = nullptr, const QString &categoryTitle);
  PlaylistItem(PlaylistItem *parentItem = nullptr, const StationRecord &stationRecord);
  ~PlaylistItem();

  PlaylistItem *getParent();
  PlaylistItem *getChild(int row);

  bool addChild(const PlaylistItem &playlistItem);
  bool deleteChild(int row);

  int getChildCount() const;
  int getRowFor(PlaylistItem *item = nullptr) const;

  QString getData(int column) const;
  bool setData(int column, const QString &dataValue);

private:
  bool m_isRoot = false;
  bool m_isCategory = false;

  PlaylistItem *m_parentItem = nullptr;
  QList<PlaylistItem*> m_childItemsList;

  QString m_title;
  QString m_url;

};


#endif // PLAYLISTITEM_HPP
