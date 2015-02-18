/*
This file is part of Choqok, the KDE micro-blogging client

Copyright (C) 2010-2011 Marcello Ceschia <marcelloceschia@users.sourceforge.net>
Copyright (C) 2010-2012 Mehrdad Momeny <mehrdad.momeny@gmail.com>

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

#include "yourls.h"

#include <QUrl>

#include <KAboutData>
#include <KIO/Job>
#include <KIO/NetAccess>
#include <KLocalizedString>
#include <KPluginFactory>

#include "notifymanager.h"
#include "passwordmanager.h"

#include "yourlssettings.h"

K_PLUGIN_FACTORY_WITH_JSON( YourlsFactory, "choqok_yourls.json",
                            registerPlugin < Yourls > (); )

Yourls::Yourls( QObject *parent, const QVariantList & )
    : Choqok::Shortener( "choqok_yourls", parent )
{
    connect( YourlsSettings::self(), SIGNAL(configChanged()),
             SLOT(reloadConfigs()) );
}

Yourls::~Yourls()
{}

QString Yourls::shorten( const QString &url )
{
    QByteArray data;                                                    /* output field */

    QUrl reqUrl( YourlsSettings::yourlsHost() );
    reqUrl.addQueryItem( "action", "shorturl" );                        /* set action to shorturl */
    reqUrl.addQueryItem( "format", "xml" );                             /* get result as xml */
    reqUrl.addQueryItem( "url", QUrl( url ).url() );                    /* url to be shorted */
    password = Choqok::PasswordManager::self()->readPassword(
                                                QString("yourls_%1").arg(YourlsSettings::username())).toUtf8();
    if( !YourlsSettings::username().isEmpty() ){
        reqUrl.addQueryItem( "username", YourlsSettings::username() );
        reqUrl.addQueryItem( "password", password );
    }

    KIO::Job *job = KIO::get( reqUrl, KIO::Reload, KIO::HideProgressInfo );

    if ( KIO::NetAccess::synchronousRun( job, 0, &data ) ) {
        QString output(data);

        QRegExp rx( QString( "<shorturl>(.+)</shorturl>" ) );
        rx.setMinimal(true);
        rx.indexIn(output);
        output = rx.cap(1);


        if(!output.isEmpty()) {
            return output;
        }else{
            output = data;
            QRegExp rx( QString( "<message>(.+)</message>" ) );
            rx.setMinimal(true);
            rx.indexIn(output);
            output = rx.cap(1);

            Choqok::NotifyManager::error( output, i18n("Yourls Error") );
        }
    } else {
            Choqok::NotifyManager::error( i18n("Cannot create a short URL.\n%1",
                                               job->errorString()) );
    }
    return url;
}

void Yourls::reloadConfigs()
{
    password = Choqok::PasswordManager::self()->readPassword(
                                                QString("yourls_%1").arg(YourlsSettings::username())).toUtf8();
}

#include "yourls.moc"