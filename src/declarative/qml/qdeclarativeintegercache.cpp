/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativeintegercache_p.h"

#include "qdeclarativeengine_p.h"
#include "qdeclarativemetatype_p.h"

QT_BEGIN_NAMESPACE

QDeclarativeIntegerCache::QDeclarativeIntegerCache(QDeclarativeEngine *e)
: QDeclarativeCleanup(e), engine(e)
{
}

QDeclarativeIntegerCache::~QDeclarativeIntegerCache()
{
    clear();
}

void QDeclarativeIntegerCache::clear()
{
    qDeleteAll(stringCache);
    stringCache.clear();
    identifierCache.clear();
    engine = 0;
}

QString QDeclarativeIntegerCache::findId(int value) const
{
    for (StringCache::ConstIterator iter = stringCache.begin();
            iter != stringCache.end(); ++iter) {
        if (iter.value() && iter.value()->value == value)
            return iter.key();
    }
    return QString();
}

void QDeclarativeIntegerCache::add(const QString &id, int value)
{
    Q_ASSERT(!stringCache.contains(id));

    QDeclarativeEnginePrivate *enginePriv = QDeclarativeEnginePrivate::get(engine);

    // ### use contextClass
    Data *d = new Data(enginePriv->objectClass->createPersistentIdentifier(id), value);

    stringCache.insert(id, d);
    identifierCache.insert(d->identifier, d);
}

int QDeclarativeIntegerCache::value(const QString &id)
{
    Data *d = stringCache.value(id);
    return d?d->value:-1;
}

QT_END_NAMESPACE
