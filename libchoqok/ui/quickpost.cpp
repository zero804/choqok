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

#include "quickpost.h"
#include "choqoktextedit.h"
#include "accountmanager.h"
#include "choqokbehaviorsettings.h"
#include <KDebug>
#include <microblog.h>
#include <QCheckBox>
#include <klocalizedstring.h>
#include <kcombobox.h>
#include <QHBoxLayout>
#include <KPluginInfo>

using namespace Choqok::UI;
using namespace Choqok;

class QuickPost::Private
{
public:
    Private()
    : submittedPost(0)
    {}
    QCheckBox *all;
    KComboBox *comboAccounts;
    TextEdit *txtPost;

    QHash< QString, Account* > accountsList;
    Post *submittedPost;
//     QString replyToId;
};

QuickPost::QuickPost( QWidget* parent )
    : KDialog( parent ), d(new Private)
{
    kDebug();
    setupUi();
    loadAccounts();
    connect( d->comboAccounts, SIGNAL(currentIndexChanged(int)),
             this, SLOT(slotCurrentAccountChanged(int)) );
    connect( d->txtPost, SIGNAL( returnPressed( QString ) ),
             this, SLOT( submitPost( QString ) ) );
    connect( d->all, SIGNAL( toggled( bool ) ),
             this, SLOT( checkAll( bool ) ) );
    connect( AccountManager::self(), SIGNAL( accountAdded(Choqok::Account*)),
             this, SLOT( addAccount( Choqok::Account*)) );
    connect( AccountManager::self(), SIGNAL( accountRemoved( const QString& ) ),
             this, SLOT( removeAccount( const QString& ) ) );

    d->all->setChecked( Choqok::BehaviorSettings::all() );
    slotCurrentAccountChanged(d->comboAccounts->currentIndex());
}

void QuickPost::setupUi()
{
    QWidget *wdg = new QWidget( this );
    this->setMainWidget( wdg );

    this->resize( Choqok::BehaviorSettings::quickPostDialogSize() );
    d->all = new QCheckBox( i18n("All"), this);
    d->comboAccounts = new KComboBox(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(d->all);
    hLayout->addWidget(d->comboAccounts);
    mainLayout->addLayout(hLayout);
    d->txtPost = new TextEdit( 0, this );
    d->txtPost->setTabChangesFocus( true );
    mainLayout->addWidget( d->txtPost );
    if(wdg->layout())
        wdg->layout()->deleteLater();
    wdg->setLayout(mainLayout);
    d->txtPost->setFocus( Qt::OtherFocusReason );
    this->setCaption( i18n( "Quick Post" ) );
}

QuickPost::~QuickPost()
{
    BehaviorSettings::setAll( d->all->isChecked() );
    BehaviorSettings::setQuickPostDialogSize( this->size() );
    BehaviorSettings::self()->writeConfig();
    kDebug();
}

void QuickPost::show()
{
    d->txtPost->setFocus( Qt::OtherFocusReason );
    KDialog::show();
}

void QuickPost::slotSubmitPost( Account* theAccount, Post* post )
{
    if (post == d->submittedPost) {
        d->txtPost->setEnabled(true);
        d->txtPost->clear();
        emit newPostSubmitted(Success);
        //TODO Notify
        delete d->submittedPost;
        d->submittedPost = 0L;
//         d->replyToId.clear();
    }
}

void QuickPost::postError(Account* theAccount, MicroBlog::ErrorType error,
                          const QString& errorMessage, Choqok::Post* post)
{
    if (post == d->submittedPost) {
        d->txtPost->setEnabled(true);
        emit newPostSubmitted(Fail);
        //TODO Notify
        delete d->submittedPost;
        d->submittedPost = 0L;
//         d->replyToId.clear();
    }
}

void QuickPost::submitPost( const QString & newPost )
{
    kDebug();
    this->hide();
    if ( d->all->isChecked() ) {
            d->submittedPost = new Post;
            d->submittedPost->content = newPost;
            d->submittedPost->isPrivate = false;
        foreach ( Account* acc, d->accountsList.values() ) {
            acc->microblog()->createPost( acc, d->submittedPost );
        }
    } else {
        d->submittedPost = new Post;
        d->submittedPost->content = newPost;
        d->submittedPost->isPrivate = false;
        d->accountsList.value(d->comboAccounts->currentText())->microblog()->createPost(d->accountsList.value(d->comboAccounts->currentText()),
                                                                             d->submittedPost );
    }
}

void QuickPost::slotButtonClicked(int button)
{
    kDebug();
    if(button == KDialog::Ok) {
        const QString txt = d->txtPost->toPlainText();
        submitPost( txt );
    } else
        KDialog::slotButtonClicked(button);
}

void QuickPost::loadAccounts()
{
    kDebug();
    QList<Account*> ac = AccountManager::self()->accounts();
    QListIterator<Account*> it( ac );
    while ( it.hasNext() ) {
        Account *current = it.next();
        d->accountsList.insert( current->alias(), current );
        d->comboAccounts->addItem( KIcon(current->microblog()->pluginInfo().icon()), current->alias() );
        connect(current->microblog(), SIGNAL(postCreated(Account*,Post*)), SLOT(slotSubmitPost(Account*,Post*)) );
        connect(current->microblog(),
                SIGNAL(errorPost(Account*,MicroBlog::ErrorType,QString,Post*)),
                 SLOT(postError(Account*,MicroBlog::ErrorType,QString,Post*)) );
    }
}

void QuickPost::addAccount( Choqok::Account* account )
{
    kDebug();
    d->accountsList.insert( account->alias(), account );
    d->comboAccounts->addItem( KIcon(account->microblog()->pluginInfo().icon()), account->alias() );
}

void QuickPost::removeAccount( const QString & alias )
{
    kDebug();
    d->accountsList.remove( alias );
    d->comboAccounts->removeItem( d->comboAccounts->findText(alias) );
}

void QuickPost::checkAll( bool isAll )
{
    d->comboAccounts->setEnabled( !isAll );
}

void QuickPost::setText( const QString& text )
{
    d->txtPost->setText(text);
//     if(account)
//         d->comboAccounts->setCurrentItem(account->alias());
//     if(!replyToId.isEmpty())
//         d->replyToId = replyToId;
}

void QuickPost::slotCurrentAccountChanged(int index)
{
    Q_UNUSED(index)
    if( !d->accountsList.isEmpty() )
        d->txtPost->setCharLimit( d->accountsList.value(d->comboAccounts->currentText())->microblog()->postCharLimit() );
}

#include "quickpost.moc"