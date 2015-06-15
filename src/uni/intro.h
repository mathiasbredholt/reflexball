#ifdef __APPLE__
#define GCC
#endif

#ifdef __WIN32__
#define GCC
#endif

#ifndef _INTRO_H_
#define _INTRO_H_

#ifndef GCC
rom char title[42][8] = {
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aazxcggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aaasdggt",
	"aazxcggt"
};
#endif

void intro_play();

#endif  // _INTRO_H_