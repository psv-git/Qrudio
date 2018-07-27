// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef STATIONRECORD_HPP
#define STATIONRECORD_HPP

#include "GlobalClasses.hpp"


class StationRecord {

public:
  StationRecord();
  StationRecord(const QString &categoryTitle, const QString &stationTitle, const QVariant &stationUrl);
  ~StationRecord();

  bool isValid() const;

  const QString getCategoryTitle() const;
  const QString getStationTitle() const;
  const QString getStationUrl() const;

private:
  bool m_isValid = false;

  QString m_categoryTitle;
  QString m_stationTitle;
  QString m_stationUrl;

};


#endif // STATIONRECORD_HPP
