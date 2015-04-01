/*!
  Description   : A Waiting Dialog.
  Author        : Ruining Song
  Date          : 2014.1.16
  Remark        :
*/

#ifndef WAITDLG_H
#define WAITDLG_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QPoint>

class QPainter;

class WaitDlg : public QWidget
{
    Q_OBJECT
public:
	enum DisplayMode{IMAGE, TEXT};
    explicit WaitDlg(QWidget *parent);

	void SetDisplayMode(DisplayMode mode);
	void SetText(QString text);
	void SetSize(QSize size);
	void SetOpacity(int opacity);

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void DrawCircle(QPainter* painter);
	virtual void DrawText(QPainter* painter);

private slots:
    void timeout();

private:
    int angle;
    QTimer timer;
    QPoint circleCenter;
	DisplayMode displayMode;
	QString displayText;
	int m_opacity;
};

#endif // WAITDLG_H
