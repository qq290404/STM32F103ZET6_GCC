#ifndef __CPOINT_H__
#define __CPOINT_H__

#define PCPOINT_NULL					((CPoint *) 0)

class CPoint
{
public:
    CPoint(void);
    CPoint(int, int);
    ~CPoint(void);

public:
    void SetPoint(int, int);
    void SetPoint(const CPoint &);
    void SetX(int);
    void SetY(int);
    int GetX(void) const;
    int GetY(void) const;
    void Offset(int, int);
    void Offset(const CPoint &);
    bool operator !=(const CPoint &) const;
    bool operator ==(const CPoint &) const;

private:
    int x;
    int y;
};

#endif // __CPOINT_H__
