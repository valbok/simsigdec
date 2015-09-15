/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QStringList>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    /**
     * On clicked scan button.
     */
    void on_pushButton_clicked();

    /**
     * Emits when socket is connected.
     */
    void connected();

    /**
     * Emits when socket is disconnected.
     */
    void disconnected();

    /**
     * Main point to read data from server.
     */
    void readyRead();

    /**
     * Displayes an error as a dialog.
     */
    void displayError(QAbstractSocket::SocketError socketError);

private:

    /**
     * Searches files in dir reqursively.
     */
    void findFiles(QStringList& files);

private:

    /**
     * Main ui.
     */
    Ui::MainWindow *ui;

    /**
     * Socket to connect the server.
     */
    QTcpSocket mSocket;

    /**
     * Files to proceed.
     */
    QStringList mFiles;
};

#endif // MAINWINDOW_H
