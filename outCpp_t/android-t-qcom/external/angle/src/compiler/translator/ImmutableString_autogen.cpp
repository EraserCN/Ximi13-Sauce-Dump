// GENERATED FILE - DO NOT EDIT.
// Generated by gen_builtin_symbols.py using data from builtin_variables.json and
// builtin_function_declarations.txt.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ImmutableString_autogen.cpp: Wrapper for static or pool allocated char arrays, that are
// guaranteed to be valid and unchanged for the duration of the compilation. Implements
// mangledNameHash using perfect hash function from gen_builtin_symbols.py

#include "compiler/translator/ImmutableString.h"

std::ostream &operator<<(std::ostream &os, const sh::ImmutableString &str)
{
    return os.write(str.data(), str.length());
}

#if defined(_MSC_VER)
#    pragma warning(disable : 4309)  // truncation of constant value
#endif

namespace
{

constexpr int mangledkT1[] = {3546, 2600, 2348, 169,  532,  3775, 2253, 3125, 1751, 1314,
                              3710, 2091, 2556, 3068, 2568, 1744, 1901, 804,  1150, 864,
                              3239, 2611, 1726, 2407, 3292, 2026, 3216, 991,  2572, 3704,
                              3659, 845,  2548, 55,   888,  2695, 863,  2540, 902,  163};
constexpr int mangledkT2[] = {89,   1293, 21,   1365, 406,  752,  3029, 444,  1838, 1852,
                              4066, 4072, 409,  1997, 1064, 340,  749,  3552, 3712, 3685,
                              115,  1038, 2453, 411,  3752, 2161, 2519, 2094, 2188, 2643,
                              624,  3569, 2792, 1608, 41,   149,  148,  3789, 4093, 1937};
constexpr int mangledkG[]  = {
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1705, 0,
    0,    2921, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    3645, 0,    0,    0,    0,    0,    602,  0,
    0,    0,    750,  0,    1172, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1096,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    2749, 0,    233,  0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1379, 3371, 3210,
    0,    0,    3069, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    1028, 0,    0,    0,    0,    0,    1856, 0,    2313, 0,    0,    0,    0,    736,  0,
    0,    0,    2608, 0,    0,    0,    0,    0,    0,    601,  0,    6,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2071, 0,    0,    0,    0,    0,    0,    2629, 1847, 2869, 0,
    0,    2780, 0,    2040, 0,    98,   0,    0,    0,    3438, 0,    0,    0,    0,    0,    839,
    0,    0,    0,    0,    0,    0,    0,    3773, 0,    0,    1852, 0,    0,    0,    2270, 2530,
    0,    3883, 3634, 2205, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    3795, 0,    126,  0,    1888, 1956, 0,    0,    0,    1831, 0,    476,  0,    0,    0,    0,
    0,    2016, 0,    0,    0,    0,    0,    0,    1688, 0,    0,    0,    1059, 0,    0,    0,
    0,    0,    2123, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    2986, 0,    0,
    0,    0,    0,    3625, 0,    0,    0,    1948, 0,    0,    808,  0,    0,    0,    0,    0,
    0,    0,    0,    0,    3215, 0,    0,    3496, 1865, 0,    790,  1837, 734,  0,    402,  0,
    3292, 2986, 0,    0,    0,    0,    0,    18,   321,  1433, 0,    0,    0,    0,    2463, 1120,
    0,    2520, 0,    0,    0,    0,    48,   1608, 3952, 3485, 3863, 1024, 0,    821,  3675, 0,
    0,    1449, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1869, 0,    3635, 43,
    2872, 0,    0,    3093, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    3018, 0,
    80,   0,    3464, 270,  0,    0,    1436, 653,  0,    0,    3369, 0,    2961, 0,    1330, 69,
    2203, 0,    15,   0,    0,    0,    4076, 2197, 2003, 0,    0,    0,    0,    3004, 0,    0,
    0,    1325, 1853, 0,    0,    0,    390,  0,    0,    0,    0,    0,    0,    0,    0,    3457,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1751, 0,    2019,
    2208, 0,    2527, 0,    0,    0,    0,    1672, 0,    0,    1940, 3942, 0,    2398, 0,    1758,
    0,    0,    0,    384,  0,    466,  0,    822,  2654, 611,  558,  0,    3744, 0,    0,    0,
    0,    3969, 0,    315,  0,    0,    2884, 0,    0,    439,  0,    0,    566,  2401, 0,    0,
    969,  3930, 629,  2210, 0,    0,    3513, 921,  0,    0,    2875, 0,    0,    0,    789,  3257,
    0,    0,    30,   0,    0,    0,    0,    0,    0,    0,    3761, 2938, 0,    0,    0,    0,
    831,  0,    0,    1786, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    1825, 0,    0,    3683, 1685, 0,    0,    0,    0,    1955, 0,    0,    1004, 1324,
    3985, 1350, 0,    0,    0,    0,    0,    514,  0,    0,    3922, 0,    2890, 0,    0,    1216,
    0,    0,    0,    0,    1847, 1310, 0,    0,    3532, 0,    0,    930,  311,  0,    3470, 0,
    0,    205,  278,  2646, 0,    482,  0,    0,    0,    0,    763,  0,    0,    2929, 0,    0,
    2421, 844,  2580, 863,  1743, 664,  0,    1831, 0,    0,    1145, 819,  0,    1328, 3264, 0,
    0,    515,  1936, 108,  0,    2589, 3861, 0,    0,    0,    0,    369,  1792, 153,  0,    852,
    0,    248,  1727, 3294, 4084, 1114, 2987, 0,    0,    0,    0,    3177, 3640, 0,    0,    0,
    0,    2131, 211,  0,    767,  3062, 0,    508,  885,  0,    1366, 432,  2181, 1819, 0,    0,
    2518, 0,    0,    3648, 559,  0,    1946, 575,  0,    0,    1546, 0,    0,    0,    0,    0,
    1642, 2248, 0,    0,    3236, 0,    0,    0,    0,    0,    2804, 0,    0,    0,    2410, 3872,
    4056, 0,    0,    3257, 0,    0,    0,    2188, 695,  0,    0,    3984, 2444, 0,    0,    0,
    0,    0,    800,  1867, 3965, 3412, 492,  3388, 765,  678,  0,    1788, 0,    795,  0,    1376,
    0,    0,    3199, 0,    0,    1353, 2750, 1544, 641,  0,    2017, 2904, 0,    757,  3880, 0,
    1720, 3810, 0,    3578, 692,  165,  1948, 0,    1185, 3213, 0,    1735, 0,    1604, 567,  0,
    0,    0,    0,    0,    0,    0,    407,  904,  1058, 1282, 0,    520,  0,    3568, 1736, 445,
    689,  0,    0,    882,  0,    0,    0,    548,  0,    0,    0,    0,    0,    0,    1512, 3977,
    1771, 3246, 0,    1259, 0,    0,    3535, 0,    0,    0,    0,    237,  0,    0,    0,    2275,
    0,    0,    1332, 0,    0,    1215, 0,    355,  0,    862,  0,    1166, 0,    2338, 898,  139,
    33,   0,    2210, 0,    3934, 1306, 3404, 0,    1193, 0,    1382, 0,    1010, 1520, 0,    0,
    364,  0,    0,    0,    0,    0,    0,    0,    0,    4069, 2142, 0,    575,  723,  2716, 0,
    0,    0,    44,   0,    2751, 503,  0,    0,    0,    607,  776,  3028, 0,    0,    771,  0,
    629,  0,    2943, 1674, 0,    1566, 948,  3326, 0,    1388, 0,    551,  0,    0,    3652, 2016,
    0,    3289, 0,    1291, 1604, 1090, 1794, 707,  0,    1418, 486,  6,    0,    3086, 2289, 0,
    0,    1056, 303,  937,  196,  0,    0,    1006, 1906, 680,  0,    1146, 771,  0,    528,  0,
    0,    0,    0,    3061, 0,    624,  0,    0,    3452, 2657, 2333, 0,    0,    0,    0,    0,
    2613, 0,    0,    0,    1119, 2860, 1268, 0,    0,    0,    3693, 0,    649,  0,    0,    3106,
    2752, 0,    2317, 0,    0,    2791, 148,  3932, 2379, 0,    0,    0,    0,    3786, 0,    0,
    0,    0,    3974, 0,    746,  0,    0,    621,  3334, 4039, 174,  0,    0,    1925, 0,    1474,
    1138, 180,  279,  0,    0,    0,    1159, 0,    1477, 0,    0,    849,  762,  3880, 2025, 0,
    0,    2468, 633,  0,    1857, 1467, 628,  863,  2019, 0,    385,  462,  0,    0,    0,    1817,
    1779, 0,    243,  548,  769,  0,    0,    0,    3392, 0,    1952, 1614, 2960, 2644, 0,    0,
    1073, 0,    0,    0,    0,    0,    93,   0,    2520, 0,    2269, 1620, 0,    2559, 0,    2895,
    0,    3826, 28,   2093, 0,    2121, 1172, 1621, 0,    0,    4,    0,    633,  0,    0,    1764,
    3663, 0,    733,  1362, 3308, 2709, 0,    2918, 31,   609,  230,  2839, 0,    3482, 0,    0,
    1664, 3741, 0,    0,    0,    0,    3841, 0,    645,  0,    0,    1505, 2971, 0,    459,  3958,
    0,    997,  0,    2128, 971,  208,  411,  0,    760,  0,    0,    580,  530,  0,    0,    848,
    2595, 2619, 0,    0,    2438, 1029, 0,    2503, 2195, 0,    1451, 0,    0,    3767, 0,    0,
    2168, 0,    0,    0,    3718, 0,    1464, 0,    4088, 0,    809,  0,    0,    0,    1504, 1678,
    121,  1133, 3486, 0,    3897, 860,  0,    0,    673,  3366, 0,    0,    0,    0,    0,    3599,
    0,    2714, 263,  0,    0,    929,  0,    0,    0,    0,    0,    0,    844,  0,    0,    1858,
    257,  0,    2181, 0,    0,    0,    3886, 2897, 0,    902,  3930, 0,    688,  353,  0,    0,
    1356, 138,  0,    0,    1392, 0,    0,    1569, 560,  0,    0,    3674, 0,    0,    0,    0,
    0,    752,  1097, 2127, 112,  0,    0,    1271, 2014, 0,    56,   0,    0,    0,    65,   791,
    2042, 3396, 2921, 0,    0,    790,  0,    3626, 0,    1219, 0,    0,    608,  0,    3501, 0,
    0,    0,    0,    0,    0,    0,    0,    715,  3915, 0,    797,  1967, 0,    645,  3317, 0,
    1999, 0,    2052, 1898, 0,    0,    975,  2511, 160,  1867, 0,    0,    0,    3470, 0,    0,
    3827, 303,  1629, 0,    0,    875,  0,    202,  0,    2309, 3758, 3828, 2991, 1853, 0,    0,
    0,    0,    0,    0,    4058, 1071, 3927, 0,    2160, 0,    0,    0,    0,    0,    100,  1349,
    0,    0,    1973, 3913, 3317, 2868, 1593, 1451, 2802, 2616, 0,    3147, 0,    3749, 0,    0,
    0,    1528, 1916, 3219, 0,    0,    0,    0,    516,  0,    1019, 0,    909,  383,  0,    1811,
    0,    501,  179,  0,    1014, 1724, 3104, 1444, 344,  0,    2156, 0,    3709, 1581, 3968, 3511,
    2765, 0,    0,    137,  300,  0,    0,    0,    3513, 1199, 1632, 1272, 0,    2602, 1362, 0,
    0,    0,    1169, 3821, 0,    0,    2020, 0,    0,    1149, 0,    0,    0,    1644, 1430, 3500,
    1082, 0,    0,    2110, 2430, 453,  3067, 1395, 2593, 0,    719,  0,    4078, 0,    0,    0,
    715,  0,    0,    0,    1037, 3257, 1392, 1411, 593,  0,    0,    1707, 769,  0,    0,    1747,
    58,   0,    732,  0,    0,    289,  1289, 0,    0,    0,    0,    2193, 2013, 284,  0,    0,
    1573, 0,    0,    263,  0,    0,    0,    3503, 2846, 3599, 0,    0,    986,  0,    2159, 0,
    0,    2228, 0,    3729, 0,    0,    2356, 0,    0,    3651, 3074, 0,    0,    0,    0,    1203,
    3061, 1930, 1742, 1523, 0,    1137, 0,    0,    1620, 2069, 0,    0,    0,    0,    0,    1452,
    1620, 625,  1433, 0,    1907, 0,    0,    0,    896,  0,    0,    857,  0,    0,    174,  2013,
    2952, 1618, 0,    203,  903,  252,  0,    1029, 1311, 0,    0,    0,    0,    0,    955,  2082,
    0,    0,    3630, 0,    0,    1706, 0,    272,  0,    2007, 842,  2921, 525,  372,  0,    118,
    1515, 0,    3019, 33,   0,    0,    3249, 0,    4,    94,   3073, 0,    3762, 186,  796,  391,
    0,    4094, 0,    0,    0,    830,  0,    0,    0,    0,    0,    0,    0,    3383, 3558, 0,
    0,    1264, 1156, 0,    1971, 0,    894,  1471, 0,    0,    2775, 3520, 897,  729,  0,    3745,
    1131, 0,    2549, 0,    1345, 1440, 797,  0,    1441, 1332, 0,    1963, 0,    226,  1365, 0,
    0,    1281, 0,    2291, 617,  276,  3604, 2906, 0,    91,   0,    0,    0,    0,    973,  1536,
    0,    0,    57,   1938, 0,    0,    2879, 0,    0,    0,    0,    951,  0,    0,    0,    0,
    1208, 0,    0,    0,    3012, 0,    0,    1743, 0,    1699, 3206, 0,    3110, 3958, 0,    0,
    1497, 0,    1805, 1706, 0,    2594, 1149, 0,    1734, 0,    667,  853,  0,    639,  0,    0,
    0,    191,  0,    1121, 383,  234,  0,    0,    0,    1907, 246,  0,    0,    0,    1945, 19,
    0,    0,    0,    0,    0,    0,    0,    1324, 2550, 2539, 556,  428,  418,  2386, 3773, 1721,
    0,    2546, 0,    0,    3315, 0,    0,    0,    688,  1127, 2903, 0,    0,    3849, 3815, 1875,
    0,    0,    2811, 1523, 1753, 2949, 3299, 1087, 2534, 0,    2086, 3852, 0,    3013, 3154, 2799,
    1346, 0,    550,  515,  0,    0,    2679, 0,    0,    0,    209,  0,    1160, 1344, 3125, 0,
    1004, 402,  1414, 799,  0,    3818, 0,    292,  0,    798,  782,  0,    3462, 0,    829,  0,
    0,    0,    66,   0,    2499, 3553, 405,  0,    0,    0,    274,  1425, 0,    0,    4058, 1290,
    3610, 0,    0,    0,    3341, 0,    3889, 0,    0,    624,  289,  0,    0,    2038, 311,  814,
    25,   0,    0,    721,  211,  945,  313,  2463, 0,    3524, 0,    1077, 0,    0,    0,    1389,
    2141, 0,    0,    3738, 3577, 535,  991,  0,    0,    0,    0,    1563, 2114, 2978, 0,    0,
    0,    1612, 0,    654,  0,    1110, 0,    0,    1744, 2150, 1431, 2807, 0,    513,  0,    240,
    0,    0,    2893, 181,  2885, 3485, 1909, 0,    3687, 3127, 3220, 0,    0,    0,    0,    1518,
    0,    107,  0,    0,    1948, 0,    2899, 0,    165,  1733, 0,    855,  3709, 0,    1826, 0,
    56,   0,    0,    3972, 1453, 1872, 0,    2271, 1909, 1056, 570,  2846, 3495, 381,  0,    0,
    409,  1700, 0,    1189, 799,  0,    1685, 574,  2549, 0,    1869, 537,  1440, 1802, 295,  0,
    794,  0,    0,    3713, 1587, 1520, 12,   0,    948,  2899, 0,    0,    432,  0,    2588, 0,
    1862, 0,    0,    761,  0,    1925, 0,    0,    1340, 0,    0,    3686, 0,    3928, 518,  0,
    0,    0,    0,    0,    0,    3545, 920,  0,    0,    0,    0,    757,  0,    2948, 0,    1394,
    0,    0,    1513, 547,  1920, 338,  0,    294,  3532, 0,    0,    2918, 0,    0,    0,    412,
    1363, 0,    0,    0,    2861, 1402, 468,  0,    1510, 0,    0,    436,  549,  2784, 1844, 1756,
    3368, 0,    0,    0,    4035, 1597, 3717, 1210, 3379, 0,    0,    1294, 1577, 2873, 1118, 2277,
    433,  0,    213,  0,    1926, 1984, 0,    1007, 2562, 1707, 3311, 0,    3490, 0,    1120, 1845,
    3952, 1600, 0,    846,  0,    0,    668,  471,  1097, 0,    0,    0,    2126, 2147, 0,    936,
    0,    4088, 0,    0,    0,    0,    4025, 2015, 0,    1536, 0,    295,  0,    0,    801,  0,
    54,   961,  1702, 4057, 0,    0,    0,    3076, 0,    1770, 0,    0,    533,  835,  1135, 4022,
    0,    0,    84,   2768, 0,    0,    101,  0,    3287, 0,    0,    470,  0,    603,  1019, 0,
    0,    2153, 1456, 0,    0,    114,  0,    0,    812,  0,    0,    2168, 3378, 1352, 0,    1819,
    0,    3248, 0,    969,  1235, 0,    0,    670,  2005, 2654, 0,    633,  2508, 0,    0,    0,
    1726, 514,  0,    2578, 0,    3149, 146,  0,    3755, 480,  2284, 0,    887,  2641, 2461, 0,
    0,    3471, 2099, 3389, 3244, 1116, 1506, 3606, 0,    0,    0,    3380, 1172, 2901, 552,  571,
    0,    1016, 0,    2490, 1348, 0,    642,  0,    0,    0,    0,    1162, 2670, 0,    2468, 3513,
    0,    0,    1309, 0,    0,    1181, 640,  0,    1119, 0,    0,    1233, 2827, 74,   2427, 3706,
    0,    1758, 0,    0,    0,    3675, 0,    0,    2174, 127,  0,    0,    0,    846,  0,    0,
    0,    0,    0,    3518, 403,  1146, 706,  0,    0,    0,    1310, 266,  438,  443,  1210, 2048,
    0,    137,  0,    2830, 174,  625,  3957, 0,    0,    0,    3167, 0,    0,    0,    2090, 3743,
    65,   0,    3284, 1469, 963,  711,  548,  0,    945,  2039, 3628, 0,    0,    227,  2115, 3006,
    214,  0,    4051, 3975, 391,  0,    1440, 2501, 1766, 3979, 0,    0,    0,    0,    17,   0,
    2302, 3386, 302,  0,    995,  3867, 0,    789,  0,    988,  1205, 1787, 3295, 3454, 3405, 0,
    0,    0,    583,  0,    580,  0,    0,    2025, 1739, 1574, 1912, 0,    734,  2129, 154,  3142,
    3695, 908,  0,    0,    0,    370,  436,  697,  0,    552,  0,    1748, 2956, 2338, 1554, 1484,
    0,    1610, 0,    464,  1924, 2506, 1343, 604,  1238, 3029, 1125, 0,    0,    1091, 3552, 4034,
    1487, 3348, 768,  0,    258,  0,    1964, 0,    1460, 1578, 3080, 0,    0,    0,    804,  0,
    4102, 254,  439,  0,    3052, 0,    1026, 3127, 0,    0,    3507, 0,    0,    0,    0,    1552,
    2648, 658,  0,    852,  316,  0,    1683, 3199, 4105, 2934, 0,    0,    948,  804,  2504, 1936,
    0,    0,    0,    2025, 0,    1214, 81,   0,    1828, 3517, 0,    0,    0,    1181, 0,    1603,
    0,    884,  0,    1571, 0,    1570, 0,    0,    1861, 0,    0,    0,    0,    3013, 377,  0,
    0,    3593, 2230, 0,    0,    1615, 0,    0,    0,    0,    0,    1384, 0,    0,    458,  1311,
    0,    0,    1039, 0,    1609, 0,    0,    0,    2326, 1990, 0,    1624, 3233, 2681, 0,    418,
    2113, 1057, 3466, 0,    3019, 3705, 2536, 0,    0,    452,  13,   0,    0,    3904, 3961, 3122,
    0,    0,    0,    1024, 0,    564,  0,    2976, 3693, 1005, 0,    38,   1775, 958,  0,    0,
    0,    129,  0,    0,    3986, 0,    0,    2989, 0,    2009, 1890, 0,    0,    0,    2050, 0,
    0,    622,  0,    159,  1524, 0,    747,  501,  0,    741,  0,    0,    1439, 0,    3633, 3563,
    3575, 0,    0,    403,  0,    1955, 717,  1666, 0,    3161, 0,    1045, 2788, 0,    0,    2998,
    2799, 1860, 990,  192,  0,    1267, 0,    2705, 974,  151,  2231, 3022, 3996, 0,    4029, 423,
    1258, 0,    674,  3589, 0,    2497, 0,    2601, 3570, 0,    0,    0,    3204, 2042, 2047, 0,
    26,   0,    2863, 1808, 1695, 1844, 1529, 1825, 0,    0,    2403, 477,  0,    2370, 862,  0,
    0,    0,    1694, 3216, 0,    0,    1677, 2981, 0,    682,  975,  0,    0,    0,    0,    880,
    0,    1985, 803,  538,  1190, 0,    3872, 0,    0,    690,  306,  762,  0,    327,  0,    1139,
    230,  0,    1362, 2918, 1660, 1707, 2068, 1607, 232,  42,   70,   0,    0,    1229, 354,  0,
    3204, 0,    0,    0,    3951, 0,    3955, 0,    0,    1165, 0,    1927, 389,  0,    3127, 264,
    2441, 2195, 1572, 0,    3167, 0,    800,  4051, 3252, 0,    759,  1565, 2595, 0,    0,    2750,
    2563, 0,    0,    0,    0,    2411, 0,    0,    253,  0,    992,  2369, 0,    0,    0,    0,
    1655, 1229, 0,    0,    1800, 257,  3590, 0,    0,    1800, 138,  3925, 2540, 0,    1642, 0,
    0,    1230, 3965, 1342, 0,    0,    0,    1788, 1574, 631,  0,    0,    0,    0,    0,    3093,
    2053, 256,  575,  3556, 1910, 0,    0,    259,  0,    1008, 827,  0,    598,  767,  3680, 692,
    0,    139,  3867, 483,  3975, 1995, 0,    1192, 3403, 969,  2607, 1152, 881,  0,    0,    0,
    0,    1793, 724,  0,    0,    209,  1201, 269,  0,    3717, 3378, 447,  0,    1503, 0,    0,
    396,  0,    1647, 0,    0,    0,    0,    0,    0,    0,    0,    931,  0,    457,  0,    2735,
    834,  0,    0,    3912, 2765, 3764, 2966, 0,    0,    0,    2174, 4084, 0,    3147, 882,  1848,
    306,  0,    0,    3311, 0,    728,  0,    813,  1567, 1524, 1906, 0,    220,  3261, 0,    0,
    685,  0,    18,   1557, 0,    914,  0,    860,  0,    3550, 0,    1293, 3721, 1254, 0,    2302,
    2071, 2457, 1265, 3964, 258,  0,    341,  0,    1802, 1374, 261,  0,    2096, 1561, 0,    1197,
    0,    0,    85,   858,  0,    0,    3592, 0,    3888, 0,    1890, 1864, 197,  1366, 2486, 128,
    3150, 0,    2676, 0,    0,    651,  0,    3330, 2087, 2437, 2068, 0,    1769, 0,    2365, 0,
    2655, 1294, 924,  3139, 520,  2054, 2611, 1298, 0,    1093, 0,    33,   3894, 874,  737,  1538,
    0,    0,    0,    1231, 0,    567,  0,    0,    3393, 0,    0,    472,  1708, 626,  1753, 0,
    2511, 0,    0,    0,    1441, 3539, 0,    2141, 0,    0,    915,  250,  1498, 1631, 3911, 1986,
    0,    968,  3148, 0,    592,  0,    460,  1336, 1800, 0,    0,    0,    0,    1740, 3075, 1184,
    0,    2673, 3860, 0,    215,  1918, 1586, 1479, 1881, 252,  2637, 1213, 0,    0,    137,  0,
    110,  3945, 2605, 104,  3106, 1109, 3928, 2137, 1885, 1515, 1008, 0,    0,    3599, 0,    1884,
    3905, 1525, 3002, 0,    0,    1700, 0,    0,    2151, 1407, 531,  0,    0,    0,    2218, 0,
    4028, 743,  1898, 2177, 1507, 0,    2819, 0,    0,    0,    0,    371,  0,    222,  3479, 0,
    1430, 0,    3830, 0,    3065, 3523, 1655, 0,    0,    132,  2290, 1796, 287,  966,  0,    1782,
    0,    3848, 124,  2967, 0,    3110, 0,    74,   833,  1250, 0,    0,    0,    0,    132,  4092,
    2101, 333,  144,  89,   0,    816,  0,    1457, 1815, 952,  0,    0,    289,  727,  0,    3314,
    946,  0,    946,  957,  798,  726,  345,  0,    944,  1626, 1478, 0,    0,    413,  169,  2783,
    0,    0,    521,  1546, 2537, 280,  1909, 0,    903,  0,    0,    842,  0,    2514, 0,    2447,
    3755, 0,    883,  0,    1629, 0,    0,    1451, 0,    3946, 3317, 0,    1524, 0,    0,    0,
    0,    315,  0,    0,    2055, 0,    1077, 0,    4069, 2658, 0,    2895, 0,    0,    0,    3804,
    0,    0,    2478, 1541, 2786, 0,    0,    1464, 1051, 0,    2435, 832,  0,    0,    0,    1306,
    1535, 111,  0,    489,  0,    0,    2767, 573,  0,    0,    3117, 0,    331,  0,    978,  3563,
    2082, 0,    1650, 1499, 2037, 0,    2810, 1543, 4099, 443,  1241, 0,    0,    1548, 71,   1184,
    0,    263,  0,    934,  0,    0,    3455, 0,    361,  0,    1438, 50,   2344, 983,  2716, 0,
    0,    0,    0,    982,  635,  1378, 4106, 860,  0,    1154, 1209, 0,    2104, 0,    1531, 3300,
    3783, 3764, 0,    0,    2413, 649,  3889, 2682, 462,  0,    1670, 0,    2310, 2480, 98,   0,
    2288, 2084, 1598, 1852, 1409, 0,    2075, 0,    0,    0,    1318, 0,    0,    1730, 1472, 21,
    0,    0,    304,  1682, 0,    0,    1217, 2454, 0,    0,    441,  0,    0,    0,    0,    0,
    2109, 2273, 639,  0,    71,   714,  1045, 1126, 2907, 0,    0,    3120, 1623, 3183, 2713, 0,
    3659, 270,  0,    4048, 1589, 1037, 1580, 0,    3642, 2887, 2154, 0,    3855, 0,    0,    2817,
    0,    1604, 933,  0,    2600, 0,    0,    0,    62,   0,    0,    455,  1019, 0,    0,    0,
    0,    2135, 1327, 2326, 1786, 594,  3648, 0,    3770, 0,    3125, 2862, 594,  4072, 1141, 0,
    0,    0,    643,  0,    1792, 1841, 1013, 151,  0,    787,  136,  722,  966,  0,    1853, 576,
    1251, 314,  60,   178,  0,    835,  720,  0,    4079, 0,    862,  42,   523,  2092, 2036, 0,
    663,  807,  2042, 0,    1034, 2806, 872,  0,    450,  0,    0,    4098, 2684, 0,    0,    0,
    461,  1553, 389,  1397, 3143, 0,    3202, 0,    3244, 105,  0,    1048, 0,    0,    1763, 3526,
    331,  2146, 602,  0,    1482, 393,  2473, 982,  0,    1838, 0,    0,    0,    1216, 0,    0,
    3157, 2032, 1648, 492,  0,    3877, 1063, 1382, 1866, 0,    0,    3650, 1687, 79,   322,  1257,
    0,    0,    0,    223,  1593, 0,    1508, 2066, 497,  1998, 1120, 2373, 0,    2956, 0,    0,
    1489, 0,    0,    1031, 1447, 3780, 497,  0,    0,    2136, 1083, 1822, 0,    2697, 0,    2143,
    2806, 1958, 3692, 1558, 3749, 1709, 2676, 0,    0,    3397, 1236, 3656, 0,    0,    0,    0,
    1947, 1427, 1299, 0,    0,    0,    1584, 2923, 1961, 3579, 2975, 1707, 392,  1122, 3332, 66,
    3366, 0,    547,  0,    170,  0,    30,   131,  1462, 4025, 1727, 0,    1639, 0,    1299, 0,
    1234, 3816, 639,  1414, 0,    0,    0,    0,    1248, 2120, 161,  0,    0,    0,    3262, 0,
    0,    0,    0,    0,    3654, 927,  1575, 0,    1692, 0,    2582, 0,    1584, 0,    0,    0,
    2973, 1919, 1740, 1245, 1719, 0,    285,  696,  1986, 0,    0,    1405, 0,    1547, 0,    1226,
    0,    2478, 3004, 2134, 0,    0,    0,    2099, 0,    844,  0,    792,  1341, 0,    3325, 0,
    556,  0,    180,  0,    271,  0,    0,    0,    0,    0,    0,    283,  0,    518,  947,  0,
    2106, 0,    72,   1517, 1796, 2756, 0,    0,    1761, 1622, 3374, 0,    3841, 0,    0,    0,
    0,    1780, 1692, 1993, 463,  941,  2138, 0,    0,    0,    1485, 0,    0,    0,    0,    0,
    326,  1189, 415,  1210, 2824, 3307, 1450, 709,  0,    1861, 622,  1956, 0,    396,  0,    0,
    1319, 954,  1923, 1619, 133,  0,    1218, 1562, 0,    0,    0,    1545, 1228, 637,  185,  3619,
    3599, 3792, 3417, 0,    3985, 0,    1757, 1914, 2033, 1240, 1499, 0,    2068, 0,    0,    0,
    0,    0,    2638, 0,    0,    0,    3717, 3999, 405,  1187, 1575, 1602, 1912, 0,    0,    1856,
    87,   2203, 429,  0,    0,    0,    2556, 0,    974,  0,    0,    446,  585,  704,  0,    0,
    29,   2361, 392,  3,    4032, 1066, 0,    818,  244,  3776, 914,  51,   1526, 3725, 0,    0,
    214,  0,    0,    3296, 73,   1486, 0,    831,  0,    3906, 0,    3833, 1320, 0,    2282, 791,
    2126, 1630, 0,    0,    0,    0,    129,  2674, 1359, 0,    0,    1167, 3449, 54,   305,  0,
    4004, 0,    3367, 2651, 2504, 2176, 0,    1827, 0,    1189, 893,  0,    3610, 61,   183,  0,
    2745, 461,  1614, 2140, 0,    956,  0,    0,    3409, 1085, 3206, 1700, 4013, 0,    0,    4053,
    529,  1270, 1291, 0,    0,    1715, 1401, 225,  0,    1173, 0,    1099, 109,  0,    697,  467,
    2654, 820,  0,    0,    0,    0,    0,    1688, 0,    360,  883,  646,  1373, 4081, 0,    678,
    0,    0,    0,    0,    2701, 1648, 703,  0,    876,  3998, 1363, 2325, 964,  2609, 0,    1358,
    1847, 346,  0,    918,  518,  0,    225,  0,    9,    108,  1590, 2643, 3620, 0,    0,    0,
    1686, 0,    0,    0,    1571, 3263, 307,  19,   1437, 0,    668,  235,  1089, 2708, 0,    0,
    490,  176,  414,  959,  1195, 4029, 0,    0,    2273, 363,  1123, 0,    0,    0,    0,    778,
    2788, 0,    672,  92,   596,  2956, 724,  445,  1339, 3741, 329,  809,  0,    2251, 0,    1260,
    529,  1418, 3327, 0,    1478, 1872, 1911, 3182, 1093, 1628, 2946, 3783, 918,  2735, 3293, 0,
    0,    0,    0,    0,    1663, 4059, 893,  0,    0,    599,  0,    1467, 0,    871,  0,    0,
    2697, 134,  0,    400,  0,    1949, 83,   2943, 0,    0,    0,    0,    840,  0,    420,  340,
    1054, 0,    4062, 1016, 0,    1059, 0,    0,    0,    0,    2219, 779,  0,    1981, 1883, 1276,
    1796, 191,  91,   349,  578,  0,    1654, 2565, 0,    774,  0,    1386, 0,    408,  2175, 384,
    1274, 0,    1786, 0,    0,    461,  890,  0,    0,    1801, 1035, 243,  0,    877,  0,    249,
    0,    2312, 1335, 0,    228,  1449, 2869, 1111, 0,    243,  1089, 2166, 655,  0,    1132, 837,
    3068, 1920, 301,  739,  813,  1059, 1281, 2078, 755,  0,    406,  0,    0,    635,  2150, 3781,
    1945, 3850, 3658, 1407, 3640, 2462, 0,    902,  541,  2264, 0,    0,    0,    1370, 3838, 0,
    598,  0,    704,  0,    0,    4049, 3829, 551,  0,    0,    657,  0,    3180, 3095, 0,    836,
    1523, 262,  0,    2001, 1155, 0,    1157, 949,  2283, 3815, 1254, 107,  4060, 636,  0,    4086,
    739,  0,    0,    1931, 563,  1328, 985,  3170, 466,  0,    2358, 3023, 210,  1064, 204,  0,
    0,    2642, 1876, 1273, 2886, 1090, 770,  548,  0,    0,    1934, 3865, 3905, 384,  0,    141,
    0,    0,    413,  603,  3472, 0,    1761, 2152, 3604, 2279, 0,    43,   640,  335,  1714, 0,
    3843, 2810, 280,  245,  0,    0,    1934, 0,    738,  1872, 0,    570,  632,  1050, 2124, 0,
    4104, 1150, 0,    0,    0,    1,    3428, 1380, 172,  0,    1125, 0,    0,    0,    1055, 0,
    2095, 0,    0,    4064, 1619, 1592, 0,    0,    0,    82,   2993, 2118, 0,    3391, 2689, 2164,
    3095, 0,    0,    2048, 977,  236,  284,  419,  1289, 544,  3400, 1243, 0,    0,    578,  0,
    228,  0,    0,    1052, 2659, 2471, 124,  0,    0,    0,    359,  217,  2056, 2913};

int MangledHashG(const char *key, const int *T)
{
    int sum = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += T[i] * key[i];
        sum %= 4110;
    }
    return mangledkG[sum];
}

