// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "MFCGlimpretest.h"
#include "CDlgImage.h"
#include "afxdialogex.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{

	InitImage();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgImage::UpdateCoordLabel()
{
	if (m_pParent == nullptr) return;

	CString text;
	if (nNum >= 1) {
		text.AppendFormat(_T("P1(%d,%d) "), Numbers[0].x, Numbers[0].y);
	}
	if (nNum >= 2) {
		text.AppendFormat(_T("P2(%d,%d) "), Numbers[1].x, Numbers[1].y);
	}
	if (nNum >= 3) {
		text.AppendFormat(_T("P3(%d,%d)"), Numbers[2].x, Numbers[2].y);
	}

	if (text.IsEmpty())
		text = _T("좌표 없음");

	m_pParent->SetDlgItemText(IDC_STATIC_XY, text);
}


void CDlgImage::InitImage() {
	int nWidth = 720;
	int nHeight = 640;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbBlue = rgb[i].rgbGreen = rgb[i].rgbRed = i;

		m_image.SetColorTable(0, 256, rgb);
	}

	ResetImage();
}

void CDlgImage::ResetImage()
{
	nNum = 0;
	UpdateCoordLabel();

	const int nWidth = m_image.GetWidth();
	const int nHeight = m_image.GetHeight();
	const int nPitch = m_image.GetPitch(); 

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int y = 0; y < nHeight; ++y)
		memset(fm + y * nPitch, 255, nPitch);

	Invalidate(FALSE);
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_image)
	{
		m_image.Draw(dc, 0, 0);
	}
}


void CDlgImage::ClearImage(int v)
{
	const int nHeight = m_image.GetHeight();
	const int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int y = 0; y < nHeight; ++y)
		memset(fm + y * nPitch, v, nPitch);
}

void CDlgImage::RenderAllCircles()
{
	ClearImage(255); // 배경 흰색
	for (int i = 0; i < nNum; ++i)
		MakeCircle(Numbers[i].x, Numbers[i].y, nRadius, 0);

	GetBorder();

	Invalidate(FALSE);
}

void CDlgImage::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);

	if (isDraging) {
		isDraging = false;
		pDragTarget = nullptr;
		return;
	}

	if (nNum >= 3) return;

	Numbers[nNum] = point;
	++nNum;

	UpdateCoordLabel();
	RenderAllCircles(); 
}


void CDlgImage::MakeCircle(int x, int y, int r, int color)
{
	const int nWidth = m_image.GetWidth();
	const int nHeight = m_image.GetHeight();
	const int nPitch = m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int i = y - r; i < y + r; ++i)
	{
		if (i < 0) continue;
		if (i >= nHeight) break;

		for (int l = x - r; l < x + r; ++l)
		{
			if (l < 0) continue;
			if (l >= nWidth) break;

			if ((x - l) * (x - l) + (y - i) * (y - i) <= r * r)
				fm[i * nPitch + l] = color;
		}
	}
}



void CDlgImage::Random()
{
	const int nWidth = m_image.GetWidth();
	const int nHeight = m_image.GetHeight();

	nNum = 3;
	for (int i = 0; i < nNum; ++i)
	{
		Numbers[i].x = rand() % nWidth;
		Numbers[i].y = rand() % nHeight;
		printf("%d is %d, %d\n", i, Numbers[i].x, Numbers[i].y);
	}

	UpdateCoordLabel();
	RenderAllCircles();
}

void CDlgImage::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	if (point.x < 0 || point.y < 0 || point.x >= nWidth || point.y >= nHeight)
		return;

	int pitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	if (fm[point.y * pitch + point.x] == 255) return;

	// 가장 가까운 점 선택
	int d0 = GetDistance(Numbers[0], point);
	int d1 = GetDistance(Numbers[1], point);
	int d2 = GetDistance(Numbers[2], point);

	int idx = 0;
	int dmin = d0;
	if (d1 < dmin) { dmin = d1; idx = 1; }
	if (d2 < dmin) { dmin = d2; idx = 2; }

	pDragTarget = &Numbers[idx];
	isDraging = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}

int CDlgImage::GetDistance(CPoint& A, CPoint& B)
{
	int dx = A.x - B.x;
	int dy = A.y - B.y;
	return dx * dx + dy * dy;
}



void CDlgImage::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (!isDraging || pDragTarget == nullptr) return;

	*pDragTarget = point; 
	RenderAllCircles();      
	UpdateCoordLabel();

	CDialogEx::OnMouseMove(nFlags, point);
}

bool CDlgImage::FindCenter()
{
	if (nNum < 3) return false;

	double ax = (double)Numbers[0].x, ay = (double)Numbers[0].y;
	double bx = (double)Numbers[1].x, by = (double)Numbers[1].y;
	double cx = (double)Numbers[2].x, cy = (double)Numbers[2].y;

	double d = 2.0 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
	if (d == 0.0) return false; // 원 성립 불가

	double a2 = ax * ax + ay * ay;
	double b2 = bx * bx + by * by;
	double c2 = cx * cx + cy * cy;

	double ux = (a2 * (by - cy) + b2 * (cy - ay) + c2 * (ay - by)) / d;
	double uy = (a2 * (cx - bx) + b2 * (ax - cx) + c2 * (bx - ax)) / d;

	center.x = (int)(ux + (ux >= 0 ? 0.5 : -0.5));
	center.y = (int)(uy + (uy >= 0 ? 0.5 : -0.5));

	double dx = ux - ax;
	double dy = uy - ay;
	nCircleR = (int)(sqrt(dx * dx + dy * dy) + 0.5);

	return (nCircleR > 0);
}

void CDlgImage::DrawBorder()
{
	if (nNum < 3) return;
	if (!FindCenter()) return;

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	if (nPitch < 0) nPitch = -nPitch;

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	double t = (double)nBorder / 2.0;
	double rin = nCircleR - t; if (rin < 0) rin = 0;
	double rout = nCircleR + t;

	double rin2 = rin * rin;
	double rout2 = rout * rout;

	int x0 = (int)floor(center.x - rout) - 1;
	int x1 = (int)ceil(center.x + rout) + 1;
	int y0 = (int)floor(center.y - rout) - 1;
	int y1 = (int)ceil(center.y + rout) + 1;

	if (x0 < 0) x0 = 0;
	if (y0 < 0) y0 = 0;
	if (x1 > nWidth)  x1 = nWidth;
	if (y1 > nHeight) y1 = nHeight;

	for (int y = y0; y < y1; ++y)
	{
		int dy = y - center.y;
		for (int x = x0; x < x1; ++x)
		{
			int dx = x - center.x;
			double d2 = (double)dx * dx + (double)dy * dy;

			if (d2 >= rin2 && d2 <= rout2)
				fm[y * nPitch + x] = 0;
		}
	}
}


void CDlgImage::GetBorder()
{
	if (nNum >= 3) {
		DrawBorder();
	}
}



