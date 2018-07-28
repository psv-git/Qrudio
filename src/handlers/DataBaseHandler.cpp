// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "DataBaseHandler.hpp"


DataBaseHandler::DataBaseHandler() {
  m_dataBase = QSqlDatabase::addDatabase("QSQLITE");

  // open database
  m_dataBase.setDatabaseName(GetHomePath() + DEFAULT_SETTINGS.dataBasePath);
  if (!m_dataBase.open()) {
    ErrorHandler::getInstance().addErrorMessage(tr("Data base was not open."));
  }

  // create query
  m_query = new QSqlQuery();

  // create stations table if not exist
  if (!sendQuery(QString("CREATE TABLE IF NOT EXISTS %1 (category TEXT, title TEXT, url TEXT);").arg(DEFAULT_SETTINGS.stationsTableName))) {
    ErrorHandler::getInstance().addErrorMessage(tr("Stations table was not created."));
  }
}


DataBaseHandler::~DataBaseHandler() {
  clearRecordsList();
  if (m_query) delete m_query;
}

// public methods =============================================================

int DataBaseHandler::addRecord(const StationRecord &record) {
  if (!record.isValid()) return 0;
  if (!sendQuery(QString("INSERT INTO %1 (rowid, category, title, url) VALUES (NULL, '%2', '%3', '%4');").arg(DEFAULT_SETTINGS.stationsTableName).arg(record.getCategoryTitle().toString()).arg(record.getStationTitle().toString()).arg(record.getStationUrl().toString()))) {
    ErrorHandler::getInstance().addErrorMessage(tr("Can't add data to the table."));
    return 0;
  }
  if (sendQuery("SELECT last_insert_rowid()")) return m_query->lastInsertId().toInt();
  else return 0;
}


bool DataBaseHandler::deleteRecord(int recordId) {
  if (!sendQuery(QString("DELETE FROM %1 WHERE rowid = %2;").arg(DEFAULT_SETTINGS.stationsTableName).arg(recordId))) {
    ErrorHandler::getInstance().addErrorMessage(tr("Can't delete data from the table."));
    return false;
  }
  return true;
}


//bool DataBaseHandler::updateRecord(const StationRecord &record) {
//  if (!record.isValid()) false;
//  if (!sendQuery(QString("UPDATE %1 SET value = '%3' WHERE field = '%2';").arg(tableName).arg(record.getStationTitle()).arg(record.getStationUrl()))) {
//    ErrorHandler::getInstance().addErrorMessage("Can't update data in the table.");
//    return false;
//  }
//  return true;
//}


QList<StationRecord*>* DataBaseHandler::getRecordsList() {
  clearRecordsList();
  if (!sendQuery(QString("SELECT rowid, * FROM %1").arg(DEFAULT_SETTINGS.stationsTableName))) {
    ErrorHandler::getInstance().addErrorMessage(tr("Can't read information from the table."));
  } else {
    while (m_query->next()) {
      QSqlRecord rec = m_query->record();
      m_recordsList.push_back(new StationRecord(rec.value(1), rec.value(2), rec.value(3), rec.value(0)));
    }
  }
  return &m_recordsList;
}

// private methods ============================================================

bool DataBaseHandler::sendQuery(const QString &queryString) {
  return m_query->exec(queryString);
}


void DataBaseHandler::clearRecordsList() {
  for (int i = 0; i < m_recordsList.size(); i++) {
    delete m_recordsList.at(i);
  }
  m_recordsList.clear();
}
