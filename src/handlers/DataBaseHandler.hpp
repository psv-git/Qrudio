// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef DATABASEHANDLER_HPP
#define DATABASEHANDLER_HPP

#include <QtSql>
#include "GlobalClasses.hpp"
#include "StationRecord.hpp"


class DataBaseHandler : public QObject {
Q_OBJECT

public:
  explicit DataBaseHandler();
  ~DataBaseHandler();

  bool addRecord(const StationRecord &record);
  bool deleteRecord(const StationRecord &record);
//  bool updateRecord(const StationRecord &record);
  QList<StationRecord*>* getRecordsList();

private:
  QSqlDatabase m_dataBase;
  QSqlQuery *m_query = nullptr; // must be created after database init
  QList<StationRecord*> m_recordsList;

  bool sendQuery(const QString &queryString);
  void clearRecordsList();

};


#endif // DATABASEHANDLER_HPP
