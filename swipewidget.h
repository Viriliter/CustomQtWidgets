#ifndef SWIPEWIDGET_H
#define SWIPEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>

#include "CustomColor.h"

class SwipeWidget: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int value READ getValue_ WRITE setValue_);
    Q_PROPERTY(int glarePos READ getGlarePos_ WRITE setGlarePos_);
    Q_PROPERTY(QString baseText READ getBaseText_ WRITE setBaseText_);

private:
    QColor base_fore_color_;
    QColor base_bg_color_;
    QColor swipe_fore_color_;
    QColor swipe_bg_color_;
    QColor border_color_;

    QString base_text_ = "slide to unlock";

    bool is_mouse_pressed_ = false;
    qreal last_value_ = 0.0;
    qreal value_ = 0.0;
    QPoint last_pos_{};
    qreal travel_value_ = 0.0;
    qreal swipe_width_ = 0.1;
    qreal glare_pos_ = 0.0;

    QPropertyAnimation *text_anim_;

    void setBaseText_(const QString &base_text);

    qreal getValue_() const;

    void setValue_(qreal value);

    qreal getGlarePos_() const;

    void setGlarePos_(qreal glare_pos);

    QString getBaseText_() const;

    void setBaseText_(QString &base_text);

    void startAnimation_();

    void pauseAnimation_();

    void resumeAnimation_();

    void stopAnimation_();

protected:
    void mouseMoveEvent(QMouseEvent *event_);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void resizeEvent(QResizeEvent *event_);

public:
    SwipeWidget(QWidget *parent_=nullptr);

    void setTheme(const std::map<QString, QString> &style);

    void lock();

    void unlock();

signals:
    void unlocked();
    void locked();

};

#endif // SWIPEWIDGET_H
