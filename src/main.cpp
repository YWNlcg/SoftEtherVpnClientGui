#include "MainWindow.h"

#include <QApplication>
#include "VpnClient.h"
#include "CmdAdapter.h"

#include "CTypes.h"

CmdAdapter& GetCmdAdapterInstance() {
    static CmdAdapter cmdAdapter;
    return cmdAdapter;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    VpnClient cl(argc, argv);
    cl.Connect("localhost", "");
    auto& cmdAdapter = GetCmdAdapterInstance();
    cmdAdapter.init(&cl);


    MainWindow w;



    w.show();
    return a.exec();
}
