#include "customtoggles.h"

/**
 * @brief ToggleSwitch::ToggleSwitch
 * @param parent_
 */

ToggleSwitch::ToggleSwitch(QWidget *parent_)
{
    this->setParent(parent_);
    this->setCheckable(true);

    this->setFixedWidth(60);
    this->setFixedHeight(30);

    this->fore_color_ = QColorConstants::White;
    this->text_color_ = QColorConstants::Black;

    this->unchecked_color_ = QColor(185, 185, 185);
    this->checked_color_ = QColor(137, 218, 103);

    this->state_1_text_ = "ON";
    this->state_2_text_ = "OFF";

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedSlot_()));
}

void ToggleSwitch::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.setPen(Qt::NoPen);
    painter.translate(0,0);

    int border_thickness = 2;
    qreal width = this->width();
    qreal height = width*.5;

    qreal radius = qMax<int>(qMin<int>(width, height)/2.0 - border_thickness, 0);

    QColor button_color, slot_color, border_color;
    if (this->isEnabled()){
        if (this->isChecked()){
            button_color = this->fore_color_;
            slot_color = this->checked_color_;
            border_color = BLACK_COLOR;
        }
        else{
            button_color = this->fore_color_;
            slot_color = this->unchecked_color_;
            border_color = BLACK_COLOR;
        }
    }
    else{
        if (this->isChecked()){
            button_color = this->fore_color_.lightness();
            slot_color = this->checked_color_.lightness();
            border_color = BLACK_COLOR.lightness();
        }
        else{
            button_color = this->fore_color_.lightness();
            slot_color = this->unchecked_color_.lightness();
            border_color = BLACK_COLOR.lightness();
        }
    }

    // Draw border
    QPen pen;
    pen = QPen(border_color);
    pen.setWidth(border_thickness);
    painter.setPen(pen);

    // Draw slot
    QRect slot_rect;
    slot_rect.translate((int) (border_thickness), (int) (border_thickness));
    slot_rect.setSize(QSize((int) (width - border_thickness*2), (int) (height - border_thickness*2)));
    painter.setBrush(slot_color);
    painter.drawRoundedRect(slot_rect, (int) radius, (int) radius);

    // Draw Button
    QRect sw_rect;
    sw_rect.translate((int) border_thickness, (int) border_thickness);
    sw_rect.setSize(QSize((int) (radius*2), (int) (radius*2)));
    painter.setBrush(button_color);
    if (this->isChecked())
        sw_rect.moveLeft((int) (slot_rect.width() - radius*2) + border_thickness);
    painter.drawEllipse(sw_rect);

    // Draw Label
    QString label;
    label = this->isChecked()? this->state_1_text_: this->state_2_text_;
    QFont text_font("Verdana", 20, QFont::ExtraBold);
    text_font.setPixelSize((int) (sw_rect.height()*0.3));
    painter.setPen(slot_color);
    painter.setFont(text_font);
    painter.drawText(sw_rect, Qt::AlignCenter, label);
};

void ToggleSwitch::setTheme(const std::map<QString, QString> &style){
    QColor fore_color, text_color, checked_color, unchecked_color;

    fore_color.setNamedColor(style.at("foreground"));
    text_color.setNamedColor(style.at("text"));
    checked_color.setNamedColor(style.at("checked"));
    unchecked_color.setNamedColor(style.at("unchecked"));

    this->fore_color_ = fore_color;
    this->text_color_ = text_color;
    this->checked_color_ = checked_color;
    this->unchecked_color_ = unchecked_color;
    this->repaint();
};

QString ToggleSwitch::getState1Text_() const{
    return this->state_1_text_;
};

void ToggleSwitch::setState1Text_(const QString &text){
    this->state_1_text_ = text;
    this->repaint();
};

QString ToggleSwitch::getState2Text_() const{
    return this->state_2_text_;
};

void ToggleSwitch::setState2Text_(const QString &text){
    this->state_2_text_ = text;
    this->repaint();
};

