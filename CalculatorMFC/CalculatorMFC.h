
// CalculatorMFC.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CCalculatorMFCApp:
// Сведения о реализации этого класса: CalculatorMFC.cpp
//

class CCalculatorMFCApp : public CWinApp
{
public:
	CCalculatorMFCApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CCalculatorMFCApp theApp;
