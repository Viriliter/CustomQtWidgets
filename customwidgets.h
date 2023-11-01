#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>
#include <QPlainTextEdit>

#include "CustomColor.h"

#if defined(_WIN32) || defined(_WIN64)
    #define NEWLINE "\r\n"
#elif defined(__APPLE__)
    #define NEWLINE "\n"
#elif defined(__linux__)
    #define NEWLINE "\n"
#else
    #define NEWLINE "\n"
#endif

/**
 * @brief The CustomFileBrowser class
 */
class CustomFileBrowser: public QWidget
{
    Q_OBJECT
private:

private slots:
    void clicked_browse_();

public:
    CustomFileBrowser(QWidget *parent_=nullptr);
};

/**
 * @brief The FastLogViewer class
 */
class FastLogViewer: public QPlainTextEdit
{
    Q_OBJECT
private:
    unsigned int maxLineCount_ = 50000;
    unsigned int refrashRate_;

    QList<QString> bufferedLines;

    QTimer *updateTimer_;

    unsigned int getMaximumLine_() const;

    void setMaximumLine_(unsigned int lineCount);

public:
    FastLogViewer(QWidget *parent_=nullptr);

    void setMaximumLine(unsigned int lineCount);

    void setRefreshRate(unsigned int refreshRate);

    void addRaw(const QString &newRaw);

    void addRaw(const QList<QString> &newRaws);

    void updateContent();

    void clearContent();
};
#endif // CUSTOMWIDGETS_H
