#ifndef __C_COMMON_H__
#define __C_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct POINT
{
	int x;
	int y;
};

void SetPoint(struct POINT* ppoint, int x, int y);
void SetPointEmpty(struct POINT* ppoint);
void CopyPoint(struct POINT* pdrc, const struct POINT* psrc);
void OffsetPoint(struct POINT* ppoint, int x, int y);
void PointOut(struct POINT* ppoint);

struct LINE
{
	struct POINT p1;
	struct POINT p2;
};

void SetLine(struct LINE* pline, const struct POINT* pt1, const struct POINT* pt2);
void SetLineEmpty(struct LINE* pline);
void CopyLine(struct LINE* pdrc, const struct LINE* psrc);
bool IsLineNormal(const struct LINE* pline);
void OffsetLine(struct LINE* pline, int x, int y);
bool IntersectLine(struct POINT* ppoint, const struct LINE* psrc1, const struct LINE* psrc2);
void LineOut(struct LINE* pline);

struct RECT
{
	int left;
	int top;
	int right;
	int bottom;
};

void SetRect(struct RECT* prc, int left, int top, int right, int bottom);
void SetRectEmpty(struct RECT* prc);
void CopyRect(struct RECT* pdrc, const struct RECT* psrc);
bool IsRectEmpty(const struct RECT* prc);
bool EqualRect(const struct RECT* prc1, const struct RECT* prc2);
bool IsRectNormal(const struct RECT* prc);
void NormalizeRect(struct RECT* pRect);
bool IsCovered(const struct RECT* prc1, const struct RECT* prc2);
bool IntersectRect(struct RECT* pdrc, const struct RECT* psrc1, const struct RECT* psrc2);
bool DoesIntersect(const struct RECT* psrc1, const struct RECT* psrc2);
bool UnionRect(struct RECT* pdrc, const struct RECT* psrc1, const struct RECT* psrc2);
void GetBoundRect(struct RECT* pdrc,  const struct RECT* psrc1, const struct RECT* psrc2);
int SubtractRect(struct RECT* rc, const struct RECT* psrc1, const struct RECT* psrc2);
void OffsetRect(struct RECT* prc, int x, int y);
void InflateRect(struct RECT* prc, int cx, int cy);
void DeflateRect(struct RECT* prc, int cx, int cy);
void InflateRectToPt(struct RECT* prc, int x, int y);
bool PtInRect(const struct RECT* prc, int x, int y);
void RectOut(struct RECT* prc);

struct RGB
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct BITMAP
{
	int width;
	int height;
	int bits;
	const unsigned char* pBmpBits;
	const unsigned int* pPalette;
};

#ifdef __cplusplus
}
#endif

#endif /* __C_COMMON_H__ */
