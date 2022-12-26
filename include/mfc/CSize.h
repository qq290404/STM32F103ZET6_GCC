#ifndef __CSIZE_H__
#define __CSIZE_H__

#define PCSIZE_NULL					((CSize *) 0)

class CSize
{
public:
    CSize(void);
    CSize(int, int);

    bool operator ==(CSize &) const;
    bool operator !=(CSize &) const;
    void operator +=(CSize &);
    void operator -=(CSize &);

    CSize operator+(CSize size) const;
    CSize operator-(CSize size) const;

    void SetSize(int x = 0, int y = 0);

private:
    int x;
    int y;
};
#endif // __CSIZE_H__
