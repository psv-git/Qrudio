// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "DataRecord.hpp"


DataRecord::DataRecord() {}


DataRecord::DataRecord(const QString &field, const QVariant &value) :
m_isValid(true),
m_field(field),
m_value(value) {}


DataRecord::~DataRecord() {}

// ============================================================================

bool operator == (const DataRecord& dr1, const DataRecord& dr2) {
  if (dr1.m_field != dr2.m_field) return false;
  return true;
}


bool DataRecord::isValid() const {
  return m_isValid;
}

// getters/setters ============================================================

const QString DataRecord::getField() const {
  return m_field;
}


const QVariant DataRecord::getValue() const {
  return m_value;
}
