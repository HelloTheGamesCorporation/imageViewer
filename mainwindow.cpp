#include "mainwindow.h"

#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QFileDialog>
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    light = R"(
    MainWindow {
        background-color: white;
    }

    QLabel {
        color: black;
    }

    QPushButton {
        background-color: #f0f0f0;
        color: black;
        border: 1px solid #ccc;
        border-radius: 7px;
        padding: 5px;
        width: 85px;
    }

    QPushButton:hover {
        border: 3px solid #ccc;
        border-radius: 7px;
    }

    QFileDialog {
        background-color: white;
        color: black;
    }

    QListView, QTreeView, QTableView {
        background-color: white;
        color: black;
    }

    QLineEdit {
        background-color: white;
        color: black;
    }

    QToolButton {
        background-color: white;
        color: black;
    }

    QFileDialog QWidget {
        background-color: white;
        color: black;
    }

    QFileDialog QToolBar {
        background-color: white;
        color: black;
    }

    QListView::item:selected, QTreeView::item:selected {
        background-color: #ccc;
        color: black;
    }

    QFileDialog QWidget#preview {
        background-color: #f5f5f5;
    }

    QComboBox {
        background-color: white;
        color: black;
    }
    )";

    dark = R"(
    MainWindow {
        background-color: #333;
    }

    QLabel {
        color: white;
    }

    QPushButton {
        background-color: #555;
        color: white;
        border: 1px solid #666;
        border-radius: 7px;
        padding: 5px;
        width: 85px;
    }

    QPushButton:hover {
        border: 3px solid #666;
        border-radius: 7px;
    }

    QFileDialog {
        background-color: #333;
        color: white;
    }

    QListView, QTreeView, QTableView {
        background-color: #333;
        color: white;
    }

    QLineEdit {
        background-color: #333;
        color: white;
    }

    QToolButton {
        background-color: #333;
        color: white;
    }

    QFileDialog QWidget {
        background-color: #333;
        color: white;
    }

    QFileDialog QToolBar {
        background-color: #333;
        color: white;
    }

    QListView::item:selected, QTreeView::item:selected {
        background-color: #666;
        color: white;
    }

    QFileDialog QWidget#preview {
        background-color: #454545;
    }

    QComboBox {
        background-color: #333;
        color: white;
    }
    )";

    setStyleSheet(light);

    setWindowTitle("Image Viewer");
    setFixedSize(800, 700);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *generalLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(generalLayout);
    setCentralWidget(centralWidget);

    imageLabel = new QLabel("");
    imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    imageLabel->setMinimumSize(400, 300);
    generalLayout->addWidget(imageLabel);

    QHBoxLayout *buttonsLayout = new QHBoxLayout(this);
    QPushButton *loadImageBtn = new QPushButton("↺ Load Image");
    changeThemeBtn = new QPushButton("☾ Dark");


    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    connect(loadImageBtn, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(changeThemeBtn, &QPushButton::clicked, this, &MainWindow::changeTheme);

    buttonsLayout->addWidget(loadImageBtn);
    buttonsLayout->addItem(spacer);
    buttonsLayout->addWidget(changeThemeBtn);
    generalLayout->addLayout(buttonsLayout);
}

void MainWindow::loadImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg);;All Files (*)");
    if (!filePath.isEmpty()) {
        QPixmap pixmap(filePath);
        if (!pixmap.isNull()) {
            originalPixmap = pixmap;
            resizeImage();
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    if(!originalPixmap.isNull()) {
        resizeImage();
    }
}

void MainWindow::resizeImage() {
    QPixmap scaled = originalPixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(scaled);
}

void MainWindow::changeTheme() {
    if (changeThemeBtn->text() == "☾ Dark") {
        setStyleSheet(dark);
        changeThemeBtn->setText("☀ Light");
    } else {
        setStyleSheet(light);
        changeThemeBtn->setText("☾ Dark");
    }
}

MainWindow::~MainWindow() {}
