#include "QRCodeTool.h"
#include <QDebug>
#include "qr.h"

QRCodeTool::QRCodeTool(QObject *parent)
	: QObject(parent)
{

}

QRCodeTool::~QRCodeTool()
{
   
}

QImage QRCodeTool::createSquareQrCode(const QRCodeInfo& info)
{
	QString content = info.content;
    m_pQRCode = QRcode_encodeString(content.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 1);
    if (nullptr == m_pQRCode)
    {
        return QImage();
    }
    qint32 temp_width = info.qrCodeSize.width() - info.borderWidth * 2;
    qint32 temp_height = info.qrCodeSize.height() - info.borderWidth * 2;
    qint32 qrcode_width = m_pQRCode->width > 0 ? m_pQRCode->width : 1;
    double scale_x = (double)temp_width / (double)qrcode_width;
    double scale_y = (double)temp_height / (double)qrcode_width;
    m_Image = QImage(info.qrCodeSize.width(), info.qrCodeSize.height(), QImage::Format_ARGB32);
    QPainter painter(&m_Image);

    QColor background(info.bgColor);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, info.qrCodeSize.width(), info.qrCodeSize.height());
    QColor foreground(info.codeColor); // 二维码颜色
    painter.setBrush(foreground);
    for (qint32 y = 0; y < qrcode_width; y++)
    {
        for (qint32 x = 0; x < qrcode_width; x++)
        {
            unsigned char b = m_pQRCode->data[y * qrcode_width + x];
            if (b & 0x01)
            {
                QRectF r(x * scale_x + info.borderWidth, y * scale_y + info.borderWidth, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
    delete[] m_pQRCode;
	if (info.logo.isEmpty()) {
		return m_Image;
	}
	int logoWidth = info.logoSize.width();
    //绘制二维码Logo
    QColor logoBg(info.bgColor);
    painter.setBrush(logoBg);
    painter.setPen(Qt::NoPen);
    painter.drawRect((info.qrCodeSize.width() - logoWidth) / 2, (info.qrCodeSize.height() - logoWidth) / 2, logoWidth, logoWidth);

    QPixmap logoPixmap;
    logoPixmap.load(info.logo);
    logoPixmap = logoPixmap.scaled(logoWidth - info.borderWidth, logoWidth - info.borderWidth);
    painter.drawPixmap((info.qrCodeSize.width() - logoWidth + info.borderWidth) / 2, (info.qrCodeSize.height() - logoWidth + info.borderWidth) / 2, logoPixmap);

    return m_Image;
}

QPixmap QRCodeTool::getQrCode(const QString & strData, const QImage & iconImage)
{
	QPixmap pixMap = QPixmap();
	//qrInit的5个参数分别是version,mode,纠错等级和掩码，使用过程中使用除了QR_EM_8BIT以外的mode会生成不正常的二维码，暂时不知道原因。
	int errcode = QR_ERR_NONE;
	QRCode* p = qrInit(5, QR_EM_8BIT, 1, -1, &errcode);

	qrAddData(p, (const qr_byte_t *)strData.toStdString().data(), strData.toStdString().length());

	if (!qrFinalize(p))
	{
		qInfo() << "error" << qrFinalize(p);
		return pixMap;
	}
	int size = 0;
	qr_byte_t * buffer = qrSymbolToBMP(p, 1, 5, &size);

	if (buffer != NULL)
	{
		QImage mapImage = QPixmap::fromImage(QImage::fromData(buffer, size)).toImage();
		//图片与icon处理
		int posX = (mapImage.width() - iconImage.width()) / 2;
		int posY = (mapImage.height() - iconImage.height()) / 2;
		QPainter painter;
		painter.begin(&mapImage);
		painter.drawImage(posX, posY, iconImage);
		painter.end();
		pixMap = QPixmap::fromImage(mapImage);
	}
	return pixMap;
}
