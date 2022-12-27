#ifndef __CPLUSPLUS_RGB_H__
#define __CPLUSPLUS_RGB_H__

class CRGB
{
public:
    CRGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
    ~CRGB(void);

public:
    void SetHue(int val);
    void SetBri(int val);
    void SetSat(int val);

public:
    inline int Red(void) { return r; }
    inline int Green(void) { return g; }
    inline int Blue(void) { return b; }
    inline int Alpha(void) { return a; }

    inline void SetRGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    static inline CRGB Gray(unsigned char r, unsigned char g, unsigned char b)
    {
        unsigned char gray = (r * 11 + g * 16 + b * 5)/32;
        return CRGB(gray, gray, gray);
    }
    inline CRGB Gray(void)
    { return CRGB::Gray(Red(), Green(), Blue()); }

    inline bool IsGray(void)
    { return Red() == Green() && Red() == Blue(); }

    CRGB& operator =(const CRGB& rgb)
    {
        this->r = rgb.r;
        this->g = rgb.g;
        this->b = rgb.b;
        this->a = rgb.a;
        return *this;
    }

    CRGB& operator +=(const CRGB& rgb)
    {
        unsigned char a1 = (this->a);
        unsigned char a2 = (rgb.a);
        unsigned char r1 = (this->r);
        unsigned char r2 = (rgb.r);
        unsigned char g1 = (this->g);
        unsigned char g2 = (rgb.g);
        unsigned char b1 = (this->b);
        unsigned char b2 = (rgb.b);

        if(a1 == 0 && a2 == 0) {
            return *this;
        }
        this->a = (a1 + a2 - (a1 * a2) / 255);
        this->r = (r1 * a1 + r2 * a2 - (r1 * a1 * a2) / 255) / (this->a);
        this->g = (g1 * a1 + g2 * a2 - (g1 * a1 * a2) / 255) / (this->a);
        this->b = (b1 * a1 + b2 * a2 - (b1 * a1 * a2) / 255) / (this->a);
        return *this;
    }

    CRGB& operator -=(const CRGB& rgb)
    {
        unsigned char a1 = (this->a);
        unsigned char a2 = (rgb.a);
        unsigned char r1 = (this->r);
        unsigned char r2 = (rgb.r);
        unsigned char g1 = (this->g);
        unsigned char g2 = (rgb.g);
        unsigned char b1 = (this->b);
        unsigned char b2 = (rgb.b);

        if(a1 < a2) {
            this->a = 0;
            this->r = 0;
            this->g = 0;
            this->b = 0;
            return *this;
        }
        this->a = ((a1 - a2) * 255)/(255 - a2);
        this->r = (((r1 * a1) - (r2 * a2) + (r2 * a2 * this->a) / 255) / 255);
        this->g = (((g1 * a1) - (g2 * a2) + (g2 * a2 * this->a) / 255) / 255);
        this->b = (((b1 * a1) - (b2 * a2) + (b2 * a2 * this->a) / 255) / 255);
        return *this;
    }

    operator unsigned int() const
    {
        #define GBRA(G, B, R, A) (unsigned int)(((unsigned int)(A & 0xFF) << 24) | ((unsigned int)(R & 0xFF) << 16) | ((unsigned int)(G & 0xFF) << 8) | ((unsigned int)(B & 0xFF)));
        return GBRA(g, b, r, a);
    }

    friend CRGB operator +(const CRGB &, const CRGB &);
    friend CRGB operator -(const CRGB &, const CRGB &);

private:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

#endif
