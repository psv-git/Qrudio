// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "DataRecord.hpp"


DataRecord::DataRecord() {}


DataRecord::DataRecord(const QString &field, const QVariant &value) {
  m_field = field;
  m_value = value;
  if (!m_field.isEmpty() && !m_value.toString().isEmpty()) {
    // TODO: check url on valid
    m_isValid = true;
  }
}


DataRecord::~DataRecord() {}

// ============================================================================

bool DataRecord::isValid() const {
  return m_isValid;
}


const QString DataRecord::getField() const {
  return m_field;
}


const QVariant DataRecord::getValue() const {
  return m_value;
}
