// Shopping List
// Wyatt Strippoli
// This project is an application that allows the user to create shopping lists with the names and quantities of items.
// They can then save the list as a text file that can be reopened at a later date and edited if needed.

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "removeitemcommand.h"

#include <QUndoCommand>
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidget>
#include <QUndoStack>
#include <QAction>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    undoStack = new QUndoStack(this);

    // Loads default file from Documents
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\listFile.txt");

    if(!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Event handler for add button
void MainWindow::on_btnAdd_clicked()
{
    // Gets the item name
    QString name = ui->txtItem->text().trimmed();
    if (name.isEmpty()) {
        ui->txtItem->setFocus();
        return;
    }

    // Gets the item quantity (default 1)
    int qty = 1;
    if (ui->spinQty)
        qty = ui->spinQty->value();

    // Format as “Item x Quantity”
    QString text = QString("%1 x %2").arg(name).arg(qty);

    // Adds item to the list and makes it editable
    QListWidgetItem* item = new QListWidgetItem(text, ui->listWidget);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);

    // Reset UI fields
    ui->txtItem->clear();
    if (ui->spinQty) ui->spinQty->setValue(1);
    ui->txtItem->setFocus();
}

// Event handler for remove button
void MainWindow::on_btnRemove_clicked()
{
    int row = ui->listWidget->currentRow();
    if (row < 0)
        return;

    // Adds removed item to a stack of items
    undoStack->push(new RemoveItemCommand(ui->listWidget, row));
}

// Event handler for remove all button
void MainWindow::on_btnRemoveAll_clicked()
{
    undoStack->push(new ClearListCommand(ui->listWidget));
}

// Event handler for save as button
void MainWindow::on_actionSave_As_2_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QTextStream out(&file);

    // Write list entries exactly as displayed
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        out << item->text() << "\n";
    }

    file.close();
    file_path_ = fileName;
    // Displays a message box to let the user know the file has been succesfully saved
    QMessageBox::information(this, tr("File Saved"), tr("The list widget contents have been saved to %1").arg(fileName));
}

// Event handler for save button
void MainWindow::on_actionSave_2_triggered()
{
    if (file_path_.isEmpty()) {
        on_actionSave_As_2_triggered();
        return;
    }

    // Handles error if the file can't be saved
    QFile file(file_path_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save to file");
        return;
    }

    QTextStream out(&file);

    // Save item text including quantity format
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        out << ui->listWidget->item(i)->text() << "\n";
    }

    file.close();
    // Displays a message box to let the user know the file has been succesfully saved
    QMessageBox::information(this, "Saved", "File saved successfully.");
}

// Event handler for open button
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "",
        tr("Text Files (*.txt);;All Files (*)")
        );

    if (fileName.isEmpty())
        return;

    // Handles error if the file can't be opened
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "Could not open the file");
        return;
    }

    ui->listWidget->clear();

    QTextStream in(&file);
    QRegularExpression re(R"((.+)\s+x\s+(\d+)$)");

    // Loop that makes every item within the list is formated correctly when read from the file
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QRegularExpressionMatch m = re.match(line);
        if (m.hasMatch()) {
            QString name = m.captured(1).trimmed();
            int qty = m.captured(2).toInt();
            QString text = QString("%1 x %2").arg(name).arg(qty);
            QListWidgetItem *item = new QListWidgetItem(text);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            ui->listWidget->addItem(item);
        } else {
            QListWidgetItem *item = new QListWidgetItem(line);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            ui->listWidget->addItem(item);
        }
    }

    file.close();
    file_path_ = fileName;
}

// Event handler for undo button (See removeitemcommand.h to see functionality)
void MainWindow::on_actionUndo_triggered()
{
    undoStack->undo();
}

// Event handler for redo button (See removeitemcommand.h to see functionality)
void MainWindow::on_actionRedo_triggered()
{
    undoStack->redo();
}

