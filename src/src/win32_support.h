#ifndef __WIN32_SUPPORT_H__
#define __WIN32_SUPPORT_H__

#if defined(WIN32) || defined(_WIN32)
#define __func__ __FUNCTION__
#define snprintf _snprintf
#endif

#endif // __WIN32_SUPPORT_H__
