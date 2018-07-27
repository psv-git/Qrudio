#ifndef PLAYLISTITEM_HPP
#define PLAYLISTITEM_HPP

#include "GlobalClasses.hpp"
#include "StationRecord.hpp"


class PlaylistItem {

public:
  PlaylistItem();
  PlaylistItem(const QString &categoryTitle, const PlaylistItem *parent = nullptr);
  PlaylistItem(const StationRecord &stationRecord, const PlaylistItem *parent = nullptr);
  ~PlaylistItem();

  PlaylistItem *getChild(int row) const;

  bool addChild(PlaylistItem *child);
  bool deleteChild(int row);

  int getChildCount() const;
  int getRowFor(const PlaylistItem *item = nullptr) const;

  PlaylistItem *getParent() const;
  void setParent(const PlaylistItem *parent);

  QString getData(int column) const;
  bool setData(int column, const QString &value);

private:
  bool m_isRoot = false;
  bool m_isCategory = false;

  PlaylistItem *m_parent = nullptr;
  QList<PlaylistItem*> m_childsList;

  QString m_title;
  QString m_url;

};


#endif // PLAYLISTITEM_HPP
