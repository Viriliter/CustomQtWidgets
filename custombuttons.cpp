#include "custombuttons.h"

/**
 * @brief ActivationButton::ActivationButton
 * @param parent_
 */

ActivationButton::ActivationButton(QWidget *parent_)
{
    this->setParent(parent_);

    this->setMouseTracking(true);
    this->installEventFilter(this);

    this->setCheckable(true);
    this->setFixedHeight(80);
    this->setFixedWidth(80);

    this->fore_color_ = WHITE_COLOR;
    this->bg_color_ = QColor(26,27,20,255);
    this->glow_color_ = GREEN_COLOR;

    this->shadow_ = new QGraphicsDropShadowEffect{this};
    this->shadow_->setColor(QColor(0,0,0,77));
    this->shadow_->setXOffset(1);
    this->shadow_->setYOffset(1);
    this->shadow_->setBlurRadius(this->width()*1.2);
    this->setGraphicsEffect(this->shadow_);

    glow_anim_ = new QPropertyAnimation{this, "glowSize", this};
}

bool ActivationButton::eventFilter(QObject *obj_, QEvent *event_){
    if(obj_ == this && event_->type() == QEvent::MouseButtonPress)
        this->glowAnimation();
    if(obj_ == this && event_->type() == QEvent::MouseButtonRelease)
        this->glow_anim_->stop();

    return false;
}

void ActivationButton::enterEvent(QEvent *event_){
    this->shadow_->setXOffset(0);
    this->shadow_->setYOffset(0);
    this->setStyleSheet("background-color:#45b545;");
};

void ActivationButton::leaveEvent(QEvent *event_){
    this->shadow_->setXOffset(0);
    this->shadow_->setYOffset(0);
    this->setStyleSheet("background-color:yellow;");
};

void ActivationButton::paintEvent(QPaintEvent *event_){
    QString label;
    label = this->isChecked()? "ON": "OFF";

    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(0,0);

    qreal size = (this->width()>this->height())? this->height(): this->width();
    qreal radius = size * 0.8;

    QRect full_rect;
    full_rect.setSize(QSize(size, size));

    //Draw Glow
    QRect glow_rect;
    glow_rect.setSize(QSize(size, size));
    glow_rect.translate(0, 0);
    QRadialGradient glow_grad{full_rect.center(), size/2};

    QColor faint{this->glow_color_};
    faint.setAlphaF(.5);

    QColor faintest{this->glow_color_};
    faintest.setAlphaF(0);

    glow_grad.setStops(QGradientStops{QGradientStop{0, faint},
                                      QGradientStop{1, faintest}});

    QColor text_color;
    if (this->isChecked()){
        painter.setBrush(this->glow_color_);
        text_color = this->glow_color_;
    }
    else{
        painter.setBrush(this->glow_color_.lighter(150));
        text_color = this->glow_color_.lighter(150);
    }
    painter.drawEllipse(glow_rect);

    //Draw Background
    QRect rect;
    rect.setSize(QSize(radius, radius));
    rect.translate((int) (size/2.0 - radius*0.5), (int) (size/2.0 - radius*0.5));
    painter.setBrush(QBrush(bg_color_));
    painter.drawEllipse(rect);

    //Draw icon
    QRect icon_rect;
    icon_rect.setSize(QSize(size, size));
    icon_rect.translate(0, 0);
    painter.setPen(text_color);
    painter.drawText(icon_rect, Qt::AlignCenter, label);
};

void ActivationButton::glowAnimation(){
    if (this->glow_anim_->state() == QPropertyAnimation::Running) return;

    this->glow_anim_->setDuration(1000);  // miliseconds, default:1000ms
    this->glow_anim_->setLoopCount(1);  // loop count of the animation, default:1 (run only once)

    this->glow_anim_->setStartValue(0);
    this->glow_anim_->setEndValue(this->width());
    this->glow_anim_->start();
};

int ActivationButton::getGlowSize_() const{
    return this->glow_size_;
};

void ActivationButton::setGlowSize_(int glow_size){
    this->glow_size_ = glow_size;
};

/**
 * @brief ConnectionButton::ConnectionButton
 * @param parent_
 */

ConnectionButton::ConnectionButton(QWidget *parent_)
{
    this->setParent(parent_);

    this->setMouseTracking(true);
    this->installEventFilter(this);

    this->setCheckable(true);

    this->fore_color_1_ = WHITE_COLOR;
    this->fore_color_2_ = GREEN_COLOR;
    this->bg_color_ = QColor{26,27,20,255};
    this->bg_default_color_ = this->bg_color_;

    connection_anim_ = new QPropertyAnimation{this, "swapColorFlag", this};
}

bool ConnectionButton::eventFilter(QObject *obj_, QEvent *event_){
    return false;
};

void ConnectionButton::enterEvent(QEvent *event_){
    this->bg_color_ = this->bg_color_.lighter(150);
};

