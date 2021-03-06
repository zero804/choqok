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

#include "tighturl.h"

#include <QEventLoop>
#include <QUrl>

#include <KIO/StoredTransferJob>
#include <KLocalizedString>
#include <KPluginFactory>

#include "notifymanager.h"

K_PLUGIN_FACTORY_WITH_JSON(TightUrlFactory, "choqok_tighturl.json",
                           registerPlugin < TightUrl > ();)

TightUrl::TightUrl(QObject *parent, const QVariantList &)
    : Choqok::Shortener(QLatin1String("choqok_tighturl"), parent)
{
}

QString TightUrl::shorten(const QString &url)
{
    QUrl reqUrl(QLatin1String("http://2tu.us/"));
    QUrlQuery reqQuery;
    reqQuery.addQueryItem(QLatin1String("save"), QLatin1String("y"));
    reqQuery.addQueryItem(QLatin1String("url"), QUrl(url).url());
    reqUrl.setQuery(reqQuery);

    QEventLoop loop;
    KIO::StoredTransferJob *job = KIO::storedGet(reqUrl, KIO::Reload, KIO::HideProgressInfo);
    connect(job, &KIO::StoredTransferJob::result, &loop, &QEventLoop::quit);
    job->start();
    loop.exec();

    if (job->error() == KJob::NoError) {
        QString output(QLatin1String(job->data()));
        QRegExp rx(QLatin1String("<code>(.+)</code>"));
        rx.setMinimal(true);
        rx.indexIn(output);
        output = rx.cap(1);
        rx.setPattern(QLatin1String("href=[\'\"](.+)[\'\"]"));
        rx.indexIn(output);
        output = rx.cap(1);
        if (!output.isEmpty()) {
            return output;
        }
    } else {
        Choqok::NotifyManager::error(i18n("Cannot create a short URL.\n%1",
                                          job->errorString()), i18n("TightUrl Error"));
    }
    return url;
}

TightUrl::~TightUrl()
{
}

#include "tighturl.moc"
