#ifndef __GUN_ATTRIBUTE_H__
#define __GUN_ATTRIBUTE_H__

#define __set_attribute__(param)	__attribute__(param)

#define __pragma_section(param) 	__set_attribute__((section(param)))

#define __pragma_aligned(param) 	__set_attribute__((aligned (param)))

#define __pragma_at(param)			__set_attribute__((at(param)))

#define __pragma_format(fmt, m, n)	__set_attribute__((format(fmt, m, n)))

#define __pragma_packed 			__set_attribute__((__packed__))

#define __pragma_noreturn 			__set_attribute__((noreturn))

#define __pragma_const				__set_attribute__((const))

#define __pragma_constructor 		__set_attribute__((constructor))

#define __pragma_destructor			__set_attribute__((destructor))

#define __pragma_always_inline		__set_attribute__((always_inline)) 

#define __pragma_used	        	__set_attribute__((used))

#define __pragma_unused				__set_attribute__((unused))

#define __pragma_weak          		__set_attribute__((weak))

#define __pragma_deprecated(x)		__set_attribute__((deprecated(x)))

#define __pragma_bitwise			__set_attribute__((bitwise))

#endif //__GUN_ATTRIBUTE_H__
