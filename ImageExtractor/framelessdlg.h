#ifndef FramelessDlg_H
#define FramelessDlg_H

#include <QtGui>
#include <QPixmap>

#define MIN_BUTTON		0x00000001L
#define CLOSE_BUTTON	0x00000002L
#define MENU_BUTTON		0x00000004L
#define SUB_TITLE		0x00000008L

class FramelessDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit FramelessDlg(QWidget *parent, unsigned int flag = MIN_BUTTON | CLOSE_BUTTON | MENU_BUTTON | SUB_TITLE );
    ~FramelessDlg();

public:
    void SetDlg(QWidget* dlg);

public slots:
	void SetTitle(QString title);
	void SetCloseEnable(bool enable);
	void AddMenuAction(QAction* action);
	void RemoveMenuAction(QAction* action);
	void AddSubMenu(QMenu* menu);
	void SetSubTitle(QString subTitle);
	void Resize(QSize size);
	void CenterWindow();

protected:
    void paintEvent(QPaintEvent *e);
    void showEvent(QShowEvent *e);
	bool winEvent(MSG *msg, long *result);

private:
	void InitTitleBar();

private:
    QPixmap m_shadow;
	QLabel* m_title;
	QLabel* m_subTitle;
	QToolButton* m_closeBtn;
	QMenu* m_menu;
	unsigned int m_flag;
};

#endif // FramelessDlg_H
