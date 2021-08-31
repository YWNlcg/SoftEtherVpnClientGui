#ifndef VPNCLIENT_H
#define VPNCLIENT_H

#include "CTypes.h"
#include "Types.h"

#define MAYAQUA_DEBUG false

class VpnClient {
public:
    VpnClient() {};
    VpnClient(int argc, char** argv);
    ~VpnClient();
    void Connect(const char* serverName, const char* serverPass);
    CONSOLE* GetConsole();
    REMOTE_CLIENT* GetRemoteClient();
    PC* GetPc();

private:
    void Init(int argc, char** argv);
    void Free();

private:
    CONSOLE* _console;
    REMOTE_CLIENT* _client;
    PC* _pc;
};

#endif // VPNCLIENT_H
