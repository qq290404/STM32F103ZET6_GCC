#ifndef __CPLUSPLUS_RECT_H__
#define __CPLUSPLUS_RECT_H__

#define PCRECT_NULL								((CRect *) 0)

class CRect
{
public:
    CRect(void);
    CRect(int left, int top, int right, int bottom);
    ~CRect(void);

public:
    inline int get_rect_left(void)const				{	return left;		}
    inline int get_rect_top(void)const				{	return top;			}
    inline int get_rect_right(void)const			{	return right;		}
    inline int get_rect_bottom(void)const			{	return bottom;		}

    inline void set_rect_left(int left)				{	this->left = left;		}
    inline void set_rect_top(int top)				{	this->top 	= top;		}
    inline void set_rect_right(int right)			{	this->right = right;	}
    inline void set_rect_bottom(int bottom)         {	this->bottom = bottom;	}

private:
    int left;
    int top;
    int right;
    int bottom;
};
#endif /* __CRECT_H__ */

