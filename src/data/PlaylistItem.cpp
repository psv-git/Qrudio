#include "PlaylistItem.hpp"


// constructor for root node
PlaylistItem::PlaylistItem() {
  m_isRoot = true;
}


// constructor for category node
PlaylistItem::PlaylistItem(const QString &categoryTitle, const PlaylistItem *parent) {
  m_isCategory = true;
  m_parent = const_cast<PlaylistItem*>(parent);
  m_title = QVariant(categoryTitle);
}


// constructors for station node
PlaylistItem::PlaylistItem(const StationRecord &stationRecord, const PlaylistItem *parent) : PlaylistItem(&stationRecord, parent) {}

PlaylistItem::PlaylistItem(const StationRecord *stationRecord, const PlaylistItem *parent) {
  m_parent = const_cast<PlaylistItem*>(parent);
  m_title = QVariant(stationRecord->getStationTitle());
  m_url = QVariant(stationRecord->getStationUrl());
  m_id = QVariant(stationRecord->getId());
}


// copy constructor
PlaylistItem::PlaylistItem(const PlaylistItem &item) {
  m_parent = item.getParent();
  if (!item.isRoot()) {
    m_title = item.getData(0);
    if (!item.isCategory()) {
      m_url = item.getData(1);
      m_id = item.getData(2);
    }
  }
}


PlaylistItem::~PlaylistItem() {
  for (int i = 0; i < m_childsList.size(); i++) {
    delete m_childsList.at(i);
  }
  m_childsList.clear();
}

// public methods =============================================================

bool PlaylistItem::isRoot() const {
  return m_isRoot;
}


bool PlaylistItem::isCategory() const {
  return m_isCategory;
}


PlaylistItem* PlaylistItem::getChild(int row) const {
  return m_childsList.value(row, nullptr);
}


bool PlaylistItem::addChild(const PlaylistItem &child) {
  return this->addChild(new PlaylistItem(child));
}


bool PlaylistItem::addChild(const PlaylistItem *child) {
  PlaylistItem *item = const_cast<PlaylistItem*>(child);
  if (!m_childsList.contains(item)) {
    m_childsList.append(item);
    item->setParent(this);
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


// get row for this from parent object
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


QVariant PlaylistItem::getData(int column) const {
  if (column == 0) return m_title;
  else if (column == 1) return m_url;
  else if (column == 2) return m_id;
  else if (column == 3) {
    if (!this->isRoot() && !this->isCategory() && m_parent) return m_parent->getData(0);
  }
  return QVariant();
}


bool PlaylistItem::setData(int column, const QVariant &value) {
  if (this->isRoot()) return false;

  if (column == 0) m_title = value;
  else if (column == 1 && !this->isCategory()) m_url = value;
  else if (column == 2 && !this->isCategory()) m_id = value;
  else return false;
  return true;
}
