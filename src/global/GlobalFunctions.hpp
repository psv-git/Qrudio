// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef GLOBALFUNCTIONS_HPP
#define GLOBALFUNCTIONS_HPP

#include <QFileDialog>
#include <QDesktopServices>
#include <QTimer>

#include "headers.hpp"


// ============================================================================

void Delay(int ms);

// paths & files ==============================================================

QString GetHomePath();
QString GetProgramPath();

const QString GetDirectoryPath(const QString &title);
const QString GetFilePath(const QString &title, const QString &extStr);
const QString GetFileName(const QString &title, const QString &extStr);

void CreateDirectory(const QString &directoryPath, const QString &directoryName);
void RemoveDirectory(const QString &directoryPath, const QString &directoryName);

void OpenFile(QFile& file, QFlags<QIODevice::OpenModeFlag> openMode);
void CloseFile(QFile& file);
void RemoveFile(QFile& file);

// web ========================================================================

void OpenUrl(const QString &url);
void OpenUrl(const QUrl &url);

// i/o ========================================================================

template <typename V>
int ReadDataFromStream(QDataStream& stream, V& var, int size = 0) {
  if (size == 0) size = static_cast<int>(sizeof(var));
  int count = stream.readRawData(reinterpret_cast<char*>(&var), size);
  if (count < 0) throw std::ios_base::failure("reading data from file was failed");
  return count;
}


template <typename V>
int WriteDataToStream(QDataStream& stream, V& var, int size = 0) {
  if (size == 0) size = static_cast<int>(sizeof(var));
  int count = stream.writeRawData(reinterpret_cast<char*>(&var), size);
  if (count < 0) throw std::ios_base::failure("writing data to file was failed");
  return count;
}

// images =====================================================================

QIcon TransformIcon(const QIcon &icon, int width, int height, int degree);


#endif // GLOBALFUNCTIONS_HPP
