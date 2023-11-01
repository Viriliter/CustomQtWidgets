#ifndef CUSTOMTEXTWIDGETS_H
#define CUSTOMTEXTWIDGETS_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>
#include <QApplication>
#include <QTextEdit>
#include <QLineEdit>
#include <QToolTip>

#include "CustomColor.h"

class CustomTextEdit: public QTextEdit
{
    Q_OBJECT
private:
    QString tooltip_;
    QPoint last_pos_;

public:
    CustomTextEdit(QWidget *parent_=nullptr);

    void setToolTip(const QString &tooltip);

    bool event(QEvent *event_);
};

class CustomLineEdit: public QLineEdit
{
    Q_OBJECT
private:
    QString tooltip_;
    QPoint last_pos_;

protected:
    bool event(QEvent *event_);

public:
    CustomLineEdit(QWidget *parent_=nullptr);

    void setToolTip(const QString &tooltip);
};

class BorderedTextEdit: public QTextEdit
{
    Q_OBJECT

    Q_PROPERTY(QColor foreColor READ getForeColor_ WRITE setForeColor_);
    Q_PROPERTY(QColor bgColor READ getBgColor_ WRITE setBgColor_);
    Q_PROPERTY(QColor borderColor READ getBorderColor_ WRITE setBorderColor_);
    Q_PROPERTY(unsigned int borderWeight READ getBorderWeight_ WRITE setBorderWeight_);

    QColor getForeColor_() const;

    void setForeColor_(const QColor &color);

    QColor getBgColor_() const;

    void setBgColor_(const QColor &color);

    QColor getBorderColor_() const;

    void setBorderColor_(const QColor &color);

    unsigned int getBorderWeight_() const;

    void setBorderWeight_(unsigned int  weight);

private:
    QColor fore_color_;
    QColor bg_color_;
    QColor border_color_;

    unsigned int border_weight_;

    QString text_;

protected:
    void paintEvent(QPaintEvent *event_);

public:
    BorderedTextEdit(QWidget *parent_=nullptr);

    void setTheme(const std::map<QString, QString> &style);

    void setText(const QString &text);
};

class BorderedTextLineEdit: public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(QColor foreColor READ getForeColor_ WRITE setForeColor_);
    Q_PROPERTY(QColor bgColor READ getBgColor_ WRITE setBgColor_);
    Q_PROPERTY(QColor borderColor READ getBorderColor_ WRITE setBorderColor_);
    Q_PROPERTY(unsigned int borderWeight READ getBorderWeight_ WRITE setBorderWeight_);

    QColor getForeColor_() const;

    void setForeColor_(const QColor &color);

    QColor getBgColor_() const;

    void setBgColor_(const QColor &color);

    QColor getBorderColor_() const;

    void setBorderColor_(const QColor &color);

    unsigned int getBorderWeight_() const;

    void setBorderWeight_(unsigned int  weight);

private:
    QColor fore_color_;
    QColor bg_color_;
    QColor border_color_;

    unsigned int border_weight_;

    QString text_;

protected:
    void paintEvent(QPaintEvent *event_);

public:
    BorderedTextLineEdit(QWidget *parent_=nullptr);

    void setTheme(const std::map<QString, QString> &style);

    void setText(const QString &text);

};

#endif // CUSTOMTEXTWIDGETS_H
