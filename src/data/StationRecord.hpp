// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef STATIONRECORD_HPP
#define STATIONRECORD_HPP

#include "GlobalClasses.hpp"


class StationRecord {

public:
  StationRecord();
  StationRecord(const QVariant &categoryTitle, const QVariant &stationTitle, const QVariant &stationUrl, const QVariant &id = QVariant());
  ~StationRecord();

  bool isValid() const;

  const QVariant& getId() const;
  void setId(const QVariant &id);

  const QVariant& getCategoryTitle() const;
  const QVariant& getStationTitle() const;
  const QVariant& getStationUrl() const;

private:
  bool m_isValid = false;
  QVariant m_categoryTitle;
  QVariant m_stationTitle;
  QVariant m_stationUrl;
  QVariant m_id;

};


#endif // STATIONRECORD_HPP
