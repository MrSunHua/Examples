#include "sampleqtablewidget.h"
#include "ui_sampleqtablewidget.h"

#include <QDebug>

//#define Q_SAMPLE_BACKGROUND_GIF
#define Q_SAMPLE_BACKGROUND_STATIC_PICTURE

#if defined(Q_SAMPLE_BACKGROUND_GIF)
# include <QDir>
# include <QTimer>
# include <QMovie>
#endif

SampleQTableWidget::SampleQTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SampleQTableWidget)
{
    ui->setupUi(this);

    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->tableWidget->horizontalHeader()->setMinimumHeight(120);
    this->ui->tableWidget->setRowCount(10);
#if defined(Q_SAMPLE_BACKGROUND_STATIC_PICTURE)
    //QString url = QString("QWidget#%1{border-image: url(%2.png);}")
    this->ui->tableWidget->horizontalHeader()->setStyleSheet("border-image: url(:/static/resources/static_byk_viewport_bk_01.jpg);");

    QString url = QString("QWidget#%1{border-image: url(%2);}")
            .arg(this->ui->tableWidget->viewport()->objectName())
            .arg(":/static/resources/static_byk_viewport_bk_02.jpg");
    this->ui->tableWidget->viewport()->setStyleSheet(url);
#endif

#if defined(Q_SAMPLE_BACKGROUND_GIF)
    /**
      Split the dynamic image into static multi frame images and cache them in the cache folder under the working directory.
     */
    auto movie = this->initializeQtDynamicPictureToCache(":/dynamic/resources/dynamic_byk_viewport_bk_01.webp", "cache");
    auto movie_header = this->initializeQtDynamicPictureToCache(":/dynamic/resources/dynamic_byk_viewport_bk_02.webp", "cache_header");

    // The timer circularly updates the static picture of the corresponding frame cached by the dynamic picture to achieve
    // the effect of static picture to dynamic picture.
    QTimer* renderBkTimer = new QTimer();
    connect(renderBkTimer, &QTimer::timeout, this, [=](){

        this->updateDynamicPictureForNextFPS(movie_header, movie);
    });
    renderBkTimer->start(60);
#endif
}

SampleQTableWidget::~SampleQTableWidget()
{
    delete ui;
}

QMovie* SampleQTableWidget::initializeQtDynamicPictureToCache(const QString &file, const QString &cache) const
{
#if defined(Q_SAMPLE_BACKGROUND_GIF)
    QDir dir(QDir::currentPath());
    if(dir.exists(cache))
    {
        dir.rmdir(cache);
    }
    dir.mkdir(cache);
    dir.setPath(cache);
    QMovie* movie = new QMovie(file);
    movie->setCacheMode(QMovie::CacheAll);
    for(auto index = 0; index < movie->frameCount(); ++index)
    {
        movie->jumpToFrame(index);
        movie->currentImage().save(QString("%1/%2.png").arg(dir.absolutePath()).arg(index));
    }
    return movie;
#else
    Q_UNUSED(file)
    Q_UNUSED(cache)
    return nullptr;
#endif
}

void SampleQTableWidget::updateDynamicPictureForNextFPS(QMovie* header, QMovie* viewPort)
{
    this->updateHeaderDynamicPictureForNextFPS(header);
    this->updateViewPortDynamicPictureForNextFPS(viewPort);
}

void SampleQTableWidget::updateHeaderDynamicPictureForNextFPS(QMovie* movie)
{
#if defined(Q_SAMPLE_BACKGROUND_GIF)
    if(nullptr == movie)
    {
        return;
    }
    static int index = 0;
    if(index < movie->frameCount())
    {
        QString url = QString("QWidget#%1{border-image: url(%2.png);}")
                .arg(this->ui->tableWidget->viewport()->objectName())
                .arg(QDir::current().absoluteFilePath("cache/" + QString::number(index)));

        this->ui->tableWidget->viewport()->setStyleSheet(url);
    }
    if(++index >= movie->frameCount())
    {
        index = 0;
    }
#else
    Q_UNUSED(movie)
#endif
}

void SampleQTableWidget::updateViewPortDynamicPictureForNextFPS(QMovie* movie)
{
#if defined(Q_SAMPLE_BACKGROUND_GIF)
    if(nullptr == movie)
    {
        return;
    }
    static int index = 0;
    if(index < movie->frameCount())
    {
        QString url = QString("border-image: url(%1.png);")
                .arg(QDir::current().absoluteFilePath("cache_header/" + QString::number(index)));

        this->ui->tableWidget->horizontalHeader()->setStyleSheet(url);
    }
    if(++index >= movie->frameCount())
    {
        index = 0;
    }
#else
    Q_UNUSED(movie)
#endif
}
