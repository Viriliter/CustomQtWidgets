#include "swipewidget.h"

SwipeWidget::SwipeWidget(QWidget *parent_)
{
    this->setParent(parent_);

    this->setMouseTracking(true);
    this->installEventFilter(this);

    this->base_fore_color_ = WHITE_COLOR;
    this->base_bg_color_ = QColor(5, 5, 5);
    this->swipe_fore_color_ = QColor(124, 124, 124);
    this->swipe_bg_color_ = QColor(166, 166, 166);
    this->border_color_ = BLACK_COLOR;

    last_pos_ = this->pos();
    text_anim_ = new QPropertyAnimation{this, "glarePos", this};
    this->startTextAnimation();
}

void SwipeWidget::mouseMoveEvent(QMouseEvent *event_){
    if (this->is_mouse_pressed_){
        if (event_->localPos().x() > 0){
            if (event_->localPos().x() <= this->width() - this->swipe_width_){
                qreal travel_x_ = event_->localPos().x();
                this->travel_value_ = qRound((travel_x_/(this->width() - this->swipe_width_))* 10.0) / 10.0;
                this->setValue_(this->travel_value_);
                this->repaint();
            }
        }
    }
};

bool SwipeWidget::eventFilter(QObject *obj_, QEvent *event_){
    if (obj_ != this) return false;

    if (event_->type() == QEvent::MouseButtonPress){
        this->pauseTextAnimation();
        this->is_mouse_pressed_ = true;
    }

    else if (event_->type() == QEvent::MouseButtonRelease){
        this->resumeTextAnimation();
        this->is_mouse_pressed_ = false;
        if (this->value_ < 0.5){
            this->travel_value_ = 0;
            this->setValue_(0);
            if (this->last_value_ != 0){
                this->startTextAnimation();
                emit this->locked();
            }
            this->last_value_ = 0;
            this->update();
        }
        else{
            this->travel_value_ = 1;
            this->setValue_(1);
            if (this->last_value_ != 1){
                this->stopTextAnimation();
                emit this->unlocked();
            }
            this->last_value_ = 1;
            this->update();
        }
    }
    return false;
};

void SwipeWidget::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    // Sizes
    qreal width = this->width();
    qreal height = width * 0.2;
    qreal base_radius = width * 0.04;

    qreal swipe_offset = 0;  // width*0.0011;
    this->swipe_width_ = width*0.243 - swipe_offset;
    qreal swipe_height = height - swipe_offset;
    qreal swipe_radius = width*0.04;

    qreal text_width = width + width*0.243;
    qreal text_height = height;

    qreal arrow_width = this->swipe_width_*0.64;  // self._swipe_width*0.8;
    qreal arrow_height = arrow_width*0.586;  // arrow_width*0.732;
    qreal arrow_width_offset = (this->swipe_width_-arrow_width)/2.0;
    qreal arrow_height_offset = (swipe_height-arrow_height)/2.0;

    // Draw base rectangular
    QLinearGradient bg_lin_color{};
    bg_lin_color.setStart(0, 0);
    bg_lin_color.setFinalStop(0, height);

    bg_lin_color.setColorAt(0, this->base_bg_color_);
    bg_lin_color.setColorAt(1, QColor(100, 100, 100));
    painter.setBrush(bg_lin_color);

    QRect base_rect(0, 0, (int) width, (int) height);
    painter.drawRoundedRect(base_rect, (int) base_radius, (int) base_radius);

    // Draw Text
    QRect text_rect(0, 0, (int) text_width, (int) text_height);

    QLinearGradient text_lin_color{};
    text_lin_color.setStart(0, 0);
    text_lin_color.setStart(0, 0);

    if (this->isEnabled()){
        text_lin_color.setFinalStop(text_rect.width(), 0);
        text_lin_color.setColorAt(0, QColor(150, 150, 150));
        text_lin_color.setColorAt(qMax<qreal>(qMin<qreal>(this->glare_pos_/text_rect.width()*0.8, 1), 0), QColor(150, 150, 150));
        text_lin_color.setColorAt(qMax<qreal>(qMin<qreal>(this->glare_pos_/text_rect.width(), 1), 0), QColor(255, 255, 255));
        text_lin_color.setColorAt(qMax<qreal>(qMin<qreal>(this->glare_pos_/text_rect.width()*1.2, 1), 0), QColor(150, 150, 150));
        text_lin_color.setColorAt(1, QColor(150, 150, 150));

        QFont text_font(QFont("Verdana", 10, QFont::Normal));
        text_font.setPixelSize((int) (height*0.4));
        painter.setPen(QPen(text_lin_color, 2, Qt::PenStyle::SolidLine));
        painter.setFont(text_font);
        painter.drawText(text_rect, Qt::AlignCenter, this->base_text_);
    }

    // Draw Text Mask
    painter.setPen(Qt::NoPen);

    QLinearGradient text_bg_lin_color{};
    text_bg_lin_color.setStart(0, 0);
    text_bg_lin_color.setFinalStop(0, height);

    text_bg_lin_color.setColorAt(0, this->base_bg_color_);
    text_bg_lin_color.setColorAt(1, QColor(100, 100, 100));
    painter.setBrush(text_bg_lin_color);

    qreal travel_x = this->travel_value_ * (this->width() - this->swipe_width_);
    QRect mask_rect((int) base_radius, 0, (int) travel_x, (int) height);
    painter.drawRect(mask_rect);

    // Draw Swipe Button
    QLinearGradient swipe_bg_lin_color;
    swipe_bg_lin_color.setStart(0, 0);
    swipe_bg_lin_color.setFinalStop(0, swipe_height);

    swipe_bg_lin_color.setColorAt(1, this->swipe_bg_color_);
    swipe_bg_lin_color.setColorAt(0, this->swipe_bg_color_.lighter(200));

    painter.setBrush(swipe_bg_lin_color);

    QRect swipe_rect((int) (travel_x + swipe_offset), (int) swipe_offset,
                     (int) this->swipe_width_, (int) swipe_height);
    painter.drawRoundedRect(swipe_rect, (int) swipe_radius, (int) swipe_radius);

    // Draw Arrow
    painter.setPen(QPen(this->border_color_, 1, Qt::SolidLine));

    QLinearGradient arrow_bg_lin_color;
    arrow_bg_lin_color.setStart(0, 0);
    arrow_bg_lin_color.setFinalStop(0, arrow_height);

    arrow_bg_lin_color.setColorAt(1, this->swipe_fore_color_);
    arrow_bg_lin_color.setColorAt(0, this->swipe_fore_color_.lighter(200));

    painter.setBrush(arrow_bg_lin_color);

    QPoint point_0(0, (int) (arrow_height*0.27));
    QPoint point_1((int) (arrow_width*0.51), (int) (arrow_height*0.27));
    QPoint point_2((int) (arrow_width*0.51), 0);
    QPoint point_3((int) (arrow_width), (int) (arrow_height*0.5));
    QPoint point_4((int) (arrow_width*0.51), (int) (arrow_height));
    QPoint point_5((int) (arrow_width*0.51), (int) (arrow_height*0.73));
    QPoint point_6(0, (int)(arrow_height*0.73));
    QPainterPath arrow_path(point_0);
    arrow_path.lineTo(point_1);
    arrow_path.lineTo(point_2);
    arrow_path.lineTo(point_3);
    arrow_path.lineTo(point_4);
    arrow_path.lineTo(point_5);
    arrow_path.lineTo(point_6);
    arrow_path.lineTo(point_0);
    arrow_path.translate(travel_x+arrow_width_offset, arrow_height_offset);
    painter.drawPath(arrow_path);
};