void ConnectionButton::leaveEvent(QEvent *event_){
    this->bg_color_ = this->bg_default_color_;
};

void ConnectionButton::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0,0);

    qreal size = (this->width()>this->height())? this->height(): this->width();
    int radius = (int) (size*0.1);

    QRect full_rect{};
    full_rect.setSize(QSize(this->width(), this->height()));

    // Draw Background
    QRect rect{};
    rect.setSize(QSize((int) size, (int) size));
    painter.setBrush(QBrush(this->bg_color_));
    painter.drawRoundedRect(rect, radius, radius);

    //Draw Icon Rect
    QRect icon_rect{};
    int icon_width = size*0.8;
    int icon_height = icon_width;
    icon_rect.setSize(QSize(icon_width, icon_height));
    painter.translate((size-icon_width)/2, (size-icon_height)/2);

    //Draw Arrow 1
    QPainterPath upper_icon_path;
    upper_icon_path.moveTo(icon_rect.left(), icon_rect.top() + icon_rect.height()/6);
    upper_icon_path.lineTo(icon_rect.left() + icon_rect.width()*(2/3), icon_rect.top() + icon_rect.height()/6);
    upper_icon_path.lineTo(icon_rect.left() + icon_rect.width()*(2/3), icon_rect.top());
    upper_icon_path.lineTo(icon_rect.right(), icon_rect.top() + icon_rect.height()/4);
    upper_icon_path.lineTo(icon_rect.left() + icon_rect.width()*(2/3), icon_rect.top() + icon_rect.height()/2);
    upper_icon_path.lineTo(icon_rect.left() + icon_rect.width()*(2/3), icon_rect.top() + icon_rect.height()/3);
    upper_icon_path.lineTo(icon_rect.left(), icon_rect.top() + icon_rect.height()/6);

    if (this->swap_color_flag_ == 1)
        painter.fillPath(upper_icon_path, this->fore_color_2_);
    else
        painter.fillPath(upper_icon_path, this->fore_color_1_);

    //Draw Arrow 2
    QPainterPath lower_icon_path;
    lower_icon_path.moveTo(icon_rect.right(), icon_rect.bottom() - icon_rect.height()/6);
    lower_icon_path.lineTo(icon_rect.right() - icon_rect.width()*(2/3), icon_rect.bottom() - icon_rect.height()/6);
    lower_icon_path.lineTo(icon_rect.right() - icon_rect.width()*(2/3), icon_rect.bottom());
    lower_icon_path.lineTo(icon_rect.left(), icon_rect.bottom() - icon_rect.height()/4);
    lower_icon_path.lineTo(icon_rect.right() - icon_rect.width()*(2/3), icon_rect.bottom() - icon_rect.height()/2);
    lower_icon_path.lineTo(icon_rect.right() - icon_rect.width()*(2/3), icon_rect.bottom() - icon_rect.height()/3);
    lower_icon_path.lineTo(icon_rect.right(), icon_rect.bottom() - icon_rect.height()/3);
    lower_icon_path.lineTo(icon_rect.right(), icon_rect.bottom() - icon_rect.height()/6);

    if (this->swap_color_flag_ == 1)
        painter.fillPath(lower_icon_path, this->fore_color_1_);
    else
        painter.fillPath(lower_icon_path, this->fore_color_2_);
};

void ConnectionButton::setBgColor_(const QColor color){
    this->bg_color_ = color;
    this->bg_default_color_ = this->bg_color_;
    this->repaint();
};

std::pair<QColor, QColor> ConnectionButton::getForeColors_() const{
    return std::make_pair(this->fore_color_1_, this->fore_color_2_);
};

void ConnectionButton::setForeColors_(std::pair<QColor, QColor> colors){
    this->fore_color_1_ = colors.first;
    this->fore_color_2_ = colors.second;
    this->repaint();
};

int ConnectionButton::getSwapColorFlag_() const{
    return this->swap_color_flag_;
};

void ConnectionButton::setSwapColorFlag_(int flag){
    this->swap_color_flag_ = flag;
    this->repaint();
};

void ConnectionButton::connectionAnimation(){
    if (this->connection_anim_->state() == QPropertyAnimation::Running) return;

    this->connection_anim_->setDuration(1000);  // Miliseconds, default: 250ms
    this->connection_anim_->setLoopCount(-1);  // loop count of the animation, default: -1 (runs continously)

    this->connection_anim_->setStartValue(1);
    this->connection_anim_->setKeyValueAt(0.5, 1);  // Reverse colors
    this->connection_anim_->setEndValue(0);
    this->connection_anim_->start();
};

void ConnectionButton::resumeAnimation(){
    this->connection_anim_->resume();
};

void ConnectionButton::pauseAnimation(){
    this->connection_anim_->pause();
};

void ConnectionButton::stopAnimation(){
    this->connection_anim_->stop();
};

