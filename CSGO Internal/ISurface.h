#pragma once

enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum FONTS
{
	FONT_ESP = 7
};

class Color
{
public:
	int r, g, b, a;
	Color(int R, int G, int B, int A = 255)
	{
		r = R; g = G; b = B; a = A;
	}
	Color()
	{
		r = g = b = 0;
		a = 255;
	}
};

class ISurface
{
public:
	virtual void Func0();
	virtual void Func1();
	virtual void Func2();
	virtual void Func3();
	virtual void Func4();
	virtual void Func5();
	virtual void Func6();
	virtual void Func7();
	virtual void Func8();
	virtual void Func9();
	virtual void Func10();
	virtual void Func11();
	virtual void Func12(int a1, int a2);
	virtual void Func13();
	virtual void Func14();
	virtual void SetDrawColor(int r, int g, int b, int a = 255);
	virtual void DrawFilledRect(int x, int y, int x2, int y2);
	virtual void Func17();
	virtual void DrawOutlinedRect(int x, int y, int x2, int y2);
	virtual void DrawLine(int x1, int y1, int x2, int y2);
	virtual void Func20();
	virtual void Func21();
	virtual void Func22();
	virtual void SetFont(int font);
	virtual void Func24();
	virtual void SetTextColor(int r, int g, int b, int a = 255);
	virtual void SetTextPos(int x, int y);
	virtual void GetTextPos(int& x, int& y);
	virtual void DrawPrintTextEx(const wchar_t* text, int textLength, FontDrawType_t DrawType = FontDrawType_t::FONT_DRAW_DEFAULT);
	virtual void Func29();
	virtual void Func30();
	virtual void Func31();
	virtual void Func32();
	virtual void Func33();
	virtual void Func34();
	virtual void Func35();
	virtual void Func36();
	virtual void Func37();
	virtual void Func38();
	virtual void Func39();
	virtual void Func40();
	virtual void Func41();
	virtual void Func42();
	virtual void Func43();
	virtual void GetScreenSize(int& w, int& h);
	virtual void Func45();
	virtual void Func46();
	virtual void Func47();
	virtual void Func48();
	virtual void Func49();
	virtual void Func50();
	virtual void Func51();
	virtual void Func52();
	virtual void Func53();
	virtual void Func54();
	virtual void Func55();
	virtual void Func56();
	virtual void Func57();
	virtual void Func58();
	virtual void Func59();
	virtual void Func60();
	virtual void Func61();
	virtual void Func62();
	virtual void Func63();
	virtual void Func64();
	virtual void Func65();
	virtual void Func66();
	virtual void Func67();
	virtual void Func68();
	virtual void Func69();
	virtual void Func70();
	virtual void Func71();
	virtual void Func72();
	virtual void Func73();
	virtual void Func74();
	virtual void Func75();
	virtual void Func76();
	virtual void Func77();
	virtual void Func78();
	virtual void Func79();
	virtual void Func80();
	virtual void Func81();
	virtual void Func82();
	virtual void Func83();
	virtual void Func84();
	virtual void Func85();
	virtual void Func86();
	virtual void Func87();
	virtual void Func88();
	virtual void Func89();
	virtual void Func90();
	virtual void Func91();
	virtual void Func92();
	virtual void Func93();
	virtual void Func94();
	virtual void Func95();
	virtual void Func96();
	virtual void Func97();
	virtual void Func98();
	virtual void Func99();
	virtual void Func100();
	virtual void Func101();
	virtual void DrawOutlinedCircle(int x, int y, int rad, int seg);
	virtual void Func102();
	virtual void Func103();
	virtual void Func104();
	virtual void Func105();
	virtual void Func106();
	virtual void Func107();
	virtual void Func108();
	virtual void Func109();
	virtual void Func110();
	virtual void Func111();
	virtual void Func112();
	virtual void Func113();
	virtual void Func114();
	virtual void Func115();
	virtual void Func116();
	virtual void Func117();
	virtual void Func118();
	virtual void Func119();
	virtual void Func120();
	virtual void Func121();
	virtual void Func122();
	virtual void Func123();
	virtual void Func124();
	virtual void Func125();
	virtual void Func126();
	virtual void Func127();
	virtual void Func128();
	virtual void Func129();
	virtual void Func130();
	virtual void Func131();
	virtual void Func132();
	virtual void GetScreenSize(int* w, int* h);

	const void DrawRect(int x, int y, int w, int h)
	{
		DrawFilledRect(x, y, x + w, y + h);
	}

	const void DrawPrintText(const char* text, int x = 0, int y = 0, int font = 293, Color col = Color(255, 255, 255))
	{

		size_t newsize = strlen(text) + 1;
		wchar_t* wcstring = new wchar_t[newsize];

		// Convert char* string to a wchar_t* string.
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wcstring, newsize, text, _TRUNCATE);

		SetTextColor(col.r, col.g, col.b, col.a);
		SetFont(font);
		SetTextPos(x, y);
		DrawPrintTextEx(wcstring, convertedChars);

		delete[] wcstring;
	}
};