void SwipeWidget::resizeEvent(QResizeEvent *event_){
    this->repaint();
    this->stopTextAnimation();
    this->startTextAnimation();
};

void SwipeWidget::setBaseText_(const QString &base_text){
    this->base_text_ = base_text;
};

qreal SwipeWidget::getValue_() const{
    return this->value_;
};

void SwipeWidget::setValue_(qreal value){
    this->value_ = value;
};

qreal SwipeWidget::getGlarePos_() const{
    return this->glare_pos_;
};

void SwipeWidget::setGlarePos_(qreal glare_pos){
    this->glare_pos_ = glare_pos;
    this->repaint();
};

QString SwipeWidget::getBaseText_() const{
    return this->base_text_;
};

void SwipeWidget::setBaseText_(QString &base_text){
    this->base_text_ = base_text;
    this->repaint();
};

void SwipeWidget::startTextAnimation(){
    //if (this->text_anim_->state() == QAbstractAnimation::Running) return;
    if (this->text_anim_->state() == QPropertyAnimation::Running) return;


    this->text_anim_->setDuration(1500);  // Miliseconds, default: 250ms
    this->text_anim_->setLoopCount(-1);  // loop count of the animation, default: -1 (runs continously)

    this->text_anim_->setStartValue(0);
    this->text_anim_->setEndValue(this->width());
    this->text_anim_->start();
};

void SwipeWidget::pauseTextAnimation(){
    if (this->text_anim_->state() == QPropertyAnimation::Running) this->text_anim_->pause();
};

void SwipeWidget::resumeTextAnimation(){
    if (this->text_anim_->state() == QPropertyAnimation::Paused) this->text_anim_->resume();
};

void SwipeWidget::stopTextAnimation(){
    if (this->text_anim_->state() == QPropertyAnimation::Running ||
        this->text_anim_->state() == QPropertyAnimation::Paused){
        this->glare_pos_ = 0;
        this->text_anim_->stop();
    }
};

void SwipeWidget::setTheme(const std::map<QString, QString> &style){
    QColor foreground, base_foreground, background, base_background;

    base_background.setNamedColor(style.at("baseBackground"));
    base_foreground.setNamedColor(style.at("baseForeground"));
    background.setNamedColor(style.at("background"));
    foreground.setNamedColor(style.at("foreground"));

    this->base_bg_color_ = base_background;
    this->base_fore_color_ = base_foreground;
    this->swipe_bg_color_ = background;
    this->swipe_fore_color_ = foreground;
    this->border_color_ = foreground;

    this->repaint();
};

void SwipeWidget::lock(){
    this->travel_value_ = 0;
    this->last_value_ = 0;
    this->value_ = 0;
    emit this->locked();
    this->startTextAnimation();
};

void SwipeWidget::unlock(){
    this->travel_value_ = 1;
    this->last_value_ = 1;
    this->value_ = 1;
    emit this->unlocked();
    this->stopTextAnimation();
};
