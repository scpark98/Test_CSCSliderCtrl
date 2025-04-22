
// Test_CSCSliderCtrlDlg.h: 헤더 파일
//

#pragma once

#include "../../Common/ResizeCtrl.h"
#include "../../Common/CSliderCtrl/SCSliderCtrl/SCSliderCtrl.h"
#include "../../Common/CProgressCtrl/MacProgressCtrl/MacProgressCtrl.h"

// CTestCSCSliderCtrlDlg 대화 상자
class CTestCSCSliderCtrlDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestCSCSliderCtrlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CResizeCtrl		m_resize;
	LRESULT			on_message_CSCSliderCtrl(WPARAM wParam, LPARAM lParam);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_CSCSLIDERCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSCSliderCtrl m_slider;
	CMacProgressCtrl m_progress;
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	CButton m_check_hide_thumb;
	afx_msg void OnBnClickedCheckHideThumb();
	CButton m_check_disable;
	afx_msg void OnBnClickedCheckDisable();
	CButton m_check_forced_gray;
	afx_msg void OnBnClickedCheckForcedGray();
};
