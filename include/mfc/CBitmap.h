#ifndef __CPLUSPLUS_BITMAP_H__
#define __CPLUSPLUS_BITMAP_H__

#include <cstdlib>
#define PCBITMAP_NULL					((CBitmap *) 0)

class CBitmap
{
public:
	enum bitmap_bits_e
	{
		bitmap_bits_1,
		bitmap_bits_2,
		bitmap_bits_4,
		bitmap_bits_8,
		bitmap_bits_16,
		bitmap_bits_24,
		bitmap_bits_32,
		bitmap_bits_max,
	};
public:
    CBitmap(void);
    CBitmap(int width, int height, int bits, const unsigned char* pBmpBits, const unsigned int* pPalette = NULL);
    ~CBitmap(void);

public:
	int GetWidth(void)	{ return this->width; }
	int GetHeight(void)	{ return this->height; }

public:
	void SetBitmap(int width, int height, int bits, const unsigned char* pBmpBits, const unsigned int* pPalette);
	unsigned int At(unsigned int index);
	unsigned int At(unsigned int x, unsigned int y);

public:
	unsigned int operator[](unsigned int);

private:
	unsigned int GetColorDataForm1bpp(unsigned int index);
	unsigned int GetColorDataForm2bpp(unsigned int index);
	unsigned int GetColorDataForm4bpp(unsigned int index);
	unsigned int GetColorDataForm8bpp(unsigned int index);
	unsigned int GetColorDataForm16bpp(unsigned int index);
	unsigned int GetColorDataForm24bpp(unsigned int index);
	unsigned int GetColorDataForm32bpp(unsigned int index);

private:
	int width;
	int height;
	int bits;
	const unsigned char* pBmpBits;
	const unsigned int* pPalette;
};
#endif // __CPLUSPLUS_BITMAP_H__
