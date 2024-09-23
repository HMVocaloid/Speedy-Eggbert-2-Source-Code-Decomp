#pragma once
#include "obstacle.h"

extern int table_blitz[]
{
	0,  7, 15, 18, 26, 27, 32, 39, 45, 47,
	50, 58, 60, 62, 64, 66, 68, 70, 71, 72,
	-1
};

extern int table_vitesse_march[]
{
	2, 4, 6, 8
};

extern int table_vitesse_nage[]
{
	2, 1, 5, 10, 8, 6, 4
};

extern int table_vitesse_surf[]
{
	0, 2, 5, 8, 3, 0
};

extern int speed[]
{
	-8,
					-6,
					-4,
					0,
					4,
					6,
					8
};

extern int table_bulldozer_left[8]{ 66, 66, 67, 67, 66, 66, 65, 65 };

extern int table_bulldozer_right[8]{ 58, 58, 57, 57, 58, 58, 59, 59 };

extern int table_bulldozer_turn2l[22]
{
	58, 59, 59, 59, 60, 60, 60, 61, 61, 62,
	62, 63, 63, 64, 64, 64, 65, 65, 65, 66,
	66, 66
};

extern int table_bulldozer_turn2r[22]
{
	66, 65, 65, 65, 64, 64, 64, 63, 63, 62,
	62, 61, 61, 60, 60, 60, 59, 59, 59, 58,
	58, 58
};

extern int table_poisson_left[8]{ 82, 82, 81, 81, 82, 82, 83, 83 };

extern int table_poisson_right[8]{ 79, 79, 78, 78, 79, 79, 80, 80 };

extern int table_poisson_turn2l[48]
{
	79, 79, 80, 80, 84, 84, 85, 85, 86, 86,
	87, 87, 88, 88, 83, 83, 82, 82, 83, 83,
	88, 88, 87, 87, 86, 86, 85, 85, 84, 84,
	79, 79, 79, 79, 80, 80, 84, 84, 85, 85,
	86, 86, 87, 87, 88, 88, 83, 83
};

extern int table_poisson_turn2r[48]
{
	82, 82, 83, 83, 88, 88, 87, 87, 86, 86,
	85, 85, 84, 84, 79, 79, 79, 79, 80, 80,
	84, 84, 85, 85, 86, 86, 87, 87, 88, 88,
	83, 83, 82, 82, 83, 83, 88, 88, 87, 87,
	86, 86, 85, 85, 84, 84, 79, 79
};

extern int table_oiseau_left[8]{ 98, 99, 100, 101, 102, 103, 104, 105 };

extern int table_oiseau_right[8]{ 90, 91, 92, 93, 94, 95, 96, 97 };

extern int table_oiseau_turn2l[10]{ 106, 107, 108, 109, 110, 111, 112, 113, 105, 105 };

extern int table_oiseau_turn2r[10]{ 114, 115, 116, 117, 118, 119, 120, 121, 97, 97 };

extern int table_guepe_left[6]{ 195, 196, 197, 198, 197, 196 };

extern int table_guepe_right[6]{ 199, 200, 201, 202, 201, 200 };

extern int table_guepe_turn2l[5]{ 207, 206, 205, 204, 203 };

extern int table_guepe_turn2r[5]{ 203, 204, 205, 206, 207 };

extern int table_creature_left[8]{ 247, 248, 249, 250, 251, 250, 249, 248 };

extern int table_creature_right[8]{ 247, 248, 249, 250, 251, 250, 249, 248 };

extern int table_creature_turn2[152]
{
	244, 244, 244, 244, 244, 244, 244, 244, 243, 243,
	242, 242, 242, 242, 242, 242, 242, 242, 243, 243,
	244, 244, 245, 245, 246, 246, 246, 246, 246, 246,
	246, 246, 245, 245, 244, 244, 243, 243, 242, 242,
	242, 242, 242, 242, 243, 243, 244, 244, 245, 245,
	246, 246, 246, 246, 246, 246, 245, 245, 244, 244,
	243, 243, 242, 242, 242, 242, 243, 243, 244, 244,
	245, 245, 246, 246, 246, 246, 245, 245, 244, 244,
	243, 243, 242, 242, 243, 243, 244, 244, 245, 245,
	246, 246, 245, 245, 244, 244, 243, 243, 242, 242,
	242, 242, 243, 243, 244, 244, 245, 245, 246, 246,
	246, 246, 245, 245, 244, 244, 243, 243, 242, 242,
	242, 242, 242, 242, 243, 243, 244, 244, 245, 245,
	246, 246, 246, 246, 246, 246, 245, 245, 244, 244,
	244, 244, 244, 244, 244, 244, 244, 244, 244, 244,
	244, 244
};

