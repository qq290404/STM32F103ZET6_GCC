#ifndef __CPLUSPLUS_LINE_H__
#define __CPLUSPLUS_LINE_H__

#define PCLINE_NULL					((CLine *) 0)

class CPoint;

class CLine
{
public:
    CLine(void);
    CLine(const CPoint &, const CPoint &);
};
#endif // __CLINE_H__