void ConnectionButton::setTheme(const std::map<QString, QString> &style){
    QColor foreground, background;
    foreground.setNamedColor(style.at("foreground"));
    background.setNamedColor(style.at("background"));

    this->fore_color_1_ = foreground;
    this->fore_color_2_ = foreground;
    this->bg_color_ = background;
};

/**
 * @brief FlatButton::FlatButton
 * @param parent_
 */

FlatButton::FlatButton(QWidget *parent_)
{
    this->setParent(parent_);

    this->installEventFilter(this);
    this->setCheckable(true);
    this->fore_color_ = WHITE_COLOR;
    this->bg_color_ = QColor(5, 5, 5);
    this->checked_color_ = this->bg_color_;
    this->border_color_ = WHITE_COLOR;

    this->text_ = "Text";
}

bool FlatButton::eventFilter(QObject *obj_, QEvent *event_){
    /*
    if (obj_ == this && event_->type() == QEvent::MouseButtonPress)
        this->fore_color_ = this->fore_on_press_.lightness();
    if (obj_ == this && event_->type() == QEvent::MouseButtonRelease)
        this->fore_color_ = this->fore_on_release_;

    if (obj_ == this && event_->type() == QEvent::HoverEnter)
        this->fore_color_ = this->fore_on_press_.lighter(150);
    if (obj_ == this && event_->type() == QEvent::HoverLeave)
        this->fore_color_ = this->fore_on_press_;
    */

    return false;
};

void FlatButton::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();

    QRect base_rect(0, 0, width, height);

    QColor bg_color;
    QFont text_font{};
    if (this->isChecked()){
        bg_color = this->checked_color_;
        text_font.setBold(true);
    }
    else{
        bg_color = this->bg_color_;
        text_font.setBold(false);
    }

    // Draw Base Rectangle
    painter.setBrush(bg_color);
    painter.drawRect(base_rect);

    // Draw Text
    int text_width = width;
    int text_height = height;
    QRect text_rect(10, 0, (int) text_width, (int) text_height);

    painter.setPen(QPen(this->fore_color_, 1, Qt::PenStyle::SolidLine));
    painter.setFont(text_font);
    painter.drawText(text_rect, Qt::AlignVCenter, this->text_);
};

QString FlatButton::getText() const{
    return this->text_;
};

void FlatButton::setText(const QString &text){
    setText_(text);
};

void FlatButton::setTheme(const std::map<QString, QString> &style){
    QColor foreground, background, checked_color, border;

    foreground.setNamedColor(style.at("foreground"));
    background.setNamedColor(style.at("background"));
    checked_color.setNamedColor(style.at("checked_color"));
    border.setNamedColor(style.at("border"));

    this->fore_color_ = foreground;
    this->bg_color_ = background;
    this->checked_color_ = background;
    this->border_color_ = border;
    this->repaint();
};

/**
 * @brief PanelButton::PanelButton
 * @param parent_
 */

PanelButton::PanelButton(QWidget *parent_)
{
    this->setParent(parent_);

    this->installEventFilter(this);
    this->setCheckable(true);
    this->setChecked(false);

    this->fore_color_ = QColor(0, 255, 0);
    this->bg_color_ = QColor(10, 10, 10);
    this->border_color_ = WHITE_COLOR;
    this->checked_color_ = QColor(0, 255, 0);
    this->unchecked_color_ = QColor(50, 50, 50);
    this->bg_on_hover_color_ = this->bg_color_.lighter(150);
    this->bg_on_press_color_ = this->bg_color_.lighter(300);
    this->bg_on_release_color_ = this->bg_color_;

    this->setSizePolicy(QSizePolicy::Expanding,
                        QSizePolicy::Expanding);

    this->text_ = "Text";

    this->check_anim_ = new QPropertyAnimation(this, "checked", this);
}

bool PanelButton::eventFilter(QObject *obj_, QEvent *event_){
    if (obj_ == this && event_->type() == QEvent::MouseButtonPress)
        this->bg_color_ = this->bg_on_press_color_;

    else if (obj_ == this && event_->type() == QEvent::MouseButtonRelease)
        this->bg_color_ = this->bg_on_release_color_;

    else if (obj_ == this && event_->type() == QEvent::HoverEnter)
        this->bg_color_ = this->bg_on_hover_color_;

    else if (obj_ == this && event_->type() == QEvent::HoverLeave)
        this->bg_color_ = this->bg_on_release_color_;

    return false;
};

