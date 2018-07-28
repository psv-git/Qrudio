// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "StationRecord.hpp"


StationRecord::StationRecord() {}


StationRecord::StationRecord(const QVariant &categoryTitle, const QVariant &stationTitle, const QVariant &stationUrl, const QVariant &id) {
  if (!stationTitle.toString().isEmpty() && !stationUrl.toString().isEmpty()) {
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


const QVariant& StationRecord::getId() const {
  return m_id;
}


void StationRecord::setId(const QVariant &id) {
  m_id = id;
}


const QVariant& StationRecord::getCategoryTitle() const {
  return m_categoryTitle;
}


const QVariant& StationRecord::getStationTitle() const {
  return m_stationTitle;
}


const QVariant& StationRecord::getStationUrl() const {
  return m_stationUrl;
}
