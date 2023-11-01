#include "customprogressbars.h"

CustomProgressBar::CustomProgressBar(QWidget *parent_)
{
    this->setParent(parent_);

    this->setFixedWidth(300);
    this->setFixedHeight(30);

    this->fore_color_ = QColorConstants::Black;
    this->bg_color_ = QColor(221, 221, 221);
    this->progress_color_ = QColor(137, 218, 103);

    this->progress_text_ = "";

    progress_anim_ = new QPropertyAnimation{this, "progress", this};
    color_anim_ = new QPropertyAnimation{this, "progressColor", this};
}

void CustomProgressBar::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0,0);

    qreal width = this->width();
    qreal height = this->height();
    QRect full_rect;
    full_rect.setSize(QSize(width, height));
    full_rect.translate(0, 0);

    // Draw progress slot
    qreal slot_width = full_rect.width();
    qreal slot_height = full_rect.height();
    qreal slot_radius = full_rect.height()*.5;
    QRect slot_rect;
    slot_rect.setSize(QSize(slot_width, slot_height));
    slot_rect.translate(0, 0);

    QLinearGradient progress_color{};
    progress_color.setStart(0, 0);
    progress_color.setFinalStop(slot_rect.width(), 0);
    if (this->progress_ == 0)
        painter.setBrush(this->bg_color_);
    else{
        progress_color.setColorAt(0, this->progress_color_);
        progress_color.setColorAt(this->progress_, this->progress_color_);
        progress_color.setColorAt(qMin<qreal>(this->progress_+0.001, 1), this->bg_color_);  // Create a sharp transition
        if (this->progress_ != 1) progress_color.setColorAt(1, this->bg_color_);
    }
    painter.setBrush(progress_color);
    painter.drawRoundedRect(slot_rect, (int) slot_radius, (int) slot_radius);

    if(!this->progress_visibility_) return;
    // Draw text
    QString text;
    text = this->progress_text_ + " " +QString::number((int) (this->progress_*100) % 100) + "%";
    painter.setPen(this->fore_color_);
    painter.drawText(slot_rect, Qt::AlignCenter, QString(text));
};

QColor CustomProgressBar::getForeColor_() const{
    return this->fore_color_;
};

void CustomProgressBar::setForeColor_(const QColor &color) {
    this->fore_color_ = color; this->repaint();
    this->repaint();
};

QColor CustomProgressBar::getBgColor_() const{
    return this->bg_color_;
};

void CustomProgressBar::setBgColor_(const QColor &color) {
    this->bg_color_ = color; this->repaint();
    this->repaint();
};

QColor CustomProgressBar::getProgressColor_() const{
    return this->progress_color_;
};

void CustomProgressBar::setProgressColor_(const QColor &color){
    this->progress_color_ = color;
    this->repaint();
};

qreal CustomProgressBar::getProgress_() const{
    return this->progress_;
};

void CustomProgressBar::setProgress_(qreal value){
    this->progress_ = value;
    if (this->progress_ == 1.0) emit finished();
    this->repaint();
};

QString CustomProgressBar::getProgressText_() const{
    return this->progress_text_;
};

void CustomProgressBar::setProgressText_(const QString &text){
    this->progress_text_ = text;
    this->repaint();
};

void CustomProgressBar::startAnimation(qreal start_value, qreal end_value,
                                               qint64 duration, qint64 count){
    if (this->progress_anim_->state() == QPropertyAnimation::Running) return;

    this->progress_anim_->setDuration(duration); // Miliseconds, default: 1000ms
    this->progress_anim_->setLoopCount(count);  // loop count of the animation, default: 1 (runs only once)

    this->progress_anim_->setStartValue(start_value);
    this->progress_anim_->setEndValue(end_value);
    this->progress_anim_->start();
};

void CustomProgressBar::stopAnimation(){
    if (this->progress_anim_->state() == QPropertyAnimation::Running ||
        this->progress_anim_->state() == QPropertyAnimation::Paused){
        this->progress_ = 0;
        this->repaint();
        emit stopped();
    }
};

void CustomProgressBar::pauseAnimation(){
    if (this->progress_anim_->state() == QPropertyAnimation::Running){
        this->progress_anim_->pause();
        emit paused();
    }
};

