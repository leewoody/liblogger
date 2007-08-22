#ifndef __LLTIMEUTIL_H__
#define __LLTIMEUTIL_H__

/**
 * Returns the current date time as a string.
 * \param [out] str String where the date time is returned.
 * \param [in]	strLen The length of the arg \a str.
 * \returns 0 on success, -1 on failure.
 * */
int LLGetCurDateTime(char* str, int strLen);

#endif // __LLTIMEUTIL_H__
