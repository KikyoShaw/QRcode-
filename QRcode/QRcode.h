#pragma once

#include <QtWidgets/QWidget>
#include "QRCodeTool.h"
#include "ui_QRcode.h"

class QRcodeTest : public QWidget
{
    Q_OBJECT

public:
	QRcodeTest(QWidget *parent = Q_NULLPTR);
	~QRcodeTest();

private slots:
	void sltCreateQRcodeNoDLL();
	void sltCreateQRcodeByDLL();

private:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::QRcodeClass ui;
	//�����ƶ�����ֵ
	QPoint m_point;
	volatile bool m_bMove = false;
	//��ά�빤����
	QRCodeTool m_qrCodeTool;
};
