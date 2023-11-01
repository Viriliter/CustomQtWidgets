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

/**
 * @brief The ACustomButton class
 */
class ACustomButton: public QPushButton{
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
    ACustomButton(QWidget *parent_=nullptr){ this->setParent(parent_); };

};

/**
 * @brief The ActivationButton class
 */
class ActivationButton: public ACustomButton
{
    Q_OBJECT
    Q_PROPERTY(int glowSize READ getGlowSize_ WRITE setGlowSize_);
private:
    QColor glow_color_;

    int glow_size_ = 0;
    bool is_pressed_ = false;

    QPropertyAnimation *glow_anim_;
    QGraphicsDropShadowEffect *shadow_;

    /**
     * @brief This private returns glow size.
     * @return Size of glow
     */
    int getGlowSize_() const;

    /**
     * @brief This private function sets glow size.
     * @param[in] glow_size Size of glow
     */
    void setGlowSize_(int glow_size);

    /**
     * @brief This private function shows shadow effect.
     */
    void showShadow_();

    /**
     * @brief This private function hides shadow effect.
     */
    void hideShadow_();

protected:
    void paintEvent(QPaintEvent *event_);

public:
    ActivationButton(QWidget *parent_=nullptr);

    /**
     * @brief This function starts glow animation.
     */
    void startAnimation();

    /**
     * @brief This function stops glow animation.
     */
    void stopGlowAnimation();
};

/**
 * @brief The enumConnectionButtonStates enum
 */
enum enumConnectionButtonStates{
    Default,
    Connecting,
    Connected,
    Disconnected
};

/**
 * @brief The ConnectionButton class
 */
class ConnectionButton: public ACustomButton
{
    Q_OBJECT
    Q_PROPERTY(qreal pathOffset READ getPathOffset_ WRITE setPathOffset_);
private:

    QColor default_fore_color_;
    QColor connecting_fore_color_;
    QColor connected_fore_color_;
    QColor disconnected_fore_color_;

    QColor icon_color_1_;
    QColor icon_color_2_;

    qreal path_offset_ = 0.0;
    bool is_pressed_ = false;

    enumConnectionButtonStates state_ = enumConnectionButtonStates::Default;

    QPropertyAnimation *connection_anim_;

    /**
     * @brief This private function returns offset of dash of path
     * @return Path offset
     */
    qreal getPathOffset_() const;

    /**
     * @brief This private function sets offset of dash of path
     * @param[in] offset Path offset
     */
    void setPathOffset_(qreal offset);

    /**
     * @brief This private function starts connection animation.
     */
    void startAnimation_();

    /**
     * @brief This private function resumes connection animation.
     */
    void resumeAnimation_();

    /**
     * @brief This private function pause connection animation.
     */
    void pauseAnimation_();

    /**
     * @brief This private function stop connection animation.
     */
    void stopAnimation_();

protected:
    void paintEvent(QPaintEvent *event_);

public:
    ConnectionButton(QWidget *parent_=nullptr);

    enumConnectionButtonStates getState() const;

    /**
     * @brief This function sets connection state.
     * @param[in] state Connection state
     */
    void setState(enumConnectionButtonStates state);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

};

/**
 * @brief The FlatButton class
 */
class FlatButton: public ACustomButton
{
    Q_OBJECT
private:

protected:
    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    FlatButton(QWidget *parent_=nullptr);

    /**
     * @brief This function returns text of the button.
     * @return Text of button
     */
    QString getText() const;

    /**
     * @brief This function sets text of the button.
     * @param[in] text Text of button
     */
    void setText(const QString &text);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);
};

/**
 * @brief The PanelButton class
 */
class PanelButton: public ACustomButton
{
    Q_OBJECT

    Q_PROPERTY(bool isBlinked READ getIsBlinked_ WRITE setIsBlinked_);
    Q_PROPERTY(bool checked READ getToggled_ WRITE setToggled_);
private:
    bool is_blinked_ = false;

    QPropertyAnimation *check_anim_;

    /**
     * @brief This function returns blink condition.
     * @return Blink condition
     */
    bool getIsBlinked_() const;

    /**
     * @brief This function sets blink condition.
     * @param[in] is_blinked Blink condition
     */
    void setIsBlinked_(bool is_blinked);

    /**
     * @brief This private function returns toggle state of the button.
     * @return Toggle state
     */
    bool getToggled_() const;

    /**
     * @brief This private function sets toggle state of the button.
     * @param[in] checked Toggle state
     */
    void setToggled_(bool checked);

protected:
    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    PanelButton(QWidget *parent_=nullptr);

    /**
     * @brief This function starts blink animation.
     */
    void startAnimation();

    /**
     * @brief This function stops blink animation.
     */
    void stopAnimation();

    /**
     * @brief This function returns tect of the button.
     * @param text Text of the button
     */
    void setText(const QString &text);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);
};

