#include <QtWidgets>
#include "PlaylistModel.hpp"
#include "PlaylistItem.hpp"


PlaylistModel::PlaylistModel() {
  m_rootItem = new PlaylistItem();
}


PlaylistModel::~PlaylistModel() {
  if (m_rootItem) delete m_rootItem;
}

// public methods =============================================================

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();

  PlaylistItem *item = this->getItemFromIndex(index);
  return QVariant(item->getData(index.column()));
}


bool PlaylistModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (role != Qt::EditRole) return false;
  PlaylistItem *item = this->getItemFromIndex(index);
  if (item->setData(index.column(), value.toString())) {
    emit this->dataChanged(index, index);
    return true;
  }
  return false;
}


QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &index) const {
  if (!hasIndex(row, column, index)) return QModelIndex();
  PlaylistItem *parent = m_rootItem;
  if (index.isValid()) parent = static_cast<PlaylistItem*>(index.internalPointer());
  PlaylistItem *child = parent->getChild(row);
  if (child) return this->createIndex(row, column, child);
  else return QModelIndex();
}


QModelIndex PlaylistModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();
  PlaylistItem *child = getItemFromIndex(index);
  PlaylistItem *parent = child->getParent();
  if (!parent || parent == m_rootItem) return QModelIndex();
  else return this->createIndex(parent->getRowFor(), 0, parent);
}


int PlaylistModel::rowCount(const QModelIndex &index) const {
  PlaylistItem *parent = this->getItemFromIndex(index);
  return parent->getChildCount();
}


int PlaylistModel::columnCount(const QModelIndex &index) const {
  return 2;
}


bool PlaylistModel::addRow(const PlaylistItem &playlistItem, const QModelIndex &index) {
  PlaylistItem *parent = getItemFromIndex(index);
  return parent->addChild(playlistItem);
}


bool PlaylistModel::deleteRow(int row, const QModelIndex &index) {
  PlaylistItem *parent = getItemFromIndex(index);
  return parent->deleteChild(row);
}

// private methods ============================================================

PlaylistItem* PlaylistModel::getItemFromIndex(const QModelIndex &index) const {
  if (index.isValid()) {
    PlaylistItem *item = static_cast<PlaylistItem*>(index.internalPointer());
    if (item) return item;
  }
  return m_rootItem;
}
