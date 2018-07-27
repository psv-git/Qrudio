// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef DATABASEHANDLER_HPP
#define DATABASEHANDLER_HPP

#include <QtSql>
#include "GlobalClasses.hpp"
#include "StationRecord.hpp"


class DataBaseHandler {

public:
  explicit DataBaseHandler();
  ~DataBaseHandler();

  bool addRecord(const QString &tableName, const StationRecord &record);
  bool deleteRecord(const QString &tableName, const StationRecord &record);
  bool updateRecord(const QString &tableName, const StationRecord &record);
  QVector<StationRecord*>* getRecordsList(const QString &tableName);

private:
  QSqlDatabase m_dataBase;
  QSqlQuery *m_query = nullptr; // must be created after database init
  QVector<StationRecord*> m_recordsList;

  bool sendQuery(const QString &queryString);
  void clearRecordsList();

};


#endif // DATABASEHANDLER_HPP
