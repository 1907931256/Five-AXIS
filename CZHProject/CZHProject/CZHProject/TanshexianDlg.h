#pragma once
#include "ui_TanshexianDlg.h"
#include <QWidget>
#include "QDialog.h"
#include "qmessagebox.h"
class TanshexianDlg :public QDialog
{
	Q_OBJECT
public:
	TanshexianDlg(QWidget* parent = 0);
	virtual ~TanshexianDlg();

	Ui::TancexianDlg *ui_T;

public:
	double angel;
	///////////�ۺ���////////
	public slots :
	           void Linput();
};

