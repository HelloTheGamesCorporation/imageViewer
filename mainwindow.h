#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void loadImage();
    void resizeImage();
    void changeTheme();

private:
    QLabel *imageLabel;
    QPushButton *changeThemeBtn;
    QPixmap originalPixmap;
    QString dark;
    QString light;
};
#endif // MAINWINDOW_H
