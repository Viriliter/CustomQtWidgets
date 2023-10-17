#ifndef CUSTOMBUTTONS_H
#define CUSTOMBUTTONS_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QMouseEvent>
#include <QPushButton>
#include <QIcon>
#include <QGraphicsDropShadowEffect>
#include <QApplication>

#include "CustomColor.h"

class ICustomButton: public QPushButton{
    Q_OBJECT

    Q_PROPERTY(QColor foreColor READ getForeColor_ WRITE setForeColor_);
    Q_PROPERTY(QColor foreDefaultColor READ getForeDefaultColor_ WRITE setForeDefaultColor_);
    Q_PROPERTY(QColor foreOnHoverColor READ getForeOnHoverColor_ WRITE setForeOnHoverColor_);
    Q_PROPERTY(QColor foreOnPressColor READ getForeOnPressColor_ WRITE setForeOnPressColor_);
    Q_PROPERTY(QColor foreOnReleaseColor READ getForeOnReleaseColor_ WRITE setForeOnReleaseColor_);
    Q_PROPERTY(QColor foreOnClickColor READ getForeOnClickColor_ WRITE setForeOnClickColor_);
    Q_PROPERTY(QColor bgColor READ getBgColor_ WRITE setBgColor_);
    Q_PROPERTY(QColor bgDefaultColor READ getBgDefaultColor_ WRITE setBgDefaultColor_);
    Q_PROPERTY(QColor bgOnHoverColor READ getBgOnHoverColor_ WRITE setBgOnHoverColor_);
    Q_PROPERTY(QColor bgOnPressColor READ getBgOnPressColor_ WRITE setBgOnPressColor_);
    Q_PROPERTY(QColor bgOnReleaseColor READ getBgOnReleaseColor_ WRITE setBgOnReleaseColor_);
    Q_PROPERTY(QColor bgOnClickColor READ getBgOnClickColor_ WRITE setBgOnClickColor_);
    Q_PROPERTY(QColor checkedColor READ getCheckedColor_ WRITE setCheckedColor_);
    Q_PROPERTY(QColor uncheckedColor READ getUncheckedColor_ WRITE setUncheckedColor_);
    Q_PROPERTY(QColor borderColor READ getBorderColor_ WRITE setBorderColor_);
    Q_PROPERTY(unsigned int borderWeight READ getBorderWeight_ WRITE setBorderWeight_);
    Q_PROPERTY(QString text READ getText_ WRITE setText_);

protected:
    QColor fore_color_;
    QColor fore_default_color_;
    QColor fore_on_hover_color_;
    QColor fore_on_press_color_;
    QColor fore_on_release_color_;
    QColor fore_on_click_color_;

    QColor bg_color_;
    QColor bg_default_color_;
    QColor bg_on_hover_color_;
    QColor bg_on_press_color_;
    QColor bg_on_release_color_;
    QColor bg_on_click_color_;

    QColor checked_color_;
    QColor unchecked_color_;

    QColor border_color_;

    unsigned int border_weight_;

    QString text_;

    QColor getForeColor_() const{ return this->fore_color_; };

    void setForeColor_(const QColor &color) { this->fore_color_ = color; this->repaint(); };

    QColor getForeDefaultColor_() const{ return this->fore_default_color_; };

    void setForeDefaultColor_(const QColor &color) { this->fore_default_color_ = color; this->repaint(); };

    QColor getForeOnHoverColor_() const{ return this->fore_on_hover_color_; };

    void setForeOnHoverColor_(const QColor &color) { this->fore_on_hover_color_ = color; this->repaint(); };

    QColor getForeOnPressColor_() const{ return this->fore_on_press_color_; };

    void setForeOnPressColor_(const QColor &color) { this->fore_on_press_color_ = color; this->repaint(); };

    QColor getForeOnReleaseColor_() const{ return this->fore_on_release_color_; };

    void setForeOnReleaseColor_(const QColor &color) { this->fore_on_release_color_ = color; this->repaint(); };

    QColor getForeOnClickColor_() const{ return this->fore_on_click_color_; };

    void setForeOnClickColor_(const QColor &color) { this->fore_on_click_color_ = color; this->repaint(); };

    QColor getBgColor_() const{ return this->bg_color_; };

