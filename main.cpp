#include <QApplication>
#include <maingame.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainGame game;
    game.run();

    return app.exec();
}
