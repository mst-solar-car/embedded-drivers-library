/**
 * This file contains directives for a Fixture that makes creating microcontroller
 * drivers easier and simpler to read. A Fixture is just a wrapper.
 *
 * So this file is weird. This fixture allows for the .spec file and the .driver
 * file to do what they do.
 *
 * For the .spec file, you might notice a lot of #ifdef RUN_SPEC_FILE_LIKE_C_FILE
 * directives in here, a lot of similar directives, and a lot of #undef
 * This is because this fixture forces the .spec file to behave differently whether it
 * is #include in a header file or a code file... :)
 * So sorry.
 *
 * Authors: Michael Rouse and people on the internet
 */
#include "interface.h"
#include "../datatypes.h"



/**
 * Ports and Pins
 */

/* Create list of pins */
#undef REGISTER_PINS
#undef _REGISTER_PIN
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_PINS(numberOfPins)   pin_map_t pin_map[numberOfPins+1];

#else
  /* Header File */
  #define REGISTER_PINS(numberOfPins)                       \
    enum {                                                  \
      EVAL256(MAP_COUNTING(_REGISTER_PIN, numberOfPins))    \
      MC_NUMBER_OF_PINS = numberOfPins,                     \
    };

  #define _REGISTER_PIN(n)    PIN_NAME(n) = n,
#endif


/* Create list of ports */
#undef REGISTER_PORTS
#undef _REGISTER_PORT
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_PORTS(...)                             \
    vuint16_t* dir_registers[NUM_ARGS(1, __VA_ARGS__)];   \
    vuint16_t* out_registers[NUM_ARGS(1, __VA_ARGS__)];   \
    vuint16_t*  in_registers[NUM_ARGS(1, __VA_ARGS__)];   \
    vuint16_t* sel_registers[NUM_ARGS(1, __VA_ARGS__)];   \
    vuint16_t* ies_registers[NUM_ARGS(1, __VA_ARGS__)];   \
    vuint16_t*  ie_registers[NUM_ARGS(1, __VA_ARGS__)];   \
    vuint16_t* ifg_registers[NUM_ARGS(1, __VA_ARGS__)];

#else
  /* Header File */
  #define REGISTER_PORTS(...)                         \
    enum {                                            \
      __IGNORE_THIS_##__LINE__ = 0,                   \
      EVAL256(MAP(_REGISTER_PORT, __VA_ARGS__))       \
      MC_NUMBER_OF_PORTS = NUM_ARGS(__VA_ARGS__),     \
    };

  #define _REGISTER_PORT(p)    PORT_NAME(p),
#endif


/* Set port bits to pins in bulk */
#undef REGISTER_PINS_FOR_PORT
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_PINS_FOR_PORT(port, ...)                             \
    void __attribute__((constructor(800))) __PORT##port##_SETUP(void) {      \
      CAT(_SETUP_PIN_MAP_, NUM_ARGS(__VA_ARGS__))(port, __VA_ARGS__)    \
    };

#else
  /* Header File */
  #define REGISTER_PINS_FOR_PORT(port, ...)                                   \
    enum {                                                                    \
      EVAL256(CAT(_PORT_BITS_, NUM_ARGS(__VA_ARGS__))(port, __VA_ARGS__))     \
      MC_NUMBER_OF_BITS_ON_PORT##port = NUM_ARGS(__VA_ARGS__),               \
    };
#endif


/* Register Pin Aliases (other functions, etc..) */
#undef REGISTER_PIN_ALIAS
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_PIN_ALIAS(pin, alias)  /* Nothing */

#else
  /* Header File */
  #define REGISTER_PIN_ALIAS(pin, alias)      \
    enum {                                    \
      alias = pin,                            \
    };
#endif

/* Setup Registers for the Ports */
#undef SET_PORT_REGISTERS
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define SET_PORT_REGISTERS(port, dir, out, in, sel, ies, ie, ifg)           \
    void __attribute__((constructor(300))) __PORT##port##_REGISTER_SETUP(void) {   \
      dir_registers[PORT_NAME(port)] = REG(dir);                              \
      out_registers[PORT_NAME(port)] = REG(out);                              \
      in_registers[PORT_NAME(port)]  = REG(in);                               \
      sel_registers[PORT_NAME(port)] = REG(sel);                              \
      ies_registers[PORT_NAME(port)] = REG(ies);                              \
      ie_registers[PORT_NAME(port)]  = REG(ie);                               \
      ifg_registers[PORT_NAME(port)] = REG(ifg);                              \
    };

