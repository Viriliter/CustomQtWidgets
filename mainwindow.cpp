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

    swipeWidget->setFixedSize(QSize(200,50));
    layout_custom_widgets->addWidget(swipeWidget);

    groupB_custom_widgets->setLayout(layout_custom_widgets);

    /*
     * Custom Text Edits
     */
    QGroupBox *groupB_custom_text_edits = new QGroupBox(scrollA_contents);
    groupB_custom_text_edits->setTitle("Custom Text Edits");
    groupB_custom_text_edits->setObjectName(QString::fromUtf8("groupB_custom_text_edits"));
    QGridLayout *layout_custom_text = new QGridLayout{};

    customTextEdit->setText("This is CustomTextEdit");
    customTextEdit->setToolTip("Dynamic update");
    customLineEdit->setText("This is CustomLineEdit");
    customLineEdit->setToolTip("Dynamic update");
    borderedTextEdit->setText("This is BorderedTextEdit");
    borderedTextLineEdit->setText("This is BorderedTextLineEdit");

    //layout_custom_text->addWidget(borderedTextEdit);
    //layout_custom_text->addWidget(borderedTextLineEdit);
    //layout_custom_text->addWidget(customTextEdit);
    //layout_custom_text->addWidget(customLineEdit);

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

    layout_custom_toggles->addWidget(toggleSwitchIOS);
    layout_custom_toggles->addWidget(delayedToggleSwitchIOS);
    layout_custom_toggles->addWidget(toggleSwitchAndroid);
    layout_custom_toggles->addWidget(delayedToggleSwitchAndroid);
    layout_custom_toggles->addWidget(toggleSwitch);

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

    layout_custom_indicators->addWidget(classicLedIndicator);
    layout_custom_indicators->addWidget(realisticLedIndicator);

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

    layout_custom_labels->addWidget(highlightLabel);
    layout_custom_labels->addWidget(dynamicTooltipLabel);

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

    layout_custom_buttons->addWidget(activationButton);
    layout_custom_buttons->addWidget(badgeButton);  // Bug in bg color after mouse click release
    layout_custom_buttons->addWidget(connectionButton);
    layout_custom_buttons->addWidget(fireButton);
    layout_custom_buttons->addWidget(panelButton);
    layout_custom_buttons->addWidget(flatButton);
    layout_custom_buttons->addWidget(toggleButton);

    groupB_custom_buttons->setLayout(layout_custom_buttons);

    /*
     * Custom Loading Bars
     */
    QGroupBox *groupB_custom_loading_bars = new QGroupBox(scrollA_contents);
    groupB_custom_loading_bars->setTitle("Custom LoadingBars");
    groupB_custom_loading_bars->setObjectName(QString::fromUtf8("groupB_custom_loading_bars"));
    QGridLayout *layout_custom_loading_bars = new QGridLayout{};

    layout_custom_loading_bars->addWidget(progressBar);
    layout_custom_loading_bars->addWidget(circularProgressBar);

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
    QObject::connect(toggleButton, SIGNAL(toggled(bool)), this, SLOT(toggledButton(bool)));

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
    qInfo() << "Toggle Status: " + QString(toggled);
};

void MainWindow::toggledDelayedSwitchIOS(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString(toggled);
};

void MainWindow::toggledSwitchAndroid(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString(toggled);
};

void MainWindow::toggledDelayedSwitchAndroid(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString(toggled);
};

void MainWindow::toggledButton(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString(toggled);
};

void MainWindow::toggledSwitch(bool toggled) noexcept{
    qInfo() << "Toggled!";
    qInfo() << "Toggle Status: " + QString(toggled);
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

