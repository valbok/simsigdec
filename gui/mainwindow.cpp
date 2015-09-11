/**
 * @author VaL Doroshchuk <valbok@gmail.com>
 * @date Sep 2015
 * @copyright VaL Doroshchuk
 * @license GNU GPL v2
 * @package Simsigdec
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include <core/config.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mHandler(0)
{
    ui->setupUi(this);
    if (!core::config::read("signatures.txt", mSingnatures))
    {
        ui->textBrowser->insertHtml("<font color='red'>Could not read signatures from <b>signatures.txt</b></font><br/>\n");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mHandler;
}

void MainWindow::findFiles(QStringList& files)
{
    QString path = ui->pathEdit->text();
    ui->textBrowser->insertHtml("Reading from <b>" + path + "</b>:<br/>\n");
    ui->pushButton->setEnabled(false);
    QDirIterator it(path, QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
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
    if (mSingnatures.empty())
    {
        ui->textBrowser->insertHtml("No signatures! <br/>\n");
        return;
    }
    ui->pushButton->setEnabled(false);
    QStringList files;
    findFiles(files);

    if (files.size() > 0) {
        delete mHandler;
        mHandler = new objects::Handler(files, mSingnatures);
        connect(mHandler, SIGNAL(finishedFile(const QString&, const QStringList&)),
            this, SLOT(finishedFile(const QString&, const QStringList&)));

        connect(mHandler, SIGNAL(processed(unsigned, unsigned, unsigned)),
            this, SLOT(processed(unsigned, unsigned, unsigned)));

        mHandler->process();
    }
    else
    {
        ui->pushButton->setEnabled(true);
    }
}

void MainWindow::finishedFile(const QString& name, const QStringList& list)
{
    if (!list.empty())
    {
        QString infected = "<font color='red'>" +name + " infected by: </font><ul>\n";
        for (auto& r: list)
        {
            infected += "<li>" + r + "</li>";
        }
        infected += "</ul><br/>\n";
        ui->textBrowser->insertHtml(infected);
    }
}

void MainWindow::processed(unsigned processed, unsigned total, unsigned infected)
{
    ui->progressBar->setValue(processed * 100 / total);
    QString summary = "Found " + QString::number(infected) + " infected files!";
    ui->statusBar->showMessage(summary);
    if (processed == total)
    {
        ui->pushButton->setEnabled(true);
        ui->textBrowser->insertHtml(summary + "<br/>\n");
    }
}
