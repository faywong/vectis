#include "vmainwindow.h"
#include "ui_vmainwindow.h"
#include <QPainter>
#include <QScrollArea>
#include <QLayout>

#include <QDebug>

VMainWindow::VMainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VMainWindow)
{
    // Set the window maximize / minimize / exit buttons
    Qt::WindowFlags flags = Qt::Window   |
            Qt::WindowMaximizeButtonHint |
            Qt::WindowMinimizeButtonHint |
            Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
    // Set the background color for window. Notice: style sheets are
    // more portable than modifying the palette directly
    /* this->setStyleSheet("QDialog { background-color: #272822; }"); */

    ui->setupUi(this);

    // Crea il controllo code editor
    m_customCodeEdit = std::make_unique<CodeTextEdit>(this);
    ui->codeTextEditArea->addWidget(m_customCodeEdit.get());

    qWarning() << "TODO: muovi lo stylesheet e il font setting DENTRO il controllo, non qui!";
    // Set background color for the edit code control
    m_customCodeEdit->setStyleSheet("QTextEdit {                                        \
                                     background-color: #272822;                         \
                                     color: white;                                      \
                                     border: 0px;                                       \
                                     font-size: 14px;                                   \
                                     }");
    // Consolas è installato di default su tutti i sistemi Windows, ma non linux.
    // Il matching engine di Qt tenterà di trovare Consolas o un monospace di rimpiazzo
    // font-family: Consolas, monospace;
    QFont font("Consolas");
    font.setStyleHint(QFont::Monospace);
    m_customCodeEdit->setFont(font);
    m_customCodeEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //ui->plainTextEdit->setVerticalScrollBar(new CustomScrollBar(ui->plainTextEdit));
    //QScrollBar *vertScrollBar = ui->plainTextEdit->verticalScrollBar();

    /*vertScrollBar->setStyleSheet("\
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { \
                             background: red; \
                             }\
                         ");*/
    /*ui->plainTextEdit->verticalScrollBar()->setStyleSheet(
        QString("\
                QScrollBar:vertical {\
                    background: rgba(34,34,34);\
                    width:13px;\
                }\
                QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\
                    background: none;\
                }\
                QScrollBar:left-arrow:vertical, QScrollBar::right-arrow:vertical {\
                    height: 1px;\
                    width: 1px;\
                }\
                QScrollBar::handle:vertical {\
                    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\
                    stop:0 rgb(55,55,55), stop: 0.5 rgb(71,71,71), stop:1 rgb(47,48,41));\
                    border-radius: 5px;\
                    width: 4px;\
                }\
                "));*/
    m_verticalScrollBar = std::make_unique<ScrollBar>(m_customCodeEdit.get());
    m_customCodeEdit->setVerticalScrollBar(m_verticalScrollBar.get());
    m_customCodeEdit->verticalScrollBar()->setStyleSheet(QString("\
                                                                  QScrollBar:vertical {\
                                                                    width:15px;\
                                                                  }"));

    // Crea la TabsBar
    m_tabsBar = std::make_unique<TabsBar>(this);
    //m_tabsBar->addTab("cazzo tab di prova");
    //m_tabsBar->addTab("seconda tab");
    ui->tabsBarArea->addWidget(m_tabsBar.get());



    //vertScrollBar->setAttribute( Qt::WA_TranslucentBackground );
}

void VMainWindow::paintEvent(QPaintEvent *)
{

}

VMainWindow::~VMainWindow() {
    delete ui;
}
