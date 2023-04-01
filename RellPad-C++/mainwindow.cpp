#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <finddialog.h>
#include <aboutdialog.h>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    ui->textEdit->setStyleSheet("QTextEdit:focus { border: 1px solid transparant; }");
    setWindowTitle("Untitled - RellPad");

    ui->statusbar->addPermanentWidget(ui->label_dummy);
    ui->statusbar->addPermanentWidget(ui->line_col_label);
    ui->statusbar->addPermanentWidget(ui->zoom_label);
    ui->zoom_label->setText("");
    updateLineAndColum();
}

MainWindow::~MainWindow()
{
    delete ui;
}


///File Features
///
///
//Tombol New
void MainWindow::on_actionNew_triggered()
{
    //Jika textEdit teredit.
    if(windowTitle().startsWith("*"))
    {
        //Keluarkan notif peringatan kalau file belum di save.
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Unsaved Changes", "Do you want to save changes to the current document?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        //Mengecek pilihan
        switch (button) {
            case QMessageBox::Save: //Jika memilih save
                on_actionSave_triggered(); //Memanggil fungsi save
                break;
            case QMessageBox::Discard: //Jika memilih discard //Mengatur isEdited ke false
                setWindowTitle("Untitled - RellPad"); //Set Window title
                on_actionNew_triggered();//Memanggil fungsi ini lagi
                break;
            case QMessageBox::Cancel: //Jika memilih cancel
            default:
                break;
        }

        return;
    }

    //Jika textEdit tidak teredit
    file_path = ""; //kosongin file path
    ui->textEdit->setText(""); //kosongin editText
    setWindowTitle("Untitled - RellPad"); //Set Window title
}

//Tombol Open
void MainWindow::on_actionOpen_triggered()
{
    //Cek apakah text telah di edit atau tidak
    if(windowTitle().startsWith("*"))
    {
        //Munculkan notif kalau text belum di edit.
        QMessageBox::StandardButton choice = QMessageBox::warning(this, "Unsaved Changes", "Do you want to save changes to the current document?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        //Ngecek pilihan
        switch (choice) {
            case QMessageBox::Save: //Jika memilih save
                on_actionSave_triggered(); //Panggil fungsi save
                break;
            case QMessageBox::Discard: //Jika memilih discard
                openFile(); //Panggil fungsi openFile
                break;
            case QMessageBox::Cancel: //Jika memilih cancel
            default:
                break;
        }

        return;
    }

    //Jika text belum di edit.
    openFile();
}

//Fungsi untuk membuka file
void MainWindow::openFile()
{
    //Membuka file
    QString file_location = QFileDialog::getOpenFileName(this, "Open file", "", "Text Document (*.txt);;All Files (*.*)");

    //Cek Apakah file lokasi kosong atau tidak
    if(!file_location.isEmpty())
    {
        //Memasukkan lokasi file ke object file
        QFile file(file_location);

        //Buka file dan cek apakah file bisa dibuka apa tidak?
        if(!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "..", "File can't open.");
            return;
        }

        //Menaruh file_location ke variable global
        file_path = file_location;

        //Membaca file
        QTextStream in (&file);
        QString text = in.readAll();

        //Set text pada textedit
        ui->textEdit->setText(text);

        //Merubah Window Title Menjadi Nama File.extension
        QFileInfo file_info(file_location);
        setWindowTitle(file_info.fileName() + " - RellPad");
    }
}

//Tombol Save
void MainWindow::on_actionSave_triggered()
{
    if(!file_path.isEmpty())
    {
        //Memasukkan lokasi file global ke object file
        QFile file(file_path);

        //Buka file dan cek apakah file bisa dibuka apa tidak?
        if(!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "..", "File can't save");
            return;
        }

        //Membaca file
        QTextStream out (&file);
        //Mengambil text dari textEdit ke variable
        QString text = ui->textEdit->toPlainText();
        //Menuliskan text ke variable out
        out << text;

        // memastikan semua data dituliskan ke file
        file.flush();
        // menutup file
        file.close();

        //Merubah Window Title Menjadi Nama File.extension
        QFileInfo file_info(file_path);
        setWindowTitle(file_info.fileName() + " - RellPad");
    }else{

        //Munculkan tab untuk save file
        QString file_location = QFileDialog::getSaveFileName(this, "Save This File", "", "Text Document (*.txt);;All Files (*.*)");

        //Cek apkah file lokasi kosong atau tidak
        if(!file_location.isEmpty())
        {
            //Memasukkan lokasi file ke sebuah object
            QFile file(file_location);

            //Buka file, dan cek apakah file bisa di buka atau tidak?
            if(!file.open(QFile::WriteOnly | QFile::Text))
            {
                QMessageBox::warning(this, "..", "File can't save");
                return;
            }

            //Memasukkan lokasi file ke variable global
            file_path = file_location;

            //Membaca file
            QTextStream out (&file);
            //Mengambil text dari textEdit ke variable
            QString text = ui->textEdit->toPlainText();
            //Menuliskan text ke variable out
            out << text;

            // memastikan semua data dituliskan ke file
            file.flush();
            // menutup file
            file.close();

            //Merubah Window Title Menjadi Nama File.extension
            QFileInfo file_info(file_location);
            setWindowTitle(file_info.fileName() + " - RellPad");
        }
    }
}

