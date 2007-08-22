#include "LLTimeUtil.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Returns the current date time as a string.
 * \param [out] str String where the date time is returned.
 * \param [in]	strLen The length of the arg \a str.
 * \returns 0 on success, -1 on failure.
 * */
int LLGetCurDateTime(char* str, int strLen)
{
	time_t t;
	struct tm *tmp;

	t = time(NULL);
	tmp = localtime(&t);
	if (tmp == NULL) {
		perror("localtime");
		return -1;
	}

	if (strftime(str, strLen, " %F %T", tmp) == 0) {
		fprintf(stderr, "strftime returned 0");
		return -1;
	}
	return 0;

}
