#ifndef SAMPLEQTABLEWIDGET_H
#define SAMPLEQTABLEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SampleQTableWidget; }
QT_END_NAMESPACE


class QMovie;
class SampleQTableWidget : public QWidget
{
    Q_OBJECT

public:
    SampleQTableWidget(QWidget *parent = nullptr);
    ~SampleQTableWidget();

private:
    QMovie* initializeQtDynamicPictureToCache(const QString& file, const QString& cache) const;

    void updateDynamicPictureForNextFPS(QMovie*, QMovie*);
    void updateHeaderDynamicPictureForNextFPS(QMovie*);
    void updateViewPortDynamicPictureForNextFPS(QMovie*);
private:
    Ui::SampleQTableWidget *ui;
};
#endif // SAMPLEQTABLEWIDGET_H
