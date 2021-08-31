#include "VpnClient.h"

VpnClient::VpnClient(int argc, char **argv)
    : _console(NULL), _client(NULL), _pc(NULL) {
    Init(argc, argv);
}

VpnClient::~VpnClient() {
    Free();
}

void VpnClient::Connect(const char* serverName, const char* serverPass) {
    auto lengthServerName = strlen(serverName);
    auto lengthServerPass = strlen(serverPass);
    char* copyServerName = new char[lengthServerName + 1];
    char* copyServerPass = new char[lengthServerPass + 1];
    bzero(copyServerName, lengthServerName + 1);
    bzero(copyServerPass, lengthServerPass + 1);
    strncpy(copyServerName, serverName, lengthServerName + 1);
    strncpy(copyServerPass, serverPass, lengthServerPass + 1);

    bool badPass, noRemote;
    _client = CcConnectRpc(copyServerName, copyServerPass, &badPass, &noRemote, 0);
    if (_client == NULL) {
        if (noRemote) {
            QMessageBox::critical(NULL, PROGRAMM_NAME, "Remote Error");
        }
        else if (badPass) {
            QMessageBox::critical(NULL, PROGRAMM_NAME, "Password Error");
        }
        else {
            QMessageBox::critical(NULL, PROGRAMM_NAME, "Unknown Error");
        }
        exit(1);
    }
}

CONSOLE *VpnClient::GetConsole() {
    return _console;
}

REMOTE_CLIENT *VpnClient::GetRemoteClient() {
    return _client;
}

PC *VpnClient::GetPc() {
    return _pc;
}

void VpnClient::Init(int argc, char **argv) {
    InitMayaqua(MAYAQUA_DEBUG, MAYAQUA_DEBUG, argc, argv);
    InitCedar();
}

void VpnClient::Free() {
    FreeCedar();
    FreeMayaqua();
}
