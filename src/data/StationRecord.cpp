// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "StationRecord.hpp"


StationRecord::StationRecord() {}


StationRecord::StationRecord(const QString &categoryTitle, const QString &stationTitle, const QString &stationUrl) {
  m_categoryTitle = categoryTitle;
  m_stationTitle = stationTitle;
  m_stationUrl = stationUrl;
  if (!m_stationTitle.isEmpty()) {
   if (!m_stationUrl.isEmpty()) {
     // TODO: check url on valid
     m_isValid = true;
   }
  }
}


StationRecord::~StationRecord() {}

// public methods =============================================================

bool StationRecord::isValid() const {
  return m_isValid;
}


const QString StationRecord::getCategoryTitle() const {
  return m_categoryTitle;
}


const QString StationRecord::getStationTitle() const {
  return m_stationTitle;
}


const QString StationRecord::getStationUrl() const {
  return m_stationUrl;
}
