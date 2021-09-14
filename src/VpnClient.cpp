#include "VpnClient.h"

VpnClient::VpnClient(int argc, char **argv)
    : _console(NULL), _client(NULL), _pc(NULL) {
    logInfo(DefLog, "Init Vpn Client");
    init(argc, argv);
}

VpnClient::~VpnClient() {
    free();
}

void VpnClient::connect(const char* serverName, const char* serverPass) {
    logInfo(DefLog, "Connecting to %s...", serverName);

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
            logCritical(DefLog, "Remote error");
            QMessageBox::critical(NULL, PROGRAMM_NAME, "Remote Error");
        }
        else if (badPass) {
            logCritical(DefLog, "Password error");
            QMessageBox::critical(NULL, PROGRAMM_NAME, "Password Error");
        }
        else {
            logCritical(DefLog, "Error connect to daemon. Please start SoftEtherVpn Service");
            QMessageBox::critical(NULL, PROGRAMM_NAME, "Unknown Error");
        }
        exit(1);
    }
    logInfo(DefLog, "Connect to %s", serverName);
}

CONSOLE *VpnClient::getConsole() {
    return _console;
}

REMOTE_CLIENT *VpnClient::getRemoteClient() {
    return _client;
}

PC *VpnClient::getPc() {
    return _pc;
}

void VpnClient::init(int argc, char **argv) {
    logDebug(DefLog, "Init Mayaqua");
    InitMayaqua(MAYAQUA_DEBUG, MAYAQUA_DEBUG, argc, argv);
    logDebug(DefLog, "Init Cedar");
    InitCedar();
}

void VpnClient::free() {
    logDebug(DefLog, "Free Cedar");
    FreeCedar();
    logDebug(DefLog, "Free Mayaqua");
    FreeMayaqua();
}
