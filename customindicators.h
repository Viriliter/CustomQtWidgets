#ifndef CUSTOMINDICATORS_H
#define CUSTOMINDICATORS_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>
#include <QApplication>
#include <QLabel>

#include "CustomColor.h"

class ClassicLedIndicator: public QLabel
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ getColor_ WRITE setColor_);
    Q_PROPERTY(QColor defaultForeColor READ getDefaultForeColor_ WRITE setDefaultForeColor_);
private:
    QColor fore_color_;
    QColor default_fore_color_;
    QColor bg_color_;

    bool is_glowed_ = false;

    QPropertyAnimation *color_anim_;

    QColor getColor_() const;

    void setColor_(const QColor &color);

    QColor getDefaultForeColor_() const;

    void setDefaultForeColor_(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event_);

public:
    ClassicLedIndicator(QWidget *parent_=nullptr);

    void setTheme(const std::map<QString, QString> &style);

    void setColor(const QColor &color);

    void setGlow(bool is_glowed);

    void startColorAnimation(QColor color1, QColor color2, unsigned int frequency=1000, int duration=-1);

    void stopColorAnimation();

    void pauseColorAnimation();

    void resumeColorAnimation();
};

class RealisticLedIndicator: public QLabel
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ getColor_ WRITE setColor_);
    Q_PROPERTY(QColor defaultForeColor READ getDefaultForeColor_ WRITE setDefaultForeColor_);
private:
    QColor fore_color_;
    QColor default_fore_color_;
    QColor bg_color_;

    bool is_glowed_ = false;

    QPropertyAnimation *color_anim_;

    QColor getColor_() const;

    void setColor_(const QColor &color);

    QColor getDefaultForeColor_() const;

    void setDefaultForeColor_(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event_);

public:
    RealisticLedIndicator(QWidget *parent_=nullptr);

    void setTheme(const std::map<QString, QString> &style);

    void setColor(const QColor &color);

    void setGlow(bool is_glowed);

    void startColorAnimation(QColor color1, QColor color2, unsigned int frequency=1000, int duration=-1);

    void stopColorAnimation();

    void pauseColorAnimation();

    void resumeColorAnimation();
};

#endif // CUSTOMINDICATORS_H
