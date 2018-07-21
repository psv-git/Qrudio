// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef TRACKMETADATA_HPP
#define TRACKMETADATA_HPP

#include "GlobalFunctions.hpp"
#include "GlobalVariables.hpp"


class TrackMetaData {

public:
  TrackMetaData();
  ~TrackMetaData();

  QString getTrackTitle();
  QString getSampleRate();
  QString getBitRate();

  void setTrackTitle(const QString &trackTitle);
  void setSampleRate(int sampleRate);
  void setBitRate(int bitRate);

private:
  QString m_trackTitle;
  QString m_sampleRate;
  QString m_bitRate;

};


#endif // TRACKMETADATA_HPP
