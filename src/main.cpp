#include "MainWindow.h"

#include <QApplication>
#include "VpnClient.h"
#include "CmdAdapter.h"
<<<<<<< HEAD

=======
#include "ContextMenuAccount.h"
#include "ContextMenuNic.h"
>>>>>>> restart-project
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

<<<<<<< HEAD

    MainWindow w;


=======
    MainWindow w;

    w.setCMenuNics(new ContextMenuNic(&w));
    w.setCMenuVpnAcc(new ContextMenuAccount(&w));
>>>>>>> restart-project

    w.show();
    return a.exec();
}
