#ifndef CUSTOMPROGRESSBARS_H
#define CUSTOMPROGRESSBARS_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QMouseEvent>
#include <QProgressBar>

#include "CustomColor.h"

class CustomProgressBar: public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor READ getProgressColor_ WRITE setProgressColor_);
    Q_PROPERTY(qreal progress READ getProgress_ WRITE setProgress_);
    Q_PROPERTY(QString progressText READ getProgressText_ WRITE setProgressText_);
private:

    QColor fore_color_;
    QColor bg_color_;
    QColor progress_color_;
    qreal progress_ = 0.0;

    QString progress_text_;

    bool progress_visibility_ = true;

    QColor getForeColor_() const;

    void setForeColor_(const QColor &color);

    QColor getBgColor_() const;

    void setBgColor_(const QColor &color);

    QColor getProgressColor_() const;

    void setProgressColor_(const QColor &color);

    qreal getProgress_() const;

    void setProgress_(qreal value);

    QString getProgressText_() const;

    void setProgressText_(const QString &text);

    QPropertyAnimation *progress_anim_;
    QPropertyAnimation *color_anim_;

protected:
    void paintEvent(QPaintEvent *event_);

public:
    CustomProgressBar(QWidget *parent_=nullptr);
    
    void startAnimation(qreal start_value=0, qreal end_value=1, qint64 duration=1000, qint64 count=1);
    
    void stopAnimation();
    
    void pauseAnimation();
    
    void resumeAnimation();

    void animateColor(QColor start_color, QColor end_value, qint64 duration=1000, qint64 count=1);

    void animateFlash(qint64 duration=1000, qint64 count=1);

    void setProgressVisibity(bool visibility);

    void setProgress(qint64 progress, QString text="");

    qint64 getProgress() const;

    void setTheme(const std::map<QString, QString> &style);

signals:
    void finished();
    void stopped();
    void paused();
    void resumed();
};

class CustomCircularProgressBar: public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor READ getProgressColor_ WRITE setProgressColor_);
    Q_PROPERTY(qreal progress READ getProgress_ WRITE setProgress_);
    Q_PROPERTY(QString progressText READ getProgressText_ WRITE setProgressText_);
private:

    QColor fore_color_;
    QColor bg_color_;
    QColor progress_color_;
    qreal progress_ = 0.0;

    QString progress_text_;

    bool progress_visibility_ = true;

    QColor getForeColor_() const;

    void setForeColor_(const QColor &color);

    QColor getBgColor_() const;

    void setBgColor_(const QColor &color);

    QColor getProgressColor_() const;

    void setProgressColor_(const QColor &color);

    qreal getProgress_() const;

    void setProgress_(qreal value);

    QString getProgressText_() const;

    void setProgressText_(const QString &text);

    QPropertyAnimation *progress_anim_;

    QPropertyAnimation *color_anim_;

protected:
    void paintEvent(QPaintEvent *event_);

public:
    CustomCircularProgressBar(QWidget *parent_=nullptr);

    void startProgressAnimation(qreal start_value=0, qreal end_value=1, qint64 duration=1000, qint64 count=1);

    void stopProgressAnimation();

    void pauseProgressAnimation();

    void resumeProgressAnimation();

    void animateColor(QColor start_color, QColor end_value, qint64 duration=1000, qint64 count=1);

    void animateFlash(qint64 duration=1000, qint64 count=1);

    void setProgressVisibity(bool visibility);

    void setProgress(qint64 progress, QString text="");

    qint64 getProgress() const;

    void setTheme(const std::map<QString, QString> &style);

signals:
    void finished();
    void stopped();
    void paused();
    void resumed();
};

#endif // CUSTOMPROGRESSBARS_H
