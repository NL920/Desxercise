#include <QApplication>
#include "../ui/MainWindow.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}



/*mkdir build
cd build
cmake ..
cmake --build .
*/

/*sqlite3 trainings.db
.tables
.schema trainings
.quit*/