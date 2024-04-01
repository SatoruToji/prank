#include <windows.h> 
#include <windowsx.h>
#include "iostream"
using namespace std;
bool isButtonHovered = false;
HWND buttonNo, buttonYes, text, Answer, Answer2, Answer3, Answer4;

void huy(int i);

void bText(int t, int e, int x, HDC hdc, int b, int c, int k) {
    SetBkColor(hdc, RGB(t, e, x));
    SetTextColor(hdc, RGB(b, c, k));
}

void PAINT(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HBRUSH hBrush = CreateSolidBrush(RGB(36, 36, 36));

    FillRect(hdc, &ps.rcPaint, hBrush);

    //HBRUSH hBrush2 = CreateSolidBrush(RGB(233, 0, 0));

    //SelectObject(hdc, hBrush2);

    //Rectangle(hdc, 300, 300, 200, 200);


    DeleteObject(hBrush);
    //DeleteObject(hBrush2);
    EndPaint(hwnd, &ps);
}

void DRAWITEM(LPDRAWITEMSTRUCT lpDrawItem, const wchar_t* word, HWND button) {
    HDC hdc = lpDrawItem->hDC;
    RECT rc = lpDrawItem->rcItem;

    HBRUSH hBrush = CreateSolidBrush(RGB(36, 36, 36));
    FillRect(hdc, &rc, hBrush);

    bText(36, 36, 36, hdc, 255, 255, 255);

    if (lpDrawItem->hwndItem == button) DrawText(hdc, word, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    DeleteObject(hBrush);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SIZE: {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        int textX = width / 2 - 50;
        int textY = height * 3 / 4;

        int buttonNoX = width / 4 - 50;
        int buttonYesX = width * 3 / 4 - 50;
        int buttonY = height / 3;

        SetWindowPos(buttonNo, NULL, buttonNoX, buttonY, 100, 30, SWP_NOZORDER);
        SetWindowPos(buttonYes, NULL, buttonYesX, buttonY, 100, 30, SWP_NOZORDER);
        SetWindowPos(text, NULL, textX, textY, 100, 30, SWP_NOZORDER);
        break;
    }

    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) {
            MessageBox(hwnd, L"You clicked Yes!", L"Message", MB_OK | MB_ICONINFORMATION);
        }

        if (lParam == (LPARAM)buttonNo) {
            huy(1);
        }
        else if (lParam == (LPARAM)buttonYes) {
            MessageBox(hwnd, L"You clicked Yes!", L"Message", MB_OK | MB_ICONINFORMATION);
        }
        return 0;

    case WM_CTLCOLORSTATIC: {
        HDC hdc = (HDC)wParam;

        bText(36, 36, 36, hdc, 170, 170, 170);

        return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));
    }

    case WM_DRAWITEM: {
        LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
        if (lpDrawItem->hwndItem == buttonYes)
            DRAWITEM(lpDrawItem, L"не пидор", buttonYes);

        if (lpDrawItem->hwndItem == buttonNo)
            DRAWITEM(lpDrawItem, L"Нет", buttonNo);

    }

    case WM_PAINT: {
        PAINT(hwnd);
        break;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK childWnd(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CTLCOLORSTATIC: {
        HDC hdc = (HDC)wParam;

        bText(45, 45, 45, hdc, 170, 170, 170);

        return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));
    }

    case WM_DRAWITEM: {
        LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;

        if (lpDrawItem->hwndItem == Answer)
            DRAWITEM(lpDrawItem, L"Шлюхи аргумент!", Answer);
        if (lpDrawItem->hwndItem == Answer2)
            DRAWITEM(lpDrawItem, L"Аргумент не вечен, пидор обеспечен)", Answer2);;
        if (lpDrawItem->hwndItem == Answer3)
            DRAWITEM(lpDrawItem, L"Пидор мафиозный, твой анал спидозный", Answer3);
        if (lpDrawItem->hwndItem == Answer4)
            DRAWITEM(lpDrawItem, L"Анал мой вечен, твой помечен)", Answer4);
    }

    case WM_COMMAND:
        if (lParam == (LPARAM)Answer)huy(2);
        if (lParam == (LPARAM)Answer2)huy(3);
        if (lParam == (LPARAM)Answer3)huy(4);
        if (lParam == (LPARAM)Answer4)huy(5);

    case WM_PAINT: {
        PAINT(hwnd);
        break;
    }
                 if (msg == WM_CLOSE)return 0;
    default: return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

void huy(int i) {
    const wchar_t name[] = L"childWnd";
    WNDCLASS wc{};
    wc.lpfnWndProc = childWnd;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = name;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, name, L"Dicks", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, NULL, NULL, NULL, NULL);
    if (hwnd != nullptr)ShowWindow(hwnd, SW_SHOW);
    if (i == 1) {
        wchar_t name[] = L"huy";
        Answer = CreateWindow(L"BUTTON", L"Шлюхи аргумент. ", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 60, 35, 350, 30, hwnd, NULL, NULL, NULL);
        text = CreateWindow(L"STATIC", L"хахахха, пидора ответ.", WS_VISIBLE | WS_CHILD | WS_EX_TRANSPARENT | BS_OWNERDRAW, 150, 100, 200, 20, hwnd, NULL, NULL, NULL);
    }
    if (i == 2) {
        Answer2 = CreateWindow(L"BUTTON", L"Аргумент не вечен, пидор обеспечен.", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 60, 35, 350, 30, hwnd, NULL, NULL, NULL);
        text = CreateWindow(L"STATIC", L"Аргумент не нужен, пидор обнаружен)", WS_VISIBLE | WS_CHILD | WS_EX_TRANSPARENT | BS_OWNERDRAW, 100, 100, 350, 20, hwnd, NULL, NULL, NULL);
    }
    if (i == 3) {
        Answer3 = CreateWindow(L"BUTTON", L"Пидор мафиозный, твой анал спидозный", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 60, 35, 350, 30, hwnd, NULL, NULL, NULL);
        text = CreateWindow(L"STATIC", L"Пидор засекречен, твой анал не вечен)))))", WS_VISIBLE | WS_CHILD | WS_EX_TRANSPARENT | BS_OWNERDRAW, 100, 100, 350, 20, hwnd, NULL, NULL, NULL);
    }
    if (i == 4) {
        Answer4 = CreateWindow(L"BUTTON", L"Анал мой вечен, твой помечен)", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 60, 35, 350, 30, hwnd, NULL, NULL, NULL);
        text = CreateWindow(L"STATIC", L"Аргумент не вечен, в твоей жопе huy овечий)", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 60, 100, 350, 30, hwnd, NULL, NULL, NULL);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"winda";

    WNDCLASS wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Dick", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, NULL, NULL, hInstance, NULL);
    if (hwnd != NULL) ShowWindow(hwnd, nCmdShow);

    buttonNo = CreateWindow(L"BUTTON", L"Нет", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 60, 35, 100, 30, hwnd, NULL, hInstance, NULL);
    buttonYes = CreateWindow(L"BUTTON", L"Да", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 230, 35, 100, 30, hwnd, NULL, hInstance, NULL);
    text = CreateWindow(L"STATIC", L"Ты пидор?", WS_VISIBLE | WS_CHILD | WS_EX_TRANSPARENT | BS_OWNERDRAW, 150, 100, 200, 20, hwnd, NULL, hInstance, NULL);

    MSG msg{};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}