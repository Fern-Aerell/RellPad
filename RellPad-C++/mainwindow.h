#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void open_With_File(QString file_location);

private slots:
    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionCopy_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionDelete_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionNew_WIndow_triggered();

    void on_textEdit_textChanged();

    void openFile();

    void updateLineAndColum();

    void on_textEdit_cursorPositionChanged();

    void on_actionSelect_All_triggered();

    void on_actionFind_triggered();

    void on_actionGithub_triggered();

    void on_actionYoutube_triggered();

    void on_actionAbout_RellPad_triggered();

private:
    Ui::MainWindow *ui;
    QString file_path;
    QString encoding;
};
#endif // MAINWINDOW_H
