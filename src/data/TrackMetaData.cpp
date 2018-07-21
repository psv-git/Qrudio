// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "TrackMetaData.hpp"


TrackMetaData::TrackMetaData() {}


TrackMetaData::~TrackMetaData() {}

// public methods =============================================================

QString TrackMetaData::getTrackTitle() {
  return m_trackTitle;
}


QString TrackMetaData::getSampleRate() {
  return m_sampleRate;
}


QString TrackMetaData::getBitRate() {
  return m_bitRate;
}


void TrackMetaData::setTrackTitle(const QString &trackTitle) {
  if (!trackTitle.isEmpty()) m_trackTitle = trackTitle;
  else m_trackTitle = "unknown";
}


void TrackMetaData::setSampleRate(int sampleRate) {
  if (sampleRate > 0) m_sampleRate = QString::number(sampleRate);
  else m_sampleRate = "unknown";
}


void TrackMetaData::setBitRate(int bitRate) {
  if (bitRate > 0) m_bitRate = QString::number(bitRate);
  else m_bitRate = "unknown";
}
