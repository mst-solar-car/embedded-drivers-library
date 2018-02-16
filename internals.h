/**
 * Header file for directives that used for the inner workings of this library.
 * They can be used in user code, but they are mainly for making things easier
 * in the library.
 *
 * Authors: Michael Rouse
 */
#ifndef __INTERNALS__
#define __INTERNALS__

#include "datatypes.h"



/* Information about a Port */
typedef struct _port_info_t {
  uint8_t   number;
  vuint8_t* const dir_reg;
  vuint8_t* const out_reg;
  vuint8_t* const in_reg;
  vuint8_t* const sel_reg;
  vuint8_t* const ies_reg;
  vuint8_t* const ie_reg;
  vuint8_t* const ifg_reg;
} port_info_t;

/* Information about a Pin */
typedef struct _pin_info_t {
  port_info_t* port;
  uint8_t bit;
} pin_info_t;

/* Maps pins on a microcontroller to a port and a bit */
typedef struct _pin_map_t {
  uint8_t port;
  uint8_t bit;
} pin_map_t;

/* Returns information about a pin */
#define GetPinInfo(pin)                                                       \
  (                                                                           \
    (                                                                         \
      (uint8_t)(pin) > (uint8_t)(MC_NUMBER_OF_PINS) ||                        \
      (uint8_t)(pin) < 1                                                      \
    )                                                                         \
    ? __NO_PIN_INFO :                                                         \
    ((pin_info_t){                                                            \
      &(port_map[pin_map[pin].port]),                                         \
      pin_map[pin].bit                                                        \
    })                                                                        \
  )

#define IsValidPinInfo(pi) (pi.port != (port_info_t*)NO_PORT && pi.bit != NO_BIT)

/* Pin Info for No Pin (an invalid pin) */
#define __NO_PIN_INFO               \
  ((pin_info_t) {                   \
    (port_info_t*)NO_PORT,          \
    NO_BIT,                         \
  })


/* Retrieve Port Information */
#define GetPortInfo(port)                                                     \
  (                                                                           \
    (                                                                         \
      (uint8_t)(port) > (uint8_t)(MC_NUMBER_OF_PORTS) ||                      \
      (uint8_t)(port) < 1                                                     \
    )                                                                         \
    ? __NO_PORT_INFO :                                                        \
    ((port_info_t){                                                           \
      port,                                                                   \
      (port_map[port].dir_reg),                                               \
      (port_map[port].out_reg),                                               \
      (port_map[port].in_reg ),                                               \
      (port_map[port].sel_reg),                                               \
      (port_map[port].ies_reg),                                               \
      (port_map[port].ie_reg ),                                               \
      (port_map[port].ifg_reg )                                               \
    })                                                                        \
  )

#define IsValidPortInfo(pi)   (pi.number != (uint8_t)NO_PORT)

/* Info for an invalid Port */
#define __NO_PORT_INFO              \
  ((port_info_t) {                  \
    (uint8_t)NO_PORT,               \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
    (vuint8_t*)NO_REGISTER,         \
  })



/**
 * Bit Helpers
 */
/**
 * This will convert BIT0 -> 1, BIT4 -> 5, etc... (for indexing in an array)
 * These indexes need to start at 1 because NO_BIT evaluates to 0 in an array
 */
#define GetBitIndex(b)         \
  ((uint8_t)(                   \
    (b == BIT0) ? 1  :          \
    (b == BIT1) ? 2  :          \
    (b == BIT2) ? 3  :          \
    (b == BIT3) ? 4  :          \
    (b == BIT4) ? 5  :          \
    (b == BIT5) ? 6  :          \
    (b == BIT6) ? 7  :          \
    (b == BIT7) ? 8  :          \
    (b == BIT8) ? 9  :          \
    (b == BIT9) ? 10 :          \
    (b == BITA) ? 11 :          \
    (b == BITB) ? 12 :          \
    (b == BITC) ? 13 :          \
    (b == BITD) ? 14 :          \
    (b == BITE) ? 15 :          \
    (b == BITF) ? 16 :          \
    NO_BIT                      \
  ))

/* This does the opposite of GetBitIndex */
#define GetBitFromIndex(i)  \
  (                         \
    (i == 1)  ? BIT0 :      \
    (i == 2)  ? BIT1 :      \
    (i == 3)  ? BIT2 :      \
    (i == 4)  ? BIT3 :      \
    (i == 5)  ? BIT4 :      \
    (i == 6)  ? BIT5 :      \
    (i == 7)  ? BIT6 :      \
    (i == 8)  ? BIT7 :      \
    (i == 9)  ? BIT8 :      \
    (i == 10) ? BIT9 :      \
    (i == 11) ? BITA :      \
    (i == 12) ? BITB :      \
    (i == 13) ? BITC :      \
    (i == 14) ? BITD :      \
    (i == 15) ? BITE :      \
    (i == 16) ? BITF :      \
    NO_BIT                  \
  )


