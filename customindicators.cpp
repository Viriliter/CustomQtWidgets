#include "customindicators.h"

ClassicLedIndicator::ClassicLedIndicator(QWidget *parent_)
{
    this->setParent(parent_);

    this->color_anim_ = new QPropertyAnimation{this, "color", this};
    this->fore_color_ = QColorConstants::White;
    this->bg_color_ = QColorConstants::Black;
    this->default_fore_color_ =  QColorConstants::White;
}

void ClassicLedIndicator::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    int size = qMin<int>(this->height(), this->width());

    QRect fullRect;
    fullRect.setSize(QSize(size, size));

    qreal radius = size * .1;
    QRect rect = fullRect.adjusted(round(radius), round(radius), round(-radius), round(-radius));

    // Outer Bezel
    painter.setBrush(this->bg_color_);
    painter.drawEllipse(rect);

    // Main Color
    rect.adjust(round(radius / 2), round(radius / 2), round(-radius / 2), round(-radius / 2));
    painter.setBrush(this->fore_color_);
    painter.drawEllipse(rect);

    if (this->is_glowed_)
        return;

    // Glow
    QRadialGradient glowGrad(fullRect.center(), fullRect.width() / 2);

    QColor faint(this->fore_color_);
    faint.setAlphaF(.5);

    QColor faintest (this->fore_color_);
    faintest.setAlphaF(0);
    glowGrad.setStops(QGradientStops{{QGradientStop(0, faint)},
                                     {QGradientStop(1, faintest)}});
    painter.setBrush(glowGrad);
    painter.drawEllipse(fullRect);
};

QColor ClassicLedIndicator::getColor_() const{
    return this->fore_color_;
};

void ClassicLedIndicator::setColor_(const QColor &color){
    this->fore_color_ = color;
    this->repaint();
};

QColor ClassicLedIndicator::getDefaultForeColor_() const{
    return this->default_fore_color_;
};

void ClassicLedIndicator::setDefaultForeColor_(const QColor &color){
    this->default_fore_color_ = color;
    this->repaint();
};

void ClassicLedIndicator::setColor(const QColor &color){
    this->stopColorAnimation();

    this->setColor(color);
    this->repaint();
};

void ClassicLedIndicator::setGlow(bool is_glowed){
    this->is_glowed_ = is_glowed;
    this->repaint();
};

void ClassicLedIndicator::startColorAnimation(QColor color1, QColor color2, unsigned int frequency, int duration){
    if (this->color_anim_->state() == QPropertyAnimation::Running) return;

    this->color_anim_->setDuration(frequency);  // milliseconds , default:1000ms

    if (duration == -1)  // It is infinite
        this->color_anim_->setLoopCount(-1);  // Loop count of the animation, default:-1 (run only once)
    else
        this->color_anim_->setLoopCount(int(duration/frequency));

    this->color_anim_->setStartValue(color1);
    this->color_anim_->setEndValue(color2);
    this->color_anim_->start();
};

void ClassicLedIndicator::stopColorAnimation(){
    if (this->color_anim_->state() == QPropertyAnimation::Running ||
        this->color_anim_->state() == QPropertyAnimation::Paused){
        this->fore_color_ = default_fore_color_;  // Set to default foreground
        this->color_anim_->stop();
    }
};

void ClassicLedIndicator::pauseColorAnimation(){
    if (this->color_anim_->state() == QPropertyAnimation::Running) this->color_anim_->pause();
};

void ClassicLedIndicator::resumeColorAnimation(){
    if (this->color_anim_->state() == QPropertyAnimation::Paused) this->color_anim_->resume();
};

void ClassicLedIndicator::setTheme(const std::map<QString, QString> &style){
    QColor foreground, default_foreground, background;

    foreground.setNamedColor(style.at("foreground"));
    default_foreground.setNamedColor(style.at("defaultForeground"));
    background.setNamedColor(style.at("background"));

    this->fore_color_ = foreground;
    this->default_fore_color_ = default_foreground;
    this->bg_color_ = background;

    this->repaint();
};



RealisticLedIndicator::RealisticLedIndicator(QWidget *parent_)
{
    this->setParent(parent_);

    this->color_anim_ = new QPropertyAnimation{this, "color", this};
    this->fore_color_ = QColorConstants::White;
    this->bg_color_ = QColorConstants::Black;
    this->default_fore_color_ =  QColorConstants::White;
}