extern int table_blupih_left[8]{ 66, 67, 68, 67, 66, 69, 70, 69 };

extern int table_blupih_right[8]{ 61, 62, 63, 62, 61, 64, 65, 64 };

extern int table_blupih_turn2l[26]
{
	71, 71, 72, 72, 73, 73, 74, 74, 75, 75,
	68, 68, 275, 275, 271, 271, 271, 271, 272, 272,
	273, 273, 273, 273, 275, 275
};

extern int table_blupih_turn2r[26]
{
	75, 75, 74, 74, 73, 73, 72, 72, 71, 71,
	63, 63, 274, 274, 271, 271, 271, 271, 272, 272,
	273, 273, 273, 273, 274, 274
};

extern int table_blupit_left[8]{ 249, 249, 250, 250, 249, 249, 248, 248 };

extern int table_blupit_right[8]{ 238, 238, 237, 237, 238, 238, 239, 239 };

extern int table_blupit_turn2l[24]
{
	238, 238, 251, 251, 238, 238, 238, 239, 240, 241,
	242, 243, 244, 245, 246, 247, 248, 249, 249, 249,
	252, 252, 249, 249
};

extern int table_blupit_turn2r[24]
{
	249, 249, 252, 252, 249, 249, 249, 248, 247, 246,
	245, 244, 243, 242, 241, 240, 239, 238, 238, 238,
	251, 251, 238, 238
};

extern int table_explo1[39]
{
	0, 0, 1, 1, 2, 2, 3, 3, 4, 3,
	4, 4, 3, 4, 3, 3, 4, 4, 5, 5,
	4, 5, 6, 5, 6, 6, 5, 5, 6, 7,
	7, 8, 8, 9, 9, 10, 10, 11, 11
};

extern int table_explo2[20]
{
	12, -1, 13, 14, -1, 15, 13, -1, 14, 15,
	12, -1, 13, 15, 14, 14, -1, 14, 15, 13
};

extern int table_explo3[20]
{
	32, 32, 34, 34, 32, 32, 34, 34, 32, 32,
	34, 34, 32, 32, 35, 35, 32, 32, 35, 35
};

extern int table_explo4[9]{ 12, 13, 14, 15, 7, 8, 9, 10, 11 };

extern int table_explo5[12]
{
	54, -1, 55, -1, 56, -1, 57, -1, 58, -1,
	59, -1
};

extern int table_explo6[6]{ 54, 55, 56, 57, 58, 59 };

extern int table_explo7[128]
{
	60, 61, -1, 63, 64, 65, 62, 64, 62, 60,
	62, -1, 65, -1, 60, 65, 63, 61, 62, -1,
	64, 65, -1, 62, 64, 61, 62, 63, -1, 65,
	60, -1, 65, -1, 63, 65, -1, 61, 60, 65,
	62, 63, 64, -1, 62, 63, -1, 62, 62, 60,
	62, -1, 65, -1, 60, 65, 64, 61, 62, 63,
	-1, 65, 60, -1, 63, 61, 62, -1, 64, 65,
	-1, 62, 62, 60, 62, -1, 65, -1, 60, 65,
	60, 61, -1, 63, 64, 65, 62, 64, 63, 61,
	62, -1, 64, 65, -1, 62, 60, 61, -1, 63,
	64, 65, 62, 64, -1, 60, -1, -1, 65, -1,
	60, -1, 63, -1, 62, -1, -1, 65, -1, -1,
	-1, 61, -1, -1, -1, 60, -1, -1
};

extern int table_explo8[5]{ 7, 8, 9, 10, 11 };

