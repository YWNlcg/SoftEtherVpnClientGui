#include "MainWindow.h"

#include <QApplication>
#include "VpnClient.h"
#include "CmdAdapter.h"
#include "ContextMenuAccount.h"
#include "ContextMenuNic.h"
#include "CTypes.h"

CmdAdapter& GetCmdAdapterInstance() {
    static CmdAdapter cmdAdapter;
    return cmdAdapter;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    VpnClient cl(argc, argv);
    cl.connect("localhost", "");
    auto& cmdAdapter = GetCmdAdapterInstance();
    cmdAdapter.init(&cl);

    MainWindow w;

    w.setCMenuNics(new ContextMenuNic(&w));
    w.setCMenuVpnAcc(new ContextMenuAccount(&w));

    w.show();
    return a.exec();
}