void PanelButton::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);

    int border_thickness = 5;
    int width = this->width() - border_thickness*2;
    int height = this->height() - border_thickness*2;

    qreal radius = qMin<qreal>(width, height) * 0.01;
    QRect base_rect(border_thickness, border_thickness, width, height);

    painter.setBrush(this->bg_color_);
    QColor text_color;
    if (this->isChecked()){
        painter.setPen(QPen(this->checked_color_, border_thickness, Qt::PenStyle::SolidLine));
        text_color = this->checked_color_;
    }
    else{
        painter.setPen(QPen(this->unchecked_color_, border_thickness, Qt::PenStyle::SolidLine));
        text_color = this->unchecked_color_;
    }

    // Draw Base Rectangle
    painter.drawRoundedRect(base_rect, radius, radius);

    // Draw Text
    int text_width = width;
    int text_height = height;
    QRect text_rect(border_thickness, border_thickness, (int) text_width, (int) text_height);

    // text_font = QtGui.QFont(QtGui.QFont("Verdana", 10, QtGui.QFont.Normal));
    QFont text_font{};
    // text_font.setPixelSize(int(min(width*0.1, height*0.3)));

    painter.setPen(QPen(text_color, 2, Qt::PenStyle::SolidLine));
    painter.setFont(text_font);
    painter.drawText(text_rect, Qt::AlignCenter, this->text_);
};

bool PanelButton::getIsBlinked_() const{
    return this->is_blinked_;
};

void PanelButton::setIsBlinked_(bool is_blinked){
    this->is_blinked_ = is_blinked;
};

bool PanelButton::getToggled_() const{
    return this->isChecked();
};

void PanelButton::setToggled_(bool checked){
    this->setChecked(checked);
    this->repaint();
};

void PanelButton::startAnimation(){
    if (this->check_anim_->state() == QPropertyAnimation::Running) return;
    this->is_blinked_ = true;

    this->check_anim_->setDuration(10000);  // Miliseconds, default: 1000ms
    this->check_anim_->setLoopCount(-1);  // loop count of the animation, default: -1 (runs continously)

    this->check_anim_->setStartValue(true);
    this->check_anim_->setKeyValueAt(0.5, false);
    this->check_anim_->setEndValue(true);
    this->check_anim_->start();
};

void PanelButton::stopAnimation(){
    if (this->check_anim_->state() == QPropertyAnimation::Running){
        this->is_blinked_ = false;
        this->check_anim_->stop();
    }
};

void PanelButton::setText(const QString &text){
    setText_(text);
};

void PanelButton::setTheme(const std::map<QString, QString> &style){
    QColor foreground, background, checked_color, unchecked_color, bg_on_hover, bg_on_press, bg_on_release;

    foreground.setNamedColor(style.at("foreground"));
    background.setNamedColor(style.at("background"));
    checked_color.setNamedColor(style.at("checked_color"));
    unchecked_color.setNamedColor(style.at("unchecked_color"));
    bg_on_hover.setNamedColor(style.at("bg_on_hover"));
    bg_on_press.setNamedColor(style.at("bg_on_press"));
    bg_on_release.setNamedColor(style.at("bg_on_release"));

    this->fore_color_ = foreground;
    this->bg_color_ = background;
    this->checked_color_ = checked_color;
    this->unchecked_color_ = unchecked_color;
    this->bg_on_hover_color_ = bg_on_hover;
    this->bg_on_press_color_ = bg_on_press;
    this->bg_on_release_color_ = bg_on_release;
    this->repaint();
};

/**
 * @brief FireButton::FireButton
 * @param parent_
 */

FireButton::FireButton(QWidget *parent_)
{
    this->setParent(parent_);

    this->installEventFilter(this);
    this->bg_color_ = QColor(200, 0, 0);
    this->fore_color_ = WHITE_COLOR;
    this->text_ = QString("FIRE");

    QObject::connect(this, SIGNAL(pressed()), this, SLOT(clicked_()));

    this->border_color_ = BLACK_COLOR;
    this->is_active_ = false;

    this->glow_anim_ = new QPropertyAnimation{this, "glowDia", this};
    //startGlowAnimation();
}

void FireButton::keyPressEvent(QKeyEvent *event_){
    //if (event_->key() == Qt::Key_Shift)

 };

void FireButton::keyReleaseEvent(QKeyEvent *event_){
    //if (event_->key() == Qt::Key_Shift)

};

void FireButton::mousePressEvent(QMouseEvent *event_){
    if (event_->type() == QMouseEvent::MouseButtonPress){
        emit this->pressed();
    }
};

void FireButton::resizeEvent(QResizeEvent *event_){
    this->max_glow_dia_ = qMin<int>(this->width(), this->height());
}