    void setBgColor_(const QColor &color) { this->bg_color_ = color; this->repaint(); };

    QColor getBgDefaultColor_() const{ return this->bg_default_color_; };

    void setBgDefaultColor_(const QColor &color) { this->bg_default_color_ = color; this->repaint(); };

    QColor getBgOnHoverColor_() const{ return this->bg_on_hover_color_; };

    void setBgOnHoverColor_(const QColor &color) { this->bg_on_hover_color_ = color; this->repaint(); };

    QColor getBgOnPressColor_() const{ return this->bg_on_press_color_; };

    void setBgOnPressColor_(const QColor &color) { this->bg_on_press_color_ = color; this->repaint(); };

    QColor getBgOnReleaseColor_() const{ return this->bg_on_release_color_; };

    void setBgOnReleaseColor_(const QColor &color) { this->bg_on_release_color_ = color; this->repaint(); };

    QColor getBgOnClickColor_() const{ return this->bg_on_click_color_; };

    void setBgOnClickColor_(const QColor &color) { this->bg_on_click_color_ = color; this->repaint(); };

    QColor getCheckedColor_() const{ return this->checked_color_; };

    void setCheckedColor_(const QColor &color) { this->checked_color_ = color; this->repaint(); };

    QColor getUncheckedColor_() const{ return this->unchecked_color_; };

    void setUncheckedColor_(const QColor &color) { this->unchecked_color_ = color; this->repaint(); };

    QColor getBorderColor_() const{ return this->border_color_; };

    void setBorderColor_(const QColor &color) { this->border_color_ = color; this->repaint(); };

    unsigned int getBorderWeight_() const{ return this->border_weight_; };

    void setBorderWeight_(unsigned int weight) { this->border_weight_ = weight; this->repaint(); };

    QString getText_() const{ return this->text_; };

    void setText_(const QString &text) { this->text_ = text; this->repaint(); };

public:
    ICustomButton(QWidget *parent_=nullptr){ this->setParent(parent_); };

};

class ActivationButton: public ICustomButton
{
    Q_OBJECT
    Q_PROPERTY(int glowSize READ getGlowSize_ WRITE setGlowSize_);
private:
    QColor glow_color_;

    int glow_size_ = 0;
    bool is_pressed_ = false;
    QPropertyAnimation *glow_anim_;
    QGraphicsDropShadowEffect *shadow_;

    int getGlowSize_() const;

