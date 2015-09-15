/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDirIterator>
#include <QStringList>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&mSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(&mSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(&mSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readyRead()
{
    unsigned processed = 0;
    unsigned total = 0;
    unsigned infected = 0;
    QString response = mSocket.readAll();
    if (response.isEmpty())
    {
        return;
    }

    QStringList list = response.split("\n");
    for(auto& r: list)
    {
        if (r.isEmpty())
        {
            continue;
        }

        QJsonDocument d = QJsonDocument::fromJson(r.toUtf8());
        QJsonObject root = d.object();
        processed = root["processed"].toString().toInt();
        total = root["total"].toString().toInt();
        infected = root["infected"].toString().toInt();
        if (total > 0)
        {
            ui->progressBar->setValue(processed * 100 / total);
        }
        QString filename = root["filename"].toString();
        QJsonArray result = root["result"].toArray();
        if (!result.isEmpty())
        {
            QString summary = "<font color='red'>" + filename + " infected by: </font><ul>\n";
            foreach (const QJsonValue & r, result)
            {
                summary += "<li>" + r.toString() + "</li>";
            }
            summary += "</ul><br/>\n";
            ui->textBrowser->insertHtml(summary);
        }
    }

    QString summary = "Found " + QString::number(infected) + " infected files!";
    ui->statusBar->showMessage(summary);
    if (processed == total)
    {
        ui->textBrowser->insertHtml(summary + "<br/>\n");
    }
}

void MainWindow::disconnected()
{
    ui->pushButton->setEnabled(true);
}

void MainWindow::connected()
{
    QString req = mFiles.join("\n");
    mSocket.write(req.toLocal8Bit().constData());
}

void MainWindow::findFiles(QStringList& files)
{
    QString path = ui->pathEdit->text();
    ui->textBrowser->insertHtml("Reading from <b>" + path + "</b>:<br/>\n");
    QDirIterator it(path, QStringList() << "*", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString s = it.next();
        files.push_back(s);
        ui->statusBar->showMessage(QString::number(files.size()) + "> " + s);
    }

    ui->textBrowser->insertHtml("Checking " + QString::number(files.size()) + " files<br/>\n");
}

void MainWindow::on_pushButton_clicked()
{
    mFiles = QStringList();
    findFiles(mFiles);
    if (!mFiles.isEmpty())
    {
        ui->pushButton->setEnabled(false);
        mSocket.connectToHost("localhost", 6666);
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    ui->pushButton->setEnabled(true);
    if (socketError == QTcpSocket::RemoteHostClosedError)
    {
        return;
    }

    QMessageBox::critical(this, tr("Network error"),
        tr("The following error occurred: %1.")
        .arg(mSocket.errorString()));

    mSocket.close();
    ui->progressBar->setValue(0);
}