void FireButton::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QRect rect(0, 0, this->width(), this->height());

    // Draw Base Ellipse
    painter.setBrush(QColor(200, 0, 0));
    qreal diameter = qMin<qreal>(this->width(), this->height())*0.7;
    QRect base_rect(0, 0, (int) diameter, (int) diameter);
    base_rect.translate((int) ((rect.width()-base_rect.width())/2), (int) ((rect.height()-base_rect.height())/2));

    QLinearGradient base_color{};
    base_color.setStart((int) ((rect.width()-base_rect.width())/2), (int) ((rect.height()-base_rect.height())/2));
    base_color.setFinalStop((int) ((rect.width()-base_rect.width())/2)+diameter, (int) ((rect.height()-base_rect.height())/2)+diameter);

    base_color.setColorAt(0, QColor(255, 120, 120));
    base_color.setColorAt(1, QColor(138, 0, 2));
    painter.setBrush(base_color);

    painter.drawEllipse(base_rect);
    this->min_glow_dia_ = qMin<int>((int) base_rect.width(), (int) base_rect.height());

    // Draw Outer Circle
    painter.setBrush(Qt::transparent);
    QLinearGradient outer_circle_lin_color{};
    outer_circle_lin_color.setStart((int) ((rect.width()-base_rect.width())/2),
                                    (int) ((rect.height()-base_rect.height())/2));
    outer_circle_lin_color.setFinalStop((int) ((rect.width()-base_rect.width())/2)+diameter,
                                        (int) ((rect.height()-base_rect.height())/2)+diameter);

    outer_circle_lin_color.setColorAt(0, QColor(255, 240, 240));
    outer_circle_lin_color.setColorAt(1, QColor(242, 1, 3));

    painter.setPen(QPen(outer_circle_lin_color, 3, Qt::SolidLine));

    qreal outer_circle_dia = diameter*0.95;
    QRect outer_circle_rect(0, 0, (int) outer_circle_dia, (int) outer_circle_dia);
    outer_circle_rect.translate((int) ((rect.width()-outer_circle_rect.width())/2),
                                (int) ((rect.height()-outer_circle_rect.height())/2));

    painter.drawEllipse(outer_circle_rect);
    painter.setPen(Qt::PenStyle::NoPen);

    // Draw Inner Ellipse
    int inner_diameter = qMin<int>(this->width(), this->height())*0.4;
    QRect inner_rect(0, 0, (int) inner_diameter, (int) inner_diameter);
    inner_rect.translate((int) ((rect.width()-inner_rect.width())/2),
                         (int) ((rect.height()-inner_rect.height())/2));

    QLinearGradient inner_color{};
    inner_color.setStart((int) ((rect.width()-inner_rect.width())/2), (int) ((rect.height()-inner_rect.height())/2));
    inner_color.setFinalStop((int) ((rect.width()-inner_rect.width())/2)+inner_diameter,
                             (int) ((rect.height()-inner_rect.height())/2)+inner_diameter);

    inner_color.setColorAt(0, QColor(180, 3, 4));
    inner_color.setColorAt(0.5, QColor(254, 29, 27));
    inner_color.setColorAt(1, QColor(255, 150, 150));
    painter.setBrush(inner_color);

    painter.drawEllipse(inner_rect);

    // Draw Inner Circle
    painter.setBrush(Qt::transparent);
    painter.setPen(QPen(QColor(242, 1, 3), 2, Qt::SolidLine));

    QRect inner_circle_rect(0, 0, (int) inner_diameter, (int) inner_diameter);
    inner_circle_rect.translate((int) ((rect.width()-inner_rect.width())/2),
                                (int) ((rect.height()-inner_rect.height())/2));
    painter.drawEllipse(inner_circle_rect);

    // Draw Glow
    painter.setPen(Qt::PenStyle::NoPen);
    this->max_glow_dia_ = qMin<int>(this->width(), this->height());
    QRect glow_rect(0, 0, this->glow_dia_, this->glow_dia_);
    glow_rect.translate((int) ((rect.width()-glow_rect.width())/2),
                        (int) ((rect.height()-glow_rect.height())/2));

    QPoint center_point((int) ((rect.width() - glow_rect.width())/2 + this->glow_dia_/2),
                        (int) ((rect.height() - glow_rect.height())/2 + this->glow_dia_/2));
    QRadialGradient glow_color(center_point, this->glow_dia_/2);

    glow_color.setColorAt(0, QColor(255, 0, 0, 100));
    glow_color.setColorAt(0.5, QColor(255, 0, 0, 100));
    glow_color.setColorAt(0.9, QColor(240, 0, 0, 100));
    glow_color.setColorAt(1, QColor(240, 0, 0, 0));

    painter.setBrush(glow_color);
    painter.drawEllipse(glow_rect);

    // Draw Text
    QColor text_color = this->fore_color_;
    QFont text_font("Verdana", 20, QFont::ExtraBold);
    text_font.setPixelSize((int) (inner_rect.height()*0.3));

    painter.setPen(QPen(text_color, 2, Qt::PenStyle::SolidLine));
    painter.setFont(text_font);
    painter.drawText(inner_rect, Qt::AlignCenter, this->text_);

    // Disabled Mask
    if (!this->isEnabled()){
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 255, 255, 150));
        painter.drawEllipse(base_rect);
    }
};

void FireButton::clicked_(){
    Qt::KeyboardModifiers modifier = QApplication::keyboardModifiers();

    if (modifier == Qt::KeyboardModifier::ShiftModifier){
        emit this->fire();
    }
};