extern int table_sploutch1[10]{ 90, 91, 92, 93, 94, 95, 96, 97, 98, 99 };

extern int table_sploutch2[13]
{
	-1, -1, -1, 90, 91, 92, 93, 94, 95, 96,
	97, 98, 99
};

extern int table_sploutch3[18]
{
	-1, -1, -1, -1, -1, -1, -1, -1, 90, 91,
	92, 93, 94, 95, 96, 97, 98, 99
};

extern int table_tentacule[45]
{
	86, 85, 84, 83, 84, 85, 86, -1, 86, 85,
	84, 83, 82, 81, 80, 79, 78, 77, 76, 75,
	74, 73, 72, 71, 70, 70, 70, 70, 71, 72,
	73, 74, 75, 76, 77, 78, 79, 80, 81, 82,
	83, 84, 85, 86, -1
};

extern int table_bridge[157]
{
	365, 366, 365, 366, 365, 366, 365, 366, 365, 366,
	365, 366, 365, 366, 365, 366, 367, 367, 368, 368,
	369, 369, 370, 370, 371, 371, 372, 372, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	372, 372, 371, 371, 370, 370, 369, 369, 368, 368,
	367, 367, 366, 366, 365, 365, 364
};

extern int table_pollution[8]{ 179, 180, 181, 182, 183, 184, 185, 186 };

extern int table_invertstart[8]{ 179, 180, 181, 182, 183, 184, 185, 186 };

extern int table_invertstop[8]{ 186, 185, 184, 183, 182, 181, 180, 179 };

extern int table_invertpanel[8]{ 187, 188, 189, 190, 191, 192, 193, 194 };

extern int table_plouf[7]{ 99, 100, 101, 102, 101, 100, 99 };

extern int table_tiplouf[3]{ 244, 99, 244 };

extern int table_blup[20]
{
	103, 104, 105, 106, 104, 103, 106, 105, 103, 104,
	103, 105, 106, 103, 105, 106, 103, 104, 106, 105
};

extern int table_follow1[26]
{
	256, 256, 256, 257, 257, 258, 259, 260, 261, 262,
	263, 264, 264, 265, 265, 265, 264, 264, 263, 262,
	261, 260, 259, 258, 257, 257
};

extern int table_follow2[5]{ 256, 258, 260, 262, 264 };

extern int table_cle[12]
{
	122, 123, 124, 125, 126, 127, 128, 127, 126, 125,
	124, 123
};

extern int table_cle1[12]
{
	209, 210, 211, 212, 213, 214, 215, 214, 213, 212, 211, 210
};

extern int table_cle2[12]
{
	220, 221, 222, 221, 220, 219, 218, 217, 216, 217, 218, 219
};

extern int table_cle3[12]
{
	229, 228, 227, 226, 225, 224, 223, 224, 225, 226, 227, 228 
};

