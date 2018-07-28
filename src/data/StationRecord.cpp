// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "StationRecord.hpp"


StationRecord::StationRecord() {}


StationRecord::StationRecord(const QString &categoryTitle, const QString &stationTitle, const QString &stationUrl, int id) {
  if (!stationTitle.isEmpty() && !stationUrl.isEmpty()) {
    m_id = id;
    m_categoryTitle = categoryTitle;
    m_stationTitle = stationTitle;
    m_stationUrl = stationUrl;
    m_isValid = true;
  }
}


StationRecord::~StationRecord() {}

// public methods =============================================================

bool StationRecord::isValid() const {
  return m_isValid;
}


int StationRecord::getId() const {
  return m_id;
}


const QString& StationRecord::getCategoryTitle() const {
  return m_categoryTitle;
}


const QString& StationRecord::getStationTitle() const {
  return m_stationTitle;
}


const QString& StationRecord::getStationUrl() const {
  return m_stationUrl;
}
