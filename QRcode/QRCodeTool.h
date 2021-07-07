#ifndef QRCODETOOL_H
#define QRCODETOOL_H

#include <QObject>
#include <QPainter>
#include "qrcode/qrencode.h"

struct QRCodeInfo
{
	QString content;  //��ά������
	QString logo;	  //��ά��logo
	QSize logoSize = QSize(50, 50); //logo��С
	QSize qrCodeSize = QSize(180, 180); //��ά���С
	QColor codeColor = QColor("#000000"); //��ά����ɫ
	QColor bgColor = QColor("#ffffff"); //��ά�뱳����ɫ
	int borderWidth = 5; //��ά��߿���
};

class QRCodeTool : public QObject
{
	Q_OBJECT

public:
	explicit QRCodeTool(QObject *parent = nullptr);
	~QRCodeTool();

public:
	//��ʹ��������Ķ�ά��ӿ�
	QImage createSquareQrCode(const QRCodeInfo&);
	//ʹ��������Ķ�ά��ӿ�
	QPixmap getQrCode(const QString &strData, const QImage &iconImage);

private:
	QRcode* m_pQRCode;
	QImage m_Image;
};

#endif