void ToggleSwitch::setStates(const QString &state1, const QString &state2){
    setState1Text_(state1);
    setState2Text_(state2);
};

void ToggleSwitch::clickedSlot_(){
    emit this->toggled(this->isChecked());
}

/**
 * @brief ToggleSwitchAndroid::ToggleSwitchAndroid
 * @param parent_
 */

ToggleSwitchAndroid::ToggleSwitchAndroid(QWidget *parent_)
{
    this->setParent(parent_);

    this->installEventFilter(this);
    this->setCheckable(true);
    this->setFixedWidth(60);
    this->setFixedHeight(60);

    this->fore_color_ = QColor(200, 200, 200);  // Switch Color
    this->checked_color_ = QColor(67,144,133);
    this->unchecked_color_ = QColor(185,185,185);
}

bool ToggleSwitchAndroid::eventFilter(QObject *obj_, QEvent *event_){

    if (obj_ == this and this->isEnabled()){
        if (event_->type() == QEvent::MouseButtonPress){
            //this->is_mouse_pressed_ = true;
        }

        if (event_->type() == QEvent::MouseButtonRelease){
            //this->is_mouse_pressed_ = false;
            emit this->toggled(this->isChecked());
        }
    }
    return false;
};

void ToggleSwitchAndroid::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0,0);

    // Fixed ratios of toggle switch. Adapted from Android toggle button
    qreal slot_width = this->width();
    qreal slot_height = this->width() * 0.3717;
    qreal button_dia = this->width() * 0.5398;
    qreal travel = this->width() * 0.4779;
    painter.translate(0, (int) (button_dia/2.0 - slot_height/4.0));

    QColor slot_color, switch_color;
    if (this->isEnabled()){
        if (this->isChecked()){
            slot_color = this->checked_color_.lighter(150);
            switch_color = this->checked_color_;
        }
        else{
            slot_color = this->unchecked_color_;
            switch_color = this->fore_color_;
        }
    }
    else{
        if (this->isChecked()){
            slot_color = this->checked_color_.lighter(250);
            switch_color = this->fore_color_.lighter(200);
        }
        else{
            slot_color = this->unchecked_color_.lighter(250);
            switch_color = this->fore_color_.lighter(200);
        }
    }

    // Draw Slot
    QRect slot_rect;
    slot_rect.translate(0, (int) (button_dia/4));
    slot_rect.setSize(QSize((int) slot_width, (int) slot_height));
    painter.setBrush(slot_color);
    painter.drawRoundedRect(slot_rect, (int) (slot_height/2), (int) (slot_height/2));

    // Draw Switch
    QRect sw_rect;
    sw_rect.translate(0, (int) (button_dia/8));
    sw_rect.setSize(QSize((int) button_dia, (int) button_dia));

    painter.setBrush(switch_color);
    if (this->isChecked())
        sw_rect.moveLeft(travel);
    painter.drawEllipse(sw_rect);
};

void ToggleSwitchAndroid::setTheme(const std::map<QString, QString> &style){
    QColor foreground, checked_color, unchecked_color;

    foreground.setNamedColor(style.at("foreground"));
    checked_color.setNamedColor(style.at("checked"));
    unchecked_color.setNamedColor(style.at("unchecked"));

    this->fore_color_ = foreground;
    this->checked_color_ = checked_color;
    this->unchecked_color_ = unchecked_color;
    this->repaint();
};

/**
 * @brief DelayedToggleSwitchAndroid::DelayedToggleSwitchAndroid
 * @param parent_
 */

DelayedToggleSwitchAndroid::DelayedToggleSwitchAndroid(QWidget *parent_){
    this->setParent(parent_);

    this->installEventFilter(this);
    this->setCheckable(true);
    this->setFixedWidth(60);
    this->setFixedHeight(60);

    this->fore_color_ = QColor(200, 200, 200);  // Switch Color
    this->checked_color_ = QColor(67,144,133);
    this->unchecked_color_ = QColor(185,185,185);

    this->wait_anim_ = new QPropertyAnimation{this, "progress", this};
};