/**
 * Register Control (POINTERS TO REGISTERS ONLY)
 */
#define SET_REGISTER_PTR(reg, val)            (*(reg) = (val))
#define SET_REGISTER_PTR_BIT_LOW(reg, bit)    (*(reg) &= ~(bit))
#define SET_REGISTER_PTR_BIT_HIGH(reg, bit)   (*(reg) |= (bit))
#define TOGGLE_REGISTER_PTR_BIT(reg, bit)     (*(reg) ^= (bit))







/**
 * These definitions are for doing complex things with the preprocessor
 * They come from: http://jhnet.co.uk/articles/cpp_magic
 */

/* Count the number of arguments on a variadic macro */
#ifndef _NUM_ARGS
#define _NUM_ARGS(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, Pn, ...) Pn
#endif
#ifndef NUM_ARGS
#define NUM_ARGS(...) _NUM_ARGS(-1, ##__VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

#define IF_ELSE(condition)  _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)
#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE
#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define BOOL(x)       NOT(NOT(x))
#define NOT(x)        IS_PROBE(CAT(_NOT_, x))
#define _NOT_0        PROBE()
#define IS_PROBE(...) SECOND(__VA_ARGS__, 0)
#define PROBE()       ~, 1

#define CAT(a,b)    _CAT(a,b)
#define _CAT(a, b)  a ## b


#define FIRST(a, ...)     a
#define SECOND(a, b, ...) b

#define EVAL(...)     EVAL1024(__VA_ARGS__)
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL512(...)  EVAL256(EVAL256(__VA_ARGS__))
#define EVAL256(...)  EVAL128(EVAL128(__VA_ARGS__))
#define EVAL128(...)  EVAL64(EVAL64(__VA_ARGS__))
#define EVAL64(...)   EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...)   EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...)   EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...)    EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...)    EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...)    EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...)    __VA_ARGS__

#define EMPTY()
#define DEFER(m) DEFER1(m)
#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()
#define DEFER3(m) m EMPTY EMPTY EMPTY()()()
#define DEFER4(m) m EMPTY EMPTY EMPTY EMPTY()()()()


/* Paired Map */
#define MAP_PAIR_PARAMETERS(f, p1, ...)             \
  DEFER2(f)p1                                       \
  IF_ELSE(NUM_ARGS(__VA_ARGS__))(                   \
    DEFER2(_MAP_PAIR_PARAMETERS)()(f, __VA_ARGS__)  \
  )()

#define _MAP_PAIR_PARAMETERS()  MAP_PAIR_PARAMETERS

/* Counting Map */
#define MAP_COUNTING(f, i)                        \
  IF_ELSE(i)(                                     \
    DEFER2(_MAP_COUNTING)()(f, DEC(i))            \
    f(i)                                          \
  )()

#define _MAP_COUNTING()   MAP_COUNTING


/* Standard Map */
#define MAP(m, first, ...)            \
  m(first)                            \
  IF_ELSE(NUM_ARGS(__VA_ARGS__))(     \
    DEFER2(_MAP)()(m, __VA_ARGS__)    \
  )()

#define _MAP()  MAP





