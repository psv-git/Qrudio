// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "GlobalClasses.hpp"
#include "PlayerWindow.hpp"


int main(int argc, char *argv[]) {
  QTextCodec* codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);

  CreateDirectory(GetHomePath(), DEFAULT_SETTINGS.applicationDirectoryName);

  QApplication app(argc, argv);

  PlayerWindow pw;
  pw.run();

  return app.exec();
}