bool DelayedToggleSwitchAndroid::eventFilter(QObject *obj_, QEvent *event_){

    if (obj_ == this and this->isEnabled()){
        if (event_->type() == QEvent::MouseButtonPress){
            this->startAnimation_();
            this->is_mouse_pressed_ = true;
        }

        if (event_->type() == QEvent::MouseButtonRelease){
            this->stopAnimation_();
            this->is_mouse_pressed_ = false;

            if (this->progress_ == 100)
                emit this->toggled(true);

            if (this->progress_ == 0)
                emit this->toggled(false);

            if (this->progress_ < 100)
                this->progress_ = 0;

            if (this->progress_ > 0)
                this->progress_ = 100;
        }
    }
    return false;
};

void DelayedToggleSwitchAndroid::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0,0);

    // Fixed ratios of toggle switch. Adapted from Android toggle button
    qreal size = qMin<qreal>(this->width(), this->height());
    qreal slot_width = size;
    qreal slot_height = size * 0.3717;
    qreal button_dia = size * 0.5398;
    qreal travel = size * 0.4779;
    painter.translate(0, (int) (button_dia/2.0 - slot_height/4.0));

    if (this->progress_ == 100){
        this->setChecked_(true);
    }
    else if (this->progress_ == 0){
        this->setChecked_(false);
    }

    QColor switch_color;
    if (this->isEnabled()){
        if (this->isChecked()){
            switch_color = this->checked_color_;
        }
        else{
            switch_color = this->fore_color_;
        }
    }
    else{
        if (this->isChecked()){
            switch_color = this->checked_color_.lighter(200);
        }
        else{
            switch_color = this->fore_color_.lighter(200);
        }
    }

    // Draw Slot
    QRect slot_rect;
    slot_rect.translate(0, (int) (button_dia/4));
    slot_rect.setSize(QSize((int) slot_width, (int) slot_height));
    painter.setBrush(this->unchecked_color_);
    painter.drawRoundedRect(slot_rect, (int) slot_height/2, (int) slot_height/2);

    // Draw Animation
    QLinearGradient checked_gradient;
    if (!this->is_checked_){
        checked_gradient = QLinearGradient (QPointF(0, (int) slot_height/2), QPointF(slot_width, (int) slot_height/2));
        checked_gradient.setColorAt(0, this->checked_color_.lighter(150));
        checked_gradient.setColorAt(qMax<qreal>(qMin<qreal>((this->progress_/100)-0.001, 1), 0), this->checked_color_.lighter(150));  // Create Sharp edge over color transition
        checked_gradient.setColorAt(qMax<qreal>(qMin<qreal>((this->progress_/100), 1), 0), QColorConstants::Transparent);
    }
    else{
        checked_gradient = QLinearGradient(QPointF(0, (int) slot_height/2), QPointF(slot_width, (int) slot_height/2));
        checked_gradient.setColorAt(0, this->checked_color_.lighter(150));
        checked_gradient.setColorAt(qMax<qreal>(qMin<qreal>((this->progress_/100)-0.001, 1), 0), this->checked_color_.lighter(150));  // Create Sharp edge over color transition
        checked_gradient.setColorAt(qMax<qreal>(qMin<qreal>((this->progress_/100), 1), 0), QColorConstants::Transparent);
    }

    painter.setBrush(checked_gradient);
    painter.drawRoundedRect(slot_rect, (int) slot_height/2, (int) slot_width/2);

    // Draw Switch
    QRect sw_rect;
    sw_rect.translate(0, button_dia/8);
    sw_rect.setSize(QSize((int) (button_dia), (int) (button_dia)));

    if (this->is_checked_){
        painter.setBrush(switch_color);
        sw_rect.moveLeft(travel);
        this->progress_ = 100;
    }
    else{
        painter.setBrush(this->fore_color_);
    }
    painter.drawEllipse(sw_rect);
};

