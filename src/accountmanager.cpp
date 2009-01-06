/*
    This file is part of choqoK, the KDE Twitter client

    Copyright (C) 2008 Mehrdad Momeny <mehrdad.momeny@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/
#include "accountmanager.h"
#include <kdebug.h>
#include <KConfig>
#include <KConfigGroup>

AccountManager::AccountManager(QObject* parent):
        QObject(parent)
{
    kDebug();
    conf = new KConfig( );
    loadAccounts();
}


AccountManager::~AccountManager()
{
    mSelf = 0L;
    conf->sync();
    delete conf;
}

AccountManager * AccountManager::mSelf = 0L;

AccountManager * AccountManager::self()
{
    if( !mSelf )
        mSelf = new AccountManager;
    return mSelf;
}

const QList< Account > & AccountManager::accounts() const
{
    return mAccounts;
}

Account & AccountManager::findAccount( QString &alias )
{
    kDebug()<<"Finding: "<<alias;
    int count = mAccounts.count();
    for ( int i=0; i<count; ++i )
    {
        if ( mAccounts[i].alias == alias ){
            mAccounts[i].isError = false;
            return mAccounts[i];
        }
    }
    Account a;
    a.isError = true;
    return a;
}

bool AccountManager::removeAccount(const QString &alias)
{
    kDebug()<<"Removing "<<alias;
    int count = mAccounts.count();
    for(int i=0; i<count; ++i){
        if(mAccounts[i].alias == alias){
            conf->deleteGroup( QString::fromLatin1("Account %1").arg(alias) );
            conf->sync();
            mAccounts.removeAt(i);
            emit accountRemoved(alias);
            return true;
        }
    }
    return false;
}

Account & AccountManager::addAccount(Account & account)
{
    kDebug()<<"Adding: "<<account.alias;
//     if( mAccounts.contains( account ) )
//         return account;
    
    if( account.alias.isEmpty() )
    {
        account.isError = true;
        return account;
    }
    
    // If this account already exists, do nothing
    QListIterator<Account> it( mAccounts );
    while ( it.hasNext() )
    {
        Account curracc = it.next();
        if ( account.alias == curracc.alias )
        {
            account.isError = true;
            return account;
        }
    }
    mAccounts.append( account );
    KConfigGroup acConf ( conf, QString::fromLatin1("Account %1").arg(account.alias) );
    acConf.writeEntry ( "alias", account.alias );
    acConf.writeEntry ( "username", account.username );
    acConf.writeEntry ( "password", account.password );
    acConf.writeEntry ( "direction", ( account.direction == Qt::RightToLeft ) ? "rtl" : "ltr" );
    acConf.writeEntry ( "service", account.serviceName );
    acConf.writeEntry ( "api_path", account.apiPath );
    conf->sync();
    emit accountAdded(account);
    account.isError = false;
    return account;
}

Account & AccountManager::modifyAccount(Account & account, const QString & previousAlias)
{
    kDebug()<<"Modifing: "<<previousAlias;
    
    if(removeAccount(previousAlias))
        return addAccount(account);
    
    account.isError = true;
    return account;
}

void AccountManager::loadAccounts()
{
    kDebug();
    QStringList list = conf->groupList();
//     kDebug()<<"Accounts : "<<list;
    int count = list.count();
    for(int i=0; i<count; ++i){
        if(list[i].contains("Account")){
            Account a;
            KConfigGroup accountGrp(conf, list[i]);
            a.username = accountGrp.readEntry("username", QString());
            a.alias = accountGrp.readEntry("alias", a.username);
            a.password = accountGrp.readEntry("password", QString());
            a.serviceName = accountGrp.readEntry("service", QString());
            a.apiPath = accountGrp.readEntry("api_path", QString());
            a.direction = (accountGrp.readEntry("direction", "ltr") == "rtl") ? Qt::RightToLeft : Qt::LeftToRight;
            a.isError = false;
            mAccounts.append(a);
        }
    }
    kDebug()<<mAccounts.count()<<" accounts loaded.";
}

#include "accountmanager.moc"
