#pragma once

#include <QMainWindow>
#include <QString>

class QDate;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void updateSelectedDate(const QDate &date);
    void applyTheme(const QString &themeName);
    void showThemeSettings();
};
