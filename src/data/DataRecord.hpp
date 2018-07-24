// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef DATARECORD_HPP
#define DATARECORD_HPP

#include "GlobalVariables.hpp"


class DataRecord {

public:
  DataRecord();
  DataRecord(const QString &field, const QVariant &value);
  ~DataRecord();

  bool isValid() const;

  const QString getField() const;
  const QVariant getValue() const;

private:
  bool m_isValid = false;

  QString m_field;
  QVariant m_value;

};


#endif // DATARECORD_HPP
