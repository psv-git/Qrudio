#ifndef PLAYLISTITEM_HPP
#define PLAYLISTITEM_HPP

#include "GlobalClasses.hpp"
#include "StationRecord.hpp"


class PlaylistItem {

public:
  PlaylistItem();
  PlaylistItem(const QVariant &categoryTitle, const PlaylistItem *parentItem = nullptr);
  PlaylistItem(const StationRecord &record, const PlaylistItem *parentItem = nullptr);
  PlaylistItem(const StationRecord *record, const PlaylistItem *parentItem = nullptr);
  PlaylistItem(const PlaylistItem &item);
  ~PlaylistItem();

  bool isRoot() const;
  bool isCategory() const;

  PlaylistItem *getChild(int row) const;

  bool addChild(const PlaylistItem &childItem);
  bool addChild(const PlaylistItem *childItem);
  bool deleteChild(int row);

  int getChildCount() const;
  int getRowFor(const PlaylistItem *item = nullptr) const;

  PlaylistItem *getParent() const;
  void setParent(const PlaylistItem *parentItem);

  QVariant getData(int column) const;
  bool setData(int column, const QVariant &value);

private:
  PlaylistItem *m_parentItem = nullptr;
  QList<PlaylistItem*> m_childItemsList;

  bool m_isRoot = false;
  bool m_isCategory = false;
  QVariant m_title;
  QVariant m_url;
  QVariant m_id;

};


#endif // PLAYLISTITEM_HPP
