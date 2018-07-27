#include "PlaylistItem.hpp"


// constructor for root node
PlaylistItem::PlaylistItem() {
  m_isRoot = true;
}


// constructor for category node
PlaylistItem::PlaylistItem(const QString &categoryTitle, const PlaylistItem *parent) {
  m_isCategory = true;
  m_parent = const_cast<PlaylistItem*>(parent);
  m_title = categoryTitle;
}


// constructor for station node
PlaylistItem::PlaylistItem(const StationRecord &stationRecord, const PlaylistItem *parent) {
  m_parent = const_cast<PlaylistItem*>(parent);
  m_title = stationRecord.getStationTitle();
  m_url = stationRecord.getStationUrl();
}


PlaylistItem::~PlaylistItem() {
  for (int i = 0; i < m_childsList.size(); i++) {
    delete m_childsList.at(i);
  }
  m_childsList.clear();
}

// public methods =============================================================

PlaylistItem* PlaylistItem::getChild(int row) const {
  return m_childsList.value(row, nullptr);
}


bool PlaylistItem::addChild(PlaylistItem *child) {
  if (!m_childsList.contains(child)) {
    m_childsList.append(child);
    child->setParent(this);
    return true;
  }
  return false;
}


bool PlaylistItem::deleteChild(int row) {
  if (row < 0 || row >= m_childsList.size()) return false;
  delete m_childsList.takeAt(row);
  return true;
}


int PlaylistItem::getChildCount() const {
  return m_childsList.size();
}


int PlaylistItem::getRowFor(const PlaylistItem *item) const {
  if (!item || item == this) {
    if (m_parent) return m_parent->getRowFor(this);
  } else {
    return m_childsList.indexOf(const_cast<PlaylistItem*>(item));
  }
  return 0;
}


PlaylistItem* PlaylistItem::getParent() const {
  return m_parent;
}


void PlaylistItem::setParent(const PlaylistItem *parent) {
  if (m_parent != parent) {
    m_parent = const_cast<PlaylistItem*>(parent);
    m_parent->addChild(this);
  }
}


QString PlaylistItem::getData(int column) const {
  switch (column) {
    case 0: return m_title;
    case 1: return m_url;
    default: return QString();
  }
}


bool PlaylistItem::setData(int column, const QString &value) {
  if (m_isRoot) return false;
  if (column == 0) m_title = value;
  else if (column == 1 && !m_isCategory) m_url = value;
  else return false;
  return true;
}
