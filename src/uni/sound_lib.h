#ifndef _SOUND_LIB_H_
#define _SOUBD_LIB_H_

// rom char theme1[513][5] = {
// 	{ 1, 0x02, 0x26, 0x00, 0x37 },
// 	{ 1, 0x02, 0x26, 0x00, 0x6E },
// 	{ 1, 0x02, 0x26, 0x00, 0xA5 },
// 	{ 1, 0x02, 0x26, 0x00, 0xDC },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x15 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x43 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x71 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 1, 0x01, 0x6F, 0x01, 0x4A },
// 	{ 1, 0x01, 0x6F, 0x00, 0xDC },
// 	{ 1, 0x01, 0x6F, 0x01, 0x00 },
// 	{ 1, 0x01, 0x6F, 0x01, 0x25 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x26, 0x00, 0x37 },
// 	{ 1, 0x02, 0x26, 0x00, 0x6E },
// 	{ 1, 0x02, 0x26, 0x00, 0xA5 },
// 	{ 1, 0x02, 0x26, 0x00, 0xDC },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x15 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x43 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x71 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 1, 0x01, 0x6F, 0x01, 0x4A },
// 	{ 1, 0x01, 0x6F, 0x00, 0xDC },
// 	{ 1, 0x01, 0x6F, 0x01, 0x00 },
// 	{ 1, 0x01, 0x6F, 0x01, 0x25 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x26, 0x00, 0x37 },
// 	{ 1, 0x02, 0x26, 0x00, 0x6E },
// 	{ 1, 0x02, 0x26, 0x00, 0xA5 },
// 	{ 1, 0x02, 0x26, 0x00, 0xDC },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x15 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x43 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x71 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 1, 0x01, 0x6F, 0x01, 0x4A },
// 	{ 1, 0x01, 0x6F, 0x00, 0xDC },
// 	{ 1, 0x01, 0x6F, 0x01, 0x00 },
// 	{ 1, 0x01, 0x6F, 0x01, 0x25 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x26, 0x00, 0x37 },
// 	{ 1, 0x02, 0x26, 0x00, 0x6E },
// 	{ 1, 0x02, 0x26, 0x00, 0xA5 },
// 	{ 1, 0x02, 0x26, 0x00, 0xDC },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x15 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x43 },
// 	{ 1, 0x01, 0xCE, 0x01, 0x71 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
// 	{ 1, 0x01, 0x6F, 0x01, 0x4A },
// 	{ 1, 0x01, 0x6F, 0x00, 0xDC },
// 	{ 1, 0x01, 0x6F, 0x01, 0x00 },
// 	{ 1, 0x01, 0x6F, 0x01, 0x25 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 0, 0x01, 0x6F, 0x00, 0xB7 },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x26, 0x00, 0x37 },
// 	{ 1, 0x02, 0x26, 0x00, 0x6E },
// 	{ 1, 0x02, 0x26, 0x00, 0xA5 },
// 	{ 1, 0x02, 0x26, 0x00, 0xDC },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x5A, 0x01, 0x37 },
// 	{ 1, 0x01, 0x5A, 0x00, 0xCF },
// 	{ 1, 0x01, 0x5A, 0x00, 0xF2 },
// 	{ 1, 0x01, 0x5A, 0x01, 0x14 },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x26, 0x00, 0x37 },
// 	{ 1, 0x02, 0x26, 0x00, 0x6E },
// 	{ 1, 0x02, 0x26, 0x00, 0xA5 },
// 	{ 1, 0x02, 0x26, 0x00, 0xDC },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x5A, 0x01, 0x37 },
// 	{ 1, 0x01, 0x5A, 0x00, 0xCF },
// 	{ 1, 0x01, 0x5A, 0x00, 0xF2 },
// 	{ 1, 0x01, 0x5A, 0x01, 0x14 },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x26, 0x00, 0x37 },
// 	{ 1, 0x02, 0x26, 0x00, 0x6E },
// 	{ 1, 0x02, 0x26, 0x00, 0xA5 },
// 	{ 1, 0x02, 0x26, 0x00, 0xDC },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x5A, 0x01, 0x37 },
// 	{ 1, 0x01, 0x5A, 0x00, 0xCF },
// 	{ 1, 0x01, 0x5A, 0x00, 0xF2 },
// 	{ 1, 0x01, 0x5A, 0x01, 0x14 },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x26, 0x00, 0x37 },
// 	{ 1, 0x02, 0x26, 0x00, 0x6E },
// 	{ 1, 0x02, 0x26, 0x00, 0xA5 },
// 	{ 1, 0x02, 0x26, 0x00, 0xDC },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x5A, 0x01, 0x37 },
// 	{ 1, 0x01, 0x5A, 0x00, 0xCF },
// 	{ 1, 0x01, 0x5A, 0x00, 0xF2 },
// 	{ 1, 0x01, 0x5A, 0x01, 0x14 },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 0, 0x01, 0x5A, 0x00, 0xAD },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x69, 0x00, 0x3D },
// 	{ 1, 0x02, 0x69, 0x00, 0x7B },
// 	{ 1, 0x02, 0x69, 0x00, 0xB9 },
// 	{ 1, 0x02, 0x69, 0x00, 0xF6 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 1, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x26 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x57 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x88 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x72 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x69, 0x00, 0x3D },
// 	{ 1, 0x02, 0x69, 0x00, 0x7B },
// 	{ 1, 0x02, 0x69, 0x00, 0xB9 },
// 	{ 1, 0x02, 0x69, 0x00, 0xF6 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 1, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x26 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x57 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x88 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x72 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x69, 0x00, 0x3D },
// 	{ 1, 0x02, 0x69, 0x00, 0x7B },
// 	{ 1, 0x02, 0x69, 0x00, 0xB9 },
// 	{ 1, 0x02, 0x69, 0x00, 0xF6 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 1, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x26 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x57 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x88 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x72 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x69, 0x00, 0x3D },
// 	{ 1, 0x02, 0x69, 0x00, 0x7B },
// 	{ 1, 0x02, 0x69, 0x00, 0xB9 },
// 	{ 1, 0x02, 0x69, 0x00, 0xF6 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 0, 0x02, 0x69, 0x01, 0x34 },
// 	{ 1, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x26 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x57 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x88 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x72 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x13, 0x00, 0xA5 },
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x01, 0x13, 0x00, 0x6E },
// 	{ 1, 0x01, 0x13, 0x00, 0x52 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x47, 0x00, 0x3A },
// 	{ 1, 0x02, 0x47, 0x00, 0x74 },
// 	{ 1, 0x02, 0x47, 0x00, 0xAE },
// 	{ 1, 0x02, 0x47, 0x00, 0xE9 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 1, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x26 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x57 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x88 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x72 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x23, 0x00, 0xAE },
// 	{ 1, 0x01, 0x23, 0x00, 0x91 },
// 	{ 1, 0x01, 0x23, 0x00, 0x74 },
// 	{ 1, 0x01, 0x23, 0x00, 0x57 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 1, 0x02, 0x47, 0x00, 0x3A },
// 	{ 1, 0x02, 0x47, 0x00, 0x74 },
// 	{ 1, 0x02, 0x47, 0x00, 0xAE },
// 	{ 1, 0x02, 0x47, 0x00, 0xE9 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 1, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x26 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x57 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x88 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x72 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x23, 0x00, 0xAE },
// 	{ 1, 0x01, 0x23, 0x00, 0x91 },
// 	{ 1, 0x01, 0x23, 0x00, 0x74 },
// 	{ 1, 0x01, 0x23, 0x00, 0x57 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 1, 0x02, 0x47, 0x00, 0x3A },
// 	{ 1, 0x02, 0x47, 0x00, 0x74 },
// 	{ 1, 0x02, 0x47, 0x00, 0xAE },
// 	{ 1, 0x02, 0x47, 0x00, 0xE9 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 1, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x26 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x57 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x88 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x72 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x23, 0x00, 0xAE },
// 	{ 1, 0x01, 0x23, 0x00, 0x91 },
// 	{ 1, 0x01, 0x23, 0x00, 0x74 },
// 	{ 1, 0x01, 0x23, 0x00, 0x57 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 1, 0x02, 0x47, 0x00, 0x3A },
// 	{ 1, 0x02, 0x47, 0x00, 0x74 },
// 	{ 1, 0x02, 0x47, 0x00, 0xAE },
// 	{ 1, 0x02, 0x47, 0x00, 0xE9 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 0, 0x02, 0x47, 0x01, 0x23 },
// 	{ 1, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x26 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x57 },
// 	{ 1, 0x01, 0xEA, 0x01, 0x88 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 0, 0x01, 0xEA, 0x00, 0xF5 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x72 },
// 	{ 1, 0x01, 0x9C, 0x00, 0xF7 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x20 },
// 	{ 1, 0x01, 0x9C, 0x01, 0x49 },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 0, 0x01, 0x9C, 0x00, 0xCE },
// 	{ 1, 0x01, 0x23, 0x00, 0xAE },
// 	{ 1, 0x01, 0x23, 0x00, 0x91 },
// 	{ 1, 0x01, 0x23, 0x00, 0x74 },
// 	{ 1, 0x01, 0x23, 0x00, 0x57 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 },
// 	{ 0, 0x01, 0x23, 0x00, 0x91 }
// };

