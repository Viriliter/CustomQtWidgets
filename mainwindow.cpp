#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("background: #eeeeee;");

    grabKeyboard();

    QWidget *centralwidget = new QWidget();
    QGridLayout *layout_ = new QGridLayout{};

    QScrollArea *scrollA = new QScrollArea(centralwidget);
    scrollA->setObjectName(QString::fromUtf8("scrollA"));
    scrollA->setWidgetResizable(true);
    QWidget *scrollA_contents = new QWidget();
    scrollA_contents->setObjectName(QString::fromUtf8("scrollA_contents"));
    QGridLayout *layout_scroll_area = new QGridLayout(scrollA_contents);
    layout_scroll_area->setObjectName(QString::fromUtf8("layout_scroll_area"));

    /*
     * Custom Widgets
     */
    QGroupBox *groupB_custom_widgets = new QGroupBox(scrollA_contents);
    groupB_custom_widgets->setTitle("Custom Widgets");
    groupB_custom_widgets->setObjectName(QString::fromUtf8("groupB_custom_widgets"));
    QGridLayout *layout_custom_widgets = new QGridLayout{};

    QLabel *labelSwipeWidget = new QLabel("Swipe Widget");

    swipeWidget->setFixedSize(QSize(200,50));
    layout_custom_widgets->addWidget(labelSwipeWidget, 0, 0, 1, 1);
    layout_custom_widgets->addWidget(swipeWidget, 0, 1, 1, 1);

    groupB_custom_widgets->setLayout(layout_custom_widgets);

    /*
     * Custom Text Edits
     */
    QGroupBox *groupB_custom_text_edits = new QGroupBox(scrollA_contents);
    groupB_custom_text_edits->setTitle("Custom Text Edits");
    groupB_custom_text_edits->setObjectName(QString::fromUtf8("groupB_custom_text_edits"));
    QGridLayout *layout_custom_text = new QGridLayout{};

    QLabel *labelCustomTextEdit = new QLabel("Custom Text Edit");
    QLabel *labelBorderedTextEdit = new QLabel("Bordered Text Edit");
    QLabel *labelBorderedTextLineEdit = new QLabel("Bordered Text Line Edit");

    customTextEdit->setText("This is CustomTextEdit");
    customTextEdit->setToolTip("Dynamic update");
    customLineEdit->setText("This is CustomLineEdit");
    customLineEdit->setToolTip("Dynamic update");
    borderedTextEdit->setText("This is BorderedTextEdit");
    borderedTextLineEdit->setText("This is BorderedTextLineEdit");

    //layout_custom_text->addWidget(labelCustomTextEdit, 0, 0, 1, 1);
    //layout_custom_text->addWidget(customTextEdit, 0, 1, 1, 1);
    //layout_custom_text->addWidget(labelBorderedTextEdit, 1, 0, 1, 1);
    //layout_custom_text->addWidget(borderedTextEdit, 1, 1, 1, 1);
    //layout_custom_text->addWidget(labelBorderedTextLineEdit, 2, 0, 1, 1);
    //layout_custom_text->addWidget(borderedTextLineEdit, 2, 1, 1, 1);

    groupB_custom_text_edits->setLayout(layout_custom_text);

    /*
     * Custom Toggles
     */
    QGroupBox *groupB_custom_toggles = new QGroupBox(scrollA_contents);
    groupB_custom_toggles->setTitle("Custom Toggles");
    groupB_custom_toggles->setObjectName(QString::fromUtf8("groupB_custom_toggles"));
    QGridLayout *layout_custom_toggles = new QGridLayout{};

    delayedToggleSwitchIOS->setChecked(false);
    delayedToggleSwitchAndroid->setChecked(false);

    QLabel *labelToggleSwitchIOS = new QLabel("Toggle Switch (IOS)");
    QLabel *labelDelayedToggleSwitchIOS = new QLabel("Delayed Toggle Switch (IOS)");
    QLabel *labelToggleSwitchAndroid = new QLabel("Toggle Switch (Android)");
    QLabel *labelDelayedToggleSwitchAndroid = new QLabel("Delayed Toggle Switch (Android)");
    QLabel *labelToggleSwitch = new QLabel("Toggle Switch");

    layout_custom_toggles->addWidget(labelToggleSwitchIOS, 0, 0, 1, 1);
    layout_custom_toggles->addWidget(toggleSwitchIOS, 0, 1, 1, 1);
    layout_custom_toggles->addWidget(labelDelayedToggleSwitchIOS, 1, 0, 1, 1);
    layout_custom_toggles->addWidget(delayedToggleSwitchIOS, 1, 1, 1, 1);
    layout_custom_toggles->addWidget(labelToggleSwitchAndroid, 2, 0, 1, 1);
    layout_custom_toggles->addWidget(toggleSwitchAndroid, 2, 1, 1, 1);
    layout_custom_toggles->addWidget(labelDelayedToggleSwitchAndroid, 3, 0, 1, 1);
    layout_custom_toggles->addWidget(delayedToggleSwitchAndroid, 3, 1, 1, 1);
    layout_custom_toggles->addWidget(labelToggleSwitch, 4, 0, 1, 1);
    layout_custom_toggles->addWidget(toggleSwitch, 4, 1, 1, 1);

    groupB_custom_toggles->setLayout(layout_custom_toggles);

    /*
     * Custom Indicators
     */
    QGroupBox *groupB_custom_indicators = new QGroupBox(scrollA_contents);
    groupB_custom_indicators->setTitle("Custom Indicators");
    groupB_custom_indicators->setObjectName(QString::fromUtf8("groupB_custom_indicators"));
    QGridLayout *layout_custom_indicators = new QGridLayout{};

    classicLedIndicator->setFixedSize(QSize(30,30));
    realisticLedIndicator->setFixedSize(QSize(30,30));
    classicLedIndicator->setGlow(true);
    realisticLedIndicator->setGlow(true);
    classicLedIndicator->startColorAnimation(QColor(255,0,0), QColor(255,255,255));
    realisticLedIndicator->startColorAnimation(QColor(255,0,0), QColor(255,255,255));

    QLabel *labelClassicLedIndicator = new QLabel("Classic Led Indicator");
    QLabel *labelRealisticLedIndicator = new QLabel("Realistic Led Indicator");

    layout_custom_indicators->addWidget(labelClassicLedIndicator, 0, 0, 1, 1);
    layout_custom_indicators->addWidget(classicLedIndicator, 0, 1, 1, 1);
    layout_custom_indicators->addWidget(labelRealisticLedIndicator, 1, 0, 1, 1);
    layout_custom_indicators->addWidget(realisticLedIndicator, 1, 1, 1, 1);

    groupB_custom_indicators->setLayout(layout_custom_indicators);

    /*
     * Custom Labels
     */

    QGroupBox *groupB_custom_labels = new QGroupBox(scrollA_contents);
    groupB_custom_labels->setTitle("Custom Labels");
    groupB_custom_labels->setObjectName(QString::fromUtf8("groupB_custom_labels"));
    QGridLayout *layout_custom_labels = new QGridLayout{};

    highlightLabel->setText("This is HighlightLabel");
    dynamicTooltipLabel->setText("This is CustomLabel");
    dynamicTooltipLabel->setToolTip("Dynamic update");

    QLabel *labelHighlightLabel = new QLabel("Highlight Label");
    QLabel *labelDynamicTooltipLabel = new QLabel("Dynamic Tooltip Label");

    layout_custom_labels->addWidget(labelHighlightLabel, 0, 0, 1, 1);
    layout_custom_labels->addWidget(highlightLabel, 0, 1, 1, 1);
    layout_custom_labels->addWidget(labelDynamicTooltipLabel, 1, 0, 1, 1);
    layout_custom_labels->addWidget(dynamicTooltipLabel, 1, 1, 1, 1);

    groupB_custom_labels->setLayout(layout_custom_labels);

    /*
     * Custom Buttons
     */
    QGroupBox *groupB_custom_buttons = new QGroupBox(scrollA_contents);
    groupB_custom_buttons->setTitle("Custom Buttons");
    groupB_custom_buttons->setObjectName(QString::fromUtf8("groupB_custom_buttons"));
    QGridLayout *layout_custom_buttons = new QGridLayout{};

    connectionButton->setFixedSize(QSize(50,50));
    fireButton->setFixedSize(QSize(150,150));
    panelButton->setFixedSize(QSize(100,50));
    backNavigationButton->setFixedSize(QSize(170,44));
    nextNavigationButton->setFixedSize(QSize(170,44));

    QLabel *labelActivationButton = new QLabel("Activation Button");
    QLabel *labelBadgeButton = new QLabel("Badge Button");
    QLabel *labelConnectionButton = new QLabel("Connection Button");
    QLabel *labelFireButton = new QLabel("Fire Button");
    QLabel *labelPanelButton = new QLabel("Panel Button");
    QLabel *labelFlatButton = new QLabel("Flat Button");
    QLabel *labelBackNavigationButton = new QLabel("Back Button");
    QLabel *labelNextNavigationButton = new QLabel("Next Button");

    layout_custom_buttons->addWidget(labelActivationButton, 0, 0, 1, 1);
    layout_custom_buttons->addWidget(activationButton, 0, 1, 1, 1);
    layout_custom_buttons->addWidget(labelBadgeButton, 1, 0, 1, 1);  // Bug in bg color after mouse click release
    layout_custom_buttons->addWidget(badgeButton, 1, 1, 1, 1);  // Bug in bg color after mouse click release
    layout_custom_buttons->addWidget(labelConnectionButton, 2, 0, 1, 1);
    layout_custom_buttons->addWidget(connectionButton, 2, 1, 1, 1);
    layout_custom_buttons->addWidget(labelFireButton, 3, 0, 1, 1);
    layout_custom_buttons->addWidget(fireButton, 3, 1, 1, 1);
    layout_custom_buttons->addWidget(labelPanelButton, 4, 0, 1, 1);
    layout_custom_buttons->addWidget(panelButton, 4, 1, 1, 1);
    layout_custom_buttons->addWidget(labelFlatButton, 5, 0, 1, 1);
    layout_custom_buttons->addWidget(flatButton, 5, 1, 1, 1);
    layout_custom_buttons->addWidget(labelBackNavigationButton, 6, 0, 1, 1);
    layout_custom_buttons->addWidget(backNavigationButton, 6, 1, 1, 1);
    layout_custom_buttons->addWidget(labelNextNavigationButton, 7, 0, 1, 1);
    layout_custom_buttons->addWidget(nextNavigationButton, 7, 1, 1, 1);

    groupB_custom_buttons->setLayout(layout_custom_buttons);

    /*
     * Custom Loading Bars
     */
    QGroupBox *groupB_custom_loading_bars = new QGroupBox(scrollA_contents);
    groupB_custom_loading_bars->setTitle("Custom LoadingBars");
    groupB_custom_loading_bars->setObjectName(QString::fromUtf8("groupB_custom_loading_bars"));
    QGridLayout *layout_custom_loading_bars = new QGridLayout{};

    QLabel *labelProgressBar = new QLabel("Progress Bar");
    QLabel *labelCircularProgressBar = new QLabel("Circular Progress Bar");

    layout_custom_loading_bars->addWidget(labelProgressBar, 0, 0, 1, 1);
    layout_custom_loading_bars->addWidget(progressBar, 0, 1, 1, 1);
    layout_custom_loading_bars->addWidget(labelCircularProgressBar, 1, 0, 1, 1);
    layout_custom_loading_bars->addWidget(circularProgressBar, 1, 1, 1, 1);

    this->progressBar->startProgressAnimation(0, 1, 5000, -1);
    this->circularProgressBar->startProgressAnimation(0, 1, 5000, -1);

    groupB_custom_loading_bars->setLayout(layout_custom_loading_bars);

    layout_scroll_area->addWidget(groupB_custom_widgets,    0, 0, 1, 1);
    layout_scroll_area->addWidget(groupB_custom_text_edits, 0, 1, 1, 1);
    layout_scroll_area->addWidget(groupB_custom_toggles,    1, 0, 2, 1);
    layout_scroll_area->addWidget(groupB_custom_indicators, 1, 1, 1, 1);
    layout_scroll_area->addWidget(groupB_custom_labels, 2, 1, 1, 1);
    layout_scroll_area->addWidget(groupB_custom_buttons,    3, 0, 1, 1);
    layout_scroll_area->addWidget(groupB_custom_loading_bars,    3, 1, 1, 1);

    scrollA->setWidget(scrollA_contents);
    layout_->addWidget(scrollA);
    centralwidget->setLayout(layout_);
    this->setCentralWidget(centralwidget);

    QObject::connect(badgeButton, SIGNAL(clicked()), this, SLOT(clickedBadgeButton()));
    QObject::connect(connectionButton, SIGNAL(clicked()), this, SLOT(clickedConnectionButton()));
    QObject::connect(swipeWidget, SIGNAL(locked()), this, SLOT(lockedSwipedButton()));
    QObject::connect(swipeWidget, SIGNAL(unlocked()), this, SLOT(unlockedSwipedButton()));
    QObject::connect(fireButton, SIGNAL(fire()), this, SLOT(fireFireButton()));
    QObject::connect(panelButton, SIGNAL(clicked()), this, SLOT(clickedPanelButton()));
    QObject::connect(flatButton, SIGNAL(clicked()), this, SLOT(clickedFlatButton()));

    QObject::connect(toggleSwitchIOS, SIGNAL(toggled(bool)), this, SLOT(toggledSwitchIOS(bool)));
    QObject::connect(delayedToggleSwitchIOS, SIGNAL(toggled(bool)), this, SLOT(toggledDelayedSwitchIOS(bool)));
    QObject::connect(toggleSwitchAndroid, SIGNAL(toggled(bool)), this, SLOT(toggledSwitchAndroid(bool)));
    QObject::connect(delayedToggleSwitchAndroid, SIGNAL(toggled(bool)), this, SLOT(toggledDelayedSwitchAndroid(bool)));
    QObject::connect(toggleSwitch, SIGNAL(toggled(bool)), this, SLOT(toggledSwitch(bool)));
    QObject::connect(nextNavigationButton, SIGNAL(toggled(bool)), this, SLOT(toggledButton(bool)));

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeoutTimer()));
    timer->setParent(this);
    timer->setInterval(1000);
    timer->start();
}