#else
  /* Header File */
  #define SET_PORT_REGISTERS(port, dir, out, in, sel, ies, ie, ifg) /* Nothing */
#endif


/**
 * SPI Buses
 */
#undef REGISTER_SPI_BUSES
#undef _REGISTER_SPI_BUS
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_SPI_BUSES(n)  /* Nothing */

#else
  /* Header File */
  #define REGISTER_SPI_BUSES(n)                     \
    enum {                                          \
      EVAL256(MAP_COUNTING(_REGISTER_SPI_BUS, n))   \
      MC_NUMBER_OF_SPI_BUSES = n,                   \
    };

  #define _REGISTER_SPI_BUS(n)    SPI_BUS_##n = n,
#endif


/**
 * Interrupts
 */
#undef REGISTER_INTERRUPTABLE_PORTS
#undef _REGISTER_INTERRUPTABLE_PORT
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #define REGISTER_INTERRUPTABLE_PORTS(...)   EVAL256(MAP_PAIR_PARAMETERS(_REGISTER_INTERRUPTABLE_PORT, __VA_ARGS__))

  #define _REGISTER_INTERRUPTABLE_PORT(p,v)                           \
    void __attribute__((interrupt(v))) __##p##_ISR(void) {            \
      __interrupt_dispatch(p);                           \
    };

#else
  /* Header File */
  #define REGISTER_INTERRUPTABLE_PORTS(...)                         \
    enum {                                                          \
      MC_NUMBER_OF_INTERRUPTABLE_PORTS = NUM_ARGS(__VA_ARGS__),     \
    };
#endif


/**
 * Registers
 */
#undef MAKE_REGISTERS
#undef _MAKE_REGISTER
#undef _MAKE_REGISTERS_INIT
#ifdef RUN_SPEC_FILE_LIKE_C_FILE
  /* C File */
  #ifndef UNIT_TEST
    /* Non Unit Test in C File */
    #define MAKE_REGISTERS(...)  /* Nothing */

  #else
    /* Unit Test in C File (function to malloc space for fake registers) */
    #define MAKE_REGISTERS(...)                                                                                         \
      EVAL256(MAP_PAIR_PARAMETERS(_MAKE_REGISTER, __VA_ARGS__))                                                         \
      void __attribute__((constructor(200))) CAT(CAT(__SETUP_MOCK_REGISTERS_,DEFER1(__COUNTER__)),_REGISTERS)(void) {   \
        EVAL256(MAP_PAIR_PARAMETERS(_MAKE_REGISTER_INIT, __VA_ARGS__))                                                  \
      }

    #define _MAKE_REGISTER(name, addr)        vuint16_t* name;
    #define _MAKE_REGISTER_INIT(name, addr)   name = (vuint16_t*)malloc(sizeof(vuint16_t));

  #endif

#else
  /* Header File */
  #ifndef UNIT_TEST
    /* Non Unit Test in Header File */
    #define MAKE_REGISTERS(...)         enum { EVAL256(MAP_PAIR_PARAMETERS(_MAKE_REGISTER, __VA_ARGS__)) }

    #define _MAKE_REGISTER(name, addr)  name = addr,

  #else
    /* Unit Testing in Header File */
    #define MAKE_REGISTERS(...)         EVAL256(MAP_PAIR_PARAMETERS(_MAKE_REGISTER, __VA_ARGS__))

    #define _MAKE_REGISTER(name, addr)   extern vuint16_t* name;
  #endif
#endif



/**
 * Helper Directives
 * (Nitty and Gritty)
 */
#ifndef __MICROCONTROLLER_FIXTURE__
#define __MICROCONTROLLER_FIXTURE__

#define REG(name)         (vuint16_t*)name

#define PIN(n)            PIN##n
#define PIN_NAME(n)       PIN##n

#define PB(n, b)          P##n##_##b
#define PORTB_NAME(n, b)  P##n##_##b

#define PORT(n)           PORT##n
#define PORT_NAME(n)      PORT##n








