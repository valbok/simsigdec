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
#include <QThreadPool>
#include <QStringList>
#include <core/types.hpp>
#include <objects/Handler.hpp>

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
    void on_pushButton_clicked();

public slots:
    void finishedFile(const QString& filename, const QStringList& result);
    void processed(unsigned processed, unsigned total, unsigned infected);

private:
    void findFiles(QStringList& files);

private:
    Ui::MainWindow *ui;
    objects::Handler* mHandler;
    core::TSignaturesBySizes mSingnatures;
};

#endif // MAINWINDOW_H
