/*
    This file is part of choqoK, the KDE micro-blogging client

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

#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>
#include <QKeyEvent>

#include "ui_searchwidget_base.h"
#include "account.h"
#include "search.h"

class QLabel;
class StatusTextEdit;
class StatusWidget;

/**
The Search Widget

For any microblogging service compatible with the Twitter Search API

 @author Stephen Henderson <hendersonsk@gmail.com>
*/
class SearchWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWindow(const Account &account, QWidget* parent = 0 );
    ~SearchWindow();

    void clearSearchResults();
    void updateStatusList();
    void setAccount(const Account &account);
    void init(int type = 0, const QString & query = QString());

protected:
    virtual void keyPressEvent( QKeyEvent *e );

public slots:
    void updateSearchResults();
    void autoUpdateSearchResults();

protected slots:
    void search();
    void searchResultsReceived( QList<Status> &stautsList );
    void error( QString message );

signals:
    void forwardReply( const QString &username, uint statusId, bool dMsg );
    void forwardFavorited( uint statusId, bool isFavorite );
//     void updateTimeLines();

private:
    void addNewStatusesToUi( QList<Status> &statusList );
    void resetSearchArea(int type = 0, const QString & query = QString());
    void markStatusesAsRead();

private slots:
    void updateSearchArea(int type = 0, const QString & query = QString());

protected:
    QList<StatusWidget*> listResults;

private:
    Account mAccount;
    Search* mSearch;
    Ui::searchwidget_base ui;

    QString lastSearchQuery;
    int lastSearchType;
};

#endif
