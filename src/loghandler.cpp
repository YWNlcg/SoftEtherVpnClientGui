#include "Types.h"

void log_handler(QtMsgType type, const char *msg) {
    QString curr_date_time = "[" +
              QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") + "]";

    switch(type) {
    case QtDebugMsg:
        cout << QString("%1 Debug - %2").arg(curr_date_time).arg(msg).toStdString() << "\n";
        break;
    case QtWarningMsg:
        cout << QString("%1 Warning - %2").arg(curr_date_time).arg(msg).toStdString() << "\n";
        break;
    case QtCriticalMsg:
        cout << QString("%1 Critical - %2").arg(curr_date_time).arg(msg).toStdString() << "\n";
        break;
    case QtFatalMsg:
        cout << QString("%1 Fatal - %2").arg(curr_date_time).arg(msg).toStdString() << "\n";
        abort();
    }
}
