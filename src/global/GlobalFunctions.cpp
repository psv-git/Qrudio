// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "GlobalFunctions.hpp"


// ============================================================================

void Delay(int ms) {
  QEventLoop loop;
  QTimer::singleShot(ms, &loop, &QEventLoop::quit);
  loop.exec();
}

// paths & files ==============================================================

QString GetHomePath() {
  return QDir::homePath();
}


QString GetProgramPath() {
  return QDir::currentPath();
}


const QString GetDirectoryPath(const QString &title) {
  return QFileDialog::getExistingDirectory(nullptr, title, "/.", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}


void CreateDirectory(const QString &directoryPath, const QString &directoryName) {
  QDir path(directoryPath);
  if (!path.exists(directoryName)) {
    if (!path.mkdir(directoryName)) throw std::runtime_error("creating directory \"" + directoryName.toStdString() + "\" by path \"" + directoryPath.toStdString() + "\" was failed.");
  }
}


void RemoveDirectory(const QString &directoryPath, const QString &directoryName) {
  QDir path(directoryPath);
  if (path.exists(directoryName)) {
    if (!path.rmdir(directoryName)) throw std::runtime_error("removing directory \"" + directoryName.toStdString() + "\" by path \"" + directoryPath.toStdString() + "\" was failed.");
  }
}


// extStr may be "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)" for example
const QString GetFilePath(const QString &title, const QString &extStr) {
  return QFileDialog::getOpenFileName(nullptr, title, "./", extStr);
}


const QString GetFileName(const QString &title, const QString &extStr) {
  QString filePath = GetFilePath(title, extStr);
  QFileInfo fileInfo(filePath);
  return fileInfo.fileName();
}


void OpenFile(QFile& file, QFlags<QIODevice::OpenModeFlag> openMode) {
  if (!file.open(openMode)) throw std::runtime_error("opening \"" + file.fileName().toStdString() + "\" file was failed.");
}


void CloseFile(QFile& file) {
  file.close();
  if (file.isOpen()) throw std::runtime_error("closing \"" + file.fileName().toStdString() + "\" file was failed.");
}


void RemoveFile(QFile& file) {
  if (file.isOpen()) file.close();;
  if (!file.remove()) throw std::runtime_error("removing \"" + file.fileName().toStdString() + "\" file was failed.");
}

// web ========================================================================

void OpenUrl(const QString &url) {
  OpenUrl(QUrl(url));
}


void OpenUrl(const QUrl &url) {
  QDesktopServices::openUrl(url);
}

// images =====================================================================

QIcon TransformIcon(const QIcon &icon, int width, int height, int degree) {
  QPixmap pixmap = icon.pixmap(width, height);
  QMatrix matrix;
  matrix.rotate(degree);
  pixmap = pixmap.transformed(matrix);
  return QIcon(pixmap);
}
