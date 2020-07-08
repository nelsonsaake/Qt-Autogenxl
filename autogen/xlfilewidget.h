#ifndef XLFILE_H
#define XLFILE_H

#include <QFileInfo>
#include <QWidget>

namespace Ui {
class xlFile;
}

class XlFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XlFileWidget(QWidget *parent = nullptr);
    ~XlFileWidget();

    void loadDataToUi();
    void saveUiData();

    QString get() const;
    void set(const QString &value);

private slots:
    void on_save_clicked();

signals:
    void updated();

private:
    Ui::xlFile *ui;
    QString filePath;
};

#endif // XLFILE_H
