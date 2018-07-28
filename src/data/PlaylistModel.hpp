#ifndef PLAYLISTMODEL_HPP
#define PLAYLISTMODEL_HPP

#include <QAbstractItemModel>
#include "GlobalClasses.hpp"
#include "PlaylistItem.hpp"


class PlaylistModel : public QAbstractItemModel {
Q_OBJECT

public:
  explicit PlaylistModel(QObject *parent = nullptr);
  ~PlaylistModel();

  QVariant data(const QModelIndex &itemIndex, int role) const override;
  bool setData(const QModelIndex &itemIndex, const QVariant &value, int role) override;

  PlaylistItem *getItemFromIndex(const QModelIndex &itemIndex = QModelIndex()) const;
  QModelIndex index(int row, int column, const QModelIndex &parentIndex) const override;
  QModelIndex parent(const QModelIndex &itemIndex) const override;

  bool addRow(const PlaylistItem &item, const QModelIndex &parentIndex = QModelIndex());
  bool addRow(const PlaylistItem *item, const QModelIndex &parentIndex = QModelIndex());
  bool deleteRow(int row, const QModelIndex &parentIndex = QModelIndex());

  int rowCount(const QModelIndex &itemIndex = QModelIndex()) const override;
  int columnCount(const QModelIndex &itemIndex = QModelIndex()) const override;

private:
  PlaylistItem *m_rootItem;

};


#endif // PLAYLISTMODEL_HPP