QColor FireButton::getBgColor_() const{
    return this->bg_color_;
};

void FireButton::setBgColor_(const QColor color){
    this->bg_color_ = color;
    this->repaint();
};

QColor FireButton::getForeColor_() const{
    return this->fore_color_;
};

void FireButton::setForeColor_(const QColor color){
    this->fore_color_ = color;
    this->repaint();
};

QString FireButton::getText_() const{
    return this->text_;
};

void FireButton::setText_(const QString &text){
    this->text_ = text;
    this->repaint();
};

qreal FireButton::getGlowDia_() const{
    return this->glow_dia_;
};

void FireButton::setGlowDia_(qreal glow_dia){
    this->glow_dia_ = glow_dia;
    this->repaint();
};

void FireButton::startGlowAnimation(){
    this->repaint();
    if (this->glow_anim_->state() == QPropertyAnimation::Running) return;

    this->max_glow_dia_ = qMin<int>(this->width(), this->height());

    this->glow_anim_->setDuration(1000);  // Miliseconds, default: 1000ms
    this->glow_anim_->setLoopCount(-1);  // loop count of the animation, default: -1 (runs continously)

    this->glow_anim_->setStartValue(this->min_glow_dia_);
    this->glow_anim_->setEndValue(this->max_glow_dia_);
    this->glow_anim_->start();
};

void FireButton::stopGlowAnimation(){
    if (this->glow_anim_->state() == QPropertyAnimation::Running){
        this->setGlowDia_(0);
        this->glow_anim_->stop();
    }
};

void FireButton::setTheme(const std::map<QString, QString> &style){
    QColor foreground, background, border;

    foreground.setNamedColor(style.at("foreground"));
    background.setNamedColor(style.at("background"));
    border.setNamedColor(style.at("border"));

    this->fore_color_ = foreground;
    this->bg_color_ = background;
    this->border_color_ = border;
    this->repaint();
};

void FireButton::setText(const QString &text){
    this->setText_(text);
};

/**
 * @brief BadgeButton::BadgeButton
 * @param parent_
 */

BadgeButton::BadgeButton(QWidget *parent_)
{
    this->setParent(parent_);

    this->setMouseTracking(true);
    this->installEventFilter(this);

    this->setFixedHeight(100);
    this->setFixedWidth(100);

    this->fore_color_ = WHITE_COLOR;
    this->bg_color_ = DARK_GRAY_COLOR;
    this->bg_on_press_color_ = this->bg_color_.lighter(200);
    this->bg_on_hover_color_ = this->bg_color_.lighter(150);
    this->bg_on_release_color_ = this->bg_color_;
    this->badge_color_ = QColor(230,56,25);

    badge_anim_ = new QPropertyAnimation{this, "badgeColor", this};
}

bool BadgeButton::eventFilter(QObject *obj_, QEvent *event_){
    if(obj_ == this && event_->type() == QEvent::MouseButtonPress){
        is_pressed_ = true;
        this->bg_color_ = this->bg_on_press_color_;
    }
    else if(obj_ == this && event_->type() == QEvent::MouseButtonRelease){
        is_pressed_ = false;
        this->bg_color_ = this->bg_on_release_color_;
    }

    return false;
};

void BadgeButton::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(0,0);

    qreal size = qMin<qreal>(this->height(), this->width());
    // Fixed ratio of badge button. Adapted from IOS icon
    qreal offset_x = size * 0.0758;
    qreal offset_y = size * 0.0623;
    qreal round_radius = size * 0.236;
    qreal badge_size = size * 0.3535;  // Diameter
    qreal badge_offset_x = size * 0.65;
    qreal badge_offset_y = size * 0.01;

    // Draw Background
    QRect rect{};
    rect.translate(0, (int) offset_y);
    rect.setSize(QSize((int)(size-offset_x), (int)(size-offset_y)));

    if (this->underMouse())
        this->bg_color_ = this->is_pressed_? this->bg_on_press_color_: this->bg_on_hover_color_;
    else
        this->bg_color_ = this->bg_on_release_color_;

    painter.setBrush(bg_color_);
    painter.drawRoundedRect(rect, round_radius, round_radius);

    // Draw Icon
    QPixmap pixmap = this->icon_.pixmap(QSize(size, size));
    QRectF source_pixmap = QRectF(0, 0, size, size);
    QRectF target_pixmap = QRectF(0, 0, size*.5, size*.5);
    target_pixmap.translate(size*.25, size*.25);
    painter.drawPixmap(target_pixmap, pixmap, source_pixmap);

    // Do not draw badge if there is no notification
    if (this->notification_number_ <= 0) return;

    // Draw Badge
    QRect badge_rect{};
    badge_rect.translate((int) badge_offset_x, (int) badge_offset_y);
    badge_rect.setSize(QSize((int)badge_size, (int)badge_size));
    painter.setBrush(this->badge_color_);
    painter.drawEllipse(badge_rect);
    painter.setPen(this->fore_color_);
    painter.drawText(badge_rect, Qt::AlignCenter, QString::number(this->notification_number_));
};

