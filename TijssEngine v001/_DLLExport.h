#pragma once

#define TIJSSEN_EXPORTING

#ifdef TIJSSEN_EXPORTING
#define TIJSSEN_DECLSPEC __declspec(dllexport)
#else
#define TIJSSEN_DECLSPEC __declspec(dllimport)
#endif // TIJSSEN_EXPORTING
