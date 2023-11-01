#ifndef CUSTOMPROGRESSBARS_H
#define CUSTOMPROGRESSBARS_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QMouseEvent>
#include <QProgressBar>

#include "CustomColor.h"

/**
 * @brief The ACustomProgressBar class
 */
class ACustomProgressBar: public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor READ getProgressColor_ WRITE setProgressColor_);
    Q_PROPERTY(qreal progress READ getProgress_ WRITE setProgress_);
    Q_PROPERTY(QString progressText READ getProgressText_ WRITE setProgressText_);

protected:
    QColor fore_color_;
    QColor bg_color_;
    QColor progress_color_;
    qreal progress_ = 0.0;

    QString progress_text_;

    bool progress_visibility_ = true;

    QPropertyAnimation *progress_anim_;

    QPropertyAnimation *color_anim_;

    /**
     * @brief This protected function returns foreground color.
     * @return Foreground color
     */
    QColor getForeColor_() const;

    /**
     * @brief This protected function sets foreground color.
     * @param[in] color Foreground color
     */
    void setForeColor_(const QColor &color);

    /**
     * @brief This protected function returns background color.
     * @return Background color
     */
    QColor getBgColor_() const;

    /**
     * @brief This protected function sets background color.
     * @param[in] color Background color
     */
    void setBgColor_(const QColor &color);

    /**
     * @brief This protected function returns progress color.
     * @return Background color
     */
    QColor getProgressColor_() const;

    /**
     * @brief This protected function sets progress color.
     * @param[in] color Progress color
     */
    void setProgressColor_(const QColor &color);

    /**
     * @brief This protected function returns progress.
     * @return Progress
     */
    qreal getProgress_() const;

    /**
     * @brief This protected function sets progress.
     * @param[in] value Progress
     */
    void setProgress_(qreal value);

    /**
     * @brief This protected function returns progress text.
     * @return Progress text
     */
    QString getProgressText_() const;

    /**
     * @brief This protected function sets progress text.
     * @param[in] text Progress text
     */
    void setProgressText_(const QString &text);

    virtual void paintEvent(QPaintEvent *event_) = 0;


public:
    ACustomProgressBar(QWidget *parent_=nullptr);

    /**
     * @brief This function starts progress animation.
     * @param[in] start_value Value where progress starts
     * @param[in] end_value Value where progress ends
     * @param[in] duration Duration of the animation in miliseconds (default:1000)
     * @param[in] count Count (default:1)
     */
    void startAnimation(qreal start_value=0, qreal end_value=1, qint64 duration=1000, qint64 count=1);

    /**
     * @brief This function stops progress animation.
     */
    void stopAnimation();

    /**
     * @brief This function pauses progress animation.
     */
    void pauseAnimation();

    /**
     * @brief This function resumes progress animation.
     */
    void resumeAnimation();

    /**
     * @brief This function starts color animation.
     * @param[in] start_color Color which progress starts
     * @param[in] end_value Color which progress ends
     * @param[in] duration Duration of animation in miliseconds (default:1000)
     * @param[in] count Count (default:1)
     */
    void animateColor(QColor start_color, QColor end_value, qint64 duration=1000, qint64 count=1);

    /**
     * @brief This function starts flash animation of progress bar.
     * @param[in] duration Duration of the animation in miliseconds (default:1000)
     * @param[in] count Count (default:1)
     */
    void animateFlash(qint64 duration=1000, qint64 count=1);

    /**
     * @brief This function sets visibility of progress value.
     * @param[in] visibility Visibility of progress
     */
    void setProgressVisibity(bool visibility);

    /**
     * @brief This function sets progress.
     * @param[in] progress Value of progress [0-1]
     * @param[in] progress Progress text (default:"")
     */
    void setProgress(qint64 progress, QString text="");

    /**
     * @brief This function retuns progress value.
     * @return Value of progress [0-1]
     */
    qint64 getProgress() const;

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

signals:
    void finished();
    void stopped();
    void paused();
    void resumed();
};

/**
 * @brief The CustomProgressBar class
 */
class CustomProgressBar: public ACustomProgressBar
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event_);

public:
    CustomProgressBar(QWidget *parent_=nullptr);
    
};

/**
 * @brief The CustomCircularProgressBar class
 */
class CustomCircularProgressBar: public ACustomProgressBar
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event_);

public:
    CustomCircularProgressBar(QWidget *parent_=nullptr);
};

#endif // CUSTOMPROGRESSBARS_H