rom char bossTheme[128][5] = {
	{ 1, 0x02, 0x26, 0x01, 0x13 },
	{ 1, 0x04, 0x4C, 0x02, 0x26 },
	{ 1, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 1, 0x00, 0x89, 0x00, 0x44 },
	{ 0, 0x00, 0x89, 0x00, 0x44 },
	{ 1, 0x03, 0x9D, 0x01, 0xCE },
	{ 0, 0x03, 0x9D, 0x01, 0xCE },
	{ 1, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 1, 0x01, 0xCE, 0x00, 0xE7 },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 1, 0x03, 0x9D, 0x01, 0xCE },
	{ 0, 0x03, 0x9D, 0x01, 0xCE },
	{ 1, 0x04, 0x4C, 0x02, 0x26 },
	{ 0, 0x04, 0x4C, 0x02, 0x26 },
	{ 1, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 1, 0x00, 0x81, 0x00, 0x40 },
	{ 1, 0x01, 0x13, 0x00, 0x89 },
	{ 0, 0x01, 0x13, 0x00, 0x89 },
	{ 0, 0x01, 0x13, 0x00, 0x89 },
	{ 1, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 1, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 1, 0x02, 0x26, 0x01, 0x13 },
	{ 1, 0x04, 0x4C, 0x02, 0x26 },
	{ 1, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 1, 0x00, 0x89, 0x00, 0x44 },
	{ 0, 0x00, 0x89, 0x00, 0x44 },
	{ 1, 0x02, 0x07, 0x01, 0x03 },
	{ 0, 0x02, 0x07, 0x01, 0x03 },
	{ 1, 0x02, 0x07, 0x01, 0x03 },
	{ 0, 0x02, 0x07, 0x01, 0x03 },
	{ 1, 0x02, 0x07, 0x01, 0x03 },
	{ 0, 0x02, 0x07, 0x01, 0x03 },
	{ 1, 0x01, 0xCE, 0x00, 0xE7 },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 1, 0x02, 0x26, 0x01, 0x13 },
	{ 1, 0x04, 0x4C, 0x02, 0x26 },
	{ 1, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 1, 0x00, 0x81, 0x00, 0x40 },
	{ 1, 0x01, 0x13, 0x00, 0x89 },
	{ 0, 0x01, 0x13, 0x00, 0x89 },
	{ 0, 0x01, 0x13, 0x00, 0x89 },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 1, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 1, 0x02, 0x26, 0x01, 0x13 },
	{ 1, 0x04, 0x4C, 0x02, 0x26 },
	{ 1, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 1, 0x00, 0x89, 0x00, 0x44 },
	{ 0, 0x00, 0x89, 0x00, 0x44 },
	{ 1, 0x03, 0x9D, 0x01, 0xCE },
	{ 0, 0x03, 0x9D, 0x01, 0xCE },
	{ 1, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 1, 0x01, 0xCE, 0x00, 0xE7 },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 1, 0x03, 0x9D, 0x01, 0xCE },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 1, 0x04, 0x4C, 0x02, 0x26 },
	{ 1, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 1, 0x00, 0x81, 0x00, 0x40 },
	{ 1, 0x01, 0x13, 0x00, 0x89 },
	{ 0, 0x01, 0x13, 0x00, 0x89 },
	{ 0, 0x01, 0x13, 0x00, 0x89 },
	{ 1, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 0, 0x02, 0xDE, 0x01, 0x6F },
	{ 1, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 0, 0x01, 0xB4, 0x00, 0xDA },
	{ 1, 0x02, 0x26, 0x01, 0x13 },
	{ 1, 0x04, 0x4C, 0x02, 0x26 },
	{ 1, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 1, 0x00, 0x89, 0x00, 0x44 },
	{ 0, 0x00, 0x89, 0x00, 0x44 },
	{ 1, 0x02, 0x07, 0x01, 0x03 },
	{ 0, 0x02, 0x07, 0x01, 0x03 },
	{ 1, 0x02, 0x07, 0x01, 0x03 },
	{ 0, 0x02, 0x07, 0x01, 0x03 },
	{ 1, 0x02, 0x07, 0x01, 0x03 },
	{ 0, 0x02, 0x07, 0x01, 0x03 },
	{ 1, 0x01, 0xCE, 0x00, 0xE7 },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 0, 0x01, 0xCE, 0x00, 0xE7 },
	{ 1, 0x02, 0x26, 0x01, 0x13 },
	{ 1, 0x04, 0x4C, 0x02, 0x26 },
	{ 1, 0x08, 0x99, 0x04, 0x4C },
	{ 0, 0x08, 0x99, 0x04, 0x4C },
	{ 1, 0x01, 0x03, 0x00, 0x81 },
	{ 0, 0x01, 0x13, 0x00, 0x89 },
	{ 1, 0x01, 0x85, 0x00, 0xC2 },
	{ 0, 0x01, 0x85, 0x00, 0xC2 },
	{ 0, 0x02, 0x26, 0x01, 0x13 },
	{ 0, 0x02, 0x26, 0x01, 0x13 },
	{ 1, 0x02, 0x26, 0x01, 0x13 },
	{ 0, 0x02, 0x26, 0x01, 0x13 },
	{ 1, 0x02, 0x47, 0x01, 0x23 },
	{ 1, 0x02, 0x47, 0x01, 0x23 },
	{ 1, 0x02, 0x47, 0x01, 0x23 },
	{ 1, 0x02, 0x47, 0x01, 0x23 }
};