qreal DelayedToggleSwitchAndroid::getProgress_() const{
    return this->progress_;
};

void DelayedToggleSwitchAndroid::setProgress_(qreal value){
    this->progress_ = value;
    this->repaint();
};

bool DelayedToggleSwitchAndroid::setChecked_(bool value){
    this->is_checked_ = value;
    this-> progress_ = (this->is_checked_)? 100: 0;
};

void DelayedToggleSwitchAndroid::setTheme(const std::map<QString, QString> &style){
    QColor fore_color, checked_color, unchecked_color;

    checked_color.setNamedColor(style.at("checked"));
    unchecked_color.setNamedColor(style.at("unchecked"));
    fore_color.setNamedColor(style.at("fore_color"));

    this->fore_color_ = fore_color;
    this->checked_color_ = checked_color;
    this->unchecked_color_ = unchecked_color;
    this->repaint();
};

bool DelayedToggleSwitchAndroid::isChecked() const{
    return this->is_checked_;
};

bool DelayedToggleSwitchAndroid::setChecked(bool value){
    setChecked_(value);
    this->repaint();
};

void DelayedToggleSwitchAndroid::startAnimation_(){
    if (this->wait_anim_->state() == QPropertyAnimation::Running) return;

    this->wait_anim_->setDuration(1000);  // Miliseconds, default: 1000ms
    this->wait_anim_->setLoopCount(1); // loop count of the animation, default: 1 (runs onlt once)

    if (! this->is_checked_){
        this->wait_anim_->setStartValue(0);
        this->wait_anim_->setEndValue(100);
    }
    else{
        this->wait_anim_->setStartValue(100);
        this->wait_anim_->setEndValue(0);
    }
    this->wait_anim_->start();
};

void DelayedToggleSwitchAndroid::stopAnimation_(){
    if (this->wait_anim_->state() == QPropertyAnimation::Running ||
        this->wait_anim_->state() == QPropertyAnimation::Paused){
        this->wait_anim_->stop();
    }
};

void DelayedToggleSwitchAndroid::resumeAnimation_(){
    if (this->wait_anim_->state() == QPropertyAnimation::Paused){
        this->wait_anim_->resume();
    }
};

void DelayedToggleSwitchAndroid::pauseAnimation_(){
    if (this->wait_anim_->state() == QPropertyAnimation::Running){
        this->wait_anim_->pause();
    }
};

/**
 * @brief ToggleSwitchIOS::ToggleSwitchIOS
 * @param parent_
 */

ToggleSwitchIOS::ToggleSwitchIOS(QWidget *parent_)
{
    this->setParent(parent_);

    this->installEventFilter(this);
    this->setCheckable(true);
    this->setFixedWidth(100);
    this->setFixedHeight(30);
    this->fore_color_ = QColorConstants::White;  // Switch Color
    this->checked_color_ = GREEN_COLOR;
    this->unchecked_color_ = GRAY_COLOR;
}

bool ToggleSwitchIOS::eventFilter(QObject *obj_, QEvent *event_){

    if (obj_ == this and this->isEnabled()){
        if (event_->type() == QEvent::MouseButtonPress){
            //this->is_mouse_pressed_ = true;
        }

        if (event_->type() == QEvent::MouseButtonRelease){
            //this->is_mouse_pressed_ = false;
            emit this->toggled(this->isChecked());
        }
    }
    return false;
};