void RealisticLedIndicator::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    int size = qMin<int>(this->height(), this->width());

    QRect fullRect;
    fullRect.setSize(QSize(size, size));

    qreal radius = size * .1;
    QRect rect = fullRect.adjusted((int) radius, (int) radius, (int) -radius, (int) -radius);

    // Outer Bezel
    QLinearGradient outerBezelGrad(rect.topLeft(), rect.bottomLeft());
    outerBezelGrad.setStops(QGradient(QGradient::RiskyConcrete).stops());
    painter.setBrush(outerBezelGrad);
    painter.drawEllipse(rect);

    // Inner Bezel
    rect.adjust((int) radius, (int) radius, (int) -radius, (int) -radius);
    QLinearGradient innerBezelGrad(rect.bottomLeft(), rect.topLeft());
    innerBezelGrad.setStops(QGradient(QGradient::RichMetal).stops());
    painter.setBrush(innerBezelGrad);
    painter.drawEllipse(rect);

    // Main Color
    QColor mainColor = this->fore_color_;
    rect.adjust((int) (radius / 2), (int) (radius / 2), (int) (-radius / 2), (int) (-radius / 2));
    QLinearGradient mainColorGrad(rect.bottomLeft(), rect.topLeft());
    mainColorGrad.setStops(QGradientStops{{QGradientStop(0, mainColor.lighter())},
                                          {QGradientStop(1, mainColor.darker())}});
    painter.setBrush(mainColorGrad);
    painter.drawEllipse(rect);

    // HighLight
    rect.adjust((int) (rect.width() / 6), (int) (radius / 4), (int) (-rect.width() / 6), (int) (-rect.height() * 2 / 5.));
    QLinearGradient highlightGrad(rect.topLeft(), rect.bottomLeft());
    highlightGrad.setStops(QGradientStops{{QGradientStop(0, QColor(255, 255, 255, 192))},
                                          {QGradientStop(1, QColor(255, 255, 255, 0))}});

    painter.setBrush(highlightGrad);
    painter.drawEllipse(rect);

    if (!this->is_glowed_)
        return;

    // Glow
    QRadialGradient glowGrad(fullRect.center(), (int) (fullRect.width() / 2));

    QColor faint(this->fore_color_);
    faint.setAlphaF(.5);

    QColor faintest (this->fore_color_);
    faintest.setAlphaF(0);
    glowGrad.setStops(QGradientStops{{QGradientStop(0, faint)},
                                    {QGradientStop(1, faintest)}});
    painter.setBrush(glowGrad);
    painter.drawEllipse(fullRect);
};

QColor RealisticLedIndicator::getColor_() const{
    return this->fore_color_;
};

void RealisticLedIndicator::setColor_(const QColor &color){
    this->fore_color_ = color;
    this->repaint();
};

QColor RealisticLedIndicator::getDefaultForeColor_() const{
    return this->default_fore_color_;
};

void RealisticLedIndicator::setDefaultForeColor_(const QColor &color){
    this->default_fore_color_ = color;
    this->repaint();
};

void RealisticLedIndicator::setColor(const QColor &color){
    this->stopColorAnimation();

    this->setColor(color);
    this->repaint();
};

void RealisticLedIndicator::setGlow(bool is_glowed){
    this->is_glowed_ = is_glowed;
    this->repaint();
};

void RealisticLedIndicator::startColorAnimation(QColor color1, QColor color2, unsigned int frequency, int duration){
    if (this->color_anim_->state() == QPropertyAnimation::Running) return;

    this->color_anim_->setDuration(frequency);  // milliseconds , default:1000ms

    if (duration == -1)  // It is infinite
        this->color_anim_->setLoopCount(-1);  // Loop count of the animation, default:-1 (run only once)
    else
        this->color_anim_->setLoopCount(int(duration/frequency));

    this->color_anim_->setStartValue(color1);
    this->color_anim_->setEndValue(color2);
    this->color_anim_->start();
};

void RealisticLedIndicator::stopColorAnimation(){
    if (this->color_anim_->state() == QPropertyAnimation::Running ||
        this->color_anim_->state() == QPropertyAnimation::Paused){
        this->fore_color_ = default_fore_color_;  // Set to default foreground
        this->color_anim_->stop();
    }
};

void RealisticLedIndicator::pauseColorAnimation(){
    if (this->color_anim_->state() == QPropertyAnimation::Running) this->color_anim_->pause();
};

void RealisticLedIndicator::resumeColorAnimation(){
    if (this->color_anim_->state() == QPropertyAnimation::Paused) this->color_anim_->resume();
};

void RealisticLedIndicator::setTheme(const std::map<QString, QString> &style){
    QColor foreground, default_foreground, background;

    foreground.setNamedColor(style.at("foreground"));
    default_foreground.setNamedColor(style.at("defaultForeground"));
    background.setNamedColor(style.at("background"));

    this->fore_color_ = foreground;
    this->default_fore_color_ = default_foreground;
    this->bg_color_ = background;

    this->repaint();
};

