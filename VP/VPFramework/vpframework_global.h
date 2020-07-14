#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(VPFRAMEWORK_LIB)
#  define VPFRAMEWORK_EXPORT Q_DECL_EXPORT
# else
#  define VPFRAMEWORK_EXPORT Q_DECL_IMPORT
# endif
#else
# define VPFRAMEWORK_EXPORT
#endif