void CustomProgressBar::resumeAnimation(){
    if (this->progress_anim_->state() == QPropertyAnimation::Paused) {
        this->progress_anim_->resume();
        emit resumed();
    }
};

void CustomProgressBar::animateColor(QColor start_value, QColor end_value,
                                     qint64 duration, qint64 count){
    if (this->color_anim_->state() == QPropertyAnimation::Running) return;

    this->color_anim_->setDuration(duration);  // milliseconds , default:1000ms
    this->color_anim_->setLoopCount(count);  // loop count of the animation, default:1 (runs only once)

    this->color_anim_->setStartValue(start_value);
    this->color_anim_->setEndValue(end_value);
    this->color_anim_->start();
};

void CustomProgressBar::animateFlash(qint64 duration, qint64 count){
    if (this->color_anim_->state() == QPropertyAnimation::Running) return;

    this->color_anim_->setDuration(duration);  // milliseconds , default:1000ms
    this->color_anim_->setLoopCount(count);  // loop count of the animation, default:1 (runs only once)

    QColor original_color = progress_color_;
    this->color_anim_->setStartValue(original_color);
    this->color_anim_->setKeyValueAt(0.5, original_color.lighter(200));
    this->color_anim_->setEndValue(original_color.lighter(200));
    this->color_anim_->start();
};

void CustomProgressBar::setProgressVisibity(bool visibility){
    this->progress_visibility_ = visibility;
};

void CustomProgressBar::setProgress(qint64 progress, QString text){
    this->setProgressText_(text);
    this->setProgress_(progress);
};

qint64 CustomProgressBar::getProgress() const{
    return getProgress_();
};

void CustomProgressBar::setTheme(const std::map<QString, QString> &style){
    QColor foreground, background, progress;

    foreground.setNamedColor(style.at("foreground"));
    background.setNamedColor(style.at("background"));
    progress.setNamedColor(style.at("progress"));

    this->bg_color_ = background;
    this->fore_color_ = foreground;
    this->progress_color_ = progress;
    this->repaint();
};


CustomCircularProgressBar::CustomCircularProgressBar(QWidget *parent_)
{
    this->setParent(parent_);

    this->setFixedWidth(100);
    this->setFixedHeight(100);

    this->fore_color_ = GREEN_COLOR;
    this->bg_color_ = FAINT_GREEN_COLOR;
    this->progress_color_ = QColor(137, 218, 103);

    this->progress_text_ = "";

    progress_anim_ = new QPropertyAnimation{this, "progress", this};
    color_anim_ = new QPropertyAnimation{this, "progressColor", this};
}

void CustomCircularProgressBar::paintEvent(QPaintEvent *event_){
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.translate(0, 0);

    int size = qMin<int>(this->width(), this->height());
    qreal elapsed = this->progress_ * 360.0;
    qreal remained = 360.0 - elapsed;

    painter.translate(size/4, size/4);
    painter.fillRect(this->rect(), Qt::transparent);

    QPainterPath path, path2;
    path.moveTo(size/4, 0);
    path.arcTo(QRectF(0, 0, size/2, size/2), 90, -elapsed);

    path2.moveTo(size/4, 0);
    path2.arcTo(QRectF(0, 0, size/2, size/2), 90, remained);

    // Draw Elapsed Percentage
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(this->fore_color_);
    pen.setWidth(8);
    painter.strokePath(path, pen);

    // Draw Remaining Percentage
    QPen pen2;
    pen2.setCapStyle(Qt::FlatCap);
    pen2.setColor(this->bg_color_);
    pen2.setWidth(8);
    painter.strokePath(path2, pen2);

    if (!this->progress_visibility_)
        return;

    // Draw Percentage text
    QRect rect;
    rect.setSize(QSize((int) (size/2), (int) (size/2)));
    rect = rect.adjusted(size, size, -size, -size);
    painter.setPen(this->fore_color_);
    QString text;
    text = QString::number((int) ((int) (this->progress_*100) % 100)) + "%";
    painter.drawText(rect, Qt::AlignCenter, text);
};

QColor CustomCircularProgressBar::getForeColor_() const{
    return this->fore_color_;
};

