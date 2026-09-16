#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_btnRemoveAll_clicked();

    void on_actionSave_As_2_triggered();

    void on_actionSave_2_triggered();

    void on_actionOpen_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::MainWindow *ui;
    QString file_path_;
    QUndoStack *undoStack;
};
#endif // MAINWINDOW_H
