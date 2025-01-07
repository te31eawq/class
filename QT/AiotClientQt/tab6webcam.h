#ifndef TAB6WEBCAM_H
#define TAB6WEBCAM_H

#include <QWidget>

namespace Ui {
class Tab6WebCam;
}

class Tab6WebCam : public QWidget
{
    Q_OBJECT

public:
    explicit Tab6WebCam(QWidget *parent = nullptr);
    ~Tab6WebCam();

private:
    Ui::Tab6WebCam *ui;
};

#endif // TAB6WEBCAM_H
