/*
This file is part of Choqok, the KDE micro-blogging client

Copyright (C) 2008-2012 Mehrdad Momeny <mehrdad.momeny@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy
defined in Section 14 of version 3 of the license.


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see http://www.gnu.org/licenses/

*/

#ifndef BEHAVIORCONFIG_SHORTEN_H
#define BEHAVIORCONFIG_SHORTEN_H

#include "ui_behaviorconfig_shorten_base.h"
#include <QtGui/QWidget>
#include <kplugininfo.h>
#include <shortener.h>

class KCModuleProxy;
class BehaviorConfig_Shorten: public QWidget, public Ui::BehaviorConfig_ShortenBase
{
    Q_OBJECT
public:
    BehaviorConfig_Shorten( QWidget *parent = 0 );
    ~BehaviorConfig_Shorten();
    void load();
    void save();

Q_SIGNALS:
    void changed(bool isChanged);

private Q_SLOTS:
    void currentPluginChanged( int index );

protected Q_SLOTS:
    void slotAboutClicked();
    void slotConfigureClicked();

private:
    QMap<QString, KPluginInfo> availablePlugins;
    Choqok::Shortener *currentShortener;
    QString prevShortener;
    QList<KCModuleProxy*> moduleProxyList;
};

#endif
