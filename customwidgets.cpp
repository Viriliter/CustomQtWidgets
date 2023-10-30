#include "customwidgets.h"

CustomFileBrowser::CustomFileBrowser(QWidget *parent_)
{
    this->setParent(parent_);
};

void CustomFileBrowser::clicked_browse_(){};

FastLogViewer::FastLogViewer(QWidget *parent_){
    this->setParent(parent_);

    this->setReadOnly(true);
    this->setMaximumBlockCount(maxLineCount_);
    this->setUndoRedoEnabled(false);

    updateTimer_ = new QTimer{};

    QObject::connect(updateTimer_, SIGNAL(timeout()), this, SLOT(updateContent()));
    updateTimer_->setParent(this);
    updateTimer_->setInterval(this->refrashRate_ / 1000);
    updateTimer_->start();
};

unsigned int FastLogViewer::getMaximumLine_() const{
    return this->maxLineCount_;
};

void FastLogViewer::setMaximumLine_(unsigned int lineCount){
    this->maxLineCount_ = lineCount;
};

void FastLogViewer::setMaximumLine(unsigned int lineCount){
    this->setMaximumLine_(lineCount);
};

void FastLogViewer::setRefreshRate(unsigned int refreshRate){
    if (updateTimer_->isActive()) updateTimer_->stop();

    this->refrashRate_ = refreshRate;
    updateTimer_->setInterval(this->refrashRate_ / 1000);
    updateTimer_->start();
};

void FastLogViewer::addRaw(const QString &newRaw){
    this->bufferedLines.append(newRaw);
};

void FastLogViewer::addRaw(const QList<QString> &newRaws){
    for(auto &newRaw:newRaws){
        this->bufferedLines.append(newRaw);
    }
};

void FastLogViewer::updateContent(){
    if (this->bufferedLines.size() == 0) return;

    this->setUpdatesEnabled(false);
    for(auto &line: this->bufferedLines){
        this->appendPlainText(line + NEWLINE);
    }

    this->bufferedLines.clear();
    this->setUpdatesEnabled(true);
};

void FastLogViewer::clearContent(){
    this->clear();
};