void MainWindow::keyPressEvent(QKeyEvent *event_){
    if (event_->key() == Qt::Key_Shift)
        this->fireButton->startGlowAnimation();
    };

void MainWindow::keyReleaseEvent(QKeyEvent *event_){
    if (event_->key() == Qt::Key_Shift)
        this->fireButton->stopGlowAnimation();
    };

void MainWindow::clickedBadgeButton() noexcept{
    this->badgeButton->increaseNotifyNumber();
}

void MainWindow::clickedConnectionButton() noexcept{
    this->connectionButton->connectionAnimation();
}

void MainWindow::lockedSwipedButton() noexcept{
    qInfo("Locked!");
};

void MainWindow::unlockedSwipedButton() noexcept{
    qInfo("Unlocked!");
};

void MainWindow::fireFireButton() noexcept{
    qInfo("Fire!");
};

void MainWindow::clickedPanelButton() noexcept{
    qInfo("Clicked!");
};

void MainWindow::clickedFlatButton() noexcept{
    qInfo("Clicked!");
};

void MainWindow::toggledSwitchIOS(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString::number(toggled);
};

void MainWindow::toggledDelayedSwitchIOS(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString::number(toggled);
};

void MainWindow::toggledSwitchAndroid(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString::number(toggled);
};

void MainWindow::toggledDelayedSwitchAndroid(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString::number(toggled);
};

void MainWindow::toggledButton(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString::number(toggled);
};

void MainWindow::toggledSwitch(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString::number(toggled);
};

void MainWindow::timeoutTimer() noexcept{
    qint64 msec = QDateTime::currentMSecsSinceEpoch();
    dynamicTooltipLabel->setToolTip(QString::number(msec));
    customTextEdit->setToolTip(QString::number(msec));
    customLineEdit->setToolTip(QString::number(msec));
};

MainWindow::~MainWindow()
{
    delete ui;
}

