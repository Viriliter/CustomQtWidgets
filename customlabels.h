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

/**
 * @brief The HighlightLabel class
 */
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

    /**
     * @brief This function returns checked stated.
     * @return Checked state
     */
    bool getIsChecked_() const;

    /**
     * @brief This function sets checked stated.
     * @param[in] is_checked Checked state
     */
    void setIsChecked_(bool is_checked);

    /**
     * @brief This protected function returns base background color.
     * @return Base background color
     */
    QColor getBaseBgColor_() const;

    /**
     * @brief This protected function sets base background color.
     * @param[in] color Base background color
     */
    void setBaseBgColor_(const QColor &color);

    /**
     * @brief This private function returns base foreground color.
     * @return Base foreground color
     */
    QColor getBaseForeColor_() const;

    /**
     * @brief This private function sets base foreground color.
     * @param[in] color Base foreground color
     */
    void setBaseForeColor_(const QColor &color);

public:
    HighlightLabel(QWidget *parent_=nullptr);

};

/**
 * @brief The DynamicToolTipLabel class
 */
class DynamicToolTipLabel: public QLabel
{
    Q_OBJECT
private:
    QString tooltip_;
    QPoint last_pos_;

protected:
    bool event(QEvent *event_);

public:
    DynamicToolTipLabel(QWidget *parent_=nullptr);

    void setToolTip(const QString &tooltip);
};

#endif // CUSTOMLABELS_H