/* Counting */
#define INC(n)     INC_##n ()
#define INC_0()    1
#define INC_1()    2
#define INC_2()    3
#define INC_3()    4
#define INC_4()    5
#define INC_5()    6
#define INC_6()    7
#define INC_7()    8
#define INC_8()    9
#define INC_9()    10
#define INC_10()   11
#define INC_11()   12
#define INC_12()   13
#define INC_13()   14
#define INC_14()   15
#define INC_15()   16
#define INC_16()   17
#define INC_17()   18
#define INC_18()   19
#define INC_19()   20
#define INC_20()   21
#define INC_21()   22
#define INC_22()   23
#define INC_23()   24
#define INC_24()   25
#define INC_25()   26
#define INC_26()   27
#define INC_27()   28
#define INC_28()   29
#define INC_29()   30
#define INC_30()   31
#define INC_31()   32
#define INC_32()   33
#define INC_33()   34
#define INC_34()   35
#define INC_35()   36
#define INC_36()   37
#define INC_37()   38
#define INC_38()   39
#define INC_39()   40
#define INC_40()   41
#define INC_41()   42
#define INC_42()   43
#define INC_43()   44
#define INC_44()   45
#define INC_45()   46
#define INC_46()   47
#define INC_47()   48
#define INC_48()   49
#define INC_49()   50
#define INC_50()   51
#define INC_51()   52
#define INC_52()   53
#define INC_53()   54
#define INC_54()   55
#define INC_55()   56
#define INC_56()   57
#define INC_57()   58
#define INC_58()   59
#define INC_59()   60
#define INC_60()   61
#define INC_61()   62
#define INC_62()   63
#define INC_63()   64
#define INC_64()   65
#define INC_65()   66
#define INC_66()   67
#define INC_67()   68
#define INC_68()   69
#define INC_69()   70
#define INC_70()   71
#define INC_71()   72
#define INC_72()   73
#define INC_73()   74
#define INC_74()   75
#define INC_75()   76
#define INC_76()   77
#define INC_77()   78
#define INC_78()   79
#define INC_79()   80
#define INC_80()   81
#define INC_81()   82
#define INC_82()   83
#define INC_83()   84
#define INC_84()   85
#define INC_85()   86
#define INC_86()   87
#define INC_87()   88
#define INC_88()   89
#define INC_89()   90
#define INC_90()   91
#define INC_91()   92
#define INC_92()   93
#define INC_93()   94
#define INC_94()   95
#define INC_95()   96
#define INC_96()   97
#define INC_97()   98
#define INC_98()   99
#define INC_99()   100
#define INC_100()    101
#define INC_101()    102
#define INC_102()    103
#define INC_103()    104
#define INC_104()    105
#define INC_105()    106
#define INC_106()    107
#define INC_107()    108
#define INC_108()    109
#define INC_109()    110
#define INC_110()   111
#define INC_111()   112
#define INC_112()   113
#define INC_113()   114
#define INC_114()   115
#define INC_115()   116
#define INC_116()   117
#define INC_117()   118
#define INC_118()   119
#define INC_119()   120
#define INC_120()   121
#define INC_121()   122
#define INC_122()   123
#define INC_123()   124
#define INC_124()   125
#define INC_125()   126
#define INC_126()   127
#define INC_127()   128
#define INC_128()   129
#define INC_129()   130
#define INC_130()   131
#define INC_131()   132
#define INC_132()   133
#define INC_133()   134
#define INC_134()   135
#define INC_135()   136
#define INC_136()   137
#define INC_137()   138
#define INC_138()   139
#define INC_139()   140
#define INC_140()   141
#define INC_141()   142
#define INC_142()   143
#define INC_143()   144
#define INC_144()   145
#define INC_145()   146
#define INC_146()   147
#define INC_147()   148
#define INC_148()   149
#define INC_149()   150
#define INC_150()   151
#define INC_151()   152
#define INC_152()   153
#define INC_153()   154
#define INC_154()   155
#define INC_155()   156
#define INC_156()   157
#define INC_157()   158
#define INC_158()   159
#define INC_159()   160
#define INC_160()   161
#define INC_161()   162
#define INC_162()   163
#define INC_163()   164
#define INC_164()   165
#define INC_165()   166
#define INC_166()   167
#define INC_167()   168
#define INC_168()   169
#define INC_169()   170
#define INC_170()   171
#define INC_171()   172
#define INC_172()   173
#define INC_173()   174
#define INC_174()   175
#define INC_175()   176
#define INC_176()   177
#define INC_177()   178
#define INC_178()   179
#define INC_179()   180
#define INC_180()   181
#define INC_181()   182
#define INC_182()   183
#define INC_183()   184
#define INC_184()   185
#define INC_185()   186
#define INC_186()   187
#define INC_187()   188
#define INC_188()   189
#define INC_189()   190
#define INC_190()   191
#define INC_191()   192
#define INC_192()   193
#define INC_193()   194
#define INC_194()   195
#define INC_195()   196
#define INC_196()   197
#define INC_197()   198
#define INC_198()   199
#define INC_199()   200


