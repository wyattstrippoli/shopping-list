#ifndef REMOVEITEMCOMMAND_H
#define REMOVEITEMCOMMAND_H

#include <QUndoCommand>
#include <QListWidget>

//
// This command handles removing a single item from the list.
// When executed (redo), it removes the item.
// When undone, it re-inserts the original text back into the correct row.
//
class RemoveItemCommand : public QUndoCommand
{
public:
    RemoveItemCommand(QListWidget *list, int row, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), m_list(list), m_row(row)
    {
        // Save the text of the item being removed so we can restore it later.
        if (m_list && m_row >= 0 && m_row < m_list->count())
            m_text = m_list->item(m_row)->text();

        setText("Remove item");  // Name shown in Undo/Redo menus
    }

    // Undo removes the effect of redo -> reinsert the item
    void undo() override {
        if (!m_list) return;

        // Recreate the item using the stored text
        QListWidgetItem* item = new QListWidgetItem(m_text);
        item->setFlags(item->flags() | Qt::ItemIsEditable);

        // Put the item back into its original position
        m_list->insertItem(m_row, item);
    }

    // Redo performs the actual remove operation again
    void redo() override {
        if (!m_list) return;

        QListWidgetItem* it = m_list->takeItem(m_row);
        delete it;
    }

private:
    QListWidget *m_list{nullptr};  // Pointer to the list being modified
    int m_row{-1};                 // Row of the removed item
    QString m_text;                // Original text of the item
};


//
// This command handles "Remove All"
// Undo restores all removed items.
// Redo clears the list again.
//
class ClearListCommand : public QUndoCommand
{
public:
    ClearListCommand(QListWidget *list, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), listWidget(list)
    {
        // Save all item texts so Undo can restore them later
        for (int i = 0; i < listWidget->count(); ++i) {
            texts.append(listWidget->item(i)->text());
        }

        setText("Remove All Items");
    }

    // Undo re-adds all items in the same order as before
    void undo() override {
        for (int i = 0; i < texts.size(); ++i) {
            QListWidgetItem *item = new QListWidgetItem(texts[i]);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            listWidget->addItem(item);
        }
    }

    // Redo clears the list again
    void redo() override {
        listWidget->clear();
    }

private:
    QListWidget *listWidget;
    QStringList texts;
};

#endif // REMOVEITEMCOMMAND_H