//Tombol Save As
void MainWindow::on_actionSave_As_triggered()
{
    //Munculkan tab untuk save as file
    QString file_location = QFileDialog::getSaveFileName(this, "Save As This File", "", "Text Document (*.txt);;All Files (*.*)");

    //Cek apakah file_name tidak kosong?
    if(!file_location.isEmpty())
    {
        //Memasukkan lokasi file ke sebuah object
        QFile file(file_location);

        //Buka file dan cek apakah file bisa dibuka apa tidak?
        if(!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "..", "File can't save as");
            return;
        }

        //Memasukkan lokasi file ke variable global
        file_path = file_location;

        //Membaca file
        QTextStream out (&file);
        //Mengambil text dari textEdit ke variable
        QString text = ui->textEdit->toPlainText();
        //Menuliskan text ke variable out
        out << text;

        // memastikan semua data dituliskan ke file
        file.flush();
        // menutup file
        file.close();

        //Merubah Window Title Menjadi Nama File.extension
        QFileInfo file_info(file_location);
        setWindowTitle(file_info.fileName() + " - RellPad");

    }
}

//Tombol New Window
void MainWindow::on_actionNew_WIndow_triggered()
{
    MainWindow *window = new MainWindow();
    window->show();
}

//Jika Text Edit Berubah
void MainWindow::on_textEdit_textChanged()
{
    //File di edit
    if(!windowTitle().startsWith("*"))
    {
        setWindowTitle("*" + windowTitle());
    }

    //Apakah bisa di undo?
    ui->actionUndo->setEnabled(ui->textEdit->document()->isUndoAvailable());

    //Apakah bisa di redo?
    ui->actionRedo->setEnabled(ui->textEdit->document()->isRedoAvailable());

    //Apakah Bisa Paste?
    ui->actionPaste->setEnabled(ui->textEdit->canPaste());
}

//Jika CusorPosition Pada Text Edit Berubah
void MainWindow::on_textEdit_cursorPositionChanged()
{
    updateLineAndColum();
}

//Get Line And Column
void MainWindow::updateLineAndColum()
{
    QTextCursor cursorPosition = ui->textEdit->textCursor();
    int colum = cursorPosition.columnNumber() + 1;
    int line = cursorPosition.blockNumber() + 1;
    ui->line_col_label->setText(" Ln " + QString::number(line) + ", Col " + QString::number(colum) + "\t\t");

    //Apakah bisa copy?
    ui->actionCopy->setEnabled(cursorPosition.hasSelection());

    //Apakah bisa delete?
    ui->actionDelete->setEnabled(cursorPosition.hasSelection());

    //Apkah bisa di selectAll?
    ui->actionSelect_All->setEnabled(colum > 1 || line > 1);

    //Apkah bisa di cut?
    ui->actionCut->setEnabled(cursorPosition.hasSelection());
}

//Tombol Exit
void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

///Edit Features
///
///
//Tombol Undo
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

//Tombol Redo
void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

//Tombol Cut
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

//Tombol Copy
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

//Tombol Paste
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

//Tombol Hapus
void MainWindow::on_actionDelete_triggered()
{
    // Mengambil kursor teks dari textEdit
    QTextCursor cursor = ui->textEdit->textCursor();

    // Mengecek apakah ada teks yang dipilih
    if (cursor.hasSelection()) {
        // Menghapus teks yang dipilih
        cursor.removeSelectedText();
    }
}

//Tombol Select All
void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

//Tombol Find
void MainWindow::on_actionFind_triggered()
{
    FindDialog* findDialog = new FindDialog();
    findDialog->setModal(false);
    findDialog->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    findDialog->show();
}

///Help Button
///
//Github
void MainWindow::on_actionGithub_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/AerellDev/RellPad"));
}

//Youtube
void MainWindow::on_actionYoutube_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/channel/UClrf-q-Ktm5GtLGZ3yKj0Nw?sub_confirmation=1"));
}

//About
void MainWindow::on_actionAbout_RellPad_triggered()
{
    AboutDialog* aboutDialog = new AboutDialog();
    aboutDialog->setModal(true);
    aboutDialog->setWindowFlags(Qt::WindowCloseButtonHint);

    aboutDialog->show();
}

