/**
 * @brief The FireButton class
 */
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

    /**
     * @brief This private function sets background color.
     * @return Background color
     */
    QColor getBgColor_() const;

    /**
     * @brief This private function sets background color.
     * @param[in] color Background color
     */
    void setBgColor_(const QColor color);

    /**
     * @brief This private function sets foreground color.
     * @return Foreground color
     */
    QColor getForeColor_() const;

    /**
     * @brief This private function sets foreground color.
     * @param[in] color Foreground color
     */
    void setForeColor_(const QColor color);

    /**
     * @brief This private function returns text of the button.
     * @return Text of the button
     */
    QString getText_() const;

    /**
     * @brief This private function sets text of the button.
     * @param[in] text Text of the button
     */
    void setText_(const QString &text);

    /**
     * @brief This private function returns glow diameter.
     * @return Glow diameter
     */
    qreal getGlowDia_() const;

    /**
     * @brief This private function sets glow diameter.
     * @param[in] glow_dia Glow diameter
     */
    void setGlowDia_(qreal glow_dia);

protected:
    void keyPressEvent(QKeyEvent *event_);

    void keyReleaseEvent(QKeyEvent *event_);

    void mousePressEvent(QMouseEvent *event_);

    void resizeEvent(QResizeEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    FireButton(QWidget *parent_=nullptr);

    /**
     * @brief This function starts glow animation.
     */
    void startAnimation();

    /**
     * @brief This function stops glow animation.
     */
    void stopAnimation();

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

    /**
     * @brief This function sets text of the button.
     * @param[in] text Tex of the button
     */
    void setText(const QString &text);

private slots:
    void clicked_();

signals:
    void fire();
    void pressed();
};

/**
 * @brief The BadgeButton class
 */
class BadgeButton: public ACustomButton
{
    Q_OBJECT
    Q_PROPERTY(unsigned int highlightFactor READ getHighlightFactor_ WRITE setHighlightFactor_);
    Q_PROPERTY(QColor badgeColor READ getBadgeColor_ WRITE setBadgeColor_);
    Q_PROPERTY(unsigned int notificationNumber READ getNotifyNumber_ WRITE setNotifyNumber_);

private:
    QColor badge_color_;

    unsigned int highlight_factor_ = 150;
    unsigned int notification_number_ = 0;

    bool is_pressed_ = false;

    QPropertyAnimation *badge_anim_;

    QIcon icon_{":icons/speech-bubble.png"};

    /**
     * @brief This private function sets background color.
     * @param[in] color Background color
     */
    void setBgColor_(QColor color);

    /**
     * @brief This private function returns highlight factor of background color of badge notification number.
     * @returns Highlight factor
     */
    unsigned int getHighlightFactor_();

    /**
     * @brief This private function sets highlight factor of background color of badge notification number.
     * @param[in] highlight_factor Highlight factor
     */
    void setHighlightFactor_(unsigned int highlight_factor);

    /**
     * @brief This private function returns background color of badge notification number.
     * @return Background color of badge notification number
     */
    QColor getBadgeColor_();

    /**
     * @brief This private function sets background color of badge notification number.
     * @param[in] color Background color of badge notification number
     */
    void setBadgeColor_(QColor color);

    /**
     * @brief This private function returns notification count.
     * @returns Notification count
     */
    unsigned int getNotifyNumber_();

    /**
     * @brief This private function sets notification count.
     * @param[in] notification_number Notification count
     */
    void setNotifyNumber_(unsigned int notification_number);

    /**
     * @brief This private function starts badge animation.
     */
    void startAnimation_();

protected:
    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    BadgeButton(QWidget *parent_=nullptr);

    unsigned int getNotifyNumber();

    /**
     * @brief This private function sets notification count.
     * @param[in] notification_number Notification count
     */
    void setNotifyNumber(unsigned int notification_number);

    /**
     * @brief This private function decreases notification count by 1.
     */
    void decreaseNotifyNumber();

    /**
     * @brief This private function increases notification count by 1.
     */
    void increaseNotifyNumber();

    /**
     * @brief This private function resets notification count to 0.
     */
    void resetNotifyNumber();
};

/**
 * @brief The ToggleOrientation enum
 */
enum ToggleOrientation{
    Vertical,
    Horizontal
};

/**
 * @brief The NavigationButton class
 */
class NavigationButton: public ACustomButton
{
    Q_OBJECT
public:
    enum ButtonType{
        DefaultButton,
        BackButton,
        NextButton,
        FinishButton
    };

private:
    QString text_;

    ButtonType button_type_;

    QGraphicsDropShadowEffect *shadow_;

    /**
     * @brief This private function returns unchecked color of the button.
     * @return Unchecked color
     */
    QColor getUncheckedColor_() const;

    /**
     * @brief This private function sets unchecked color of the button.
     * @param[in] color Unchecked color
     */
    void setUncheckedColor_(const QColor &color);

    /**
     * @brief This private function returns checked color of the button.
     * @return Checked color
     */
    QColor getCheckedColor_() const;

    /**
     * @brief This private function sets checked color of the button.
     * @param[in] color Checked color
     */
    void setCheckedColor_(const QColor &color);

    /**
     * @brief This private sets button type.
     * @param[in] button_type Type of the button (ButtonType::DefaultButton | ButtonType::BackButton | ButtonType::NextButton | ButtonType::FinishButton)
     */
    void setButtonType_(const ButtonType button_type);

private slots:
    void clickedSlot_();

protected:
    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    NavigationButton(QWidget *parent_=nullptr);

    NavigationButton(const ButtonType button_type, QWidget *parent_=nullptr);

    /**
     * @brief This function shows shadow effect.
     */
    void showShadow_();

    /**
     * @brief This function hides shadow effect.
     */
    void hideShadow_();

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

signals:
    void toggled(bool);
};

#endif // CUSTOMBUTTONS_H
