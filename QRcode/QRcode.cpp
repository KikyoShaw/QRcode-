#include "QRcode.h"
#include <QMouseEvent>
#include <QMessageBox>

QRcodeTest::QRcodeTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	ui.lineEdit->setText("https://blog.csdn.net/qq_36651243");

	connect(ui.pushButton_close, &QPushButton::clicked, this, &QWidget::close);
	connect(ui.pushButton_qrcode, &QPushButton::clicked, this, &QRcodeTest::sltCreateQRcodeNoDLL);
	connect(ui.pushButton_dll, &QPushButton::clicked, this, &QRcodeTest::sltCreateQRcodeByDLL);
}

QRcodeTest::~QRcodeTest()
{
}

void QRcodeTest::sltCreateQRcodeNoDLL()
{
	QString strText = ui.lineEdit->text();
	if (strText.isEmpty()) {
		QMessageBox::information(NULL, QStringLiteral("��ʾ"), QStringLiteral("��Ҫ��װ�Ķ�ά�����ݲ���Ϊ��"));
		return;
	}
	QRCodeInfo info;
	info.content = strText;
	info.qrCodeSize = QSize(200, 200);
	//��������logo��Ĭ��Ϊ�վͺ�
	info.logo = ":/QRcode/qrc/logo1.png";
	info.logoSize = QSize(60, 60);
	QImage codeImage = m_qrCodeTool.createSquareQrCode(info);
	QPixmap qrCode = QPixmap::fromImage(codeImage);
	if (!qrCode.isNull()) {
		ui.label_image->setPixmap(qrCode);
	}
}

void QRcodeTest::sltCreateQRcodeByDLL()
{
	QString strText = ui.lineEdit->text();
	if (strText.isEmpty()) {
		QMessageBox::information(NULL, QStringLiteral("��ʾ"), QStringLiteral("��Ҫ��װ�Ķ�ά�����ݲ���Ϊ��"));
		return;
	}
	//��������logo��Ĭ��Ϊ�վͺ�
	QPixmap qrCode = m_qrCodeTool.getQrCode(strText, QImage(":/QRcode/qrc/logo2.png"));
	if (!qrCode.isNull()) {
		ui.label_image->setPixmap(qrCode);
	}
}

void QRcodeTest::mouseMoveEvent(QMouseEvent * event)
{
	//�ж�����Ƿ񱻰��£�ֻ����������ˣ��䷵��ֵ����1(true)
	if ((event->buttons() & Qt::LeftButton) && m_bMove)
	{
		move(event->globalPos() - m_point);
	}
	QWidget::mouseMoveEvent(event);
}

void QRcodeTest::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bMove = true;
		m_point = event->globalPos() - frameGeometry().topLeft();
	}
	QWidget::mousePressEvent(event);
}

void QRcodeTest::mouseReleaseEvent(QMouseEvent * event)
{
	m_bMove = false;
	QWidget::mouseReleaseEvent(event);
}
