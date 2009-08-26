/*
This file is part of Choqok, the KDE micro-blogging client

Copyright (C) 2008-2009 Mehrdad Momeny <mehrdad.momeny@gmail.com>

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

#ifndef _CHOQOK_BEHAVIOR_H
#define _CHOQOK_BEHAVIOR_H

#define KDE3_SUPPORT
#include <kcmodule.h>
#undef KDE3_SUPPORT

class BehaviorConfig : public KCModule
{
Q_OBJECT

public:
    BehaviorConfig(QWidget *parent, const QVariantList &args) ;
    ~BehaviorConfig();

    virtual void save();
    virtual void load();

private:
    class Private;
    Private *d;
};
#endif
// vim: set noet ts=4 sts=4 sw=4: