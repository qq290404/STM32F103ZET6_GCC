#ifndef __CPLUSPLUS_STRING_H__
#define __CPLUSPLUS_STRING_H__

#define PCSTRING_NULL					((CString *) 0)

class CString
{
public:
    CString(void);
    CString(const char *);
    CString(const CString &);
    CString(const char , unsigned int nRepeat = 1);
    CString(const char *, unsigned int, unsigned int nBegin = 0);
    CString(const CString &, unsigned int, unsigned int nBegin = 0);

    ~CString(void);

    const char* c_str(void);
    unsigned int GetLength(void) const;
    bool IsEmpty(void);
    void Empty(void);
    char GetAt(unsigned int);
    void SetAt(unsigned int, const char);

    int Compare(const char *);
    int Compare(const CString &);
    int CompareNoCase(const char *);
    int CompareNoCase(const CString &);

    CString Right(unsigned int) const;
    CString Left(unsigned int) const;
    CString Middle(unsigned int, unsigned int) const;

    CString& operator =(const char);
    CString& operator =(const char *);
    CString& operator =(const CString &);
    CString& operator +=(const char);
    CString& operator +=(const char *);
    CString& operator +=(const CString &);
    char operator[](unsigned int) const;

    void MakeUpper(void);
    void MakeLower(void);
    void MakeReverse(void);

    int Replace(const char, const char);
    int Replace(const char *, const char *);

    int Remove(const char);
    int Delete(unsigned int, unsigned int nCount = 1);

    int Insert(unsigned int, const char);
    int Insert(unsigned int, const char *);

    void TrimLeft(void);
    void TrimLeft(const char);
    void TrimLeft(const char *);
    void TrimRight(void);
    void TrimRight(const char);
    void TrimRight(const char *);

    int Find(const char, unsigned int nBegin = 0);
    int Find(const char *, unsigned int nBegin = 0);
    int ReverseFind(const char);
    int FindOneOf(const char *);

    void Format(const char *, ...);

    friend CString operator +(const char, const CString &);
    friend CString operator +(const char *, const CString &);
    friend CString operator +(const CString &, const char);
    friend CString operator +(const CString &, const char *);
    friend CString operator +(const CString &, const CString &);

    friend bool operator ==(const CString &, const CString &);
    friend bool operator ==(const CString &, const char *);
    friend bool operator ==(const char *, const CString &);

    friend bool operator !=(const CString &, const CString &);
    friend bool operator !=(const CString &, const char *);
    friend bool operator !=(const char *, const CString &);

    friend bool operator <(const CString &, const CString &);
    friend bool operator <(const CString &, const char *);
    friend bool operator <(const char *, const CString &);
    friend bool operator >(const CString &, const CString &);
    friend bool operator >(const CString &, const char *);
    friend bool operator >(const char *, const CString &);

    friend bool operator <=(const CString &, const CString &);
    friend bool operator <=(const CString &, const char *);
    friend bool operator <=(const char *, const CString &);
    friend bool operator >=(const CString &, const CString &);
    friend bool operator >=(const CString &, const char *);
    friend bool operator >=(const char *, const CString &);

private:
    char* pString;
};
#endif // __CSTRING_H__
