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


/**
 * @brief The ALedIndicator class
 */
class ALedIndicator: public QLabel
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ getColor_ WRITE setColor_);
    Q_PROPERTY(QColor defaultForeColor READ getDefaultForeColor_ WRITE setDefaultForeColor_);
protected:
    QColor fore_color_;
    QColor default_fore_color_;
    QColor bg_color_;

    bool is_glowed_ = false;

    QPropertyAnimation *color_anim_;

    /**
     * @brief This protected function returns LED color.
     * @return LED color
     */
    QColor getColor_() const;

    /**
     * @brief This protected function sets LED color.
     * @param[in] color LED color
     */
    void setColor_(const QColor &color);

    /**
     * @brief This protected function returns default LED color.
     * @return default LED color
     */
    QColor getDefaultForeColor_() const;

    /**
     * @brief This protected function sets default LED color.
     * @param[in] color default LED color
     */
    void setDefaultForeColor_(const QColor &color);

    virtual void paintEvent(QPaintEvent *event_) = 0;

public:
    ALedIndicator(QWidget *parent_=nullptr);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

    /**
     * @brief This private function sets LED color.
     * @param[in] color LED color
     */
    void setColor(const QColor &color);

    /**
     * @brief This function sets glow feature of LED.
     * @param[in] is_glowed glow is enabled if true
     */
    void setGlow(bool is_glowed);

    /**
     * @brief This function starts blink animation of LED.
     * The blink effect alternates two provided color in defined frequency and duration.
     *
     * @param[in] color1 Color1
     * @param[in] color2 Color2
     * @param[in] frequency frequency of blink in miliseconds
     * @param[in] duration duration of blink in miliseconds
     */
    void startColorAnimation(QColor color1, QColor color2, unsigned int frequency=1000, int duration=-1);

    /**
     * @brief This function stops blink animation.
     */
    void stopColorAnimation();

    /**
     * @brief This function pauses blink animation.
     */
    void pauseColorAnimation();

    /**
     * @brief This function resumes blink animation.
     */
    void resumeColorAnimation();

};

/**
 * @brief The ClassicLedIndicator class
 */
class ClassicLedIndicator: public ALedIndicator
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event_);
};

/**
 * @brief The RealisticLedIndicator class
 */
class RealisticLedIndicator: public ALedIndicator
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event_);
};

#endif // CUSTOMINDICATORS_H
