#ifndef EXTERN_H
#define EXTERN_H

#include <QTextStream>
#include "CmdAdapter.h"

void log_handler(QtMsgType type, const char *msg);
CmdAdapter& GetCmdAdapterInstance();

#endif // EXTERN_H
