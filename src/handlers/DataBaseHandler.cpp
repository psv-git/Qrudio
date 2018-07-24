// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "DataBaseHandler.hpp"


DataBaseHandler::DataBaseHandler() {
  m_dataBase = QSqlDatabase::addDatabase("QSQLITE");

  // open database
  m_dataBase.setDatabaseName(GetHomePath() + DEFAULT_SETTINGS.dataBasePath);
  if (!m_dataBase.open()) {
    ErrorHandler::getInstance().addErrorMessage("Data base was not open.");
  }

  // create query
  m_query = new QSqlQuery();

  // create stations table if not exist
  if (!sendQuery(QString("CREATE TABLE IF NOT EXISTS %1 (field TEXT PRIMARY KEY, value TEXT) WITHOUT ROWID;").arg(DEFAULT_SETTINGS.stationsTableName))) {
    ErrorHandler::getInstance().addErrorMessage("Stations table was not created.");
  }
}


DataBaseHandler::~DataBaseHandler() {
  if (m_query) delete m_query;
}

// public methods =============================================================

bool DataBaseHandler::addRecord(const QString &tableName, const DataRecord &record) {
  if (!record.isValid()) false;
  if (!sendQuery(QString("INSERT INTO %1 (field, value) VALUES ('%2', '%3');").arg(tableName).arg(record.getField()).arg(record.getValue().toString()))) {
    ErrorHandler::getInstance().addErrorMessage("Can't add data to the table.");
    return false;
  }
  return true;
}


bool DataBaseHandler::deleteRecord(const QString &tableName, const DataRecord &record) {
  if (!record.isValid()) false;
  if (!sendQuery(QString("DELETE FROM %1 WHERE field = '%2';").arg(tableName).arg(record.getField()))) {
    ErrorHandler::getInstance().addErrorMessage("Can't delete data from the table.");
    return false;
  }
  return true;
}


bool DataBaseHandler::updateRecord(const QString &tableName, const DataRecord &record) {
  if (!record.isValid()) false;
  if (!sendQuery(QString("UPDATE %1 SET value = '%3' WHERE field = '%2';").arg(tableName).arg(record.getField()).arg(record.getValue().toString()))) {
    ErrorHandler::getInstance().addErrorMessage("Can't update data in the table.");
    return false;
  }
  return true;
}


QVector<DataRecord*>* DataBaseHandler::getRecordsList(const QString &tableName) {
  clearRecordsList();
  if (!sendQuery(QString("SELECT * FROM %1").arg(tableName))) {
    ErrorHandler::getInstance().addErrorMessage("Can't read information from the table.");
  } else {
    while (m_query->next()) {
      QSqlRecord rec = m_query->record();
      m_recordsList.push_back(new DataRecord(rec.value(0).toString(), rec.value(1).toString()));
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
