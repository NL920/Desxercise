#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QCalendarWidget>
#include <QDate>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->calendarWidget->setSizePolicy(
    QSizePolicy::Expanding,
    QSizePolicy::Expanding
);

    setWindowTitle("Desxercise");
    resize(1200, 760);
    setMinimumSize(900, 600);

    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    updateSelectedDate(QDate::currentDate());

    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged,
            this, [this]() {
                updateSelectedDate(ui->calendarWidget->selectedDate());
            });

    connect(ui->addTrainingButton, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(
            this,
            "Add Training",
            "Tutaj dodamy formularz tworzenia treningu w kolejnym etapie."
        );
    });

    connect(ui->changeStatusButton, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(
            this,
            "Change Training Status",
            "Tutaj dodamy zmianę statusu treningu."
        );
    });

    connect(ui->routineButton, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(
            this,
            "My Training Routine",
            "Tutaj znajdzie się konfiguracja typów treningów i preferencji."
        );
    });

    connect(ui->settingsButton, &QPushButton::clicked,
            this, &MainWindow::showThemeSettings);

    connect(ui->aboutButton, &QPushButton::clicked, this, [this]() {
        QMessageBox::about(
            this,
            "About Desxercise",
            "Desxercise\\n\\nPlan • Train • Progress"
        );
    });

    applyTheme("Pink");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSelectedDate(const QDate &date)
{
    ui->selectedDateLabel->setText(date.toString("dddd, d MMMM yyyy"));

    // Na razie kalendarz nie jest jeszcze połączony z bazą danych.
    // W kolejnym etapie w tym miejscu pobierzemy treningi dla wybranej daty.
    ui->dayStatusLabel->setText("No trainings planned for this day.");
    ui->dayHintLabel->setText(
        "Your day is free. Desxercise will be able to suggest a workout here."
    );
}

void MainWindow::showThemeSettings()
{
    const QStringList themes = {
        "Pink", "Purple", "Blue", "Green", "Light"
    };

    bool accepted = false;
    const QString selectedTheme = QInputDialog::getItem(
        this,
        "Appearance",
        "Choose application theme:",
        themes,
        0,
        false,
        &accepted
    );

    if (accepted) {
        applyTheme(selectedTheme);
    }
}

void MainWindow::applyTheme(const QString &themeName)
{
    QString accent;
    QString accentHover;
    QString accentSoft;
    QString background;
    QString surface;
    QString text;
    QString border;

    if (themeName == "Purple") {
        accent = "#8954B8";
        accentHover = "#74439F";
        accentSoft = "#F0E5F8";
        background = "#FBF8FD";
        surface = "#FFFFFF";
        text = "#30243A";
        border = "#E8DDF0";
    } else if (themeName == "Blue") {
        accent = "#4387C7";
        accentHover = "#326FA9";
        accentSoft = "#E5F1FB";
        background = "#F7FAFD";
        surface = "#FFFFFF";
        text = "#203448";
        border = "#DCE8F3";
    } else if (themeName == "Green") {
        accent = "#399879";
        accentHover = "#2D8065";
        accentSoft = "#E3F3ED";
        background = "#F7FBF9";
        surface = "#FFFFFF";
        text = "#203A32";
        border = "#D9EAE3";
    } else if (themeName == "Light") {
        accent = "#687386";
        accentHover = "#535F70";
        accentSoft = "#EDF0F4";
        background = "#F5F6F8";
        surface = "#FFFFFF";
        text = "#252B35";
        border = "#E0E3E8";
    } else {
        // Domyślny motyw Desxercise: Pink.
        accent = "#D93686";
        accentHover = "#BD286F";
        accentSoft = "#FCE4F0";
        background = "#FFF7FB";
        surface = "#FFFFFF";
        text = "#42243A";
        border = "#F2D4E4";
    }

    const QString style = QString(R"(
        QMainWindow, QWidget#centralWidget {
            background-color: %1;
            color: %2;
            font-family: "Segoe UI";
            font-size: 10pt;
        }

        QFrame#sidebar, QFrame#detailsPanel {
            background-color: %3;
            border: 1px solid %4;
            border-radius: 14px;
        }

        QLabel#appNameLabel {
            color: %2;
            font-size: 21pt;
            font-weight: 700;
        }

        QLabel#taglineLabel, QLabel#mutedLabel, QLabel#dayHintLabel {
            color: #8A7182;
        }

        QLabel#sectionTitleLabel {
            color: %2;
            font-size: 15pt;
            font-weight: 700;
        }

        QPushButton {
            background-color: transparent;
            color: %2;
            border: none;
            border-radius: 9px;
            padding: 11px 13px;
            text-align: left;
        }

        QPushButton:hover {
            background-color: %5;
        }

        QPushButton#settingsButton {
            margin-top: 10px;
        }

        QCalendarWidget QWidget {
            alternate-background-color: %5;
        }

        QCalendarWidget QToolButton {
            color: %2;
            background-color: %3;
            border: none;
            border-radius: 7px;
            padding: 7px;
            font-weight: 600;
        }

        QCalendarWidget QToolButton:hover {
            background-color: %5;
        }

        QCalendarWidget QMenu {
            background-color: %3;
            color: %2;
        }

        QCalendarWidget QSpinBox {
            color: %2;
            background-color: %3;
            selection-background-color: %1;
        }

        QCalendarWidget QAbstractItemView {
            background-color: %3;
            color: %2;
            selection-background-color: %1;
            selection-color: white;
            outline: 0;
        }

        QCalendarWidget QAbstractItemView:enabled {
            font-size: 11pt;
        }

        QFrame#dayCard {
            background-color: %5;
            border: 1px solid %4;
            border-radius: 12px;
        }

        QLabel#emptyDayIcon {
            color: %1;
            font-size: 25pt;
            font-weight: 700;
        }

        QStatusBar {
            background-color: %3;
            color: #8A7182;
            border-top: 1px solid %4;
        }
    )").arg(accent, text, surface, border, accentSoft);

    setStyleSheet(style);
    statusBar()->showMessage(QString("Theme: %1").arg(themeName));
}
