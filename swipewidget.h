#ifndef SWIPEWIDGET_H
#define SWIPEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>

#include "CustomColor.h"

/**
 * @brief The SwipeWidget class
 */
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

    /**
     * @brief This private function sets base text of the widget.
     * @param[in] base_text Base text
     */
    void setBaseText_(const QString &base_text);

    /**
     * @brief This private function returns swipe button position.
     * @return Swipe button position
     */
    qreal getValue_() const;

    /**
     * @brief This private function sets swipe button position.
     * @param[in] value Swipe button position
     */
    void setValue_(qreal value);

    /**
     * @brief This private function returns position of the glare.
     * @return Glare Position
     */
    qreal getGlarePos_() const;

    /**
     * @brief This private function sets position of the glare.
     * @param[in] glare_pos Glare Position
     */
    void setGlarePos_(qreal glare_pos);

    /**
     * @brief This private function returns base text of the widget.
     * @return Base text
     */
    QString getBaseText_() const;

    /**
     * @brief This private function sets base text of the widget.
     * @param[in] base_text Base text
     */
    void setBaseText_(QString &base_text);

    /**
     * @brief This private function starts slide color mask animation.
     */
    void startAnimation_();

    /**
     * @brief This private function pauses slide color mask animation.
     */
    void pauseAnimation_();

    /**
     * @brief This private function resume slide color mask animation.
     */
    void resumeAnimation_();

    /**
     * @brief This private function stops slide color mask animation.
     */
    void stopAnimation_();

protected:
    void mouseMoveEvent(QMouseEvent *event_);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void resizeEvent(QResizeEvent *event_);

public:
    SwipeWidget(QWidget *parent_=nullptr);

    /**
     * @brief This function sets text of the button.
     * @param[in] text Tex of the button
     */
    void setTheme(const std::map<QString, QString> &style);

    /**
     * @brief This function sets widget to locked position.
     */
    void lock();

    /**
     * @brief This function sets widget to unlocked position.
     */
    void unlock();

signals:
    void unlocked();
    void locked();

};

#endif // SWIPEWIDGET_H
