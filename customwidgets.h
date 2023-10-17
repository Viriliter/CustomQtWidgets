#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>
#include <QApplication>
#include <QLabel>
#include <QToolTip>
#include <QTextEdit>
#include <QLineEdit>

#include "CustomColor.h"

class CustomFileBrowser: public QWidget
{
    Q_OBJECT
private:

private slots:
    void clicked_browse_();

public:
    CustomFileBrowser(QWidget *parent_=nullptr);
};

#endif // CUSTOMWIDGETS_H
