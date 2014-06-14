// [AsmJit]
// Complete x86/x64 JIT and Remote Assembler for C++.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// [Export]
#define ASMJIT_EXPORTS

// [Guard]
#include "../build.h"
#if defined(ASMJIT_BUILD_X86) || defined(ASMJIT_BUILD_X64)

// [Dependencies - AsmJit]
#include "../x86/x86inst.h"

// [Api-Begin]
#include "../apibegin.h"

namespace asmjit {

// ============================================================================
// [Macros]
// ============================================================================

#if !defined(ASMJIT_DISABLE_INST_NAMES)
# define INST_NAME_INDEX(_Code_) _Code_##_NameIndex
#else
# define INST_NAME_INDEX(_Code_) 0
#endif

#define G(_Group_) kX86InstGroup##_Group_
#define F(_Flags_) kX86InstFlag##_Flags_
#define O(_Op_) kX86InstOp##_Op_

#define U 0
#define L kX86InstOpCode_L_True

#define O_000000(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_00   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_000F00(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_0F   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_000F01(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_0F01 | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_000F0F(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_0F   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_000F38(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_0F38 | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_000F3A(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_0F3A | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_660000(_OpCode_, _R_) (kX86InstOpCode_PP_66 | kX86InstOpCode_MM_00   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_660F00(_OpCode_, _R_) (kX86InstOpCode_PP_66 | kX86InstOpCode_MM_0F   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_660F38(_OpCode_, _R_) (kX86InstOpCode_PP_66 | kX86InstOpCode_MM_0F38 | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_660F3A(_OpCode_, _R_) (kX86InstOpCode_PP_66 | kX86InstOpCode_MM_0F3A | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_9B0000(_OpCode_, _R_) (kX86InstOpCode_PP_9B | kX86InstOpCode_MM_00   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_F20000(_OpCode_, _R_) (kX86InstOpCode_PP_F2 | kX86InstOpCode_MM_00   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_F20F00(_OpCode_, _R_) (kX86InstOpCode_PP_F2 | kX86InstOpCode_MM_0F   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_F20F38(_OpCode_, _R_) (kX86InstOpCode_PP_F2 | kX86InstOpCode_MM_0F38 | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_F20F3A(_OpCode_, _R_) (kX86InstOpCode_PP_F2 | kX86InstOpCode_MM_0F3A | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_F30000(_OpCode_, _R_) (kX86InstOpCode_PP_F3 | kX86InstOpCode_MM_00   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_F30F00(_OpCode_, _R_) (kX86InstOpCode_PP_F3 | kX86InstOpCode_MM_0F   | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_F30F38(_OpCode_, _R_) (kX86InstOpCode_PP_F3 | kX86InstOpCode_MM_0F38 | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_F30F3A(_OpCode_, _R_) (kX86InstOpCode_PP_F3 | kX86InstOpCode_MM_0F3A | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))

#define O_00_M03(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_00011| (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_00_M08(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_01000| (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_00_M09(_OpCode_, _R_) (kX86InstOpCode_PP_00 | kX86InstOpCode_MM_01001| (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))

#define O_66_M03(_OpCode_, _R_) (kX86InstOpCode_PP_66 | kX86InstOpCode_MM_00011| (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_66_M08(_OpCode_, _R_) (kX86InstOpCode_PP_66 | kX86InstOpCode_MM_01000| (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_66_M09(_OpCode_, _R_) (kX86InstOpCode_PP_66 | kX86InstOpCode_MM_01001| (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))

#define O_00_X(_OpCode_, _R_) (kX86InstOpCode_PP_00 | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))
#define O_9B_X(_OpCode_, _R_) (kX86InstOpCode_PP_9B | (0x##_OpCode_) | ((_R_) << kX86InstOpCode_O_Shift))

#define INST(_Code_, _Name_, _Group_, _Flags_, _MoveSize_, _OpFlags0_, _OpFlags1_, _OpFlags2_, _OpFlags3_, _OpCode0_, _OpCode1_) \
  { INST_NAME_INDEX(_Code_), _Code_##_ExtendedIndex, _OpCode0_ }

// ============================================================================
// [asmjit::X86Inst]
// ============================================================================

// ${X86InstData:Begin}
// Automatically generated, do not edit.
#if !defined(ASMJIT_DISABLE_INST_NAMES)
const char _x86InstName[] =
  "\0"
  "adc\0"
  "add\0"
  "addpd\0"
  "addps\0"
  "addsd\0"
  "addss\0"
  "addsubpd\0"
  "addsubps\0"
  "aesdec\0"
  "aesdeclast\0"
  "aesenc\0"
  "aesenclast\0"
  "aesimc\0"
  "aeskeygenassist\0"
  "and\0"
  "andn\0"
  "andnpd\0"
  "andnps\0"
  "andpd\0"
  "andps\0"
  "bextr\0"
  "blendpd\0"
  "blendps\0"
  "blendvpd\0"
  "blendvps\0"
  "blsi\0"
  "blsmsk\0"
  "blsr\0"
  "bsf\0"
  "bsr\0"
  "bswap\0"
  "bt\0"
  "btc\0"
  "btr\0"
  "bts\0"
  "bzhi\0"
  "call\0"
  "cbw\0"
  "cdq\0"
  "cdqe\0"
  "clc\0"
  "cld\0"
  "clflush\0"
  "cmc\0"
  "cmova\0"
  "cmovae\0"
  "cmovb\0"
  "cmovbe\0"
  "cmovc\0"
  "cmove\0"
  "cmovg\0"
  "cmovge\0"
  "cmovl\0"
  "cmovle\0"
  "cmovna\0"
  "cmovnae\0"
  "cmovnb\0"
  "cmovnbe\0"
  "cmovnc\0"
  "cmovne\0"
  "cmovng\0"
  "cmovnge\0"
  "cmovnl\0"
  "cmovnle\0"
  "cmovno\0"
  "cmovnp\0"
  "cmovns\0"
  "cmovnz\0"
  "cmovo\0"
  "cmovp\0"
  "cmovpe\0"
  "cmovpo\0"
  "cmovs\0"
  "cmovz\0"
  "cmp\0"
  "cmppd\0"
  "cmpps\0"
  "cmpsb\0"
  "cmpsd\0"
  "cmpsq\0"
  "cmpss\0"
  "cmpsw\0"
  "cmpxchg\0"
  "cmpxchg16b\0"
  "cmpxchg8b\0"
  "comisd\0"
  "comiss\0"
  "cpuid\0"
  "cqo\0"
  "crc32\0"
  "cvtdq2pd\0"
  "cvtdq2ps\0"
  "cvtpd2dq\0"
  "cvtpd2pi\0"
  "cvtpd2ps\0"
  "cvtpi2pd\0"
  "cvtpi2ps\0"
  "cvtps2dq\0"
  "cvtps2pd\0"
  "cvtps2pi\0"
  "cvtsd2si\0"
  "cvtsd2ss\0"
  "cvtsi2sd\0"
  "cvtsi2ss\0"
  "cvtss2sd\0"
  "cvtss2si\0"
  "cvttpd2dq\0"
  "cvttpd2pi\0"
  "cvttps2dq\0"
  "cvttps2pi\0"
  "cvttsd2si\0"
  "cvttss2si\0"
  "cwd\0"
  "cwde\0"
  "daa\0"
  "das\0"
  "dec\0"
  "div\0"
  "divpd\0"
  "divps\0"
  "divsd\0"
  "divss\0"
  "dppd\0"
  "dpps\0"
  "emms\0"
  "enter\0"
  "extractps\0"
  "f2xm1\0"
  "fabs\0"
  "fadd\0"
  "faddp\0"
  "fbld\0"
  "fbstp\0"
  "fchs\0"
  "fclex\0"
  "fcmovb\0"
  "fcmovbe\0"
  "fcmove\0"
  "fcmovnb\0"
  "fcmovnbe\0"
  "fcmovne\0"
  "fcmovnu\0"
  "fcmovu\0"
  "fcom\0"
  "fcomi\0"
  "fcomip\0"
  "fcomp\0"
  "fcompp\0"
  "fcos\0"
  "fdecstp\0"
  "fdiv\0"
  "fdivp\0"
  "fdivr\0"
  "fdivrp\0"
  "femms\0"
  "ffree\0"
  "fiadd\0"
  "ficom\0"
  "ficomp\0"
  "fidiv\0"
  "fidivr\0"
  "fild\0"
  "fimul\0"
  "fincstp\0"
  "finit\0"
  "fist\0"
  "fistp\0"
  "fisttp\0"
  "fisub\0"
  "fisubr\0"
  "fld\0"
  "fld1\0"
  "fldcw\0"
  "fldenv\0"
  "fldl2e\0"
  "fldl2t\0"
  "fldlg2\0"
  "fldln2\0"
  "fldpi\0"
  "fldz\0"
  "fmul\0"
  "fmulp\0"
  "fnclex\0"
  "fninit\0"
  "fnop\0"
  "fnsave\0"
  "fnstcw\0"
  "fnstenv\0"
  "fnstsw\0"
  "fpatan\0"
  "fprem\0"
  "fprem1\0"
  "fptan\0"
  "frndint\0"
  "frstor\0"
  "fsave\0"
  "fscale\0"
  "fsin\0"
  "fsincos\0"
  "fsqrt\0"
  "fst\0"
  "fstcw\0"
  "fstenv\0"
  "fstp\0"
  "fstsw\0"
  "fsub\0"
  "fsubp\0"
  "fsubr\0"
  "fsubrp\0"
  "ftst\0"
  "fucom\0"
  "fucomi\0"
  "fucomip\0"
  "fucomp\0"
  "fucompp\0"
  "fwait\0"
  "fxam\0"
  "fxch\0"
  "fxrstor\0"
  "fxsave\0"
  "fxtract\0"
  "fyl2x\0"
  "fyl2xp1\0"
  "haddpd\0"
  "haddps\0"
  "hsubpd\0"
  "hsubps\0"
  "idiv\0"
  "imul\0"
  "inc\0"
  "insertps\0"
  "int\0"
  "ja\0"
  "jae\0"
  "jb\0"
  "jbe\0"
  "jc\0"
  "je\0"
  "jg\0"
  "jge\0"
  "jl\0"
  "jle\0"
  "jna\0"
  "jnae\0"
  "jnb\0"
  "jnbe\0"
  "jnc\0"
  "jne\0"
  "jng\0"
  "jnge\0"
  "jnl\0"
  "jnle\0"
  "jno\0"
  "jnp\0"
  "jns\0"
  "jnz\0"
  "jo\0"
  "jp\0"
  "jpe\0"
  "jpo\0"
  "js\0"
  "jz\0"
  "jecxz\0"
  "jmp\0"
  "lahf\0"
  "lddqu\0"
  "ldmxcsr\0"
  "lea\0"
  "leave\0"
  "lfence\0"
  "lodsb\0"
  "lodsd\0"
  "lodsq\0"
  "lodsw\0"
  "lzcnt\0"
  "maskmovdqu\0"
  "maskmovq\0"
  "maxpd\0"
  "maxps\0"
  "maxsd\0"
  "maxss\0"
  "mfence\0"
  "minpd\0"
  "minps\0"
  "minsd\0"
  "minss\0"
  "monitor\0"
  "mov\0"
  "mov_ptr\0"
  "movapd\0"
  "movaps\0"
  "movbe\0"
  "movd\0"
  "movddup\0"
  "movdq2q\0"
  "movdqa\0"
  "movdqu\0"
  "movhlps\0"
  "movhpd\0"
  "movhps\0"
  "movlhps\0"
  "movlpd\0"
  "movlps\0"
  "movmskpd\0"
  "movmskps\0"
  "movntdq\0"
  "movntdqa\0"
  "movnti\0"
  "movntpd\0"
  "movntps\0"
  "movntq\0"
  "movq\0"
  "movq2dq\0"
  "movsb\0"
  "movsd\0"
  "movshdup\0"
  "movsldup\0"
  "movsq\0"
  "movss\0"
  "movsw\0"
  "movsx\0"
  "movsxd\0"
  "movupd\0"
  "movups\0"
  "movzx\0"
  "mpsadbw\0"
  "mul\0"
  "mulpd\0"
  "mulps\0"
  "mulsd\0"
  "mulss\0"
  "mulx\0"
  "mwait\0"
  "neg\0"
  "nop\0"
  "not\0"
  "or\0"
  "orpd\0"
  "orps\0"
  "pabsb\0"
  "pabsd\0"
  "pabsw\0"
  "packssdw\0"
  "packsswb\0"
  "packusdw\0"
  "packuswb\0"
  "paddb\0"
  "paddd\0"
  "paddq\0"
  "paddsb\0"
  "paddsw\0"
  "paddusb\0"
  "paddusw\0"
  "paddw\0"
  "palignr\0"
  "pand\0"
  "pandn\0"
  "pause\0"
  "pavgb\0"
  "pavgw\0"
  "pblendvb\0"
  "pblendw\0"
  "pclmulqdq\0"
  "pcmpeqb\0"
  "pcmpeqd\0"
  "pcmpeqq\0"
  "pcmpeqw\0"
  "pcmpestri\0"
  "pcmpestrm\0"
  "pcmpgtb\0"
  "pcmpgtd\0"
  "pcmpgtq\0"
  "pcmpgtw\0"
  "pcmpistri\0"
  "pcmpistrm\0"
  "pdep\0"
  "pext\0"
  "pextrb\0"
  "pextrd\0"
  "pextrq\0"
  "pextrw\0"
  "pf2id\0"
  "pf2iw\0"
  "pfacc\0"
  "pfadd\0"
  "pfcmpeq\0"
  "pfcmpge\0"
  "pfcmpgt\0"
  "pfmax\0"
  "pfmin\0"
  "pfmul\0"
  "pfnacc\0"
  "pfpnacc\0"
  "pfrcp\0"
  "pfrcpit1\0"
  "pfrcpit2\0"
  "pfrsqit1\0"
  "pfrsqrt\0"
  "pfsub\0"
  "pfsubr\0"
  "phaddd\0"
  "phaddsw\0"
  "phaddw\0"
  "phminposuw\0"
  "phsubd\0"
  "phsubsw\0"
  "phsubw\0"
  "pi2fd\0"
  "pi2fw\0"
  "pinsrb\0"
  "pinsrd\0"
  "pinsrq\0"
  "pinsrw\0"
  "pmaddubsw\0"
  "pmaddwd\0"
  "pmaxsb\0"
  "pmaxsd\0"
  "pmaxsw\0"
  "pmaxub\0"
  "pmaxud\0"
  "pmaxuw\0"
  "pminsb\0"
  "pminsd\0"
  "pminsw\0"
  "pminub\0"
  "pminud\0"
  "pminuw\0"
  "pmovmskb\0"
  "pmovsxbd\0"
  "pmovsxbq\0"
  "pmovsxbw\0"
  "pmovsxdq\0"
  "pmovsxwd\0"
  "pmovsxwq\0"
  "pmovzxbd\0"
  "pmovzxbq\0"
  "pmovzxbw\0"
  "pmovzxdq\0"
  "pmovzxwd\0"
  "pmovzxwq\0"
  "pmuldq\0"
  "pmulhrsw\0"
  "pmulhuw\0"
  "pmulhw\0"
  "pmulld\0"
  "pmullw\0"
  "pmuludq\0"
  "pop\0"
  "popa\0"
  "popcnt\0"
  "popf\0"
  "por\0"
  "prefetch\0"
  "prefetch_3dnow\0"
  "prefetchw_3dnow\0"
  "psadbw\0"
  "pshufb\0"
  "pshufd\0"
  "pshufhw\0"
  "pshuflw\0"
  "pshufw\0"
  "psignb\0"
  "psignd\0"
  "psignw\0"
  "pslld\0"
  "pslldq\0"
  "psllq\0"
  "psllw\0"
  "psrad\0"
  "psraw\0"
  "psrld\0"
  "psrldq\0"
  "psrlq\0"
  "psrlw\0"
  "psubb\0"
  "psubd\0"
  "psubq\0"
  "psubsb\0"
  "psubsw\0"
  "psubusb\0"
  "psubusw\0"
  "psubw\0"
  "pswapd\0"
  "ptest\0"
  "punpckhbw\0"
  "punpckhdq\0"
  "punpckhqdq\0"
  "punpckhwd\0"
  "punpcklbw\0"
  "punpckldq\0"
  "punpcklqdq\0"
  "punpcklwd\0"
  "push\0"
  "pusha\0"
  "pushf\0"
  "pxor\0"
  "rcl\0"
  "rcpps\0"
  "rcpss\0"
  "rcr\0"
  "rdfsbase\0"
  "rdgsbase\0"
  "rdrand\0"
  "rdtsc\0"
  "rdtscp\0"
  "rep lodsb\0"
  "rep lodsd\0"
  "rep lodsq\0"
  "rep lodsw\0"
  "rep movsb\0"
  "rep movsd\0"
  "rep movsq\0"
  "rep movsw\0"
  "rep stosb\0"
  "rep stosd\0"
  "rep stosq\0"
  "rep stosw\0"
  "repe cmpsb\0"
  "repe cmpsd\0"
  "repe cmpsq\0"
  "repe cmpsw\0"
  "repe scasb\0"
  "repe scasd\0"
  "repe scasq\0"
  "repe scasw\0"
  "repne cmpsb\0"
  "repne cmpsd\0"
  "repne cmpsq\0"
  "repne cmpsw\0"
  "repne scasb\0"
  "repne scasd\0"
  "repne scasq\0"
  "repne scasw\0"
  "ret\0"
  "rol\0"
  "ror\0"
  "rorx\0"
  "roundpd\0"
  "roundps\0"
  "roundsd\0"
  "roundss\0"
  "rsqrtps\0"
  "rsqrtss\0"
  "sahf\0"
  "sal\0"
  "sar\0"
  "sarx\0"
  "sbb\0"
  "scasb\0"
  "scasd\0"
  "scasq\0"
  "scasw\0"
  "seta\0"
  "setae\0"
  "setb\0"
  "setbe\0"
  "setc\0"
  "sete\0"
  "setg\0"
  "setge\0"
  "setl\0"
  "setle\0"
  "setna\0"
  "setnae\0"
  "setnb\0"
  "setnbe\0"
  "setnc\0"
  "setne\0"
  "setng\0"
  "setnge\0"
  "setnl\0"
  "setnle\0"
  "setno\0"
  "setnp\0"
  "setns\0"
  "setnz\0"
  "seto\0"
  "setp\0"
  "setpe\0"
  "setpo\0"
  "sets\0"
  "setz\0"
  "sfence\0"
  "shl\0"
  "shld\0"
  "shlx\0"
  "shr\0"
  "shrd\0"
  "shrx\0"
  "shufpd\0"
  "shufps\0"
  "sqrtpd\0"
  "sqrtps\0"
  "sqrtsd\0"
  "sqrtss\0"
  "stc\0"
  "std\0"
  "stmxcsr\0"
  "stosb\0"
  "stosd\0"
  "stosq\0"
  "stosw\0"
  "sub\0"
  "subpd\0"
  "subps\0"
  "subsd\0"
  "subss\0"
  "test\0"
  "tzcnt\0"
  "ucomisd\0"
  "ucomiss\0"
  "ud2\0"
  "unpckhpd\0"
  "unpckhps\0"
  "unpcklpd\0"
  "unpcklps\0"
  "vaddpd\0"
  "vaddps\0"
  "vaddsd\0"
  "vaddss\0"
  "vaddsubpd\0"
  "vaddsubps\0"
  "vaesdec\0"
  "vaesdeclast\0"
  "vaesenc\0"
  "vaesenclast\0"
  "vaesimc\0"
  "vaeskeygenassist\0"
  "vandnpd\0"
  "vandnps\0"
  "vandpd\0"
  "vandps\0"
  "vblendpd\0"
  "vblendps\0"
  "vblendvpd\0"
  "vblendvps\0"
  "vbroadcastf128\0"
  "vbroadcasti128\0"
  "vbroadcastsd\0"
  "vbroadcastss\0"
  "vcmppd\0"
  "vcmpps\0"
  "vcmpsd\0"
  "vcmpss\0"
  "vcomisd\0"
  "vcomiss\0"
  "vcvtdq2pd\0"
  "vcvtdq2ps\0"
  "vcvtpd2dq\0"
  "vcvtpd2ps\0"
  "vcvtph2ps\0"
  "vcvtps2dq\0"
  "vcvtps2pd\0"
  "vcvtps2ph\0"
  "vcvtsd2si\0"
  "vcvtsd2ss\0"
  "vcvtsi2sd\0"
  "vcvtsi2ss\0"
  "vcvtss2sd\0"
  "vcvtss2si\0"
  "vcvttpd2dq\0"
  "vcvttps2dq\0"
  "vcvttsd2si\0"
  "vcvttss2si\0"
  "vdivpd\0"
  "vdivps\0"
  "vdivsd\0"
  "vdivss\0"
  "vdppd\0"
  "vdpps\0"
  "vextractf128\0"
  "vextracti128\0"
  "vextractps\0"
  "vfmadd132pd\0"
  "vfmadd132ps\0"
  "vfmadd132sd\0"
  "vfmadd132ss\0"
  "vfmadd213pd\0"
  "vfmadd213ps\0"
  "vfmadd213sd\0"
  "vfmadd213ss\0"
  "vfmadd231pd\0"
  "vfmadd231ps\0"
  "vfmadd231sd\0"
  "vfmadd231ss\0"
  "vfmaddpd\0"
  "vfmaddps\0"
  "vfmaddsd\0"
  "vfmaddss\0"
  "vfmaddsub132pd\0"
  "vfmaddsub132ps\0"
  "vfmaddsub213pd\0"
  "vfmaddsub213ps\0"
  "vfmaddsub231pd\0"
  "vfmaddsub231ps\0"
  "vfmaddsubpd\0"
  "vfmaddsubps\0"
  "vfmsub132pd\0"
  "vfmsub132ps\0"
  "vfmsub132sd\0"
  "vfmsub132ss\0"
  "vfmsub213pd\0"
  "vfmsub213ps\0"
  "vfmsub213sd\0"
  "vfmsub213ss\0"
  "vfmsub231pd\0"
  "vfmsub231ps\0"
  "vfmsub231sd\0"
  "vfmsub231ss\0"
  "vfmsubadd132pd\0"
  "vfmsubadd132ps\0"
  "vfmsubadd213pd\0"
  "vfmsubadd213ps\0"
  "vfmsubadd231pd\0"
  "vfmsubadd231ps\0"
  "vfmsubaddpd\0"
  "vfmsubaddps\0"
  "vfmsubpd\0"
  "vfmsubps\0"
  "vfmsubsd\0"
  "vfmsubss\0"
  "vfnmadd132pd\0"
  "vfnmadd132ps\0"
  "vfnmadd132sd\0"
  "vfnmadd132ss\0"
  "vfnmadd213pd\0"
  "vfnmadd213ps\0"
  "vfnmadd213sd\0"
  "vfnmadd213ss\0"
  "vfnmadd231pd\0"
  "vfnmadd231ps\0"
  "vfnmadd231sd\0"
  "vfnmadd231ss\0"
  "vfnmaddpd\0"
  "vfnmaddps\0"
  "vfnmaddsd\0"
  "vfnmaddss\0"
  "vfnmsub132pd\0"
  "vfnmsub132ps\0"
  "vfnmsub132sd\0"
  "vfnmsub132ss\0"
  "vfnmsub213pd\0"
  "vfnmsub213ps\0"
  "vfnmsub213sd\0"
  "vfnmsub213ss\0"
  "vfnmsub231pd\0"
  "vfnmsub231ps\0"
  "vfnmsub231sd\0"
  "vfnmsub231ss\0"
  "vfnmsubpd\0"
  "vfnmsubps\0"
  "vfnmsubsd\0"
  "vfnmsubss\0"
  "vfrczpd\0"
  "vfrczps\0"
  "vfrczsd\0"
  "vfrczss\0"
  "vgatherdpd\0"
  "vgatherdps\0"
  "vgatherqpd\0"
  "vgatherqps\0"
  "vhaddpd\0"
  "vhaddps\0"
  "vhsubpd\0"
  "vhsubps\0"
  "vinsertf128\0"
  "vinserti128\0"
  "vinsertps\0"
  "vlddqu\0"
  "vldmxcsr\0"
  "vmaskmovdqu\0"
  "vmaskmovpd\0"
  "vmaskmovps\0"
  "vmaxpd\0"
  "vmaxps\0"
  "vmaxsd\0"
  "vmaxss\0"
  "vminpd\0"
  "vminps\0"
  "vminsd\0"
  "vminss\0"
  "vmovapd\0"
  "vmovaps\0"
  "vmovd\0"
  "vmovddup\0"
  "vmovdqa\0"
  "vmovdqu\0"
  "vmovhlps\0"
  "vmovhpd\0"
  "vmovhps\0"
  "vmovlhps\0"
  "vmovlpd\0"
  "vmovlps\0"
  "vmovmskpd\0"
  "vmovmskps\0"
  "vmovntdq\0"
  "vmovntdqa\0"
  "vmovntpd\0"
  "vmovntps\0"
  "vmovq\0"
  "vmovsd\0"
  "vmovshdup\0"
  "vmovsldup\0"
  "vmovss\0"
  "vmovupd\0"
  "vmovups\0"
  "vmpsadbw\0"
  "vmulpd\0"
  "vmulps\0"
  "vmulsd\0"
  "vmulss\0"
  "vorpd\0"
  "vorps\0"
  "vpabsb\0"
  "vpabsd\0"
  "vpabsw\0"
  "vpackssdw\0"
  "vpacksswb\0"
  "vpackusdw\0"
  "vpackuswb\0"
  "vpaddb\0"
  "vpaddd\0"
  "vpaddq\0"
  "vpaddsb\0"
  "vpaddsw\0"
  "vpaddusb\0"
  "vpaddusw\0"
  "vpaddw\0"
  "vpalignr\0"
  "vpand\0"
  "vpandn\0"
  "vpavgb\0"
  "vpavgw\0"
  "vpblendd\0"
  "vpblendvb\0"
  "vpblendw\0"
  "vpbroadcastb\0"
  "vpbroadcastd\0"
  "vpbroadcastq\0"
  "vpbroadcastw\0"
  "vpclmulqdq\0"
  "vpcmov\0"
  "vpcmpeqb\0"
  "vpcmpeqd\0"
  "vpcmpeqq\0"
  "vpcmpeqw\0"
  "vpcmpestri\0"
  "vpcmpestrm\0"
  "vpcmpgtb\0"
  "vpcmpgtd\0"
  "vpcmpgtq\0"
  "vpcmpgtw\0"
  "vpcmpistri\0"
  "vpcmpistrm\0"
  "vpcomb\0"
  "vpcomd\0"
  "vpcomq\0"
  "vpcomub\0"
  "vpcomud\0"
  "vpcomuq\0"
  "vpcomuw\0"
  "vpcomw\0"
  "vperm2f128\0"
  "vperm2i128\0"
  "vpermd\0"
  "vpermil2pd\0"
  "vpermil2ps\0"
  "vpermilpd\0"
  "vpermilps\0"
  "vpermpd\0"
  "vpermps\0"
  "vpermq\0"
  "vpextrb\0"
  "vpextrd\0"
  "vpextrq\0"
  "vpextrw\0"
  "vpgatherdd\0"
  "vpgatherdq\0"
  "vpgatherqd\0"
  "vpgatherqq\0"
  "vphaddbd\0"
  "vphaddbq\0"
  "vphaddbw\0"
  "vphaddd\0"
  "vphadddq\0"
  "vphaddsw\0"
  "vphaddubd\0"
  "vphaddubq\0"
  "vphaddubw\0"
  "vphaddudq\0"
  "vphadduwd\0"
  "vphadduwq\0"
  "vphaddw\0"
  "vphaddwd\0"
  "vphaddwq\0"
  "vphminposuw\0"
  "vphsubbw\0"
  "vphsubd\0"
  "vphsubdq\0"
  "vphsubsw\0"
  "vphsubw\0"
  "vphsubwd\0"
  "vpinsrb\0"
  "vpinsrd\0"
  "vpinsrq\0"
  "vpinsrw\0"
  "vpmacsdd\0"
  "vpmacsdqh\0"
  "vpmacsdql\0"
  "vpmacssdd\0"
  "vpmacssdqh\0"
  "vpmacssdql\0"
  "vpmacsswd\0"
  "vpmacssww\0"
  "vpmacswd\0"
  "vpmacsww\0"
  "vpmadcsswd\0"
  "vpmadcswd\0"
  "vpmaddubsw\0"
  "vpmaddwd\0"
  "vpmaskmovd\0"
  "vpmaskmovq\0"
  "vpmaxsb\0"
  "vpmaxsd\0"
  "vpmaxsw\0"
  "vpmaxub\0"
  "vpmaxud\0"
  "vpmaxuw\0"
  "vpminsb\0"
  "vpminsd\0"
  "vpminsw\0"
  "vpminub\0"
  "vpminud\0"
  "vpminuw\0"
  "vpmovmskb\0"
  "vpmovsxbd\0"
  "vpmovsxbq\0"
  "vpmovsxbw\0"
  "vpmovsxdq\0"
  "vpmovsxwd\0"
  "vpmovsxwq\0"
  "vpmovzxbd\0"
  "vpmovzxbq\0"
  "vpmovzxbw\0"
  "vpmovzxdq\0"
  "vpmovzxwd\0"
  "vpmovzxwq\0"
  "vpmuldq\0"
  "vpmulhrsw\0"
  "vpmulhuw\0"
  "vpmulhw\0"
  "vpmulld\0"
  "vpmullw\0"
  "vpmuludq\0"
  "vpor\0"
  "vpperm\0"
  "vprotb\0"
  "vprotd\0"
  "vprotq\0"
  "vprotw\0"
  "vpsadbw\0"
  "vpshab\0"
  "vpshad\0"
  "vpshaq\0"
  "vpshaw\0"
  "vpshlb\0"
  "vpshld\0"
  "vpshlq\0"
  "vpshlw\0"
  "vpshufb\0"
  "vpshufd\0"
  "vpshufhw\0"
  "vpshuflw\0"
  "vpsignb\0"
  "vpsignd\0"
  "vpsignw\0"
  "vpslld\0"
  "vpslldq\0"
  "vpsllq\0"
  "vpsllvd\0"
  "vpsllvq\0"
  "vpsllw\0"
  "vpsrad\0"
  "vpsravd\0"
  "vpsraw\0"
  "vpsrld\0"
  "vpsrldq\0"
  "vpsrlq\0"
  "vpsrlvd\0"
  "vpsrlvq\0"
  "vpsrlw\0"
  "vpsubb\0"
  "vpsubd\0"
  "vpsubq\0"
  "vpsubsb\0"
  "vpsubsw\0"
  "vpsubusb\0"
  "vpsubusw\0"
  "vpsubw\0"
  "vptest\0"
  "vpunpckhbw\0"
  "vpunpckhdq\0"
  "vpunpckhqdq\0"
  "vpunpckhwd\0"
  "vpunpcklbw\0"
  "vpunpckldq\0"
  "vpunpcklqdq\0"
  "vpunpcklwd\0"
  "vpxor\0"
  "vrcpps\0"
  "vrcpss\0"
  "vroundpd\0"
  "vroundps\0"
  "vroundsd\0"
  "vroundss\0"
  "vrsqrtps\0"
  "vrsqrtss\0"
  "vshufpd\0"
  "vshufps\0"
  "vsqrtpd\0"
  "vsqrtps\0"
  "vsqrtsd\0"
  "vsqrtss\0"
  "vstmxcsr\0"
  "vsubpd\0"
  "vsubps\0"
  "vsubsd\0"
  "vsubss\0"
  "vtestpd\0"
  "vtestps\0"
  "vucomisd\0"
  "vucomiss\0"
  "vunpckhpd\0"
  "vunpckhps\0"
  "vunpcklpd\0"
  "vunpcklps\0"
  "vxorpd\0"
  "vxorps\0"
  "vzeroall\0"
  "vzeroupper\0"
  "wrfsbase\0"
  "wrgsbase\0"
  "xadd\0"
  "xchg\0"
  "xor\0"
  "xorpd\0"
  "xorps\0";

// Automatically generated, do not edit.
enum kX86InstAlphaIndex {
  kX86InstAlphaIndexFirst = 'a',
  kX86InstAlphaIndexLast = 'z',
  kX86InstAlphaIndexInvalid = 0xFFFF
};

// Automatically generated, do not edit.
static const uint16_t _x86InstAlphaIndex[26] = {
  kX86InstIdAdc,
  kX86InstIdBextr,
  kX86InstIdCall,
  kX86InstIdDaa,
  kX86InstIdEmms,
  kX86InstIdF2xm1,
  0xFFFF,
  kX86InstIdHaddpd,
  kX86InstIdIdiv,
  kX86InstIdJa,
  0xFFFF,
  kX86InstIdLahf,
  kX86InstIdMaskmovdqu,
  kX86InstIdNeg,
  kX86InstIdOr,
  kX86InstIdPabsb,
  0xFFFF,
  kX86InstIdRcl,
  kX86InstIdSahf,
  kX86InstIdTest,
  kX86InstIdUcomisd,
  kX86InstIdVaddpd,
  kX86InstIdWrfsbase,
  kX86InstIdXadd,
  0xFFFF,
  0xFFFF
};

// Automatically generated, do not edit.
enum kX86InstData_NameIndex {
  kInstIdNone_NameIndex = 0,
  kX86InstIdAdc_NameIndex = 1,
  kX86InstIdAdd_NameIndex = 5,
  kX86InstIdAddpd_NameIndex = 9,
  kX86InstIdAddps_NameIndex = 15,
  kX86InstIdAddsd_NameIndex = 21,
  kX86InstIdAddss_NameIndex = 27,
  kX86InstIdAddsubpd_NameIndex = 33,
  kX86InstIdAddsubps_NameIndex = 42,
  kX86InstIdAesdec_NameIndex = 51,
  kX86InstIdAesdeclast_NameIndex = 58,
  kX86InstIdAesenc_NameIndex = 69,
  kX86InstIdAesenclast_NameIndex = 76,
  kX86InstIdAesimc_NameIndex = 87,
  kX86InstIdAeskeygenassist_NameIndex = 94,
  kX86InstIdAnd_NameIndex = 110,
  kX86InstIdAndn_NameIndex = 114,
  kX86InstIdAndnpd_NameIndex = 119,
  kX86InstIdAndnps_NameIndex = 126,
  kX86InstIdAndpd_NameIndex = 133,
  kX86InstIdAndps_NameIndex = 139,
  kX86InstIdBextr_NameIndex = 145,
  kX86InstIdBlendpd_NameIndex = 151,
  kX86InstIdBlendps_NameIndex = 159,
  kX86InstIdBlendvpd_NameIndex = 167,
  kX86InstIdBlendvps_NameIndex = 176,
  kX86InstIdBlsi_NameIndex = 185,
  kX86InstIdBlsmsk_NameIndex = 190,
  kX86InstIdBlsr_NameIndex = 197,
  kX86InstIdBsf_NameIndex = 202,
  kX86InstIdBsr_NameIndex = 206,
  kX86InstIdBswap_NameIndex = 210,
  kX86InstIdBt_NameIndex = 216,
  kX86InstIdBtc_NameIndex = 219,
  kX86InstIdBtr_NameIndex = 223,
  kX86InstIdBts_NameIndex = 227,
  kX86InstIdBzhi_NameIndex = 231,
  kX86InstIdCall_NameIndex = 236,
  kX86InstIdCbw_NameIndex = 241,
  kX86InstIdCdq_NameIndex = 245,
  kX86InstIdCdqe_NameIndex = 249,
  kX86InstIdClc_NameIndex = 254,
  kX86InstIdCld_NameIndex = 258,
  kX86InstIdClflush_NameIndex = 262,
  kX86InstIdCmc_NameIndex = 270,
  kX86InstIdCmova_NameIndex = 274,
  kX86InstIdCmovae_NameIndex = 280,
  kX86InstIdCmovb_NameIndex = 287,
  kX86InstIdCmovbe_NameIndex = 293,
  kX86InstIdCmovc_NameIndex = 300,
  kX86InstIdCmove_NameIndex = 306,
  kX86InstIdCmovg_NameIndex = 312,
  kX86InstIdCmovge_NameIndex = 318,
  kX86InstIdCmovl_NameIndex = 325,
  kX86InstIdCmovle_NameIndex = 331,
  kX86InstIdCmovna_NameIndex = 338,
  kX86InstIdCmovnae_NameIndex = 345,
  kX86InstIdCmovnb_NameIndex = 353,
  kX86InstIdCmovnbe_NameIndex = 360,
  kX86InstIdCmovnc_NameIndex = 368,
  kX86InstIdCmovne_NameIndex = 375,
  kX86InstIdCmovng_NameIndex = 382,
  kX86InstIdCmovnge_NameIndex = 389,
  kX86InstIdCmovnl_NameIndex = 397,
  kX86InstIdCmovnle_NameIndex = 404,
  kX86InstIdCmovno_NameIndex = 412,
  kX86InstIdCmovnp_NameIndex = 419,
  kX86InstIdCmovns_NameIndex = 426,
  kX86InstIdCmovnz_NameIndex = 433,
  kX86InstIdCmovo_NameIndex = 440,
  kX86InstIdCmovp_NameIndex = 446,
  kX86InstIdCmovpe_NameIndex = 452,
  kX86InstIdCmovpo_NameIndex = 459,
  kX86InstIdCmovs_NameIndex = 466,
  kX86InstIdCmovz_NameIndex = 472,
  kX86InstIdCmp_NameIndex = 478,
  kX86InstIdCmppd_NameIndex = 482,
  kX86InstIdCmpps_NameIndex = 488,
  kX86InstIdCmpsb_NameIndex = 494,
  kX86InstIdCmpsd_NameIndex = 500,
  kX86InstIdCmpsq_NameIndex = 506,
  kX86InstIdCmpss_NameIndex = 512,
  kX86InstIdCmpsw_NameIndex = 518,
  kX86InstIdCmpxchg_NameIndex = 524,
  kX86InstIdCmpxchg16b_NameIndex = 532,
  kX86InstIdCmpxchg8b_NameIndex = 543,
  kX86InstIdComisd_NameIndex = 553,
  kX86InstIdComiss_NameIndex = 560,
  kX86InstIdCpuid_NameIndex = 567,
  kX86InstIdCqo_NameIndex = 573,
  kX86InstIdCrc32_NameIndex = 577,
  kX86InstIdCvtdq2pd_NameIndex = 583,
  kX86InstIdCvtdq2ps_NameIndex = 592,
  kX86InstIdCvtpd2dq_NameIndex = 601,
  kX86InstIdCvtpd2pi_NameIndex = 610,
  kX86InstIdCvtpd2ps_NameIndex = 619,
  kX86InstIdCvtpi2pd_NameIndex = 628,
  kX86InstIdCvtpi2ps_NameIndex = 637,
  kX86InstIdCvtps2dq_NameIndex = 646,
  kX86InstIdCvtps2pd_NameIndex = 655,
  kX86InstIdCvtps2pi_NameIndex = 664,
  kX86InstIdCvtsd2si_NameIndex = 673,
  kX86InstIdCvtsd2ss_NameIndex = 682,
  kX86InstIdCvtsi2sd_NameIndex = 691,
  kX86InstIdCvtsi2ss_NameIndex = 700,
  kX86InstIdCvtss2sd_NameIndex = 709,
  kX86InstIdCvtss2si_NameIndex = 718,
  kX86InstIdCvttpd2dq_NameIndex = 727,
  kX86InstIdCvttpd2pi_NameIndex = 737,
  kX86InstIdCvttps2dq_NameIndex = 747,
  kX86InstIdCvttps2pi_NameIndex = 757,
  kX86InstIdCvttsd2si_NameIndex = 767,
  kX86InstIdCvttss2si_NameIndex = 777,
  kX86InstIdCwd_NameIndex = 787,
  kX86InstIdCwde_NameIndex = 791,
  kX86InstIdDaa_NameIndex = 796,
  kX86InstIdDas_NameIndex = 800,
  kX86InstIdDec_NameIndex = 804,
  kX86InstIdDiv_NameIndex = 808,
  kX86InstIdDivpd_NameIndex = 812,
  kX86InstIdDivps_NameIndex = 818,
  kX86InstIdDivsd_NameIndex = 824,
  kX86InstIdDivss_NameIndex = 830,
  kX86InstIdDppd_NameIndex = 836,
  kX86InstIdDpps_NameIndex = 841,
  kX86InstIdEmms_NameIndex = 846,
  kX86InstIdEnter_NameIndex = 851,
  kX86InstIdExtractps_NameIndex = 857,
  kX86InstIdF2xm1_NameIndex = 867,
  kX86InstIdFabs_NameIndex = 873,
  kX86InstIdFadd_NameIndex = 878,
  kX86InstIdFaddp_NameIndex = 883,
  kX86InstIdFbld_NameIndex = 889,
  kX86InstIdFbstp_NameIndex = 894,
  kX86InstIdFchs_NameIndex = 900,
  kX86InstIdFclex_NameIndex = 905,
  kX86InstIdFcmovb_NameIndex = 911,
  kX86InstIdFcmovbe_NameIndex = 918,
  kX86InstIdFcmove_NameIndex = 926,
  kX86InstIdFcmovnb_NameIndex = 933,
  kX86InstIdFcmovnbe_NameIndex = 941,
  kX86InstIdFcmovne_NameIndex = 950,
  kX86InstIdFcmovnu_NameIndex = 958,
  kX86InstIdFcmovu_NameIndex = 966,
  kX86InstIdFcom_NameIndex = 973,
  kX86InstIdFcomi_NameIndex = 978,
  kX86InstIdFcomip_NameIndex = 984,
  kX86InstIdFcomp_NameIndex = 991,
  kX86InstIdFcompp_NameIndex = 997,
  kX86InstIdFcos_NameIndex = 1004,
  kX86InstIdFdecstp_NameIndex = 1009,
  kX86InstIdFdiv_NameIndex = 1017,
  kX86InstIdFdivp_NameIndex = 1022,
  kX86InstIdFdivr_NameIndex = 1028,
  kX86InstIdFdivrp_NameIndex = 1034,
  kX86InstIdFemms_NameIndex = 1041,
  kX86InstIdFfree_NameIndex = 1047,
  kX86InstIdFiadd_NameIndex = 1053,
  kX86InstIdFicom_NameIndex = 1059,
  kX86InstIdFicomp_NameIndex = 1065,
  kX86InstIdFidiv_NameIndex = 1072,
  kX86InstIdFidivr_NameIndex = 1078,
  kX86InstIdFild_NameIndex = 1085,
  kX86InstIdFimul_NameIndex = 1090,
  kX86InstIdFincstp_NameIndex = 1096,
  kX86InstIdFinit_NameIndex = 1104,
  kX86InstIdFist_NameIndex = 1110,
  kX86InstIdFistp_NameIndex = 1115,
  kX86InstIdFisttp_NameIndex = 1121,
  kX86InstIdFisub_NameIndex = 1128,
  kX86InstIdFisubr_NameIndex = 1134,
  kX86InstIdFld_NameIndex = 1141,
  kX86InstIdFld1_NameIndex = 1145,
  kX86InstIdFldcw_NameIndex = 1150,
  kX86InstIdFldenv_NameIndex = 1156,
  kX86InstIdFldl2e_NameIndex = 1163,
  kX86InstIdFldl2t_NameIndex = 1170,
  kX86InstIdFldlg2_NameIndex = 1177,
  kX86InstIdFldln2_NameIndex = 1184,
  kX86InstIdFldpi_NameIndex = 1191,
  kX86InstIdFldz_NameIndex = 1197,
  kX86InstIdFmul_NameIndex = 1202,
  kX86InstIdFmulp_NameIndex = 1207,
  kX86InstIdFnclex_NameIndex = 1213,
  kX86InstIdFninit_NameIndex = 1220,
  kX86InstIdFnop_NameIndex = 1227,
  kX86InstIdFnsave_NameIndex = 1232,
  kX86InstIdFnstcw_NameIndex = 1239,
  kX86InstIdFnstenv_NameIndex = 1246,
  kX86InstIdFnstsw_NameIndex = 1254,
  kX86InstIdFpatan_NameIndex = 1261,
  kX86InstIdFprem_NameIndex = 1268,
  kX86InstIdFprem1_NameIndex = 1274,
  kX86InstIdFptan_NameIndex = 1281,
  kX86InstIdFrndint_NameIndex = 1287,
  kX86InstIdFrstor_NameIndex = 1295,
  kX86InstIdFsave_NameIndex = 1302,
  kX86InstIdFscale_NameIndex = 1308,
  kX86InstIdFsin_NameIndex = 1315,
  kX86InstIdFsincos_NameIndex = 1320,
  kX86InstIdFsqrt_NameIndex = 1328,
  kX86InstIdFst_NameIndex = 1334,
  kX86InstIdFstcw_NameIndex = 1338,
  kX86InstIdFstenv_NameIndex = 1344,
  kX86InstIdFstp_NameIndex = 1351,
  kX86InstIdFstsw_NameIndex = 1356,
  kX86InstIdFsub_NameIndex = 1362,
  kX86InstIdFsubp_NameIndex = 1367,
  kX86InstIdFsubr_NameIndex = 1373,
  kX86InstIdFsubrp_NameIndex = 1379,
  kX86InstIdFtst_NameIndex = 1386,
  kX86InstIdFucom_NameIndex = 1391,
  kX86InstIdFucomi_NameIndex = 1397,
  kX86InstIdFucomip_NameIndex = 1404,
  kX86InstIdFucomp_NameIndex = 1412,
  kX86InstIdFucompp_NameIndex = 1419,
  kX86InstIdFwait_NameIndex = 1427,
  kX86InstIdFxam_NameIndex = 1433,
  kX86InstIdFxch_NameIndex = 1438,
  kX86InstIdFxrstor_NameIndex = 1443,
  kX86InstIdFxsave_NameIndex = 1451,
  kX86InstIdFxtract_NameIndex = 1458,
  kX86InstIdFyl2x_NameIndex = 1466,
  kX86InstIdFyl2xp1_NameIndex = 1472,
  kX86InstIdHaddpd_NameIndex = 1480,
  kX86InstIdHaddps_NameIndex = 1487,
  kX86InstIdHsubpd_NameIndex = 1494,
  kX86InstIdHsubps_NameIndex = 1501,
  kX86InstIdIdiv_NameIndex = 1508,
  kX86InstIdImul_NameIndex = 1513,
  kX86InstIdInc_NameIndex = 1518,
  kX86InstIdInsertps_NameIndex = 1522,
  kX86InstIdInt_NameIndex = 1531,
  kX86InstIdJa_NameIndex = 1535,
  kX86InstIdJae_NameIndex = 1538,
  kX86InstIdJb_NameIndex = 1542,
  kX86InstIdJbe_NameIndex = 1545,
  kX86InstIdJc_NameIndex = 1549,
  kX86InstIdJe_NameIndex = 1552,
  kX86InstIdJg_NameIndex = 1555,
  kX86InstIdJge_NameIndex = 1558,
  kX86InstIdJl_NameIndex = 1562,
  kX86InstIdJle_NameIndex = 1565,
  kX86InstIdJna_NameIndex = 1569,
  kX86InstIdJnae_NameIndex = 1573,
  kX86InstIdJnb_NameIndex = 1578,
  kX86InstIdJnbe_NameIndex = 1582,
  kX86InstIdJnc_NameIndex = 1587,
  kX86InstIdJne_NameIndex = 1591,
  kX86InstIdJng_NameIndex = 1595,
  kX86InstIdJnge_NameIndex = 1599,
  kX86InstIdJnl_NameIndex = 1604,
  kX86InstIdJnle_NameIndex = 1608,
  kX86InstIdJno_NameIndex = 1613,
  kX86InstIdJnp_NameIndex = 1617,
  kX86InstIdJns_NameIndex = 1621,
  kX86InstIdJnz_NameIndex = 1625,
  kX86InstIdJo_NameIndex = 1629,
  kX86InstIdJp_NameIndex = 1632,
  kX86InstIdJpe_NameIndex = 1635,
  kX86InstIdJpo_NameIndex = 1639,
  kX86InstIdJs_NameIndex = 1643,
  kX86InstIdJz_NameIndex = 1646,
  kX86InstIdJecxz_NameIndex = 1649,
  kX86InstIdJmp_NameIndex = 1655,
  kX86InstIdLahf_NameIndex = 1659,
  kX86InstIdLddqu_NameIndex = 1664,
  kX86InstIdLdmxcsr_NameIndex = 1670,
  kX86InstIdLea_NameIndex = 1678,
  kX86InstIdLeave_NameIndex = 1682,
  kX86InstIdLfence_NameIndex = 1688,
  kX86InstIdLodsb_NameIndex = 1695,
  kX86InstIdLodsd_NameIndex = 1701,
  kX86InstIdLodsq_NameIndex = 1707,
  kX86InstIdLodsw_NameIndex = 1713,
  kX86InstIdLzcnt_NameIndex = 1719,
  kX86InstIdMaskmovdqu_NameIndex = 1725,
  kX86InstIdMaskmovq_NameIndex = 1736,
  kX86InstIdMaxpd_NameIndex = 1745,
  kX86InstIdMaxps_NameIndex = 1751,
  kX86InstIdMaxsd_NameIndex = 1757,
  kX86InstIdMaxss_NameIndex = 1763,
  kX86InstIdMfence_NameIndex = 1769,
  kX86InstIdMinpd_NameIndex = 1776,
  kX86InstIdMinps_NameIndex = 1782,
  kX86InstIdMinsd_NameIndex = 1788,
  kX86InstIdMinss_NameIndex = 1794,
  kX86InstIdMonitor_NameIndex = 1800,
  kX86InstIdMov_NameIndex = 1808,
  kX86InstIdMovPtr_NameIndex = 1812,
  kX86InstIdMovapd_NameIndex = 1820,
  kX86InstIdMovaps_NameIndex = 1827,
  kX86InstIdMovbe_NameIndex = 1834,
  kX86InstIdMovd_NameIndex = 1840,
  kX86InstIdMovddup_NameIndex = 1845,
  kX86InstIdMovdq2q_NameIndex = 1853,
  kX86InstIdMovdqa_NameIndex = 1861,
  kX86InstIdMovdqu_NameIndex = 1868,
  kX86InstIdMovhlps_NameIndex = 1875,
  kX86InstIdMovhpd_NameIndex = 1883,
  kX86InstIdMovhps_NameIndex = 1890,
  kX86InstIdMovlhps_NameIndex = 1897,
  kX86InstIdMovlpd_NameIndex = 1905,
  kX86InstIdMovlps_NameIndex = 1912,
  kX86InstIdMovmskpd_NameIndex = 1919,
  kX86InstIdMovmskps_NameIndex = 1928,
  kX86InstIdMovntdq_NameIndex = 1937,
  kX86InstIdMovntdqa_NameIndex = 1945,
  kX86InstIdMovnti_NameIndex = 1954,
  kX86InstIdMovntpd_NameIndex = 1961,
  kX86InstIdMovntps_NameIndex = 1969,
  kX86InstIdMovntq_NameIndex = 1977,
  kX86InstIdMovq_NameIndex = 1984,
  kX86InstIdMovq2dq_NameIndex = 1989,
  kX86InstIdMovsb_NameIndex = 1997,
  kX86InstIdMovsd_NameIndex = 2003,
  kX86InstIdMovshdup_NameIndex = 2009,
  kX86InstIdMovsldup_NameIndex = 2018,
  kX86InstIdMovsq_NameIndex = 2027,
  kX86InstIdMovss_NameIndex = 2033,
  kX86InstIdMovsw_NameIndex = 2039,
  kX86InstIdMovsx_NameIndex = 2045,
  kX86InstIdMovsxd_NameIndex = 2051,
  kX86InstIdMovupd_NameIndex = 2058,
  kX86InstIdMovups_NameIndex = 2065,
  kX86InstIdMovzx_NameIndex = 2072,
  kX86InstIdMpsadbw_NameIndex = 2078,
  kX86InstIdMul_NameIndex = 2086,
  kX86InstIdMulpd_NameIndex = 2090,
  kX86InstIdMulps_NameIndex = 2096,
  kX86InstIdMulsd_NameIndex = 2102,
  kX86InstIdMulss_NameIndex = 2108,
  kX86InstIdMulx_NameIndex = 2114,
  kX86InstIdMwait_NameIndex = 2119,
  kX86InstIdNeg_NameIndex = 2125,
  kX86InstIdNop_NameIndex = 2129,
  kX86InstIdNot_NameIndex = 2133,
  kX86InstIdOr_NameIndex = 2137,
  kX86InstIdOrpd_NameIndex = 2140,
  kX86InstIdOrps_NameIndex = 2145,
  kX86InstIdPabsb_NameIndex = 2150,
  kX86InstIdPabsd_NameIndex = 2156,
  kX86InstIdPabsw_NameIndex = 2162,
  kX86InstIdPackssdw_NameIndex = 2168,
  kX86InstIdPacksswb_NameIndex = 2177,
  kX86InstIdPackusdw_NameIndex = 2186,
  kX86InstIdPackuswb_NameIndex = 2195,
  kX86InstIdPaddb_NameIndex = 2204,
  kX86InstIdPaddd_NameIndex = 2210,
  kX86InstIdPaddq_NameIndex = 2216,
  kX86InstIdPaddsb_NameIndex = 2222,
  kX86InstIdPaddsw_NameIndex = 2229,
  kX86InstIdPaddusb_NameIndex = 2236,
  kX86InstIdPaddusw_NameIndex = 2244,
  kX86InstIdPaddw_NameIndex = 2252,
  kX86InstIdPalignr_NameIndex = 2258,
  kX86InstIdPand_NameIndex = 2266,
  kX86InstIdPandn_NameIndex = 2271,
  kX86InstIdPause_NameIndex = 2277,
  kX86InstIdPavgb_NameIndex = 2283,
  kX86InstIdPavgw_NameIndex = 2289,
  kX86InstIdPblendvb_NameIndex = 2295,
  kX86InstIdPblendw_NameIndex = 2304,
  kX86InstIdPclmulqdq_NameIndex = 2312,
  kX86InstIdPcmpeqb_NameIndex = 2322,
  kX86InstIdPcmpeqd_NameIndex = 2330,
  kX86InstIdPcmpeqq_NameIndex = 2338,
  kX86InstIdPcmpeqw_NameIndex = 2346,
  kX86InstIdPcmpestri_NameIndex = 2354,
  kX86InstIdPcmpestrm_NameIndex = 2364,
  kX86InstIdPcmpgtb_NameIndex = 2374,
  kX86InstIdPcmpgtd_NameIndex = 2382,
  kX86InstIdPcmpgtq_NameIndex = 2390,
  kX86InstIdPcmpgtw_NameIndex = 2398,
  kX86InstIdPcmpistri_NameIndex = 2406,
  kX86InstIdPcmpistrm_NameIndex = 2416,
  kX86InstIdPdep_NameIndex = 2426,
  kX86InstIdPext_NameIndex = 2431,
  kX86InstIdPextrb_NameIndex = 2436,
  kX86InstIdPextrd_NameIndex = 2443,
  kX86InstIdPextrq_NameIndex = 2450,
  kX86InstIdPextrw_NameIndex = 2457,
  kX86InstIdPf2id_NameIndex = 2464,
  kX86InstIdPf2iw_NameIndex = 2470,
  kX86InstIdPfacc_NameIndex = 2476,
  kX86InstIdPfadd_NameIndex = 2482,
  kX86InstIdPfcmpeq_NameIndex = 2488,
  kX86InstIdPfcmpge_NameIndex = 2496,
  kX86InstIdPfcmpgt_NameIndex = 2504,
  kX86InstIdPfmax_NameIndex = 2512,
  kX86InstIdPfmin_NameIndex = 2518,
  kX86InstIdPfmul_NameIndex = 2524,
  kX86InstIdPfnacc_NameIndex = 2530,
  kX86InstIdPfpnacc_NameIndex = 2537,
  kX86InstIdPfrcp_NameIndex = 2545,
  kX86InstIdPfrcpit1_NameIndex = 2551,
  kX86InstIdPfrcpit2_NameIndex = 2560,
  kX86InstIdPfrsqit1_NameIndex = 2569,
  kX86InstIdPfrsqrt_NameIndex = 2578,
  kX86InstIdPfsub_NameIndex = 2586,
  kX86InstIdPfsubr_NameIndex = 2592,
  kX86InstIdPhaddd_NameIndex = 2599,
  kX86InstIdPhaddsw_NameIndex = 2606,
  kX86InstIdPhaddw_NameIndex = 2614,
  kX86InstIdPhminposuw_NameIndex = 2621,
  kX86InstIdPhsubd_NameIndex = 2632,
  kX86InstIdPhsubsw_NameIndex = 2639,
  kX86InstIdPhsubw_NameIndex = 2647,
  kX86InstIdPi2fd_NameIndex = 2654,
  kX86InstIdPi2fw_NameIndex = 2660,
  kX86InstIdPinsrb_NameIndex = 2666,
  kX86InstIdPinsrd_NameIndex = 2673,
  kX86InstIdPinsrq_NameIndex = 2680,
  kX86InstIdPinsrw_NameIndex = 2687,
  kX86InstIdPmaddubsw_NameIndex = 2694,
  kX86InstIdPmaddwd_NameIndex = 2704,
  kX86InstIdPmaxsb_NameIndex = 2712,
  kX86InstIdPmaxsd_NameIndex = 2719,
  kX86InstIdPmaxsw_NameIndex = 2726,
  kX86InstIdPmaxub_NameIndex = 2733,
  kX86InstIdPmaxud_NameIndex = 2740,
  kX86InstIdPmaxuw_NameIndex = 2747,
  kX86InstIdPminsb_NameIndex = 2754,
  kX86InstIdPminsd_NameIndex = 2761,
  kX86InstIdPminsw_NameIndex = 2768,
  kX86InstIdPminub_NameIndex = 2775,
  kX86InstIdPminud_NameIndex = 2782,
  kX86InstIdPminuw_NameIndex = 2789,
  kX86InstIdPmovmskb_NameIndex = 2796,
  kX86InstIdPmovsxbd_NameIndex = 2805,
  kX86InstIdPmovsxbq_NameIndex = 2814,
  kX86InstIdPmovsxbw_NameIndex = 2823,
  kX86InstIdPmovsxdq_NameIndex = 2832,
  kX86InstIdPmovsxwd_NameIndex = 2841,
  kX86InstIdPmovsxwq_NameIndex = 2850,
  kX86InstIdPmovzxbd_NameIndex = 2859,
  kX86InstIdPmovzxbq_NameIndex = 2868,
  kX86InstIdPmovzxbw_NameIndex = 2877,
  kX86InstIdPmovzxdq_NameIndex = 2886,
  kX86InstIdPmovzxwd_NameIndex = 2895,
  kX86InstIdPmovzxwq_NameIndex = 2904,
  kX86InstIdPmuldq_NameIndex = 2913,
  kX86InstIdPmulhrsw_NameIndex = 2920,
  kX86InstIdPmulhuw_NameIndex = 2929,
  kX86InstIdPmulhw_NameIndex = 2937,
  kX86InstIdPmulld_NameIndex = 2944,
  kX86InstIdPmullw_NameIndex = 2951,
  kX86InstIdPmuludq_NameIndex = 2958,
  kX86InstIdPop_NameIndex = 2966,
  kX86InstIdPopa_NameIndex = 2970,
  kX86InstIdPopcnt_NameIndex = 2975,
  kX86InstIdPopf_NameIndex = 2982,
  kX86InstIdPor_NameIndex = 2987,
  kX86InstIdPrefetch_NameIndex = 2991,
  kX86InstIdPrefetch3dNow_NameIndex = 3000,
  kX86InstIdPrefetchw3dNow_NameIndex = 3015,
  kX86InstIdPsadbw_NameIndex = 3031,
  kX86InstIdPshufb_NameIndex = 3038,
  kX86InstIdPshufd_NameIndex = 3045,
  kX86InstIdPshufhw_NameIndex = 3052,
  kX86InstIdPshuflw_NameIndex = 3060,
  kX86InstIdPshufw_NameIndex = 3068,
  kX86InstIdPsignb_NameIndex = 3075,
  kX86InstIdPsignd_NameIndex = 3082,
  kX86InstIdPsignw_NameIndex = 3089,
  kX86InstIdPslld_NameIndex = 3096,
  kX86InstIdPslldq_NameIndex = 3102,
  kX86InstIdPsllq_NameIndex = 3109,
  kX86InstIdPsllw_NameIndex = 3115,
  kX86InstIdPsrad_NameIndex = 3121,
  kX86InstIdPsraw_NameIndex = 3127,
  kX86InstIdPsrld_NameIndex = 3133,
  kX86InstIdPsrldq_NameIndex = 3139,
  kX86InstIdPsrlq_NameIndex = 3146,
  kX86InstIdPsrlw_NameIndex = 3152,
  kX86InstIdPsubb_NameIndex = 3158,
  kX86InstIdPsubd_NameIndex = 3164,
  kX86InstIdPsubq_NameIndex = 3170,
  kX86InstIdPsubsb_NameIndex = 3176,
  kX86InstIdPsubsw_NameIndex = 3183,
  kX86InstIdPsubusb_NameIndex = 3190,
  kX86InstIdPsubusw_NameIndex = 3198,
  kX86InstIdPsubw_NameIndex = 3206,
  kX86InstIdPswapd_NameIndex = 3212,
  kX86InstIdPtest_NameIndex = 3219,
  kX86InstIdPunpckhbw_NameIndex = 3225,
  kX86InstIdPunpckhdq_NameIndex = 3235,
  kX86InstIdPunpckhqdq_NameIndex = 3245,
  kX86InstIdPunpckhwd_NameIndex = 3256,
  kX86InstIdPunpcklbw_NameIndex = 3266,
  kX86InstIdPunpckldq_NameIndex = 3276,
  kX86InstIdPunpcklqdq_NameIndex = 3286,
  kX86InstIdPunpcklwd_NameIndex = 3297,
  kX86InstIdPush_NameIndex = 3307,
  kX86InstIdPusha_NameIndex = 3312,
  kX86InstIdPushf_NameIndex = 3318,
  kX86InstIdPxor_NameIndex = 3324,
  kX86InstIdRcl_NameIndex = 3329,
  kX86InstIdRcpps_NameIndex = 3333,
  kX86InstIdRcpss_NameIndex = 3339,
  kX86InstIdRcr_NameIndex = 3345,
  kX86InstIdRdfsbase_NameIndex = 3349,
  kX86InstIdRdgsbase_NameIndex = 3358,
  kX86InstIdRdrand_NameIndex = 3367,
  kX86InstIdRdtsc_NameIndex = 3374,
  kX86InstIdRdtscp_NameIndex = 3380,
  kX86InstIdRepLodsb_NameIndex = 3387,
  kX86InstIdRepLodsd_NameIndex = 3397,
  kX86InstIdRepLodsq_NameIndex = 3407,
  kX86InstIdRepLodsw_NameIndex = 3417,
  kX86InstIdRepMovsb_NameIndex = 3427,
  kX86InstIdRepMovsd_NameIndex = 3437,
  kX86InstIdRepMovsq_NameIndex = 3447,
  kX86InstIdRepMovsw_NameIndex = 3457,
  kX86InstIdRepStosb_NameIndex = 3467,
  kX86InstIdRepStosd_NameIndex = 3477,
  kX86InstIdRepStosq_NameIndex = 3487,
  kX86InstIdRepStosw_NameIndex = 3497,
  kX86InstIdRepeCmpsb_NameIndex = 3507,
  kX86InstIdRepeCmpsd_NameIndex = 3518,
  kX86InstIdRepeCmpsq_NameIndex = 3529,
  kX86InstIdRepeCmpsw_NameIndex = 3540,
  kX86InstIdRepeScasb_NameIndex = 3551,
  kX86InstIdRepeScasd_NameIndex = 3562,
  kX86InstIdRepeScasq_NameIndex = 3573,
  kX86InstIdRepeScasw_NameIndex = 3584,
  kX86InstIdRepneCmpsb_NameIndex = 3595,
  kX86InstIdRepneCmpsd_NameIndex = 3607,
  kX86InstIdRepneCmpsq_NameIndex = 3619,
  kX86InstIdRepneCmpsw_NameIndex = 3631,
  kX86InstIdRepneScasb_NameIndex = 3643,
  kX86InstIdRepneScasd_NameIndex = 3655,
  kX86InstIdRepneScasq_NameIndex = 3667,
  kX86InstIdRepneScasw_NameIndex = 3679,
  kX86InstIdRet_NameIndex = 3691,
  kX86InstIdRol_NameIndex = 3695,
  kX86InstIdRor_NameIndex = 3699,
  kX86InstIdRorx_NameIndex = 3703,
  kX86InstIdRoundpd_NameIndex = 3708,
  kX86InstIdRoundps_NameIndex = 3716,
  kX86InstIdRoundsd_NameIndex = 3724,
  kX86InstIdRoundss_NameIndex = 3732,
  kX86InstIdRsqrtps_NameIndex = 3740,
  kX86InstIdRsqrtss_NameIndex = 3748,
  kX86InstIdSahf_NameIndex = 3756,
  kX86InstIdSal_NameIndex = 3761,
  kX86InstIdSar_NameIndex = 3765,
  kX86InstIdSarx_NameIndex = 3769,
  kX86InstIdSbb_NameIndex = 3774,
  kX86InstIdScasb_NameIndex = 3778,
  kX86InstIdScasd_NameIndex = 3784,
  kX86InstIdScasq_NameIndex = 3790,
  kX86InstIdScasw_NameIndex = 3796,
  kX86InstIdSeta_NameIndex = 3802,
  kX86InstIdSetae_NameIndex = 3807,
  kX86InstIdSetb_NameIndex = 3813,
  kX86InstIdSetbe_NameIndex = 3818,
  kX86InstIdSetc_NameIndex = 3824,
  kX86InstIdSete_NameIndex = 3829,
  kX86InstIdSetg_NameIndex = 3834,
  kX86InstIdSetge_NameIndex = 3839,
  kX86InstIdSetl_NameIndex = 3845,
  kX86InstIdSetle_NameIndex = 3850,
  kX86InstIdSetna_NameIndex = 3856,
  kX86InstIdSetnae_NameIndex = 3862,
  kX86InstIdSetnb_NameIndex = 3869,
  kX86InstIdSetnbe_NameIndex = 3875,
  kX86InstIdSetnc_NameIndex = 3882,
  kX86InstIdSetne_NameIndex = 3888,
  kX86InstIdSetng_NameIndex = 3894,
  kX86InstIdSetnge_NameIndex = 3900,
  kX86InstIdSetnl_NameIndex = 3907,
  kX86InstIdSetnle_NameIndex = 3913,
  kX86InstIdSetno_NameIndex = 3920,
  kX86InstIdSetnp_NameIndex = 3926,
  kX86InstIdSetns_NameIndex = 3932,
  kX86InstIdSetnz_NameIndex = 3938,
  kX86InstIdSeto_NameIndex = 3944,
  kX86InstIdSetp_NameIndex = 3949,
  kX86InstIdSetpe_NameIndex = 3954,
  kX86InstIdSetpo_NameIndex = 3960,
  kX86InstIdSets_NameIndex = 3966,
  kX86InstIdSetz_NameIndex = 3971,
  kX86InstIdSfence_NameIndex = 3976,
  kX86InstIdShl_NameIndex = 3983,
  kX86InstIdShld_NameIndex = 3987,
  kX86InstIdShlx_NameIndex = 3992,
  kX86InstIdShr_NameIndex = 3997,
  kX86InstIdShrd_NameIndex = 4001,
  kX86InstIdShrx_NameIndex = 4006,
  kX86InstIdShufpd_NameIndex = 4011,
  kX86InstIdShufps_NameIndex = 4018,
  kX86InstIdSqrtpd_NameIndex = 4025,
  kX86InstIdSqrtps_NameIndex = 4032,
  kX86InstIdSqrtsd_NameIndex = 4039,
  kX86InstIdSqrtss_NameIndex = 4046,
  kX86InstIdStc_NameIndex = 4053,
  kX86InstIdStd_NameIndex = 4057,
  kX86InstIdStmxcsr_NameIndex = 4061,
  kX86InstIdStosb_NameIndex = 4069,
  kX86InstIdStosd_NameIndex = 4075,
  kX86InstIdStosq_NameIndex = 4081,
  kX86InstIdStosw_NameIndex = 4087,
  kX86InstIdSub_NameIndex = 4093,
  kX86InstIdSubpd_NameIndex = 4097,
  kX86InstIdSubps_NameIndex = 4103,
  kX86InstIdSubsd_NameIndex = 4109,
  kX86InstIdSubss_NameIndex = 4115,
  kX86InstIdTest_NameIndex = 4121,
  kX86InstIdTzcnt_NameIndex = 4126,
  kX86InstIdUcomisd_NameIndex = 4132,
  kX86InstIdUcomiss_NameIndex = 4140,
  kX86InstIdUd2_NameIndex = 4148,
  kX86InstIdUnpckhpd_NameIndex = 4152,
  kX86InstIdUnpckhps_NameIndex = 4161,
  kX86InstIdUnpcklpd_NameIndex = 4170,
  kX86InstIdUnpcklps_NameIndex = 4179,
  kX86InstIdVaddpd_NameIndex = 4188,
  kX86InstIdVaddps_NameIndex = 4195,
  kX86InstIdVaddsd_NameIndex = 4202,
  kX86InstIdVaddss_NameIndex = 4209,
  kX86InstIdVaddsubpd_NameIndex = 4216,
  kX86InstIdVaddsubps_NameIndex = 4226,
  kX86InstIdVaesdec_NameIndex = 4236,
  kX86InstIdVaesdeclast_NameIndex = 4244,
  kX86InstIdVaesenc_NameIndex = 4256,
  kX86InstIdVaesenclast_NameIndex = 4264,
  kX86InstIdVaesimc_NameIndex = 4276,
  kX86InstIdVaeskeygenassist_NameIndex = 4284,
  kX86InstIdVandnpd_NameIndex = 4301,
  kX86InstIdVandnps_NameIndex = 4309,
  kX86InstIdVandpd_NameIndex = 4317,
  kX86InstIdVandps_NameIndex = 4324,
  kX86InstIdVblendpd_NameIndex = 4331,
  kX86InstIdVblendps_NameIndex = 4340,
  kX86InstIdVblendvpd_NameIndex = 4349,
  kX86InstIdVblendvps_NameIndex = 4359,
  kX86InstIdVbroadcastf128_NameIndex = 4369,
  kX86InstIdVbroadcasti128_NameIndex = 4384,
  kX86InstIdVbroadcastsd_NameIndex = 4399,
  kX86InstIdVbroadcastss_NameIndex = 4412,
  kX86InstIdVcmppd_NameIndex = 4425,
  kX86InstIdVcmpps_NameIndex = 4432,
  kX86InstIdVcmpsd_NameIndex = 4439,
  kX86InstIdVcmpss_NameIndex = 4446,
  kX86InstIdVcomisd_NameIndex = 4453,
  kX86InstIdVcomiss_NameIndex = 4461,
  kX86InstIdVcvtdq2pd_NameIndex = 4469,
  kX86InstIdVcvtdq2ps_NameIndex = 4479,
  kX86InstIdVcvtpd2dq_NameIndex = 4489,
  kX86InstIdVcvtpd2ps_NameIndex = 4499,
  kX86InstIdVcvtph2ps_NameIndex = 4509,
  kX86InstIdVcvtps2dq_NameIndex = 4519,
  kX86InstIdVcvtps2pd_NameIndex = 4529,
  kX86InstIdVcvtps2ph_NameIndex = 4539,
  kX86InstIdVcvtsd2si_NameIndex = 4549,
  kX86InstIdVcvtsd2ss_NameIndex = 4559,
  kX86InstIdVcvtsi2sd_NameIndex = 4569,
  kX86InstIdVcvtsi2ss_NameIndex = 4579,
  kX86InstIdVcvtss2sd_NameIndex = 4589,
  kX86InstIdVcvtss2si_NameIndex = 4599,
  kX86InstIdVcvttpd2dq_NameIndex = 4609,
  kX86InstIdVcvttps2dq_NameIndex = 4620,
  kX86InstIdVcvttsd2si_NameIndex = 4631,
  kX86InstIdVcvttss2si_NameIndex = 4642,
  kX86InstIdVdivpd_NameIndex = 4653,
  kX86InstIdVdivps_NameIndex = 4660,
  kX86InstIdVdivsd_NameIndex = 4667,
  kX86InstIdVdivss_NameIndex = 4674,
  kX86InstIdVdppd_NameIndex = 4681,
  kX86InstIdVdpps_NameIndex = 4687,
  kX86InstIdVextractf128_NameIndex = 4693,
  kX86InstIdVextracti128_NameIndex = 4706,
  kX86InstIdVextractps_NameIndex = 4719,
  kX86InstIdVfmadd132pd_NameIndex = 4730,
  kX86InstIdVfmadd132ps_NameIndex = 4742,
  kX86InstIdVfmadd132sd_NameIndex = 4754,
  kX86InstIdVfmadd132ss_NameIndex = 4766,
  kX86InstIdVfmadd213pd_NameIndex = 4778,
  kX86InstIdVfmadd213ps_NameIndex = 4790,
  kX86InstIdVfmadd213sd_NameIndex = 4802,
  kX86InstIdVfmadd213ss_NameIndex = 4814,
  kX86InstIdVfmadd231pd_NameIndex = 4826,
  kX86InstIdVfmadd231ps_NameIndex = 4838,
  kX86InstIdVfmadd231sd_NameIndex = 4850,
  kX86InstIdVfmadd231ss_NameIndex = 4862,
  kX86InstIdVfmaddpd_NameIndex = 4874,
  kX86InstIdVfmaddps_NameIndex = 4883,
  kX86InstIdVfmaddsd_NameIndex = 4892,
  kX86InstIdVfmaddss_NameIndex = 4901,
  kX86InstIdVfmaddsub132pd_NameIndex = 4910,
  kX86InstIdVfmaddsub132ps_NameIndex = 4925,
  kX86InstIdVfmaddsub213pd_NameIndex = 4940,
  kX86InstIdVfmaddsub213ps_NameIndex = 4955,
  kX86InstIdVfmaddsub231pd_NameIndex = 4970,
  kX86InstIdVfmaddsub231ps_NameIndex = 4985,
  kX86InstIdVfmaddsubpd_NameIndex = 5000,
  kX86InstIdVfmaddsubps_NameIndex = 5012,
  kX86InstIdVfmsub132pd_NameIndex = 5024,
  kX86InstIdVfmsub132ps_NameIndex = 5036,
  kX86InstIdVfmsub132sd_NameIndex = 5048,
  kX86InstIdVfmsub132ss_NameIndex = 5060,
  kX86InstIdVfmsub213pd_NameIndex = 5072,
  kX86InstIdVfmsub213ps_NameIndex = 5084,
  kX86InstIdVfmsub213sd_NameIndex = 5096,
  kX86InstIdVfmsub213ss_NameIndex = 5108,
  kX86InstIdVfmsub231pd_NameIndex = 5120,
  kX86InstIdVfmsub231ps_NameIndex = 5132,
  kX86InstIdVfmsub231sd_NameIndex = 5144,
  kX86InstIdVfmsub231ss_NameIndex = 5156,
  kX86InstIdVfmsubadd132pd_NameIndex = 5168,
  kX86InstIdVfmsubadd132ps_NameIndex = 5183,
  kX86InstIdVfmsubadd213pd_NameIndex = 5198,
  kX86InstIdVfmsubadd213ps_NameIndex = 5213,
  kX86InstIdVfmsubadd231pd_NameIndex = 5228,
  kX86InstIdVfmsubadd231ps_NameIndex = 5243,
  kX86InstIdVfmsubaddpd_NameIndex = 5258,
  kX86InstIdVfmsubaddps_NameIndex = 5270,
  kX86InstIdVfmsubpd_NameIndex = 5282,
  kX86InstIdVfmsubps_NameIndex = 5291,
  kX86InstIdVfmsubsd_NameIndex = 5300,
  kX86InstIdVfmsubss_NameIndex = 5309,
  kX86InstIdVfnmadd132pd_NameIndex = 5318,
  kX86InstIdVfnmadd132ps_NameIndex = 5331,
  kX86InstIdVfnmadd132sd_NameIndex = 5344,
  kX86InstIdVfnmadd132ss_NameIndex = 5357,
  kX86InstIdVfnmadd213pd_NameIndex = 5370,
  kX86InstIdVfnmadd213ps_NameIndex = 5383,
  kX86InstIdVfnmadd213sd_NameIndex = 5396,
  kX86InstIdVfnmadd213ss_NameIndex = 5409,
  kX86InstIdVfnmadd231pd_NameIndex = 5422,
  kX86InstIdVfnmadd231ps_NameIndex = 5435,
  kX86InstIdVfnmadd231sd_NameIndex = 5448,
  kX86InstIdVfnmadd231ss_NameIndex = 5461,
  kX86InstIdVfnmaddpd_NameIndex = 5474,
  kX86InstIdVfnmaddps_NameIndex = 5484,
  kX86InstIdVfnmaddsd_NameIndex = 5494,
  kX86InstIdVfnmaddss_NameIndex = 5504,
  kX86InstIdVfnmsub132pd_NameIndex = 5514,
  kX86InstIdVfnmsub132ps_NameIndex = 5527,
  kX86InstIdVfnmsub132sd_NameIndex = 5540,
  kX86InstIdVfnmsub132ss_NameIndex = 5553,
  kX86InstIdVfnmsub213pd_NameIndex = 5566,
  kX86InstIdVfnmsub213ps_NameIndex = 5579,
  kX86InstIdVfnmsub213sd_NameIndex = 5592,
  kX86InstIdVfnmsub213ss_NameIndex = 5605,
  kX86InstIdVfnmsub231pd_NameIndex = 5618,
  kX86InstIdVfnmsub231ps_NameIndex = 5631,
  kX86InstIdVfnmsub231sd_NameIndex = 5644,
  kX86InstIdVfnmsub231ss_NameIndex = 5657,
  kX86InstIdVfnmsubpd_NameIndex = 5670,
  kX86InstIdVfnmsubps_NameIndex = 5680,
  kX86InstIdVfnmsubsd_NameIndex = 5690,
  kX86InstIdVfnmsubss_NameIndex = 5700,
  kX86InstIdVfrczpd_NameIndex = 5710,
  kX86InstIdVfrczps_NameIndex = 5718,
  kX86InstIdVfrczsd_NameIndex = 5726,
  kX86InstIdVfrczss_NameIndex = 5734,
  kX86InstIdVgatherdpd_NameIndex = 5742,
  kX86InstIdVgatherdps_NameIndex = 5753,
  kX86InstIdVgatherqpd_NameIndex = 5764,
  kX86InstIdVgatherqps_NameIndex = 5775,
  kX86InstIdVhaddpd_NameIndex = 5786,
  kX86InstIdVhaddps_NameIndex = 5794,
  kX86InstIdVhsubpd_NameIndex = 5802,
  kX86InstIdVhsubps_NameIndex = 5810,
  kX86InstIdVinsertf128_NameIndex = 5818,
  kX86InstIdVinserti128_NameIndex = 5830,
  kX86InstIdVinsertps_NameIndex = 5842,
  kX86InstIdVlddqu_NameIndex = 5852,
  kX86InstIdVldmxcsr_NameIndex = 5859,
  kX86InstIdVmaskmovdqu_NameIndex = 5868,
  kX86InstIdVmaskmovpd_NameIndex = 5880,
  kX86InstIdVmaskmovps_NameIndex = 5891,
  kX86InstIdVmaxpd_NameIndex = 5902,
  kX86InstIdVmaxps_NameIndex = 5909,
  kX86InstIdVmaxsd_NameIndex = 5916,
  kX86InstIdVmaxss_NameIndex = 5923,
  kX86InstIdVminpd_NameIndex = 5930,
  kX86InstIdVminps_NameIndex = 5937,
  kX86InstIdVminsd_NameIndex = 5944,
  kX86InstIdVminss_NameIndex = 5951,
  kX86InstIdVmovapd_NameIndex = 5958,
  kX86InstIdVmovaps_NameIndex = 5966,
  kX86InstIdVmovd_NameIndex = 5974,
  kX86InstIdVmovddup_NameIndex = 5980,
  kX86InstIdVmovdqa_NameIndex = 5989,
  kX86InstIdVmovdqu_NameIndex = 5997,
  kX86InstIdVmovhlps_NameIndex = 6005,
  kX86InstIdVmovhpd_NameIndex = 6014,
  kX86InstIdVmovhps_NameIndex = 6022,
  kX86InstIdVmovlhps_NameIndex = 6030,
  kX86InstIdVmovlpd_NameIndex = 6039,
  kX86InstIdVmovlps_NameIndex = 6047,
  kX86InstIdVmovmskpd_NameIndex = 6055,
  kX86InstIdVmovmskps_NameIndex = 6065,
  kX86InstIdVmovntdq_NameIndex = 6075,
  kX86InstIdVmovntdqa_NameIndex = 6084,
  kX86InstIdVmovntpd_NameIndex = 6094,
  kX86InstIdVmovntps_NameIndex = 6103,
  kX86InstIdVmovq_NameIndex = 6112,
  kX86InstIdVmovsd_NameIndex = 6118,
  kX86InstIdVmovshdup_NameIndex = 6125,
  kX86InstIdVmovsldup_NameIndex = 6135,
  kX86InstIdVmovss_NameIndex = 6145,
  kX86InstIdVmovupd_NameIndex = 6152,
  kX86InstIdVmovups_NameIndex = 6160,
  kX86InstIdVmpsadbw_NameIndex = 6168,
  kX86InstIdVmulpd_NameIndex = 6177,
  kX86InstIdVmulps_NameIndex = 6184,
  kX86InstIdVmulsd_NameIndex = 6191,
  kX86InstIdVmulss_NameIndex = 6198,
  kX86InstIdVorpd_NameIndex = 6205,
  kX86InstIdVorps_NameIndex = 6211,
  kX86InstIdVpabsb_NameIndex = 6217,
  kX86InstIdVpabsd_NameIndex = 6224,
  kX86InstIdVpabsw_NameIndex = 6231,
  kX86InstIdVpackssdw_NameIndex = 6238,
  kX86InstIdVpacksswb_NameIndex = 6248,
  kX86InstIdVpackusdw_NameIndex = 6258,
  kX86InstIdVpackuswb_NameIndex = 6268,
  kX86InstIdVpaddb_NameIndex = 6278,
  kX86InstIdVpaddd_NameIndex = 6285,
  kX86InstIdVpaddq_NameIndex = 6292,
  kX86InstIdVpaddsb_NameIndex = 6299,
  kX86InstIdVpaddsw_NameIndex = 6307,
  kX86InstIdVpaddusb_NameIndex = 6315,
  kX86InstIdVpaddusw_NameIndex = 6324,
  kX86InstIdVpaddw_NameIndex = 6333,
  kX86InstIdVpalignr_NameIndex = 6340,
  kX86InstIdVpand_NameIndex = 6349,
  kX86InstIdVpandn_NameIndex = 6355,
  kX86InstIdVpavgb_NameIndex = 6362,
  kX86InstIdVpavgw_NameIndex = 6369,
  kX86InstIdVpblendd_NameIndex = 6376,
  kX86InstIdVpblendvb_NameIndex = 6385,
  kX86InstIdVpblendw_NameIndex = 6395,
  kX86InstIdVpbroadcastb_NameIndex = 6404,
  kX86InstIdVpbroadcastd_NameIndex = 6417,
  kX86InstIdVpbroadcastq_NameIndex = 6430,
  kX86InstIdVpbroadcastw_NameIndex = 6443,
  kX86InstIdVpclmulqdq_NameIndex = 6456,
  kX86InstIdVpcmov_NameIndex = 6467,
  kX86InstIdVpcmpeqb_NameIndex = 6474,
  kX86InstIdVpcmpeqd_NameIndex = 6483,
  kX86InstIdVpcmpeqq_NameIndex = 6492,
  kX86InstIdVpcmpeqw_NameIndex = 6501,
  kX86InstIdVpcmpestri_NameIndex = 6510,
  kX86InstIdVpcmpestrm_NameIndex = 6521,
  kX86InstIdVpcmpgtb_NameIndex = 6532,
  kX86InstIdVpcmpgtd_NameIndex = 6541,
  kX86InstIdVpcmpgtq_NameIndex = 6550,
  kX86InstIdVpcmpgtw_NameIndex = 6559,
  kX86InstIdVpcmpistri_NameIndex = 6568,
  kX86InstIdVpcmpistrm_NameIndex = 6579,
  kX86InstIdVpcomb_NameIndex = 6590,
  kX86InstIdVpcomd_NameIndex = 6597,
  kX86InstIdVpcomq_NameIndex = 6604,
  kX86InstIdVpcomub_NameIndex = 6611,
  kX86InstIdVpcomud_NameIndex = 6619,
  kX86InstIdVpcomuq_NameIndex = 6627,
  kX86InstIdVpcomuw_NameIndex = 6635,
  kX86InstIdVpcomw_NameIndex = 6643,
  kX86InstIdVperm2f128_NameIndex = 6650,
  kX86InstIdVperm2i128_NameIndex = 6661,
  kX86InstIdVpermd_NameIndex = 6672,
  kX86InstIdVpermil2pd_NameIndex = 6679,
  kX86InstIdVpermil2ps_NameIndex = 6690,
  kX86InstIdVpermilpd_NameIndex = 6701,
  kX86InstIdVpermilps_NameIndex = 6711,
  kX86InstIdVpermpd_NameIndex = 6721,
  kX86InstIdVpermps_NameIndex = 6729,
  kX86InstIdVpermq_NameIndex = 6737,
  kX86InstIdVpextrb_NameIndex = 6744,
  kX86InstIdVpextrd_NameIndex = 6752,
  kX86InstIdVpextrq_NameIndex = 6760,
  kX86InstIdVpextrw_NameIndex = 6768,
  kX86InstIdVpgatherdd_NameIndex = 6776,
  kX86InstIdVpgatherdq_NameIndex = 6787,
  kX86InstIdVpgatherqd_NameIndex = 6798,
  kX86InstIdVpgatherqq_NameIndex = 6809,
  kX86InstIdVphaddbd_NameIndex = 6820,
  kX86InstIdVphaddbq_NameIndex = 6829,
  kX86InstIdVphaddbw_NameIndex = 6838,
  kX86InstIdVphaddd_NameIndex = 6847,
  kX86InstIdVphadddq_NameIndex = 6855,
  kX86InstIdVphaddsw_NameIndex = 6864,
  kX86InstIdVphaddubd_NameIndex = 6873,
  kX86InstIdVphaddubq_NameIndex = 6883,
  kX86InstIdVphaddubw_NameIndex = 6893,
  kX86InstIdVphaddudq_NameIndex = 6903,
  kX86InstIdVphadduwd_NameIndex = 6913,
  kX86InstIdVphadduwq_NameIndex = 6923,
  kX86InstIdVphaddw_NameIndex = 6933,
  kX86InstIdVphaddwd_NameIndex = 6941,
  kX86InstIdVphaddwq_NameIndex = 6950,
  kX86InstIdVphminposuw_NameIndex = 6959,
  kX86InstIdVphsubbw_NameIndex = 6971,
  kX86InstIdVphsubd_NameIndex = 6980,
  kX86InstIdVphsubdq_NameIndex = 6988,
  kX86InstIdVphsubsw_NameIndex = 6997,
  kX86InstIdVphsubw_NameIndex = 7006,
  kX86InstIdVphsubwd_NameIndex = 7014,
  kX86InstIdVpinsrb_NameIndex = 7023,
  kX86InstIdVpinsrd_NameIndex = 7031,
  kX86InstIdVpinsrq_NameIndex = 7039,
  kX86InstIdVpinsrw_NameIndex = 7047,
  kX86InstIdVpmacsdd_NameIndex = 7055,
  kX86InstIdVpmacsdqh_NameIndex = 7064,
  kX86InstIdVpmacsdql_NameIndex = 7074,
  kX86InstIdVpmacssdd_NameIndex = 7084,
  kX86InstIdVpmacssdqh_NameIndex = 7094,
  kX86InstIdVpmacssdql_NameIndex = 7105,
  kX86InstIdVpmacsswd_NameIndex = 7116,
  kX86InstIdVpmacssww_NameIndex = 7126,
  kX86InstIdVpmacswd_NameIndex = 7136,
  kX86InstIdVpmacsww_NameIndex = 7145,
  kX86InstIdVpmadcsswd_NameIndex = 7154,
  kX86InstIdVpmadcswd_NameIndex = 7165,
  kX86InstIdVpmaddubsw_NameIndex = 7175,
  kX86InstIdVpmaddwd_NameIndex = 7186,
  kX86InstIdVpmaskmovd_NameIndex = 7195,
  kX86InstIdVpmaskmovq_NameIndex = 7206,
  kX86InstIdVpmaxsb_NameIndex = 7217,
  kX86InstIdVpmaxsd_NameIndex = 7225,
  kX86InstIdVpmaxsw_NameIndex = 7233,
  kX86InstIdVpmaxub_NameIndex = 7241,
  kX86InstIdVpmaxud_NameIndex = 7249,
  kX86InstIdVpmaxuw_NameIndex = 7257,
  kX86InstIdVpminsb_NameIndex = 7265,
  kX86InstIdVpminsd_NameIndex = 7273,
  kX86InstIdVpminsw_NameIndex = 7281,
  kX86InstIdVpminub_NameIndex = 7289,
  kX86InstIdVpminud_NameIndex = 7297,
  kX86InstIdVpminuw_NameIndex = 7305,
  kX86InstIdVpmovmskb_NameIndex = 7313,
  kX86InstIdVpmovsxbd_NameIndex = 7323,
  kX86InstIdVpmovsxbq_NameIndex = 7333,
  kX86InstIdVpmovsxbw_NameIndex = 7343,
  kX86InstIdVpmovsxdq_NameIndex = 7353,
  kX86InstIdVpmovsxwd_NameIndex = 7363,
  kX86InstIdVpmovsxwq_NameIndex = 7373,
  kX86InstIdVpmovzxbd_NameIndex = 7383,
  kX86InstIdVpmovzxbq_NameIndex = 7393,
  kX86InstIdVpmovzxbw_NameIndex = 7403,
  kX86InstIdVpmovzxdq_NameIndex = 7413,
  kX86InstIdVpmovzxwd_NameIndex = 7423,
  kX86InstIdVpmovzxwq_NameIndex = 7433,
  kX86InstIdVpmuldq_NameIndex = 7443,
  kX86InstIdVpmulhrsw_NameIndex = 7451,
  kX86InstIdVpmulhuw_NameIndex = 7461,
  kX86InstIdVpmulhw_NameIndex = 7470,
  kX86InstIdVpmulld_NameIndex = 7478,
  kX86InstIdVpmullw_NameIndex = 7486,
  kX86InstIdVpmuludq_NameIndex = 7494,
  kX86InstIdVpor_NameIndex = 7503,
  kX86InstIdVpperm_NameIndex = 7508,
  kX86InstIdVprotb_NameIndex = 7515,
  kX86InstIdVprotd_NameIndex = 7522,
  kX86InstIdVprotq_NameIndex = 7529,
  kX86InstIdVprotw_NameIndex = 7536,
  kX86InstIdVpsadbw_NameIndex = 7543,
  kX86InstIdVpshab_NameIndex = 7551,
  kX86InstIdVpshad_NameIndex = 7558,
  kX86InstIdVpshaq_NameIndex = 7565,
  kX86InstIdVpshaw_NameIndex = 7572,
  kX86InstIdVpshlb_NameIndex = 7579,
  kX86InstIdVpshld_NameIndex = 7586,
  kX86InstIdVpshlq_NameIndex = 7593,
  kX86InstIdVpshlw_NameIndex = 7600,
  kX86InstIdVpshufb_NameIndex = 7607,
  kX86InstIdVpshufd_NameIndex = 7615,
  kX86InstIdVpshufhw_NameIndex = 7623,
  kX86InstIdVpshuflw_NameIndex = 7632,
  kX86InstIdVpsignb_NameIndex = 7641,
  kX86InstIdVpsignd_NameIndex = 7649,
  kX86InstIdVpsignw_NameIndex = 7657,
  kX86InstIdVpslld_NameIndex = 7665,
  kX86InstIdVpslldq_NameIndex = 7672,
  kX86InstIdVpsllq_NameIndex = 7680,
  kX86InstIdVpsllvd_NameIndex = 7687,
  kX86InstIdVpsllvq_NameIndex = 7695,
  kX86InstIdVpsllw_NameIndex = 7703,
  kX86InstIdVpsrad_NameIndex = 7710,
  kX86InstIdVpsravd_NameIndex = 7717,
  kX86InstIdVpsraw_NameIndex = 7725,
  kX86InstIdVpsrld_NameIndex = 7732,
  kX86InstIdVpsrldq_NameIndex = 7739,
  kX86InstIdVpsrlq_NameIndex = 7747,
  kX86InstIdVpsrlvd_NameIndex = 7754,
  kX86InstIdVpsrlvq_NameIndex = 7762,
  kX86InstIdVpsrlw_NameIndex = 7770,
  kX86InstIdVpsubb_NameIndex = 7777,
  kX86InstIdVpsubd_NameIndex = 7784,
  kX86InstIdVpsubq_NameIndex = 7791,
  kX86InstIdVpsubsb_NameIndex = 7798,
  kX86InstIdVpsubsw_NameIndex = 7806,
  kX86InstIdVpsubusb_NameIndex = 7814,
  kX86InstIdVpsubusw_NameIndex = 7823,
  kX86InstIdVpsubw_NameIndex = 7832,
  kX86InstIdVptest_NameIndex = 7839,
  kX86InstIdVpunpckhbw_NameIndex = 7846,
  kX86InstIdVpunpckhdq_NameIndex = 7857,
  kX86InstIdVpunpckhqdq_NameIndex = 7868,
  kX86InstIdVpunpckhwd_NameIndex = 7880,
  kX86InstIdVpunpcklbw_NameIndex = 7891,
  kX86InstIdVpunpckldq_NameIndex = 7902,
  kX86InstIdVpunpcklqdq_NameIndex = 7913,
  kX86InstIdVpunpcklwd_NameIndex = 7925,
  kX86InstIdVpxor_NameIndex = 7936,
  kX86InstIdVrcpps_NameIndex = 7942,
  kX86InstIdVrcpss_NameIndex = 7949,
  kX86InstIdVroundpd_NameIndex = 7956,
  kX86InstIdVroundps_NameIndex = 7965,
  kX86InstIdVroundsd_NameIndex = 7974,
  kX86InstIdVroundss_NameIndex = 7983,
  kX86InstIdVrsqrtps_NameIndex = 7992,
  kX86InstIdVrsqrtss_NameIndex = 8001,
  kX86InstIdVshufpd_NameIndex = 8010,
  kX86InstIdVshufps_NameIndex = 8018,
  kX86InstIdVsqrtpd_NameIndex = 8026,
  kX86InstIdVsqrtps_NameIndex = 8034,
  kX86InstIdVsqrtsd_NameIndex = 8042,
  kX86InstIdVsqrtss_NameIndex = 8050,
  kX86InstIdVstmxcsr_NameIndex = 8058,
  kX86InstIdVsubpd_NameIndex = 8067,
  kX86InstIdVsubps_NameIndex = 8074,
  kX86InstIdVsubsd_NameIndex = 8081,
  kX86InstIdVsubss_NameIndex = 8088,
  kX86InstIdVtestpd_NameIndex = 8095,
  kX86InstIdVtestps_NameIndex = 8103,
  kX86InstIdVucomisd_NameIndex = 8111,
  kX86InstIdVucomiss_NameIndex = 8120,
  kX86InstIdVunpckhpd_NameIndex = 8129,
  kX86InstIdVunpckhps_NameIndex = 8139,
  kX86InstIdVunpcklpd_NameIndex = 8149,
  kX86InstIdVunpcklps_NameIndex = 8159,
  kX86InstIdVxorpd_NameIndex = 8169,
  kX86InstIdVxorps_NameIndex = 8176,
  kX86InstIdVzeroall_NameIndex = 8183,
  kX86InstIdVzeroupper_NameIndex = 8192,
  kX86InstIdWrfsbase_NameIndex = 8203,
  kX86InstIdWrgsbase_NameIndex = 8212,
  kX86InstIdXadd_NameIndex = 8221,
  kX86InstIdXchg_NameIndex = 8226,
  kX86InstIdXor_NameIndex = 8231,
  kX86InstIdXorpd_NameIndex = 8235,
  kX86InstIdXorps_NameIndex = 8241
};
#endif // !ASMJIT_DISABLE_INST_NAMES

// Automatically generated, do not edit.
const X86InstExtendedInfo _x86InstExtendedInfo[] = {
  { G(None)          , 0 , F(None)                , { 0                   , 0                   , 0                   , 0                   }, 0                },
  { G(X86Arith)      , 0 , F(Lock)                , { O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   }, U                },
  { G(ExtRm)         , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(ExtRmi)        , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   }, U                },
  { G(AvxRvm)        , 0 , F(None)                , { O(Gqd)              , O(Gqd)              , O(GqdMem)           , U                   }, U                },
  { G(AvxRmv)        , 0 , F(None)                , { O(Gqd)              , O(GqdMem)           , O(Gqd)              , U                   }, U                },
  { G(ExtRm)         , 0 , F(None)|F(Special)     , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(AvxVm)         , 0 , F(None)                , { O(Gqd)              , O(GqdMem)           , U                   , U                   }, U                },
  { G(X86RegRm)      , 0 , F(None)                , { O(Gqdw)             , O(GqdwMem)          , U                   , U                   }, U                },
  { G(X86BSwap)      , 0 , F(None)                , { O(Gqd)              , U                   , U                   , U                   }, U                },
  { G(X86BTest)      , 0 , F(Test)                , { O(GqdwMem)          , O(Gqdw)|O(Imm)      , U                   , U                   }, O_000F00(BA,4)   },
  { G(X86BTest)      , 0 , F(Lock)                , { O(GqdwMem)          , O(Gqdw)|O(Imm)      , U                   , U                   }, O_000F00(BA,7)   },
  { G(X86BTest)      , 0 , F(Lock)                , { O(GqdwMem)          , O(Gqdw)|O(Imm)      , U                   , U                   }, O_000F00(BA,6)   },
  { G(X86BTest)      , 0 , F(Lock)                , { O(GqdwMem)          , O(Gqdw)|O(Imm)      , U                   , U                   }, O_000F00(BA,5)   },
  { G(X86Call)       , 0 , F(Flow)                , { O(GqdMem)|O(Imm)|O(Label), U              , U                   , U                   }, O_000000(E8,U)   },
  { G(X86Op)         , 0 , F(None)|F(Special)     , { U                   , U                   , U                   , U                   }, U                },
  { G(X86Op)         , 0 , F(None)|F(Special)|F(W), { U                   , U                   , U                   , U                   }, U                },
  { G(X86Op)         , 0 , F(None)                , { U                   , U                   , U                   , U                   }, U                },
  { G(X86M)          , 0 , F(None)                , { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(X86Arith)      , 0 , F(Test)                , { O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   }, U                },
  { G(Cmpsd)         , 0 , F(None)|F(Special)     , { O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   }, U                },
  { G(X86Op_66H)     , 0 , F(None)|F(Special)     , { U                   , U                   , U                   , U                   }, U                },
  { G(X86RmReg)      , 0 , F(Lock)|F(Special)     , { U                   , U                   , U                   , U                   }, U                },
  { G(X86M)          , 0 , F(None)|F(Special)|F(W), { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(X86M)          , 0 , F(None)|F(Special)     , { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(ExtRm)         , 0 , F(Test)                , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(ExtCrc)        , 0 , F(None)                , { O(Gqd)              , O(GqdwbMem)         , U                   , U                   }, U                },
  { G(ExtRm)         , 16, F(Move)                , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(ExtRm)         , 8 , F(Move)                , { O(Mm)               , O(XmmMem)           , U                   , U                   }, U                },
  { G(ExtRm)         , 16, F(Move)                , { O(Xmm)              , O(MmMem)            , U                   , U                   }, U                },
  { G(ExtRm)         , 8 , F(Move)                , { O(Xmm)              , O(MmMem)            , U                   , U                   }, U                },
  { G(ExtRm_Q)       , 8 , F(Move)                , { O(Gqd)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(ExtRm)         , 4 , F(Move)                , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(ExtRm_Q)       , 8 , F(Move)                , { O(Xmm)              , O(GqdMem)           , U                   , U                   }, U                },
  { G(ExtRm_Q)       , 4 , F(Move)                , { O(Xmm)              , O(GqdMem)           , U                   , U                   }, U                },
  { G(ExtRm)         , 8 , F(Move)                , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(X86IncDec)     , 0 , F(Lock)                , { O(GqdwbMem)         , U                   , U                   , U                   }, O_000000(48,U)   },
  { G(X86Rm_B)       , 0 , F(None)|F(Special)     , { U                   , U                   , U                   , U                   }, U                },
  { G(X86Enter)      , 0 , F(None)|F(Special)     , { U                   , U                   , U                   , U                   }, U                },
  { G(ExtExtract)    , 8 , F(Move)                , { O(GqdMem)           , O(Xmm)              , U                   , U                   }, O_660F3A(17,U)   },
  { G(FpuOp)         , 0 , F(Fp)                  , { U                   , U                   , U                   , U                   }, U                },
  { G(FpuArith)      , 0 , F(Fp)|F(Mem4_8)        , { O(FpMem)            , O(Fp)               , U                   , U                   }, U                },
  { G(FpuRDef)       , 0 , F(Fp)                  , { O(Fp)               , U                   , U                   , U                   }, U                },
  { G(X86M)          , 0 , F(Fp)                  , { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(FpuR)          , 0 , F(Fp)                  , { O(Fp)               , U                   , U                   , U                   }, U                },
  { G(FpuCom)        , 0 , F(Fp)                  , { O(Fp)|O(Mem)        , O(Fp)               , U                   , U                   }, U                },
  { G(X86Op)         , 0 , F(Fp)                  , { U                   , U                   , U                   , U                   }, U                },
  { G(FpuM)          , 0 , F(Fp)|F(Mem2_4)        , { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(FpuM)          , 0 , F(Fp)|F(Mem2_4_8)      , { O(Mem)              , U                   , U                   , U                   }, O_000000(DF,5)   },
  { G(FpuM)          , 0 , F(Fp)|F(Mem2_4_8)      , { O(Mem)              , U                   , U                   , U                   }, O_000000(DF,7)   },
  { G(FpuM)          , 0 , F(Fp)|F(Mem2_4_8)      , { O(Mem)              , U                   , U                   , U                   }, O_000000(DD,1)   },
  { G(FpuFldFst)     , 0 , F(Fp)|F(Mem4_8_10)     , { O(Mem)              , U                   , U                   , U                   }, O_000000(DB,5)   },
  { G(FpuStsw)       , 0 , F(Fp)                  , { O(Mem)              , U                   , U                   , U                   }, O_00_X(DFE0,U)   },
  { G(FpuFldFst)     , 0 , F(Fp)|F(Mem4_8)        , { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(FpuFldFst)     , 0 , F(Fp)|F(Mem4_8_10)     , { O(Mem)              , U                   , U                   , U                   }, O_000000(DB,7)   },
  { G(FpuStsw)       , 0 , F(Fp)                  , { O(Mem)              , U                   , U                   , U                   }, O_9B_X(DFE0,U)   },
  { G(X86Rm_B)       , 0 , F(None)|F(Special)     , { 0                   , 0                   , U                   , U                   }, U                },
  { G(X86Imul)       , 0 , F(None)|F(Special)     , { 0                   , 0                   , U                   , U                   }, U                },
  { G(X86IncDec)     , 0 , F(Lock)                , { O(GqdwbMem)         , U                   , U                   , U                   }, O_000000(40,U)   },
  { G(X86Int)        , 0 , F(None)                , { U                   , U                   , U                   , U                   }, U                },
  { G(X86Jcc)        , 0 , F(Flow)                , { O(Label)            , U                   , U                   , U                   }, U                },
  { G(X86Jecxz)      , 0 , F(Flow)|F(Special)     , { O(Gqdw)             , O(Label)            , U                   , U                   }, U                },
  { G(X86Jmp)        , 0 , F(Flow)                , { O(Imm)|O(Label)     , U                   , U                   , U                   }, O_000000(E9,U)   },
  { G(ExtRm)         , 16, F(Move)                , { O(Xmm)              , O(Mem)              , U                   , U                   }, U                },
  { G(X86Lea)        , 0 , F(Move)                , { O(Gqd)              , O(Mem)              , U                   , U                   }, U                },
  { G(ExtFence)      , 0 , F(None)                , { U                   , U                   , U                   , U                   }, U                },
  { G(ExtRm)         , 0 , F(None)|F(Special)     , { O(Xmm)              , O(Xmm)              , U                   , U                   }, U                },
  { G(ExtRm)         , 0 , F(None)|F(Special)     , { O(Mm)               , O(Mm)               , U                   , U                   }, U                },
  { G(X86Mov)        , 0 , F(Move)                , { O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   }, U                },
  { G(X86MovPtr)     , 0 , F(Move)|F(Special)     , { O(Gqdwb)            , O(Imm)              , U                   , U                   }, O_000000(A2,U)   },
  { G(ExtMov)        , 16, F(Move)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_660F00(29,U)   },
  { G(ExtMov)        , 16, F(Move)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_000F00(29,U)   },
  { G(ExtMovBe)      , 0 , F(Move)                , { O(GqdwMem)          , O(GqdwMem)          , U                   , U                   }, O_000F38(F1,U)   },
  { G(ExtMovD)       , 16, F(Move)                , { O(Gd)|O(MmXmmMem)   , O(Gd)|O(MmXmmMem)   , U                   , U                   }, O_000F00(7E,U)   },
  { G(ExtMov)        , 16, F(Move)                , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(ExtMov)        , 8 , F(Move)                , { O(Mm)               , O(Xmm)              , U                   , U                   }, U                },
  { G(ExtMov)        , 16, F(Move)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_660F00(7F,U)   },
  { G(ExtMov)        , 16, F(Move)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_F30F00(7F,U)   },
  { G(ExtMov)        , 8 , F(Move)                , { O(Xmm)              , O(Xmm)              , U                   , U                   }, U                },
  { G(ExtMov)        , 0 , F(None)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_660F00(17,U)   },
  { G(ExtMov)        , 0 , F(None)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_000F00(17,U)   },
  { G(ExtMov)        , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , U                   , U                   }, U                },
  { G(ExtMov)        , 8 , F(Move)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_660F00(13,U)   },
  { G(ExtMov)        , 8 , F(Move)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_000F00(13,U)   },
  { G(ExtMovNoRexW)  , 8 , F(Move)                , { O(Gqd)              , O(Xmm)              , U                   , U                   }, U                },
  { G(ExtMov)        , 16, F(Move)                , { O(Mem)              , O(Xmm)              , U                   , U                   }, O_660F00(E7,U)   },
  { G(ExtMov)        , 16, F(Move)                , { O(Xmm)              , O(Mem)              , U                   , U                   }, U                },
  { G(ExtMov)        , 8 , F(Move)                , { O(Mem)              , O(Gqd)              , U                   , U                   }, O_000F00(C3,U)   },
  { G(ExtMov)        , 16, F(Move)                , { O(Mem)              , O(Xmm)              , U                   , U                   }, O_660F00(2B,U)   },
  { G(ExtMov)        , 16, F(Move)                , { O(Mem)              , O(Xmm)              , U                   , U                   }, O_000F00(2B,U)   },
  { G(ExtMov)        , 8 , F(Move)                , { O(Mem)              , O(Mm)               , U                   , U                   }, O_000F00(E7,U)   },
  { G(ExtMovQ)       , 16, F(Move)                , { O(Gq)|O(MmXmmMem)   , O(Gq)|O(MmXmmMem)   , U                   , U                   }, U                },
  { G(ExtRm)         , 16, F(Move)                , { O(Xmm)              , O(Mm)               , U                   , U                   }, U                },
  { G(Movsd)         , 8 , F(Move)|F(Special)|F(Z), { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_F20F00(11,U)   },
  { G(ExtMov)        , 4 , F(Move)           |F(Z), { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_F30F00(11,U)   },
  { G(X86MovSxZx)    , 0 , F(Move)                , { O(Gqdw)             , O(GwbMem)           , U                   , U                   }, U                },
  { G(X86MovSxd)     , 0 , F(Move)                , { O(Gq)               , O(GdMem)            , U                   , U                   }, U                },
  { G(ExtMov)        , 16, F(Move)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_660F00(11,U)   },
  { G(ExtMov)        , 16, F(Move)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_000F00(11,U)   },
  { G(X86Rm_B)       , 0 , F(Lock)                , { O(GqdwbMem)         , U                   , U                   , U                   }, U                },
  { G(ExtRm_P)       , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)         , U                   , U                   }, U                },
  { G(ExtRmi_P)      , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)         , O(Imm)              , U                   }, U                },
  { G(ExtExtract)    , 8 , F(Move)                , { O(Gd)|O(Gb)|O(Mem)  , O(Xmm)              , U                   , U                   }, O_000F3A(14,U)   },
  { G(ExtExtract)    , 8 , F(Move)                , { O(GdMem)            , O(Xmm)              , U                   , U                   }, O_000F3A(16,U)   },
  { G(ExtExtract)    , 8 , F(Move)           |F(W), { O(GqdMem)           , O(Xmm)              , U                   , U                   }, O_000F3A(16,U)   },
  { G(ExtExtract)    , 8 , F(Move)                , { O(GdMem)            , O(MmXmm)            , U                   , U                   }, O_000F3A(15,U)   },
  { G(3dNow)         , 0 , F(None)                , { O(Mm)               , O(MmMem)            , U                   , U                   }, U                },
  { G(ExtRmi)        , 0 , F(None)                , { O(Xmm)              , O(GdMem)            , O(Imm)              , U                   }, U                },
  { G(ExtRmi)        , 0 , F(None)           |F(W), { O(Xmm)              , O(GqMem)            , O(Imm)              , U                   }, U                },
  { G(ExtRmi_P)      , 0 , F(None)                , { O(MmXmm)            , O(GdMem)            , O(Imm)              , U                   }, U                },
  { G(ExtRm_PQ)      , 8 , F(Move)                , { O(Gqd)              , O(MmXmm)            , U                   , U                   }, U                },
  { G(X86Pop)        , 0 , F(None)|F(Special)     , { 0                   , U                   , U                   , U                   }, O_000000(58,U)   },
  { G(ExtPrefetch)   , 0 , F(None)                , { O(Mem)              , O(Imm)              , U                   , U                   }, U                },
  { G(ExtRmi)        , 16, F(Move)                , { O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   }, U                },
  { G(ExtRmi_P)      , 8 , F(Move)                , { O(Mm)               , O(MmMem)            , O(Imm)              , U                   }, U                },
  { G(ExtRmRi_P)     , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   }, O_000F00(72,6)   },
  { G(ExtRmRi)       , 0 , F(None)                , { O(Xmm)              , O(Imm)              , U                   , U                   }, O_660F00(73,7)   },
  { G(ExtRmRi_P)     , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   }, O_000F00(73,6)   },
  { G(ExtRmRi_P)     , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   }, O_000F00(71,6)   },
  { G(ExtRmRi_P)     , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   }, O_000F00(72,4)   },
  { G(ExtRmRi_P)     , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   }, O_000F00(71,4)   },
  { G(ExtRmRi_P)     , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   }, O_000F00(72,2)   },
  { G(ExtRmRi)       , 0 , F(None)                , { O(Xmm)              , O(Imm)              , U                   , U                   }, O_660F00(73,3)   },
  { G(ExtRmRi_P)     , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   }, O_000F00(73,2)   },
  { G(ExtRmRi_P)     , 0 , F(None)                , { O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   }, O_000F00(71,2)   },
  { G(X86Push)       , 0 , F(None)|F(Special)     , { 0                   , U                   , U                   , U                   }, O_000000(50,U)   },
  { G(X86Rot)        , 0 , F(None)|F(Special)     , { O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   }, U                },
  { G(X86Rm)         , 8 , F(Move)                , { O(Gqd)              , U                   , U                   , U                   }, U                },
  { G(X86Rm)         , 8 , F(Move)                , { O(Gqdw)             , U                   , U                   , U                   }, U                },
  { G(X86Rep)        , 0 , F(None)|F(Special)     , { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(X86Rep)        , 0 , F(None)|F(Special)|F(W), { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(X86Rep)        , 0 , F(None)|F(Special)     , { O(Mem)              , O(Mem)              , U                   , U                   }, U                },
  { G(X86Rep)        , 0 , F(None)|F(Special)|F(W), { O(Mem)              , O(Mem)              , U                   , U                   }, U                },
  { G(X86Ret)        , 0 , F(None)|F(Special)     , { U                   , U                   , U                   , U                   }, U                },
  { G(AvxRmi)        , 0 , F(None)                , { O(Gqd)              , O(GqdMem)           , O(Imm)              , U                   }, U                },
  { G(ExtRmi)        , 8 , F(Move)                , { O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   }, U                },
  { G(ExtRmi)        , 4 , F(Move)                , { O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   }, U                },
  { G(X86Set)        , 1 , F(Move)                , { O(GbMem)            , U                   , U                   , U                   }, U                },
  { G(X86Shlrd)      , 0 , F(None)|F(Special)     , { O(GqdwbMem)         , O(Gb)               , U                   , U                   }, U                },
  { G(X86Shlrd)      , 0 , F(None)|F(Special)     , { O(GqdwbMem)         , O(Gqdwb)            , U                   , U                   }, U                },
  { G(X86Test)       , 0 , F(Test)                , { O(GqdwbMem)         , O(Gqdwb)|O(Imm)     , U                   , U                   }, O_000000(F6,U)   },
  { G(X86RegRm)      , 0 , F(Move)                , { O(Gqdw)             , O(GqdwMem)          , U                   , U                   }, U                },
  { G(AvxRvm_P)      , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   }, U                },
  { G(AvxRvm)        , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   }, U                },
  { G(AvxRm)         , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(AvxRmi)        , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   }, U                },
  { G(AvxRvmi_P)     , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              }, U                },
  { G(AvxRvmr_P)     , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmm)           }, U                },
  { G(AvxRm)         , 0 , F(None)                , { O(Ymm)              , O(Mem)              , U                   , U                   }, U                },
  { G(AvxRm)         , 0 , F(None)                , { O(Ymm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(AvxRvmi)       , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              }, U                },
  { G(AvxRm_P)       , 0 , F(None)                , { O(XmmYmm)           , O(XmmMem)           , U                   , U                   }, U                },
  { G(AvxRm_P)       , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   }, U                },
  { G(AvxRm)         , 0 , F(None)                , { O(Xmm)              , O(XmmYmmMem)        , U                   , U                   }, U                },
  { G(AvxMri_P)      , 0 , F(None)                , { O(XmmMem)           , O(XmmYmm)           , O(Imm)              , U                   }, U                },
  { G(AvxRm)         , 0 , F(None)                , { O(Gqd)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(AvxRvm)        , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(GqdMem)           , U                   }, U                },
  { G(AvxRm_P)       , 0 , F(None)                , { O(Xmm)              , O(XmmYmmMem)        , U                   , U                   }, U                },
  { G(AvxMri)        , 0 , F(None)                , { O(XmmMem)           , O(Ymm)              , O(Imm)              , U                   }, U                },
  { G(AvxMri)        , 0 , F(None)                , { O(GqdMem)           , O(Xmm)              , O(Imm)              , U                   }, U                },
  { G(AvxRvm_P)      , 0 , F(None)           |F(W), { O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   }, U                },
  { G(AvxRvm)        , 0 , F(None)           |F(W), { O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   }, U                },
  { G(Fma4_P)        , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        }, U                },
  { G(Fma4)          , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           }, U                },
  { G(XopRm_P)       , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   }, U                },
  { G(XopRm)         , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , U                   , U                   }, U                },
  { G(AvxGather)     , 0 , F(None)           |F(W), { O(XmmYmm)           , O(Mem)              , O(XmmYmm)           , U                   }, U                },
  { G(AvxGather)     , 0 , F(None)                , { O(XmmYmm)           , O(Mem)              , O(XmmYmm)           , U                   }, U                },
  { G(AvxGatherEx)   , 0 , F(None)                , { O(Xmm)              , O(Mem)              , O(Xmm)              , U                   }, U                },
  { G(AvxRvmi)       , 0 , F(None)                , { O(Ymm)              , O(Ymm)              , O(XmmMem)           , O(Imm)              }, U                },
  { G(AvxRm_P)       , 0 , F(None)                , { O(XmmYmm)           , O(Mem)              , U                   , U                   }, U                },
  { G(AvxM)          , 0 , F(None)                , { O(Mem)              , U                   , U                   , U                   }, U                },
  { G(AvxRm)         , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , U                   , U                   }, U                },
  { G(AvxRvmMvr_P)   , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmm)           , O(XmmYmmMem)        , U                   }, O_660F38(2F,U)   },
  { G(AvxRvmMvr_P)   , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmm)           , O(XmmYmmMem)        , U                   }, O_660F38(2E,U)   },
  { G(AvxRmMr_P)     , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   }, O_660F00(29,U)   },
  { G(AvxRmMr_P)     , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   }, O_000F00(29,U)   },
  { G(AvxRmMr)       , 0 , F(None)                , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_660F00(7E,U)   },
  { G(AvxRmMr_P)     , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   }, O_660F00(7F,U)   },
  { G(AvxRmMr_P)     , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   }, O_F30F00(7F,U)   },
  { G(AvxRvm)        , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(Xmm)              , U                   }, U                },
  { G(AvxRvmMr)      , 0 , F(None)                , { O(XmmMem)           , O(Xmm)              , O(Mem)              , U                   }, O_660F00(17,U)   },
  { G(AvxRvmMr)      , 0 , F(None)                , { O(XmmMem)           , O(Xmm)              , O(Mem)              , U                   }, O_000F00(17,U)   },
  { G(AvxRvmMr)      , 0 , F(None)                , { O(XmmMem)           , O(Xmm)              , O(Mem)              , U                   }, O_660F00(13,U)   },
  { G(AvxRvmMr)      , 0 , F(None)                , { O(XmmMem)           , O(Xmm)              , O(Mem)              , U                   }, O_000F00(13,U)   },
  { G(AvxRm_P)       , 0 , F(None)                , { O(Gqd)              , O(XmmYmm)           , U                   , U                   }, U                },
  { G(AvxMr)         , 0 , F(None)                , { O(Mem)              , O(XmmYmm)           , U                   , U                   }, U                },
  { G(AvxMr_P)       , 0 , F(None)                , { O(Mem)              , O(XmmYmm)           , U                   , U                   }, U                },
  { G(AvxRmMr)       , 0 , F(None)           |F(W), { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_660F00(7E,U)   },
  { G(AvxMovSsSd)    , 0 , F(None)                , { O(XmmMem)           , O(XmmMem)           , O(Xmm)              , U                   }, O_F20F00(11,U)   },
  { G(AvxMovSsSd)    , 0 , F(None)                , { O(XmmMem)           , O(Xmm)              , O(Xmm)              , U                   }, O_F30F00(11,U)   },
  { G(AvxRmMr_P)     , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   }, O_660F00(11,U)   },
  { G(AvxRmMr_P)     , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   }, O_000F00(11,U)   },
  { G(AvxRvmr)       , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmm)           }, U                },
  { G(XopRvrmRvmr_P) , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        }, U                },
  { G(XopRvmi)       , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              }, U                },
  { G(AvxRvmi)       , 0 , F(None)                , { O(Ymm)              , O(Ymm)              , O(YmmMem)           , O(Imm)              }, U                },
  { G(AvxRvm)        , 0 , F(None)                , { O(Ymm)              , O(Ymm)              , O(YmmMem)           , U                   }, U                },
  { G(AvxRvrmRvmr_P) , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        }, U                },
  { G(AvxRvmRmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F3A(05,U)   },
  { G(AvxRvmRmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F3A(04,U)   },
  { G(AvxRmi)        , 0 , F(None)           |F(W), { O(Ymm)              , O(YmmMem)           , O(Imm)              , U                   }, U                },
  { G(AvxMri)        , 0 , F(None)                , { O(GqdwbMem)         , O(Xmm)              , O(Imm)              , U                   }, U                },
  { G(AvxMri)        , 0 , F(None)           |F(W), { O(GqMem)            , O(Xmm)              , O(Imm)              , U                   }, U                },
  { G(AvxMri)        , 0 , F(None)                , { O(GqdwMem)          , O(Xmm)              , O(Imm)              , U                   }, U                },
  { G(AvxRvmi)       , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(GqdwbMem)         , O(Imm)              }, U                },
  { G(AvxRvmi)       , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(GqdMem)           , O(Imm)              }, U                },
  { G(AvxRvmi)       , 0 , F(None)           |F(W), { O(Xmm)              , O(Xmm)              , O(GqMem)            , O(Imm)              }, U                },
  { G(AvxRvmi)       , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(GqdwMem)          , O(Imm)              }, U                },
  { G(XopRvmr)       , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              }, U                },
  { G(AvxRvmMvr_P)   , 0 , F(None)                , { O(XmmYmmMem)        , O(XmmYmm)           , O(XmmYmmMem)        , U                   }, O_660F38(8E,U)   },
  { G(AvxRvmMvr_P)   , 0 , F(None)           |F(W), { O(XmmYmmMem)        , O(XmmYmm)           , O(XmmYmmMem)        , U                   }, O_660F38(8E,U)   },
  { G(XopRvrmRvmr)   , 0 , F(None)                , { O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           }, U                },
  { G(XopRvmRmi)     , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , O(XmmMem)|O(Imm)    , U                   }, O_00_M08(C0,U)   },
  { G(XopRvmRmi)     , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , O(XmmMem)|O(Imm)    , U                   }, O_00_M08(C2,U)   },
  { G(XopRvmRmi)     , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , O(XmmMem)|O(Imm)    , U                   }, O_00_M08(C3,U)   },
  { G(XopRvmRmi)     , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , O(XmmMem)|O(Imm)    , U                   }, O_00_M08(C1,U)   },
  { G(XopRvmRmv)     , 0 , F(None)                , { O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   }, U                },
  { G(AvxRmi_P)      , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   }, U                },
  { G(AvxRvmVmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F00(72,6)   },
  { G(AvxVmi_P)      , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   }, U                },
  { G(AvxRvmVmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F00(73,6)   },
  { G(AvxRvmVmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F00(71,6)   },
  { G(AvxRvmVmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F00(72,4)   },
  { G(AvxRvmVmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F00(71,4)   },
  { G(AvxRvmVmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F00(72,2)   },
  { G(AvxRvmVmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F00(73,2)   },
  { G(AvxRvmVmi_P)   , 0 , F(None)                , { O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   }, O_660F00(71,2)   },
  { G(AvxRm_P)       , 0 , F(Test)                , { O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   }, U                },
  { G(AvxOp)         , 0 , F(None)                , { U                   , U                   , U                   , U                   }, U                },
  { G(X86Rm)         , 0 , F(None)                , { O(Gqd)              , U                   , U                   , U                   }, U                },
  { G(X86Xadd)       , 0 , F(Xchg)|F(Lock)        , { O(GqdwbMem)         , O(Gqdwb)            , U                   , U                   }, U                },
  { G(X86Xchg)       , 0 , F(Xchg)|F(Lock)        , { O(GqdwbMem)         , O(Gqdwb)            , U                   , U                   }, U                }
};

// Automatically generated, do not edit.
enum kX86InstData_ExtendedIndex {
  kInstIdNone_ExtendedIndex = 0,
  kX86InstIdAdc_ExtendedIndex = 1,
  kX86InstIdAdd_ExtendedIndex = 1,
  kX86InstIdAddpd_ExtendedIndex = 2,
  kX86InstIdAddps_ExtendedIndex = 2,
  kX86InstIdAddsd_ExtendedIndex = 2,
  kX86InstIdAddss_ExtendedIndex = 2,
  kX86InstIdAddsubpd_ExtendedIndex = 2,
  kX86InstIdAddsubps_ExtendedIndex = 2,
  kX86InstIdAesdec_ExtendedIndex = 2,
  kX86InstIdAesdeclast_ExtendedIndex = 2,
  kX86InstIdAesenc_ExtendedIndex = 2,
  kX86InstIdAesenclast_ExtendedIndex = 2,
  kX86InstIdAesimc_ExtendedIndex = 2,
  kX86InstIdAeskeygenassist_ExtendedIndex = 3,
  kX86InstIdAnd_ExtendedIndex = 1,
  kX86InstIdAndn_ExtendedIndex = 4,
  kX86InstIdAndnpd_ExtendedIndex = 2,
  kX86InstIdAndnps_ExtendedIndex = 2,
  kX86InstIdAndpd_ExtendedIndex = 2,
  kX86InstIdAndps_ExtendedIndex = 2,
  kX86InstIdBextr_ExtendedIndex = 5,
  kX86InstIdBlendpd_ExtendedIndex = 3,
  kX86InstIdBlendps_ExtendedIndex = 3,
  kX86InstIdBlendvpd_ExtendedIndex = 6,
  kX86InstIdBlendvps_ExtendedIndex = 6,
  kX86InstIdBlsi_ExtendedIndex = 7,
  kX86InstIdBlsmsk_ExtendedIndex = 7,
  kX86InstIdBlsr_ExtendedIndex = 7,
  kX86InstIdBsf_ExtendedIndex = 8,
  kX86InstIdBsr_ExtendedIndex = 8,
  kX86InstIdBswap_ExtendedIndex = 9,
  kX86InstIdBt_ExtendedIndex = 10,
  kX86InstIdBtc_ExtendedIndex = 11,
  kX86InstIdBtr_ExtendedIndex = 12,
  kX86InstIdBts_ExtendedIndex = 13,
  kX86InstIdBzhi_ExtendedIndex = 5,
  kX86InstIdCall_ExtendedIndex = 14,
  kX86InstIdCbw_ExtendedIndex = 15,
  kX86InstIdCdq_ExtendedIndex = 15,
  kX86InstIdCdqe_ExtendedIndex = 16,
  kX86InstIdClc_ExtendedIndex = 17,
  kX86InstIdCld_ExtendedIndex = 17,
  kX86InstIdClflush_ExtendedIndex = 18,
  kX86InstIdCmc_ExtendedIndex = 17,
  kX86InstIdCmova_ExtendedIndex = 8,
  kX86InstIdCmovae_ExtendedIndex = 8,
  kX86InstIdCmovb_ExtendedIndex = 8,
  kX86InstIdCmovbe_ExtendedIndex = 8,
  kX86InstIdCmovc_ExtendedIndex = 8,
  kX86InstIdCmove_ExtendedIndex = 8,
  kX86InstIdCmovg_ExtendedIndex = 8,
  kX86InstIdCmovge_ExtendedIndex = 8,
  kX86InstIdCmovl_ExtendedIndex = 8,
  kX86InstIdCmovle_ExtendedIndex = 8,
  kX86InstIdCmovna_ExtendedIndex = 8,
  kX86InstIdCmovnae_ExtendedIndex = 8,
  kX86InstIdCmovnb_ExtendedIndex = 8,
  kX86InstIdCmovnbe_ExtendedIndex = 8,
  kX86InstIdCmovnc_ExtendedIndex = 8,
  kX86InstIdCmovne_ExtendedIndex = 8,
  kX86InstIdCmovng_ExtendedIndex = 8,
  kX86InstIdCmovnge_ExtendedIndex = 8,
  kX86InstIdCmovnl_ExtendedIndex = 8,
  kX86InstIdCmovnle_ExtendedIndex = 8,
  kX86InstIdCmovno_ExtendedIndex = 8,
  kX86InstIdCmovnp_ExtendedIndex = 8,
  kX86InstIdCmovns_ExtendedIndex = 8,
  kX86InstIdCmovnz_ExtendedIndex = 8,
  kX86InstIdCmovo_ExtendedIndex = 8,
  kX86InstIdCmovp_ExtendedIndex = 8,
  kX86InstIdCmovpe_ExtendedIndex = 8,
  kX86InstIdCmovpo_ExtendedIndex = 8,
  kX86InstIdCmovs_ExtendedIndex = 8,
  kX86InstIdCmovz_ExtendedIndex = 8,
  kX86InstIdCmp_ExtendedIndex = 19,
  kX86InstIdCmppd_ExtendedIndex = 3,
  kX86InstIdCmpps_ExtendedIndex = 3,
  kX86InstIdCmpsb_ExtendedIndex = 15,
  kX86InstIdCmpsd_ExtendedIndex = 20,
  kX86InstIdCmpsq_ExtendedIndex = 16,
  kX86InstIdCmpss_ExtendedIndex = 3,
  kX86InstIdCmpsw_ExtendedIndex = 21,
  kX86InstIdCmpxchg_ExtendedIndex = 22,
  kX86InstIdCmpxchg16b_ExtendedIndex = 23,
  kX86InstIdCmpxchg8b_ExtendedIndex = 24,
  kX86InstIdComisd_ExtendedIndex = 25,
  kX86InstIdComiss_ExtendedIndex = 25,
  kX86InstIdCpuid_ExtendedIndex = 15,
  kX86InstIdCqo_ExtendedIndex = 16,
  kX86InstIdCrc32_ExtendedIndex = 26,
  kX86InstIdCvtdq2pd_ExtendedIndex = 27,
  kX86InstIdCvtdq2ps_ExtendedIndex = 27,
  kX86InstIdCvtpd2dq_ExtendedIndex = 27,
  kX86InstIdCvtpd2pi_ExtendedIndex = 28,
  kX86InstIdCvtpd2ps_ExtendedIndex = 27,
  kX86InstIdCvtpi2pd_ExtendedIndex = 29,
  kX86InstIdCvtpi2ps_ExtendedIndex = 30,
  kX86InstIdCvtps2dq_ExtendedIndex = 27,
  kX86InstIdCvtps2pd_ExtendedIndex = 27,
  kX86InstIdCvtps2pi_ExtendedIndex = 28,
  kX86InstIdCvtsd2si_ExtendedIndex = 31,
  kX86InstIdCvtsd2ss_ExtendedIndex = 32,
  kX86InstIdCvtsi2sd_ExtendedIndex = 33,
  kX86InstIdCvtsi2ss_ExtendedIndex = 34,
  kX86InstIdCvtss2sd_ExtendedIndex = 35,
  kX86InstIdCvtss2si_ExtendedIndex = 31,
  kX86InstIdCvttpd2dq_ExtendedIndex = 27,
  kX86InstIdCvttpd2pi_ExtendedIndex = 28,
  kX86InstIdCvttps2dq_ExtendedIndex = 27,
  kX86InstIdCvttps2pi_ExtendedIndex = 28,
  kX86InstIdCvttsd2si_ExtendedIndex = 31,
  kX86InstIdCvttss2si_ExtendedIndex = 31,
  kX86InstIdCwd_ExtendedIndex = 15,
  kX86InstIdCwde_ExtendedIndex = 15,
  kX86InstIdDaa_ExtendedIndex = 15,
  kX86InstIdDas_ExtendedIndex = 15,
  kX86InstIdDec_ExtendedIndex = 36,
  kX86InstIdDiv_ExtendedIndex = 37,
  kX86InstIdDivpd_ExtendedIndex = 2,
  kX86InstIdDivps_ExtendedIndex = 2,
  kX86InstIdDivsd_ExtendedIndex = 2,
  kX86InstIdDivss_ExtendedIndex = 2,
  kX86InstIdDppd_ExtendedIndex = 3,
  kX86InstIdDpps_ExtendedIndex = 3,
  kX86InstIdEmms_ExtendedIndex = 17,
  kX86InstIdEnter_ExtendedIndex = 38,
  kX86InstIdExtractps_ExtendedIndex = 39,
  kX86InstIdF2xm1_ExtendedIndex = 40,
  kX86InstIdFabs_ExtendedIndex = 40,
  kX86InstIdFadd_ExtendedIndex = 41,
  kX86InstIdFaddp_ExtendedIndex = 42,
  kX86InstIdFbld_ExtendedIndex = 43,
  kX86InstIdFbstp_ExtendedIndex = 43,
  kX86InstIdFchs_ExtendedIndex = 40,
  kX86InstIdFclex_ExtendedIndex = 40,
  kX86InstIdFcmovb_ExtendedIndex = 44,
  kX86InstIdFcmovbe_ExtendedIndex = 44,
  kX86InstIdFcmove_ExtendedIndex = 44,
  kX86InstIdFcmovnb_ExtendedIndex = 44,
  kX86InstIdFcmovnbe_ExtendedIndex = 44,
  kX86InstIdFcmovne_ExtendedIndex = 44,
  kX86InstIdFcmovnu_ExtendedIndex = 44,
  kX86InstIdFcmovu_ExtendedIndex = 44,
  kX86InstIdFcom_ExtendedIndex = 45,
  kX86InstIdFcomi_ExtendedIndex = 44,
  kX86InstIdFcomip_ExtendedIndex = 44,
  kX86InstIdFcomp_ExtendedIndex = 45,
  kX86InstIdFcompp_ExtendedIndex = 40,
  kX86InstIdFcos_ExtendedIndex = 40,
  kX86InstIdFdecstp_ExtendedIndex = 40,
  kX86InstIdFdiv_ExtendedIndex = 41,
  kX86InstIdFdivp_ExtendedIndex = 42,
  kX86InstIdFdivr_ExtendedIndex = 41,
  kX86InstIdFdivrp_ExtendedIndex = 42,
  kX86InstIdFemms_ExtendedIndex = 46,
  kX86InstIdFfree_ExtendedIndex = 44,
  kX86InstIdFiadd_ExtendedIndex = 47,
  kX86InstIdFicom_ExtendedIndex = 47,
  kX86InstIdFicomp_ExtendedIndex = 47,
  kX86InstIdFidiv_ExtendedIndex = 47,
  kX86InstIdFidivr_ExtendedIndex = 47,
  kX86InstIdFild_ExtendedIndex = 48,
  kX86InstIdFimul_ExtendedIndex = 47,
  kX86InstIdFincstp_ExtendedIndex = 40,
  kX86InstIdFinit_ExtendedIndex = 40,
  kX86InstIdFist_ExtendedIndex = 47,
  kX86InstIdFistp_ExtendedIndex = 49,
  kX86InstIdFisttp_ExtendedIndex = 50,
  kX86InstIdFisub_ExtendedIndex = 47,
  kX86InstIdFisubr_ExtendedIndex = 47,
  kX86InstIdFld_ExtendedIndex = 51,
  kX86InstIdFld1_ExtendedIndex = 40,
  kX86InstIdFldcw_ExtendedIndex = 43,
  kX86InstIdFldenv_ExtendedIndex = 43,
  kX86InstIdFldl2e_ExtendedIndex = 40,
  kX86InstIdFldl2t_ExtendedIndex = 40,
  kX86InstIdFldlg2_ExtendedIndex = 40,
  kX86InstIdFldln2_ExtendedIndex = 40,
  kX86InstIdFldpi_ExtendedIndex = 40,
  kX86InstIdFldz_ExtendedIndex = 40,
  kX86InstIdFmul_ExtendedIndex = 41,
  kX86InstIdFmulp_ExtendedIndex = 42,
  kX86InstIdFnclex_ExtendedIndex = 40,
  kX86InstIdFninit_ExtendedIndex = 40,
  kX86InstIdFnop_ExtendedIndex = 40,
  kX86InstIdFnsave_ExtendedIndex = 43,
  kX86InstIdFnstcw_ExtendedIndex = 43,
  kX86InstIdFnstenv_ExtendedIndex = 43,
  kX86InstIdFnstsw_ExtendedIndex = 52,
  kX86InstIdFpatan_ExtendedIndex = 40,
  kX86InstIdFprem_ExtendedIndex = 40,
  kX86InstIdFprem1_ExtendedIndex = 40,
  kX86InstIdFptan_ExtendedIndex = 40,
  kX86InstIdFrndint_ExtendedIndex = 40,
  kX86InstIdFrstor_ExtendedIndex = 43,
  kX86InstIdFsave_ExtendedIndex = 43,
  kX86InstIdFscale_ExtendedIndex = 40,
  kX86InstIdFsin_ExtendedIndex = 40,
  kX86InstIdFsincos_ExtendedIndex = 40,
  kX86InstIdFsqrt_ExtendedIndex = 40,
  kX86InstIdFst_ExtendedIndex = 53,
  kX86InstIdFstcw_ExtendedIndex = 43,
  kX86InstIdFstenv_ExtendedIndex = 43,
  kX86InstIdFstp_ExtendedIndex = 54,
  kX86InstIdFstsw_ExtendedIndex = 55,
  kX86InstIdFsub_ExtendedIndex = 41,
  kX86InstIdFsubp_ExtendedIndex = 42,
  kX86InstIdFsubr_ExtendedIndex = 41,
  kX86InstIdFsubrp_ExtendedIndex = 42,
  kX86InstIdFtst_ExtendedIndex = 40,
  kX86InstIdFucom_ExtendedIndex = 42,
  kX86InstIdFucomi_ExtendedIndex = 44,
  kX86InstIdFucomip_ExtendedIndex = 44,
  kX86InstIdFucomp_ExtendedIndex = 42,
  kX86InstIdFucompp_ExtendedIndex = 40,
  kX86InstIdFwait_ExtendedIndex = 46,
  kX86InstIdFxam_ExtendedIndex = 40,
  kX86InstIdFxch_ExtendedIndex = 44,
  kX86InstIdFxrstor_ExtendedIndex = 43,
  kX86InstIdFxsave_ExtendedIndex = 43,
  kX86InstIdFxtract_ExtendedIndex = 40,
  kX86InstIdFyl2x_ExtendedIndex = 40,
  kX86InstIdFyl2xp1_ExtendedIndex = 40,
  kX86InstIdHaddpd_ExtendedIndex = 2,
  kX86InstIdHaddps_ExtendedIndex = 2,
  kX86InstIdHsubpd_ExtendedIndex = 2,
  kX86InstIdHsubps_ExtendedIndex = 2,
  kX86InstIdIdiv_ExtendedIndex = 56,
  kX86InstIdImul_ExtendedIndex = 57,
  kX86InstIdInc_ExtendedIndex = 58,
  kX86InstIdInsertps_ExtendedIndex = 3,
  kX86InstIdInt_ExtendedIndex = 59,
  kX86InstIdJa_ExtendedIndex = 60,
  kX86InstIdJae_ExtendedIndex = 60,
  kX86InstIdJb_ExtendedIndex = 60,
  kX86InstIdJbe_ExtendedIndex = 60,
  kX86InstIdJc_ExtendedIndex = 60,
  kX86InstIdJe_ExtendedIndex = 60,
  kX86InstIdJg_ExtendedIndex = 60,
  kX86InstIdJge_ExtendedIndex = 60,
  kX86InstIdJl_ExtendedIndex = 60,
  kX86InstIdJle_ExtendedIndex = 60,
  kX86InstIdJna_ExtendedIndex = 60,
  kX86InstIdJnae_ExtendedIndex = 60,
  kX86InstIdJnb_ExtendedIndex = 60,
  kX86InstIdJnbe_ExtendedIndex = 60,
  kX86InstIdJnc_ExtendedIndex = 60,
  kX86InstIdJne_ExtendedIndex = 60,
  kX86InstIdJng_ExtendedIndex = 60,
  kX86InstIdJnge_ExtendedIndex = 60,
  kX86InstIdJnl_ExtendedIndex = 60,
  kX86InstIdJnle_ExtendedIndex = 60,
  kX86InstIdJno_ExtendedIndex = 60,
  kX86InstIdJnp_ExtendedIndex = 60,
  kX86InstIdJns_ExtendedIndex = 60,
  kX86InstIdJnz_ExtendedIndex = 60,
  kX86InstIdJo_ExtendedIndex = 60,
  kX86InstIdJp_ExtendedIndex = 60,
  kX86InstIdJpe_ExtendedIndex = 60,
  kX86InstIdJpo_ExtendedIndex = 60,
  kX86InstIdJs_ExtendedIndex = 60,
  kX86InstIdJz_ExtendedIndex = 60,
  kX86InstIdJecxz_ExtendedIndex = 61,
  kX86InstIdJmp_ExtendedIndex = 62,
  kX86InstIdLahf_ExtendedIndex = 15,
  kX86InstIdLddqu_ExtendedIndex = 63,
  kX86InstIdLdmxcsr_ExtendedIndex = 18,
  kX86InstIdLea_ExtendedIndex = 64,
  kX86InstIdLeave_ExtendedIndex = 15,
  kX86InstIdLfence_ExtendedIndex = 65,
  kX86InstIdLodsb_ExtendedIndex = 15,
  kX86InstIdLodsd_ExtendedIndex = 15,
  kX86InstIdLodsq_ExtendedIndex = 16,
  kX86InstIdLodsw_ExtendedIndex = 21,
  kX86InstIdLzcnt_ExtendedIndex = 8,
  kX86InstIdMaskmovdqu_ExtendedIndex = 66,
  kX86InstIdMaskmovq_ExtendedIndex = 67,
  kX86InstIdMaxpd_ExtendedIndex = 2,
  kX86InstIdMaxps_ExtendedIndex = 2,
  kX86InstIdMaxsd_ExtendedIndex = 2,
  kX86InstIdMaxss_ExtendedIndex = 2,
  kX86InstIdMfence_ExtendedIndex = 65,
  kX86InstIdMinpd_ExtendedIndex = 2,
  kX86InstIdMinps_ExtendedIndex = 2,
  kX86InstIdMinsd_ExtendedIndex = 2,
  kX86InstIdMinss_ExtendedIndex = 2,
  kX86InstIdMonitor_ExtendedIndex = 15,
  kX86InstIdMov_ExtendedIndex = 68,
  kX86InstIdMovPtr_ExtendedIndex = 69,
  kX86InstIdMovapd_ExtendedIndex = 70,
  kX86InstIdMovaps_ExtendedIndex = 71,
  kX86InstIdMovbe_ExtendedIndex = 72,
  kX86InstIdMovd_ExtendedIndex = 73,
  kX86InstIdMovddup_ExtendedIndex = 74,
  kX86InstIdMovdq2q_ExtendedIndex = 75,
  kX86InstIdMovdqa_ExtendedIndex = 76,
  kX86InstIdMovdqu_ExtendedIndex = 77,
  kX86InstIdMovhlps_ExtendedIndex = 78,
  kX86InstIdMovhpd_ExtendedIndex = 79,
  kX86InstIdMovhps_ExtendedIndex = 80,
  kX86InstIdMovlhps_ExtendedIndex = 81,
  kX86InstIdMovlpd_ExtendedIndex = 82,
  kX86InstIdMovlps_ExtendedIndex = 83,
  kX86InstIdMovmskpd_ExtendedIndex = 84,
  kX86InstIdMovmskps_ExtendedIndex = 84,
  kX86InstIdMovntdq_ExtendedIndex = 85,
  kX86InstIdMovntdqa_ExtendedIndex = 86,
  kX86InstIdMovnti_ExtendedIndex = 87,
  kX86InstIdMovntpd_ExtendedIndex = 88,
  kX86InstIdMovntps_ExtendedIndex = 89,
  kX86InstIdMovntq_ExtendedIndex = 90,
  kX86InstIdMovq_ExtendedIndex = 91,
  kX86InstIdMovq2dq_ExtendedIndex = 92,
  kX86InstIdMovsb_ExtendedIndex = 15,
  kX86InstIdMovsd_ExtendedIndex = 93,
  kX86InstIdMovshdup_ExtendedIndex = 27,
  kX86InstIdMovsldup_ExtendedIndex = 27,
  kX86InstIdMovsq_ExtendedIndex = 16,
  kX86InstIdMovss_ExtendedIndex = 94,
  kX86InstIdMovsw_ExtendedIndex = 21,
  kX86InstIdMovsx_ExtendedIndex = 95,
  kX86InstIdMovsxd_ExtendedIndex = 96,
  kX86InstIdMovupd_ExtendedIndex = 97,
  kX86InstIdMovups_ExtendedIndex = 98,
  kX86InstIdMovzx_ExtendedIndex = 95,
  kX86InstIdMpsadbw_ExtendedIndex = 3,
  kX86InstIdMul_ExtendedIndex = 56,
  kX86InstIdMulpd_ExtendedIndex = 2,
  kX86InstIdMulps_ExtendedIndex = 2,
  kX86InstIdMulsd_ExtendedIndex = 2,
  kX86InstIdMulss_ExtendedIndex = 2,
  kX86InstIdMulx_ExtendedIndex = 4,
  kX86InstIdMwait_ExtendedIndex = 15,
  kX86InstIdNeg_ExtendedIndex = 99,
  kX86InstIdNop_ExtendedIndex = 17,
  kX86InstIdNot_ExtendedIndex = 99,
  kX86InstIdOr_ExtendedIndex = 1,
  kX86InstIdOrpd_ExtendedIndex = 2,
  kX86InstIdOrps_ExtendedIndex = 2,
  kX86InstIdPabsb_ExtendedIndex = 100,
  kX86InstIdPabsd_ExtendedIndex = 100,
  kX86InstIdPabsw_ExtendedIndex = 100,
  kX86InstIdPackssdw_ExtendedIndex = 100,
  kX86InstIdPacksswb_ExtendedIndex = 100,
  kX86InstIdPackusdw_ExtendedIndex = 2,
  kX86InstIdPackuswb_ExtendedIndex = 100,
  kX86InstIdPaddb_ExtendedIndex = 100,
  kX86InstIdPaddd_ExtendedIndex = 100,
  kX86InstIdPaddq_ExtendedIndex = 100,
  kX86InstIdPaddsb_ExtendedIndex = 100,
  kX86InstIdPaddsw_ExtendedIndex = 100,
  kX86InstIdPaddusb_ExtendedIndex = 100,
  kX86InstIdPaddusw_ExtendedIndex = 100,
  kX86InstIdPaddw_ExtendedIndex = 100,
  kX86InstIdPalignr_ExtendedIndex = 101,
  kX86InstIdPand_ExtendedIndex = 100,
  kX86InstIdPandn_ExtendedIndex = 100,
  kX86InstIdPause_ExtendedIndex = 17,
  kX86InstIdPavgb_ExtendedIndex = 100,
  kX86InstIdPavgw_ExtendedIndex = 100,
  kX86InstIdPblendvb_ExtendedIndex = 6,
  kX86InstIdPblendw_ExtendedIndex = 3,
  kX86InstIdPclmulqdq_ExtendedIndex = 3,
  kX86InstIdPcmpeqb_ExtendedIndex = 100,
  kX86InstIdPcmpeqd_ExtendedIndex = 100,
  kX86InstIdPcmpeqq_ExtendedIndex = 2,
  kX86InstIdPcmpeqw_ExtendedIndex = 100,
  kX86InstIdPcmpestri_ExtendedIndex = 3,
  kX86InstIdPcmpestrm_ExtendedIndex = 3,
  kX86InstIdPcmpgtb_ExtendedIndex = 100,
  kX86InstIdPcmpgtd_ExtendedIndex = 100,
  kX86InstIdPcmpgtq_ExtendedIndex = 2,
  kX86InstIdPcmpgtw_ExtendedIndex = 100,
  kX86InstIdPcmpistri_ExtendedIndex = 3,
  kX86InstIdPcmpistrm_ExtendedIndex = 3,
  kX86InstIdPdep_ExtendedIndex = 4,
  kX86InstIdPext_ExtendedIndex = 4,
  kX86InstIdPextrb_ExtendedIndex = 102,
  kX86InstIdPextrd_ExtendedIndex = 103,
  kX86InstIdPextrq_ExtendedIndex = 104,
  kX86InstIdPextrw_ExtendedIndex = 105,
  kX86InstIdPf2id_ExtendedIndex = 106,
  kX86InstIdPf2iw_ExtendedIndex = 106,
  kX86InstIdPfacc_ExtendedIndex = 106,
  kX86InstIdPfadd_ExtendedIndex = 106,
  kX86InstIdPfcmpeq_ExtendedIndex = 106,
  kX86InstIdPfcmpge_ExtendedIndex = 106,
  kX86InstIdPfcmpgt_ExtendedIndex = 106,
  kX86InstIdPfmax_ExtendedIndex = 106,
  kX86InstIdPfmin_ExtendedIndex = 106,
  kX86InstIdPfmul_ExtendedIndex = 106,
  kX86InstIdPfnacc_ExtendedIndex = 106,
  kX86InstIdPfpnacc_ExtendedIndex = 106,
  kX86InstIdPfrcp_ExtendedIndex = 106,
  kX86InstIdPfrcpit1_ExtendedIndex = 106,
  kX86InstIdPfrcpit2_ExtendedIndex = 106,
  kX86InstIdPfrsqit1_ExtendedIndex = 106,
  kX86InstIdPfrsqrt_ExtendedIndex = 106,
  kX86InstIdPfsub_ExtendedIndex = 106,
  kX86InstIdPfsubr_ExtendedIndex = 106,
  kX86InstIdPhaddd_ExtendedIndex = 100,
  kX86InstIdPhaddsw_ExtendedIndex = 100,
  kX86InstIdPhaddw_ExtendedIndex = 100,
  kX86InstIdPhminposuw_ExtendedIndex = 2,
  kX86InstIdPhsubd_ExtendedIndex = 100,
  kX86InstIdPhsubsw_ExtendedIndex = 100,
  kX86InstIdPhsubw_ExtendedIndex = 100,
  kX86InstIdPi2fd_ExtendedIndex = 106,
  kX86InstIdPi2fw_ExtendedIndex = 106,
  kX86InstIdPinsrb_ExtendedIndex = 107,
  kX86InstIdPinsrd_ExtendedIndex = 107,
  kX86InstIdPinsrq_ExtendedIndex = 108,
  kX86InstIdPinsrw_ExtendedIndex = 109,
  kX86InstIdPmaddubsw_ExtendedIndex = 100,
  kX86InstIdPmaddwd_ExtendedIndex = 100,
  kX86InstIdPmaxsb_ExtendedIndex = 2,
  kX86InstIdPmaxsd_ExtendedIndex = 2,
  kX86InstIdPmaxsw_ExtendedIndex = 100,
  kX86InstIdPmaxub_ExtendedIndex = 100,
  kX86InstIdPmaxud_ExtendedIndex = 2,
  kX86InstIdPmaxuw_ExtendedIndex = 2,
  kX86InstIdPminsb_ExtendedIndex = 2,
  kX86InstIdPminsd_ExtendedIndex = 2,
  kX86InstIdPminsw_ExtendedIndex = 100,
  kX86InstIdPminub_ExtendedIndex = 100,
  kX86InstIdPminud_ExtendedIndex = 2,
  kX86InstIdPminuw_ExtendedIndex = 2,
  kX86InstIdPmovmskb_ExtendedIndex = 110,
  kX86InstIdPmovsxbd_ExtendedIndex = 27,
  kX86InstIdPmovsxbq_ExtendedIndex = 27,
  kX86InstIdPmovsxbw_ExtendedIndex = 27,
  kX86InstIdPmovsxdq_ExtendedIndex = 27,
  kX86InstIdPmovsxwd_ExtendedIndex = 27,
  kX86InstIdPmovsxwq_ExtendedIndex = 27,
  kX86InstIdPmovzxbd_ExtendedIndex = 27,
  kX86InstIdPmovzxbq_ExtendedIndex = 27,
  kX86InstIdPmovzxbw_ExtendedIndex = 27,
  kX86InstIdPmovzxdq_ExtendedIndex = 27,
  kX86InstIdPmovzxwd_ExtendedIndex = 27,
  kX86InstIdPmovzxwq_ExtendedIndex = 27,
  kX86InstIdPmuldq_ExtendedIndex = 2,
  kX86InstIdPmulhrsw_ExtendedIndex = 100,
  kX86InstIdPmulhuw_ExtendedIndex = 100,
  kX86InstIdPmulhw_ExtendedIndex = 100,
  kX86InstIdPmulld_ExtendedIndex = 2,
  kX86InstIdPmullw_ExtendedIndex = 100,
  kX86InstIdPmuludq_ExtendedIndex = 100,
  kX86InstIdPop_ExtendedIndex = 111,
  kX86InstIdPopa_ExtendedIndex = 15,
  kX86InstIdPopcnt_ExtendedIndex = 8,
  kX86InstIdPopf_ExtendedIndex = 15,
  kX86InstIdPor_ExtendedIndex = 100,
  kX86InstIdPrefetch_ExtendedIndex = 112,
  kX86InstIdPrefetch3dNow_ExtendedIndex = 18,
  kX86InstIdPrefetchw3dNow_ExtendedIndex = 18,
  kX86InstIdPsadbw_ExtendedIndex = 100,
  kX86InstIdPshufb_ExtendedIndex = 100,
  kX86InstIdPshufd_ExtendedIndex = 113,
  kX86InstIdPshufhw_ExtendedIndex = 113,
  kX86InstIdPshuflw_ExtendedIndex = 113,
  kX86InstIdPshufw_ExtendedIndex = 114,
  kX86InstIdPsignb_ExtendedIndex = 100,
  kX86InstIdPsignd_ExtendedIndex = 100,
  kX86InstIdPsignw_ExtendedIndex = 100,
  kX86InstIdPslld_ExtendedIndex = 115,
  kX86InstIdPslldq_ExtendedIndex = 116,
  kX86InstIdPsllq_ExtendedIndex = 117,
  kX86InstIdPsllw_ExtendedIndex = 118,
  kX86InstIdPsrad_ExtendedIndex = 119,
  kX86InstIdPsraw_ExtendedIndex = 120,
  kX86InstIdPsrld_ExtendedIndex = 121,
  kX86InstIdPsrldq_ExtendedIndex = 122,
  kX86InstIdPsrlq_ExtendedIndex = 123,
  kX86InstIdPsrlw_ExtendedIndex = 124,
  kX86InstIdPsubb_ExtendedIndex = 100,
  kX86InstIdPsubd_ExtendedIndex = 100,
  kX86InstIdPsubq_ExtendedIndex = 100,
  kX86InstIdPsubsb_ExtendedIndex = 100,
  kX86InstIdPsubsw_ExtendedIndex = 100,
  kX86InstIdPsubusb_ExtendedIndex = 100,
  kX86InstIdPsubusw_ExtendedIndex = 100,
  kX86InstIdPsubw_ExtendedIndex = 100,
  kX86InstIdPswapd_ExtendedIndex = 106,
  kX86InstIdPtest_ExtendedIndex = 25,
  kX86InstIdPunpckhbw_ExtendedIndex = 100,
  kX86InstIdPunpckhdq_ExtendedIndex = 100,
  kX86InstIdPunpckhqdq_ExtendedIndex = 2,
  kX86InstIdPunpckhwd_ExtendedIndex = 100,
  kX86InstIdPunpcklbw_ExtendedIndex = 100,
  kX86InstIdPunpckldq_ExtendedIndex = 100,
  kX86InstIdPunpcklqdq_ExtendedIndex = 2,
  kX86InstIdPunpcklwd_ExtendedIndex = 100,
  kX86InstIdPush_ExtendedIndex = 125,
  kX86InstIdPusha_ExtendedIndex = 15,
  kX86InstIdPushf_ExtendedIndex = 15,
  kX86InstIdPxor_ExtendedIndex = 100,
  kX86InstIdRcl_ExtendedIndex = 126,
  kX86InstIdRcpps_ExtendedIndex = 27,
  kX86InstIdRcpss_ExtendedIndex = 32,
  kX86InstIdRcr_ExtendedIndex = 126,
  kX86InstIdRdfsbase_ExtendedIndex = 127,
  kX86InstIdRdgsbase_ExtendedIndex = 127,
  kX86InstIdRdrand_ExtendedIndex = 128,
  kX86InstIdRdtsc_ExtendedIndex = 15,
  kX86InstIdRdtscp_ExtendedIndex = 15,
  kX86InstIdRepLodsb_ExtendedIndex = 129,
  kX86InstIdRepLodsd_ExtendedIndex = 129,
  kX86InstIdRepLodsq_ExtendedIndex = 130,
  kX86InstIdRepLodsw_ExtendedIndex = 129,
  kX86InstIdRepMovsb_ExtendedIndex = 131,
  kX86InstIdRepMovsd_ExtendedIndex = 131,
  kX86InstIdRepMovsq_ExtendedIndex = 132,
  kX86InstIdRepMovsw_ExtendedIndex = 131,
  kX86InstIdRepStosb_ExtendedIndex = 129,
  kX86InstIdRepStosd_ExtendedIndex = 129,
  kX86InstIdRepStosq_ExtendedIndex = 130,
  kX86InstIdRepStosw_ExtendedIndex = 129,
  kX86InstIdRepeCmpsb_ExtendedIndex = 131,
  kX86InstIdRepeCmpsd_ExtendedIndex = 131,
  kX86InstIdRepeCmpsq_ExtendedIndex = 132,
  kX86InstIdRepeCmpsw_ExtendedIndex = 131,
  kX86InstIdRepeScasb_ExtendedIndex = 131,
  kX86InstIdRepeScasd_ExtendedIndex = 131,
  kX86InstIdRepeScasq_ExtendedIndex = 132,
  kX86InstIdRepeScasw_ExtendedIndex = 131,
  kX86InstIdRepneCmpsb_ExtendedIndex = 131,
  kX86InstIdRepneCmpsd_ExtendedIndex = 131,
  kX86InstIdRepneCmpsq_ExtendedIndex = 132,
  kX86InstIdRepneCmpsw_ExtendedIndex = 131,
  kX86InstIdRepneScasb_ExtendedIndex = 131,
  kX86InstIdRepneScasd_ExtendedIndex = 131,
  kX86InstIdRepneScasq_ExtendedIndex = 132,
  kX86InstIdRepneScasw_ExtendedIndex = 131,
  kX86InstIdRet_ExtendedIndex = 133,
  kX86InstIdRol_ExtendedIndex = 126,
  kX86InstIdRor_ExtendedIndex = 126,
  kX86InstIdRorx_ExtendedIndex = 134,
  kX86InstIdRoundpd_ExtendedIndex = 113,
  kX86InstIdRoundps_ExtendedIndex = 113,
  kX86InstIdRoundsd_ExtendedIndex = 135,
  kX86InstIdRoundss_ExtendedIndex = 136,
  kX86InstIdRsqrtps_ExtendedIndex = 27,
  kX86InstIdRsqrtss_ExtendedIndex = 32,
  kX86InstIdSahf_ExtendedIndex = 15,
  kX86InstIdSal_ExtendedIndex = 126,
  kX86InstIdSar_ExtendedIndex = 126,
  kX86InstIdSarx_ExtendedIndex = 5,
  kX86InstIdSbb_ExtendedIndex = 1,
  kX86InstIdScasb_ExtendedIndex = 15,
  kX86InstIdScasd_ExtendedIndex = 15,
  kX86InstIdScasq_ExtendedIndex = 16,
  kX86InstIdScasw_ExtendedIndex = 21,
  kX86InstIdSeta_ExtendedIndex = 137,
  kX86InstIdSetae_ExtendedIndex = 137,
  kX86InstIdSetb_ExtendedIndex = 137,
  kX86InstIdSetbe_ExtendedIndex = 137,
  kX86InstIdSetc_ExtendedIndex = 137,
  kX86InstIdSete_ExtendedIndex = 137,
  kX86InstIdSetg_ExtendedIndex = 137,
  kX86InstIdSetge_ExtendedIndex = 137,
  kX86InstIdSetl_ExtendedIndex = 137,
  kX86InstIdSetle_ExtendedIndex = 137,
  kX86InstIdSetna_ExtendedIndex = 137,
  kX86InstIdSetnae_ExtendedIndex = 137,
  kX86InstIdSetnb_ExtendedIndex = 137,
  kX86InstIdSetnbe_ExtendedIndex = 137,
  kX86InstIdSetnc_ExtendedIndex = 137,
  kX86InstIdSetne_ExtendedIndex = 137,
  kX86InstIdSetng_ExtendedIndex = 137,
  kX86InstIdSetnge_ExtendedIndex = 137,
  kX86InstIdSetnl_ExtendedIndex = 137,
  kX86InstIdSetnle_ExtendedIndex = 137,
  kX86InstIdSetno_ExtendedIndex = 137,
  kX86InstIdSetnp_ExtendedIndex = 137,
  kX86InstIdSetns_ExtendedIndex = 137,
  kX86InstIdSetnz_ExtendedIndex = 137,
  kX86InstIdSeto_ExtendedIndex = 137,
  kX86InstIdSetp_ExtendedIndex = 137,
  kX86InstIdSetpe_ExtendedIndex = 137,
  kX86InstIdSetpo_ExtendedIndex = 137,
  kX86InstIdSets_ExtendedIndex = 137,
  kX86InstIdSetz_ExtendedIndex = 137,
  kX86InstIdSfence_ExtendedIndex = 65,
  kX86InstIdShl_ExtendedIndex = 126,
  kX86InstIdShld_ExtendedIndex = 138,
  kX86InstIdShlx_ExtendedIndex = 5,
  kX86InstIdShr_ExtendedIndex = 126,
  kX86InstIdShrd_ExtendedIndex = 139,
  kX86InstIdShrx_ExtendedIndex = 5,
  kX86InstIdShufpd_ExtendedIndex = 3,
  kX86InstIdShufps_ExtendedIndex = 3,
  kX86InstIdSqrtpd_ExtendedIndex = 27,
  kX86InstIdSqrtps_ExtendedIndex = 27,
  kX86InstIdSqrtsd_ExtendedIndex = 35,
  kX86InstIdSqrtss_ExtendedIndex = 32,
  kX86InstIdStc_ExtendedIndex = 17,
  kX86InstIdStd_ExtendedIndex = 17,
  kX86InstIdStmxcsr_ExtendedIndex = 18,
  kX86InstIdStosb_ExtendedIndex = 15,
  kX86InstIdStosd_ExtendedIndex = 15,
  kX86InstIdStosq_ExtendedIndex = 16,
  kX86InstIdStosw_ExtendedIndex = 21,
  kX86InstIdSub_ExtendedIndex = 1,
  kX86InstIdSubpd_ExtendedIndex = 2,
  kX86InstIdSubps_ExtendedIndex = 2,
  kX86InstIdSubsd_ExtendedIndex = 2,
  kX86InstIdSubss_ExtendedIndex = 2,
  kX86InstIdTest_ExtendedIndex = 140,
  kX86InstIdTzcnt_ExtendedIndex = 141,
  kX86InstIdUcomisd_ExtendedIndex = 25,
  kX86InstIdUcomiss_ExtendedIndex = 25,
  kX86InstIdUd2_ExtendedIndex = 17,
  kX86InstIdUnpckhpd_ExtendedIndex = 2,
  kX86InstIdUnpckhps_ExtendedIndex = 2,
  kX86InstIdUnpcklpd_ExtendedIndex = 2,
  kX86InstIdUnpcklps_ExtendedIndex = 2,
  kX86InstIdVaddpd_ExtendedIndex = 142,
  kX86InstIdVaddps_ExtendedIndex = 142,
  kX86InstIdVaddsd_ExtendedIndex = 142,
  kX86InstIdVaddss_ExtendedIndex = 142,
  kX86InstIdVaddsubpd_ExtendedIndex = 142,
  kX86InstIdVaddsubps_ExtendedIndex = 142,
  kX86InstIdVaesdec_ExtendedIndex = 143,
  kX86InstIdVaesdeclast_ExtendedIndex = 143,
  kX86InstIdVaesenc_ExtendedIndex = 143,
  kX86InstIdVaesenclast_ExtendedIndex = 143,
  kX86InstIdVaesimc_ExtendedIndex = 144,
  kX86InstIdVaeskeygenassist_ExtendedIndex = 145,
  kX86InstIdVandnpd_ExtendedIndex = 142,
  kX86InstIdVandnps_ExtendedIndex = 142,
  kX86InstIdVandpd_ExtendedIndex = 142,
  kX86InstIdVandps_ExtendedIndex = 142,
  kX86InstIdVblendpd_ExtendedIndex = 146,
  kX86InstIdVblendps_ExtendedIndex = 146,
  kX86InstIdVblendvpd_ExtendedIndex = 147,
  kX86InstIdVblendvps_ExtendedIndex = 147,
  kX86InstIdVbroadcastf128_ExtendedIndex = 148,
  kX86InstIdVbroadcasti128_ExtendedIndex = 148,
  kX86InstIdVbroadcastsd_ExtendedIndex = 149,
  kX86InstIdVbroadcastss_ExtendedIndex = 149,
  kX86InstIdVcmppd_ExtendedIndex = 146,
  kX86InstIdVcmpps_ExtendedIndex = 146,
  kX86InstIdVcmpsd_ExtendedIndex = 150,
  kX86InstIdVcmpss_ExtendedIndex = 150,
  kX86InstIdVcomisd_ExtendedIndex = 144,
  kX86InstIdVcomiss_ExtendedIndex = 144,
  kX86InstIdVcvtdq2pd_ExtendedIndex = 151,
  kX86InstIdVcvtdq2ps_ExtendedIndex = 152,
  kX86InstIdVcvtpd2dq_ExtendedIndex = 153,
  kX86InstIdVcvtpd2ps_ExtendedIndex = 153,
  kX86InstIdVcvtph2ps_ExtendedIndex = 151,
  kX86InstIdVcvtps2dq_ExtendedIndex = 152,
  kX86InstIdVcvtps2pd_ExtendedIndex = 151,
  kX86InstIdVcvtps2ph_ExtendedIndex = 154,
  kX86InstIdVcvtsd2si_ExtendedIndex = 155,
  kX86InstIdVcvtsd2ss_ExtendedIndex = 143,
  kX86InstIdVcvtsi2sd_ExtendedIndex = 156,
  kX86InstIdVcvtsi2ss_ExtendedIndex = 156,
  kX86InstIdVcvtss2sd_ExtendedIndex = 143,
  kX86InstIdVcvtss2si_ExtendedIndex = 155,
  kX86InstIdVcvttpd2dq_ExtendedIndex = 157,
  kX86InstIdVcvttps2dq_ExtendedIndex = 152,
  kX86InstIdVcvttsd2si_ExtendedIndex = 155,
  kX86InstIdVcvttss2si_ExtendedIndex = 155,
  kX86InstIdVdivpd_ExtendedIndex = 142,
  kX86InstIdVdivps_ExtendedIndex = 142,
  kX86InstIdVdivsd_ExtendedIndex = 143,
  kX86InstIdVdivss_ExtendedIndex = 143,
  kX86InstIdVdppd_ExtendedIndex = 150,
  kX86InstIdVdpps_ExtendedIndex = 146,
  kX86InstIdVextractf128_ExtendedIndex = 158,
  kX86InstIdVextracti128_ExtendedIndex = 158,
  kX86InstIdVextractps_ExtendedIndex = 159,
  kX86InstIdVfmadd132pd_ExtendedIndex = 160,
  kX86InstIdVfmadd132ps_ExtendedIndex = 142,
  kX86InstIdVfmadd132sd_ExtendedIndex = 161,
  kX86InstIdVfmadd132ss_ExtendedIndex = 143,
  kX86InstIdVfmadd213pd_ExtendedIndex = 160,
  kX86InstIdVfmadd213ps_ExtendedIndex = 142,
  kX86InstIdVfmadd213sd_ExtendedIndex = 161,
  kX86InstIdVfmadd213ss_ExtendedIndex = 143,
  kX86InstIdVfmadd231pd_ExtendedIndex = 160,
  kX86InstIdVfmadd231ps_ExtendedIndex = 142,
  kX86InstIdVfmadd231sd_ExtendedIndex = 161,
  kX86InstIdVfmadd231ss_ExtendedIndex = 143,
  kX86InstIdVfmaddpd_ExtendedIndex = 162,
  kX86InstIdVfmaddps_ExtendedIndex = 162,
  kX86InstIdVfmaddsd_ExtendedIndex = 163,
  kX86InstIdVfmaddss_ExtendedIndex = 163,
  kX86InstIdVfmaddsub132pd_ExtendedIndex = 160,
  kX86InstIdVfmaddsub132ps_ExtendedIndex = 142,
  kX86InstIdVfmaddsub213pd_ExtendedIndex = 160,
  kX86InstIdVfmaddsub213ps_ExtendedIndex = 142,
  kX86InstIdVfmaddsub231pd_ExtendedIndex = 160,
  kX86InstIdVfmaddsub231ps_ExtendedIndex = 142,
  kX86InstIdVfmaddsubpd_ExtendedIndex = 162,
  kX86InstIdVfmaddsubps_ExtendedIndex = 162,
  kX86InstIdVfmsub132pd_ExtendedIndex = 160,
  kX86InstIdVfmsub132ps_ExtendedIndex = 142,
  kX86InstIdVfmsub132sd_ExtendedIndex = 161,
  kX86InstIdVfmsub132ss_ExtendedIndex = 143,
  kX86InstIdVfmsub213pd_ExtendedIndex = 160,
  kX86InstIdVfmsub213ps_ExtendedIndex = 142,
  kX86InstIdVfmsub213sd_ExtendedIndex = 161,
  kX86InstIdVfmsub213ss_ExtendedIndex = 143,
  kX86InstIdVfmsub231pd_ExtendedIndex = 160,
  kX86InstIdVfmsub231ps_ExtendedIndex = 142,
  kX86InstIdVfmsub231sd_ExtendedIndex = 161,
  kX86InstIdVfmsub231ss_ExtendedIndex = 143,
  kX86InstIdVfmsubadd132pd_ExtendedIndex = 160,
  kX86InstIdVfmsubadd132ps_ExtendedIndex = 142,
  kX86InstIdVfmsubadd213pd_ExtendedIndex = 160,
  kX86InstIdVfmsubadd213ps_ExtendedIndex = 142,
  kX86InstIdVfmsubadd231pd_ExtendedIndex = 160,
  kX86InstIdVfmsubadd231ps_ExtendedIndex = 142,
  kX86InstIdVfmsubaddpd_ExtendedIndex = 162,
  kX86InstIdVfmsubaddps_ExtendedIndex = 162,
  kX86InstIdVfmsubpd_ExtendedIndex = 162,
  kX86InstIdVfmsubps_ExtendedIndex = 162,
  kX86InstIdVfmsubsd_ExtendedIndex = 163,
  kX86InstIdVfmsubss_ExtendedIndex = 163,
  kX86InstIdVfnmadd132pd_ExtendedIndex = 160,
  kX86InstIdVfnmadd132ps_ExtendedIndex = 142,
  kX86InstIdVfnmadd132sd_ExtendedIndex = 161,
  kX86InstIdVfnmadd132ss_ExtendedIndex = 143,
  kX86InstIdVfnmadd213pd_ExtendedIndex = 160,
  kX86InstIdVfnmadd213ps_ExtendedIndex = 142,
  kX86InstIdVfnmadd213sd_ExtendedIndex = 161,
  kX86InstIdVfnmadd213ss_ExtendedIndex = 143,
  kX86InstIdVfnmadd231pd_ExtendedIndex = 160,
  kX86InstIdVfnmadd231ps_ExtendedIndex = 142,
  kX86InstIdVfnmadd231sd_ExtendedIndex = 161,
  kX86InstIdVfnmadd231ss_ExtendedIndex = 143,
  kX86InstIdVfnmaddpd_ExtendedIndex = 162,
  kX86InstIdVfnmaddps_ExtendedIndex = 162,
  kX86InstIdVfnmaddsd_ExtendedIndex = 163,
  kX86InstIdVfnmaddss_ExtendedIndex = 163,
  kX86InstIdVfnmsub132pd_ExtendedIndex = 160,
  kX86InstIdVfnmsub132ps_ExtendedIndex = 142,
  kX86InstIdVfnmsub132sd_ExtendedIndex = 161,
  kX86InstIdVfnmsub132ss_ExtendedIndex = 143,
  kX86InstIdVfnmsub213pd_ExtendedIndex = 160,
  kX86InstIdVfnmsub213ps_ExtendedIndex = 142,
  kX86InstIdVfnmsub213sd_ExtendedIndex = 161,
  kX86InstIdVfnmsub213ss_ExtendedIndex = 143,
  kX86InstIdVfnmsub231pd_ExtendedIndex = 160,
  kX86InstIdVfnmsub231ps_ExtendedIndex = 142,
  kX86InstIdVfnmsub231sd_ExtendedIndex = 161,
  kX86InstIdVfnmsub231ss_ExtendedIndex = 143,
  kX86InstIdVfnmsubpd_ExtendedIndex = 162,
  kX86InstIdVfnmsubps_ExtendedIndex = 162,
  kX86InstIdVfnmsubsd_ExtendedIndex = 163,
  kX86InstIdVfnmsubss_ExtendedIndex = 163,
  kX86InstIdVfrczpd_ExtendedIndex = 164,
  kX86InstIdVfrczps_ExtendedIndex = 164,
  kX86InstIdVfrczsd_ExtendedIndex = 165,
  kX86InstIdVfrczss_ExtendedIndex = 165,
  kX86InstIdVgatherdpd_ExtendedIndex = 166,
  kX86InstIdVgatherdps_ExtendedIndex = 167,
  kX86InstIdVgatherqpd_ExtendedIndex = 166,
  kX86InstIdVgatherqps_ExtendedIndex = 168,
  kX86InstIdVhaddpd_ExtendedIndex = 142,
  kX86InstIdVhaddps_ExtendedIndex = 142,
  kX86InstIdVhsubpd_ExtendedIndex = 142,
  kX86InstIdVhsubps_ExtendedIndex = 142,
  kX86InstIdVinsertf128_ExtendedIndex = 169,
  kX86InstIdVinserti128_ExtendedIndex = 169,
  kX86InstIdVinsertps_ExtendedIndex = 150,
  kX86InstIdVlddqu_ExtendedIndex = 170,
  kX86InstIdVldmxcsr_ExtendedIndex = 171,
  kX86InstIdVmaskmovdqu_ExtendedIndex = 172,
  kX86InstIdVmaskmovpd_ExtendedIndex = 173,
  kX86InstIdVmaskmovps_ExtendedIndex = 174,
  kX86InstIdVmaxpd_ExtendedIndex = 142,
  kX86InstIdVmaxps_ExtendedIndex = 142,
  kX86InstIdVmaxsd_ExtendedIndex = 142,
  kX86InstIdVmaxss_ExtendedIndex = 142,
  kX86InstIdVminpd_ExtendedIndex = 142,
  kX86InstIdVminps_ExtendedIndex = 142,
  kX86InstIdVminsd_ExtendedIndex = 142,
  kX86InstIdVminss_ExtendedIndex = 142,
  kX86InstIdVmovapd_ExtendedIndex = 175,
  kX86InstIdVmovaps_ExtendedIndex = 176,
  kX86InstIdVmovd_ExtendedIndex = 177,
  kX86InstIdVmovddup_ExtendedIndex = 152,
  kX86InstIdVmovdqa_ExtendedIndex = 178,
  kX86InstIdVmovdqu_ExtendedIndex = 179,
  kX86InstIdVmovhlps_ExtendedIndex = 180,
  kX86InstIdVmovhpd_ExtendedIndex = 181,
  kX86InstIdVmovhps_ExtendedIndex = 182,
  kX86InstIdVmovlhps_ExtendedIndex = 180,
  kX86InstIdVmovlpd_ExtendedIndex = 183,
  kX86InstIdVmovlps_ExtendedIndex = 184,
  kX86InstIdVmovmskpd_ExtendedIndex = 185,
  kX86InstIdVmovmskps_ExtendedIndex = 185,
  kX86InstIdVmovntdq_ExtendedIndex = 186,
  kX86InstIdVmovntdqa_ExtendedIndex = 170,
  kX86InstIdVmovntpd_ExtendedIndex = 187,
  kX86InstIdVmovntps_ExtendedIndex = 187,
  kX86InstIdVmovq_ExtendedIndex = 188,
  kX86InstIdVmovsd_ExtendedIndex = 189,
  kX86InstIdVmovshdup_ExtendedIndex = 152,
  kX86InstIdVmovsldup_ExtendedIndex = 152,
  kX86InstIdVmovss_ExtendedIndex = 190,
  kX86InstIdVmovupd_ExtendedIndex = 191,
  kX86InstIdVmovups_ExtendedIndex = 192,
  kX86InstIdVmpsadbw_ExtendedIndex = 146,
  kX86InstIdVmulpd_ExtendedIndex = 142,
  kX86InstIdVmulps_ExtendedIndex = 142,
  kX86InstIdVmulsd_ExtendedIndex = 142,
  kX86InstIdVmulss_ExtendedIndex = 142,
  kX86InstIdVorpd_ExtendedIndex = 142,
  kX86InstIdVorps_ExtendedIndex = 142,
  kX86InstIdVpabsb_ExtendedIndex = 152,
  kX86InstIdVpabsd_ExtendedIndex = 152,
  kX86InstIdVpabsw_ExtendedIndex = 152,
  kX86InstIdVpackssdw_ExtendedIndex = 142,
  kX86InstIdVpacksswb_ExtendedIndex = 142,
  kX86InstIdVpackusdw_ExtendedIndex = 142,
  kX86InstIdVpackuswb_ExtendedIndex = 142,
  kX86InstIdVpaddb_ExtendedIndex = 142,
  kX86InstIdVpaddd_ExtendedIndex = 142,
  kX86InstIdVpaddq_ExtendedIndex = 142,
  kX86InstIdVpaddsb_ExtendedIndex = 142,
  kX86InstIdVpaddsw_ExtendedIndex = 142,
  kX86InstIdVpaddusb_ExtendedIndex = 142,
  kX86InstIdVpaddusw_ExtendedIndex = 142,
  kX86InstIdVpaddw_ExtendedIndex = 142,
  kX86InstIdVpalignr_ExtendedIndex = 146,
  kX86InstIdVpand_ExtendedIndex = 142,
  kX86InstIdVpandn_ExtendedIndex = 142,
  kX86InstIdVpavgb_ExtendedIndex = 142,
  kX86InstIdVpavgw_ExtendedIndex = 142,
  kX86InstIdVpblendd_ExtendedIndex = 146,
  kX86InstIdVpblendvb_ExtendedIndex = 193,
  kX86InstIdVpblendw_ExtendedIndex = 146,
  kX86InstIdVpbroadcastb_ExtendedIndex = 151,
  kX86InstIdVpbroadcastd_ExtendedIndex = 151,
  kX86InstIdVpbroadcastq_ExtendedIndex = 151,
  kX86InstIdVpbroadcastw_ExtendedIndex = 151,
  kX86InstIdVpclmulqdq_ExtendedIndex = 150,
  kX86InstIdVpcmov_ExtendedIndex = 194,
  kX86InstIdVpcmpeqb_ExtendedIndex = 142,
  kX86InstIdVpcmpeqd_ExtendedIndex = 142,
  kX86InstIdVpcmpeqq_ExtendedIndex = 142,
  kX86InstIdVpcmpeqw_ExtendedIndex = 142,
  kX86InstIdVpcmpestri_ExtendedIndex = 145,
  kX86InstIdVpcmpestrm_ExtendedIndex = 145,
  kX86InstIdVpcmpgtb_ExtendedIndex = 142,
  kX86InstIdVpcmpgtd_ExtendedIndex = 142,
  kX86InstIdVpcmpgtq_ExtendedIndex = 142,
  kX86InstIdVpcmpgtw_ExtendedIndex = 142,
  kX86InstIdVpcmpistri_ExtendedIndex = 145,
  kX86InstIdVpcmpistrm_ExtendedIndex = 145,
  kX86InstIdVpcomb_ExtendedIndex = 195,
  kX86InstIdVpcomd_ExtendedIndex = 195,
  kX86InstIdVpcomq_ExtendedIndex = 195,
  kX86InstIdVpcomub_ExtendedIndex = 195,
  kX86InstIdVpcomud_ExtendedIndex = 195,
  kX86InstIdVpcomuq_ExtendedIndex = 195,
  kX86InstIdVpcomuw_ExtendedIndex = 195,
  kX86InstIdVpcomw_ExtendedIndex = 195,
  kX86InstIdVperm2f128_ExtendedIndex = 196,
  kX86InstIdVperm2i128_ExtendedIndex = 196,
  kX86InstIdVpermd_ExtendedIndex = 197,
  kX86InstIdVpermil2pd_ExtendedIndex = 198,
  kX86InstIdVpermil2ps_ExtendedIndex = 198,
  kX86InstIdVpermilpd_ExtendedIndex = 199,
  kX86InstIdVpermilps_ExtendedIndex = 200,
  kX86InstIdVpermpd_ExtendedIndex = 201,
  kX86InstIdVpermps_ExtendedIndex = 197,
  kX86InstIdVpermq_ExtendedIndex = 201,
  kX86InstIdVpextrb_ExtendedIndex = 202,
  kX86InstIdVpextrd_ExtendedIndex = 159,
  kX86InstIdVpextrq_ExtendedIndex = 203,
  kX86InstIdVpextrw_ExtendedIndex = 204,
  kX86InstIdVpgatherdd_ExtendedIndex = 167,
  kX86InstIdVpgatherdq_ExtendedIndex = 166,
  kX86InstIdVpgatherqd_ExtendedIndex = 168,
  kX86InstIdVpgatherqq_ExtendedIndex = 166,
  kX86InstIdVphaddbd_ExtendedIndex = 165,
  kX86InstIdVphaddbq_ExtendedIndex = 165,
  kX86InstIdVphaddbw_ExtendedIndex = 165,
  kX86InstIdVphaddd_ExtendedIndex = 142,
  kX86InstIdVphadddq_ExtendedIndex = 165,
  kX86InstIdVphaddsw_ExtendedIndex = 142,
  kX86InstIdVphaddubd_ExtendedIndex = 165,
  kX86InstIdVphaddubq_ExtendedIndex = 165,
  kX86InstIdVphaddubw_ExtendedIndex = 165,
  kX86InstIdVphaddudq_ExtendedIndex = 165,
  kX86InstIdVphadduwd_ExtendedIndex = 165,
  kX86InstIdVphadduwq_ExtendedIndex = 165,
  kX86InstIdVphaddw_ExtendedIndex = 142,
  kX86InstIdVphaddwd_ExtendedIndex = 165,
  kX86InstIdVphaddwq_ExtendedIndex = 165,
  kX86InstIdVphminposuw_ExtendedIndex = 144,
  kX86InstIdVphsubbw_ExtendedIndex = 165,
  kX86InstIdVphsubd_ExtendedIndex = 142,
  kX86InstIdVphsubdq_ExtendedIndex = 165,
  kX86InstIdVphsubsw_ExtendedIndex = 142,
  kX86InstIdVphsubw_ExtendedIndex = 142,
  kX86InstIdVphsubwd_ExtendedIndex = 165,
  kX86InstIdVpinsrb_ExtendedIndex = 205,
  kX86InstIdVpinsrd_ExtendedIndex = 206,
  kX86InstIdVpinsrq_ExtendedIndex = 207,
  kX86InstIdVpinsrw_ExtendedIndex = 208,
  kX86InstIdVpmacsdd_ExtendedIndex = 209,
  kX86InstIdVpmacsdqh_ExtendedIndex = 209,
  kX86InstIdVpmacsdql_ExtendedIndex = 209,
  kX86InstIdVpmacssdd_ExtendedIndex = 209,
  kX86InstIdVpmacssdqh_ExtendedIndex = 209,
  kX86InstIdVpmacssdql_ExtendedIndex = 209,
  kX86InstIdVpmacsswd_ExtendedIndex = 209,
  kX86InstIdVpmacssww_ExtendedIndex = 209,
  kX86InstIdVpmacswd_ExtendedIndex = 209,
  kX86InstIdVpmacsww_ExtendedIndex = 209,
  kX86InstIdVpmadcsswd_ExtendedIndex = 209,
  kX86InstIdVpmadcswd_ExtendedIndex = 209,
  kX86InstIdVpmaddubsw_ExtendedIndex = 142,
  kX86InstIdVpmaddwd_ExtendedIndex = 142,
  kX86InstIdVpmaskmovd_ExtendedIndex = 210,
  kX86InstIdVpmaskmovq_ExtendedIndex = 211,
  kX86InstIdVpmaxsb_ExtendedIndex = 142,
  kX86InstIdVpmaxsd_ExtendedIndex = 142,
  kX86InstIdVpmaxsw_ExtendedIndex = 142,
  kX86InstIdVpmaxub_ExtendedIndex = 142,
  kX86InstIdVpmaxud_ExtendedIndex = 142,
  kX86InstIdVpmaxuw_ExtendedIndex = 142,
  kX86InstIdVpminsb_ExtendedIndex = 142,
  kX86InstIdVpminsd_ExtendedIndex = 142,
  kX86InstIdVpminsw_ExtendedIndex = 142,
  kX86InstIdVpminub_ExtendedIndex = 142,
  kX86InstIdVpminud_ExtendedIndex = 142,
  kX86InstIdVpminuw_ExtendedIndex = 142,
  kX86InstIdVpmovmskb_ExtendedIndex = 185,
  kX86InstIdVpmovsxbd_ExtendedIndex = 152,
  kX86InstIdVpmovsxbq_ExtendedIndex = 152,
  kX86InstIdVpmovsxbw_ExtendedIndex = 152,
  kX86InstIdVpmovsxdq_ExtendedIndex = 152,
  kX86InstIdVpmovsxwd_ExtendedIndex = 152,
  kX86InstIdVpmovsxwq_ExtendedIndex = 152,
  kX86InstIdVpmovzxbd_ExtendedIndex = 152,
  kX86InstIdVpmovzxbq_ExtendedIndex = 152,
  kX86InstIdVpmovzxbw_ExtendedIndex = 152,
  kX86InstIdVpmovzxdq_ExtendedIndex = 152,
  kX86InstIdVpmovzxwd_ExtendedIndex = 152,
  kX86InstIdVpmovzxwq_ExtendedIndex = 152,
  kX86InstIdVpmuldq_ExtendedIndex = 142,
  kX86InstIdVpmulhrsw_ExtendedIndex = 142,
  kX86InstIdVpmulhuw_ExtendedIndex = 142,
  kX86InstIdVpmulhw_ExtendedIndex = 142,
  kX86InstIdVpmulld_ExtendedIndex = 142,
  kX86InstIdVpmullw_ExtendedIndex = 142,
  kX86InstIdVpmuludq_ExtendedIndex = 142,
  kX86InstIdVpor_ExtendedIndex = 142,
  kX86InstIdVpperm_ExtendedIndex = 212,
  kX86InstIdVprotb_ExtendedIndex = 213,
  kX86InstIdVprotd_ExtendedIndex = 214,
  kX86InstIdVprotq_ExtendedIndex = 215,
  kX86InstIdVprotw_ExtendedIndex = 216,
  kX86InstIdVpsadbw_ExtendedIndex = 142,
  kX86InstIdVpshab_ExtendedIndex = 217,
  kX86InstIdVpshad_ExtendedIndex = 217,
  kX86InstIdVpshaq_ExtendedIndex = 217,
  kX86InstIdVpshaw_ExtendedIndex = 217,
  kX86InstIdVpshlb_ExtendedIndex = 217,
  kX86InstIdVpshld_ExtendedIndex = 217,
  kX86InstIdVpshlq_ExtendedIndex = 217,
  kX86InstIdVpshlw_ExtendedIndex = 217,
  kX86InstIdVpshufb_ExtendedIndex = 142,
  kX86InstIdVpshufd_ExtendedIndex = 218,
  kX86InstIdVpshufhw_ExtendedIndex = 218,
  kX86InstIdVpshuflw_ExtendedIndex = 218,
  kX86InstIdVpsignb_ExtendedIndex = 142,
  kX86InstIdVpsignd_ExtendedIndex = 142,
  kX86InstIdVpsignw_ExtendedIndex = 142,
  kX86InstIdVpslld_ExtendedIndex = 219,
  kX86InstIdVpslldq_ExtendedIndex = 220,
  kX86InstIdVpsllq_ExtendedIndex = 221,
  kX86InstIdVpsllvd_ExtendedIndex = 142,
  kX86InstIdVpsllvq_ExtendedIndex = 160,
  kX86InstIdVpsllw_ExtendedIndex = 222,
  kX86InstIdVpsrad_ExtendedIndex = 223,
  kX86InstIdVpsravd_ExtendedIndex = 142,
  kX86InstIdVpsraw_ExtendedIndex = 224,
  kX86InstIdVpsrld_ExtendedIndex = 225,
  kX86InstIdVpsrldq_ExtendedIndex = 220,
  kX86InstIdVpsrlq_ExtendedIndex = 226,
  kX86InstIdVpsrlvd_ExtendedIndex = 142,
  kX86InstIdVpsrlvq_ExtendedIndex = 160,
  kX86InstIdVpsrlw_ExtendedIndex = 227,
  kX86InstIdVpsubb_ExtendedIndex = 142,
  kX86InstIdVpsubd_ExtendedIndex = 142,
  kX86InstIdVpsubq_ExtendedIndex = 142,
  kX86InstIdVpsubsb_ExtendedIndex = 142,
  kX86InstIdVpsubsw_ExtendedIndex = 142,
  kX86InstIdVpsubusb_ExtendedIndex = 142,
  kX86InstIdVpsubusw_ExtendedIndex = 142,
  kX86InstIdVpsubw_ExtendedIndex = 142,
  kX86InstIdVptest_ExtendedIndex = 152,
  kX86InstIdVpunpckhbw_ExtendedIndex = 142,
  kX86InstIdVpunpckhdq_ExtendedIndex = 142,
  kX86InstIdVpunpckhqdq_ExtendedIndex = 142,
  kX86InstIdVpunpckhwd_ExtendedIndex = 142,
  kX86InstIdVpunpcklbw_ExtendedIndex = 142,
  kX86InstIdVpunpckldq_ExtendedIndex = 142,
  kX86InstIdVpunpcklqdq_ExtendedIndex = 142,
  kX86InstIdVpunpcklwd_ExtendedIndex = 142,
  kX86InstIdVpxor_ExtendedIndex = 142,
  kX86InstIdVrcpps_ExtendedIndex = 152,
  kX86InstIdVrcpss_ExtendedIndex = 143,
  kX86InstIdVroundpd_ExtendedIndex = 218,
  kX86InstIdVroundps_ExtendedIndex = 218,
  kX86InstIdVroundsd_ExtendedIndex = 150,
  kX86InstIdVroundss_ExtendedIndex = 150,
  kX86InstIdVrsqrtps_ExtendedIndex = 152,
  kX86InstIdVrsqrtss_ExtendedIndex = 143,
  kX86InstIdVshufpd_ExtendedIndex = 146,
  kX86InstIdVshufps_ExtendedIndex = 146,
  kX86InstIdVsqrtpd_ExtendedIndex = 152,
  kX86InstIdVsqrtps_ExtendedIndex = 152,
  kX86InstIdVsqrtsd_ExtendedIndex = 143,
  kX86InstIdVsqrtss_ExtendedIndex = 143,
  kX86InstIdVstmxcsr_ExtendedIndex = 171,
  kX86InstIdVsubpd_ExtendedIndex = 142,
  kX86InstIdVsubps_ExtendedIndex = 142,
  kX86InstIdVsubsd_ExtendedIndex = 143,
  kX86InstIdVsubss_ExtendedIndex = 143,
  kX86InstIdVtestpd_ExtendedIndex = 228,
  kX86InstIdVtestps_ExtendedIndex = 228,
  kX86InstIdVucomisd_ExtendedIndex = 144,
  kX86InstIdVucomiss_ExtendedIndex = 144,
  kX86InstIdVunpckhpd_ExtendedIndex = 142,
  kX86InstIdVunpckhps_ExtendedIndex = 142,
  kX86InstIdVunpcklpd_ExtendedIndex = 142,
  kX86InstIdVunpcklps_ExtendedIndex = 142,
  kX86InstIdVxorpd_ExtendedIndex = 142,
  kX86InstIdVxorps_ExtendedIndex = 142,
  kX86InstIdVzeroall_ExtendedIndex = 229,
  kX86InstIdVzeroupper_ExtendedIndex = 229,
  kX86InstIdWrfsbase_ExtendedIndex = 230,
  kX86InstIdWrgsbase_ExtendedIndex = 230,
  kX86InstIdXadd_ExtendedIndex = 231,
  kX86InstIdXchg_ExtendedIndex = 232,
  kX86InstIdXor_ExtendedIndex = 1,
  kX86InstIdXorpd_ExtendedIndex = 2,
  kX86InstIdXorps_ExtendedIndex = 2
};
// ${X86InstData:End}

// Instruction data.
//
// Please rerun tools/src-gendefs.js (by using node.js) to regenerate instruction
// names and extended info tables.
const X86InstInfo _x86InstInfo[] = {
  // Inst-Code                    | Inst-Name          | Inst-Group       | Inst-Flags             | M | Op-Flags[0]         | Op-Flags[1]         | Op-Flags[2]         | Op-Flags[2]         | OpCode[0]       | OpCode[1]       |
  INST(kInstIdNone                , ""                 , G(None)          , F(None)                , 0 , 0                   , 0                   , 0                   , 0                   , 0               , 0               ),
  INST(kX86InstIdAdc              , "adc"              , G(X86Arith)      , F(Lock)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , O_000000(10,2)  , U               ),
  INST(kX86InstIdAdd              , "add"              , G(X86Arith)      , F(Lock)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , O_000000(00,0)  , U               ),
  INST(kX86InstIdAddpd            , "addpd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(58,U)  , U               ),
  INST(kX86InstIdAddps            , "addps"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(58,U)  , U               ),
  INST(kX86InstIdAddsd            , "addsd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(58,U)  , U               ),
  INST(kX86InstIdAddss            , "addss"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(58,U)  , U               ),
  INST(kX86InstIdAddsubpd         , "addsubpd"         , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(D0,U)  , U               ),
  INST(kX86InstIdAddsubps         , "addsubps"         , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(D0,U)  , U               ),
  INST(kX86InstIdAesdec           , "aesdec"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(DE,U)  , U               ),
  INST(kX86InstIdAesdeclast       , "aesdeclast"       , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(DF,U)  , U               ),
  INST(kX86InstIdAesenc           , "aesenc"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(DC,U)  , U               ),
  INST(kX86InstIdAesenclast       , "aesenclast"       , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(DD,U)  , U               ),
  INST(kX86InstIdAesimc           , "aesimc"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(DB,U)  , U               ),
  INST(kX86InstIdAeskeygenassist  , "aeskeygenassist"  , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(DF,U)  , U               ),
  INST(kX86InstIdAnd              , "and"              , G(X86Arith)      , F(Lock)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , O_000000(20,4)  , U               ),
  INST(kX86InstIdAndn             , "andn"             , G(AvxRvm)        , F(None)                , 0 , O(Gqd)              , O(Gqd)              , O(GqdMem)           , U                   , O_000F38(F2,U)  , U               ),
  INST(kX86InstIdAndnpd           , "andnpd"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(55,U)  , U               ),
  INST(kX86InstIdAndnps           , "andnps"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(55,U)  , U               ),
  INST(kX86InstIdAndpd            , "andpd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(54,U)  , U               ),
  INST(kX86InstIdAndps            , "andps"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(54,U)  , U               ),
  INST(kX86InstIdBextr            , "bextr"            , G(AvxRmv)        , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , O(Gqd)              , U                   , O_000F38(F7,U)  , U               ),
  INST(kX86InstIdBlendpd          , "blendpd"          , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(0D,U)  , U               ),
  INST(kX86InstIdBlendps          , "blendps"          , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(0C,U)  , U               ),
  INST(kX86InstIdBlendvpd         , "blendvpd"         , G(ExtRm)         , F(None)|F(Special)     , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(15,U)  , U               ),
  INST(kX86InstIdBlendvps         , "blendvps"         , G(ExtRm)         , F(None)|F(Special)     , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(14,U)  , U               ),
  INST(kX86InstIdBlsi             , "blsi"             , G(AvxVm)         , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , U                   , U                   , O_000F38(F3,3)  , U               ),
  INST(kX86InstIdBlsmsk           , "blsmsk"           , G(AvxVm)         , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , U                   , U                   , O_000F38(F3,2)  , U               ),
  INST(kX86InstIdBlsr             , "blsr"             , G(AvxVm)         , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , U                   , U                   , O_000F38(F3,1)  , U               ),
  INST(kX86InstIdBsf              , "bsf"              , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(BC,U)  , U               ),
  INST(kX86InstIdBsr              , "bsr"              , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(BD,U)  , U               ),
  INST(kX86InstIdBswap            , "bswap"            , G(X86BSwap)      , F(None)                , 0 , O(Gqd)              , U                   , U                   , U                   , O_000F00(C8,U)  , U               ),
  INST(kX86InstIdBt               , "bt"               , G(X86BTest)      , F(Test)                , 0 , O(GqdwMem)          , O(Gqdw)|O(Imm)      , U                   , U                   , O_000F00(A3,U)  , O_000F00(BA,4)  ),
  INST(kX86InstIdBtc              , "btc"              , G(X86BTest)      , F(Lock)                , 0 , O(GqdwMem)          , O(Gqdw)|O(Imm)      , U                   , U                   , O_000F00(BB,U)  , O_000F00(BA,7)  ),
  INST(kX86InstIdBtr              , "btr"              , G(X86BTest)      , F(Lock)                , 0 , O(GqdwMem)          , O(Gqdw)|O(Imm)      , U                   , U                   , O_000F00(B3,U)  , O_000F00(BA,6)  ),
  INST(kX86InstIdBts              , "bts"              , G(X86BTest)      , F(Lock)                , 0 , O(GqdwMem)          , O(Gqdw)|O(Imm)      , U                   , U                   , O_000F00(AB,U)  , O_000F00(BA,5)  ),
  INST(kX86InstIdBzhi             , "bzhi"             , G(AvxRmv)        , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , O(Gqd)              , U                   , O_000F38(F5,U)  , U               ),
  INST(kX86InstIdCall             , "call"             , G(X86Call)       , F(Flow)                , 0 , O(GqdMem)|O(Imm)|O(Label), U              , U                   , U                   , O_000000(FF,2)  , O_000000(E8,U)  ),
  INST(kX86InstIdCbw              , "cbw"              , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_660000(98,U)  , U               ),
  INST(kX86InstIdCdq              , "cdq"              , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(99,U)  , U               ),
  INST(kX86InstIdCdqe             , "cdqe"             , G(X86Op)         , F(None)|F(Special)|F(W), 0 , U                   , U                   , U                   , U                   , O_000000(98,U)  , U               ),
  INST(kX86InstIdClc              , "clc"              , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000000(F8,U)  , U               ),
  INST(kX86InstIdCld              , "cld"              , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000000(FC,U)  , U               ),
  INST(kX86InstIdClflush          , "clflush"          , G(X86M)          , F(None)                , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(AE,7)  , U               ),
  INST(kX86InstIdCmc              , "cmc"              , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000000(F5,U)  , U               ),
  INST(kX86InstIdCmova            , "cmova"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(47,U)  , U               ),
  INST(kX86InstIdCmovae           , "cmovae"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(43,U)  , U               ),
  INST(kX86InstIdCmovb            , "cmovb"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(42,U)  , U               ),
  INST(kX86InstIdCmovbe           , "cmovbe"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(46,U)  , U               ),
  INST(kX86InstIdCmovc            , "cmovc"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(42,U)  , U               ),
  INST(kX86InstIdCmove            , "cmove"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(44,U)  , U               ),
  INST(kX86InstIdCmovg            , "cmovg"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4F,U)  , U               ),
  INST(kX86InstIdCmovge           , "cmovge"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4D,U)  , U               ),
  INST(kX86InstIdCmovl            , "cmovl"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4C,U)  , U               ),
  INST(kX86InstIdCmovle           , "cmovle"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4E,U)  , U               ),
  INST(kX86InstIdCmovna           , "cmovna"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(46,U)  , U               ),
  INST(kX86InstIdCmovnae          , "cmovnae"          , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(42,U)  , U               ),
  INST(kX86InstIdCmovnb           , "cmovnb"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(43,U)  , U               ),
  INST(kX86InstIdCmovnbe          , "cmovnbe"          , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(47,U)  , U               ),
  INST(kX86InstIdCmovnc           , "cmovnc"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(43,U)  , U               ),
  INST(kX86InstIdCmovne           , "cmovne"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(45,U)  , U               ),
  INST(kX86InstIdCmovng           , "cmovng"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4E,U)  , U               ),
  INST(kX86InstIdCmovnge          , "cmovnge"          , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4C,U)  , U               ),
  INST(kX86InstIdCmovnl           , "cmovnl"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4D,U)  , U               ),
  INST(kX86InstIdCmovnle          , "cmovnle"          , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4F,U)  , U               ),
  INST(kX86InstIdCmovno           , "cmovno"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(41,U)  , U               ),
  INST(kX86InstIdCmovnp           , "cmovnp"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4B,U)  , U               ),
  INST(kX86InstIdCmovns           , "cmovns"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(49,U)  , U               ),
  INST(kX86InstIdCmovnz           , "cmovnz"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(45,U)  , U               ),
  INST(kX86InstIdCmovo            , "cmovo"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(40,U)  , U               ),
  INST(kX86InstIdCmovp            , "cmovp"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4A,U)  , U               ),
  INST(kX86InstIdCmovpe           , "cmovpe"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4A,U)  , U               ),
  INST(kX86InstIdCmovpo           , "cmovpo"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(4B,U)  , U               ),
  INST(kX86InstIdCmovs            , "cmovs"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(48,U)  , U               ),
  INST(kX86InstIdCmovz            , "cmovz"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_000F00(44,U)  , U               ),
  INST(kX86InstIdCmp              , "cmp"              , G(X86Arith)      , F(Test)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , O_000000(38,7)  , U               ),
  INST(kX86InstIdCmppd            , "cmppd"            , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F00(C2,U)  , U               ),
  INST(kX86InstIdCmpps            , "cmpps"            , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_000F00(C2,U)  , U               ),
  INST(kX86InstIdCmpsb            , "cmpsb"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(A6,U)  , U               ),
  INST(kX86InstIdCmpsd            , "cmpsd"            , G(Cmpsd)         , F(None)|F(Special)     , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_F20F00(C2,U)  , U               ),
  INST(kX86InstIdCmpsq            , "cmpsq"            , G(X86Op)         , F(None)|F(Special)|F(W), 0 , U                   , U                   , U                   , U                   , O_000000(A7,U)  , U               ),
  INST(kX86InstIdCmpss            , "cmpss"            , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_F30F00(C2,U)  , U               ),
  INST(kX86InstIdCmpsw            , "cmpsw"            , G(X86Op_66H)     , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(A7,U)  , U               ),
  INST(kX86InstIdCmpxchg          , "cmpxchg"          , G(X86RmReg)      , F(Lock)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000F00(B0,U)  , U               ),
  INST(kX86InstIdCmpxchg16b       , "cmpxchg16b"       , G(X86M)          , F(None)|F(Special)|F(W), 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(C7,1)  , U               ),
  INST(kX86InstIdCmpxchg8b        , "cmpxchg8b"        , G(X86M)          , F(None)|F(Special)     , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(C7,1)  , U               ),
  INST(kX86InstIdComisd           , "comisd"           , G(ExtRm)         , F(Test)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(2F,U)  , U               ),
  INST(kX86InstIdComiss           , "comiss"           , G(ExtRm)         , F(Test)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(2F,U)  , U               ),
  INST(kX86InstIdCpuid            , "cpuid"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000F00(A2,U)  , U               ),
  INST(kX86InstIdCqo              , "cqo"              , G(X86Op)         , F(None)|F(Special)|F(W), 0 , U                   , U                   , U                   , U                   , O_000000(99,U)  , U               ),
  INST(kX86InstIdCrc32            , "crc32"            , G(ExtCrc)        , F(None)                , 0 , O(Gqd)              , O(GqdwbMem)         , U                   , U                   , O_F20F38(F0,U)  , U               ),
  INST(kX86InstIdCvtdq2pd         , "cvtdq2pd"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(E6,U)  , U               ),
  INST(kX86InstIdCvtdq2ps         , "cvtdq2ps"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(5B,U)  , U               ),
  INST(kX86InstIdCvtpd2dq         , "cvtpd2dq"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(E6,U)  , U               ),
  INST(kX86InstIdCvtpd2pi         , "cvtpd2pi"         , G(ExtRm)         , F(Move)                , 8 , O(Mm)               , O(XmmMem)           , U                   , U                   , O_660F00(2D,U)  , U               ),
  INST(kX86InstIdCvtpd2ps         , "cvtpd2ps"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(5A,U)  , U               ),
  INST(kX86InstIdCvtpi2pd         , "cvtpi2pd"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(MmMem)            , U                   , U                   , O_660F00(2A,U)  , U               ),
  INST(kX86InstIdCvtpi2ps         , "cvtpi2ps"         , G(ExtRm)         , F(Move)                , 8 , O(Xmm)              , O(MmMem)            , U                   , U                   , O_000F00(2A,U)  , U               ),
  INST(kX86InstIdCvtps2dq         , "cvtps2dq"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(5B,U)  , U               ),
  INST(kX86InstIdCvtps2pd         , "cvtps2pd"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(5A,U)  , U               ),
  INST(kX86InstIdCvtps2pi         , "cvtps2pi"         , G(ExtRm)         , F(Move)                , 8 , O(Mm)               , O(XmmMem)           , U                   , U                   , O_000F00(2D,U)  , U               ),
  INST(kX86InstIdCvtsd2si         , "cvtsd2si"         , G(ExtRm_Q)       , F(Move)                , 8 , O(Gqd)              , O(XmmMem)           , U                   , U                   , O_F20F00(2D,U)  , U               ),
  INST(kX86InstIdCvtsd2ss         , "cvtsd2ss"         , G(ExtRm)         , F(Move)                , 4 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(5A,U)  , U               ),
  INST(kX86InstIdCvtsi2sd         , "cvtsi2sd"         , G(ExtRm_Q)       , F(Move)                , 8 , O(Xmm)              , O(GqdMem)           , U                   , U                   , O_F20F00(2A,U)  , U               ),
  INST(kX86InstIdCvtsi2ss         , "cvtsi2ss"         , G(ExtRm_Q)       , F(Move)                , 4 , O(Xmm)              , O(GqdMem)           , U                   , U                   , O_F30F00(2A,U)  , U               ),
  INST(kX86InstIdCvtss2sd         , "cvtss2sd"         , G(ExtRm)         , F(Move)                , 8 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(5A,U)  , U               ),
  INST(kX86InstIdCvtss2si         , "cvtss2si"         , G(ExtRm_Q)       , F(Move)                , 8 , O(Gqd)              , O(XmmMem)           , U                   , U                   , O_F30F00(2D,U)  , U               ),
  INST(kX86InstIdCvttpd2dq        , "cvttpd2dq"        , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(E6,U)  , U               ),
  INST(kX86InstIdCvttpd2pi        , "cvttpd2pi"        , G(ExtRm)         , F(Move)                , 8 , O(Mm)               , O(XmmMem)           , U                   , U                   , O_660F00(2C,U)  , U               ),
  INST(kX86InstIdCvttps2dq        , "cvttps2dq"        , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(5B,U)  , U               ),
  INST(kX86InstIdCvttps2pi        , "cvttps2pi"        , G(ExtRm)         , F(Move)                , 8 , O(Mm)               , O(XmmMem)           , U                   , U                   , O_000F00(2C,U)  , U               ),
  INST(kX86InstIdCvttsd2si        , "cvttsd2si"        , G(ExtRm_Q)       , F(Move)                , 8 , O(Gqd)              , O(XmmMem)           , U                   , U                   , O_F20F00(2C,U)  , U               ),
  INST(kX86InstIdCvttss2si        , "cvttss2si"        , G(ExtRm_Q)       , F(Move)                , 8 , O(Gqd)              , O(XmmMem)           , U                   , U                   , O_F30F00(2C,U)  , U               ),
  INST(kX86InstIdCwd              , "cwd"              , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_660000(99,U)  , U               ),
  INST(kX86InstIdCwde             , "cwde"             , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(98,U)  , U               ),
  INST(kX86InstIdDaa              , "daa"              , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(27,U)  , U               ),
  INST(kX86InstIdDas              , "das"              , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(2F,U)  , U               ),
  INST(kX86InstIdDec              , "dec"              , G(X86IncDec)     , F(Lock)                , 0 , O(GqdwbMem)         , U                   , U                   , U                   , O_000000(FE,1)  , O_000000(48,U)  ),
  INST(kX86InstIdDiv              , "div"              , G(X86Rm_B)       , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(F6,6)  , U               ),
  INST(kX86InstIdDivpd            , "divpd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(5E,U)  , U               ),
  INST(kX86InstIdDivps            , "divps"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(5E,U)  , U               ),
  INST(kX86InstIdDivsd            , "divsd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(5E,U)  , U               ),
  INST(kX86InstIdDivss            , "divss"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(5E,U)  , U               ),
  INST(kX86InstIdDppd             , "dppd"             , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(41,U)  , U               ),
  INST(kX86InstIdDpps             , "dpps"             , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(40,U)  , U               ),
  INST(kX86InstIdEmms             , "emms"             , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000F00(77,U)  , U               ),
  INST(kX86InstIdEnter            , "enter"            , G(X86Enter)      , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(C8,U)  , U               ),
  INST(kX86InstIdExtractps        , "extractps"        , G(ExtExtract)    , F(Move)                , 8 , O(GqdMem)           , O(Xmm)              , U                   , U                   , O_660F3A(17,U)  , O_660F3A(17,U)  ),
  INST(kX86InstIdF2xm1            , "f2xm1"            , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F0,U)  , U               ),
  INST(kX86InstIdFabs             , "fabs"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9E1,U)  , U               ),
  INST(kX86InstIdFadd             , "fadd"             , G(FpuArith)      , F(Fp)|F(Mem4_8)        , 0 , O(FpMem)            , O(Fp)               , U                   , U                   , O_00_X(C0C0,0)  , U               ),
  INST(kX86InstIdFaddp            , "faddp"            , G(FpuRDef)       , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DEC0,U)  , U               ),
  INST(kX86InstIdFbld             , "fbld"             , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DF,4)  , U               ),
  INST(kX86InstIdFbstp            , "fbstp"            , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DF,6)  , U               ),
  INST(kX86InstIdFchs             , "fchs"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9E0,U)  , U               ),
  INST(kX86InstIdFclex            , "fclex"            , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_9B_X(DBE2,U)  , U               ),
  INST(kX86InstIdFcmovb           , "fcmovb"           , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DAC0,U)  , U               ),
  INST(kX86InstIdFcmovbe          , "fcmovbe"          , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DAD0,U)  , U               ),
  INST(kX86InstIdFcmove           , "fcmove"           , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DAC8,U)  , U               ),
  INST(kX86InstIdFcmovnb          , "fcmovnb"          , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DBC0,U)  , U               ),
  INST(kX86InstIdFcmovnbe         , "fcmovnbe"         , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DBD0,U)  , U               ),
  INST(kX86InstIdFcmovne          , "fcmovne"          , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DBC8,U)  , U               ),
  INST(kX86InstIdFcmovnu          , "fcmovnu"          , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DBD8,U)  , U               ),
  INST(kX86InstIdFcmovu           , "fcmovu"           , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DAD8,U)  , U               ),
  INST(kX86InstIdFcom             , "fcom"             , G(FpuCom)        , F(Fp)                  , 0 , O(Fp)|O(Mem)        , O(Fp)               , U                   , U                   , O_00_X(D0D0,2)  , U               ),
  INST(kX86InstIdFcomi            , "fcomi"            , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DBF0,U)  , U               ),
  INST(kX86InstIdFcomip           , "fcomip"           , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DFF0,U)  , U               ),
  INST(kX86InstIdFcomp            , "fcomp"            , G(FpuCom)        , F(Fp)                  , 0 , O(Fp)|O(Mem)        , O(Fp)               , U                   , U                   , O_00_X(D8D8,3)  , U               ),
  INST(kX86InstIdFcompp           , "fcompp"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(DED9,U)  , U               ),
  INST(kX86InstIdFcos             , "fcos"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9FF,U)  , U               ),
  INST(kX86InstIdFdecstp          , "fdecstp"          , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F6,U)  , U               ),
  INST(kX86InstIdFdiv             , "fdiv"             , G(FpuArith)      , F(Fp)|F(Mem4_8)        , 0 , O(FpMem)            , O(Fp)               , U                   , U                   , O_00_X(F0F8,6)  , U               ),
  INST(kX86InstIdFdivp            , "fdivp"            , G(FpuRDef)       , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DEF8,U)  , U               ),
  INST(kX86InstIdFdivr            , "fdivr"            , G(FpuArith)      , F(Fp)|F(Mem4_8)        , 0 , O(FpMem)            , O(Fp)               , U                   , U                   , O_00_X(F8F0,7)  , U               ),
  INST(kX86InstIdFdivrp           , "fdivrp"           , G(FpuRDef)       , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DEF0,U)  , U               ),
  INST(kX86InstIdFemms            , "femms"            , G(X86Op)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_000F00(0E,U)  , U               ),
  INST(kX86InstIdFfree            , "ffree"            , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DDC0,U)  , U               ),
  INST(kX86InstIdFiadd            , "fiadd"            , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DA,0)  , U               ),
  INST(kX86InstIdFicom            , "ficom"            , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DA,2)  , U               ),
  INST(kX86InstIdFicomp           , "ficomp"           , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DA,3)  , U               ),
  INST(kX86InstIdFidiv            , "fidiv"            , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DA,6)  , U               ),
  INST(kX86InstIdFidivr           , "fidivr"           , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DA,7)  , U               ),
  INST(kX86InstIdFild             , "fild"             , G(FpuM)          , F(Fp)|F(Mem2_4_8)      , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DB,0)  , O_000000(DF,5)  ),
  INST(kX86InstIdFimul            , "fimul"            , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DA,1)  , U               ),
  INST(kX86InstIdFincstp          , "fincstp"          , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F7,U)  , U               ),
  INST(kX86InstIdFinit            , "finit"            , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_9B_X(DBE3,U)  , U               ),
  INST(kX86InstIdFist             , "fist"             , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DB,2)  , U               ),
  INST(kX86InstIdFistp            , "fistp"            , G(FpuM)          , F(Fp)|F(Mem2_4_8)      , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DB,3)  , O_000000(DF,7)  ),
  INST(kX86InstIdFisttp           , "fisttp"           , G(FpuM)          , F(Fp)|F(Mem2_4_8)      , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DB,1)  , O_000000(DD,1)  ),
  INST(kX86InstIdFisub            , "fisub"            , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DA,4)  , U               ),
  INST(kX86InstIdFisubr           , "fisubr"           , G(FpuM)          , F(Fp)|F(Mem2_4)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DA,5)  , U               ),
  INST(kX86InstIdFld              , "fld"              , G(FpuFldFst)     , F(Fp)|F(Mem4_8_10)     , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(D9,0)  , O_000000(DB,5)  ),
  INST(kX86InstIdFld1             , "fld1"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9E8,U)  , U               ),
  INST(kX86InstIdFldcw            , "fldcw"            , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(D9,5)  , U               ),
  INST(kX86InstIdFldenv           , "fldenv"           , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(D9,4)  , U               ),
  INST(kX86InstIdFldl2e           , "fldl2e"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9EA,U)  , U               ),
  INST(kX86InstIdFldl2t           , "fldl2t"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9E9,U)  , U               ),
  INST(kX86InstIdFldlg2           , "fldlg2"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9EC,U)  , U               ),
  INST(kX86InstIdFldln2           , "fldln2"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9ED,U)  , U               ),
  INST(kX86InstIdFldpi            , "fldpi"            , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9EB,U)  , U               ),
  INST(kX86InstIdFldz             , "fldz"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9EE,U)  , U               ),
  INST(kX86InstIdFmul             , "fmul"             , G(FpuArith)      , F(Fp)|F(Mem4_8)        , 0 , O(FpMem)            , O(Fp)               , U                   , U                   , O_00_X(C8C8,1)  , U               ),
  INST(kX86InstIdFmulp            , "fmulp"            , G(FpuRDef)       , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DEC8,U)  , U               ),
  INST(kX86InstIdFnclex           , "fnclex"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(DBE2,U)  , U               ),
  INST(kX86InstIdFninit           , "fninit"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(DBE3,U)  , U               ),
  INST(kX86InstIdFnop             , "fnop"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9D0,U)  , U               ),
  INST(kX86InstIdFnsave           , "fnsave"           , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DD,6)  , U               ),
  INST(kX86InstIdFnstcw           , "fnstcw"           , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(D9,7)  , U               ),
  INST(kX86InstIdFnstenv          , "fnstenv"          , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(D9,6)  , U               ),
  INST(kX86InstIdFnstsw           , "fnstsw"           , G(FpuStsw)       , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DD,7)  , O_00_X(DFE0,U)  ),
  INST(kX86InstIdFpatan           , "fpatan"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F3,U)  , U               ),
  INST(kX86InstIdFprem            , "fprem"            , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F8,U)  , U               ),
  INST(kX86InstIdFprem1           , "fprem1"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F5,U)  , U               ),
  INST(kX86InstIdFptan            , "fptan"            , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F2,U)  , U               ),
  INST(kX86InstIdFrndint          , "frndint"          , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9FC,U)  , U               ),
  INST(kX86InstIdFrstor           , "frstor"           , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(DD,4)  , U               ),
  INST(kX86InstIdFsave            , "fsave"            , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_9B0000(DD,6)  , U               ),
  INST(kX86InstIdFscale           , "fscale"           , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9FD,U)  , U               ),
  INST(kX86InstIdFsin             , "fsin"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9FE,U)  , U               ),
  INST(kX86InstIdFsincos          , "fsincos"          , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9FB,U)  , U               ),
  INST(kX86InstIdFsqrt            , "fsqrt"            , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9FA,U)  , U               ),
  INST(kX86InstIdFst              , "fst"              , G(FpuFldFst)     , F(Fp)|F(Mem4_8)        , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(D9,2)  , U               ),
  INST(kX86InstIdFstcw            , "fstcw"            , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_9B0000(D9,7)  , U               ),
  INST(kX86InstIdFstenv           , "fstenv"           , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_9B0000(D9,6)  , U               ),
  INST(kX86InstIdFstp             , "fstp"             , G(FpuFldFst)     , F(Fp)|F(Mem4_8_10)     , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(D9,3)  , O_000000(DB,7)  ),
  INST(kX86InstIdFstsw            , "fstsw"            , G(FpuStsw)       , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_9B0000(DD,7)  , O_9B_X(DFE0,U)  ),
  INST(kX86InstIdFsub             , "fsub"             , G(FpuArith)      , F(Fp)|F(Mem4_8)        , 0 , O(FpMem)            , O(Fp)               , U                   , U                   , O_00_X(E0E8,4)  , U               ),
  INST(kX86InstIdFsubp            , "fsubp"            , G(FpuRDef)       , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DEE8,U)  , U               ),
  INST(kX86InstIdFsubr            , "fsubr"            , G(FpuArith)      , F(Fp)|F(Mem4_8)        , 0 , O(FpMem)            , O(Fp)               , U                   , U                   , O_00_X(E8E0,5)  , U               ),
  INST(kX86InstIdFsubrp           , "fsubrp"           , G(FpuRDef)       , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DEE0,U)  , U               ),
  INST(kX86InstIdFtst             , "ftst"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9E4,U)  , U               ),
  INST(kX86InstIdFucom            , "fucom"            , G(FpuRDef)       , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DDE0,U)  , U               ),
  INST(kX86InstIdFucomi           , "fucomi"           , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DBE8,U)  , U               ),
  INST(kX86InstIdFucomip          , "fucomip"          , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DFE8,U)  , U               ),
  INST(kX86InstIdFucomp           , "fucomp"           , G(FpuRDef)       , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(DDE8,U)  , U               ),
  INST(kX86InstIdFucompp          , "fucompp"          , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(DAE9,U)  , U               ),
  INST(kX86InstIdFwait            , "fwait"            , G(X86Op)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_000000(DB,U)  , U               ),
  INST(kX86InstIdFxam             , "fxam"             , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9E5,U)  , U               ),
  INST(kX86InstIdFxch             , "fxch"             , G(FpuR)          , F(Fp)                  , 0 , O(Fp)               , U                   , U                   , U                   , O_00_X(D9C8,U)  , U               ),
  INST(kX86InstIdFxrstor          , "fxrstor"          , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(AE,1)  , U               ),
  INST(kX86InstIdFxsave           , "fxsave"           , G(X86M)          , F(Fp)                  , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(AE,0)  , U               ),
  INST(kX86InstIdFxtract          , "fxtract"          , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F4,U)  , U               ),
  INST(kX86InstIdFyl2x            , "fyl2x"            , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F1,U)  , U               ),
  INST(kX86InstIdFyl2xp1          , "fyl2xp1"          , G(FpuOp)         , F(Fp)                  , 0 , U                   , U                   , U                   , U                   , O_00_X(D9F9,U)  , U               ),
  INST(kX86InstIdHaddpd           , "haddpd"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(7C,U)  , U               ),
  INST(kX86InstIdHaddps           , "haddps"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(7C,U)  , U               ),
  INST(kX86InstIdHsubpd           , "hsubpd"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(7D,U)  , U               ),
  INST(kX86InstIdHsubps           , "hsubps"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(7D,U)  , U               ),
  INST(kX86InstIdIdiv             , "idiv"             , G(X86Rm_B)       , F(None)|F(Special)     , 0 , 0                   , 0                   , U                   , U                   , O_000000(F6,7)  , U               ),
  INST(kX86InstIdImul             , "imul"             , G(X86Imul)       , F(None)|F(Special)     , 0 , 0                   , 0                   , U                   , U                   , U               , U               ),
  INST(kX86InstIdInc              , "inc"              , G(X86IncDec)     , F(Lock)                , 0 , O(GqdwbMem)         , U                   , U                   , U                   , O_000000(FE,0)  , O_000000(40,U)  ),
  INST(kX86InstIdInsertps         , "insertps"         , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(21,U)  , U               ),
  INST(kX86InstIdInt              , "int"              , G(X86Int)        , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000000(CC,U)  , U               ),
  INST(kX86InstIdJa               , "ja"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(77,U)  , U               ),
  INST(kX86InstIdJae              , "jae"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(73,U)  , U               ),
  INST(kX86InstIdJb               , "jb"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(72,U)  , U               ),
  INST(kX86InstIdJbe              , "jbe"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(76,U)  , U               ),
  INST(kX86InstIdJc               , "jc"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(72,U)  , U               ),
  INST(kX86InstIdJe               , "je"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(74,U)  , U               ),
  INST(kX86InstIdJg               , "jg"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7F,U)  , U               ),
  INST(kX86InstIdJge              , "jge"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7D,U)  , U               ),
  INST(kX86InstIdJl               , "jl"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7C,U)  , U               ),
  INST(kX86InstIdJle              , "jle"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7E,U)  , U               ),
  INST(kX86InstIdJna              , "jna"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(76,U)  , U               ),
  INST(kX86InstIdJnae             , "jnae"             , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(72,U)  , U               ),
  INST(kX86InstIdJnb              , "jnb"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(73,U)  , U               ),
  INST(kX86InstIdJnbe             , "jnbe"             , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(77,U)  , U               ),
  INST(kX86InstIdJnc              , "jnc"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(73,U)  , U               ),
  INST(kX86InstIdJne              , "jne"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(75,U)  , U               ),
  INST(kX86InstIdJng              , "jng"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7E,U)  , U               ),
  INST(kX86InstIdJnge             , "jnge"             , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7C,U)  , U               ),
  INST(kX86InstIdJnl              , "jnl"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7D,U)  , U               ),
  INST(kX86InstIdJnle             , "jnle"             , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7F,U)  , U               ),
  INST(kX86InstIdJno              , "jno"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(71,U)  , U               ),
  INST(kX86InstIdJnp              , "jnp"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7B,U)  , U               ),
  INST(kX86InstIdJns              , "jns"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(79,U)  , U               ),
  INST(kX86InstIdJnz              , "jnz"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(75,U)  , U               ),
  INST(kX86InstIdJo               , "jo"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(70,U)  , U               ),
  INST(kX86InstIdJp               , "jp"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7A,U)  , U               ),
  INST(kX86InstIdJpe              , "jpe"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7A,U)  , U               ),
  INST(kX86InstIdJpo              , "jpo"              , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(7B,U)  , U               ),
  INST(kX86InstIdJs               , "js"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(78,U)  , U               ),
  INST(kX86InstIdJz               , "jz"               , G(X86Jcc)        , F(Flow)                , 0 , O(Label)            , U                   , U                   , U                   , O_000000(74,U)  , U               ),
  INST(kX86InstIdJecxz            , "jecxz"            , G(X86Jecxz)      , F(Flow)|F(Special)     , 0 , O(Gqdw)             , O(Label)            , U                   , U                   , O_000000(E3,U)  , U               ),
  INST(kX86InstIdJmp              , "jmp"              , G(X86Jmp)        , F(Flow)                , 0 , O(Imm)|O(Label)     , U                   , U                   , U                   , O_000000(FF,4)  , O_000000(E9,U)  ),
  INST(kX86InstIdLahf             , "lahf"             , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(9F,U)  , U               ),
  INST(kX86InstIdLddqu            , "lddqu"            , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(Mem)              , U                   , U                   , O_F20F00(F0,U)  , U               ),
  INST(kX86InstIdLdmxcsr          , "ldmxcsr"          , G(X86M)          , F(None)                , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(AE,2)  , U               ),
  INST(kX86InstIdLea              , "lea"              , G(X86Lea)        , F(Move)                , 0 , O(Gqd)              , O(Mem)              , U                   , U                   , O_000000(8D,U)  , U               ),
  INST(kX86InstIdLeave            , "leave"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(C9,U)  , U               ),
  INST(kX86InstIdLfence           , "lfence"           , G(ExtFence)      , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000F00(AE,5)  , U               ),
  INST(kX86InstIdLodsb            , "lodsb"            , G(X86Op)         , F(Move)|F(Special)     , 1 , U                   , U                   , U                   , U                   , O_000000(AC,U)  , U               ),
  INST(kX86InstIdLodsd            , "lodsd"            , G(X86Op)         , F(Move)|F(Special)     , 4 , U                   , U                   , U                   , U                   , O_000000(AD,U)  , U               ),
  INST(kX86InstIdLodsq            , "lodsq"            , G(X86Op)         , F(Move)|F(Special)|F(W), 8 , U                   , U                   , U                   , U                   , O_000000(AD,U)  , U               ),
  INST(kX86InstIdLodsw            , "lodsw"            , G(X86Op_66H)     , F(Move)|F(Special)     , 2 , U                   , U                   , U                   , U                   , O_000000(AD,U)  , U               ),
  INST(kX86InstIdLzcnt            , "lzcnt"            , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_F30F00(BD,U)  , U               ),
  INST(kX86InstIdMaskmovdqu       , "maskmovdqu"       , G(ExtRm)         , F(None)|F(Special)     , 0 , O(Xmm)              , O(Xmm)              , U                   , U                   , O_660F00(57,U)  , U               ),
  INST(kX86InstIdMaskmovq         , "maskmovq"         , G(ExtRm)         , F(None)|F(Special)     , 0 , O(Mm)               , O(Mm)               , U                   , U                   , O_000F00(F7,U)  , U               ),
  INST(kX86InstIdMaxpd            , "maxpd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(5F,U)  , U               ),
  INST(kX86InstIdMaxps            , "maxps"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(5F,U)  , U               ),
  INST(kX86InstIdMaxsd            , "maxsd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(5F,U)  , U               ),
  INST(kX86InstIdMaxss            , "maxss"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(5F,U)  , U               ),
  INST(kX86InstIdMfence           , "mfence"           , G(ExtFence)      , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000F00(AE,6)  , U               ),
  INST(kX86InstIdMinpd            , "minpd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(5D,U)  , U               ),
  INST(kX86InstIdMinps            , "minps"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(5D,U)  , U               ),
  INST(kX86InstIdMinsd            , "minsd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(5D,U)  , U               ),
  INST(kX86InstIdMinss            , "minss"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(5D,U)  , U               ),
  INST(kX86InstIdMonitor          , "monitor"          , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000F01(C8,U)  , U               ),
  INST(kX86InstIdMov              , "mov"              , G(X86Mov)        , F(Move)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , U               , U               ),
  INST(kX86InstIdMovPtr           , "mov_ptr"          , G(X86MovPtr)     , F(Move)|F(Special)     , 0 , O(Gqdwb)            , O(Imm)              , U                   , U                   , O_000000(A0,U)  , O_000000(A2,U)  ),
  INST(kX86InstIdMovapd           , "movapd"           , G(ExtMov)        , F(Move)                , 16, O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_660F00(28,U)  , O_660F00(29,U)  ),
  INST(kX86InstIdMovaps           , "movaps"           , G(ExtMov)        , F(Move)                , 16, O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_000F00(28,U)  , O_000F00(29,U)  ),
  INST(kX86InstIdMovbe            , "movbe"            , G(ExtMovBe)      , F(Move)                , 0 , O(GqdwMem)          , O(GqdwMem)          , U                   , U                   , O_000F38(F0,U)  , O_000F38(F1,U)  ),
  INST(kX86InstIdMovd             , "movd"             , G(ExtMovD)       , F(Move)                , 16, O(Gd)|O(MmXmmMem)   , O(Gd)|O(MmXmmMem)   , U                   , U                   , O_000F00(6E,U)  , O_000F00(7E,U)  ),
  INST(kX86InstIdMovddup          , "movddup"          , G(ExtMov)        , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(12,U)  , U               ),
  INST(kX86InstIdMovdq2q          , "movdq2q"          , G(ExtMov)        , F(Move)                , 8 , O(Mm)               , O(Xmm)              , U                   , U                   , O_F20F00(D6,U)  , U               ),
  INST(kX86InstIdMovdqa           , "movdqa"           , G(ExtMov)        , F(Move)                , 16, O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_660F00(6F,U)  , O_660F00(7F,U)  ),
  INST(kX86InstIdMovdqu           , "movdqu"           , G(ExtMov)        , F(Move)                , 16, O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_F30F00(6F,U)  , O_F30F00(7F,U)  ),
  INST(kX86InstIdMovhlps          , "movhlps"          , G(ExtMov)        , F(Move)                , 8 , O(Xmm)              , O(Xmm)              , U                   , U                   , O_000F00(12,U)  , U               ),
  INST(kX86InstIdMovhpd           , "movhpd"           , G(ExtMov)        , F(None)                , 0 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_660F00(16,U)  , O_660F00(17,U)  ),
  INST(kX86InstIdMovhps           , "movhps"           , G(ExtMov)        , F(None)                , 0 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_000F00(16,U)  , O_000F00(17,U)  ),
  INST(kX86InstIdMovlhps          , "movlhps"          , G(ExtMov)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , U                   , U                   , O_000F00(16,U)  , U               ),
  INST(kX86InstIdMovlpd           , "movlpd"           , G(ExtMov)        , F(Move)                , 8 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_660F00(12,U)  , O_660F00(13,U)  ),
  INST(kX86InstIdMovlps           , "movlps"           , G(ExtMov)        , F(Move)                , 8 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_000F00(12,U)  , O_000F00(13,U)  ),
  INST(kX86InstIdMovmskpd         , "movmskpd"         , G(ExtMovNoRexW)  , F(Move)                , 8 , O(Gqd)              , O(Xmm)              , U                   , U                   , O_660F00(50,U)  , U               ),
  INST(kX86InstIdMovmskps         , "movmskps"         , G(ExtMovNoRexW)  , F(Move)                , 8 , O(Gqd)              , O(Xmm)              , U                   , U                   , O_000F00(50,U)  , U               ),
  INST(kX86InstIdMovntdq          , "movntdq"          , G(ExtMov)        , F(Move)                , 16, O(Mem)              , O(Xmm)              , U                   , U                   , U               , O_660F00(E7,U)  ),
  INST(kX86InstIdMovntdqa         , "movntdqa"         , G(ExtMov)        , F(Move)                , 16, O(Xmm)              , O(Mem)              , U                   , U                   , O_660F38(2A,U)  , U               ),
  INST(kX86InstIdMovnti           , "movnti"           , G(ExtMov)        , F(Move)                , 8 , O(Mem)              , O(Gqd)              , U                   , U                   , U               , O_000F00(C3,U)  ),
  INST(kX86InstIdMovntpd          , "movntpd"          , G(ExtMov)        , F(Move)                , 16, O(Mem)              , O(Xmm)              , U                   , U                   , U               , O_660F00(2B,U)  ),
  INST(kX86InstIdMovntps          , "movntps"          , G(ExtMov)        , F(Move)                , 16, O(Mem)              , O(Xmm)              , U                   , U                   , U               , O_000F00(2B,U)  ),
  INST(kX86InstIdMovntq           , "movntq"           , G(ExtMov)        , F(Move)                , 8 , O(Mem)              , O(Mm)               , U                   , U                   , U               , O_000F00(E7,U)  ),
  INST(kX86InstIdMovq             , "movq"             , G(ExtMovQ)       , F(Move)                , 16, O(Gq)|O(MmXmmMem)   , O(Gq)|O(MmXmmMem)   , U                   , U                   , U               , U               ),
  INST(kX86InstIdMovq2dq          , "movq2dq"          , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(Mm)               , U                   , U                   , O_F30F00(D6,U)  , U               ),
  INST(kX86InstIdMovsb            , "movsb"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(A4,U)  , U               ),
  INST(kX86InstIdMovsd            , "movsd"            , G(Movsd)         , F(Move)|F(Special)|F(Z), 8 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_F20F00(10,U)  , O_F20F00(11,U)  ),
  INST(kX86InstIdMovshdup         , "movshdup"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(16,U)  , U               ),
  INST(kX86InstIdMovsldup         , "movsldup"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(12,U)  , U               ),
  INST(kX86InstIdMovsq            , "movsq"            , G(X86Op)         , F(None)|F(Special)|F(W), 0 , U                   , U                   , U                   , U                   , O_000000(A5,U)  , U               ),
  INST(kX86InstIdMovss            , "movss"            , G(ExtMov)        , F(Move)           |F(Z), 4 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_F30F00(10,U)  , O_F30F00(11,U)  ),
  INST(kX86InstIdMovsw            , "movsw"            , G(X86Op_66H)     , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(A5,U)  , U               ),
  INST(kX86InstIdMovsx            , "movsx"            , G(X86MovSxZx)    , F(Move)                , 0 , O(Gqdw)             , O(GwbMem)           , U                   , U                   , O_000F00(BE,U)  , U               ),
  INST(kX86InstIdMovsxd           , "movsxd"           , G(X86MovSxd)     , F(Move)                , 0 , O(Gq)               , O(GdMem)            , U                   , U                   , O_000000(63,U)  , U               ),
  INST(kX86InstIdMovupd           , "movupd"           , G(ExtMov)        , F(Move)                , 16, O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_660F00(10,U)  , O_660F00(11,U)  ),
  INST(kX86InstIdMovups           , "movups"           , G(ExtMov)        , F(Move)                , 16, O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_000F00(10,U)  , O_000F00(11,U)  ),
  INST(kX86InstIdMovzx            , "movzx"            , G(X86MovSxZx)    , F(Move)                , 0 , O(Gqdw)             , O(GwbMem)           , U                   , U                   , O_000F00(B6,U)  , U               ),
  INST(kX86InstIdMpsadbw          , "mpsadbw"          , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(42,U)  , U               ),
  INST(kX86InstIdMul              , "mul"              , G(X86Rm_B)       , F(None)|F(Special)     , 0 , 0                   , 0                   , U                   , U                   , O_000000(F6,4)  , U               ),
  INST(kX86InstIdMulpd            , "mulpd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(59,U)  , U               ),
  INST(kX86InstIdMulps            , "mulps"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(59,U)  , U               ),
  INST(kX86InstIdMulsd            , "mulsd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(59,U)  , U               ),
  INST(kX86InstIdMulss            , "mulss"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(59,U)  , U               ),
  INST(kX86InstIdMulx             , "mulx"             , G(AvxRvm)        , F(None)                , 0 , O(Gqd)              , O(Gqd)              , O(GqdMem)           , U                   , O_F20F38(F6,U)  , U               ),
  INST(kX86InstIdMwait            , "mwait"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000F01(C9,U)  , U               ),
  INST(kX86InstIdNeg              , "neg"              , G(X86Rm_B)       , F(Lock)                , 0 , O(GqdwbMem)         , U                   , U                   , U                   , O_000000(F6,3)  , U               ),
  INST(kX86InstIdNop              , "nop"              , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000000(90,U)  , U               ),
  INST(kX86InstIdNot              , "not"              , G(X86Rm_B)       , F(Lock)                , 0 , O(GqdwbMem)         , U                   , U                   , U                   , O_000000(F6,2)  , U               ),
  INST(kX86InstIdOr               , "or"               , G(X86Arith)      , F(Lock)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , O_000000(08,1)  , U               ),
  INST(kX86InstIdOrpd             , "orpd"             , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(56,U)  , U               ),
  INST(kX86InstIdOrps             , "orps"             , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(56,U)  , U               ),
  INST(kX86InstIdPabsb            , "pabsb"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(1C,U)  , U               ),
  INST(kX86InstIdPabsd            , "pabsd"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(1E,U)  , U               ),
  INST(kX86InstIdPabsw            , "pabsw"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(1D,U)  , U               ),
  INST(kX86InstIdPackssdw         , "packssdw"         , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(6B,U)  , U               ),
  INST(kX86InstIdPacksswb         , "packsswb"         , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(63,U)  , U               ),
  INST(kX86InstIdPackusdw         , "packusdw"         , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(2B,U)  , U               ),
  INST(kX86InstIdPackuswb         , "packuswb"         , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(67,U)  , U               ),
  INST(kX86InstIdPaddb            , "paddb"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(FC,U)  , U               ),
  INST(kX86InstIdPaddd            , "paddd"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(FE,U)  , U               ),
  INST(kX86InstIdPaddq            , "paddq"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(D4,U)  , U               ),
  INST(kX86InstIdPaddsb           , "paddsb"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(EC,U)  , U               ),
  INST(kX86InstIdPaddsw           , "paddsw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(ED,U)  , U               ),
  INST(kX86InstIdPaddusb          , "paddusb"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(DC,U)  , U               ),
  INST(kX86InstIdPaddusw          , "paddusw"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(DD,U)  , U               ),
  INST(kX86InstIdPaddw            , "paddw"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(FD,U)  , U               ),
  INST(kX86InstIdPalignr          , "palignr"          , G(ExtRmi_P)      , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , O(Imm)              , U                   , O_000F3A(0F,U)  , U               ),
  INST(kX86InstIdPand             , "pand"             , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(DB,U)  , U               ),
  INST(kX86InstIdPandn            , "pandn"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(DF,U)  , U               ),
  INST(kX86InstIdPause            , "pause"            , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_F30000(90,U)  , U               ),
  INST(kX86InstIdPavgb            , "pavgb"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(E0,U)  , U               ),
  INST(kX86InstIdPavgw            , "pavgw"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(E3,U)  , U               ),
  INST(kX86InstIdPblendvb         , "pblendvb"         , G(ExtRm)         , F(None)|F(Special)     , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(10,U)  , U               ),
  INST(kX86InstIdPblendw          , "pblendw"          , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(0E,U)  , U               ),
  INST(kX86InstIdPclmulqdq        , "pclmulqdq"        , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(44,U)  , U               ),
  INST(kX86InstIdPcmpeqb          , "pcmpeqb"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(74,U)  , U               ),
  INST(kX86InstIdPcmpeqd          , "pcmpeqd"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(76,U)  , U               ),
  INST(kX86InstIdPcmpeqq          , "pcmpeqq"          , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(29,U)  , U               ),
  INST(kX86InstIdPcmpeqw          , "pcmpeqw"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(75,U)  , U               ),
  INST(kX86InstIdPcmpestri        , "pcmpestri"        , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(61,U)  , U               ),
  INST(kX86InstIdPcmpestrm        , "pcmpestrm"        , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(60,U)  , U               ),
  INST(kX86InstIdPcmpgtb          , "pcmpgtb"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(64,U)  , U               ),
  INST(kX86InstIdPcmpgtd          , "pcmpgtd"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(66,U)  , U               ),
  INST(kX86InstIdPcmpgtq          , "pcmpgtq"          , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(37,U)  , U               ),
  INST(kX86InstIdPcmpgtw          , "pcmpgtw"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(65,U)  , U               ),
  INST(kX86InstIdPcmpistri        , "pcmpistri"        , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(63,U)  , U               ),
  INST(kX86InstIdPcmpistrm        , "pcmpistrm"        , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(62,U)  , U               ),
  INST(kX86InstIdPdep             , "pdep"             , G(AvxRvm)        , F(None)                , 0 , O(Gqd)              , O(Gqd)              , O(GqdMem)           , U                   , O_F20F38(F5,U)  , U               ),
  INST(kX86InstIdPext             , "pext"             , G(AvxRvm)        , F(None)                , 0 , O(Gqd)              , O(Gqd)              , O(GqdMem)           , U                   , O_F30F38(F5,U)  , U               ),
  INST(kX86InstIdPextrb           , "pextrb"           , G(ExtExtract)    , F(Move)                , 8 , O(Gd)|O(Gb)|O(Mem)  , O(Xmm)              , U                   , U                   , O_000F3A(14,U)  , O_000F3A(14,U)  ),
  INST(kX86InstIdPextrd           , "pextrd"           , G(ExtExtract)    , F(Move)                , 8 , O(GdMem)            , O(Xmm)              , U                   , U                   , O_000F3A(16,U)  , O_000F3A(16,U)  ),
  INST(kX86InstIdPextrq           , "pextrq"           , G(ExtExtract)    , F(Move)           |F(W), 8 , O(GqdMem)           , O(Xmm)              , U                   , U                   , O_000F3A(16,U)  , O_000F3A(16,U)  ),
  INST(kX86InstIdPextrw           , "pextrw"           , G(ExtExtract)    , F(Move)                , 8 , O(GdMem)            , O(MmXmm)            , U                   , U                   , O_000F00(C5,U)  , O_000F3A(15,U)  ),
  INST(kX86InstIdPf2id            , "pf2id"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(1D,U)  , U               ),
  INST(kX86InstIdPf2iw            , "pf2iw"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(1C,U)  , U               ),
  INST(kX86InstIdPfacc            , "pfacc"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(AE,U)  , U               ),
  INST(kX86InstIdPfadd            , "pfadd"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(9E,U)  , U               ),
  INST(kX86InstIdPfcmpeq          , "pfcmpeq"          , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(B0,U)  , U               ),
  INST(kX86InstIdPfcmpge          , "pfcmpge"          , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(90,U)  , U               ),
  INST(kX86InstIdPfcmpgt          , "pfcmpgt"          , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(A0,U)  , U               ),
  INST(kX86InstIdPfmax            , "pfmax"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(A4,U)  , U               ),
  INST(kX86InstIdPfmin            , "pfmin"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(94,U)  , U               ),
  INST(kX86InstIdPfmul            , "pfmul"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(B4,U)  , U               ),
  INST(kX86InstIdPfnacc           , "pfnacc"           , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(8A,U)  , U               ),
  INST(kX86InstIdPfpnacc          , "pfpnacc"          , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(8E,U)  , U               ),
  INST(kX86InstIdPfrcp            , "pfrcp"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(96,U)  , U               ),
  INST(kX86InstIdPfrcpit1         , "pfrcpit1"         , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(A6,U)  , U               ),
  INST(kX86InstIdPfrcpit2         , "pfrcpit2"         , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(B6,U)  , U               ),
  INST(kX86InstIdPfrsqit1         , "pfrsqit1"         , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(A7,U)  , U               ),
  INST(kX86InstIdPfrsqrt          , "pfrsqrt"          , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(97,U)  , U               ),
  INST(kX86InstIdPfsub            , "pfsub"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(9A,U)  , U               ),
  INST(kX86InstIdPfsubr           , "pfsubr"           , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(AA,U)  , U               ),
  INST(kX86InstIdPhaddd           , "phaddd"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(02,U)  , U               ),
  INST(kX86InstIdPhaddsw          , "phaddsw"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(03,U)  , U               ),
  INST(kX86InstIdPhaddw           , "phaddw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(01,U)  , U               ),
  INST(kX86InstIdPhminposuw       , "phminposuw"       , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(41,U)  , U               ),
  INST(kX86InstIdPhsubd           , "phsubd"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(06,U)  , U               ),
  INST(kX86InstIdPhsubsw          , "phsubsw"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(07,U)  , U               ),
  INST(kX86InstIdPhsubw           , "phsubw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(05,U)  , U               ),
  INST(kX86InstIdPi2fd            , "pi2fd"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(0D,U)  , U               ),
  INST(kX86InstIdPi2fw            , "pi2fw"            , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(0C,U)  , U               ),
  INST(kX86InstIdPinsrb           , "pinsrb"           , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(GdMem)            , O(Imm)              , U                   , O_660F3A(20,U)  , U               ),
  INST(kX86InstIdPinsrd           , "pinsrd"           , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(GdMem)            , O(Imm)              , U                   , O_660F3A(22,U)  , U               ),
  INST(kX86InstIdPinsrq           , "pinsrq"           , G(ExtRmi)        , F(None)           |F(W), 0 , O(Xmm)              , O(GqMem)            , O(Imm)              , U                   , O_660F3A(22,U)  , U               ),
  INST(kX86InstIdPinsrw           , "pinsrw"           , G(ExtRmi_P)      , F(None)                , 0 , O(MmXmm)            , O(GdMem)            , O(Imm)              , U                   , O_000F00(C4,U)  , U               ),
  INST(kX86InstIdPmaddubsw        , "pmaddubsw"        , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(04,U)  , U               ),
  INST(kX86InstIdPmaddwd          , "pmaddwd"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(F5,U)  , U               ),
  INST(kX86InstIdPmaxsb           , "pmaxsb"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(3C,U)  , U               ),
  INST(kX86InstIdPmaxsd           , "pmaxsd"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(3D,U)  , U               ),
  INST(kX86InstIdPmaxsw           , "pmaxsw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(EE,U)  , U               ),
  INST(kX86InstIdPmaxub           , "pmaxub"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(DE,U)  , U               ),
  INST(kX86InstIdPmaxud           , "pmaxud"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(3F,U)  , U               ),
  INST(kX86InstIdPmaxuw           , "pmaxuw"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(3E,U)  , U               ),
  INST(kX86InstIdPminsb           , "pminsb"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(38,U)  , U               ),
  INST(kX86InstIdPminsd           , "pminsd"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(39,U)  , U               ),
  INST(kX86InstIdPminsw           , "pminsw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(EA,U)  , U               ),
  INST(kX86InstIdPminub           , "pminub"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(DA,U)  , U               ),
  INST(kX86InstIdPminud           , "pminud"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(3B,U)  , U               ),
  INST(kX86InstIdPminuw           , "pminuw"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(3A,U)  , U               ),
  INST(kX86InstIdPmovmskb         , "pmovmskb"         , G(ExtRm_PQ)      , F(Move)                , 8 , O(Gqd)              , O(MmXmm)            , U                   , U                   , O_000F00(D7,U)  , U               ),
  INST(kX86InstIdPmovsxbd         , "pmovsxbd"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(21,U)  , U               ),
  INST(kX86InstIdPmovsxbq         , "pmovsxbq"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(22,U)  , U               ),
  INST(kX86InstIdPmovsxbw         , "pmovsxbw"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(20,U)  , U               ),
  INST(kX86InstIdPmovsxdq         , "pmovsxdq"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(25,U)  , U               ),
  INST(kX86InstIdPmovsxwd         , "pmovsxwd"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(23,U)  , U               ),
  INST(kX86InstIdPmovsxwq         , "pmovsxwq"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(24,U)  , U               ),
  INST(kX86InstIdPmovzxbd         , "pmovzxbd"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(31,U)  , U               ),
  INST(kX86InstIdPmovzxbq         , "pmovzxbq"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(32,U)  , U               ),
  INST(kX86InstIdPmovzxbw         , "pmovzxbw"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(30,U)  , U               ),
  INST(kX86InstIdPmovzxdq         , "pmovzxdq"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(35,U)  , U               ),
  INST(kX86InstIdPmovzxwd         , "pmovzxwd"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(33,U)  , U               ),
  INST(kX86InstIdPmovzxwq         , "pmovzxwq"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(34,U)  , U               ),
  INST(kX86InstIdPmuldq           , "pmuldq"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(28,U)  , U               ),
  INST(kX86InstIdPmulhrsw         , "pmulhrsw"         , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(0B,U)  , U               ),
  INST(kX86InstIdPmulhuw          , "pmulhuw"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(E4,U)  , U               ),
  INST(kX86InstIdPmulhw           , "pmulhw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(E5,U)  , U               ),
  INST(kX86InstIdPmulld           , "pmulld"           , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(40,U)  , U               ),
  INST(kX86InstIdPmullw           , "pmullw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(D5,U)  , U               ),
  INST(kX86InstIdPmuludq          , "pmuludq"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(F4,U)  , U               ),
  INST(kX86InstIdPop              , "pop"              , G(X86Pop)        , F(None)|F(Special)     , 0 , 0                   , U                   , U                   , U                   , O_000000(8F,0)  , O_000000(58,U)  ),
  INST(kX86InstIdPopa             , "popa"             , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(61,U)  , U               ),
  INST(kX86InstIdPopcnt           , "popcnt"           , G(X86RegRm)      , F(None)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_F30F00(B8,U)  , U               ),
  INST(kX86InstIdPopf             , "popf"             , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(9D,U)  , U               ),
  INST(kX86InstIdPor              , "por"              , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(EB,U)  , U               ),
  INST(kX86InstIdPrefetch         , "prefetch"         , G(ExtPrefetch)   , F(None)                , 0 , O(Mem)              , O(Imm)              , U                   , U                   , O_000F00(18,U)  , U               ),
  INST(kX86InstIdPrefetch3dNow    , "prefetch_3dnow"   , G(X86M)          , F(None)                , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(0D,0)  , U               ),
  INST(kX86InstIdPrefetchw3dNow   , "prefetchw_3dnow"  , G(X86M)          , F(None)                , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(0D,1)  , U               ),
  INST(kX86InstIdPsadbw           , "psadbw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(F6,U)  , U               ),
  INST(kX86InstIdPshufb           , "pshufb"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(00,U)  , U               ),
  INST(kX86InstIdPshufd           , "pshufd"           , G(ExtRmi)        , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F00(70,U)  , U               ),
  INST(kX86InstIdPshufhw          , "pshufhw"          , G(ExtRmi)        , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_F30F00(70,U)  , U               ),
  INST(kX86InstIdPshuflw          , "pshuflw"          , G(ExtRmi)        , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_F20F00(70,U)  , U               ),
  INST(kX86InstIdPshufw           , "pshufw"           , G(ExtRmi_P)      , F(Move)                , 8 , O(Mm)               , O(MmMem)            , O(Imm)              , U                   , O_000F00(70,U)  , U               ),
  INST(kX86InstIdPsignb           , "psignb"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(08,U)  , U               ),
  INST(kX86InstIdPsignd           , "psignd"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(0A,U)  , U               ),
  INST(kX86InstIdPsignw           , "psignw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F38(09,U)  , U               ),
  INST(kX86InstIdPslld            , "pslld"            , G(ExtRmRi_P)     , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   , O_000F00(F2,U)  , O_000F00(72,6)  ),
  INST(kX86InstIdPslldq           , "pslldq"           , G(ExtRmRi)       , F(None)                , 0 , O(Xmm)              , O(Imm)              , U                   , U                   , U               , O_660F00(73,7)  ),
  INST(kX86InstIdPsllq            , "psllq"            , G(ExtRmRi_P)     , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   , O_000F00(F3,U)  , O_000F00(73,6)  ),
  INST(kX86InstIdPsllw            , "psllw"            , G(ExtRmRi_P)     , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   , O_000F00(F1,U)  , O_000F00(71,6)  ),
  INST(kX86InstIdPsrad            , "psrad"            , G(ExtRmRi_P)     , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   , O_000F00(E2,U)  , O_000F00(72,4)  ),
  INST(kX86InstIdPsraw            , "psraw"            , G(ExtRmRi_P)     , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   , O_000F00(E1,U)  , O_000F00(71,4)  ),
  INST(kX86InstIdPsrld            , "psrld"            , G(ExtRmRi_P)     , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   , O_000F00(D2,U)  , O_000F00(72,2)  ),
  INST(kX86InstIdPsrldq           , "psrldq"           , G(ExtRmRi)       , F(None)                , 0 , O(Xmm)              , O(Imm)              , U                   , U                   , U               , O_660F00(73,3)  ),
  INST(kX86InstIdPsrlq            , "psrlq"            , G(ExtRmRi_P)     , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   , O_000F00(D3,U)  , O_000F00(73,2)  ),
  INST(kX86InstIdPsrlw            , "psrlw"            , G(ExtRmRi_P)     , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)|O(Imm)  , U                   , U                   , O_000F00(D1,U)  , O_000F00(71,2)  ),
  INST(kX86InstIdPsubb            , "psubb"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(F8,U)  , U               ),
  INST(kX86InstIdPsubd            , "psubd"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(FA,U)  , U               ),
  INST(kX86InstIdPsubq            , "psubq"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(FB,U)  , U               ),
  INST(kX86InstIdPsubsb           , "psubsb"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(E8,U)  , U               ),
  INST(kX86InstIdPsubsw           , "psubsw"           , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(E9,U)  , U               ),
  INST(kX86InstIdPsubusb          , "psubusb"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(D8,U)  , U               ),
  INST(kX86InstIdPsubusw          , "psubusw"          , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(D9,U)  , U               ),
  INST(kX86InstIdPsubw            , "psubw"            , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(F9,U)  , U               ),
  INST(kX86InstIdPswapd           , "pswapd"           , G(3dNow)         , F(None)                , 0 , O(Mm)               , O(MmMem)            , U                   , U                   , O_000F0F(BB,U)  , U               ),
  INST(kX86InstIdPtest            , "ptest"            , G(ExtRm)         , F(Test)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(17,U)  , U               ),
  INST(kX86InstIdPunpckhbw        , "punpckhbw"        , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(68,U)  , U               ),
  INST(kX86InstIdPunpckhdq        , "punpckhdq"        , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(6A,U)  , U               ),
  INST(kX86InstIdPunpckhqdq       , "punpckhqdq"       , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(6D,U)  , U               ),
  INST(kX86InstIdPunpckhwd        , "punpckhwd"        , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(69,U)  , U               ),
  INST(kX86InstIdPunpcklbw        , "punpcklbw"        , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(60,U)  , U               ),
  INST(kX86InstIdPunpckldq        , "punpckldq"        , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(62,U)  , U               ),
  INST(kX86InstIdPunpcklqdq       , "punpcklqdq"       , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(6C,U)  , U               ),
  INST(kX86InstIdPunpcklwd        , "punpcklwd"        , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(61,U)  , U               ),
  INST(kX86InstIdPush             , "push"             , G(X86Push)       , F(None)|F(Special)     , 0 , 0                   , U                   , U                   , U                   , O_000000(FF,6)  , O_000000(50,U)  ),
  INST(kX86InstIdPusha            , "pusha"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(60,U)  , U               ),
  INST(kX86InstIdPushf            , "pushf"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(9C,U)  , U               ),
  INST(kX86InstIdPxor             , "pxor"             , G(ExtRm_P)       , F(None)                , 0 , O(MmXmm)            , O(MmXmmMem)         , U                   , U                   , O_000F00(EF,U)  , U               ),
  INST(kX86InstIdRcl              , "rcl"              , G(X86Rot)        , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   , O_000000(D0,2)  , U               ),
  INST(kX86InstIdRcpps            , "rcpps"            , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(53,U)  , U               ),
  INST(kX86InstIdRcpss            , "rcpss"            , G(ExtRm)         , F(Move)                , 4 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(53,U)  , U               ),
  INST(kX86InstIdRcr              , "rcr"              , G(X86Rot)        , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   , O_000000(D0,3)  , U               ),
  INST(kX86InstIdRdfsbase         , "rdfsbase"         , G(X86Rm)         , F(Move)                , 8 , O(Gqd)              , U                   , U                   , U                   , O_F30F00(AE,0)  , U               ),
  INST(kX86InstIdRdgsbase         , "rdgsbase"         , G(X86Rm)         , F(Move)                , 8 , O(Gqd)              , U                   , U                   , U                   , O_F30F00(AE,1)  , U               ),
  INST(kX86InstIdRdrand           , "rdrand"           , G(X86Rm)         , F(Move)                , 8 , O(Gqdw)             , U                   , U                   , U                   , O_000F00(C7,6)  , U               ),
  INST(kX86InstIdRdtsc            , "rdtsc"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000F00(31,U)  , U               ),
  INST(kX86InstIdRdtscp           , "rdtscp"           , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000F01(F9,U)  , U               ),
  INST(kX86InstIdRepLodsb         , "rep lodsb"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(AC,1)  , U               ),
  INST(kX86InstIdRepLodsd         , "rep lodsd"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(AD,1)  , U               ),
  INST(kX86InstIdRepLodsq         , "rep lodsq"        , G(X86Rep)        , F(None)|F(Special)|F(W), 0 , O(Mem)              , U                   , U                   , U                   , O_000000(AD,1)  , U               ),
  INST(kX86InstIdRepLodsw         , "rep lodsw"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , U                   , U                   , U                   , O_660000(AD,1)  , U               ),
  INST(kX86InstIdRepMovsb         , "rep movsb"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A4,1)  , U               ),
  INST(kX86InstIdRepMovsd         , "rep movsd"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A5,1)  , U               ),
  INST(kX86InstIdRepMovsq         , "rep movsq"        , G(X86Rep)        , F(None)|F(Special)|F(W), 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A5,1)  , U               ),
  INST(kX86InstIdRepMovsw         , "rep movsw"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_660000(A5,1)  , U               ),
  INST(kX86InstIdRepStosb         , "rep stosb"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(AA,1)  , U               ),
  INST(kX86InstIdRepStosd         , "rep stosd"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , U                   , U                   , U                   , O_000000(AB,1)  , U               ),
  INST(kX86InstIdRepStosq         , "rep stosq"        , G(X86Rep)        , F(None)|F(Special)|F(W), 0 , O(Mem)              , U                   , U                   , U                   , O_000000(AB,1)  , U               ),
  INST(kX86InstIdRepStosw         , "rep stosw"        , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , U                   , U                   , U                   , O_660000(AB,1)  , U               ),
  INST(kX86InstIdRepeCmpsb        , "repe cmpsb"       , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A6,1)  , U               ),
  INST(kX86InstIdRepeCmpsd        , "repe cmpsd"       , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A7,1)  , U               ),
  INST(kX86InstIdRepeCmpsq        , "repe cmpsq"       , G(X86Rep)        , F(None)|F(Special)|F(W), 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A7,1)  , U               ),
  INST(kX86InstIdRepeCmpsw        , "repe cmpsw"       , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_660000(A7,1)  , U               ),
  INST(kX86InstIdRepeScasb        , "repe scasb"       , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(AE,1)  , U               ),
  INST(kX86InstIdRepeScasd        , "repe scasd"       , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(AF,1)  , U               ),
  INST(kX86InstIdRepeScasq        , "repe scasq"       , G(X86Rep)        , F(None)|F(Special)|F(W), 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(AF,1)  , U               ),
  INST(kX86InstIdRepeScasw        , "repe scasw"       , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_660000(AF,1)  , U               ),
  INST(kX86InstIdRepneCmpsb       , "repne cmpsb"      , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A6,0)  , U               ),
  INST(kX86InstIdRepneCmpsd       , "repne cmpsd"      , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A7,0)  , U               ),
  INST(kX86InstIdRepneCmpsq       , "repne cmpsq"      , G(X86Rep)        , F(None)|F(Special)|F(W), 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(A7,0)  , U               ),
  INST(kX86InstIdRepneCmpsw       , "repne cmpsw"      , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_660000(A7,0)  , U               ),
  INST(kX86InstIdRepneScasb       , "repne scasb"      , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(AE,0)  , U               ),
  INST(kX86InstIdRepneScasd       , "repne scasd"      , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(AF,0)  , U               ),
  INST(kX86InstIdRepneScasq       , "repne scasq"      , G(X86Rep)        , F(None)|F(Special)|F(W), 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_000000(AF,0)  , U               ),
  INST(kX86InstIdRepneScasw       , "repne scasw"      , G(X86Rep)        , F(None)|F(Special)     , 0 , O(Mem)              , O(Mem)              , U                   , U                   , O_660000(AF,0)  , U               ),
  INST(kX86InstIdRet              , "ret"              , G(X86Ret)        , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(C2,U)  , U               ),
  INST(kX86InstIdRol              , "rol"              , G(X86Rot)        , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   , O_000000(D0,0)  , U               ),
  INST(kX86InstIdRor              , "ror"              , G(X86Rot)        , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   , O_000000(D0,1)  , U               ),
  INST(kX86InstIdRorx             , "rorx"             , G(AvxRmi)        , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , O(Imm)              , U                   , O_F20F3A(F0,U)  , U               ),
  INST(kX86InstIdRoundpd          , "roundpd"          , G(ExtRmi)        , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(09,U)  , U               ),
  INST(kX86InstIdRoundps          , "roundps"          , G(ExtRmi)        , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(08,U)  , U               ),
  INST(kX86InstIdRoundsd          , "roundsd"          , G(ExtRmi)        , F(Move)                , 8 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(0B,U)  , U               ),
  INST(kX86InstIdRoundss          , "roundss"          , G(ExtRmi)        , F(Move)                , 4 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(0A,U)  , U               ),
  INST(kX86InstIdRsqrtps          , "rsqrtps"          , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(52,U)  , U               ),
  INST(kX86InstIdRsqrtss          , "rsqrtss"          , G(ExtRm)         , F(Move)                , 4 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(52,U)  , U               ),
  INST(kX86InstIdSahf             , "sahf"             , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(9E,U)  , U               ),
  INST(kX86InstIdSal              , "sal"              , G(X86Rot)        , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   , O_000000(D0,4)  , U               ),
  INST(kX86InstIdSar              , "sar"              , G(X86Rot)        , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   , O_000000(D0,7)  , U               ),
  INST(kX86InstIdSarx             , "sarx"             , G(AvxRmv)        , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , O(Gqd)              , U                   , O_F30F38(F7,U)  , U               ),
  INST(kX86InstIdSbb              , "sbb"              , G(X86Arith)      , F(Lock)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , O_000000(18,3)  , U               ),
  INST(kX86InstIdScasb            , "scasb"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(AE,U)  , U               ),
  INST(kX86InstIdScasd            , "scasd"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(AF,U)  , U               ),
  INST(kX86InstIdScasq            , "scasq"            , G(X86Op)         , F(None)|F(Special)|F(W), 0 , U                   , U                   , U                   , U                   , O_000000(AF,U)  , U               ),
  INST(kX86InstIdScasw            , "scasw"            , G(X86Op_66H)     , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(AF,U)  , U               ),
  INST(kX86InstIdSeta             , "seta"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(97,U)  , U               ),
  INST(kX86InstIdSetae            , "setae"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(93,U)  , U               ),
  INST(kX86InstIdSetb             , "setb"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(92,U)  , U               ),
  INST(kX86InstIdSetbe            , "setbe"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(96,U)  , U               ),
  INST(kX86InstIdSetc             , "setc"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(92,U)  , U               ),
  INST(kX86InstIdSete             , "sete"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(94,U)  , U               ),
  INST(kX86InstIdSetg             , "setg"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9F,U)  , U               ),
  INST(kX86InstIdSetge            , "setge"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9D,U)  , U               ),
  INST(kX86InstIdSetl             , "setl"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9C,U)  , U               ),
  INST(kX86InstIdSetle            , "setle"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9E,U)  , U               ),
  INST(kX86InstIdSetna            , "setna"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(96,U)  , U               ),
  INST(kX86InstIdSetnae           , "setnae"           , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(92,U)  , U               ),
  INST(kX86InstIdSetnb            , "setnb"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(93,U)  , U               ),
  INST(kX86InstIdSetnbe           , "setnbe"           , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(97,U)  , U               ),
  INST(kX86InstIdSetnc            , "setnc"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(93,U)  , U               ),
  INST(kX86InstIdSetne            , "setne"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(95,U)  , U               ),
  INST(kX86InstIdSetng            , "setng"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9E,U)  , U               ),
  INST(kX86InstIdSetnge           , "setnge"           , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9C,U)  , U               ),
  INST(kX86InstIdSetnl            , "setnl"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9D,U)  , U               ),
  INST(kX86InstIdSetnle           , "setnle"           , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9F,U)  , U               ),
  INST(kX86InstIdSetno            , "setno"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(91,U)  , U               ),
  INST(kX86InstIdSetnp            , "setnp"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9B,U)  , U               ),
  INST(kX86InstIdSetns            , "setns"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(99,U)  , U               ),
  INST(kX86InstIdSetnz            , "setnz"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(95,U)  , U               ),
  INST(kX86InstIdSeto             , "seto"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(90,U)  , U               ),
  INST(kX86InstIdSetp             , "setp"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9A,U)  , U               ),
  INST(kX86InstIdSetpe            , "setpe"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9A,U)  , U               ),
  INST(kX86InstIdSetpo            , "setpo"            , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(9B,U)  , U               ),
  INST(kX86InstIdSets             , "sets"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(98,U)  , U               ),
  INST(kX86InstIdSetz             , "setz"             , G(X86Set)        , F(Move)                , 1 , O(GbMem)            , U                   , U                   , U                   , O_000F00(94,U)  , U               ),
  INST(kX86InstIdSfence           , "sfence"           , G(ExtFence)      , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000F00(AE,7)  , U               ),
  INST(kX86InstIdShl              , "shl"              , G(X86Rot)        , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   , O_000000(D0,4)  , U               ),
  INST(kX86InstIdShld             , "shld"             , G(X86Shlrd)      , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)               , U                   , U                   , O_000F00(A4,U)  , U               ),
  INST(kX86InstIdShlx             , "shlx"             , G(AvxRmv)        , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , O(Gqd)              , U                   , O_660F38(F7,U)  , U               ),
  INST(kX86InstIdShr              , "shr"              , G(X86Rot)        , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gb)|O(Imm)        , U                   , U                   , O_000000(D0,5)  , U               ),
  INST(kX86InstIdShrd             , "shrd"             , G(X86Shlrd)      , F(None)|F(Special)     , 0 , O(GqdwbMem)         , O(Gqdwb)            , U                   , U                   , O_000F00(AC,U)  , U               ),
  INST(kX86InstIdShrx             , "shrx"             , G(AvxRmv)        , F(None)                , 0 , O(Gqd)              , O(GqdMem)           , O(Gqd)              , U                   , O_F20F38(F7,U)  , U               ),
  INST(kX86InstIdShufpd           , "shufpd"           , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F00(C6,U)  , U               ),
  INST(kX86InstIdShufps           , "shufps"           , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_000F00(C6,U)  , U               ),
  INST(kX86InstIdSqrtpd           , "sqrtpd"           , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(51,U)  , U               ),
  INST(kX86InstIdSqrtps           , "sqrtps"           , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(51,U)  , U               ),
  INST(kX86InstIdSqrtsd           , "sqrtsd"           , G(ExtRm)         , F(Move)                , 8 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(51,U)  , U               ),
  INST(kX86InstIdSqrtss           , "sqrtss"           , G(ExtRm)         , F(Move)                , 4 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(51,U)  , U               ),
  INST(kX86InstIdStc              , "stc"              , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000000(F9,U)  , U               ),
  INST(kX86InstIdStd              , "std"              , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000000(FD,U)  , U               ),
  INST(kX86InstIdStmxcsr          , "stmxcsr"          , G(X86M)          , F(None)                , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(AE,3)  , U               ),
  INST(kX86InstIdStosb            , "stosb"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(AA,U)  , U               ),
  INST(kX86InstIdStosd            , "stosd"            , G(X86Op)         , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(AB,U)  , U               ),
  INST(kX86InstIdStosq            , "stosq"            , G(X86Op)         , F(None)|F(Special)|F(W), 0 , U                   , U                   , U                   , U                   , O_000000(AB,U)  , U               ),
  INST(kX86InstIdStosw            , "stosw"            , G(X86Op_66H)     , F(None)|F(Special)     , 0 , U                   , U                   , U                   , U                   , O_000000(AB,U)  , U               ),
  INST(kX86InstIdSub              , "sub"              , G(X86Arith)      , F(Lock)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , O_000000(28,5)  , U               ),
  INST(kX86InstIdSubpd            , "subpd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(5C,U)  , U               ),
  INST(kX86InstIdSubps            , "subps"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(5C,U)  , U               ),
  INST(kX86InstIdSubsd            , "subsd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F20F00(5C,U)  , U               ),
  INST(kX86InstIdSubss            , "subss"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(5C,U)  , U               ),
  INST(kX86InstIdTest             , "test"             , G(X86Test)       , F(Test)                , 0 , O(GqdwbMem)         , O(Gqdwb)|O(Imm)     , U                   , U                   , O_000000(84,U)  , O_000000(F6,U)  ),
  INST(kX86InstIdTzcnt            , "tzcnt"            , G(X86RegRm)      , F(Move)                , 0 , O(Gqdw)             , O(GqdwMem)          , U                   , U                   , O_F30F00(BC,U)  , U               ),
  INST(kX86InstIdUcomisd          , "ucomisd"          , G(ExtRm)         , F(Test)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(2E,U)  , U               ),
  INST(kX86InstIdUcomiss          , "ucomiss"          , G(ExtRm)         , F(Test)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(2E,U)  , U               ),
  INST(kX86InstIdUd2              , "ud2"              , G(X86Op)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000F00(0B,U)  , U               ),
  INST(kX86InstIdUnpckhpd         , "unpckhpd"         , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(15,U)  , U               ),
  INST(kX86InstIdUnpckhps         , "unpckhps"         , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(15,U)  , U               ),
  INST(kX86InstIdUnpcklpd         , "unpcklpd"         , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(14,U)  , U               ),
  INST(kX86InstIdUnpcklps         , "unpcklps"         , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(14,U)  , U               ),
  INST(kX86InstIdVaddpd           , "vaddpd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(58,U)  , U               ),
  INST(kX86InstIdVaddps           , "vaddps"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(58,U)  , U               ),
  INST(kX86InstIdVaddsd           , "vaddsd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F20F00(58,U)  , U               ),
  INST(kX86InstIdVaddss           , "vaddss"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F30F00(58,U)  , U               ),
  INST(kX86InstIdVaddsubpd        , "vaddsubpd"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(D0,U)  , U               ),
  INST(kX86InstIdVaddsubps        , "vaddsubps"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F20F00(D0,U)  , U               ),
  INST(kX86InstIdVaesdec          , "vaesdec"          , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(DE,U)  , U               ),
  INST(kX86InstIdVaesdeclast      , "vaesdeclast"      , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(DF,U)  , U               ),
  INST(kX86InstIdVaesenc          , "vaesenc"          , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(DC,U)  , U               ),
  INST(kX86InstIdVaesenclast      , "vaesenclast"      , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(DD,U)  , U               ),
  INST(kX86InstIdVaesimc          , "vaesimc"          , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(DB,U)  , U               ),
  INST(kX86InstIdVaeskeygenassist , "vaeskeygenassist" , G(AvxRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(DF,U)  , U               ),
  INST(kX86InstIdVandnpd          , "vandnpd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(55,U)  , U               ),
  INST(kX86InstIdVandnps          , "vandnps"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(55,U)  , U               ),
  INST(kX86InstIdVandpd           , "vandpd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(54,U)  , U               ),
  INST(kX86InstIdVandps           , "vandps"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(54,U)  , U               ),
  INST(kX86InstIdVblendpd         , "vblendpd"         , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F3A(0D,U)  , U               ),
  INST(kX86InstIdVblendps         , "vblendps"         , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F3A(0C,U)  , U               ),
  INST(kX86InstIdVblendvpd        , "vblendvpd"        , G(AvxRvmr_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmm)           , O_660F3A(4B,U)  , U               ),
  INST(kX86InstIdVblendvps        , "vblendvps"        , G(AvxRvmr_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmm)           , O_660F3A(4A,U)  , U               ),
  INST(kX86InstIdVbroadcastf128   , "vbroadcastf128"   , G(AvxRm)         , F(None)                , 0 , O(Ymm)              , O(Mem)              , U                   , U                   , O_660F38(1A,U)|L, U               ),
  INST(kX86InstIdVbroadcasti128   , "vbroadcasti128"   , G(AvxRm)         , F(None)                , 0 , O(Ymm)              , O(Mem)              , U                   , U                   , O_660F38(5A,U)|L, U               ),
  INST(kX86InstIdVbroadcastsd     , "vbroadcastsd"     , G(AvxRm)         , F(None)                , 0 , O(Ymm)              , O(XmmMem)           , U                   , U                   , O_660F38(19,U)|L, U               ),
  INST(kX86InstIdVbroadcastss     , "vbroadcastss"     , G(AvxRm)         , F(None)                , 0 , O(Ymm)              , O(XmmMem)           , U                   , U                   , O_660F38(18,U)  , U               ),
  INST(kX86InstIdVcmppd           , "vcmppd"           , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F00(C2,U)  , U               ),
  INST(kX86InstIdVcmpps           , "vcmpps"           , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_000F00(C2,U)  , U               ),
  INST(kX86InstIdVcmpsd           , "vcmpsd"           , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_F20F00(C2,U)  , U               ),
  INST(kX86InstIdVcmpss           , "vcmpss"           , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_F30F00(C2,U)  , U               ),
  INST(kX86InstIdVcomisd          , "vcomisd"          , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(2F,U)  , U               ),
  INST(kX86InstIdVcomiss          , "vcomiss"          , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(2F,U)  , U               ),
  INST(kX86InstIdVcvtdq2pd        , "vcvtdq2pd"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmMem)           , U                   , U                   , O_F30F00(E6,U)  , U               ),
  INST(kX86InstIdVcvtdq2ps        , "vcvtdq2ps"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_000F00(5B,U)  , U               ),
  INST(kX86InstIdVcvtpd2dq        , "vcvtpd2dq"        , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(XmmYmmMem)        , U                   , U                   , O_F20F00(E6,U)  , U               ),
  INST(kX86InstIdVcvtpd2ps        , "vcvtpd2ps"        , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(XmmYmmMem)        , U                   , U                   , O_660F00(5A,U)  , U               ),
  INST(kX86InstIdVcvtph2ps        , "vcvtph2ps"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmMem)           , U                   , U                   , O_660F38(13,U)  , U               ),
  INST(kX86InstIdVcvtps2dq        , "vcvtps2dq"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F00(5B,U)  , U               ),
  INST(kX86InstIdVcvtps2pd        , "vcvtps2pd"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmMem)           , U                   , U                   , O_000F00(5A,U)  , U               ),
  INST(kX86InstIdVcvtps2ph        , "vcvtps2ph"        , G(AvxMri_P)      , F(None)                , 0 , O(XmmMem)           , O(XmmYmm)           , O(Imm)              , U                   , O_660F3A(1D,U)  , U               ),
  INST(kX86InstIdVcvtsd2si        , "vcvtsd2si"        , G(AvxRm)         , F(None)                , 0 , O(Gqd)              , O(XmmMem)           , U                   , U                   , O_F20F00(2D,U)  , U               ),
  INST(kX86InstIdVcvtsd2ss        , "vcvtsd2ss"        , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F20F00(5A,U)  , U               ),
  INST(kX86InstIdVcvtsi2sd        , "vcvtsi2sd"        , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(GqdMem)           , U                   , O_F20F00(2A,U)  , U               ),
  INST(kX86InstIdVcvtsi2ss        , "vcvtsi2ss"        , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(GqdMem)           , U                   , O_F30F00(2A,U)  , U               ),
  INST(kX86InstIdVcvtss2sd        , "vcvtss2sd"        , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F30F00(5A,U)  , U               ),
  INST(kX86InstIdVcvtss2si        , "vcvtss2si"        , G(AvxRm)         , F(None)                , 0 , O(Gqd)              , O(XmmMem)           , U                   , U                   , O_F20F00(2D,U)  , U               ),
  INST(kX86InstIdVcvttpd2dq       , "vcvttpd2dq"       , G(AvxRm_P)       , F(None)                , 0 , O(Xmm)              , O(XmmYmmMem)        , U                   , U                   , O_660F00(E6,U)  , U               ),
  INST(kX86InstIdVcvttps2dq       , "vcvttps2dq"       , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_F30F00(5B,U)  , U               ),
  INST(kX86InstIdVcvttsd2si       , "vcvttsd2si"       , G(AvxRm)         , F(None)                , 0 , O(Gqd)              , O(XmmMem)           , U                   , U                   , O_F20F00(2C,U)  , U               ),
  INST(kX86InstIdVcvttss2si       , "vcvttss2si"       , G(AvxRm)         , F(None)                , 0 , O(Gqd)              , O(XmmMem)           , U                   , U                   , O_F30F00(2C,U)  , U               ),
  INST(kX86InstIdVdivpd           , "vdivpd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(5E,U)  , U               ),
  INST(kX86InstIdVdivps           , "vdivps"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(5E,U)  , U               ),
  INST(kX86InstIdVdivsd           , "vdivsd"           , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F20F00(5E,U)  , U               ),
  INST(kX86InstIdVdivss           , "vdivss"           , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F30F00(5E,U)  , U               ),
  INST(kX86InstIdVdppd            , "vdppd"            , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_660F3A(41,U)  , U               ),
  INST(kX86InstIdVdpps            , "vdpps"            , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F3A(40,U)  , U               ),
  INST(kX86InstIdVextractf128     , "vextractf128"     , G(AvxMri)        , F(None)                , 0 , O(XmmMem)           , O(Ymm)              , O(Imm)              , U                   , O_660F3A(19,U)|L, U               ),
  INST(kX86InstIdVextracti128     , "vextracti128"     , G(AvxMri)        , F(None)                , 0 , O(XmmMem)           , O(Ymm)              , O(Imm)              , U                   , O_660F3A(39,U)|L, U               ),
  INST(kX86InstIdVextractps       , "vextractps"       , G(AvxMri)        , F(None)                , 0 , O(GqdMem)           , O(Xmm)              , O(Imm)              , U                   , O_660F3A(17,U)  , U               ),
  INST(kX86InstIdVfmadd132pd      , "vfmadd132pd"      , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(98,U)  , U               ),
  INST(kX86InstIdVfmadd132ps      , "vfmadd132ps"      , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(98,U)  , U               ),
  INST(kX86InstIdVfmadd132sd      , "vfmadd132sd"      , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(99,U)  , U               ),
  INST(kX86InstIdVfmadd132ss      , "vfmadd132ss"      , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(99,U)  , U               ),
  INST(kX86InstIdVfmadd213pd      , "vfmadd213pd"      , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(A8,U)  , U               ),
  INST(kX86InstIdVfmadd213ps      , "vfmadd213ps"      , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(A8,U)  , U               ),
  INST(kX86InstIdVfmadd213sd      , "vfmadd213sd"      , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(A9,U)  , U               ),
  INST(kX86InstIdVfmadd213ss      , "vfmadd213ss"      , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(A9,U)  , U               ),
  INST(kX86InstIdVfmadd231pd      , "vfmadd231pd"      , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(B8,U)  , U               ),
  INST(kX86InstIdVfmadd231ps      , "vfmadd231ps"      , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(B8,U)  , U               ),
  INST(kX86InstIdVfmadd231sd      , "vfmadd231sd"      , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(B9,U)  , U               ),
  INST(kX86InstIdVfmadd231ss      , "vfmadd231ss"      , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(B9,U)  , U               ),
  INST(kX86InstIdVfmaddpd         , "vfmaddpd"         , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(69,U)  , U               ),
  INST(kX86InstIdVfmaddps         , "vfmaddps"         , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(68,U)  , U               ),
  INST(kX86InstIdVfmaddsd         , "vfmaddsd"         , G(Fma4)          , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_660F3A(6B,U)  , U               ),
  INST(kX86InstIdVfmaddss         , "vfmaddss"         , G(Fma4)          , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_660F3A(6A,U)  , U               ),
  INST(kX86InstIdVfmaddsub132pd   , "vfmaddsub132pd"   , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(96,U)  , U               ),
  INST(kX86InstIdVfmaddsub132ps   , "vfmaddsub132ps"   , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(96,U)  , U               ),
  INST(kX86InstIdVfmaddsub213pd   , "vfmaddsub213pd"   , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(A6,U)  , U               ),
  INST(kX86InstIdVfmaddsub213ps   , "vfmaddsub213ps"   , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(A6,U)  , U               ),
  INST(kX86InstIdVfmaddsub231pd   , "vfmaddsub231pd"   , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(B6,U)  , U               ),
  INST(kX86InstIdVfmaddsub231ps   , "vfmaddsub231ps"   , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(B6,U)  , U               ),
  INST(kX86InstIdVfmaddsubpd      , "vfmaddsubpd"      , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(5D,U)  , U               ),
  INST(kX86InstIdVfmaddsubps      , "vfmaddsubps"      , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(5C,U)  , U               ),
  INST(kX86InstIdVfmsub132pd      , "vfmsub132pd"      , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(9A,U)  , U               ),
  INST(kX86InstIdVfmsub132ps      , "vfmsub132ps"      , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(9A,U)  , U               ),
  INST(kX86InstIdVfmsub132sd      , "vfmsub132sd"      , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(9B,U)  , U               ),
  INST(kX86InstIdVfmsub132ss      , "vfmsub132ss"      , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(9B,U)  , U               ),
  INST(kX86InstIdVfmsub213pd      , "vfmsub213pd"      , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(AA,U)  , U               ),
  INST(kX86InstIdVfmsub213ps      , "vfmsub213ps"      , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(AA,U)  , U               ),
  INST(kX86InstIdVfmsub213sd      , "vfmsub213sd"      , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(AB,U)  , U               ),
  INST(kX86InstIdVfmsub213ss      , "vfmsub213ss"      , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(AB,U)  , U               ),
  INST(kX86InstIdVfmsub231pd      , "vfmsub231pd"      , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(BA,U)  , U               ),
  INST(kX86InstIdVfmsub231ps      , "vfmsub231ps"      , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(BA,U)  , U               ),
  INST(kX86InstIdVfmsub231sd      , "vfmsub231sd"      , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(BB,U)  , U               ),
  INST(kX86InstIdVfmsub231ss      , "vfmsub231ss"      , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(BB,U)  , U               ),
  INST(kX86InstIdVfmsubadd132pd   , "vfmsubadd132pd"   , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(97,U)  , U               ),
  INST(kX86InstIdVfmsubadd132ps   , "vfmsubadd132ps"   , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(97,U)  , U               ),
  INST(kX86InstIdVfmsubadd213pd   , "vfmsubadd213pd"   , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(A7,U)  , U               ),
  INST(kX86InstIdVfmsubadd213ps   , "vfmsubadd213ps"   , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(A7,U)  , U               ),
  INST(kX86InstIdVfmsubadd231pd   , "vfmsubadd231pd"   , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(B7,U)  , U               ),
  INST(kX86InstIdVfmsubadd231ps   , "vfmsubadd231ps"   , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(B7,U)  , U               ),
  INST(kX86InstIdVfmsubaddpd      , "vfmsubaddpd"      , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(5F,U)  , U               ),
  INST(kX86InstIdVfmsubaddps      , "vfmsubaddps"      , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(5E,U)  , U               ),
  INST(kX86InstIdVfmsubpd         , "vfmsubpd"         , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(6D,U)  , U               ),
  INST(kX86InstIdVfmsubps         , "vfmsubps"         , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(6C,U)  , U               ),
  INST(kX86InstIdVfmsubsd         , "vfmsubsd"         , G(Fma4)          , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_660F3A(6F,U)  , U               ),
  INST(kX86InstIdVfmsubss         , "vfmsubss"         , G(Fma4)          , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_660F3A(6E,U)  , U               ),
  INST(kX86InstIdVfnmadd132pd     , "vfnmadd132pd"     , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(9C,U)  , U               ),
  INST(kX86InstIdVfnmadd132ps     , "vfnmadd132ps"     , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(9C,U)  , U               ),
  INST(kX86InstIdVfnmadd132sd     , "vfnmadd132sd"     , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(9D,U)  , U               ),
  INST(kX86InstIdVfnmadd132ss     , "vfnmadd132ss"     , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(9D,U)  , U               ),
  INST(kX86InstIdVfnmadd213pd     , "vfnmadd213pd"     , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(AC,U)  , U               ),
  INST(kX86InstIdVfnmadd213ps     , "vfnmadd213ps"     , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(AC,U)  , U               ),
  INST(kX86InstIdVfnmadd213sd     , "vfnmadd213sd"     , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(AD,U)  , U               ),
  INST(kX86InstIdVfnmadd213ss     , "vfnmadd213ss"     , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(AD,U)  , U               ),
  INST(kX86InstIdVfnmadd231pd     , "vfnmadd231pd"     , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(BC,U)  , U               ),
  INST(kX86InstIdVfnmadd231ps     , "vfnmadd231ps"     , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(BC,U)  , U               ),
  INST(kX86InstIdVfnmadd231sd     , "vfnmadd231sd"     , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(BC,U)  , U               ),
  INST(kX86InstIdVfnmadd231ss     , "vfnmadd231ss"     , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(BC,U)  , U               ),
  INST(kX86InstIdVfnmaddpd        , "vfnmaddpd"        , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(79,U)  , U               ),
  INST(kX86InstIdVfnmaddps        , "vfnmaddps"        , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(78,U)  , U               ),
  INST(kX86InstIdVfnmaddsd        , "vfnmaddsd"        , G(Fma4)          , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_660F3A(7B,U)  , U               ),
  INST(kX86InstIdVfnmaddss        , "vfnmaddss"        , G(Fma4)          , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_660F3A(7A,U)  , U               ),
  INST(kX86InstIdVfnmsub132pd     , "vfnmsub132pd"     , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(9E,U)  , U               ),
  INST(kX86InstIdVfnmsub132ps     , "vfnmsub132ps"     , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(9E,U)  , U               ),
  INST(kX86InstIdVfnmsub132sd     , "vfnmsub132sd"     , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(9F,U)  , U               ),
  INST(kX86InstIdVfnmsub132ss     , "vfnmsub132ss"     , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(9F,U)  , U               ),
  INST(kX86InstIdVfnmsub213pd     , "vfnmsub213pd"     , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(AE,U)  , U               ),
  INST(kX86InstIdVfnmsub213ps     , "vfnmsub213ps"     , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(AE,U)  , U               ),
  INST(kX86InstIdVfnmsub213sd     , "vfnmsub213sd"     , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(AF,U)  , U               ),
  INST(kX86InstIdVfnmsub213ss     , "vfnmsub213ss"     , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(AF,U)  , U               ),
  INST(kX86InstIdVfnmsub231pd     , "vfnmsub231pd"     , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(BE,U)  , U               ),
  INST(kX86InstIdVfnmsub231ps     , "vfnmsub231ps"     , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(BE,U)  , U               ),
  INST(kX86InstIdVfnmsub231sd     , "vfnmsub231sd"     , G(AvxRvm)        , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(BF,U)  , U               ),
  INST(kX86InstIdVfnmsub231ss     , "vfnmsub231ss"     , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_660F38(BF,U)  , U               ),
  INST(kX86InstIdVfnmsubpd        , "vfnmsubpd"        , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(7D,U)  , U               ),
  INST(kX86InstIdVfnmsubps        , "vfnmsubps"        , G(Fma4_P)        , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_660F3A(7C,U)  , U               ),
  INST(kX86InstIdVfnmsubsd        , "vfnmsubsd"        , G(Fma4)          , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_660F3A(7F,U)  , U               ),
  INST(kX86InstIdVfnmsubss        , "vfnmsubss"        , G(Fma4)          , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_660F3A(7E,U)  , U               ),
  INST(kX86InstIdVfrczpd          , "vfrczpd"          , G(XopRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_00_M09(81,U)  , U               ),
  INST(kX86InstIdVfrczps          , "vfrczps"          , G(XopRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_00_M09(80,U)  , U               ),
  INST(kX86InstIdVfrczsd          , "vfrczsd"          , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(83,U)  , U               ),
  INST(kX86InstIdVfrczss          , "vfrczss"          , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(82,U)  , U               ),
  INST(kX86InstIdVgatherdpd       , "vgatherdpd"       , G(AvxGather)     , F(None)           |F(W), 0 , O(XmmYmm)           , O(Mem)              , O(XmmYmm)           , U                   , O_660F38(92,U)  , U               ),
  INST(kX86InstIdVgatherdps       , "vgatherdps"       , G(AvxGather)     , F(None)                , 0 , O(XmmYmm)           , O(Mem)              , O(XmmYmm)           , U                   , O_660F38(92,U)  , U               ),
  INST(kX86InstIdVgatherqpd       , "vgatherqpd"       , G(AvxGather)     , F(None)           |F(W), 0 , O(XmmYmm)           , O(Mem)              , O(XmmYmm)           , U                   , O_660F38(93,U)  , U               ),
  INST(kX86InstIdVgatherqps       , "vgatherqps"       , G(AvxGatherEx)   , F(None)                , 0 , O(Xmm)              , O(Mem)              , O(Xmm)              , U                   , O_660F38(93,U)  , U               ),
  INST(kX86InstIdVhaddpd          , "vhaddpd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(7C,U)  , U               ),
  INST(kX86InstIdVhaddps          , "vhaddps"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F20F00(7C,U)  , U               ),
  INST(kX86InstIdVhsubpd          , "vhsubpd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(7D,U)  , U               ),
  INST(kX86InstIdVhsubps          , "vhsubps"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F20F00(7D,U)  , U               ),
  INST(kX86InstIdVinsertf128      , "vinsertf128"      , G(AvxRvmi)       , F(None)                , 0 , O(Ymm)              , O(Ymm)              , O(XmmMem)           , O(Imm)              , O_660F3A(18,U)|L, U               ),
  INST(kX86InstIdVinserti128      , "vinserti128"      , G(AvxRvmi)       , F(None)                , 0 , O(Ymm)              , O(Ymm)              , O(XmmMem)           , O(Imm)              , O_660F3A(38,U)|L, U               ),
  INST(kX86InstIdVinsertps        , "vinsertps"        , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_660F3A(21,U)  , U               ),
  INST(kX86InstIdVlddqu           , "vlddqu"           , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(Mem)              , U                   , U                   , O_F20F00(F0,U)  , U               ),
  INST(kX86InstIdVldmxcsr         , "vldmxcsr"         , G(AvxM)          , F(None)                , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(AE,2)  , U               ),
  INST(kX86InstIdVmaskmovdqu      , "vmaskmovdqu"      , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(Xmm)              , U                   , U                   , O_660F00(F7,U)  , U               ),
  INST(kX86InstIdVmaskmovpd       , "vmaskmovpd"       , G(AvxRvmMvr_P)   , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(2D,U)  , O_660F38(2F,U)  ),
  INST(kX86InstIdVmaskmovps       , "vmaskmovps"       , G(AvxRvmMvr_P)   , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(2C,U)  , O_660F38(2E,U)  ),
  INST(kX86InstIdVmaxpd           , "vmaxpd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(5F,U)  , U               ),
  INST(kX86InstIdVmaxps           , "vmaxps"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(5F,U)  , U               ),
  INST(kX86InstIdVmaxsd           , "vmaxsd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F20F00(5F,U)  , U               ),
  INST(kX86InstIdVmaxss           , "vmaxss"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F30F00(5F,U)  , U               ),
  INST(kX86InstIdVminpd           , "vminpd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(5D,U)  , U               ),
  INST(kX86InstIdVminps           , "vminps"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(5D,U)  , U               ),
  INST(kX86InstIdVminsd           , "vminsd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F20F00(5D,U)  , U               ),
  INST(kX86InstIdVminss           , "vminss"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F30F00(5D,U)  , U               ),
  INST(kX86InstIdVmovapd          , "vmovapd"          , G(AvxRmMr_P)     , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   , O_660F00(28,U)  , O_660F00(29,U)  ),
  INST(kX86InstIdVmovaps          , "vmovaps"          , G(AvxRmMr_P)     , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   , O_000F00(28,U)  , O_000F00(29,U)  ),
  INST(kX86InstIdVmovd            , "vmovd"            , G(AvxRmMr)       , F(None)                , 0 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_660F00(6E,U)  , O_660F00(7E,U)  ),
  INST(kX86InstIdVmovddup         , "vmovddup"         , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_F20F00(12,U)  , U               ),
  INST(kX86InstIdVmovdqa          , "vmovdqa"          , G(AvxRmMr_P)     , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   , O_660F00(6F,U)  , O_660F00(7F,U)  ),
  INST(kX86InstIdVmovdqu          , "vmovdqu"          , G(AvxRmMr_P)     , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   , O_F30F00(6F,U)  , O_F30F00(7F,U)  ),
  INST(kX86InstIdVmovhlps         , "vmovhlps"         , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(Xmm)              , U                   , O_000F00(12,U)  , U               ),
  INST(kX86InstIdVmovhpd          , "vmovhpd"          , G(AvxRvmMr)      , F(None)                , 0 , O(XmmMem)           , O(Xmm)              , O(Mem)              , U                   , O_660F00(16,U)  , O_660F00(17,U)  ),
  INST(kX86InstIdVmovhps          , "vmovhps"          , G(AvxRvmMr)      , F(None)                , 0 , O(XmmMem)           , O(Xmm)              , O(Mem)              , U                   , O_000F00(16,U)  , O_000F00(17,U)  ),
  INST(kX86InstIdVmovlhps         , "vmovlhps"         , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(Xmm)              , U                   , O_000F00(16,U)  , U               ),
  INST(kX86InstIdVmovlpd          , "vmovlpd"          , G(AvxRvmMr)      , F(None)                , 0 , O(XmmMem)           , O(Xmm)              , O(Mem)              , U                   , O_660F00(12,U)  , O_660F00(13,U)  ),
  INST(kX86InstIdVmovlps          , "vmovlps"          , G(AvxRvmMr)      , F(None)                , 0 , O(XmmMem)           , O(Xmm)              , O(Mem)              , U                   , O_000F00(12,U)  , O_000F00(13,U)  ),
  INST(kX86InstIdVmovmskpd        , "vmovmskpd"        , G(AvxRm_P)       , F(None)                , 0 , O(Gqd)              , O(XmmYmm)           , U                   , U                   , O_660F00(50,U)  , U               ),
  INST(kX86InstIdVmovmskps        , "vmovmskps"        , G(AvxRm_P)       , F(None)                , 0 , O(Gqd)              , O(XmmYmm)           , U                   , U                   , O_000F00(50,U)  , U               ),
  INST(kX86InstIdVmovntdq         , "vmovntdq"         , G(AvxMr)         , F(None)                , 0 , O(Mem)              , O(XmmYmm)           , U                   , U                   , O_660F00(E7,U)  , U               ),
  INST(kX86InstIdVmovntdqa        , "vmovntdqa"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(Mem)              , U                   , U                   , O_660F38(2A,U)  , U               ),
  INST(kX86InstIdVmovntpd         , "vmovntpd"         , G(AvxMr_P)       , F(None)                , 0 , O(Mem)              , O(XmmYmm)           , U                   , U                   , O_660F00(2B,U)  , U               ),
  INST(kX86InstIdVmovntps         , "vmovntps"         , G(AvxMr_P)       , F(None)                , 0 , O(Mem)              , O(XmmYmm)           , U                   , U                   , O_000F00(2B,U)  , U               ),
  INST(kX86InstIdVmovq            , "vmovq"            , G(AvxRmMr)       , F(None)           |F(W), 0 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_660F00(6E,U)  , O_660F00(7E,U)  ),
  INST(kX86InstIdVmovsd           , "vmovsd"           , G(AvxMovSsSd)    , F(None)                , 0 , O(XmmMem)           , O(XmmMem)           , O(Xmm)              , U                   , O_F20F00(10,U)  , O_F20F00(11,U)  ),
  INST(kX86InstIdVmovshdup        , "vmovshdup"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_F30F00(16,U)  , U               ),
  INST(kX86InstIdVmovsldup        , "vmovsldup"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_F30F00(12,U)  , U               ),
  INST(kX86InstIdVmovss           , "vmovss"           , G(AvxMovSsSd)    , F(None)                , 0 , O(XmmMem)           , O(Xmm)              , O(Xmm)              , U                   , O_F30F00(10,U)  , O_F30F00(11,U)  ),
  INST(kX86InstIdVmovupd          , "vmovupd"          , G(AvxRmMr_P)     , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   , O_660F00(10,U)  , O_660F00(11,U)  ),
  INST(kX86InstIdVmovups          , "vmovups"          , G(AvxRmMr_P)     , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmmMem)        , U                   , U                   , O_000F00(10,U)  , O_000F00(11,U)  ),
  INST(kX86InstIdVmpsadbw         , "vmpsadbw"         , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F3A(42,U)  , U               ),
  INST(kX86InstIdVmulpd           , "vmulpd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(59,U)  , U               ),
  INST(kX86InstIdVmulps           , "vmulps"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(59,U)  , U               ),
  INST(kX86InstIdVmulsd           , "vmulsd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F20F00(59,U)  , U               ),
  INST(kX86InstIdVmulss           , "vmulss"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_F30F00(59,U)  , U               ),
  INST(kX86InstIdVorpd            , "vorpd"            , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(56,U)  , U               ),
  INST(kX86InstIdVorps            , "vorps"            , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(56,U)  , U               ),
  INST(kX86InstIdVpabsb           , "vpabsb"           , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(1C,U)  , U               ),
  INST(kX86InstIdVpabsd           , "vpabsd"           , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(1E,U)  , U               ),
  INST(kX86InstIdVpabsw           , "vpabsw"           , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(1D,U)  , U               ),
  INST(kX86InstIdVpackssdw        , "vpackssdw"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(6B,U)  , U               ),
  INST(kX86InstIdVpacksswb        , "vpacksswb"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(63,U)  , U               ),
  INST(kX86InstIdVpackusdw        , "vpackusdw"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(2B,U)  , U               ),
  INST(kX86InstIdVpackuswb        , "vpackuswb"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(67,U)  , U               ),
  INST(kX86InstIdVpaddb           , "vpaddb"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(FC,U)  , U               ),
  INST(kX86InstIdVpaddd           , "vpaddd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(FE,U)  , U               ),
  INST(kX86InstIdVpaddq           , "vpaddq"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(D4,U)  , U               ),
  INST(kX86InstIdVpaddsb          , "vpaddsb"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(EC,U)  , U               ),
  INST(kX86InstIdVpaddsw          , "vpaddsw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(ED,U)  , U               ),
  INST(kX86InstIdVpaddusb         , "vpaddusb"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(DC,U)  , U               ),
  INST(kX86InstIdVpaddusw         , "vpaddusw"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(DD,U)  , U               ),
  INST(kX86InstIdVpaddw           , "vpaddw"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(FD,U)  , U               ),
  INST(kX86InstIdVpalignr         , "vpalignr"         , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F3A(0F,U)  , U               ),
  INST(kX86InstIdVpand            , "vpand"            , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(DB,U)  , U               ),
  INST(kX86InstIdVpandn           , "vpandn"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(DF,U)  , U               ),
  INST(kX86InstIdVpavgb           , "vpavgb"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(E0,U)  , U               ),
  INST(kX86InstIdVpavgw           , "vpavgw"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(E3,U)  , U               ),
  INST(kX86InstIdVpblendd         , "vpblendd"         , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F3A(02,U)  , U               ),
  INST(kX86InstIdVpblendvb        , "vpblendvb"        , G(AvxRvmr)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmm)           , O_660F3A(4C,U)  , U               ),
  INST(kX86InstIdVpblendw         , "vpblendw"         , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F3A(0E,U)  , U               ),
  INST(kX86InstIdVpbroadcastb     , "vpbroadcastb"     , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmMem)           , U                   , U                   , O_660F38(78,U)  , U               ),
  INST(kX86InstIdVpbroadcastd     , "vpbroadcastd"     , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmMem)           , U                   , U                   , O_660F38(58,U)  , U               ),
  INST(kX86InstIdVpbroadcastq     , "vpbroadcastq"     , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmMem)           , U                   , U                   , O_660F38(59,U)  , U               ),
  INST(kX86InstIdVpbroadcastw     , "vpbroadcastw"     , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmMem)           , U                   , U                   , O_660F38(79,U)  , U               ),
  INST(kX86InstIdVpclmulqdq       , "vpclmulqdq"       , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_660F3A(44,U)  , U               ),
  INST(kX86InstIdVpcmov           , "vpcmov"           , G(XopRvrmRvmr_P) , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_00_M08(A2,U)  , U               ),
  INST(kX86InstIdVpcmpeqb         , "vpcmpeqb"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(74,U)  , U               ),
  INST(kX86InstIdVpcmpeqd         , "vpcmpeqd"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(76,U)  , U               ),
  INST(kX86InstIdVpcmpeqq         , "vpcmpeqq"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(29,U)  , U               ),
  INST(kX86InstIdVpcmpeqw         , "vpcmpeqw"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(75,U)  , U               ),
  INST(kX86InstIdVpcmpestri       , "vpcmpestri"       , G(AvxRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(61,U)  , U               ),
  INST(kX86InstIdVpcmpestrm       , "vpcmpestrm"       , G(AvxRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(60,U)  , U               ),
  INST(kX86InstIdVpcmpgtb         , "vpcmpgtb"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(64,U)  , U               ),
  INST(kX86InstIdVpcmpgtd         , "vpcmpgtd"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(66,U)  , U               ),
  INST(kX86InstIdVpcmpgtq         , "vpcmpgtq"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(37,U)  , U               ),
  INST(kX86InstIdVpcmpgtw         , "vpcmpgtw"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(65,U)  , U               ),
  INST(kX86InstIdVpcmpistri       , "vpcmpistri"       , G(AvxRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(63,U)  , U               ),
  INST(kX86InstIdVpcmpistrm       , "vpcmpistrm"       , G(AvxRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_660F3A(62,U)  , U               ),
  INST(kX86InstIdVpcomb           , "vpcomb"           , G(XopRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_00_M08(CC,U)  , U               ),
  INST(kX86InstIdVpcomd           , "vpcomd"           , G(XopRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_00_M08(CE,U)  , U               ),
  INST(kX86InstIdVpcomq           , "vpcomq"           , G(XopRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_00_M08(CF,U)  , U               ),
  INST(kX86InstIdVpcomub          , "vpcomub"          , G(XopRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_00_M08(EC,U)  , U               ),
  INST(kX86InstIdVpcomud          , "vpcomud"          , G(XopRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_00_M08(EE,U)  , U               ),
  INST(kX86InstIdVpcomuq          , "vpcomuq"          , G(XopRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_00_M08(EF,U)  , U               ),
  INST(kX86InstIdVpcomuw          , "vpcomuw"          , G(XopRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_00_M08(ED,U)  , U               ),
  INST(kX86InstIdVpcomw           , "vpcomw"           , G(XopRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_00_M08(CD,U)  , U               ),
  INST(kX86InstIdVperm2f128       , "vperm2f128"       , G(AvxRvmi)       , F(None)                , 0 , O(Ymm)              , O(Ymm)              , O(YmmMem)           , O(Imm)              , O_660F3A(06,U)|L, U               ),
  INST(kX86InstIdVperm2i128       , "vperm2i128"       , G(AvxRvmi)       , F(None)                , 0 , O(Ymm)              , O(Ymm)              , O(YmmMem)           , O(Imm)              , O_660F3A(46,U)|L, U               ),
  INST(kX86InstIdVpermd           , "vpermd"           , G(AvxRvm)        , F(None)                , 0 , O(Ymm)              , O(Ymm)              , O(YmmMem)           , U                   , O_660F38(36,U)|L, U               ),
  INST(kX86InstIdVpermil2pd       , "vpermil2pd"       , G(AvxRvrmRvmr_P) , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_66_M03(49,U)  , U               ),
  INST(kX86InstIdVpermil2ps       , "vpermil2ps"       , G(AvxRvrmRvmr_P) , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)        , O_66_M03(48,U)  , U               ),
  INST(kX86InstIdVpermilpd        , "vpermilpd"        , G(AvxRvmRmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F38(0D,U)  , O_660F3A(05,U)  ),
  INST(kX86InstIdVpermilps        , "vpermilps"        , G(AvxRvmRmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F38(0C,U)  , O_660F3A(04,U)  ),
  INST(kX86InstIdVpermpd          , "vpermpd"          , G(AvxRmi)        , F(None)           |F(W), 0 , O(Ymm)              , O(YmmMem)           , O(Imm)              , U                   , O_660F3A(01,U)|L, U               ),
  INST(kX86InstIdVpermps          , "vpermps"          , G(AvxRvm)        , F(None)                , 0 , O(Ymm)              , O(Ymm)              , O(YmmMem)           , U                   , O_660F38(16,U)|L, U               ),
  INST(kX86InstIdVpermq           , "vpermq"           , G(AvxRmi)        , F(None)           |F(W), 0 , O(Ymm)              , O(YmmMem)           , O(Imm)              , U                   , O_660F3A(00,U)|L, U               ),
  INST(kX86InstIdVpextrb          , "vpextrb"          , G(AvxMri)        , F(None)                , 0 , O(GqdwbMem)         , O(Xmm)              , O(Imm)              , U                   , O_660F3A(14,U)  , U               ),
  INST(kX86InstIdVpextrd          , "vpextrd"          , G(AvxMri)        , F(None)                , 0 , O(GqdMem)           , O(Xmm)              , O(Imm)              , U                   , O_660F3A(16,U)  , U               ),
  INST(kX86InstIdVpextrq          , "vpextrq"          , G(AvxMri)        , F(None)           |F(W), 0 , O(GqMem)            , O(Xmm)              , O(Imm)              , U                   , O_660F3A(16,U)  , U               ),
  INST(kX86InstIdVpextrw          , "vpextrw"          , G(AvxMri)        , F(None)                , 0 , O(GqdwMem)          , O(Xmm)              , O(Imm)              , U                   , O_660F3A(15,U)  , U               ),
  INST(kX86InstIdVpgatherdd       , "vpgatherdd"       , G(AvxGather)     , F(None)                , 0 , O(XmmYmm)           , O(Mem)              , O(XmmYmm)           , U                   , O_660F38(90,U)  , U               ),
  INST(kX86InstIdVpgatherdq       , "vpgatherdq"       , G(AvxGather)     , F(None)           |F(W), 0 , O(XmmYmm)           , O(Mem)              , O(XmmYmm)           , U                   , O_660F38(90,U)  , U               ),
  INST(kX86InstIdVpgatherqd       , "vpgatherqd"       , G(AvxGatherEx)   , F(None)                , 0 , O(Xmm)              , O(Mem)              , O(Xmm)              , U                   , O_660F38(91,U)  , U               ),
  INST(kX86InstIdVpgatherqq       , "vpgatherqq"       , G(AvxGather)     , F(None)           |F(W), 0 , O(XmmYmm)           , O(Mem)              , O(XmmYmm)           , U                   , O_660F38(91,U)  , U               ),
  INST(kX86InstIdVphaddbd         , "vphaddbd"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(C2,U)  , U               ),
  INST(kX86InstIdVphaddbq         , "vphaddbq"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(C3,U)  , U               ),
  INST(kX86InstIdVphaddbw         , "vphaddbw"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(C1,U)  , U               ),
  INST(kX86InstIdVphaddd          , "vphaddd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(02,U)  , U               ),
  INST(kX86InstIdVphadddq         , "vphadddq"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(CB,U)  , U               ),
  INST(kX86InstIdVphaddsw         , "vphaddsw"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(03,U)  , U               ),
  INST(kX86InstIdVphaddubd        , "vphaddubd"        , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(D2,U)  , U               ),
  INST(kX86InstIdVphaddubq        , "vphaddubq"        , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(D3,U)  , U               ),
  INST(kX86InstIdVphaddubw        , "vphaddubw"        , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(D1,U)  , U               ),
  INST(kX86InstIdVphaddudq        , "vphaddudq"        , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(DB,U)  , U               ),
  INST(kX86InstIdVphadduwd        , "vphadduwd"        , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(D6,U)  , U               ),
  INST(kX86InstIdVphadduwq        , "vphadduwq"        , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(D7,U)  , U               ),
  INST(kX86InstIdVphaddw          , "vphaddw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(01,U)  , U               ),
  INST(kX86InstIdVphaddwd         , "vphaddwd"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(C6,U)  , U               ),
  INST(kX86InstIdVphaddwq         , "vphaddwq"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(C7,U)  , U               ),
  INST(kX86InstIdVphminposuw      , "vphminposuw"      , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F38(41,U)  , U               ),
  INST(kX86InstIdVphsubbw         , "vphsubbw"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(E1,U)  , U               ),
  INST(kX86InstIdVphsubd          , "vphsubd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(06,U)  , U               ),
  INST(kX86InstIdVphsubdq         , "vphsubdq"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(E3,U)  , U               ),
  INST(kX86InstIdVphsubsw         , "vphsubsw"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(07,U)  , U               ),
  INST(kX86InstIdVphsubw          , "vphsubw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(05,U)  , U               ),
  INST(kX86InstIdVphsubwd         , "vphsubwd"         , G(XopRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_00_M09(E2,U)  , U               ),
  INST(kX86InstIdVpinsrb          , "vpinsrb"          , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(GqdwbMem)         , O(Imm)              , O_660F3A(20,U)  , U               ),
  INST(kX86InstIdVpinsrd          , "vpinsrd"          , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(GqdMem)           , O(Imm)              , O_660F3A(22,U)  , U               ),
  INST(kX86InstIdVpinsrq          , "vpinsrq"          , G(AvxRvmi)       , F(None)           |F(W), 0 , O(Xmm)              , O(Xmm)              , O(GqMem)            , O(Imm)              , O_660F3A(22,U)  , U               ),
  INST(kX86InstIdVpinsrw          , "vpinsrw"          , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(GqdwMem)          , O(Imm)              , O_660F00(C4,U)  , U               ),
  INST(kX86InstIdVpmacsdd         , "vpmacsdd"         , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(9E,U)  , U               ),
  INST(kX86InstIdVpmacsdqh        , "vpmacsdqh"        , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(9F,U)  , U               ),
  INST(kX86InstIdVpmacsdql        , "vpmacsdql"        , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(97,U)  , U               ),
  INST(kX86InstIdVpmacssdd        , "vpmacssdd"        , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(8E,U)  , U               ),
  INST(kX86InstIdVpmacssdqh       , "vpmacssdqh"       , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(8F,U)  , U               ),
  INST(kX86InstIdVpmacssdql       , "vpmacssdql"       , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(87,U)  , U               ),
  INST(kX86InstIdVpmacsswd        , "vpmacsswd"        , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(86,U)  , U               ),
  INST(kX86InstIdVpmacssww        , "vpmacssww"        , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(85,U)  , U               ),
  INST(kX86InstIdVpmacswd         , "vpmacswd"         , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(96,U)  , U               ),
  INST(kX86InstIdVpmacsww         , "vpmacsww"         , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(95,U)  , U               ),
  INST(kX86InstIdVpmadcsswd       , "vpmadcsswd"       , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(A6,U)  , U               ),
  INST(kX86InstIdVpmadcswd        , "vpmadcswd"        , G(XopRvmr)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Xmm)              , O_00_M08(B6,U)  , U               ),
  INST(kX86InstIdVpmaddubsw       , "vpmaddubsw"       , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(04,U)  , U               ),
  INST(kX86InstIdVpmaddwd         , "vpmaddwd"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(F5,U)  , U               ),
  INST(kX86InstIdVpmaskmovd       , "vpmaskmovd"       , G(AvxRvmMvr_P)   , F(None)                , 0 , O(XmmYmmMem)        , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(8C,U)  , O_660F38(8E,U)  ),
  INST(kX86InstIdVpmaskmovq       , "vpmaskmovq"       , G(AvxRvmMvr_P)   , F(None)           |F(W), 0 , O(XmmYmmMem)        , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(8C,U)  , O_660F38(8E,U)  ),
  INST(kX86InstIdVpmaxsb          , "vpmaxsb"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(3C,U)  , U               ),
  INST(kX86InstIdVpmaxsd          , "vpmaxsd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(3D,U)  , U               ),
  INST(kX86InstIdVpmaxsw          , "vpmaxsw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(EE,U)  , U               ),
  INST(kX86InstIdVpmaxub          , "vpmaxub"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(DE,U)  , U               ),
  INST(kX86InstIdVpmaxud          , "vpmaxud"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(3F,U)  , U               ),
  INST(kX86InstIdVpmaxuw          , "vpmaxuw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(3E,U)  , U               ),
  INST(kX86InstIdVpminsb          , "vpminsb"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(38,U)  , U               ),
  INST(kX86InstIdVpminsd          , "vpminsd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(39,U)  , U               ),
  INST(kX86InstIdVpminsw          , "vpminsw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(EA,U)  , U               ),
  INST(kX86InstIdVpminub          , "vpminub"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(DA,U)  , U               ),
  INST(kX86InstIdVpminud          , "vpminud"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(3B,U)  , U               ),
  INST(kX86InstIdVpminuw          , "vpminuw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(3A,U)  , U               ),
  INST(kX86InstIdVpmovmskb        , "vpmovmskb"        , G(AvxRm_P)       , F(None)                , 0 , O(Gqd)              , O(XmmYmm)           , U                   , U                   , O_660F00(D7,U)  , U               ),
  INST(kX86InstIdVpmovsxbd        , "vpmovsxbd"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(21,U)  , U               ),
  INST(kX86InstIdVpmovsxbq        , "vpmovsxbq"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(22,U)  , U               ),
  INST(kX86InstIdVpmovsxbw        , "vpmovsxbw"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(20,U)  , U               ),
  INST(kX86InstIdVpmovsxdq        , "vpmovsxdq"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(25,U)  , U               ),
  INST(kX86InstIdVpmovsxwd        , "vpmovsxwd"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(23,U)  , U               ),
  INST(kX86InstIdVpmovsxwq        , "vpmovsxwq"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(24,U)  , U               ),
  INST(kX86InstIdVpmovzxbd        , "vpmovzxbd"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(31,U)  , U               ),
  INST(kX86InstIdVpmovzxbq        , "vpmovzxbq"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(32,U)  , U               ),
  INST(kX86InstIdVpmovzxbw        , "vpmovzxbw"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(30,U)  , U               ),
  INST(kX86InstIdVpmovzxdq        , "vpmovzxdq"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(35,U)  , U               ),
  INST(kX86InstIdVpmovzxwd        , "vpmovzxwd"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(33,U)  , U               ),
  INST(kX86InstIdVpmovzxwq        , "vpmovzxwq"        , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(34,U)  , U               ),
  INST(kX86InstIdVpmuldq          , "vpmuldq"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(28,U)  , U               ),
  INST(kX86InstIdVpmulhrsw        , "vpmulhrsw"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(0B,U)  , U               ),
  INST(kX86InstIdVpmulhuw         , "vpmulhuw"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(E4,U)  , U               ),
  INST(kX86InstIdVpmulhw          , "vpmulhw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(E5,U)  , U               ),
  INST(kX86InstIdVpmulld          , "vpmulld"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(40,U)  , U               ),
  INST(kX86InstIdVpmullw          , "vpmullw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(D5,U)  , U               ),
  INST(kX86InstIdVpmuludq         , "vpmuludq"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(F4,U)  , U               ),
  INST(kX86InstIdVpor             , "vpor"             , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(EB,U)  , U               ),
  INST(kX86InstIdVpperm           , "vpperm"           , G(XopRvrmRvmr)   , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , O_00_M08(A3,U)  , U               ),
  INST(kX86InstIdVprotb           , "vprotb"           , G(XopRvmRmi)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)|O(Imm)    , U                   , O_00_M09(90,U)  , O_00_M08(C0,U)  ),
  INST(kX86InstIdVprotd           , "vprotd"           , G(XopRvmRmi)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)|O(Imm)    , U                   , O_00_M09(92,U)  , O_00_M08(C2,U)  ),
  INST(kX86InstIdVprotq           , "vprotq"           , G(XopRvmRmi)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)|O(Imm)    , U                   , O_00_M09(93,U)  , O_00_M08(C3,U)  ),
  INST(kX86InstIdVprotw           , "vprotw"           , G(XopRvmRmi)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)|O(Imm)    , U                   , O_00_M09(91,U)  , O_00_M08(C1,U)  ),
  INST(kX86InstIdVpsadbw          , "vpsadbw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(F6,U)  , U               ),
  INST(kX86InstIdVpshab           , "vpshab"           , G(XopRvmRmv)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   , O_00_M09(98,U)  , U               ),
  INST(kX86InstIdVpshad           , "vpshad"           , G(XopRvmRmv)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   , O_00_M09(9A,U)  , U               ),
  INST(kX86InstIdVpshaq           , "vpshaq"           , G(XopRvmRmv)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   , O_00_M09(9B,U)  , U               ),
  INST(kX86InstIdVpshaw           , "vpshaw"           , G(XopRvmRmv)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   , O_00_M09(99,U)  , U               ),
  INST(kX86InstIdVpshlb           , "vpshlb"           , G(XopRvmRmv)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   , O_00_M09(94,U)  , U               ),
  INST(kX86InstIdVpshld           , "vpshld"           , G(XopRvmRmv)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   , O_00_M09(96,U)  , U               ),
  INST(kX86InstIdVpshlq           , "vpshlq"           , G(XopRvmRmv)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   , O_00_M09(97,U)  , U               ),
  INST(kX86InstIdVpshlw           , "vpshlw"           , G(XopRvmRmv)     , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(XmmMem)           , U                   , O_00_M09(95,U)  , U               ),
  INST(kX86InstIdVpshufb          , "vpshufb"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(00,U)  , U               ),
  INST(kX86InstIdVpshufd          , "vpshufd"          , G(AvxRmi_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   , O_660F00(70,U)  , U               ),
  INST(kX86InstIdVpshufhw         , "vpshufhw"         , G(AvxRmi_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   , O_F30F00(70,U)  , U               ),
  INST(kX86InstIdVpshuflw         , "vpshuflw"         , G(AvxRmi_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   , O_F20F00(70,U)  , U               ),
  INST(kX86InstIdVpsignb          , "vpsignb"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(08,U)  , U               ),
  INST(kX86InstIdVpsignd          , "vpsignd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(0A,U)  , U               ),
  INST(kX86InstIdVpsignw          , "vpsignw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(09,U)  , U               ),
  INST(kX86InstIdVpslld           , "vpslld"           , G(AvxRvmVmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F00(F2,U)  , O_660F00(72,6)  ),
  INST(kX86InstIdVpslldq          , "vpslldq"          , G(AvxVmi_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   , O_660F00(73,7)  , U               ),
  INST(kX86InstIdVpsllq           , "vpsllq"           , G(AvxRvmVmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F00(F3,U)  , O_660F00(73,6)  ),
  INST(kX86InstIdVpsllvd          , "vpsllvd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(47,U)  , U               ),
  INST(kX86InstIdVpsllvq          , "vpsllvq"          , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(47,U)  , U               ),
  INST(kX86InstIdVpsllw           , "vpsllw"           , G(AvxRvmVmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F00(F1,U)  , O_660F00(71,6)  ),
  INST(kX86InstIdVpsrad           , "vpsrad"           , G(AvxRvmVmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F00(E2,U)  , O_660F00(72,4)  ),
  INST(kX86InstIdVpsravd          , "vpsravd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(46,U)  , U               ),
  INST(kX86InstIdVpsraw           , "vpsraw"           , G(AvxRvmVmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F00(E1,U)  , O_660F00(71,4)  ),
  INST(kX86InstIdVpsrld           , "vpsrld"           , G(AvxRvmVmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F00(D2,U)  , O_660F00(72,2)  ),
  INST(kX86InstIdVpsrldq          , "vpsrldq"          , G(AvxVmi_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   , O_660F00(73,3)  , U               ),
  INST(kX86InstIdVpsrlq           , "vpsrlq"           , G(AvxRvmVmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F00(D3,U)  , O_660F00(73,2)  ),
  INST(kX86InstIdVpsrlvd          , "vpsrlvd"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(45,U)  , U               ),
  INST(kX86InstIdVpsrlvq          , "vpsrlvq"          , G(AvxRvm_P)      , F(None)           |F(W), 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F38(45,U)  , U               ),
  INST(kX86InstIdVpsrlw           , "vpsrlw"           , G(AvxRvmVmi_P)   , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(XmmYmmMem)|O(Imm) , U                   , O_660F00(D1,U)  , O_660F00(71,2)  ),
  INST(kX86InstIdVpsubb           , "vpsubb"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(F8,U)  , U               ),
  INST(kX86InstIdVpsubd           , "vpsubd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(FA,U)  , U               ),
  INST(kX86InstIdVpsubq           , "vpsubq"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(FB,U)  , U               ),
  INST(kX86InstIdVpsubsb          , "vpsubsb"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(E8,U)  , U               ),
  INST(kX86InstIdVpsubsw          , "vpsubsw"          , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(E9,U)  , U               ),
  INST(kX86InstIdVpsubusb         , "vpsubusb"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(D8,U)  , U               ),
  INST(kX86InstIdVpsubusw         , "vpsubusw"         , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(D9,U)  , U               ),
  INST(kX86InstIdVpsubw           , "vpsubw"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(F9,U)  , U               ),
  INST(kX86InstIdVptest           , "vptest"           , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(17,U)  , U               ),
  INST(kX86InstIdVpunpckhbw       , "vpunpckhbw"       , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(68,U)  , U               ),
  INST(kX86InstIdVpunpckhdq       , "vpunpckhdq"       , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(6A,U)  , U               ),
  INST(kX86InstIdVpunpckhqdq      , "vpunpckhqdq"      , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(6D,U)  , U               ),
  INST(kX86InstIdVpunpckhwd       , "vpunpckhwd"       , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(69,U)  , U               ),
  INST(kX86InstIdVpunpcklbw       , "vpunpcklbw"       , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(60,U)  , U               ),
  INST(kX86InstIdVpunpckldq       , "vpunpckldq"       , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(62,U)  , U               ),
  INST(kX86InstIdVpunpcklqdq      , "vpunpcklqdq"      , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(6C,U)  , U               ),
  INST(kX86InstIdVpunpcklwd       , "vpunpcklwd"       , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(61,U)  , U               ),
  INST(kX86InstIdVpxor            , "vpxor"            , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(EF,U)  , U               ),
  INST(kX86InstIdVrcpps           , "vrcpps"           , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_000F00(53,U)  , U               ),
  INST(kX86InstIdVrcpss           , "vrcpss"           , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F30F00(53,U)  , U               ),
  INST(kX86InstIdVroundpd         , "vroundpd"         , G(AvxRmi_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   , O_660F3A(09,U)  , U               ),
  INST(kX86InstIdVroundps         , "vroundps"         , G(AvxRmi_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , U                   , O_660F3A(08,U)  , U               ),
  INST(kX86InstIdVroundsd         , "vroundsd"         , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_660F3A(0B,U)  , U               ),
  INST(kX86InstIdVroundss         , "vroundss"         , G(AvxRvmi)       , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , O(Imm)              , O_660F3A(0A,U)  , U               ),
  INST(kX86InstIdVrsqrtps         , "vrsqrtps"         , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_000F00(52,U)  , U               ),
  INST(kX86InstIdVrsqrtss         , "vrsqrtss"         , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F30F00(52,U)  , U               ),
  INST(kX86InstIdVshufpd          , "vshufpd"          , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_660F00(C6,U)  , U               ),
  INST(kX86InstIdVshufps          , "vshufps"          , G(AvxRvmi_P)     , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , O(Imm)              , O_000F00(C6,U)  , U               ),
  INST(kX86InstIdVsqrtpd          , "vsqrtpd"          , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F00(51,U)  , U               ),
  INST(kX86InstIdVsqrtps          , "vsqrtps"          , G(AvxRm_P)       , F(None)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_000F00(51,U)  , U               ),
  INST(kX86InstIdVsqrtsd          , "vsqrtsd"          , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F20F00(51,U)  , U               ),
  INST(kX86InstIdVsqrtss          , "vsqrtss"          , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F30F00(51,U)  , U               ),
  INST(kX86InstIdVstmxcsr         , "vstmxcsr"         , G(AvxM)          , F(None)                , 0 , O(Mem)              , U                   , U                   , U                   , O_000F00(AE,3)  , U               ),
  INST(kX86InstIdVsubpd           , "vsubpd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(5C,U)  , U               ),
  INST(kX86InstIdVsubps           , "vsubps"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(5C,U)  , U               ),
  INST(kX86InstIdVsubsd           , "vsubsd"           , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F20F00(5C,U)  , U               ),
  INST(kX86InstIdVsubss           , "vsubss"           , G(AvxRvm)        , F(None)                , 0 , O(Xmm)              , O(Xmm)              , O(XmmMem)           , U                   , O_F30F00(5C,U)  , U               ),
  INST(kX86InstIdVtestpd          , "vtestpd"          , G(AvxRm_P)       , F(Test)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(0F,U)  , U               ),
  INST(kX86InstIdVtestps          , "vtestps"          , G(AvxRm_P)       , F(Test)                , 0 , O(XmmYmm)           , O(XmmYmmMem)        , U                   , U                   , O_660F38(0E,U)  , U               ),
  INST(kX86InstIdVucomisd         , "vucomisd"         , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(2E,U)  , U               ),
  INST(kX86InstIdVucomiss         , "vucomiss"         , G(AvxRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(2E,U)  , U               ),
  INST(kX86InstIdVunpckhpd        , "vunpckhpd"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(15,U)  , U               ),
  INST(kX86InstIdVunpckhps        , "vunpckhps"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(15,U)  , U               ),
  INST(kX86InstIdVunpcklpd        , "vunpcklpd"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(14,U)  , U               ),
  INST(kX86InstIdVunpcklps        , "vunpcklps"        , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(14,U)  , U               ),
  INST(kX86InstIdVxorpd           , "vxorpd"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_660F00(57,U)  , U               ),
  INST(kX86InstIdVxorps           , "vxorps"           , G(AvxRvm_P)      , F(None)                , 0 , O(XmmYmm)           , O(XmmYmm)           , O(XmmYmmMem)        , U                   , O_000F00(57,U)  , U               ),
  INST(kX86InstIdVzeroall         , "vzeroall"         , G(AvxOp)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000F00(77,U)|L, U               ),
  INST(kX86InstIdVzeroupper       , "vzeroupper"       , G(AvxOp)         , F(None)                , 0 , U                   , U                   , U                   , U                   , O_000F00(77,U)  , U               ),
  INST(kX86InstIdWrfsbase         , "wrfsbase"         , G(X86Rm)         , F(None)                , 0 , O(Gqd)              , U                   , U                   , U                   , O_F30F00(AE,2)  , U               ),
  INST(kX86InstIdWrgsbase         , "wrgsbase"         , G(X86Rm)         , F(None)                , 0 , O(Gqd)              , U                   , U                   , U                   , O_F30F00(AE,3)  , U               ),
  INST(kX86InstIdXadd             , "xadd"             , G(X86Xadd)       , F(Xchg)|F(Lock)        , 0 , O(GqdwbMem)         , O(Gqdwb)            , U                   , U                   , O_000F00(C0,U)  , U               ),
  INST(kX86InstIdXchg             , "xchg"             , G(X86Xchg)       , F(Xchg)|F(Lock)        , 0 , O(GqdwbMem)         , O(Gqdwb)            , U                   , U                   , O_000000(86,U)  , U               ),
  INST(kX86InstIdXor              , "xor"              , G(X86Arith)      , F(Lock)                , 0 , O(GqdwbMem)         , O(GqdwbMem)|O(Imm)  , U                   , U                   , O_000000(30,6)  , U               ),
  INST(kX86InstIdXorpd            , "xorpd"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_660F00(57,U)  , U               ),
  INST(kX86InstIdXorps            , "xorps"            , G(ExtRm)         , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , U                   , U                   , O_000F00(57,U)  , U               )
};

#undef INST

#undef O_00_X
#undef O_9B_X

#undef O_66_M09
#undef O_66_M08
#undef O_66_M03

#undef O_00_M09
#undef O_00_M08
#undef O_00_M03

#undef O_F30F3A
#undef O_F30F38
#undef O_F30F00
#undef O_F30000
#undef O_F20F3A
#undef O_F20F38
#undef O_F20F00
#undef O_F20000
#undef O_9B0000
#undef O_660F3A
#undef O_660F38
#undef O_660F00
#undef O_660000
#undef O_000F3A
#undef O_000F38
#undef O_000F0F
#undef O_000F01
#undef O_000F00
#undef O_000000

#undef L
#undef U

#undef O
#undef F
#undef G

// ============================================================================
// [asmjit::X86Cond]
// ============================================================================

#define CC_TO_INST(_Inst_) { \
  _Inst_##o,  \
  _Inst_##no, \
  _Inst_##b,  \
  _Inst_##ae, \
  _Inst_##e,  \
  _Inst_##ne, \
  _Inst_##be, \
  _Inst_##a,  \
  _Inst_##s,  \
  _Inst_##ns, \
  _Inst_##pe, \
  _Inst_##po, \
  _Inst_##l,  \
  _Inst_##ge, \
  _Inst_##le, \
  _Inst_##g,  \
  \
  kInstIdNone,  \
  kInstIdNone,  \
  kInstIdNone,  \
  kInstIdNone   \
}

const uint32_t _x86ReverseCond[20] = {
  /* kX86CondO  -> */ kX86CondO,
  /* kX86CondNO -> */ kX86CondNO,
  /* kX86CondB  -> */ kX86CondA,
  /* kX86CondAE -> */ kX86CondBE,
  /* kX86CondE  -> */ kX86CondE,
  /* kX86CondNE -> */ kX86CondNE,
  /* kX86CondBE -> */ kX86CondAE,
  /* kX86CondA  -> */ kX86CondB,
  /* kX86CondS  -> */ kX86CondS,
  /* kX86CondNS -> */ kX86CondNS,
  /* kX86CondPE -> */ kX86CondPE,
  /* kX86CondPO -> */ kX86CondPO,

  /* kX86CondL  -> */ kX86CondG,
  /* kX86CondGE -> */ kX86CondLE,

  /* kX86CondLE -> */ kX86CondGE,
  /* kX86CondG  -> */ kX86CondL,

  /* kX86CondFpuUnordered    -> */ kX86CondFpuUnordered,
  /* kX86CondFpuNotUnordered -> */ kX86CondFpuNotUnordered,

  0x12,
  0x13
};

const uint32_t _x86CondToCmovcc[20] = CC_TO_INST(kX86InstIdCmov);
const uint32_t _x86CondToJcc   [20] = CC_TO_INST(kX86InstIdJ   );
const uint32_t _x86CondToSetcc [20] = CC_TO_INST(kX86InstIdSet );

#undef CC_TO_INST

// ============================================================================
// [asmjit::X86Util]
// ============================================================================

#if !defined(ASMJIT_DISABLE_INST_NAMES)
// Compare two instruction names.
//
// `a` is null terminated instruction name from `_x86InstName[]` table.
// `b` is non-null terminated instruction name passed to `getInstIdByName()`.
static ASMJIT_INLINE int X86Util_cmpInstName(const char* a, const char* b, size_t len) {
  for (size_t i = 0; i < len; i++) {
    int c = static_cast<int>(static_cast<uint8_t>(a[i])) -
            static_cast<int>(static_cast<uint8_t>(b[i])) ;
    if (c != 0)
      return c;
  }

  return static_cast<int>(a[len]);
}

uint32_t X86Util::getInstIdByName(const char* name, size_t len) {
  if (name == NULL)
    return kInstIdNone;

  if (len == kInvalidIndex)
    len = ::strlen(name);

  if (len == 0)
    return kInstIdNone;

  uint32_t prefix = name[0] - kX86InstAlphaIndexFirst;
  if (prefix > kX86InstAlphaIndexLast - kX86InstAlphaIndexFirst)
    return kInstIdNone;

  uint32_t index = _x86InstAlphaIndex[prefix];
  if (index == kX86InstAlphaIndexInvalid)
    return kInstIdNone;

  const X86InstInfo* base = _x86InstInfo + index;
  const X86InstInfo* end = _x86InstInfo + _kX86InstIdCount;

  // Handle instructions starting with 'j' specially. `jcc` instruction breaks
  // the sorting, because of the suffixes (it's considered as one instruction),
  // so basically `jecxz` and `jmp` are stored after all `jcc` instructions.
  bool linearSearch = prefix == ('j' - kX86InstAlphaIndexFirst);

  while (++prefix <= kX86InstAlphaIndexLast - kX86InstAlphaIndexFirst) {
    index = _x86InstAlphaIndex[prefix];
    if (index == kX86InstAlphaIndexInvalid)
      continue;
    end = _x86InstInfo + index;
    break;
  }

  if (linearSearch) {
    while (base != end) {
      if (X86Util_cmpInstName(base->getName(), name, len) == 0)
        return static_cast<uint32_t>((size_t)(base - _x86InstInfo));
      base++;
    }
  }
  else {
    for (size_t lim = (size_t)(end - base); lim != 0; lim >>= 1) {
      const X86InstInfo* cur = base + (lim >> 1);
      int result = X86Util_cmpInstName(cur->getName(), name, len);

      if (result < 0) {
        base = cur + 1;
        lim--;
        continue;
      }

      if (result > 0)
        continue;

      return static_cast<uint32_t>((size_t)(cur - _x86InstInfo));
    }
  }

  return kInstIdNone;
}
#endif // ASMJIT_DISABLE_INST_NAMES

// ============================================================================
// [asmjit::X86Util - Test]
// ============================================================================

#if defined(ASMJIT_TEST) && !defined(ASMJIT_DISABLE_INST_NAMES)
UNIT(x86_inst_name) {
  // All known instructions should be matched.
  for (uint32_t a = 0; a < _kX86InstIdCount; a++) {
    uint32_t b = X86Util::getInstIdByName(_x86InstInfo[a].getName());

    EXPECT(a == b,
      "Should match existing instruction \"%s\" {id:%u} != \"%s\" {id:%u}.",
        _x86InstInfo[a].getName(), a,
        _x86InstInfo[b].getName(), b);
  }

  // Everything else should return kInstIdNone
  EXPECT(X86Util::getInstIdByName(NULL) == kInstIdNone,
    "Should return kInstIdNone for NULL input.");

  EXPECT(X86Util::getInstIdByName("") == kInstIdNone,
    "Should return kInstIdNone for empty string.");

  EXPECT(X86Util::getInstIdByName("_") == kInstIdNone,
    "Should return kInstIdNone for unknown instruction.");

  EXPECT(X86Util::getInstIdByName("123xyz") == kInstIdNone,
    "Should return kInstIdNone for unknown instruction.");
}
#endif // ASMJIT_TEST && !ASMJIT_DISABLE_INST_NAMES

} // asmjit namespace

#include "../apiend.h"

// [Guard]
#endif // ASMJIT_BUILD_X86 || ASMJIT_BUILD_X64
