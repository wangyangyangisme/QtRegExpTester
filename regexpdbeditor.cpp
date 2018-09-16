#include "regexpdbeditor.h"

RegExpDbEditor::RegExpDbEditor(QWidget *parent) :
    QWidget(parent)
{
    db = new RegExpDb();

    /* Create toolbar */
    QToolBar *toolBar1 = new QToolBar(this);
    addAction = new QAction("Add", this);
    delAction = new QAction("Del", this);
    editAction = new QAction("Edit", this);
    insertAction = new QAction("Insert", this);
    toolBar1->addAction(addAction);
    toolBar1->addAction(editAction);
    toolBar1->addAction(delAction);


    QToolBar *toolBar2 = new QToolBar(this);
    QLabel *label = new QLabel("Search:", this);
    searchLineEdit = new QLineEdit(this);
    toolBar2->addWidget(label);
    toolBar2->addWidget(searchLineEdit);


    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    regExpListView = new QListView(this);
    regExpListView->setModel(db->model);
    regExpListView->setModelColumn(0);
    regExpEdit = new QTextEdit(this);
    regExpEdit->setReadOnly(true);
    splitter->addWidget(regExpListView);
    splitter->addWidget(regExpEdit);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(toolBar1);
    mainLayout->addWidget(toolBar2);
    mainLayout->addWidget(splitter);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    connect(addAction, SIGNAL(triggered()), this, SLOT(addRegExp()));
    connect(delAction, SIGNAL(triggered()), this, SLOT(delRegExp()));
    connect(editAction, SIGNAL(triggered()), this, SLOT(editRegExp()));
    connect(insertAction, SIGNAL(triggered()), this, SLOT(insertRegExp()));
    connect(regExpListView, SIGNAL(clicked(QModelIndex)), this, SLOT(currentItemChanged(QModelIndex)));
    connect(searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(findItem(QString)));

    regExpListView->viewport()->installEventFilter(this);
}

void RegExpDbEditor::addRegExp()
{
    AddEditDialog dialog(0, this);
    connect(&dialog, SIGNAL(okPressed()), this, SLOT(addEditRegExpCheck()));
    dialog.exec();
    disconnect(&dialog);
}

void RegExpDbEditor::editRegExp()
{
    if(regExpListView->currentIndex().isValid())
    {
        QString name  = regExpListView->currentIndex().data().toString();
        QString value = db->getValue(name);

        AddEditDialog dialog(1, this);
        dialog.setName(name);
        dialog.setValue(value);

        connect(&dialog, SIGNAL(okPressed()), this, SLOT(addEditRegExpCheck()));
        dialog.exec();
        disconnect(&dialog);
    }
    else
        QMessageBox::warning(this, "Error", "Select row", QMessageBox::Ok);
}

void RegExpDbEditor::addEditRegExpCheck()
{
    AddEditDialog *dialog = (AddEditDialog*) sender();

    if(dialog->isEdit)
    {
        if(db->updateRow(dialog->getPrevName(), dialog->getName(), dialog->getValue()))
            dialog->accept();
        else
        {
            QString errorStr = db->lastError();
            if(errorStr.contains("column name is not unique"))
            {
                errorStr = "Record with name \"%1\" already exist";
                errorStr = errorStr.arg(dialog->getName());
            }
            QMessageBox::warning(this, "Error", errorStr, QMessageBox::Ok);
        }
    }
    else
    {
        if(db->insertRow(dialog->getName(), dialog->getValue()))
            dialog->accept();
        else
        {
            QString errorStr = db->lastError();
            if(errorStr.contains("column name is not unique"))
            {
                errorStr = "Record with name \"%1\" already exist";
                errorStr = errorStr.arg(dialog->getName());
            }
            QMessageBox::warning(this, "Error", errorStr, QMessageBox::Ok);
        }
    }
}

void RegExpDbEditor::delRegExp()
{
    if(regExpListView->currentIndex().isValid())
    {
        QString str  = regExpListView->currentIndex().data().toString();
        if(QMessageBox::question(this, "Confirm",
                                 "Are you sure to delete record?",
                                 QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok)
        {
            db->deleteRow(str);
            db->model->select();
        }
    }
    else
        QMessageBox::warning(this, "Error", "Select row", QMessageBox::Ok);
}

void RegExpDbEditor::insertRegExp()
{
    if(regExpListView->currentIndex().isValid())
    {
        QString name = regExpListView->currentIndex().data().toString();
        emit insertRegExp(db->getValue(name));
    }
    else
        QMessageBox::warning(this, "Error", "Select row", QMessageBox::Ok);
}

void RegExpDbEditor::currentItemChanged(QModelIndex index)
{
    QModelIndex temp = db->model->index(index.row(), 1);
    regExpEdit->setText(temp.data().toString());
}

void RegExpDbEditor::findItem(QString pattern)
{
    db->model->setFilter(QString("name LIKE \'").append(pattern).append("%\'"));
}

bool RegExpDbEditor::eventFilter(QObject *watched, QEvent* e)
{
    if (watched == regExpListView->viewport() && e->type() == QEvent::MouseButtonDblClick)
    {
        return true;
    }
    return QWidget::eventFilter(watched, e);
}

void RegExpDbEditor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(addAction);
    menu.addAction(editAction);
    menu.addAction(delAction);
    menu.addSeparator();
    menu.addAction(insertAction);
    menu.exec(event->globalPos());
}
