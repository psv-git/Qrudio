#include "PlaylistModel.hpp"


PlaylistModel::PlaylistModel(QObject *parent) : QAbstractItemModel(parent) {
  m_rootItem = new PlaylistItem();
}


PlaylistModel::~PlaylistModel() {
  if (m_rootItem) delete m_rootItem;
}

// public methods =============================================================

QVariant PlaylistModel::data(const QModelIndex &itemIndex, int role) const {
  if (!itemIndex.isValid()) return QVariant();
  if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();

  PlaylistItem *item = this->item(itemIndex);
  return item->getData(itemIndex.column());
}


bool PlaylistModel::setData(const QModelIndex &itemIndex, const QVariant &value, int role) {
  if (role != Qt::EditRole) return false;

  PlaylistItem *item = this->item(itemIndex);
  if (item->setData(itemIndex.column(), value)) {
    emit this->dataChanged(itemIndex, itemIndex);
    return true;
  }
  return false;
}


PlaylistItem* PlaylistModel::item(const QModelIndex &itemIndex) const {
  if (itemIndex.isValid()) {
    PlaylistItem *item = static_cast<PlaylistItem*>(itemIndex.internalPointer());
    if (item) return item;
  }
  return m_rootItem;
}


QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parentIndex) const {
  if (!hasIndex(row, column, parentIndex)) return QModelIndex();

  PlaylistItem *parent = m_rootItem;
  if (parentIndex.isValid()) parent = static_cast<PlaylistItem*>(parentIndex.internalPointer());
  PlaylistItem *child = parent->getChild(row);
  if (child) return this->createIndex(row, column, child);
  else return QModelIndex();
}


QModelIndex PlaylistModel::parent(const QModelIndex &itemIndex) const {
  if (!itemIndex.isValid()) return QModelIndex();

  PlaylistItem *child = item(itemIndex);
  PlaylistItem *parent = child->getParent();
  if (!parent || parent == m_rootItem) return QModelIndex();
  else return this->createIndex(parent->getRowFor(), 0, parent);
}


QModelIndex PlaylistModel::addRow(const PlaylistItem &item, const QModelIndex &parentIndex) {
  return this->addRow(new PlaylistItem(item), parentIndex);
}


QModelIndex PlaylistModel::addRow(const PlaylistItem *item, const QModelIndex &parentIndex) {
  PlaylistItem *parent = this->item(parentIndex);
  int row = parent->getChildCount();
  QModelIndex itemIndex;

  this->beginInsertRows(parentIndex, row, row);
  if (parent->addChild(item)) itemIndex = this->index(row, 0, parentIndex);
  this->endInsertRows();

  return itemIndex;
}


bool PlaylistModel::deleteRow(int row, const QModelIndex &parentIndex) {
  PlaylistItem *parent = this->item(parentIndex);

  this->beginRemoveRows(parentIndex, row, row);
  bool success = parent->deleteChild(row);
  this->endRemoveRows();

  return success;
}


int PlaylistModel::rowCount(const QModelIndex &itemIndex) const {
  PlaylistItem *parent = this->item(itemIndex);
  return parent->getChildCount();
}


int PlaylistModel::columnCount(const QModelIndex &itemIndex) const {
  return 3;
}
