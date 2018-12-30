#include "Http_DownLoader.h"
#include "Http_DownLoaderPlugin.h"

#include <QtCore/QtPlugin>

Http_DownLoaderPlugin::Http_DownLoaderPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void Http_DownLoaderPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool Http_DownLoaderPlugin::isInitialized() const
{
	return initialized;
}

QWidget *Http_DownLoaderPlugin::createWidget(QWidget *parent)
{
	return new Http_DownLoader(parent);
}

QString Http_DownLoaderPlugin::name() const
{
	return "Http_DownLoader";
}

QString Http_DownLoaderPlugin::group() const
{
	return "My Plugins";
}

QIcon Http_DownLoaderPlugin::icon() const
{
	return QIcon();
}

QString Http_DownLoaderPlugin::toolTip() const
{
	return QString();
}

QString Http_DownLoaderPlugin::whatsThis() const
{
	return QString();
}

bool Http_DownLoaderPlugin::isContainer() const
{
	return false;
}

QString Http_DownLoaderPlugin::domXml() const
{
	return "<widget class=\"Http_DownLoader\" name=\"http_DownLoader\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>100</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString Http_DownLoaderPlugin::includeFile() const
{
	return "Http_DownLoader.h";
}