void ToggleSwitchIOS::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0,0);

    // Fixed ratios of toggle switch. Adapted from iOS toggle button
    qreal height = this->height();
    qreal radius = height * 0.86 * 0.5;
    qreal width = height * 1.62;
    qreal travel = height * 0.69;
    qreal offset = height * 0.069;

    QColor slot_color, switch_color;
    if (this->isEnabled()){
        if (this->isChecked()){
            slot_color = this->checked_color_;
            switch_color = this->fore_color_;
        }
        else{
            slot_color = this->unchecked_color_;
            switch_color =this->fore_color_;
        }
    }
    else{
        if (this->isChecked()){
            slot_color = this->checked_color_.lighter(150);
            switch_color = this->fore_color_.lighter(150);
        }
        else{
            slot_color = this->unchecked_color_.lighter(150);
            switch_color = this->fore_color_.lighter(150);
        }
    }

    // Draw Slot
    QRect slot_rect;
    slot_rect.setSize(QSize((int) width, (int) height));
    painter.setBrush(slot_color);
    painter.drawRoundedRect(slot_rect, (int) (height/2), (int) (height/2));

    // Draw Switch
    QRect sw_rect;
    sw_rect.translate(0, 0);
    sw_rect.translate(offset, offset);
    sw_rect.setSize(QSize((int) (radius*2), (int) (radius*2)));

    painter.setBrush(switch_color);
    if (this->isChecked())
        sw_rect.moveLeft(travel);
    painter.drawEllipse(sw_rect);
};

void ToggleSwitchIOS::setTheme(const std::map<QString, QString> &style){
    QColor fore_color, checked_color, unchecked_color;

    checked_color.setNamedColor(style.at("checked"));
    unchecked_color.setNamedColor(style.at("unchecked"));
    fore_color.setNamedColor(style.at("fore_color"));

    this->fore_color_ = fore_color;
    this->checked_color_ = checked_color;
    this->unchecked_color_ = unchecked_color;
    this->repaint();
};

/**
 * @brief DelayedToggleSwitchIOS::DelayedToggleSwitchIOS
 * @param parent_
 */

DelayedToggleSwitchIOS::DelayedToggleSwitchIOS(QWidget *parent_){
    this->setParent(parent_);

    this->installEventFilter(this);
    this->setCheckable(true);
    this->setFixedWidth(100);
    this->setFixedHeight(30);
    this->fore_color_ = QColorConstants::White;  // Switch Color
    this->checked_color_ = GREEN_COLOR;
    this->unchecked_color_ = GRAY_COLOR;

    this->wait_anim_ = new QPropertyAnimation{this, "progress", this};
};

bool DelayedToggleSwitchIOS::eventFilter(QObject *obj_, QEvent *event_){

    if (obj_ == this and this->isEnabled()){
        if (event_->type() == QEvent::MouseButtonPress){
            this->startAnimation_();
            this->is_mouse_pressed_ = true;
        }

        if (event_->type() == QEvent::MouseButtonRelease){
            this->stopAnimation_();
            this->is_mouse_pressed_ = false;

            if (this->progress_ == 100)
                emit this->toggled(true);

            if (this->progress_ == 0)
                emit this->toggled(false);

            if (this->progress_ < 100)
                this->progress_ = 0;

            if (this->progress_ > 0)
                this->progress_ = 100;
        }
    }
    return false;
};

