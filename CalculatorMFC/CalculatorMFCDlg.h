
// CalculatorMFCDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CCalculatorMFCDlg
class CCalculatorMFCDlg : public CDialogEx
{
// Создание
public:
	CCalculatorMFCDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATORMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	CListBox m_listHistory;

	void AddToHistory(const CString& operation); // Объявление метода AddToHistory()

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double number1;
	double number2;
	double result;
	afx_msg void OnBnClickedButtonCalculate();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnLbnSelchangeListHistory();
};
