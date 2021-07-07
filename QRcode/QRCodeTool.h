#ifndef QRCODETOOL_H
#define QRCODETOOL_H

#include <QObject>
#include <QPainter>
#include "qrcode/qrencode.h"

struct QRCodeInfo
{
	QString content;  //二维码内容
	QString logo;	  //二维码logo
	QSize logoSize = QSize(50, 50); //logo大小
	QSize qrCodeSize = QSize(180, 180); //二维码大小
	QColor codeColor = QColor("#000000"); //二维码颜色
	QColor bgColor = QColor("#ffffff"); //二维码背景颜色
	int borderWidth = 5; //二维码边框宽度
};

class QRCodeTool : public QObject
{
	Q_OBJECT

public:
	explicit QRCodeTool(QObject *parent = nullptr);
	~QRCodeTool();

public:
	//不使用依赖库的二维码接口
	QImage createSquareQrCode(const QRCodeInfo&);
	//使用依赖库的二维码接口
	QPixmap getQrCode(const QString &strData, const QImage &iconImage);

private:
	QRcode* m_pQRCode;
	QImage m_Image;
};

#endif
