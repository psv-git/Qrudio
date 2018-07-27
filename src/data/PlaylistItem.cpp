#include "PlaylistItem.hpp"


// constructor for root node
PlaylistItem::PlaylistItem() {
  m_isRoot = true;
}


// constructor for category node
PlaylistItem::PlaylistItem(PlaylistItem *parentItem, const QString &title) {
  m_isCategory = true;
  m_parentItem = parentItem;
  m_title = title;
}


// constructor for station node
PlaylistItem::PlaylistItem(PlaylistItem *parentItem, const StationRecord &stationRecord) {
  m_parentItem = parentItem;
  m_title = stationRecord.getStationTitle();
  m_url = stationRecord.getStationUrl();
}


PlaylistItem::~PlaylistItem() {
  for (int i = 0; i < m_childItemsList.size(); i++) {
    delete m_childItemsList.at(i);
  }
  m_childItemsList.clear();
}

// public methods =============================================================

PlaylistItem* PlaylistItem::getParent() {
  return m_parentItem;
}


PlaylistItem* PlaylistItem::getChild(int row) {
  return m_childItemsList.value(row, nullptr);
}


bool PlaylistItem::addChild(PlaylistItem &playlistItem) {
  m_childItemsList.append(&playlistItem);
}


bool PlaylistItem::deleteChild(int row) {
  if (row < 0 || row >= m_childItemsList.size()) return false;
  delete m_childItemsList.takeAt(row);
  return true;
}


int PlaylistItem::getChildCount() const {
  return m_childItemsList.size();
}


int PlaylistItem::getRowFor(PlaylistItem *playlistItem) const {
  if (!playlistItem || playlistItem == this) {
    if (m_parentItem) return m_parentItem->getRowFor(this);
  } else {
    return m_childItemsList.indexOf(const_cast<PlaylistItem*>(playlistItem));
  }
  return 0;
}


QString PlaylistItem::getData(int column) const {
  switch (column) {
    case 0: return m_parentItem->getData(1); // get category title
    case 1: return m_title;
    case 2: return m_url;
    default: return QString();
  }
}


bool PlaylistItem::setData(int column, const QString &dataValue) {
  if (m_isRoot) return false;
  if (column == 1) m_title = dataValue;
  else if (column == 2 && !m_isCategory) m_url = dataValue;
  else return false;
  return true;
}