int MangledPerfectHash(const char *key)
{
    if (strlen(key) > 40)
        return 0;

    return (MangledHashG(key, mangledkT1) + MangledHashG(key, mangledkT2)) % 4110;
}

constexpr int unmangledkT1[] = {92,  345, 246, 268, 315, 73,  365, 346, 291, 195, 108, 276, 63,
                                133, 247, 248, 359, 354, 315, 180, 31,  101, 342, 377, 375, 0};
constexpr int unmangledkT2[] = {10,  306, 20, 206, 67,  31,  103, 244, 1,   206, 269, 237, 25,
                                161, 27,  70, 69,  233, 167, 337, 42,  301, 42,  211, 139, 106};
constexpr int unmangledkG[]  = {
    0,   0,   0,   0,   0,   0,   0,   171, 0,   0,   0,   110, 201, 0,   0,   0,   0,   0,   0,
    0,   65,  0,   231, 12,  0,   123, 0,   0,   0,   368, 0,   248, 0,   3,   167, 0,   0,   61,
    0,   0,   0,   130, 0,   0,   0,   0,   20,  0,   278, 0,   81,  0,   58,  0,   118, 0,   0,
    361, 0,   0,   0,   0,   284, 0,   0,   0,   59,  0,   0,   54,  45,  124, 0,   0,   0,   112,
    327, 300, 191, 0,   0,   381, 0,   175, 137, 0,   0,   322, 0,   380, 120, 0,   266, 189, 9,
    0,   117, 144, 0,   0,   0,   0,   0,   56,  0,   165, 0,   0,   0,   192, 0,   0,   35,  190,
    64,  155, 0,   0,   0,   43,  0,   0,   235, 0,   16,  0,   0,   89,  183, 197, 213, 0,   0,
    0,   170, 0,   0,   70,  379, 0,   0,   0,   283, 0,   131, 28,  201, 193, 0,   149, 265, 0,
    0,   179, 0,   21,  377, 15,  373, 20,  0,   0,   0,   0,   0,   9,   0,   23,  0,   0,   0,
    69,  362, 361, 83,  289, 0,   0,   24,  359, 351, 0,   0,   0,   0,   345, 0,   314, 103, 336,
    131, 0,   365, 108, 0,   0,   70,  69,  58,  146, 0,   77,  126, 291, 335, 0,   2,   0,   169,
    42,  135, 129, 46,  0,   127, 195, 0,   0,   78,  0,   125, 129, 217, 216, 0,   336, 0,   351,
    0,   0,   253, 166, 0,   0,   47,  178, 335, 321, 0,   173, 0,   333, 130, 0,   0,   0,   83,
    157, 48,  145, 357, 0,   138, 208, 0,   371, 15,  92,  104, 0,   105, 65,  12,  317, 347, 0,
    0,   76,  0,   0,   195, 60,  169, 324, 0,   0,   66,  9,   344, 326, 235, 28,  0,   0,   0,
    0,   62,  0,   0,   0,   259, 173, 0,   181, 0,   6,   87,  0,   128, 30,  0,   0,   0,   110,
    144, 0,   123, 0,   55,  0,   100, 0,   231, 5,   14,  318, 23,  26,  0,   0,   0,   0,   280,
    25,  380, 15,  0,   122, 73,  0,   356, 239, 132, 111, 0,   0,   72,  354, 0,   177, 205, 0,
    0,   0,   37,  370, 0,   183, 0,   316, 76,  0,   232, 178, 167, 307, 207, 131, 249, 251, 14,
    290, 103, 0,   32,  24,  207, 347, 176, 383, 126, 60,  126, 0,   41,  377, 210, 0,   125, 0,
    153, 115, 0,   0,   0,   0,   0,   199};

int UnmangledHashG(const char *key, const int *T)
{
    int sum = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        sum += T[i] * key[i];
        sum %= 388;
    }
    return unmangledkG[sum];
}

int UnmangledPerfectHash(const char *key)
{
    if (strlen(key) > 26)
        return 0;

    return (UnmangledHashG(key, unmangledkT1) + UnmangledHashG(key, unmangledkT2)) % 388;
}

}  // namespace

namespace sh
{

template <>
const size_t ImmutableString::FowlerNollVoHash<4>::kFnvPrime = 16777619u;

template <>
const size_t ImmutableString::FowlerNollVoHash<4>::kFnvOffsetBasis = 0x811c9dc5u;

template <>
const size_t ImmutableString::FowlerNollVoHash<8>::kFnvPrime =
    static_cast<size_t>(1099511628211ull);

template <>
const size_t ImmutableString::FowlerNollVoHash<8>::kFnvOffsetBasis =
    static_cast<size_t>(0xcbf29ce484222325ull);

uint32_t ImmutableString::mangledNameHash() const
{
    return MangledPerfectHash(data());
}

uint32_t ImmutableString::unmangledNameHash() const
{
    return UnmangledPerfectHash(data());
}

}  // namespace sh