extern int table_decor_action[]
{
	1,32,
	-4,4, 4,-3, -4,2, 4,5, -4,-1, 4,2, -4,-4, 4,-3, -3,2, 3,2,
	-3,-5, 3,4, -3,5, 3,-2, -3,5, 3,4, -2,-2, 2,4, -2,-2, 2,-2,
	-2,-4, 2,2, -2,-2, 2,-3, -1,-3, 1,-2, -1,-1, 1,2, -1,-2, 1,-1,
	-1,1, 1,2,
	2,32,
	-4,0, 4,0, -4,0, 4,0, -4,0, 4,0, -4,0, 4,0, -3,0, 3,0,
	-3,0, 3,0, -3,0, 3,0, -3,0, 3,0, -2,0, 2,0, -2,0, 2,0,
	-2,0, 2,0, -2,0, 2,0, -1,0, 1,0, -1,0, 1,0, -1,0, 1,0,
	-1,0, 1,0,
	5,192,
	0,-32, 0,32, 0,-16, 0,6, 0,-8, 0,8, 0,-4, 0,4, 0,-2, 0,2,
	-7,0, -6,0, -5,0, -4,0, -2,0, 0,0, 2,0, 4,0, 5,0, 6,0,
	7,0, 7,0, 6,0, 5,0, 4,0, 2,0, 0,0, -2,0, -4,0, -5,0,
	-6,0, -7,0, -7,0, -6,0, -5,0, -4,0, -2,0, 0,0, 2,0, 4,0,
	5,0, 6,0, 7,0, 7,0, 6,0, 5,0, 4,0, 2,0, 0,0, -2,0, -4,0,
	-5,0, -6,0, -7,0, -7,0, -6,0, -5,0, -4,0, -2,0, 0,0, 2,0,
	4,0, 5,0, 6,0, 7,0, 7,0, 6,0, 5,0, 4,0, 2,0, 0,0,
	-2,0, -4,0, -5,0, -6,0, -7,0, -7,0, -6,0, -5,0, -4,0, -2,0,
	0,0, 2,0, 4,0, 5,0, 6,0, 7,0, 7,0, 6,0, 5,0, 4,0,
	2,0, 0,0, -2,0, -4,0, -5,0, -6,0, -7,0, -7,0, -6,0, -5,0,
	-4,0, -2,0, 0,0, 2,0, 4,0, 5,0, 6,0, 7,0, 7,0, 6,0,
	5,0, 4,0, 2,0, 0,0, -2,0, -4,0, -5,0, -6,0, -7,0, -7,0,
	-6,0, -5,0, -4,0, -2,0, 0,0, 2,0, 4,0, 5,0, 6,0, 7,0,
	7,0, 6,0, 5,0, 4,0, 2,0, 0,0, -2,0, -4,0, -5,0, -6,0,
	-7,0, -7,0, -6,0, -5,0, -4,0, -2,0, 0,0, 2,0, 4,0, 5,0,
	6,0, 7,0, 7,0, 6,0, 5,0, 4,0, 2,0, 0,0, -2,0, -4,0,
	-5,0, -6,0, -7,0, -7,0, -6,0, -5,0, -4,0, -2,0, 0,0, 2,0,
	4,0, 5,0, 6,0, 7,0, 7,0, 6,0, 5,0, 4,0, 2,0, 0,0,
	-2,0, -4,0, -5,0, -6,0, -7,0, -7,0, -6,0, -5,0, -4,0, -2,0,
	-1,0,
	0
};

extern int table_dynamitef[100]
{
	253, 252, 254, 252, 252, 255, 252, 254, 253, 252,
	253, 254, 255, 252, 255, 253, 252, 254, 252, 255,
	253, 254, 252, 253, 255, 254, 255, 252, 253, 254,
	255, 252, 253, 254, 255, 254, 254, 253, 254, 255,
	253, 252, 255, 254, 255, 253, 252, 254, 253, 255,
	253, 254, 252, 253, 255, 254, 252, 255, 253, 254,
	255, 253, 252, 254, 255, 254, 252, 253, 254, 255,
	253, 254, 255, 254, 255, 253, 252, 254, 253, 255,
	253, 254, 255, 253, 255, 254, 255, 252, 253, 254,
	255, 253, 253, 254, 255, 254, 252, 253, 254, 255
};

extern int table_skate[34]
{
	129, 129, 129, 129, 130, 130, 130, 131, 131, 132,
	132, 133, 133, 134, 134, 134, 135, 135, 135, 135,
	134, 134, 134, 133, 133, 132, 132, 131, 131, 131,
	130, 130, 130, 130
};

extern int table_glu[25]
{
	168, 168, 169, 169, 170, 170, 171, 171, 170, 170,
	169, 169, 168, 168, 169, 169, 169, 168, 168, 169,
	169, 170, 170, 169, 168
};

extern int table_clear[70]
{
	40, 40, 40, 40, 41, 41, 41, 41, 40, 40,
	40, 40, 40, 40, 40, 41, 41, 41, 40, 40,
	40, 40, 40, 40, 40, 41, 41, 41, 40, 40,
	42, 42, 42, 43, 43, 43, 44, 44, 44, 45,
	45, 45, 46, 46, 47, 47, 46, 46, 47, 47,
	46, 46, 47, 47, 46, 46, 47, 47, 46, 46,
	47, 47, 46, 46, 47, 47, 46, 46, 47, 47
};

extern int table_electro[90]
{
	266, 267, 266, 267, 266, 267, 266, 267, 266, 267,
	266, 267, 266, 267, 266, 267, 266, 267, 266, 267,
	266, 267, 266, 267, 266, 267, 266, 267, 266, 267,
	40, 40, 40, 40, 41, 41, 41, 41, 40, 40,
	40, 40, 40, 40, 40, 41, 41, 41, 40, 40,
	40, 40, 40, 40, 40, 41, 41, 41, 40, 40,
	42, 42, 42, 43, 43, 43, 44, 44, 44, 45,
	45, 45, 46, 46, 47, 47, 46, 46, 47, 47,
	46, 46, 47, 47, 46, 46, 47, 47, 46, 46
};

extern int table_chenille[6]{ 311, 312, 313, 314, 315, 316 };

extern int table_chenillei[6]{ 316, 315, 314, 313, 312, 311 };

extern int table_adapt_decor[144]
{
	153, 147, 148, 146, 40, 151, 150, 144, 39, 152,
	149, 145, 38, 36, 37, 35, 153, 147, 148, 146,
	40, 151, 150, 144, 39, 152, 149, 145, 38, 36,
	37, 156, 75, 75, 155, 155, 75, 75, 155, 155,
	74, 74, 154, 154, 75, 75, 155, 155, 157, 157,
	157, 157, 109, 109, 109, 109, 108, 108, 108, 108,
	107, 107, 107, 107, 202, 202, 138, 138, 202, 202,
	138, 138, 202, 202, 138, 138, 202, 202, 138, 138,
	283, 283, 283, 283, 262, 262, 262, 262, 263, 263,
	263, 263, 261, 261, 261, 261, 361, 359, 360, 352,
	357, 353, 355, 349, 358, 354, 356, 350, 351, 347,
	348, 341, 387, 387, 386, 386, 394, 394, 392, 392,
	395, 395, 393, 393, 397, 397, 396, 396, 251, 254,
	254, 254, 251, 258, 260, 258, 251, 257, 259, 257,
	251, 250, 256, 250
};

extern int table_adapt_fromage[32]
{
	-1, 265, 264, 268, 267, 273, 271, 275, 266, 272,
	270, 274, 269, 277, 276, 278, -1, 286, 285, 289,
	288, 294, 292, 296, 287, 293, 291, 295, 290, 298,
	297, 299
};

extern int table_shield[]
{
	16,
	144, 145, 146, 147, 148, 149, 150, 151, 266, 267,
	268, 269, 270, 271, 272, 273
};

extern int table_shield_blupi[]
{
	16,
	144, 145, 146, 147, 148, 149, 150, 151, 266, 267,
	268, 269, 270, 271, 272, 273
};

extern int table_power[]{ 8, 136, 137, 138, 139, 140, 141, 142, 143 };

extern int table_invert[]
{
	20,
	187, 187, 187, 188, 189, 190, 191, 192, 193, 194,
	187, 187, 187, 194, 193, 192, 191, 190, 189, 188
};

extern int table_charge[]{ 6, 238, 239, 240, 241, 242, 243 };

extern int table_magicloop[]{ 5, 152, 153, 154, 155, 156 };

extern int table_magictrack[]
{
	24,
	152, 153, 154, 155, 156, 152, 153, 154, 155, 156,
	157, 158, 159, 160, 157, 158, 159, 160, 161, 162,
	163, 164, 165, 166
};

extern int table_shieldloop[]{ 5, 274, 275, 276, 277, 278 };

extern int table_shieldtrack[]
{
	20,
	274, 275, 276, 277, 278, 274, 275, 276, 277, 278,
	279, 280, 281, 282, 283, 284, 285, 286, 287, 288
};

extern int table_drinkeffect[]{ 5, 274, 275, 276, 277, 278 };

extern int table_drinkoffset[]{ 3, 0, 7, 22 };

extern int table_tresortrack[]
{
	11,
	166, 165, 164, 163, 162, 161, 162, 163, 164, 165,
	166
};

extern int table_decor_piege1[]
{
	16,
	374, 374, 373, 347, 373, 374, 374, 374, 373, 347,
	347, 373, 374, 374, 374, 374
};

extern int table_decor_piege2[]{ 4, 374, 373, 347, 373 };