/**
 * Aaaaaaye, you made it. That sucks.
 * If you made it this far then something must be broken or you are curious.
 *
 * If something is broken--I'm sorry.
 * If you're curious--I'm still sorry.
 */
#define BTP(n,b,p)                                        PORTB_NAME(n,b) = p,
#define _PORT_BITS_1(n, p1)                               BTP(n,0,p1)
#define _PORT_BITS_2(n, p1, p2)                           _PORT_BITS_1(n, p1) BTP(n,1,p2)
#define _PORT_BITS_3(n, p1, p2, p3)                       _PORT_BITS_2(n, p1, p2) BTP(n,2,p3)
#define _PORT_BITS_4(n, p1, p2, p3, p4)                   _PORT_BITS_3(n,p1,p2,p3) BTP(n,3,p4)
#define _PORT_BITS_5(n,p1,p2,p3,p4,p5)                    _PORT_BITS_4(n,p1,p2,p3,p4) BTP(n,4,p5)
#define _PORT_BITS_6(n,p1,p2,p3,p4,p5,p6)                 _PORT_BITS_5(n,p1,p2,p3,p4,p5) BTP(n,5,p6)
#define _PORT_BITS_7(n,p1,p2,p3,p4,p5,p6,p7)              _PORT_BITS_6(n,p1,p2,p3,p4,p5,p6) BTP(n,6,p7)
#define _PORT_BITS_8(n,p1,p2,p3,p4,p5,p6,p7,p8)           _PORT_BITS_7(n,p1,p2,p3,p4,p5,p6,p7) BTP(n,7,p8)
#define _PORT_BITS_9(n,p1,p2,p3,p4,p5,p6,p7,p8,p9)        _PORT_BITS_8(n,p1,p2,p3,p4,p5,p6,p7,p8) BTP(n,8,p9)


#define _SETUP_PIN_MAP(n,b,p)                             pin_map[p].port = PORT_NAME(n); pin_map[p].bit = BIT##b;
#define _SETUP_PIN_MAP_1(n,p1)                            _SETUP_PIN_MAP(n,0,p1)
#define _SETUP_PIN_MAP_2(n,p1,p2)                         _SETUP_PIN_MAP_1(n,p1) _SETUP_PIN_MAP(n,1,p2)
#define _SETUP_PIN_MAP_3(n,p1,p2,p3)                      _SETUP_PIN_MAP_2(n,p1,p2) _SETUP_PIN_MAP(n,2,p3)
#define _SETUP_PIN_MAP_4(n,p1,p2,p3,p4)                   _SETUP_PIN_MAP_3(n,p1,p2,p3) _SETUP_PIN_MAP(n,3,p4)
#define _SETUP_PIN_MAP_5(n,p1,p2,p3,p4,p5)                _SETUP_PIN_MAP_4(n,p1,p2,p3,p4) _SETUP_PIN_MAP(n,4,p5)
#define _SETUP_PIN_MAP_6(n,p1,p2,p3,p4,p5,p6)             _SETUP_PIN_MAP_5(n,p1,p2,p3,p4,p5) _SETUP_PIN_MAP(n,5,p6)
#define _SETUP_PIN_MAP_7(n,p1,p2,p3,p4,p5,p6,p7)          _SETUP_PIN_MAP_6(n,p1,p2,p3,p4,p5,p6) _SETUP_PIN_MAP(n,6,p7)
#define _SETUP_PIN_MAP_8(n,p1,p2,p3,p4,p5,p6,p7,p8)       _SETUP_PIN_MAP_7(n,p1,p2,p3,p4,p5,p6,p7) _SETUP_PIN_MAP(n,7,p8)
#define _SETUP_PIN_MAP_9(n,p1,p2,p3,p4,p5,p6,p7,p8,p9)    _SETUP_PIN_MAP_8(n,p1,p2,p3,p4,p5,p6,p7,p8) _SETUP_PIN_MAP(n,8,p9)




#ifndef _NUM_ARGS
#define _NUM_ARGS(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, Pn, ...) Pn
#endif

#ifndef NUM_ARGS
#define NUM_ARGS(...) _NUM_ARGS(-1, ##__VA_ARGS__, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif


/* These definitions are for doing complex things with the preprocessor
 * They come from: http://jhnet.co.uk/articles/cpp_magic
 */
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




