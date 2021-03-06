/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "flamegraph_test.h"
#include <QtTest>
#include <QQuickItem>

namespace QmlProfiler {
namespace Internal {

void FlameGraphTest::initTestCase()
{
    flameGraph.setDelegate(&delegate);
    flameGraph.setModel(&model);
    flameGraph.setSizeRole(sizeRole);
    flameGraph.setWidth(100);
    flameGraph.setHeight(100);
    flameGraph.setSizeThreshold(0.01);

    QCOMPARE(flameGraph.delegate(), &delegate);
    QCOMPARE(flameGraph.model(), &model);
    QCOMPARE(flameGraph.sizeRole(), Qt::UserRole + 1);
    QCOMPARE(flameGraph.sizeThreshold(), 0.01);
}

void FlameGraphTest::testRebuild()
{
    flameGraph.setModel(nullptr);
    qreal sum = 0;
    for (int i = 1; i < 10; ++i) {
        QStandardItem *item = new QStandardItem;
        item->setData(i, sizeRole);
        item->setData(100 / i, dataRole);

        for (int j = 1; j < i; ++j) {
            QStandardItem *item2 = new QStandardItem;
            item2->setData(1, sizeRole);
            for (int k = 0; k < 10; ++k) {
                QStandardItem *skipped = new QStandardItem;
                skipped->setData(0.001, sizeRole);
                item2->appendRow(skipped);
            }
            item->appendRow(item2);
        }

        model.appendRow(item);
        sum += i;
    }
    model.invisibleRootItem()->setData(sum, sizeRole);
    flameGraph.setModel(nullptr);
    flameGraph.setModel(&model);
    QCOMPARE(flameGraph.depth(), 3);
    qreal i = 0;
    qreal position = 0;
    foreach (QQuickItem *child, flameGraph.childItems()) {
        FlameGraphAttached *attached = FlameGraph::qmlAttachedProperties(child);
        QCOMPARE(attached->relativeSize(), (++i) / sum);
        QCOMPARE(attached->relativePosition(), position / sum);
        QCOMPARE(attached->data(dataRole).toInt(), 100 / static_cast<int>(i));
        QVERIFY(attached->isDataValid());

        qreal j = 0;
        foreach (QQuickItem *grandchild, child->childItems()) {
            FlameGraphAttached *attached2 = FlameGraph::qmlAttachedProperties(grandchild);
            QCOMPARE(attached2->relativeSize(), 1.0 / i);
            QCOMPARE(attached2->relativePosition(), (j++) / i);
            QCOMPARE(grandchild->childItems().count(), 1);
            FlameGraphAttached *skipped =
                    FlameGraph::qmlAttachedProperties(grandchild->childItems()[0]);
            QCOMPARE(skipped->relativePosition(), 0.0);
            QCOMPARE(skipped->relativeSize(), 0.001 * 10);
        }

        position += i;
    }
    QCOMPARE(i, 9.0);
}

void FlameGraphTest::cleanupTestCase()
{

}

QObject *DelegateComponent::create(QQmlContext *context)
{
    QObject *ret = beginCreate(context);
    completeCreate();
    return ret;
}

QObject *DelegateComponent::beginCreate(QQmlContext *)
{
    return new DelegateObject;
}

void DelegateComponent::completeCreate()
{
}

} // namespace Internal
} // namespace QmlProfiler