void CustomCircularProgressBar::setForeColor_(const QColor &color) {
    this->fore_color_ = color; this->repaint();
    this->repaint();
};

QColor CustomCircularProgressBar::getBgColor_() const{
    return this->bg_color_;
};

void CustomCircularProgressBar::setBgColor_(const QColor &color) {
    this->bg_color_ = color; this->repaint();
    this->repaint();
};

QColor CustomCircularProgressBar::getProgressColor_() const{
    return this->progress_color_;
};

void CustomCircularProgressBar::setProgressColor_(const QColor &color){
    this->progress_color_ = color;
    this->repaint();
};

qreal CustomCircularProgressBar::getProgress_() const{
    return this->progress_;
};

void CustomCircularProgressBar::setProgress_(qreal value){
    this->progress_ = value;
    if (this->progress_ == 1.0) emit finished();
    this->repaint();
};

QString CustomCircularProgressBar::getProgressText_() const{
    return this->progress_text_;
};

void CustomCircularProgressBar::setProgressText_(const QString &text){
    this->progress_text_ = text;
    this->repaint();
};

void CustomCircularProgressBar::startProgressAnimation(qreal start_value, qreal end_value,
                                               qint64 duration, qint64 count){
    if (this->progress_anim_->state() == QPropertyAnimation::Running) return;

    this->progress_anim_->setDuration(duration); // Miliseconds, default: 1000ms
    this->progress_anim_->setLoopCount(count);  // loop count of the animation, default: 1 (runs only once)

    this->progress_anim_->setStartValue(start_value);
    this->progress_anim_->setEndValue(end_value);
    this->progress_anim_->start();
};

void CustomCircularProgressBar::stopProgressAnimation(){
    if (this->progress_anim_->state() == QPropertyAnimation::Running ||
        this->progress_anim_->state() == QPropertyAnimation::Paused){
        this->progress_ = 0;
        this->repaint();
        emit stopped();
    }
};

void CustomCircularProgressBar::pauseProgressAnimation(){
    if (this->progress_anim_->state() == QPropertyAnimation::Running){
        this->progress_anim_->pause();
        emit paused();
    }
};

void CustomCircularProgressBar::resumeProgressAnimation(){
    if (this->progress_anim_->state() == QPropertyAnimation::Paused) {
        this->progress_anim_->resume();
        emit resumed();
    }
};

void CustomCircularProgressBar::animateColor(QColor start_value, QColor end_value,
                                     qint64 duration, qint64 count){
    if (this->color_anim_->state() == QPropertyAnimation::Running) return;

    this->color_anim_->setDuration(duration);  // milliseconds , default:1000ms
    this->color_anim_->setLoopCount(count);  // loop count of the animation, default:1 (runs only once)

    this->color_anim_->setStartValue(start_value);
    this->color_anim_->setEndValue(end_value);
    this->color_anim_->start();
};

void CustomCircularProgressBar::animateFlash(qint64 duration, qint64 count){
    if (this->color_anim_->state() == QPropertyAnimation::Running) return;

    this->color_anim_->setDuration(duration);  // milliseconds , default:1000ms
    this->color_anim_->setLoopCount(count);  // loop count of the animation, default:1 (runs only once)

    QColor original_color = progress_color_;
    this->color_anim_->setStartValue(original_color);
    this->color_anim_->setKeyValueAt(0.5, original_color.lighter(200));
    this->color_anim_->setEndValue(original_color.lighter(200));
    this->color_anim_->start();
};

void CustomCircularProgressBar::setProgressVisibity(bool visibility){
    this->progress_visibility_ = visibility;
};

void CustomCircularProgressBar::setProgress(qint64 progress, QString text){
    this->setProgressText_(text);
    this->setProgress_(progress);
};

qint64 CustomCircularProgressBar::getProgress() const{
    return getProgress_();
};

void CustomCircularProgressBar::setTheme(const std::map<QString, QString> &style){
    QColor foreground, background, progress;

    foreground.setNamedColor(style.at("foreground"));
    background.setNamedColor(style.at("background"));
    progress.setNamedColor(style.at("progress"));

    this->bg_color_ = background;
    this->fore_color_ = foreground;
    this->progress_color_ = progress;
    this->repaint();
};
