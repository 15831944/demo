#ifndef FSCOMMONLIB_GLOBAL_H
#define FSCOMMONLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef FSCOMMONLIB_LIB
# define FSCOMMONLIB_EXPORT Q_DECL_EXPORT
#else
# define FSCOMMONLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // FSCOMMONLIB_GLOBAL_H
