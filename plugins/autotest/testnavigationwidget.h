/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Creator Enterprise Auto Test Add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#ifndef TESTNAVIGATIONWIDGETTREEVIEW_H
#define TESTNAVIGATIONWIDGETTREEVIEW_H

#include <coreplugin/inavigationwidgetfactory.h>

#include <utils/navigationtreeview.h>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QToolButton;
QT_END_NAMESPACE

namespace Core {
class IContext;
}

namespace Autotest {
namespace Internal {

class TestTreeModel;
class TestTreeSortFilterModel;
class TestTreeView;

class TestNavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestNavigationWidget(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *event);
    QList<QToolButton *> createToolButtons();

signals:

public slots:

private slots:
    void onItemActivated(const QModelIndex &index);
    void onRunAllTriggered();
    void onRunSelectedTriggered();
    void onSortClicked();
    void onFilterMenuTriggered(QAction *action);

private:
    void initializeFilterMenu();

    TestTreeModel *m_model;
    TestTreeSortFilterModel *m_sortFilterModel;
    TestTreeView *m_view;
    QToolButton *m_sort;
    QToolButton *m_filterButton;
    QMenu *m_filterMenu;
    bool m_sortAlphabetically;

};

class TestNavigationWidgetFactory : public Core::INavigationWidgetFactory
{
    Q_OBJECT

public:
    TestNavigationWidgetFactory();

private:
    Core::NavigationView createWidget();

};

} // namespace Internal
} // namespace Autotest

#endif // TESTNAVIGATIONWIDGETTREEVIEW_H