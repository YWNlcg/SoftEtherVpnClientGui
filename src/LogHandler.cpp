#include "LogHandler.h"

Q_LOGGING_CATEGORY(DefLog, "Default")
Q_LOGGING_CATEGORY(CA, "CmdAdapter")
Q_LOGGING_CATEGORY(Widget, "Widget")

void logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QFile fMessFile(QDir::currentPath() + "/" + LOG_FILENAME);
    if(!fMessFile.open(QFile::Append | QFile::Text)) {
        return;
    }

    QString typeStr;
    switch (type) {
    case QtInfoMsg:     typeStr = "Info"; break;
    case QtDebugMsg:    typeStr = "Debug"; break;
    case QtWarningMsg:  typeStr = "Warning"; break;
    case QtCriticalMsg: typeStr = "Critical"; break;
    case QtFatalMsg:    typeStr = "Fatal"; break;
    }

    QString sCurrDateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz");
    QString log = QString("[%1] - %2:%3 - %4 - %5\n").arg(sCurrDateTime, context.file)
            .arg(context.line).arg(typeStr, msg);

    QTextStream tsTextStream(&fMessFile);
    tsTextStream << log;

    tsTextStream.flush();
    fMessFile.flush();
    fMessFile.close();

    std::cout << log.toStdString();
}
