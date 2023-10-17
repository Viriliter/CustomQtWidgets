#ifndef CUSTOMLABELS_H
#define CUSTOMLABELS_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>
#include <QLabel>
#include <QToolTip>
#include <QGraphicsDropShadowEffect>

#include "CustomColor.h"

class HighlightLabel: public QLabel
{
    Q_OBJECT

    Q_PROPERTY(bool isChecked READ getIsChecked_ WRITE setIsChecked_);
    Q_PROPERTY(QColor baseBgColor READ getBaseBgColor_ WRITE setBaseBgColor_);
    Q_PROPERTY(QColor baseForeColor READ getBaseForeColor_ WRITE setBaseForeColor_);

private:
    QColor base_fore_color_;
    QColor base_bg_color_;
    QColor border_color_;
    QColor unchecked_fore_color_;
    QColor checked_fore_color_;

    QGraphicsDropShadowEffect *blur_;
    QString text_;
    QFont text_font_;

    QString default_style_;
    QString checked_style_;

    bool is_checked_ = false;

    bool getIsChecked_() const;

    void setIsChecked_(bool is_checked);

    QColor getBaseBgColor_() const;

    void setBaseBgColor_(const QColor &color);

    QColor getBaseForeColor_() const;

    void setBaseForeColor_(const QColor &color);

public:
    HighlightLabel(QWidget *parent_=nullptr);

};


class DynamicToolTipLabel: public QLabel
{
    Q_OBJECT
private:
    QString tooltip_;
    QPoint last_pos_;

public:
    DynamicToolTipLabel(QWidget *parent_=nullptr);

    void setToolTip(const QString &tooltip);

    bool event(QEvent *event_);
};

#endif // CUSTOMLABELS_H
