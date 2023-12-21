/*
Лабораторная работа №6.
Создание оконного приложения.
Лабораторная работа №3.
Стандартные элементы управления.
9. Разработать приложение, реализующее калькулятор. Приложение должно
иметь три строки редактирования (для двух операндов и результата). Набор
переключателей-радио кнопок определяет, какое арифметическое действие
необходимо выполнить: суммирование, вычитание, деление, умножение, очистку
окон редактирования. Калькулятор должен сохранять историю операций и
возможность выбора любой операции из истории.
*/

// CalculatorMFCDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "CalculatorMFC.h"
#include "CalculatorMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CCalculatorMFCDlg



CCalculatorMFCDlg::CCalculatorMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATORMFC_DIALOG, pParent)
	, number1(0)
	, number2(0)
	, result(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, number1);
	DDX_Text(pDX, IDC_EDIT2, number2);
	DDX_Text(pDX, IDC_EDIT3, result);
}

BEGIN_MESSAGE_MAP(CCalculatorMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CCalculatorMFCDlg::OnBnClickedButtonCalculate)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorMFCDlg::OnBnClickedButtonClear)
	ON_LBN_SELCHANGE(IDC_LIST_HISTORY, &CCalculatorMFCDlg::OnLbnSelchangeListHistory)
END_MESSAGE_MAP()


// Обработчики сообщений CCalculatorMFCDlg

BOOL CCalculatorMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Инициализация ListBox
	m_listHistory.SubclassDlgItem(IDC_LIST_HISTORY, this);

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CCalculatorMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCalculatorMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCalculatorMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorMFCDlg::AddToHistory(const CString& operation)
{
	m_listHistory.AddString(operation);
}