    void setGlowSize_(int glow_size);

public:
    ActivationButton(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void enterEvent(QEvent *event_);

    void leaveEvent(QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void glowAnimation();

};

class ConnectionButton: public ICustomButton
{
    Q_OBJECT
    Q_PROPERTY(std::pair<QColor, QColor> foreColors READ getForeColors_ WRITE setForeColors_);
    Q_PROPERTY(int swapColorFlag READ getSwapColorFlag_ WRITE setSwapColorFlag_);
private:
    QColor fore_color_1_;
    QColor fore_color_2_;

    int swap_color_flag_ = 0;
    bool is_pressed_ = false;

    QPropertyAnimation *connection_anim_;

    QColor convertHexToColor_(const QString &hex_value);

    void setBgColor_(const QColor color);

    std::pair<QColor, QColor> getForeColors_() const ;

    void setForeColors_(const std::pair<QColor, QColor> colors);

    int getSwapColorFlag_() const;

    void setSwapColorFlag_(int flag);

public:
    ConnectionButton(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void enterEvent(QEvent *event_);

    void leaveEvent(QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void connectionAnimation();

    void resumeAnimation();

    void pauseAnimation();

    void stopAnimation();

    void setTheme(const std::map<QString, QString> &style);

};

class FlatButton: public ICustomButton
{
    Q_OBJECT
private:

public:
    FlatButton(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    QString getText() const;

    void setText(const QString &text);

    void setTheme(const std::map<QString, QString> &style);

};

class PanelButton: public ICustomButton
{
    Q_OBJECT

    Q_PROPERTY(bool isBlinked READ getIsBlinked_ WRITE setIsBlinked_);
    Q_PROPERTY(bool checked READ getChecked_ WRITE setChecked_);
private:
    bool is_blinked_ = false;
    bool checked_ = false;
    bool toggled_ = false;

    QPropertyAnimation *check_anim_;

    bool getIsBlinked_() const;

    void setIsBlinked_(bool is_blinked);

    bool getChecked_() const;

    void setChecked_(bool checked);

    bool getToggled_() const;

    void setToggled_(bool toggled);


public:
    PanelButton(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void startAnimation();

    void stopAnimation();

    void setText(const QString &text);

    void setTheme(const std::map<QString, QString> &style);
};

class FireButton: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal glowDia READ getGlowDia_ WRITE setGlowDia_);
private:

    QColor bg_color_;
    QColor fore_color_;
    QColor border_color_;

    QString text_;
    qreal glow_dia_ = 0;
    int min_glow_dia_ = 0;
    int max_glow_dia_ = 0;

    bool is_active_ = false;

    QPropertyAnimation *glow_anim_;

    QColor getBgColor_() const;

    void setBgColor_(const QColor color);

    QColor getForeColor_() const;

    void setForeColor_(const QColor color);

    QString getText_() const;

    void setText_(const QString &text);

    qreal getGlowDia_() const;

    void setGlowDia_(qreal glow_dia);

public:
    FireButton(QWidget *parent_=nullptr);

    void keyPressEvent(QKeyEvent *event_);

    void keyReleaseEvent(QKeyEvent *event_);

    void mousePressEvent(QMouseEvent *event_);

    void resizeEvent(QResizeEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void startGlowAnimation();

    void stopGlowAnimation();

    void setTheme(const std::map<QString, QString> &style);

    void setText(const QString &text);

private slots:

    void clicked_();

signals:
    void fire();
    void pressed();
};

class BadgeButton: public ICustomButton
{
    Q_OBJECT
    Q_PROPERTY(unsigned int highlightFactor READ getHighlightFactor_ WRITE setHighlightFactor_);
    Q_PROPERTY(QColor badgeColor READ getBadgeColor_ WRITE setBadgeColor_);
    Q_PROPERTY(unsigned int notificationNumber READ getNotifyNumber_ WRITE setNotifyNumber_);

private:
    QColor badge_color_;

    unsigned int highlight_factor_ = 150;
    unsigned int notification_number_ = 0;

    QPropertyAnimation *badge_anim_;

    QIcon icon_{":icons/speech-bubble.svg"};

    void setBgColor_(QColor color);

    unsigned int getHighlightFactor_();

    void setHighlightFactor_(unsigned int highlight_factor);

    QColor getBadgeColor_();

    void setBadgeColor_(QColor color);

    unsigned int getNotifyNumber_();

    void setNotifyNumber_(unsigned int notification_number);

public:
    BadgeButton(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void badgeAnimation();

    unsigned int getNotifyNumber();

    void setNotifyNumber(unsigned int notification_number);

    void decreaseNotifyNumber();

    void increaseNotifyNumber();

    void resetNotifyNumber();
};

enum ToggleOrientation{
    Vertical,
    Horizontal
};

class ToggleButton: public ICustomButton
{
    Q_OBJECT
    Q_PROPERTY(qreal highlightFactor READ getHighlightFactor_ WRITE setHighlightFactor_);
    Q_PROPERTY(ToggleOrientation orientation READ getOrientation_ WRITE setOrientation_);
    Q_PROPERTY(QString iconOn READ getIconOn_ WRITE setIconOn_);
    Q_PROPERTY(QString iconOff READ getIconOff_ WRITE setIconOff_);

private:
    qreal highlight_factor_ = 120;

    ToggleOrientation orientation_;
    QString icon_on_;
    QString icon_off_;

    qreal getHighlightFactor_() const;

    void setHighlightFactor_(qreal value);

    QColor getUncheckedColor_() const;

    void setUncheckedColor_(const QColor &color);

    QColor getCheckedColor_() const;

    void setCheckedColor_(const QColor &color);

    ToggleOrientation getOrientation_() const;

    void setOrientation_(ToggleOrientation orientation);

    QString getIconOn_() const;

    void setIconOn_(const QString &icon);

    QString getIconOff_() const;

    void setIconOff_(const QString &icon);

private slots:
    void clickedSlot_();

public:
    ToggleButton(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void setTheme(const std::map<QString, QString> &style);

signals:
    void toggled(bool);
};

#endif // CUSTOMBUTTONS_H
