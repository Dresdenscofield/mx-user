//
//   Copyright (C) 2003-2008 by Warren Woodford
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//

#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

#include "mainwindow.h"
#include <unistd.h>

int main( int argc, char ** argv ) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon::fromTheme("mx-user"));

    QTranslator qtTran;
    if (qtTran.load(QLocale::system(), "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        app.installTranslator(&qtTran);

    QTranslator qtBaseTran;
    if (qtBaseTran.load("qtbase_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        app.installTranslator(&qtBaseTran);

    QTranslator appTran;
    if (appTran.load(app.applicationName() + "_" + QLocale::system().name(), "/usr/share/" + app.applicationName() + "/locale"))
        app.installTranslator(&appTran);

    if (getuid() == 0) {
        MainWindow mw;
        mw.show();
        return app.exec();
    } else {
        system("su-to-root -X -c " + QApplication::applicationFilePath().toUtf8() + "&");
    }
}