#define DEC(n)      DEC_##n ()
#define DEC_200()   199
#define DEC_199()   198
#define DEC_198()   197
#define DEC_197()   196
#define DEC_196()   195
#define DEC_195()   194
#define DEC_194()   193
#define DEC_193()   192
#define DEC_192()   191
#define DEC_191()   190
#define DEC_190()   189
#define DEC_189()   188
#define DEC_188()   187
#define DEC_187()   186
#define DEC_186()   185
#define DEC_185()   184
#define DEC_184()   183
#define DEC_183()   182
#define DEC_182()   181
#define DEC_181()   180
#define DEC_180()   179
#define DEC_179()   178
#define DEC_178()   177
#define DEC_177()   176
#define DEC_176()   175
#define DEC_175()   174
#define DEC_174()   173
#define DEC_173()   172
#define DEC_172()   171
#define DEC_171()   170
#define DEC_170()   169
#define DEC_169()   168
#define DEC_168()   167
#define DEC_167()   166
#define DEC_166()   165
#define DEC_165()   164
#define DEC_164()   163
#define DEC_163()   162
#define DEC_162()   161
#define DEC_161()   160
#define DEC_160()   159
#define DEC_159()   158
#define DEC_158()   157
#define DEC_157()   156
#define DEC_156()   155
#define DEC_155()   154
#define DEC_154()   153
#define DEC_153()   152
#define DEC_152()   151
#define DEC_151()   150
#define DEC_150()   149
#define DEC_149()   148
#define DEC_148()   147
#define DEC_147()   146
#define DEC_146()   145
#define DEC_145()   144
#define DEC_144()   143
#define DEC_143()   142
#define DEC_142()   141
#define DEC_141()   140
#define DEC_140()   139
#define DEC_139()   138
#define DEC_138()   137
#define DEC_137()   136
#define DEC_136()   135
#define DEC_135()   134
#define DEC_134()   133
#define DEC_133()   132
#define DEC_132()   131
#define DEC_131()   130
#define DEC_130()   129
#define DEC_129()   128
#define DEC_128()   127
#define DEC_127()   126
#define DEC_126()   125
#define DEC_125()   124
#define DEC_124()   123
#define DEC_123()   122
#define DEC_122()   121
#define DEC_121()   120
#define DEC_120()   119
#define DEC_119()   118
#define DEC_118()   117
#define DEC_117()   116
#define DEC_116()   115
#define DEC_115()   114
#define DEC_114()   113
#define DEC_113()   112
#define DEC_112()   111
#define DEC_111()   110
#define DEC_110()   109
#define DEC_109()   108
#define DEC_108()   107
#define DEC_107()   106
#define DEC_106()   105
#define DEC_105()   104
#define DEC_104()   103
#define DEC_103()   102
#define DEC_102()   101
#define DEC_101()   100
#define DEC_100()   99
#define DEC_99()   98
#define DEC_98()   97
#define DEC_97()   96
#define DEC_96()   95
#define DEC_95()   94
#define DEC_94()   93
#define DEC_93()   92
#define DEC_92()   91
#define DEC_91()   90
#define DEC_90()   89
#define DEC_89()   88
#define DEC_88()   87
#define DEC_87()   86
#define DEC_86()   85
#define DEC_85()   84
#define DEC_84()   83
#define DEC_83()   82
#define DEC_82()   81
#define DEC_81()   80
#define DEC_80()   79
#define DEC_79()   78
#define DEC_78()   77
#define DEC_77()   76
#define DEC_76()   75
#define DEC_75()   74
#define DEC_74()   73
#define DEC_73()   72
#define DEC_72()   71
#define DEC_71()   70
#define DEC_70()   69
#define DEC_69()   68
#define DEC_68()   67
#define DEC_67()   66
#define DEC_66()   65
#define DEC_65()   64
#define DEC_64()   63
#define DEC_63()   62
#define DEC_62()   61
#define DEC_61()   60
#define DEC_60()   59
#define DEC_59()   58
#define DEC_58()   57
#define DEC_57()   56
#define DEC_56()   55
#define DEC_55()   54
#define DEC_54()   53
#define DEC_53()   52
#define DEC_52()   51
#define DEC_51()   50
#define DEC_50()   49
#define DEC_49()   48
#define DEC_48()   47
#define DEC_47()   46
#define DEC_46()   45
#define DEC_45()   44
#define DEC_44()   43
#define DEC_43()   42
#define DEC_42()   41
#define DEC_41()   40
#define DEC_40()   39
#define DEC_39()   38
#define DEC_38()   37
#define DEC_37()   36
#define DEC_36()   35
#define DEC_35()   34
#define DEC_34()   33
#define DEC_33()   32
#define DEC_32()   31
#define DEC_31()   30
#define DEC_30()   29
#define DEC_29()   28
#define DEC_28()   27
#define DEC_27()   26
#define DEC_26()   25
#define DEC_25()   24
#define DEC_24()   23
#define DEC_23()   22
#define DEC_22()   21
#define DEC_21()   20
#define DEC_20()   19
#define DEC_19()   18
#define DEC_18()   17
#define DEC_17()   16
#define DEC_16()   15
#define DEC_15()   14
#define DEC_14()   13
#define DEC_13()   12
#define DEC_12()   11
#define DEC_11()   10
#define DEC_10()   9
#define DEC_9()   8
#define DEC_8()   7
#define DEC_7()   6
#define DEC_6()   5
#define DEC_5()   4
#define DEC_4()   3
#define DEC_3()   2
#define DEC_2()   1
#define DEC_1()   0

#endif
