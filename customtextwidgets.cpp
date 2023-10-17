#include "customtextwidgets.h"

CustomTextEdit::CustomTextEdit(QWidget *parent_)
{
    this->setParent(parent_);

    this->tooltip_ = "";
};

void CustomTextEdit::setToolTip(const QString &tooltip){
    // Override setToolTip function for dynamic update
    this->tooltip_ = tooltip;
    this->update();
};

bool CustomTextEdit::event(QEvent *event_){
    if (event_->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event_);
        if (!helpEvent->pos().isNull()) {
            this->last_pos_ = helpEvent->globalPos();
        }
    }

    if (event_->type() == QEvent::Paint && this->underMouse()){
        QToolTip::showText(this->last_pos_, this->tooltip_);
    }
    return QWidget::event(event_);
};



CustomLineEdit::CustomLineEdit(QWidget *parent_)
{
    this->setParent(parent_);

    this->tooltip_ = "";
}

void CustomLineEdit::setToolTip(const QString &tooltip){
    // Override setToolTip function for dynamic update
    this->tooltip_ = tooltip;
    this->update();
};

bool CustomLineEdit::event(QEvent *event_){
    if (event_->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event_);
        if (!helpEvent->pos().isNull()) {
            this->last_pos_ = helpEvent->globalPos();
        }
    }

    if (event_->type() == QEvent::Paint && this->underMouse()){
        QToolTip::showText(this->last_pos_, this->tooltip_);
    }
    return QWidget::event(event_);
};



BorderedTextEdit::BorderedTextEdit(QWidget *parent_)
{
    this->setParent(parent_);

    this->fore_color_ = QColorConstants::Black;
    this->bg_color_ = QColorConstants::White;
    this->border_color_ = QColorConstants::Black;

    this->border_weight_ = 5;

    this->text_ = "";
};

void BorderedTextEdit::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(this->border_color_);  // Set border color
    pen.setWidth(2);
    painter.setPen(pen);

    qreal width = this->width() - this->border_weight_ *2;
    qreal height = this->height() - this->border_weight_ *2;

    QRect base_rect(this->border_weight_ , this->border_weight_ , width, height);

    painter.setBrush(this->bg_color_);

    // Draw Base Rectangle
    painter.drawRect(base_rect);

    // Draw Text
    QRect text_rect(this->border_weight_ , this->border_weight_ , (int) width, (int) height);

    QFont text_font(QFont("Verdana", 10, QFont::Normal));
    // text_font.setPixelSize(int(min(width*0.1, height*0.3)));

    painter.setPen(QPen(this->fore_color_, 2, Qt::PenStyle::SolidLine));
    painter.setFont(text_font);
    painter.drawText(text_rect, Qt::AlignCenter, this->text_);
};

QColor BorderedTextEdit::getForeColor_() const{
    return this->fore_color_;
};

void BorderedTextEdit::setForeColor_(const QColor &color){
    this->fore_color_ = color;
    this->repaint();
};

QColor BorderedTextEdit::getBgColor_() const{
    return this->bg_color_;
};

void BorderedTextEdit::setBgColor_(const QColor &color){
    this->bg_color_ = color;
    this->repaint();
};

QColor BorderedTextEdit::getBorderColor_() const{
    return this->border_color_;
};

void BorderedTextEdit::setBorderColor_(const QColor &color){
    this->border_color_ = color;
    this->repaint();
};

unsigned int BorderedTextEdit::getBorderWeight_() const{
    return this->border_weight_;
};

void BorderedTextEdit::setBorderWeight_(unsigned int weight){
    this->border_weight_ = weight;
    this->repaint();
};

void BorderedTextEdit::setTheme(const std::map<QString, QString> &style){
    QColor foreground, background, border_color;
    unsigned int border_weight;

    foreground.setNamedColor(style.at("foreground"));
    background.setNamedColor(style.at("background"));
    border_color.setNamedColor(style.at("border"));
    border_weight = style.at("borderWeight").toUInt();

    this->fore_color_ = foreground;
    this->bg_color_ = background;
    this->border_color_ = border_color;
    this->border_weight_ = border_weight;

    this->repaint();
};

void BorderedTextEdit::setText(const QString &text){
    this->text_ = text;
    this->repaint();
};



BorderedTextLineEdit::BorderedTextLineEdit(QWidget *parent_)
{
    this->setParent(parent_);

    this->fore_color_ = QColorConstants::Black;
    this->bg_color_ = QColorConstants::White;
    this->border_color_ = QColorConstants::Black;

    this->border_weight_ = 2;

    this->text_ = "";
};

void BorderedTextLineEdit::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(this->border_color_);  // Set border color
    pen.setWidth(2);
    painter.setPen(pen);

    qreal width = this->width() - this->border_weight_ *2;
    qreal height = this->height() - this->border_weight_ *2;

    QRect base_rect(this->border_weight_ , this->border_weight_ , width, height);

    painter.setBrush(this->bg_color_);

    // Draw Base Rectangle
    painter.drawRect(base_rect);

    // Draw Text
    QRect text_rect(this->border_weight_ , this->border_weight_ , (int) width, (int) height);

    QFont text_font(QFont("Verdana", 10, QFont::Normal));
    // text_font.setPixelSize(int(min(width*0.1, height*0.3)));

    painter.setPen(QPen(this->fore_color_, 2, Qt::PenStyle::SolidLine));
    painter.setFont(text_font);
    painter.drawText(text_rect, Qt::AlignCenter, this->text_);
};

QColor BorderedTextLineEdit::getForeColor_() const{
    return this->fore_color_;
};

void BorderedTextLineEdit::setForeColor_(const QColor &color){
    this->fore_color_ = color;
    this->repaint();
};

QColor BorderedTextLineEdit::getBgColor_() const{
    return this->bg_color_;
};

void BorderedTextLineEdit::setBgColor_(const QColor &color){
    this->bg_color_ = color;
    this->repaint();
};

QColor BorderedTextLineEdit::getBorderColor_() const{
    return this->border_color_;
};

void BorderedTextLineEdit::setBorderColor_(const QColor &color){
    this->border_color_ = color;
    this->repaint();
};

unsigned int BorderedTextLineEdit::getBorderWeight_() const{
    return this->border_weight_;
};

void BorderedTextLineEdit::setBorderWeight_(unsigned int weight){
    this->border_weight_ = weight;
    this->repaint();
};

void BorderedTextLineEdit::setTheme(const std::map<QString, QString> &style){
    QColor foreground, background, border_color;
    unsigned int border_weight;

    foreground.setNamedColor(style.at("foreground"));
    background.setNamedColor(style.at("background"));
    border_color.setNamedColor(style.at("border"));
    border_weight = style.at("borderWeight").toUInt();

    this->fore_color_ = foreground;
    this->bg_color_ = background;
    this->border_color_ = border_color;
    this->border_weight_ = border_weight;

    this->repaint();
};

void BorderedTextLineEdit::setText(const QString &text){
    this->text_ = text;
    this->repaint();
};
