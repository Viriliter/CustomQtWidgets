#ifndef CUSTOMTOGGLES_H
#define CUSTOMTOGGLES_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtGlobal>
#include <QPushButton>

#include "CustomColor.h"

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

    QString getState1Text_() const;

    void setState1Text_(const QString &text);

    QString getState2Text_() const;

    void setState2Text_(const QString &text);

private slots:
    void clickedSlot_();

public:
    ToggleSwitch(QWidget *parent_=nullptr);

    void paintEvent(QPaintEvent *event_);

    void setStates(const QString &state1, const QString &state2);

    void setTheme(const std::map<QString, QString> &style);

signals:
    void toggled(bool);
};

class ToggleSwitchAndroid: public QPushButton
{
    Q_OBJECT
private:
    QColor fore_color_;
    QColor checked_color_;
    QColor unchecked_color_;

    bool is_mouse_pressed_ = false;

public:
    ToggleSwitchAndroid(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void setTheme(const std::map<QString, QString> &style);
};

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

    qreal getProgress_() const;

    void setProgress_(qreal value);

    bool setChecked_(bool value);

public:
    DelayedToggleSwitchAndroid(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void setTheme(const std::map<QString, QString> &style);

    bool isChecked() const;

    bool setChecked(bool value);

    void startWaitAnimation();

    void stopWaitAnimation();

    void resumeWaitAnimation();

    void pauseWaitAnimation();

signals:
    void aboutToToggled();
    void toggled(bool);
};

class ToggleSwitchIOS: public QPushButton
{
    Q_OBJECT
private:
    QColor fore_color_;
    QColor checked_color_;
    QColor unchecked_color_;

    bool is_mouse_pressed_ = false;

public:
    ToggleSwitchIOS(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void setTheme(const std::map<QString, QString> &style);

signals:
    void toggled(bool);
};

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

    qreal getProgress_() const;

    void setProgress_(qreal value);

    bool setChecked_(bool value);

public:
    DelayedToggleSwitchIOS(QWidget *parent_=nullptr);

    bool eventFilter(QObject *obj_, QEvent *event_);

    void paintEvent(QPaintEvent *event_);

    void setTheme(const std::map<QString, QString> &style);

    bool isChecked() const;

    bool setChecked(bool value);

    void startWaitAnimation();

    void stopWaitAnimation();

    void resumeWaitAnimation();

    void pauseWaitAnimation();

signals:
    void aboutToToggled();
    void toggled(bool);
};

#endif // CUSTOMTOGGLES_H
