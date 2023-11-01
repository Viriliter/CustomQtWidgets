#ifndef CUSTOMTOGGLES_H
#define CUSTOMTOGGLES_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>
#include <QPushButton>

#include "CustomColor.h"

/**
 * @brief The ToggleSwitch class
 */
class ToggleSwitch: public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QString foreColor READ getState1Text_ WRITE setState1Text_);
    Q_PROPERTY(QString bgColor READ getState2Text_ WRITE setState2Text_);

private:
    QColor fore_color_;
    QColor text_color_;
    QColor unchecked_color_;
    QColor checked_color_;

    qreal highlight_factor_ = 120;

    QString state_1_text_;
    QString state_2_text_;

    /**
     * @brief This private function returns text of the button for State 1.
     * @return Button text of State 1
     */
    QString getState1Text_() const;

    /**
     * @brief This private function sets text of the button for State 1.
     * @param[in] text Button text of State 1
     */
    void setState1Text_(const QString &text);

    /**
     * @brief This private function returns text of the button for State 2.
     * @return Button text of State 2
     */
    QString getState2Text_() const;

    /**
     * @brief This private function sets text of the button for State 2.
     * @param[in] text Button text of State 2
     */
    void setState2Text_(const QString &text);

private slots:
    void clickedSlot_();

protected:
    void paintEvent(QPaintEvent *event_);

public:
    ToggleSwitch(QWidget *parent_=nullptr);

    /**
     * @brief This function sets text of the button according to binary state.
     * @param[in] state1 State 1
     * @param[in] state1 State 2
     */
    void setStates(const QString &state1, const QString &state2);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

signals:
    void toggled(bool);
};

/**
 * @brief The ToggleSwitchAndroid class
 */
class ToggleSwitchAndroid: public QPushButton
{
    Q_OBJECT
private:
    QColor fore_color_;
    QColor checked_color_;
    QColor unchecked_color_;

    bool is_mouse_pressed_ = false;

protected:
    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    ToggleSwitchAndroid(QWidget *parent_=nullptr);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);
};

/**
 * @brief The DelayedToggleSwitchAndroid class
 */
class DelayedToggleSwitchAndroid: public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(qreal progress READ getProgress_ WRITE setProgress_);
private:
    QColor fore_color_;
    QColor checked_color_;
    QColor unchecked_color_;

    bool is_checked_ = false;
    qreal progress_ = 0.0;  // Range: 0-1
    bool is_mouse_pressed_ = false;

    QPropertyAnimation *wait_anim_;

    /**
     * @brief This private function return progress value of widget.
     * @return Progress value
     */
    qreal getProgress_() const;

    /**
     * @brief This private function sets progress value of widget.
     * @param[in] value Progress value
     */
    void setProgress_(qreal value);

    /**
     * @brief This private function returns check state.
     * @param[in] value Check state
     * @return Check state
     */
    bool setChecked_(bool value);

    /**
     * @brief This private function starts loading animation.
     */
    void startAnimation_();

    /**
     * @brief This private function stops loading animation.
     */
    void stopAnimation_();

    /**
     * @brief This private function resumes loading animation.
     */
    void resumeAnimation_();

    /**
     * @brief This private function pauses loading animation.
     */
    void pauseAnimation_();

protected:
    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    DelayedToggleSwitchAndroid(QWidget *parent_=nullptr);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

    /**
     * @brief This function returns check state.
     * @return Check state
     */
    bool isChecked() const;

    /**
     * @brief This function returns check state.
     * @param[in] value Check state
     * @return Check state
     */
    bool setChecked(bool value);

signals:
    void aboutToToggled();
    void toggled(bool);
};

/**
 * @brief The ToggleSwitchIOS class
 */
class ToggleSwitchIOS: public QPushButton
{
    Q_OBJECT
private:
    QColor fore_color_;
    QColor checked_color_;
    QColor unchecked_color_;

    bool is_mouse_pressed_ = false;

protected:
    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    ToggleSwitchIOS(QWidget *parent_=nullptr);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

signals:
    void toggled(bool);
};

/**
 * @brief The DelayedToggleSwitchIOS class
 */
class DelayedToggleSwitchIOS: public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(qreal progress READ getProgress_ WRITE setProgress_);
private:
    QColor fore_color_;
    QColor checked_color_;
    QColor unchecked_color_;

    bool is_checked_ = false;
    qreal progress_ = 0.0;  // Range: 0-1
    bool is_mouse_pressed_ = false;

    QPropertyAnimation *wait_anim_;

    /**
     * @brief This private function return progress value of widget.
     * @return Progress value
     */
    qreal getProgress_() const;

    /**
     * @brief This private function sets progress value of widget.
     * @param[in] value Progress value
     */
    void setProgress_(qreal value);

    /**
     * @brief This private function return check state.
     * @return Check state
     */
    bool setChecked_(bool value);

    /**
     * @brief This private function starts loading animation.
     */
    void startAnimation_();

    /**
     * @brief This private function stops loading animation.
     */
    void stopAnimation_();

    /**
     * @brief This private function resumes loading animation.
     */
    void resumeAnimation_();

    /**
     * @brief This private function pauses loading animation.
     */
    void pauseAnimation_();

protected:
    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

public:
    DelayedToggleSwitchIOS(QWidget *parent_=nullptr);

    /**
     * @brief This function sets theme of the widget.
     * @param[in] style style of theme
     */
    void setTheme(const std::map<QString, QString> &style);

    /**
     * @brief This function returns check state.
     * @return Check state
     */
    bool isChecked() const;

    /**
     * @brief This function sets check state.
     * @param[in] value Check state
     * @return Check state
     */
    bool setChecked(bool value);

signals:
    void aboutToToggled();
    void toggled(bool);
};

#endif // CUSTOMTOGGLES_H
