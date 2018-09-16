#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle("Regular Expression Tester v0.2");

    regExp = new QRegExp();
    regExp->setPatternSyntax(QRegExp::RegExp2);

    QStringList colors;
    colors << "blueviolet" << "tomato" << "cyan" << "blue" << "magenta" << "yellowgreen"
            << "darkRed" << "darkBlue" << "darkMagenta" << "darkCyan" << "darkorange"
            << "thistle" << "skyblue" << "mediumvioletred" << "brown" << "peachpuff";

    /*-------- Regual Expression input ---------*/
    QPushButton *button = new QPushButton("Match");
    button->setFixedWidth(50);
    button->setShortcut(QKeySequence::QKeySequence("Ctrl+M"));

    QLabel *label1 = new QLabel("Pattern Syntax:", this);
    QComboBox *patternSyntaxSelector = new QComboBox(this);
    QStringList patternList;
    patternList << "RegExp" << "Wildcard" << "FixedString" << "RegExp2" << "WildcardUnix" << "W3CXmlSchema11";
    patternSyntaxSelector->addItems(patternList);
    patternSyntaxSelector->setCurrentIndex(3); //Default value

    QLabel *label2 = new QLabel("Minimal Match:", this);
    QComboBox *minMatchSelector = new QComboBox(this);
    minMatchSelector->addItem("False"); //Default value
    minMatchSelector->addItem("True");

    QToolBar *toolBar = new QToolBar(this);
    toolBar->addWidget(button);
    toolBar->addWidget(label1);
    toolBar->addWidget(patternSyntaxSelector);
    toolBar->addSeparator();
    toolBar->addWidget(label2);
    toolBar->addWidget(minMatchSelector);

    regExpInput = new RegExpEdit(this);
    regExpInput->setColors(colors);
//    regExpInput->setText("(\\d*) (.*)");
    QWidget *tempWidget1 = new QWidget(this);
    QVBoxLayout *tempWidget1Layout = new QVBoxLayout(tempWidget1);
    tempWidget1Layout->setContentsMargins(0,0,0,0);
    tempWidget1Layout->setSpacing(0);
    tempWidget1Layout->addWidget(regExpInput);
    tempWidget1Layout->addWidget(toolBar);

    /*-------- Data input ---------------------*/
    dataInput = new TextEdit(this);
    dataInput->setColors(colors);
//    dataInput->setText("123 abcd");

    /*-------- Db Editor --------------------*/
    RegExpDbEditor *dbEditor = new RegExpDbEditor(this);

    /*-------- Status bar -------------*/
    QStatusBar *statusBar = new QStatusBar(this);
    QLabel *barLabel1 = new QLabel("Exact Match:", this);
    exactMatchStatus = new QLabel(this);
    exactMatchStatus->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    exactMatchStatus->setFixedWidth(70);

    QLabel *barLabel2 = new QLabel("Capture Count:", this);
    matchCount = new QLabel(this);
    matchCount->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    matchCount->setFixedWidth(70);

    statusBar->addPermanentWidget(barLabel1);
    statusBar->addPermanentWidget(exactMatchStatus);
    statusBar->addPermanentWidget(barLabel2);
    statusBar->addPermanentWidget(matchCount);

    setStatusBar(statusBar);


    /*-------- Right splitter --------------------*/
    QSplitter *splitter1 = new QSplitter(Qt::Vertical, this);
    splitter1->addWidget(tempWidget1);
    splitter1->addWidget(dataInput);
    splitter1->setStretchFactor(0, 1);
    splitter1->setStretchFactor(1, 3);

    /*-------- Main splitter --------------------*/
    QSplitter *splitter2 = new QSplitter(this);
    splitter2->addWidget(dbEditor);
    splitter2->addWidget(splitter1);

    splitter2->setStretchFactor(0, 2);
    splitter2->setStretchFactor(1, 4);



    /*-------- Central widget ---------------------*/
    setCentralWidget(splitter2);




    connect(button, SIGNAL(pressed()), this, SLOT(match()));
    connect(regExpInput, SIGNAL(returnPressed()), this, SLOT(match()));
    connect(patternSyntaxSelector, SIGNAL(activated(int)), this, SLOT(setPatternSyntax(int)));
    connect(minMatchSelector, SIGNAL(activated(int)), this, SLOT(setMinimal(int)));
    connect(dbEditor, SIGNAL(insertRegExp(QString)), regExpInput, SLOT(insertPlainText(QString)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::match()
{
    regExpInput->highlight();
    QString regExpStr = regExpInput->toPlainText();
    regExp->setPattern(regExpStr);

    QString result;
    dataInput->exactMatch(regExp, &result);
    exactMatchStatus->setText(result);

    int captureCount =  regExp->captureCount();
    matchCount->setText(QString::number(captureCount));   
}


void MainWindow::setPatternSyntax(int pattern)
{
    regExp->setPatternSyntax((QRegExp::PatternSyntax)pattern);
}

void MainWindow::setMinimal(int minimal)
{
    regExp->setMinimal(minimal);
}