void BadgeButton::setBgColor_(QColor color){
    this->bg_color_ = color;
    // Change also on press/release color background colors
    this->bg_on_press_color_ = this->bg_color_.lighter(200);
    this->bg_on_hover_color_ = this->bg_color_.lighter(150);
    this->bg_on_release_color_ = this->bg_color_;
    this->repaint();
};

unsigned int BadgeButton::getHighlightFactor_(){
    return this->highlight_factor_;
};

void BadgeButton::setHighlightFactor_(unsigned int highlight_factor){
    this->highlight_factor_ = highlight_factor;
    this->repaint();
};

QColor BadgeButton::getBadgeColor_(){
    return this->badge_color_;
};

void BadgeButton::setBadgeColor_(QColor color){
    this->badge_color_ = color;
    this->repaint();
};

unsigned int BadgeButton::getNotifyNumber_(){
    return this->notification_number_;
};

void BadgeButton::setNotifyNumber_(unsigned int notification_number){
    if (this->notification_number_ < 0) return;

    if (this->notification_number_ > 99)
        this->notification_number_ = 99;

    if (notification_number > this->notification_number_)
        this->badgeAnimation();

    this->notification_number_ = notification_number;
    this->repaint();
};

void BadgeButton::badgeAnimation(){
    // Do not start new animation if it is already running. Fixes bug of stacked value on repeated start
    if (this->badge_anim_->state() == QPropertyAnimation::Running) return;

    this->badge_anim_->setDuration(500);  // Milisecons, default: 250ms
    this->badge_anim_->setLoopCount(1);  // loop count of the animation, default: 1 (runs only once)

    this->badge_anim_->setStartValue(this->badge_color_);
    this->badge_anim_->setKeyValueAt(0.5, this->badge_color_.lighter(200));
    this->badge_anim_->setEndValue(this->badge_color_);
    this->badge_anim_->start();
};

unsigned int BadgeButton::getNotifyNumber(){
    return getNotifyNumber_();
};

void BadgeButton::setNotifyNumber(unsigned int notification_number){
    setNotifyNumber_(notification_number);
};

void BadgeButton::decreaseNotifyNumber(){
    setNotifyNumber_(this->notification_number_ - 1);
};

void BadgeButton::increaseNotifyNumber(){
    setNotifyNumber_(this->notification_number_ + 1);
};

void BadgeButton::resetNotifyNumber(){
    setNotifyNumber_(0);
};

/**
 * @brief ToggleButton::ToggleButton
 * @param parent_
 */

NavigationButton::NavigationButton(QWidget *parent_)
{
    this->setParent(parent_);

    setButtonType_(ButtonType::DefaultButton);

    this->setMouseTracking(true);
    this->installEventFilter(this);
    this->setCheckable(true);

    this->bg_color_ = QColor(43, 43, 43);
    this->bg_on_click_color_ = this->bg_color_.lighter(150);
    this->bg_on_release_color_ = this->bg_color_;
    this->fore_color_ = WHITE_COLOR;

    this->unchecked_color_ = QColor(60, 63, 65);
    this->checked_color_ = QColor(179, 255, 128);

    this->shadow_ = new QGraphicsDropShadowEffect{this};
    this->shadow_->setOffset(0, 0);
    this->shadow_->setColor(this->checked_color_);
    this->setGraphicsEffect(this->shadow_);

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedSlot_()));
}

NavigationButton::NavigationButton(const ButtonType button_type, QWidget *parent_)
{
    this->setParent(parent_);

    setButtonType_(button_type);

    this->setMouseTracking(true);
    this->installEventFilter(this);
    this->setCheckable(true);

    this->bg_color_ = QColor(8, 13, 20);
    this->fore_color_ = QColor(91, 192, 172);

    this->unchecked_color_ = this->bg_color_;
    this->checked_color_ = this->fore_color_;

    this->shadow_ = new QGraphicsDropShadowEffect{this};
    this->shadow_->setOffset(0, 0);
    this->shadow_->setColor(this->checked_color_);
    this->setGraphicsEffect(this->shadow_);

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedSlot_()));
}

bool NavigationButton::eventFilter(QObject *obj_, QEvent *event_){
    if (obj_ == this and event_->type() == QEvent::MouseButtonPress)
        this->bg_color_ = this->bg_on_click_color_;
    if (obj_ == this and event_->type() == QEvent::MouseButtonRelease)
        this->bg_color_ = this->bg_on_release_color_;

    return false;
};

