#ifndef PLAYLISTITEM_HPP
#define PLAYLISTITEM_HPP

#include "GlobalClasses.hpp"
#include "StationRecord.hpp"


class PlaylistItem {

public:
  PlaylistItem();
  PlaylistItem(const QString &categoryTitle, const PlaylistItem *parent = nullptr);
  PlaylistItem(const StationRecord &stationRecord, const PlaylistItem *parent = nullptr);
  PlaylistItem(const StationRecord *stationRecord, const PlaylistItem *parent = nullptr);
  PlaylistItem(const PlaylistItem &item);
  ~PlaylistItem();

  bool isRoot() const;
  bool isCategory() const;

  PlaylistItem *getChild(int row) const;

  bool addChild(const PlaylistItem &child);
  bool addChild(const PlaylistItem *child);
  bool deleteChild(int row);

  int getChildCount() const;
  int getRowFor(const PlaylistItem *item = nullptr) const;

  PlaylistItem *getParent() const;
  void setParent(const PlaylistItem *parent);

  QVariant getData(int column) const;
  bool setData(int column, const QVariant &value);

private:
  bool m_isRoot = false;
  bool m_isCategory = false;

  PlaylistItem *m_parent = nullptr;
  QList<PlaylistItem*> m_childsList;

  QVariant m_title;
  QVariant m_url;
  QVariant m_id;

};


#endif // PLAYLISTITEM_HPP
