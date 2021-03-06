/** \file PluginInformation.cpp
\brief Define the plugin information
\author alpha_one_x86
\licence GPL3, see the file COPYING */

#include "PluginInformation.h"
#include "ui_PluginInformation.h"

PluginInformation::PluginInformation() :
    ui(new Ui::PluginInformation)
{
    ui->setupUi(this);
    pluginIsLoaded=false;
}

PluginInformation::~PluginInformation()
{
    delete ui;
}

void PluginInformation::setPlugin(const PluginsAvailable &plugin)
{
    this->plugin=plugin;
    pluginIsLoaded=true;
    retranslateInformation();
}

void PluginInformation::setLanguage(const QString &language)
{
    this->language=language;
}

QString PluginInformation::categoryToTranslation(const PluginType &category) const
{
    switch(category)
    {
        case PluginType_CopyEngine:
            return tr("Copy engine");
        break;
        case PluginType_Languages:
            return tr("Languages");
        break;
        case PluginType_Listener:
            return tr("Listener");
        break;
        case PluginType_PluginLoader:
            return tr("Plugin loader");
        break;
        case PluginType_SessionLoader:
            return tr("Session loader");
        break;
        case PluginType_Themes:
            return tr("Themes");
        break;
        default:
            ULTRACOPIER_DEBUGCONSOLE(Ultracopier::DebugLevel_Warning,"cat translation not found");
            return tr("Unknown");
        break;
    }
}

void PluginInformation::retranslateInformation()
{
    if(!pluginIsLoaded)
        return;
    ui->retranslateUi(this);
    this->setWindowTitle(tr("Information about %1").arg(plugin.name));
    ui->name->setText(plugin.name);
    ui->title->setText(getTranslatedText(plugin,QStringLiteral("title"),language));
    ui->category->setText(categoryToTranslation(plugin.category));
    ui->author->setText(getInformationText(plugin,QStringLiteral("author")));
    QString website=getTranslatedText(plugin,QStringLiteral("website"),language);
    ui->website->setText(QStringLiteral("<a href=\"")+website+QStringLiteral("\" title=\"")+website+QStringLiteral("\">")+website+QStringLiteral("</a>"));
    bool ok;
    int timeStamps=getInformationText(plugin,QStringLiteral("pubDate")).toInt(&ok);
    QDateTime date;
    date.setTime_t(timeStamps);
    ui->date->setDateTime(date);
    if(!ok || timeStamps<=0)
        ui->date->setEnabled(false);
    ui->description->setPlainText(getTranslatedText(plugin,QStringLiteral("description"),language));
    ui->version->setText(getInformationText(plugin,QStringLiteral("version")));
}

/// \brief get informations text
QString PluginInformation::getInformationText(const PluginsAvailable &plugin,const QString &informationName)
{
    int index=0;
    while(index<plugin.informations.size())
    {
        if(plugin.informations.at(index).size()==2 && plugin.informations.at(index).first()==informationName)
            return plugin.informations.at(index).last();
        index++;
    }
    ULTRACOPIER_DEBUGCONSOLE(Ultracopier::DebugLevel_Warning,"information not found: "+informationName+", for: "+plugin.name+", cat: "+categoryToTranslation(plugin.category));
    return "";
}

/// \brief get translated text
QString PluginInformation::getTranslatedText(const PluginsAvailable &plugin,const QString &informationName,const QString &mainShortName)
{
    int index=0;
    QString TextFound;
    while(index<plugin.informations.size())
    {
        if(plugin.informations.at(index).size()==3)
        {
            if(plugin.informations.at(index).first()==informationName)
            {
                if(plugin.informations.at(index).at(1)==mainShortName)
                    return plugin.informations.at(index).last();
                else if(plugin.informations.at(index).at(1)==QStringLiteral("en"))
                    TextFound=plugin.informations.at(index).last();

            }
        }
        index++;
    }
    #ifdef ULTRACOPIER_DEBUG
    if(TextFound.isEmpty() || TextFound.isEmpty())
        ULTRACOPIER_DEBUGCONSOLE(Ultracopier::DebugLevel_Warning,"text is not found or empty for: "+informationName+", with the language: "+mainShortName+", for the plugin: "+plugin.path);
    #endif // ULTRACOPIER_DEBUG
    return TextFound;
}