void CCalculatorMFCDlg::OnBnClickedButtonCalculate()
{
	// Получение операндов и оператора для выполнения операции
	CString operand1, operand2, operation;
	GetDlgItemText(IDC_EDIT1, operand1);
	GetDlgItemText(IDC_EDIT2, operand2);

	// Получение выбранного переключателя
	UINT checkedRadioButton = GetCheckedRadioButton(IDC_RADIO_PLUS, IDC_RADIO_DIVIDE);

	// Определение оператора на основе выбранного переключателя
	switch (checkedRadioButton)
	{
	case IDC_RADIO_PLUS:
		operation = "+";
		break;
	case IDC_RADIO_MINUS:
		operation = "-";
		break;
	case IDC_RADIO_MULTIPLY:
		operation = "*";
		break;
	case IDC_RADIO_DIVIDE:
		operation = "/";
		break;
	default:
		// Обработка ошибки, если ни один переключатель не выбран
		MessageBox(_T("Ошибка: Оператор не выбран!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
		return;
	}

	// Выполнение операции и получение результата
	double result = 0.0;
	if (operation == "+")
	{
		result = _ttof(operand1) + _ttof(operand2);
	}
	else if (operation == "-")
	{
		result = _ttof(operand1) - _ttof(operand2);
	}
	else if (operation == "*")
	{
		result = _ttof(operand1) * _ttof(operand2);
	}
	else if (operation == "/")
	{
		if (_ttof(operand2) != 0.0)
		{
			result = _ttof(operand1) / _ttof(operand2);
		}
		else
		{
			// Обработка деления на ноль
			MessageBox(_T("Ошибка: Деление на нуль!"), _T("Ошибка"), MB_OK | MB_ICONERROR);
			return;
		}
	}

	// Формирование строки операции для добавления в ListBox
	CString operationString;
	operationString.Format(_T("%s %s %s = %.2f"), operand1, operation, operand2, result);

	// Добавление операции в ListBox
	AddToHistory(operationString);

	// Отображение результата на диалоговом окне
	CString resultString;
	resultString.Format(_T("%.2f"), result);
	SetDlgItemText(IDC_EDIT3, resultString);
}



void CCalculatorMFCDlg::OnBnClickedButtonClear()
{
	// TODO: добавьте свой код обработчика уведомлений

	UpdateData(TRUE);

	if (IDC_EDIT1 != NULL || IDC_EDIT2 != NULL || IDC_EDIT2 != NULL)
	{
		number1 = NULL;
		number2 = NULL;
		result = NULL;
	}

	CButton* pButtonPlus = static_cast<CButton*>(GetDlgItem(IDC_RADIO_PLUS));
	CButton* pButtonMinus = static_cast<CButton*>(GetDlgItem(IDC_RADIO_MINUS));
	CButton* pButtonMultiply = static_cast<CButton*>(GetDlgItem(IDC_RADIO_MULTIPLY));
	CButton* pButtonDivide = static_cast<CButton*>(GetDlgItem(IDC_RADIO_DIVIDE));

	pButtonPlus->SetCheck(BST_UNCHECKED);
	pButtonMinus->SetCheck(BST_UNCHECKED);
	pButtonMultiply->SetCheck(BST_UNCHECKED);
	pButtonDivide->SetCheck(BST_UNCHECKED);

	m_listHistory.ResetContent(); // Очистка содержимого ListBox

	UpdateData(FALSE);
}


void CCalculatorMFCDlg::OnLbnSelchangeListHistory()
{
	// TODO: добавьте свой код обработчика уведомлений
	
	CListBox* pListBox = static_cast<CListBox*>(GetDlgItem(IDC_LIST_HISTORY));
	if (pListBox)
	{
		int selectedIndex = pListBox->GetCurSel();
		if (selectedIndex != LB_ERR)
		{
			CString selectedText;
			pListBox->GetText(selectedIndex, selectedText);

			// Разделение строки на операнды и результат
			CString operand1, operand2, result, operation;
			int equalIndex = selectedText.Find(L" ");
			if (equalIndex != -1)
			{
				// Извлечение первого операнда
				operand1 = selectedText.Left(equalIndex);
				operand1.Trim();

				CString expression = selectedText.Mid(equalIndex + 1);
				expression.Trim();

				// Извлечение операции и второго операнда
				int spaceIndex = expression.Find(L" ");
				if (spaceIndex != -1)
				{
					operation = expression.Left(spaceIndex);
					operation.Trim();
					expression = expression.Mid(spaceIndex + 1);

					operand2 = expression.Left(expression.Find(L" "));
					operand2.Trim();

					// Извлечение результата
					result = expression.Mid(expression.Find(L"=") + 1);
					result.Trim();
				}
			}

			// Вставка значений в соответствующие поля
			SetDlgItemText(IDC_EDIT1, operand1);
			SetDlgItemText(IDC_EDIT2, operand2);
			SetDlgItemText(IDC_EDIT3, result);

			// Выбор соответствующей радио-кнопки и снятие выбора с остальных
			CButton* pButtonPlus = static_cast<CButton*>(GetDlgItem(IDC_RADIO_PLUS));
			CButton* pButtonMinus = static_cast<CButton*>(GetDlgItem(IDC_RADIO_MINUS));
			CButton* pButtonMultiply = static_cast<CButton*>(GetDlgItem(IDC_RADIO_MULTIPLY));
			CButton* pButtonDivide = static_cast<CButton*>(GetDlgItem(IDC_RADIO_DIVIDE));

			if (operation == L"+")
			{
				pButtonPlus->SetCheck(BST_CHECKED);
				pButtonMinus->SetCheck(BST_UNCHECKED);
				pButtonMultiply->SetCheck(BST_UNCHECKED);
				pButtonDivide->SetCheck(BST_UNCHECKED);
			}
			else if (operation == L"-")
			{
				pButtonPlus->SetCheck(BST_UNCHECKED);
				pButtonMinus->SetCheck(BST_CHECKED);
				pButtonMultiply->SetCheck(BST_UNCHECKED);
				pButtonDivide->SetCheck(BST_UNCHECKED);
			}
			else if (operation == L"*")
			{
				pButtonPlus->SetCheck(BST_UNCHECKED);
				pButtonMinus->SetCheck(BST_UNCHECKED);
				pButtonMultiply->SetCheck(BST_CHECKED);
				pButtonDivide->SetCheck(BST_UNCHECKED);
			}
			else if (operation == L"/")
			{
				pButtonPlus->SetCheck(BST_UNCHECKED);
				pButtonMinus->SetCheck(BST_UNCHECKED);
				pButtonMultiply->SetCheck(BST_UNCHECKED);
				pButtonDivide->SetCheck(BST_CHECKED);
			}
		}
	}
}
