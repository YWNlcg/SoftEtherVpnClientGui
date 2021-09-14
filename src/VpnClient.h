#ifndef VPNCLIENT_H
#define VPNCLIENT_H

#include "CTypes.h"
#include "Types.h"
#include "LogHandler.h"

#define MAYAQUA_DEBUG false

class VpnClient {
public:
    VpnClient(int argc, char** argv);
    ~VpnClient();
    void connect(const char* serverName, const char* serverPass);
    CONSOLE* getConsole();
    REMOTE_CLIENT* getRemoteClient();
    PC* getPc();

private:
    void init(int argc, char** argv);
    void free();

private:
    CONSOLE* _console;
    REMOTE_CLIENT* _client;
    PC* _pc;
};

#endif // VPNCLIENT_H