rom char soundFX[1][8][5] = {
	{
		{ 1, 0x00, 0x89, 0x00, 0x0D },
		{ 1, 0x01, 0x13, 0x00, 0x1B },
		{ 1, 0x00, 0xDA, 0x00, 0x15 },
		{ 1, 0x01, 0x13, 0x00, 0x1B },
		{ 1, 0x00, 0xDA, 0x00, 0x15 },
		{ 1, 0x01, 0x13, 0x00, 0x1B },
		{ 1, 0x00, 0xDA, 0x00, 0x15 },
		{ 1, 0x00, 0x89, 0x00, 0x0D }
	}
};

rom char music[4][128][5] = {
	{	// Main theme 1
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x02, 0x26, 0x00, 0x37 },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x01, 0xEA, 0x00, 0x31 },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x01, 0xCE, 0x00, 0x2E },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x01, 0x9C, 0x00, 0x29 },
		{ 0, 0x01, 0x9C, 0x00, 0x29 },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x01, 0x6F, 0x00, 0x24 },
		{ 0, 0x01, 0x6F, 0x00, 0x24 },
		{ 0, 0x01, 0x6F, 0x00, 0x24 },
		{ 0, 0x01, 0x6F, 0x00, 0x24 },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x02, 0x26, 0x00, 0x37 },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x01, 0xEA, 0x00, 0x31 },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 0, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x01, 0xCE, 0x00, 0x2E },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x01, 0x9C, 0x00, 0x29 },
		{ 0, 0x01, 0x9C, 0x00, 0x29 },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x01, 0xB4, 0x00, 0x2B },
		{ 0, 0x01, 0xB4, 0x00, 0x2B },
		{ 0, 0x01, 0xB4, 0x00, 0x2B },
		{ 0, 0x01, 0xB4, 0x00, 0x2B }
	}, { // Main theme 2
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 2, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x01, 0xB4, 0x00, 0x2B },
		{ 0, 0x01, 0xB4, 0x00, 0x2B },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 2, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x02, 0x26, 0x00, 0x37 },
		{ 2, 0x02, 0x26, 0x00, 0x37 },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 2, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 2, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x02, 0x26, 0x00, 0x37 },
		{ 2, 0x02, 0x26, 0x00, 0x37 },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 2, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x02, 0x07, 0x00, 0x33 },
		{ 0, 0x02, 0x07, 0x00, 0x33 },
		{ 1, 0x01, 0xEA, 0x00, 0x31 },
		{ 2, 0x01, 0xEA, 0x00, 0x31 },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 2, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x02, 0x69, 0x00, 0x3D },
		{ 2, 0x02, 0x69, 0x00, 0x3D },
		{ 1, 0x03, 0xD4, 0x00, 0x62 },
		{ 0, 0x03, 0xD4, 0x00, 0x62 },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 2, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 2, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x02, 0xDE, 0x00, 0x49 },
		{ 0, 0x02, 0xDE, 0x00, 0x49 },
		{ 1, 0x01, 0xCE, 0x00, 0x2E },
		{ 2, 0x01, 0xCE, 0x00, 0x2E },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 2, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 2, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 2, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x01, 0x9C, 0x00, 0x29 },
		{ 0, 0x01, 0x9C, 0x00, 0x29 },
		{ 1, 0x01, 0x9C, 0x00, 0x29 },
		{ 2, 0x01, 0x9C, 0x00, 0x29 },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 2, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x01, 0x6F, 0x00, 0x24 },
		{ 2, 0x01, 0x6F, 0x00, 0x24 },
		{ 0, 0x01, 0x6F, 0x00, 0x24 },
		{ 0, 0x01, 0x6F, 0x00, 0x24 },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 2, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x01, 0xB4, 0x00, 0x2B },
		{ 0, 0x01, 0xB4, 0x00, 0x2B },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 2, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x02, 0x26, 0x00, 0x37 },
		{ 2, 0x02, 0x26, 0x00, 0x37 },
		{ 1, 0x04, 0x4C, 0x00, 0x6E },
		{ 2, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 0, 0x04, 0x4C, 0x00, 0x6E },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 2, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x02, 0x26, 0x00, 0x37 },
		{ 2, 0x02, 0x26, 0x00, 0x37 },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 2, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x02, 0x07, 0x00, 0x33 },
		{ 0, 0x02, 0x07, 0x00, 0x33 },
		{ 1, 0x01, 0xEA, 0x00, 0x31 },
		{ 2, 0x01, 0xEA, 0x00, 0x31 },
		{ 1, 0x04, 0xD3, 0x00, 0x7B },
		{ 2, 0x04, 0xD3, 0x00, 0x7B },
		{ 1, 0x02, 0x69, 0x00, 0x3D },
		{ 2, 0x02, 0x69, 0x00, 0x3D },
		{ 1, 0x03, 0xD4, 0x00, 0x62 },
		{ 0, 0x03, 0xD4, 0x00, 0x62 },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 2, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 2, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x02, 0xDE, 0x00, 0x49 },
		{ 0, 0x02, 0xDE, 0x00, 0x49 },
		{ 1, 0x01, 0xCE, 0x00, 0x2E },
		{ 2, 0x01, 0xCE, 0x00, 0x2E },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 2, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x03, 0x9D, 0x00, 0x5C },
		{ 0, 0x03, 0x9D, 0x00, 0x5C },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 2, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 0, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 2, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x01, 0x9C, 0x00, 0x29 },
		{ 0, 0x01, 0x9C, 0x00, 0x29 },
		{ 1, 0x01, 0x9C, 0x00, 0x29 },
		{ 2, 0x01, 0x9C, 0x00, 0x29 },
		{ 1, 0x04, 0x0F, 0x00, 0x67 },
		{ 2, 0x04, 0x0F, 0x00, 0x67 },
		{ 1, 0x01, 0x6F, 0x00, 0x24 },
		{ 2, 0x01, 0x6F, 0x00, 0x24 },
		{ 0, 0x01, 0x6F, 0x00, 0x24 },
		{ 0, 0x01, 0x6F, 0x00, 0x24 }
	}, { // Imperial theme
		{ 1, 0x03, 0x69, 0x02, 0x0B },
		{ 2, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 1, 0x06, 0xD3, 0x04, 0x18 },
		{ 2, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 1, 0x03, 0x69, 0x02, 0x0B },
		{ 2, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 1, 0x06, 0xD3, 0x04, 0x18 },
		{ 2, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 1, 0x03, 0x69, 0x02, 0x0B },
		{ 2, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 1, 0x05, 0xBD, 0x03, 0x71 },
		{ 2, 0x05, 0xBD, 0x03, 0x71 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 1, 0x04, 0x4C, 0x02, 0x94 },
		{ 2, 0x04, 0x4C, 0x02, 0x94 },
		{ 0, 0x04, 0x4C, 0x02, 0x94 },
		{ 0, 0x04, 0x4C, 0x02, 0x94 },
		{ 1, 0x05, 0xBD, 0x03, 0x71 },
		{ 2, 0x05, 0xBD, 0x03, 0x71 },
		{ 1, 0x02, 0xDE, 0x01, 0xB8 },
		{ 2, 0x02, 0xDE, 0x01, 0xB8 },
		{ 1, 0x03, 0x69, 0x02, 0x0B },
		{ 2, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 1, 0x08, 0x99, 0x05, 0x28 },
		{ 2, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 1, 0x04, 0x4C, 0x02, 0x94 },
		{ 2, 0x04, 0x4C, 0x02, 0x94 },
		{ 0, 0x04, 0x4C, 0x02, 0x94 },
		{ 0, 0x04, 0x4C, 0x02, 0x94 },
		{ 1, 0x08, 0x99, 0x05, 0x28 },
		{ 2, 0x08, 0x99, 0x05, 0x28 },
		{ 1, 0x05, 0x1D, 0x03, 0x11 },
		{ 2, 0x05, 0x1D, 0x03, 0x11 },
		{ 1, 0x03, 0x69, 0x02, 0x0B },
		{ 2, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 1, 0x09, 0x1C, 0x05, 0x77 },
		{ 2, 0x09, 0x1C, 0x05, 0x77 },
		{ 0, 0x09, 0x1C, 0x05, 0x77 },
		{ 0, 0x09, 0x1C, 0x05, 0x77 },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 1, 0x02, 0x47, 0x01, 0x5D },
		{ 2, 0x02, 0x47, 0x01, 0x5D },
		{ 0, 0x02, 0x47, 0x01, 0x5D },
		{ 0, 0x02, 0x47, 0x01, 0x5D },
		{ 1, 0x06, 0xD3, 0x04, 0x18 },
		{ 2, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 1, 0x02, 0x47, 0x01, 0x5D },
		{ 2, 0x02, 0x47, 0x01, 0x5D },
		{ 0, 0x02, 0x47, 0x01, 0x5D },
		{ 0, 0x02, 0x47, 0x01, 0x5D },
		{ 1, 0x06, 0xD3, 0x04, 0x18 },
		{ 2, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 1, 0x02, 0x47, 0x01, 0x5D },
		{ 2, 0x02, 0x47, 0x01, 0x5D },
		{ 0, 0x02, 0x47, 0x01, 0x5D },
		{ 0, 0x02, 0x47, 0x01, 0x5D },
		{ 1, 0x05, 0xBD, 0x03, 0x71 },
		{ 2, 0x05, 0xBD, 0x03, 0x71 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 0, 0x06, 0xD3, 0x04, 0x18 },
		{ 1, 0x02, 0x26, 0x01, 0x4A },
		{ 2, 0x02, 0x26, 0x01, 0x4A },
		{ 0, 0x02, 0x26, 0x01, 0x4A },
		{ 0, 0x02, 0x26, 0x01, 0x4A },
		{ 1, 0x05, 0xBD, 0x03, 0x71 },
		{ 2, 0x05, 0xBD, 0x03, 0x71 },
		{ 1, 0x02, 0xDE, 0x01, 0xB8 },
		{ 2, 0x02, 0xDE, 0x01, 0xB8 },
		{ 1, 0x03, 0x69, 0x02, 0x0B },
		{ 2, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 1, 0x08, 0x99, 0x05, 0x28 },
		{ 2, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 1, 0x04, 0x4C, 0x02, 0x94 },
		{ 2, 0x04, 0x4C, 0x02, 0x94 },
		{ 0, 0x04, 0x4C, 0x02, 0x94 },
		{ 0, 0x04, 0x4C, 0x02, 0x94 },
		{ 1, 0x08, 0x99, 0x05, 0x28 },
		{ 2, 0x08, 0x99, 0x05, 0x28 },
		{ 1, 0x05, 0x1D, 0x03, 0x11 },
		{ 2, 0x05, 0x1D, 0x03, 0x11 },
		{ 1, 0x03, 0x69, 0x02, 0x0B },
		{ 2, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 1, 0x09, 0x1C, 0x05, 0x77 },
		{ 2, 0x09, 0x1C, 0x05, 0x77 },
		{ 0, 0x09, 0x1C, 0x05, 0x77 },
		{ 0, 0x09, 0x1C, 0x05, 0x77 },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x03, 0x69, 0x02, 0x0B },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 },
		{ 0, 0x08, 0x99, 0x05, 0x28 }
	}, { // Boss theme
		{ 1, 0x02, 0x26, 0x01, 0x13 },
		{ 1, 0x04, 0x4C, 0x02, 0x26 },
		{ 1, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 1, 0x00, 0x89, 0x00, 0x44 },
		{ 0, 0x00, 0x89, 0x00, 0x44 },
		{ 1, 0x03, 0x9D, 0x01, 0xCE },
		{ 0, 0x03, 0x9D, 0x01, 0xCE },
		{ 1, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 1, 0x01, 0xCE, 0x00, 0xE7 },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 1, 0x03, 0x9D, 0x01, 0xCE },
		{ 0, 0x03, 0x9D, 0x01, 0xCE },
		{ 1, 0x04, 0x4C, 0x02, 0x26 },
		{ 0, 0x04, 0x4C, 0x02, 0x26 },
		{ 1, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 1, 0x00, 0x81, 0x00, 0x40 },
		{ 1, 0x01, 0x13, 0x00, 0x89 },
		{ 0, 0x01, 0x13, 0x00, 0x89 },
		{ 0, 0x01, 0x13, 0x00, 0x89 },
		{ 1, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 1, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 1, 0x02, 0x26, 0x01, 0x13 },
		{ 1, 0x04, 0x4C, 0x02, 0x26 },
		{ 1, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 1, 0x00, 0x89, 0x00, 0x44 },
		{ 0, 0x00, 0x89, 0x00, 0x44 },
		{ 1, 0x02, 0x07, 0x01, 0x03 },
		{ 0, 0x02, 0x07, 0x01, 0x03 },
		{ 1, 0x02, 0x07, 0x01, 0x03 },
		{ 0, 0x02, 0x07, 0x01, 0x03 },
		{ 1, 0x02, 0x07, 0x01, 0x03 },
		{ 0, 0x02, 0x07, 0x01, 0x03 },
		{ 1, 0x01, 0xCE, 0x00, 0xE7 },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 1, 0x02, 0x26, 0x01, 0x13 },
		{ 1, 0x04, 0x4C, 0x02, 0x26 },
		{ 1, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 1, 0x00, 0x81, 0x00, 0x40 },
		{ 1, 0x01, 0x13, 0x00, 0x89 },
		{ 0, 0x01, 0x13, 0x00, 0x89 },
		{ 0, 0x01, 0x13, 0x00, 0x89 },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 1, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 1, 0x02, 0x26, 0x01, 0x13 },
		{ 1, 0x04, 0x4C, 0x02, 0x26 },
		{ 1, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 1, 0x00, 0x89, 0x00, 0x44 },
		{ 0, 0x00, 0x89, 0x00, 0x44 },
		{ 1, 0x03, 0x9D, 0x01, 0xCE },
		{ 0, 0x03, 0x9D, 0x01, 0xCE },
		{ 1, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 1, 0x01, 0xCE, 0x00, 0xE7 },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 1, 0x03, 0x9D, 0x01, 0xCE },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 1, 0x04, 0x4C, 0x02, 0x26 },
		{ 1, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 1, 0x00, 0x81, 0x00, 0x40 },
		{ 1, 0x01, 0x13, 0x00, 0x89 },
		{ 0, 0x01, 0x13, 0x00, 0x89 },
		{ 0, 0x01, 0x13, 0x00, 0x89 },
		{ 1, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 0, 0x02, 0xDE, 0x01, 0x6F },
		{ 1, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 0, 0x01, 0xB4, 0x00, 0xDA },
		{ 1, 0x02, 0x26, 0x01, 0x13 },
		{ 1, 0x04, 0x4C, 0x02, 0x26 },
		{ 1, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 1, 0x00, 0x89, 0x00, 0x44 },
		{ 0, 0x00, 0x89, 0x00, 0x44 },
		{ 1, 0x02, 0x07, 0x01, 0x03 },
		{ 0, 0x02, 0x07, 0x01, 0x03 },
		{ 1, 0x02, 0x07, 0x01, 0x03 },
		{ 0, 0x02, 0x07, 0x01, 0x03 },
		{ 1, 0x02, 0x07, 0x01, 0x03 },
		{ 0, 0x02, 0x07, 0x01, 0x03 },
		{ 1, 0x01, 0xCE, 0x00, 0xE7 },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 0, 0x01, 0xCE, 0x00, 0xE7 },
		{ 1, 0x02, 0x26, 0x01, 0x13 },
		{ 1, 0x04, 0x4C, 0x02, 0x26 },
		{ 1, 0x08, 0x99, 0x04, 0x4C },
		{ 0, 0x08, 0x99, 0x04, 0x4C },
		{ 1, 0x01, 0x03, 0x00, 0x81 },
		{ 0, 0x01, 0x13, 0x00, 0x89 },
		{ 1, 0x01, 0x85, 0x00, 0xC2 },
		{ 0, 0x01, 0x85, 0x00, 0xC2 },
		{ 0, 0x02, 0x26, 0x01, 0x13 },
		{ 0, 0x02, 0x26, 0x01, 0x13 },
		{ 1, 0x02, 0x26, 0x01, 0x13 },
		{ 0, 0x02, 0x26, 0x01, 0x13 },
		{ 2, 0x02, 0x47, 0x01, 0x23 },
		{ 2, 0x02, 0x47, 0x01, 0x23 },
		{ 2, 0x02, 0x47, 0x01, 0x23 },
		{ 2, 0x02, 0x47, 0x01, 0x23 }
	}
};


// rom char soundFX[1][8][5] = {{ // old one for merge
// 	{ 1, 0x01, 0x13, 0x00, 0x89 },
// 	{ 1, 0x02, 0x26, 0x01, 0x13 },
// 	{ 1, 0x04, 0x4C, 0x02, 0x26 },
// 	{ 1, 0x08, 0x99, 0x04, 0x4C },
// 	{ 0, 0x01, 0x13, 0x00, 0x89 },
// 	{ 0, 0x02, 0x26, 0x01, 0x13 },
// 	{ 0, 0x04, 0x4C, 0x02, 0x26 },
// 	{ 0, 0x08, 0x99, 0x04, 0x4C }
// }};
#endif