extern int table_decor_goutte[]
{
	48,
	410, 409, 410, -1, -1, -1, -1, -1, -1, 410,
	409, 408, 409, 410, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, 410, 409, 408, 407, 406, 405,
	404, 405, 406, 407, 408, 409, 410, -1, -1, -1,
	-1, 410, 409, 410, -1, -1, -1, -1
};

extern int table_decor_ecraseur[]{ 10, 317, 317, 318, 319, 320, 321, 322, 323, 323, 323 };

extern int table_decor_scie[]{ 6, 378, 379, 380, 381, 382, 383 };

extern int table_decor_temp[]
{
	20,
	328, 328, 327, 327, 326, 326, 325, 325, 324, 324,
	325, 325, 326, 326, 327, 329, 328, 328, -1, -1
};

extern int table_decor_eau1[]{ 6, 92, 93, 94, 95, 94, 93 };

extern int table_decor_eau2[]{ 6, 91, 96, 97, 98, 97, 96 };



extern int table_decor_ventillod[]{ 3, 129, 130, 131 };

extern int table_decor_ventilloh[]{ 3, 132, 133, 134 };

extern int table_decor_ventillob[]{ 3, 135, 136, 137 };



extern int table_decor_ventd[]{ 4, 114, 115, 116, 117 };

extern int table_decor_venth[]{ 4, 118, 119, 120, 121 };

extern int table_decor_ventb[]{ 4, 122, 123, 124, 125 };

extern int table_marine[]
{
	0, 2, 5, 8, 3, 0
};

extern int table_36418[]{ 14, 10, 2, 3, 4, 5, 6, 7, 8, 9, 1, 11, 12, 13, 14 };
extern int table_36458[]{ 10, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29 };
extern int table_36488[]{ 4, 15, 16, 17, 18 };
extern int table_364a0[]{ 2, 73, 22 };
extern int table_364b0[]{ 7, 78, 79, 80, 81, 82, 83, 84 };
extern int table_364d0[]{ 4, 87, 88, 89, 90 };
extern int table_364e8[]{ 2, 85, 86 };
extern int table_364f8[]{ 5, 396, 388, 389, 390, 391 };
extern int table_36510[]{ 3, 398, 399, 400 };
extern int table_36520[]{ 3, 87, 88, 89 };
extern int table_36530[]{ 1, 0x99 };
extern int table_36538[]{ 2, 0x9a, 0x9b };
extern int table_36548[]{ 1, 0xb9 };
extern int table_36550[]{ 7, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f };
extern int table_36570[]{ 12, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xe6, 0xe7, 0xe9, 0xea };
extern int table_365a8[]{ 8, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe8 };
extern int table_365d0[]{ 1, 0x9d };
extern int table_365d8[]{ 5, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f };
extern int table_365f0[]{ 7, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0 };
extern int table_36610[]{ 5, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5 };
extern int table_decor_lave[]{ 8, 68, 69, 70, 71, 72, 71, 70, 69 };
extern int table_36630[]{ 2, 0x5b, 0x5c };
extern int table_decor_ventillog[]{ 3, 126, 127, 128 };
extern int table_decor_ventg[]{ 4, 110, 111, 112, 113 };
extern int table_36670[]{ 11, 0x4c, 0x4d, 0xc7, 0xc6, 0xc8, 0xc9, 0xeb, 0xec, 0x177, 0x178, 0x179 };
extern int table_366a0[]{ 3, 0x193, 0x191, 0x192 };
extern int table_366b0[]{ 3, 20, 21, 22 };
extern int table_366c0[]{ 4, 16, 17, 18, 19 };
extern int table_366d8[]{ 3, 23, 24, 25 };
extern int table_366e8[]{ 2, 0x1a, 0x1b };
extern int table_366f8[]{ 4, 0x1c, 0x1d, 0x1e, 0x1f };
extern int table_36710[]{ 12, 0x2d, 0x2e, 0x2f, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c};
extern int table_36748[]{ 4, 0x42, 0x43, 0x44, 0x45 };




extern int table_ressort[] // i dont really care to look this up right now so heres some bs
{
	8,1,2,3,4,5,5,6,7,7
};