#ifndef PLAYLISTMODEL_HPP
#define PLAYLISTMODEL_HPP

#include <QAbstractItemModel>
#include "GlobalClasses.hpp"
#include "PlaylistItem.hpp"


class PlaylistModel : public QAbstractItemModel {
Q_OBJECT

public:
  PlaylistModel();
  ~PlaylistModel();

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

  QModelIndex index(int row, int column, const QModelIndex &index = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;

  bool addRow(PlaylistItem &playlistItem, const QModelIndex &index = QModelIndex());
  bool deleteRow(int row, const QModelIndex &index = QModelIndex());

  int rowCount(const QModelIndex &index = QModelIndex()) const override;
  int columnCount(const QModelIndex &index = QModelIndex()) const override;

private:
  PlaylistItem *m_rootItem;

  PlaylistItem *getItemFromIndex(const QModelIndex &index = QModelIndex()) const;

};


#endif // PLAYLISTMODEL_HPP