void NavigationButton::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0, 0);
    // 170x44 3.86
    int width = qRound(this->height()*3.86);
    int height = this->height();
    int radius = height*.5;
    int border_thickness = 2;

    // Draw Background
    QRect base_rect;
    base_rect.setSize(QSize(width-border_thickness*2, height-border_thickness*2));
    base_rect.translate(border_thickness,
                        border_thickness);

    QColor bg_color, text_color;
    bool is_checked = this->isChecked();

    if (this->underMouse()) showShadow_();
    else hideShadow_();

    if(this->isEnabled()){
        if(is_checked){
            bg_color = this->checked_color_;
            text_color = this->unchecked_color_;
        }
        else{
            bg_color = this->unchecked_color_;
            text_color = this->checked_color_;
        }
    }
    else{
        if(is_checked){
            bg_color = this->checked_color_.lightness();
            text_color = this->unchecked_color_.lightness();
        }
        else{
            bg_color = this->unchecked_color_.lightness();
            text_color = this->checked_color_.lightness();
        }
    }
    painter.setPen(QPen(text_color, border_thickness, Qt::PenStyle::SolidLine));
    painter.setBrush(bg_color);
    painter.drawRoundedRect(base_rect, radius-border_thickness, radius-border_thickness);

    // Draw Text
    QFont text_font("Roboto", 20, QFont::Bold);
    text_font.setPixelSize((int) (base_rect.height()*0.4));

    painter.setFont(text_font);
    painter.drawText(base_rect, Qt::AlignCenter, this->text_);

    // Draw Arrow
    QRect arrow_rect;
    int arrow_size;
    QPainterPath arrow_path;
    switch(this->button_type_){
        case(ButtonType::BackButton):
            arrow_size = qMin<int>(base_rect.width()*0.2, base_rect.height()*0.25);
            arrow_rect.setSize(QSize(arrow_size, arrow_size*1.6));
            arrow_rect.translate((int)(arrow_size + base_rect.x()),
                                 (int) ((base_rect.height()-arrow_rect.height())/2 + base_rect.y()));

            arrow_path.moveTo(arrow_rect.right(), arrow_rect.top());
            arrow_path.lineTo(arrow_rect.left(), arrow_rect.top() + arrow_rect.height()/2);
            arrow_path.lineTo(arrow_rect.right(), arrow_rect.bottom());
            painter.drawPath(arrow_path);
            break;

        case(ButtonType::NextButton):
            arrow_size = qMin<int>(base_rect.width()*0.2, base_rect.height()*0.25);
            arrow_rect.setSize(QSize(arrow_size, arrow_size*1.6));
            arrow_rect.translate((int)(base_rect.width() - arrow_size*2 + base_rect.x()),
                                 (int) ((base_rect.height()-arrow_rect.height())/2 + base_rect.y()));

            arrow_path.moveTo(arrow_rect.left(), arrow_rect.top());
            arrow_path.lineTo(arrow_rect.right(), arrow_rect.top() + arrow_rect.height()/2);
            arrow_path.lineTo(arrow_rect.left(), arrow_rect.bottom());
            painter.drawPath(arrow_path);
            break;
        case(ButtonType::FinishButton):
            break;
        default:
            break;
    }

};

QColor NavigationButton::getUncheckedColor_() const{
    return this->unchecked_color_;
};

void NavigationButton::setUncheckedColor_(const QColor &color){
    this->unchecked_color_ = color;
};

QColor NavigationButton::getCheckedColor_() const{
    return this->checked_color_;
};

void NavigationButton::setCheckedColor_(const QColor &color){
    this->checked_color_ = color;
};

void NavigationButton::setButtonType_(const ButtonType button_type){
    this->button_type_ = button_type;

    switch(this->button_type_){
        case (ButtonType::BackButton):
            this->text_ = "Back";
            break;
        case (ButtonType::NextButton):
            this->text_ = "Next";
            break;
        case (ButtonType::FinishButton):
            this->text_ = "Finish";
            break;
        default:
            this->button_type_ = ButtonType::FinishButton;
            this->text_ = "Finish";
            break;
    }
};

void NavigationButton::showShadow_(){
    this->shadow_->setBlurRadius(20);
    this->setGraphicsEffect(this->shadow_);
}

void NavigationButton::hideShadow_(){
    this->shadow_->setBlurRadius(0);
    this->setGraphicsEffect(this->shadow_);
}

void NavigationButton::setTheme(const std::map<QString, QString> &style){
    QColor fore_color, bg_color, checked_color, unchecked_color;

    fore_color.setNamedColor(style.at("fore_color"));
    bg_color.setNamedColor(style.at("bg_color"));
    checked_color.setNamedColor(style.at("checked"));
    unchecked_color.setNamedColor(style.at("unchecked"));

    this->fore_color_ = fore_color;
    this->bg_color_ = bg_color;
    this->checked_color_ = checked_color;
    this->unchecked_color_ = unchecked_color;
    this->repaint();
};

void NavigationButton::clickedSlot_(){
    emit this->toggled(this->isChecked());
}
