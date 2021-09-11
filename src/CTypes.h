#ifndef CTYPES_H
#define CTYPES_H

#define CRYPTO_TYPES_H

extern "C" {
#include <Cedar/Account.h>
#include <Cedar/Client.h>
//#include <Cedar/CedarType.h>
//#include <Cedar/Cedar.h>
#include <Cedar/Connection.h>

REMOTE_CLIENT *CcConnectRpc(char *server_name, char *password, bool *bad_pass, bool *no_remote, UINT wait_retry);
UINT CcCreateVLan(REMOTE_CLIENT *r, RPC_CLIENT_CREATE_VLAN *create);
UINT CcEnumVLan(REMOTE_CLIENT *r, RPC_CLIENT_ENUM_VLAN *e);
UINT CcEnableVLan(REMOTE_CLIENT *r, RPC_CLIENT_CREATE_VLAN *vlan);
UINT CcDisableVLan(REMOTE_CLIENT *r, RPC_CLIENT_CREATE_VLAN *vlan);
UINT CcCreateAccount(REMOTE_CLIENT *r, RPC_CLIENT_CREATE_ACCOUNT *a);
UINT CcDeleteAccount(REMOTE_CLIENT *r, RPC_CLIENT_DELETE_ACCOUNT *a);
UINT CcConnect(REMOTE_CLIENT *r, RPC_CLIENT_CONNECT *connect);
UINT CcDisconnect(REMOTE_CLIENT *r, RPC_CLIENT_CONNECT *connect);
<<<<<<< HEAD
=======
UINT CcGetAccountStatus(REMOTE_CLIENT *r, RPC_CLIENT_GET_CONNECTION_STATUS *st);
>>>>>>> restart-project
void CiFreeClientEnumVLan(RPC_CLIENT_ENUM_VLAN *e);
void Zero(void *addr, UINT size);

// Mayaqua/Encrypt.h
void Sha1(void *dst, void *src, UINT size);

// Mayaqua/Table.h
char *GetErrorStr(UINT err);
}

#endif // CTYPES_H
