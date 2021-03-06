/** \file HelpDialog.cpp
\brief Define the help dialog
\author alpha_one_x86
\licence GPL3, see the file COPYING */

#include "HelpDialog.h"

#include <QTreeWidgetItem>
#include <QApplication>

/// \brief Construct the object
HelpDialog::HelpDialog() :
    ui(new Ui::HelpDialog)
{
    ULTRACOPIER_DEBUGCONSOLE(Ultracopier::DebugLevel_Notice,QStringLiteral("start"));
    ui->setupUi(this);
    reloadTextValue();
    #ifdef ULTRACOPIER_DEBUG
    ui->debugView->setModel(DebugModel::debugModel);
    connect(ui->pushButtonSaveBugReport,&QPushButton::clicked,DebugEngine::debugEngine,&DebugEngine::saveBugReport);
    #else // ULTRACOPIER_DEBUG
    ui->lineEditInsertDebug->hide();
    ui->debugView->hide();
    ui->pushButtonSaveBugReport->hide();
    ui->pushButtonCrash->hide();
    this->setMaximumSize(QSize(500,128));
    /*timeToSetText.setInterval(250);
    timeToSetText.setSingleShot(true);
    connect(&timeToSetText,QTimer::timeout,this,&DebugEngine::showDebugText);*/
    ui->pushButtonClose->hide();
    #endif // ULTRACOPIER_DEBUG
    //connect the about Qt
    connect(ui->pushButtonAboutQt,&QPushButton::toggled,&QApplication::aboutQt);
    #ifdef ULTRACOPIER_MODE_SUPERCOPIER
    setWindowTitle(tr("About Supercopier"));
    #else
    setWindowTitle(tr("About Ultracopier"));
    #endif
}

/// \brief Destruct the object
HelpDialog::~HelpDialog()
{
    delete ui;
}

/// \brief To re-translate the ui
void HelpDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ULTRACOPIER_DEBUGCONSOLE(Ultracopier::DebugLevel_Notice,QStringLiteral("start"));
        ui->retranslateUi(this);
        reloadTextValue();
        break;
    default:
        break;
    }
}

/// \brief To reload the text value
void HelpDialog::reloadTextValue()
{
    ULTRACOPIER_DEBUGCONSOLE(Ultracopier::DebugLevel_Notice,QStringLiteral("start"));
    QString text=ui->label_ultracopier->text();
    #ifdef ULTRACOPIER_VERSION_ULTIMATE
    text=text.replace(QStringLiteral("%1"),QStringLiteral("Ultimate %1").arg(ULTRACOPIER_VERSION));
    #else
    text=text.replace(QStringLiteral("%1"),ULTRACOPIER_VERSION);
    #endif
    #ifdef ULTRACOPIER_MODE_SUPERCOPIER
        text=text.replace(QStringLiteral("Ultracopier"),QStringLiteral("Supercopier"),Qt::CaseInsensitive);
    #endif
    ui->label_ultracopier->setText(text);

    text=ui->label_description->text();
    #ifdef ULTRACOPIER_VERSION_PORTABLE
        #ifdef ULTRACOPIER_VERSION_PORTABLEAPPS
            text=text.replace(QStringLiteral("%1"),tr("For http://portableapps.com/"));
        #else
            #ifdef ULTRACOPIER_PLUGIN_ALL_IN_ONE
                text=text.replace(QStringLiteral("%1"),tr("Portable and all in one version"));
            #else
                text=text.replace(QStringLiteral("%1"),tr("Portable version"));
            #endif
        #endif
    #else
        #ifdef ULTRACOPIER_PLUGIN_ALL_IN_ONE
            text=text.replace(QStringLiteral("%1"),tr("All in one version"));
        #else
            text=text.replace(QStringLiteral("%1"),tr("Normal version"));
        #endif
    #endif
    ui->label_description->setText(text);

    text=ui->label_site->text();
    //: This site need be the official site of ultracopier, into the right languages, english if not exists
    text=text.replace(QStringLiteral("%1"),getWebSite());
    ui->label_site->setText(text);

    text=ui->label_platform->text();
    text=text.replace(QStringLiteral("%1"),ULTRACOPIER_PLATFORM_NAME);
    ui->label_platform->setText(text);
}

QString HelpDialog::getWebSite()
{
    #ifdef ULTRACOPIER_MODE_SUPERCOPIER
        return tr("http://ultracopier.first-world.info/")+QStringLiteral("supercopier.html");
    #else
        return tr("http://ultracopier.first-world.info/");
    #endif
}


QString HelpDialog::getUpdateUrl()
{
    #if defined(ULTRACOPIER_VERSION_ULTIMATE)
    return tr("http://ultracopier.first-world.info/shop.html");
    #else
        #ifdef ULTRACOPIER_MODE_SUPERCOPIER
        return tr("http://ultracopier.first-world.info/")+QStringLiteral("supercopier.html");
        #else
        return tr("http://ultracopier.first-world.info/download.html");
        #endif
    #endif
}

#ifdef ULTRACOPIER_DEBUG
void HelpDialog::on_lineEditInsertDebug_returnPressed()
{
    DebugEngine::addDebugNote(ui->lineEditInsertDebug->text());
    ui->lineEditInsertDebug->clear();
    ui->debugView->scrollToBottom();
}
#endif // ULTRACOPIER_DEBUG

void HelpDialog::on_pushButtonAboutQt_clicked()
{
    QApplication::aboutQt();
}

void HelpDialog::on_pushButtonCrash_clicked()
{
    int a=0;
    int *b=NULL;
    *b=3/a;
}