void DelayedToggleSwitchIOS::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0,0);

    // Fixed ratios of toggle switch. Adapted from iOS toggle button
    qreal height = this->height();
    qreal radius = height * 0.86 * 0.5;
    qreal width = height * 1.62;
    qreal travel = height * 0.69;
    qreal offset = height * 0.069;

    if (this->progress_ == 100){
        this->setChecked_(true);
    }
    else if (this->progress_ == 0){
        this->setChecked_(false);
    }

    QColor slot_color, switch_color;
    if (this->isEnabled()){
        slot_color = this->unchecked_color_;
        switch_color = this->fore_color_;
    }
    else{
        slot_color = this->unchecked_color_.lighter(250);
        switch_color = this->fore_color_.lighter(200);
    }

    // Draw Slot
    QRect slot_rect;
    slot_rect.setSize(QSize((int) width, (int) height));
    painter.setBrush(slot_color);
    painter.drawRoundedRect(slot_rect, (int) (height/2), (int) (height/2));

    // Draw Animation
    QLinearGradient checked_gradient;
    if (!this->is_checked_){
        checked_gradient = QLinearGradient (QPointF(0, (int) (height/2)), QPointF(width, (int) (height/2)));
        checked_gradient.setColorAt(0, this->checked_color_);
        checked_gradient.setColorAt(qMax<qreal>(qMin<qreal>((this->progress_/100)-0.001, 1), 0), this->checked_color_);  // Create Sharp edge over color transition
        checked_gradient.setColorAt(qMax<qreal>(qMin<qreal>((this->progress_/100), 1), 0), QColorConstants::Transparent);
    }
    else{
        checked_gradient = QLinearGradient(QPointF(0,(int) (height/2)), QPointF(width, (int) (height/2)));
        checked_gradient.setColorAt(0, this->checked_color_);
        checked_gradient.setColorAt(qMax<qreal>(qMin<qreal>((this->progress_/100)-0.001, 1), 0), this->checked_color_);  // Create Sharp edge over color transition
        checked_gradient.setColorAt(qMax<qreal>(qMin<qreal>((this->progress_/100), 1), 0), QColorConstants::Transparent);
    }

    painter.setBrush(checked_gradient);
    painter.drawRoundedRect(slot_rect, (int) (height/2), (int) (height/2));

    // Draw Switch
    QRect sw_rect;
    sw_rect.translate(0, 0);
    sw_rect.translate(offset, offset);
    sw_rect.setSize(QSize((int) (radius*2), (int) (radius*2)));

    painter.setBrush(switch_color);
    if (this->is_checked_){
        sw_rect.moveLeft(travel);
        this->progress_ = 100;
    }
    painter.drawEllipse(sw_rect);
};

qreal DelayedToggleSwitchIOS::getProgress_() const{
    return this->progress_;
};

void DelayedToggleSwitchIOS::setProgress_(qreal value){
    this->progress_ = value;
    this->repaint();
};

bool DelayedToggleSwitchIOS::setChecked_(bool value){
    this->is_checked_ = value;
    this-> progress_ = (this->is_checked_)? 100: 0;
};

void DelayedToggleSwitchIOS::setTheme(const std::map<QString, QString> &style){
    QColor fore_color, checked_color, unchecked_color;

    checked_color.setNamedColor(style.at("checked"));
    unchecked_color.setNamedColor(style.at("unchecked"));
    fore_color.setNamedColor(style.at("fore_color"));

    this->fore_color_ = fore_color;
    this->checked_color_ = checked_color;
    this->unchecked_color_ = unchecked_color;
    this->repaint();
};

bool DelayedToggleSwitchIOS::isChecked() const{
    return this->is_checked_;
};

bool DelayedToggleSwitchIOS::setChecked(bool value){
    setChecked_(value);
    this->repaint();
};

void DelayedToggleSwitchIOS::startAnimation_(){
    if (this->wait_anim_->state() == QPropertyAnimation::Running) return;

    this->wait_anim_->setDuration(1000);  // Miliseconds, default: 1000ms
    this->wait_anim_->setLoopCount(1); // loop count of the animation, default: 1 (runs onlt once)

    if (! this->is_checked_){
        this->wait_anim_->setStartValue(0);
        this->wait_anim_->setEndValue(100);
    }
    else{
        this->wait_anim_->setStartValue(100);
        this->wait_anim_->setEndValue(0);
    }
    this->wait_anim_->start();
};

void DelayedToggleSwitchIOS::stopAnimation_(){
    if (this->wait_anim_->state() == QPropertyAnimation::Running ||
        this->wait_anim_->state() == QPropertyAnimation::Paused){
        this->wait_anim_->stop();
    }
};

void DelayedToggleSwitchIOS::resumeAnimation_(){
    if (this->wait_anim_->state() == QPropertyAnimation::Paused){
        this->wait_anim_->resume();
    }
};

void DelayedToggleSwitchIOS::pauseAnimation_(){
    if (this->wait_anim_->state() == QPropertyAnimation::Running){
        this->wait_anim_->pause();
    }
};
