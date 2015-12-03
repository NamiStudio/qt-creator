/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at
** http://www.qt.io/contact-us
**
** This file is part of the Qt Creator Enterprise Auto Test Add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io/contact-us
**
****************************************************************************/

#ifndef AUTOTESTCONSTANTS_H
#define AUTOTESTCONSTANTS_H

#include <QtGlobal>

namespace Autotest {
namespace Constants {

const char ACTION_SCAN_ID[]             = "AutoTest.ScanAction";
const char ACTION_RUN_ALL_ID[]          = "AutoTest.RunAll";
const char ACTION_RUN_SELECTED_ID[]     = "AutoTest.RunSelected";
const char MENU_ID[]                    = "AutoTest.Menu";
const char AUTOTEST_ID[]                = "AutoTest.ATP";
const char AUTOTEST_CONTEXT[]           = "Auto Tests";
const char TASK_INDEX[]                 = "AutoTest.Task.Index";
const char TASK_PARSE[]                 = "AutoTest.Task.Parse";
const char UNNAMED_QUICKTESTS[]         = QT_TR_NOOP("<unnamed>");
const char AUTOTEST_SETTINGS_CATEGORY[] = "ZY.Tests";

} // namespace Autotest
} // namespace Constants

#endif // AUTOTESTCONSTANTS_H
