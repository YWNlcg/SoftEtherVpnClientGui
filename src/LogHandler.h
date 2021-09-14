#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include <QLoggingCategory>
#include <QDateTime>
#include <QTextStream>
#include <QDir>
#include <iostream>

Q_DECLARE_LOGGING_CATEGORY(DefLog)

#define logInfo(category, ...)     qCInfo(category, __VA_ARGS__)
#define logWarning(category, ...)  qCWarning(category, __VA_ARGS__)
#define logDebug(category, ...)    qCDebug(category, __VA_ARGS__)
#define logCritical(category, ...) qCCritical(category, __VA_ARGS__)
#define logFatal(category, ...)    qCFatal(category, __VA_ARGS__)

#define LOG_FILENAME "sevpn.log"

void logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // LOGHANDLER_H
