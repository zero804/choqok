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

#include "shortenmanager.h"

#include <QApplication>

#include <KSharedConfig>

#include "choqokbehaviorsettings.h"
#include "libchoqokdebug.h"
#include "pluginmanager.h"
#include "notifymanager.h"

namespace Choqok
{

class ShortenManagerPrivate
{
public:
    Shortener *backend;
    ShortenManager instance;
    QRegExp findUrlRegExp;
    QRegExp removeUrlRegExp;

    ShortenManagerPrivate()
        : backend(nullptr)
    {
        findUrlRegExp.setPattern(QLatin1String("(ftps?|https?)://"));
        removeUrlRegExp.setPattern(QLatin1String("^(https?)://"));
        reloadConfig();
    }
    void reloadConfig()
    {
        const QString pluginId = Choqok::BehaviorSettings::shortenerPlugin();
        if (backend) {
            if (backend->pluginName() == pluginId) {
                return;//Already loaded
            } else {
                qCDebug(CHOQOK) << backend->pluginName();
                PluginManager::self()->unloadPlugin(backend->pluginName());
                backend = nullptr;
            }
        }
        if (pluginId.isEmpty()) {
            return;
        }
        Plugin *plugin = PluginManager::self()->loadPlugin(pluginId);
        backend = qobject_cast<Shortener *>(plugin);
        if (!backend) {
            qCDebug(CHOQOK) << "Could not load a Shortener plugin. Shortening Disabled";
        }
    }
};

Q_GLOBAL_STATIC(ShortenManagerPrivate, _smp)

QString shorten(const QString &url)
{
    return _smp->backend->shorten(url);
}

ShortenManager::ShortenManager(QObject *parent)
    : QObject(parent)
{
}

ShortenManager::~ShortenManager()
{}

ShortenManager *ShortenManager::self()
{
    return &_smp->instance;
}

QString ShortenManager::shortenUrl(const QString &url)
{
    if (_smp->backend) {
        qCDebug(CHOQOK) << "Shortening:" << url;
        NotifyManager::shortening(url);
        QString shortUrl = shorten(url);
        if (BehaviorSettings::removeHttp() && url != shortUrl) {
            shortUrl.remove(_smp->removeUrlRegExp);
        }
        return shortUrl;
    } else {
        qCDebug(CHOQOK) << "There isn't any Shortener plugin.";
        return url;
    }
}

void ShortenManager::reloadConfig()
{
    _smp->reloadConfig();
}

QString ShortenManager::parseText(const QString &text)
{
    qCDebug(CHOQOK);
    QString t;
    int i = 0, j = 0;
    while ((j = text.indexOf(_smp->findUrlRegExp, i)) != -1) {
        t += text.mid(i, j - i);
        int k = text.indexOf(QLatin1Char(' '), j);
        if (k == -1) {
            k = text.length();
        }
        QString baseUrl = text.mid(j, k - j);
        if (baseUrl.count() > 30) {
            QString tmp = Choqok::ShortenManager::self()->shortenUrl(baseUrl);
            if (BehaviorSettings::removeHttp() && tmp != baseUrl) {
                tmp.remove(_smp->removeUrlRegExp);
            }
            t += tmp;
        } else {
            t += baseUrl;
        }
        i = k;
    }
    t += text.mid(i);
    return t;
}

void ShortenManager::emitNewUnshortenedUrl(Choqok::UI::PostWidget *widget, const QUrl &fromUrl, const QUrl &toUrl)
{
    Q_EMIT newUnshortenedUrl(widget, fromUrl, toUrl);
}

}

