#include "PlaylistItem.hpp"


// constructor for root node
PlaylistItem::PlaylistItem() {
  m_isRoot = true;
}


// constructor for category node
PlaylistItem::PlaylistItem(const QVariant &categoryTitle, const PlaylistItem *parentItem) {
  m_isCategory = true;
  m_parentItem = const_cast<PlaylistItem*>(parentItem);
  m_title = categoryTitle;
}


// constructors for station node
PlaylistItem::PlaylistItem(const StationRecord &record, const PlaylistItem *parentItem) : PlaylistItem(&record, parentItem) {}

PlaylistItem::PlaylistItem(const StationRecord *record, const PlaylistItem *parentItem) {
  m_parentItem = const_cast<PlaylistItem*>(parentItem);
  m_title = record->getStationTitle();
  m_url = record->getStationUrl();
  m_id = record->getId();
}


// copy constructor
PlaylistItem::PlaylistItem(const PlaylistItem &item) {
  m_parentItem = item.getParent();
  if (!item.isRoot()) {
    m_title = item.getData(0);
    if (!item.isCategory()) {
      m_url = item.getData(1);
      m_id = item.getData(2);
    }
  }
}


PlaylistItem::~PlaylistItem() {
  for (int i = 0; i < m_childItemsList.size(); i++) {
    delete m_childItemsList.at(i);
  }
  m_childItemsList.clear();
}

// public methods =============================================================

bool PlaylistItem::isRoot() const {
  return m_isRoot;
}


bool PlaylistItem::isCategory() const {
  return m_isCategory;
}


PlaylistItem* PlaylistItem::getChild(int row) const {
  return m_childItemsList.value(row, nullptr);
}


bool PlaylistItem::addChild(const PlaylistItem &childItem) {
  return this->addChild(new PlaylistItem(childItem));
}


bool PlaylistItem::addChild(const PlaylistItem *childItem) {
  PlaylistItem *item = const_cast<PlaylistItem*>(childItem);
  if (!m_childItemsList.contains(item)) {
    m_childItemsList.append(item);
    item->setParent(this);
    return true;
  }
  return false;
}


bool PlaylistItem::deleteChild(int row) {
  if (row < 0 || row >= m_childItemsList.size()) return false;

  delete m_childItemsList.takeAt(row);
  return true;
}


int PlaylistItem::getChildCount() const {
  return m_childItemsList.size();
}


// get row for this from parent object
int PlaylistItem::getRowFor(const PlaylistItem *item) const {
  if (!item || item == this) {
    if (m_parentItem) return m_parentItem->getRowFor(this);
  } else return m_childItemsList.indexOf(const_cast<PlaylistItem*>(item));
  return 0;
}


PlaylistItem* PlaylistItem::getParent() const {
  return m_parentItem;
}


void PlaylistItem::setParent(const PlaylistItem *parentItem) {
  if (m_parentItem != parentItem) {
    m_parentItem = const_cast<PlaylistItem*>(parentItem);
    m_parentItem->addChild(this);
  }
}


QVariant PlaylistItem::getData(int column) const {
  if (column == 0) return m_title;
  else if (column == 1) return m_url;
  else if (column == 2) return m_id;
  else if (column == 3) {
    if (!this->isRoot() && !this->isCategory() && m_parentItem) return m_parentItem->getData(0);
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
