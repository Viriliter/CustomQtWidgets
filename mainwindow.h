#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>

#include "custombuttons.h"
#include "customtoggles.h"

#include "swipewidget.h"

#include "customindicators.h"
//#include "customwidgets.h"
#include "customlabels.h"
#include "customtextwidgets.h"

#include "customprogressbars.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    SwipeWidget *swipeWidget = new SwipeWidget{};

    ActivationButton *activationButton = new ActivationButton{};
    BadgeButton *badgeButton = new BadgeButton{};
    ConnectionButton *connectionButton = new ConnectionButton{};
    FireButton *fireButton = new FireButton{};
    PanelButton *panelButton = new PanelButton{};
    FlatButton *flatButton = new FlatButton{};
    NavigationButton *backNavigationButton = new NavigationButton{NavigationButton::ButtonType::BackButton};
    NavigationButton *nextNavigationButton = new NavigationButton{NavigationButton::ButtonType::NextButton};

    ToggleSwitchIOS *toggleSwitchIOS = new ToggleSwitchIOS{};
    DelayedToggleSwitchIOS *delayedToggleSwitchIOS = new DelayedToggleSwitchIOS{};
    ToggleSwitchAndroid *toggleSwitchAndroid = new ToggleSwitchAndroid{};
    DelayedToggleSwitchAndroid *delayedToggleSwitchAndroid = new DelayedToggleSwitchAndroid{};
    ToggleSwitch *toggleSwitch = new ToggleSwitch{};

    ClassicLedIndicator *classicLedIndicator = new ClassicLedIndicator{};
    RealisticLedIndicator *realisticLedIndicator = new RealisticLedIndicator{};

    DynamicToolTipLabel *dynamicTooltipLabel = new DynamicToolTipLabel{};
    HighlightLabel *highlightLabel= new HighlightLabel{};

    CustomTextEdit *customTextEdit = new CustomTextEdit{};
    CustomLineEdit *customLineEdit = new CustomLineEdit{};
    BorderedTextEdit *borderedTextEdit = new BorderedTextEdit {};
    BorderedTextLineEdit *borderedTextLineEdit = new BorderedTextLineEdit {};

    CustomProgressBar *progressBar = new CustomProgressBar{};
    CustomCircularProgressBar *circularProgressBar = new CustomCircularProgressBar{};

    QTimer *timer = new QTimer{};

private slots:

    void keyPressEvent(QKeyEvent *event_);
    void keyReleaseEvent(QKeyEvent *event_);

    void clickedBadgeButton() noexcept;
    void clickedConnectionButton() noexcept;
    void lockedSwipedButton() noexcept;
    void unlockedSwipedButton() noexcept;
    void fireFireButton() noexcept;
    void clickedPanelButton() noexcept;
    void clickedFlatButton() noexcept;
    void toggledSwitchIOS(bool toggled) noexcept;
    void toggledDelayedSwitchIOS(bool toggled) noexcept;
    void toggledSwitchAndroid(bool toggled) noexcept;
    void toggledDelayedSwitchAndroid(bool toggled) noexcept;
    void toggledSwitch(bool toggled) noexcept;
    void toggledButton(bool toggled) noexcept;

    void timeoutTimer() noexcept;

};
#endif // MAINWINDOW_H
