#include "customlabels.h"

HighlightLabel::HighlightLabel(QWidget *parent_)
{

    this->base_fore_color_ = QColor(255, 0, 0);
    this->base_bg_color_ = BLACK_COLOR;
    this->border_color_ = WHITE_COLOR;
    this->unchecked_fore_color_ = this->base_fore_color_.darker(200);
    this->checked_fore_color_ = this->base_fore_color_;

    this->text_ = "RESET";

    this->blur_ = new QGraphicsDropShadowEffect{this};
    this->blur_->setBlurRadius(20);
    this->blur_->setOffset(0, 0);
    this->blur_->setColor(this->base_fore_color_);
    this->setGraphicsEffect(this->blur_);

    this->default_style_ = " \
        QLabel{{ \
                color:" + this->unchecked_fore_color_.name() + "; \
                background-color: transparent;}} \
        ";

        this->checked_style_ = " \
        QLabel{{ \
                color:" + this->checked_fore_color_.name() + "; \
                background-color: transparent;}} \
        ";

        this->setStyleSheet(this->default_style_);
    this->setAlignment(Qt::AlignCenter);

    this->text_font_ = QFont("Verdana", 10, QFont::DemiBold);
    this->setFont(this->text_font_);

}
bool HighlightLabel::getIsChecked_() const{
    return this->is_checked_;
};

void HighlightLabel::setIsChecked_(bool is_checked){
    this->is_checked_ = is_checked;
};

QColor HighlightLabel::getBaseBgColor_() const{
    return this->base_bg_color_;
};

void HighlightLabel::setBaseBgColor_(const QColor &color){
    this->base_bg_color_ = color;
};

QColor HighlightLabel::getBaseForeColor_() const{
    return this->base_fore_color_;
};

void HighlightLabel::setBaseForeColor_(const QColor &color){
    this->base_fore_color_ = color;
};


DynamicToolTipLabel::DynamicToolTipLabel(QWidget *parent_)
{
    this->setParent(parent_);

    this->tooltip_ = "";
}

void DynamicToolTipLabel::setToolTip(const QString &tooltip){
    // Override setToolTip function for dynamic update
    this->tooltip_ = tooltip;
    this->update();
};

bool DynamicToolTipLabel::event(QEvent *event_){
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
