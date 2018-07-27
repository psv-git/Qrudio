#include "PlaylistItem.hpp"


// constructor for root node
PlaylistItem::PlaylistItem() {
  m_isRoot = true;
}


// constructor for category node
PlaylistItem::PlaylistItem(const QString &title, PlaylistItem *parent) {
  m_isCategory = true;
  m_parent = parent;
  m_title = title;
}


// constructor for station node
PlaylistItem::PlaylistItem(const StationRecord &stationRecord, PlaylistItem *parent) {
  m_parent = parent;
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

PlaylistItem* PlaylistItem::getChild(int row) {
  return m_childsList.value(row, nullptr);
}


bool PlaylistItem::addChild(PlaylistItem &child) {
  if (!m_childsList.contains(&child)) {
    m_childsList.append(&child);
    child.setParent(this);
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


int PlaylistItem::getRowFor(PlaylistItem *item) {
  if (!item || item == this) {
    if (m_parent) return m_parent->getRowFor(this);
  } else {
    return m_childsList.indexOf(item);
  }
  return 0;
}


PlaylistItem* PlaylistItem::getParent() {
  return m_parent;
}


void PlaylistItem::setParent(PlaylistItem *parent) {
  if (m_parent != parent) {
    m_parent = parent;
    m_parent->addChild(*this);
  }
}


QString PlaylistItem::getData(int column) const {
  switch (column) {
    case 0: return m_parent->getData(1); // get category title
    case 1: return m_title;
    case 2: return m_url;
    default: return QString();
  }
}


bool PlaylistItem::setData(int column, const QString &value) {
  if (m_isRoot) return false;
  if (column == 1) m_title = value;
  else if (column == 2 && !m_isCategory) m_url = value;
  else return false;
  return true;
}
