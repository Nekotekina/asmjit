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
  "cmpsd\0"
  "cmpss\0"
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
  "movsd\0"
  "movshdup\0"
  "movsldup\0"
  "movss\0"
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
  kX86InstIdCmpsd_NameIndex = 494,
  kX86InstIdCmpss_NameIndex = 500,
  kX86InstIdCmpxchg_NameIndex = 506,
  kX86InstIdCmpxchg16b_NameIndex = 514,
  kX86InstIdCmpxchg8b_NameIndex = 525,
  kX86InstIdComisd_NameIndex = 535,
  kX86InstIdComiss_NameIndex = 542,
  kX86InstIdCpuid_NameIndex = 549,
  kX86InstIdCqo_NameIndex = 555,
  kX86InstIdCrc32_NameIndex = 559,
  kX86InstIdCvtdq2pd_NameIndex = 565,
  kX86InstIdCvtdq2ps_NameIndex = 574,
  kX86InstIdCvtpd2dq_NameIndex = 583,
  kX86InstIdCvtpd2pi_NameIndex = 592,
  kX86InstIdCvtpd2ps_NameIndex = 601,
  kX86InstIdCvtpi2pd_NameIndex = 610,
  kX86InstIdCvtpi2ps_NameIndex = 619,
  kX86InstIdCvtps2dq_NameIndex = 628,
  kX86InstIdCvtps2pd_NameIndex = 637,
  kX86InstIdCvtps2pi_NameIndex = 646,
  kX86InstIdCvtsd2si_NameIndex = 655,
  kX86InstIdCvtsd2ss_NameIndex = 664,
  kX86InstIdCvtsi2sd_NameIndex = 673,
  kX86InstIdCvtsi2ss_NameIndex = 682,
  kX86InstIdCvtss2sd_NameIndex = 691,
  kX86InstIdCvtss2si_NameIndex = 700,
  kX86InstIdCvttpd2dq_NameIndex = 709,
  kX86InstIdCvttpd2pi_NameIndex = 719,
  kX86InstIdCvttps2dq_NameIndex = 729,
  kX86InstIdCvttps2pi_NameIndex = 739,
  kX86InstIdCvttsd2si_NameIndex = 749,
  kX86InstIdCvttss2si_NameIndex = 759,
  kX86InstIdCwd_NameIndex = 769,
  kX86InstIdCwde_NameIndex = 773,
  kX86InstIdDaa_NameIndex = 778,
  kX86InstIdDas_NameIndex = 782,
  kX86InstIdDec_NameIndex = 786,
  kX86InstIdDiv_NameIndex = 790,
  kX86InstIdDivpd_NameIndex = 794,
  kX86InstIdDivps_NameIndex = 800,
  kX86InstIdDivsd_NameIndex = 806,
  kX86InstIdDivss_NameIndex = 812,
  kX86InstIdDppd_NameIndex = 818,
  kX86InstIdDpps_NameIndex = 823,
  kX86InstIdEmms_NameIndex = 828,
  kX86InstIdEnter_NameIndex = 833,
  kX86InstIdExtractps_NameIndex = 839,
  kX86InstIdF2xm1_NameIndex = 849,
  kX86InstIdFabs_NameIndex = 855,
  kX86InstIdFadd_NameIndex = 860,
  kX86InstIdFaddp_NameIndex = 865,
  kX86InstIdFbld_NameIndex = 871,
  kX86InstIdFbstp_NameIndex = 876,
  kX86InstIdFchs_NameIndex = 882,
  kX86InstIdFclex_NameIndex = 887,
  kX86InstIdFcmovb_NameIndex = 893,
  kX86InstIdFcmovbe_NameIndex = 900,
  kX86InstIdFcmove_NameIndex = 908,
  kX86InstIdFcmovnb_NameIndex = 915,
  kX86InstIdFcmovnbe_NameIndex = 923,
  kX86InstIdFcmovne_NameIndex = 932,
  kX86InstIdFcmovnu_NameIndex = 940,
  kX86InstIdFcmovu_NameIndex = 948,
  kX86InstIdFcom_NameIndex = 955,
  kX86InstIdFcomi_NameIndex = 960,
  kX86InstIdFcomip_NameIndex = 966,
  kX86InstIdFcomp_NameIndex = 973,
  kX86InstIdFcompp_NameIndex = 979,
  kX86InstIdFcos_NameIndex = 986,
  kX86InstIdFdecstp_NameIndex = 991,
  kX86InstIdFdiv_NameIndex = 999,
  kX86InstIdFdivp_NameIndex = 1004,
  kX86InstIdFdivr_NameIndex = 1010,
  kX86InstIdFdivrp_NameIndex = 1016,
  kX86InstIdFemms_NameIndex = 1023,
  kX86InstIdFfree_NameIndex = 1029,
  kX86InstIdFiadd_NameIndex = 1035,
  kX86InstIdFicom_NameIndex = 1041,
  kX86InstIdFicomp_NameIndex = 1047,
  kX86InstIdFidiv_NameIndex = 1054,
  kX86InstIdFidivr_NameIndex = 1060,
  kX86InstIdFild_NameIndex = 1067,
  kX86InstIdFimul_NameIndex = 1072,
  kX86InstIdFincstp_NameIndex = 1078,
  kX86InstIdFinit_NameIndex = 1086,
  kX86InstIdFist_NameIndex = 1092,
  kX86InstIdFistp_NameIndex = 1097,
  kX86InstIdFisttp_NameIndex = 1103,
  kX86InstIdFisub_NameIndex = 1110,
  kX86InstIdFisubr_NameIndex = 1116,
  kX86InstIdFld_NameIndex = 1123,
  kX86InstIdFld1_NameIndex = 1127,
  kX86InstIdFldcw_NameIndex = 1132,
  kX86InstIdFldenv_NameIndex = 1138,
  kX86InstIdFldl2e_NameIndex = 1145,
  kX86InstIdFldl2t_NameIndex = 1152,
  kX86InstIdFldlg2_NameIndex = 1159,
  kX86InstIdFldln2_NameIndex = 1166,
  kX86InstIdFldpi_NameIndex = 1173,
  kX86InstIdFldz_NameIndex = 1179,
  kX86InstIdFmul_NameIndex = 1184,
  kX86InstIdFmulp_NameIndex = 1189,
  kX86InstIdFnclex_NameIndex = 1195,
  kX86InstIdFninit_NameIndex = 1202,
  kX86InstIdFnop_NameIndex = 1209,
  kX86InstIdFnsave_NameIndex = 1214,
  kX86InstIdFnstcw_NameIndex = 1221,
  kX86InstIdFnstenv_NameIndex = 1228,
  kX86InstIdFnstsw_NameIndex = 1236,
  kX86InstIdFpatan_NameIndex = 1243,
  kX86InstIdFprem_NameIndex = 1250,
  kX86InstIdFprem1_NameIndex = 1256,
  kX86InstIdFptan_NameIndex = 1263,
  kX86InstIdFrndint_NameIndex = 1269,
  kX86InstIdFrstor_NameIndex = 1277,
  kX86InstIdFsave_NameIndex = 1284,
  kX86InstIdFscale_NameIndex = 1290,
  kX86InstIdFsin_NameIndex = 1297,
  kX86InstIdFsincos_NameIndex = 1302,
  kX86InstIdFsqrt_NameIndex = 1310,
  kX86InstIdFst_NameIndex = 1316,
  kX86InstIdFstcw_NameIndex = 1320,
  kX86InstIdFstenv_NameIndex = 1326,
  kX86InstIdFstp_NameIndex = 1333,
  kX86InstIdFstsw_NameIndex = 1338,
  kX86InstIdFsub_NameIndex = 1344,
  kX86InstIdFsubp_NameIndex = 1349,
  kX86InstIdFsubr_NameIndex = 1355,
  kX86InstIdFsubrp_NameIndex = 1361,
  kX86InstIdFtst_NameIndex = 1368,
  kX86InstIdFucom_NameIndex = 1373,
  kX86InstIdFucomi_NameIndex = 1379,
  kX86InstIdFucomip_NameIndex = 1386,
  kX86InstIdFucomp_NameIndex = 1394,
  kX86InstIdFucompp_NameIndex = 1401,
  kX86InstIdFwait_NameIndex = 1409,
  kX86InstIdFxam_NameIndex = 1415,
  kX86InstIdFxch_NameIndex = 1420,
  kX86InstIdFxrstor_NameIndex = 1425,
  kX86InstIdFxsave_NameIndex = 1433,
  kX86InstIdFxtract_NameIndex = 1440,
  kX86InstIdFyl2x_NameIndex = 1448,
  kX86InstIdFyl2xp1_NameIndex = 1454,
  kX86InstIdHaddpd_NameIndex = 1462,
  kX86InstIdHaddps_NameIndex = 1469,
  kX86InstIdHsubpd_NameIndex = 1476,
  kX86InstIdHsubps_NameIndex = 1483,
  kX86InstIdIdiv_NameIndex = 1490,
  kX86InstIdImul_NameIndex = 1495,
  kX86InstIdInc_NameIndex = 1500,
  kX86InstIdInsertps_NameIndex = 1504,
  kX86InstIdInt_NameIndex = 1513,
  kX86InstIdJa_NameIndex = 1517,
  kX86InstIdJae_NameIndex = 1520,
  kX86InstIdJb_NameIndex = 1524,
  kX86InstIdJbe_NameIndex = 1527,
  kX86InstIdJc_NameIndex = 1531,
  kX86InstIdJe_NameIndex = 1534,
  kX86InstIdJg_NameIndex = 1537,
  kX86InstIdJge_NameIndex = 1540,
  kX86InstIdJl_NameIndex = 1544,
  kX86InstIdJle_NameIndex = 1547,
  kX86InstIdJna_NameIndex = 1551,
  kX86InstIdJnae_NameIndex = 1555,
  kX86InstIdJnb_NameIndex = 1560,
  kX86InstIdJnbe_NameIndex = 1564,
  kX86InstIdJnc_NameIndex = 1569,
  kX86InstIdJne_NameIndex = 1573,
  kX86InstIdJng_NameIndex = 1577,
  kX86InstIdJnge_NameIndex = 1581,
  kX86InstIdJnl_NameIndex = 1586,
  kX86InstIdJnle_NameIndex = 1590,
  kX86InstIdJno_NameIndex = 1595,
  kX86InstIdJnp_NameIndex = 1599,
  kX86InstIdJns_NameIndex = 1603,
  kX86InstIdJnz_NameIndex = 1607,
  kX86InstIdJo_NameIndex = 1611,
  kX86InstIdJp_NameIndex = 1614,
  kX86InstIdJpe_NameIndex = 1617,
  kX86InstIdJpo_NameIndex = 1621,
  kX86InstIdJs_NameIndex = 1625,
  kX86InstIdJz_NameIndex = 1628,
  kX86InstIdJecxz_NameIndex = 1631,
  kX86InstIdJmp_NameIndex = 1637,
  kX86InstIdLahf_NameIndex = 1641,
  kX86InstIdLddqu_NameIndex = 1646,
  kX86InstIdLdmxcsr_NameIndex = 1652,
  kX86InstIdLea_NameIndex = 1660,
  kX86InstIdLeave_NameIndex = 1664,
  kX86InstIdLfence_NameIndex = 1670,
  kX86InstIdLzcnt_NameIndex = 1677,
  kX86InstIdMaskmovdqu_NameIndex = 1683,
  kX86InstIdMaskmovq_NameIndex = 1694,
  kX86InstIdMaxpd_NameIndex = 1703,
  kX86InstIdMaxps_NameIndex = 1709,
  kX86InstIdMaxsd_NameIndex = 1715,
  kX86InstIdMaxss_NameIndex = 1721,
  kX86InstIdMfence_NameIndex = 1727,
  kX86InstIdMinpd_NameIndex = 1734,
  kX86InstIdMinps_NameIndex = 1740,
  kX86InstIdMinsd_NameIndex = 1746,
  kX86InstIdMinss_NameIndex = 1752,
  kX86InstIdMonitor_NameIndex = 1758,
  kX86InstIdMov_NameIndex = 1766,
  kX86InstIdMovPtr_NameIndex = 1770,
  kX86InstIdMovapd_NameIndex = 1778,
  kX86InstIdMovaps_NameIndex = 1785,
  kX86InstIdMovbe_NameIndex = 1792,
  kX86InstIdMovd_NameIndex = 1798,
  kX86InstIdMovddup_NameIndex = 1803,
  kX86InstIdMovdq2q_NameIndex = 1811,
  kX86InstIdMovdqa_NameIndex = 1819,
  kX86InstIdMovdqu_NameIndex = 1826,
  kX86InstIdMovhlps_NameIndex = 1833,
  kX86InstIdMovhpd_NameIndex = 1841,
  kX86InstIdMovhps_NameIndex = 1848,
  kX86InstIdMovlhps_NameIndex = 1855,
  kX86InstIdMovlpd_NameIndex = 1863,
  kX86InstIdMovlps_NameIndex = 1870,
  kX86InstIdMovmskpd_NameIndex = 1877,
  kX86InstIdMovmskps_NameIndex = 1886,
  kX86InstIdMovntdq_NameIndex = 1895,
  kX86InstIdMovntdqa_NameIndex = 1903,
  kX86InstIdMovnti_NameIndex = 1912,
  kX86InstIdMovntpd_NameIndex = 1919,
  kX86InstIdMovntps_NameIndex = 1927,
  kX86InstIdMovntq_NameIndex = 1935,
  kX86InstIdMovq_NameIndex = 1942,
  kX86InstIdMovq2dq_NameIndex = 1947,
  kX86InstIdMovsd_NameIndex = 1955,
  kX86InstIdMovshdup_NameIndex = 1961,
  kX86InstIdMovsldup_NameIndex = 1970,
  kX86InstIdMovss_NameIndex = 1979,
  kX86InstIdMovsx_NameIndex = 1985,
  kX86InstIdMovsxd_NameIndex = 1991,
  kX86InstIdMovupd_NameIndex = 1998,
  kX86InstIdMovups_NameIndex = 2005,
  kX86InstIdMovzx_NameIndex = 2012,
  kX86InstIdMpsadbw_NameIndex = 2018,
  kX86InstIdMul_NameIndex = 2026,
  kX86InstIdMulpd_NameIndex = 2030,
  kX86InstIdMulps_NameIndex = 2036,
  kX86InstIdMulsd_NameIndex = 2042,
  kX86InstIdMulss_NameIndex = 2048,
  kX86InstIdMulx_NameIndex = 2054,
  kX86InstIdMwait_NameIndex = 2059,
  kX86InstIdNeg_NameIndex = 2065,
  kX86InstIdNop_NameIndex = 2069,
  kX86InstIdNot_NameIndex = 2073,
  kX86InstIdOr_NameIndex = 2077,
  kX86InstIdOrpd_NameIndex = 2080,
  kX86InstIdOrps_NameIndex = 2085,
  kX86InstIdPabsb_NameIndex = 2090,
  kX86InstIdPabsd_NameIndex = 2096,
  kX86InstIdPabsw_NameIndex = 2102,
  kX86InstIdPackssdw_NameIndex = 2108,
  kX86InstIdPacksswb_NameIndex = 2117,
  kX86InstIdPackusdw_NameIndex = 2126,
  kX86InstIdPackuswb_NameIndex = 2135,
  kX86InstIdPaddb_NameIndex = 2144,
  kX86InstIdPaddd_NameIndex = 2150,
  kX86InstIdPaddq_NameIndex = 2156,
  kX86InstIdPaddsb_NameIndex = 2162,
  kX86InstIdPaddsw_NameIndex = 2169,
  kX86InstIdPaddusb_NameIndex = 2176,
  kX86InstIdPaddusw_NameIndex = 2184,
  kX86InstIdPaddw_NameIndex = 2192,
  kX86InstIdPalignr_NameIndex = 2198,
  kX86InstIdPand_NameIndex = 2206,
  kX86InstIdPandn_NameIndex = 2211,
  kX86InstIdPause_NameIndex = 2217,
  kX86InstIdPavgb_NameIndex = 2223,
  kX86InstIdPavgw_NameIndex = 2229,
  kX86InstIdPblendvb_NameIndex = 2235,
  kX86InstIdPblendw_NameIndex = 2244,
  kX86InstIdPclmulqdq_NameIndex = 2252,
  kX86InstIdPcmpeqb_NameIndex = 2262,
  kX86InstIdPcmpeqd_NameIndex = 2270,
  kX86InstIdPcmpeqq_NameIndex = 2278,
  kX86InstIdPcmpeqw_NameIndex = 2286,
  kX86InstIdPcmpestri_NameIndex = 2294,
  kX86InstIdPcmpestrm_NameIndex = 2304,
  kX86InstIdPcmpgtb_NameIndex = 2314,
  kX86InstIdPcmpgtd_NameIndex = 2322,
  kX86InstIdPcmpgtq_NameIndex = 2330,
  kX86InstIdPcmpgtw_NameIndex = 2338,
  kX86InstIdPcmpistri_NameIndex = 2346,
  kX86InstIdPcmpistrm_NameIndex = 2356,
  kX86InstIdPdep_NameIndex = 2366,
  kX86InstIdPext_NameIndex = 2371,
  kX86InstIdPextrb_NameIndex = 2376,
  kX86InstIdPextrd_NameIndex = 2383,
  kX86InstIdPextrq_NameIndex = 2390,
  kX86InstIdPextrw_NameIndex = 2397,
  kX86InstIdPf2id_NameIndex = 2404,
  kX86InstIdPf2iw_NameIndex = 2410,
  kX86InstIdPfacc_NameIndex = 2416,
  kX86InstIdPfadd_NameIndex = 2422,
  kX86InstIdPfcmpeq_NameIndex = 2428,
  kX86InstIdPfcmpge_NameIndex = 2436,
  kX86InstIdPfcmpgt_NameIndex = 2444,
  kX86InstIdPfmax_NameIndex = 2452,
  kX86InstIdPfmin_NameIndex = 2458,
  kX86InstIdPfmul_NameIndex = 2464,
  kX86InstIdPfnacc_NameIndex = 2470,
  kX86InstIdPfpnacc_NameIndex = 2477,
  kX86InstIdPfrcp_NameIndex = 2485,
  kX86InstIdPfrcpit1_NameIndex = 2491,
  kX86InstIdPfrcpit2_NameIndex = 2500,
  kX86InstIdPfrsqit1_NameIndex = 2509,
  kX86InstIdPfrsqrt_NameIndex = 2518,
  kX86InstIdPfsub_NameIndex = 2526,
  kX86InstIdPfsubr_NameIndex = 2532,
  kX86InstIdPhaddd_NameIndex = 2539,
  kX86InstIdPhaddsw_NameIndex = 2546,
  kX86InstIdPhaddw_NameIndex = 2554,
  kX86InstIdPhminposuw_NameIndex = 2561,
  kX86InstIdPhsubd_NameIndex = 2572,
  kX86InstIdPhsubsw_NameIndex = 2579,
  kX86InstIdPhsubw_NameIndex = 2587,
  kX86InstIdPi2fd_NameIndex = 2594,
  kX86InstIdPi2fw_NameIndex = 2600,
  kX86InstIdPinsrb_NameIndex = 2606,
  kX86InstIdPinsrd_NameIndex = 2613,
  kX86InstIdPinsrq_NameIndex = 2620,
  kX86InstIdPinsrw_NameIndex = 2627,
  kX86InstIdPmaddubsw_NameIndex = 2634,
  kX86InstIdPmaddwd_NameIndex = 2644,
  kX86InstIdPmaxsb_NameIndex = 2652,
  kX86InstIdPmaxsd_NameIndex = 2659,
  kX86InstIdPmaxsw_NameIndex = 2666,
  kX86InstIdPmaxub_NameIndex = 2673,
  kX86InstIdPmaxud_NameIndex = 2680,
  kX86InstIdPmaxuw_NameIndex = 2687,
  kX86InstIdPminsb_NameIndex = 2694,
  kX86InstIdPminsd_NameIndex = 2701,
  kX86InstIdPminsw_NameIndex = 2708,
  kX86InstIdPminub_NameIndex = 2715,
  kX86InstIdPminud_NameIndex = 2722,
  kX86InstIdPminuw_NameIndex = 2729,
  kX86InstIdPmovmskb_NameIndex = 2736,
  kX86InstIdPmovsxbd_NameIndex = 2745,
  kX86InstIdPmovsxbq_NameIndex = 2754,
  kX86InstIdPmovsxbw_NameIndex = 2763,
  kX86InstIdPmovsxdq_NameIndex = 2772,
  kX86InstIdPmovsxwd_NameIndex = 2781,
  kX86InstIdPmovsxwq_NameIndex = 2790,
  kX86InstIdPmovzxbd_NameIndex = 2799,
  kX86InstIdPmovzxbq_NameIndex = 2808,
  kX86InstIdPmovzxbw_NameIndex = 2817,
  kX86InstIdPmovzxdq_NameIndex = 2826,
  kX86InstIdPmovzxwd_NameIndex = 2835,
  kX86InstIdPmovzxwq_NameIndex = 2844,
  kX86InstIdPmuldq_NameIndex = 2853,
  kX86InstIdPmulhrsw_NameIndex = 2860,
  kX86InstIdPmulhuw_NameIndex = 2869,
  kX86InstIdPmulhw_NameIndex = 2877,
  kX86InstIdPmulld_NameIndex = 2884,
  kX86InstIdPmullw_NameIndex = 2891,
  kX86InstIdPmuludq_NameIndex = 2898,
  kX86InstIdPop_NameIndex = 2906,
  kX86InstIdPopa_NameIndex = 2910,
  kX86InstIdPopcnt_NameIndex = 2915,
  kX86InstIdPopf_NameIndex = 2922,
  kX86InstIdPor_NameIndex = 2927,
  kX86InstIdPrefetch_NameIndex = 2931,
  kX86InstIdPrefetch3dNow_NameIndex = 2940,
  kX86InstIdPrefetchw3dNow_NameIndex = 2955,
  kX86InstIdPsadbw_NameIndex = 2971,
  kX86InstIdPshufb_NameIndex = 2978,
  kX86InstIdPshufd_NameIndex = 2985,
  kX86InstIdPshufhw_NameIndex = 2992,
  kX86InstIdPshuflw_NameIndex = 3000,
  kX86InstIdPshufw_NameIndex = 3008,
  kX86InstIdPsignb_NameIndex = 3015,
  kX86InstIdPsignd_NameIndex = 3022,
  kX86InstIdPsignw_NameIndex = 3029,
  kX86InstIdPslld_NameIndex = 3036,
  kX86InstIdPslldq_NameIndex = 3042,
  kX86InstIdPsllq_NameIndex = 3049,
  kX86InstIdPsllw_NameIndex = 3055,
  kX86InstIdPsrad_NameIndex = 3061,
  kX86InstIdPsraw_NameIndex = 3067,
  kX86InstIdPsrld_NameIndex = 3073,
  kX86InstIdPsrldq_NameIndex = 3079,
  kX86InstIdPsrlq_NameIndex = 3086,
  kX86InstIdPsrlw_NameIndex = 3092,
  kX86InstIdPsubb_NameIndex = 3098,
  kX86InstIdPsubd_NameIndex = 3104,
  kX86InstIdPsubq_NameIndex = 3110,
  kX86InstIdPsubsb_NameIndex = 3116,
  kX86InstIdPsubsw_NameIndex = 3123,
  kX86InstIdPsubusb_NameIndex = 3130,
  kX86InstIdPsubusw_NameIndex = 3138,
  kX86InstIdPsubw_NameIndex = 3146,
  kX86InstIdPswapd_NameIndex = 3152,
  kX86InstIdPtest_NameIndex = 3159,
  kX86InstIdPunpckhbw_NameIndex = 3165,
  kX86InstIdPunpckhdq_NameIndex = 3175,
  kX86InstIdPunpckhqdq_NameIndex = 3185,
  kX86InstIdPunpckhwd_NameIndex = 3196,
  kX86InstIdPunpcklbw_NameIndex = 3206,
  kX86InstIdPunpckldq_NameIndex = 3216,
  kX86InstIdPunpcklqdq_NameIndex = 3226,
  kX86InstIdPunpcklwd_NameIndex = 3237,
  kX86InstIdPush_NameIndex = 3247,
  kX86InstIdPusha_NameIndex = 3252,
  kX86InstIdPushf_NameIndex = 3258,
  kX86InstIdPxor_NameIndex = 3264,
  kX86InstIdRcl_NameIndex = 3269,
  kX86InstIdRcpps_NameIndex = 3273,
  kX86InstIdRcpss_NameIndex = 3279,
  kX86InstIdRcr_NameIndex = 3285,
  kX86InstIdRdfsbase_NameIndex = 3289,
  kX86InstIdRdgsbase_NameIndex = 3298,
  kX86InstIdRdrand_NameIndex = 3307,
  kX86InstIdRdtsc_NameIndex = 3314,
  kX86InstIdRdtscp_NameIndex = 3320,
  kX86InstIdRepLodsb_NameIndex = 3327,
  kX86InstIdRepLodsd_NameIndex = 3337,
  kX86InstIdRepLodsq_NameIndex = 3347,
  kX86InstIdRepLodsw_NameIndex = 3357,
  kX86InstIdRepMovsb_NameIndex = 3367,
  kX86InstIdRepMovsd_NameIndex = 3377,
  kX86InstIdRepMovsq_NameIndex = 3387,
  kX86InstIdRepMovsw_NameIndex = 3397,
  kX86InstIdRepStosb_NameIndex = 3407,
  kX86InstIdRepStosd_NameIndex = 3417,
  kX86InstIdRepStosq_NameIndex = 3427,
  kX86InstIdRepStosw_NameIndex = 3437,
  kX86InstIdRepeCmpsb_NameIndex = 3447,
  kX86InstIdRepeCmpsd_NameIndex = 3458,
  kX86InstIdRepeCmpsq_NameIndex = 3469,
  kX86InstIdRepeCmpsw_NameIndex = 3480,
  kX86InstIdRepeScasb_NameIndex = 3491,
  kX86InstIdRepeScasd_NameIndex = 3502,
  kX86InstIdRepeScasq_NameIndex = 3513,
  kX86InstIdRepeScasw_NameIndex = 3524,
  kX86InstIdRepneCmpsb_NameIndex = 3535,
  kX86InstIdRepneCmpsd_NameIndex = 3547,
  kX86InstIdRepneCmpsq_NameIndex = 3559,
  kX86InstIdRepneCmpsw_NameIndex = 3571,
  kX86InstIdRepneScasb_NameIndex = 3583,
  kX86InstIdRepneScasd_NameIndex = 3595,
  kX86InstIdRepneScasq_NameIndex = 3607,
  kX86InstIdRepneScasw_NameIndex = 3619,
  kX86InstIdRet_NameIndex = 3631,
  kX86InstIdRol_NameIndex = 3635,
  kX86InstIdRor_NameIndex = 3639,
  kX86InstIdRorx_NameIndex = 3643,
  kX86InstIdRoundpd_NameIndex = 3648,
  kX86InstIdRoundps_NameIndex = 3656,
  kX86InstIdRoundsd_NameIndex = 3664,
  kX86InstIdRoundss_NameIndex = 3672,
  kX86InstIdRsqrtps_NameIndex = 3680,
  kX86InstIdRsqrtss_NameIndex = 3688,
  kX86InstIdSahf_NameIndex = 3696,
  kX86InstIdSal_NameIndex = 3701,
  kX86InstIdSar_NameIndex = 3705,
  kX86InstIdSarx_NameIndex = 3709,
  kX86InstIdSbb_NameIndex = 3714,
  kX86InstIdSeta_NameIndex = 3718,
  kX86InstIdSetae_NameIndex = 3723,
  kX86InstIdSetb_NameIndex = 3729,
  kX86InstIdSetbe_NameIndex = 3734,
  kX86InstIdSetc_NameIndex = 3740,
  kX86InstIdSete_NameIndex = 3745,
  kX86InstIdSetg_NameIndex = 3750,
  kX86InstIdSetge_NameIndex = 3755,
  kX86InstIdSetl_NameIndex = 3761,
  kX86InstIdSetle_NameIndex = 3766,
  kX86InstIdSetna_NameIndex = 3772,
  kX86InstIdSetnae_NameIndex = 3778,
  kX86InstIdSetnb_NameIndex = 3785,
  kX86InstIdSetnbe_NameIndex = 3791,
  kX86InstIdSetnc_NameIndex = 3798,
  kX86InstIdSetne_NameIndex = 3804,
  kX86InstIdSetng_NameIndex = 3810,
  kX86InstIdSetnge_NameIndex = 3816,
  kX86InstIdSetnl_NameIndex = 3823,
  kX86InstIdSetnle_NameIndex = 3829,
  kX86InstIdSetno_NameIndex = 3836,
  kX86InstIdSetnp_NameIndex = 3842,
  kX86InstIdSetns_NameIndex = 3848,
  kX86InstIdSetnz_NameIndex = 3854,
  kX86InstIdSeto_NameIndex = 3860,
  kX86InstIdSetp_NameIndex = 3865,
  kX86InstIdSetpe_NameIndex = 3870,
  kX86InstIdSetpo_NameIndex = 3876,
  kX86InstIdSets_NameIndex = 3882,
  kX86InstIdSetz_NameIndex = 3887,
  kX86InstIdSfence_NameIndex = 3892,
  kX86InstIdShl_NameIndex = 3899,
  kX86InstIdShld_NameIndex = 3903,
  kX86InstIdShlx_NameIndex = 3908,
  kX86InstIdShr_NameIndex = 3913,
  kX86InstIdShrd_NameIndex = 3917,
  kX86InstIdShrx_NameIndex = 3922,
  kX86InstIdShufpd_NameIndex = 3927,
  kX86InstIdShufps_NameIndex = 3934,
  kX86InstIdSqrtpd_NameIndex = 3941,
  kX86InstIdSqrtps_NameIndex = 3948,
  kX86InstIdSqrtsd_NameIndex = 3955,
  kX86InstIdSqrtss_NameIndex = 3962,
  kX86InstIdStc_NameIndex = 3969,
  kX86InstIdStd_NameIndex = 3973,
  kX86InstIdStmxcsr_NameIndex = 3977,
  kX86InstIdSub_NameIndex = 3985,
  kX86InstIdSubpd_NameIndex = 3989,
  kX86InstIdSubps_NameIndex = 3995,
  kX86InstIdSubsd_NameIndex = 4001,
  kX86InstIdSubss_NameIndex = 4007,
  kX86InstIdTest_NameIndex = 4013,
  kX86InstIdTzcnt_NameIndex = 4018,
  kX86InstIdUcomisd_NameIndex = 4024,
  kX86InstIdUcomiss_NameIndex = 4032,
  kX86InstIdUd2_NameIndex = 4040,
  kX86InstIdUnpckhpd_NameIndex = 4044,
  kX86InstIdUnpckhps_NameIndex = 4053,
  kX86InstIdUnpcklpd_NameIndex = 4062,
  kX86InstIdUnpcklps_NameIndex = 4071,
  kX86InstIdVaddpd_NameIndex = 4080,
  kX86InstIdVaddps_NameIndex = 4087,
  kX86InstIdVaddsd_NameIndex = 4094,
  kX86InstIdVaddss_NameIndex = 4101,
  kX86InstIdVaddsubpd_NameIndex = 4108,
  kX86InstIdVaddsubps_NameIndex = 4118,
  kX86InstIdVaesdec_NameIndex = 4128,
  kX86InstIdVaesdeclast_NameIndex = 4136,
  kX86InstIdVaesenc_NameIndex = 4148,
  kX86InstIdVaesenclast_NameIndex = 4156,
  kX86InstIdVaesimc_NameIndex = 4168,
  kX86InstIdVaeskeygenassist_NameIndex = 4176,
  kX86InstIdVandnpd_NameIndex = 4193,
  kX86InstIdVandnps_NameIndex = 4201,
  kX86InstIdVandpd_NameIndex = 4209,
  kX86InstIdVandps_NameIndex = 4216,
  kX86InstIdVblendpd_NameIndex = 4223,
  kX86InstIdVblendps_NameIndex = 4232,
  kX86InstIdVblendvpd_NameIndex = 4241,
  kX86InstIdVblendvps_NameIndex = 4251,
  kX86InstIdVbroadcastf128_NameIndex = 4261,
  kX86InstIdVbroadcasti128_NameIndex = 4276,
  kX86InstIdVbroadcastsd_NameIndex = 4291,
  kX86InstIdVbroadcastss_NameIndex = 4304,
  kX86InstIdVcmppd_NameIndex = 4317,
  kX86InstIdVcmpps_NameIndex = 4324,
  kX86InstIdVcmpsd_NameIndex = 4331,
  kX86InstIdVcmpss_NameIndex = 4338,
  kX86InstIdVcomisd_NameIndex = 4345,
  kX86InstIdVcomiss_NameIndex = 4353,
  kX86InstIdVcvtdq2pd_NameIndex = 4361,
  kX86InstIdVcvtdq2ps_NameIndex = 4371,
  kX86InstIdVcvtpd2dq_NameIndex = 4381,
  kX86InstIdVcvtpd2ps_NameIndex = 4391,
  kX86InstIdVcvtph2ps_NameIndex = 4401,
  kX86InstIdVcvtps2dq_NameIndex = 4411,
  kX86InstIdVcvtps2pd_NameIndex = 4421,
  kX86InstIdVcvtps2ph_NameIndex = 4431,
  kX86InstIdVcvtsd2si_NameIndex = 4441,
  kX86InstIdVcvtsd2ss_NameIndex = 4451,
  kX86InstIdVcvtsi2sd_NameIndex = 4461,
  kX86InstIdVcvtsi2ss_NameIndex = 4471,
  kX86InstIdVcvtss2sd_NameIndex = 4481,
  kX86InstIdVcvtss2si_NameIndex = 4491,
  kX86InstIdVcvttpd2dq_NameIndex = 4501,
  kX86InstIdVcvttps2dq_NameIndex = 4512,
  kX86InstIdVcvttsd2si_NameIndex = 4523,
  kX86InstIdVcvttss2si_NameIndex = 4534,
  kX86InstIdVdivpd_NameIndex = 4545,
  kX86InstIdVdivps_NameIndex = 4552,
  kX86InstIdVdivsd_NameIndex = 4559,
  kX86InstIdVdivss_NameIndex = 4566,
  kX86InstIdVdppd_NameIndex = 4573,
  kX86InstIdVdpps_NameIndex = 4579,
  kX86InstIdVextractf128_NameIndex = 4585,
  kX86InstIdVextracti128_NameIndex = 4598,
  kX86InstIdVextractps_NameIndex = 4611,
  kX86InstIdVfmadd132pd_NameIndex = 4622,
  kX86InstIdVfmadd132ps_NameIndex = 4634,
  kX86InstIdVfmadd132sd_NameIndex = 4646,
  kX86InstIdVfmadd132ss_NameIndex = 4658,
  kX86InstIdVfmadd213pd_NameIndex = 4670,
  kX86InstIdVfmadd213ps_NameIndex = 4682,
  kX86InstIdVfmadd213sd_NameIndex = 4694,
  kX86InstIdVfmadd213ss_NameIndex = 4706,
  kX86InstIdVfmadd231pd_NameIndex = 4718,
  kX86InstIdVfmadd231ps_NameIndex = 4730,
  kX86InstIdVfmadd231sd_NameIndex = 4742,
  kX86InstIdVfmadd231ss_NameIndex = 4754,
  kX86InstIdVfmaddpd_NameIndex = 4766,
  kX86InstIdVfmaddps_NameIndex = 4775,
  kX86InstIdVfmaddsd_NameIndex = 4784,
  kX86InstIdVfmaddss_NameIndex = 4793,
  kX86InstIdVfmaddsub132pd_NameIndex = 4802,
  kX86InstIdVfmaddsub132ps_NameIndex = 4817,
  kX86InstIdVfmaddsub213pd_NameIndex = 4832,
  kX86InstIdVfmaddsub213ps_NameIndex = 4847,
  kX86InstIdVfmaddsub231pd_NameIndex = 4862,
  kX86InstIdVfmaddsub231ps_NameIndex = 4877,
  kX86InstIdVfmaddsubpd_NameIndex = 4892,
  kX86InstIdVfmaddsubps_NameIndex = 4904,
  kX86InstIdVfmsub132pd_NameIndex = 4916,
  kX86InstIdVfmsub132ps_NameIndex = 4928,
  kX86InstIdVfmsub132sd_NameIndex = 4940,
  kX86InstIdVfmsub132ss_NameIndex = 4952,
  kX86InstIdVfmsub213pd_NameIndex = 4964,
  kX86InstIdVfmsub213ps_NameIndex = 4976,
  kX86InstIdVfmsub213sd_NameIndex = 4988,
  kX86InstIdVfmsub213ss_NameIndex = 5000,
  kX86InstIdVfmsub231pd_NameIndex = 5012,
  kX86InstIdVfmsub231ps_NameIndex = 5024,
  kX86InstIdVfmsub231sd_NameIndex = 5036,
  kX86InstIdVfmsub231ss_NameIndex = 5048,
  kX86InstIdVfmsubadd132pd_NameIndex = 5060,
  kX86InstIdVfmsubadd132ps_NameIndex = 5075,
  kX86InstIdVfmsubadd213pd_NameIndex = 5090,
  kX86InstIdVfmsubadd213ps_NameIndex = 5105,
  kX86InstIdVfmsubadd231pd_NameIndex = 5120,
  kX86InstIdVfmsubadd231ps_NameIndex = 5135,
  kX86InstIdVfmsubaddpd_NameIndex = 5150,
  kX86InstIdVfmsubaddps_NameIndex = 5162,
  kX86InstIdVfmsubpd_NameIndex = 5174,
  kX86InstIdVfmsubps_NameIndex = 5183,
  kX86InstIdVfmsubsd_NameIndex = 5192,
  kX86InstIdVfmsubss_NameIndex = 5201,
  kX86InstIdVfnmadd132pd_NameIndex = 5210,
  kX86InstIdVfnmadd132ps_NameIndex = 5223,
  kX86InstIdVfnmadd132sd_NameIndex = 5236,
  kX86InstIdVfnmadd132ss_NameIndex = 5249,
  kX86InstIdVfnmadd213pd_NameIndex = 5262,
  kX86InstIdVfnmadd213ps_NameIndex = 5275,
  kX86InstIdVfnmadd213sd_NameIndex = 5288,
  kX86InstIdVfnmadd213ss_NameIndex = 5301,
  kX86InstIdVfnmadd231pd_NameIndex = 5314,
  kX86InstIdVfnmadd231ps_NameIndex = 5327,
  kX86InstIdVfnmadd231sd_NameIndex = 5340,
  kX86InstIdVfnmadd231ss_NameIndex = 5353,
  kX86InstIdVfnmaddpd_NameIndex = 5366,
  kX86InstIdVfnmaddps_NameIndex = 5376,
  kX86InstIdVfnmaddsd_NameIndex = 5386,
  kX86InstIdVfnmaddss_NameIndex = 5396,
  kX86InstIdVfnmsub132pd_NameIndex = 5406,
  kX86InstIdVfnmsub132ps_NameIndex = 5419,
  kX86InstIdVfnmsub132sd_NameIndex = 5432,
  kX86InstIdVfnmsub132ss_NameIndex = 5445,
  kX86InstIdVfnmsub213pd_NameIndex = 5458,
  kX86InstIdVfnmsub213ps_NameIndex = 5471,
  kX86InstIdVfnmsub213sd_NameIndex = 5484,
  kX86InstIdVfnmsub213ss_NameIndex = 5497,
  kX86InstIdVfnmsub231pd_NameIndex = 5510,
  kX86InstIdVfnmsub231ps_NameIndex = 5523,
  kX86InstIdVfnmsub231sd_NameIndex = 5536,
  kX86InstIdVfnmsub231ss_NameIndex = 5549,
  kX86InstIdVfnmsubpd_NameIndex = 5562,
  kX86InstIdVfnmsubps_NameIndex = 5572,
  kX86InstIdVfnmsubsd_NameIndex = 5582,
  kX86InstIdVfnmsubss_NameIndex = 5592,
  kX86InstIdVfrczpd_NameIndex = 5602,
  kX86InstIdVfrczps_NameIndex = 5610,
  kX86InstIdVfrczsd_NameIndex = 5618,
  kX86InstIdVfrczss_NameIndex = 5626,
  kX86InstIdVgatherdpd_NameIndex = 5634,
  kX86InstIdVgatherdps_NameIndex = 5645,
  kX86InstIdVgatherqpd_NameIndex = 5656,
  kX86InstIdVgatherqps_NameIndex = 5667,
  kX86InstIdVhaddpd_NameIndex = 5678,
  kX86InstIdVhaddps_NameIndex = 5686,
  kX86InstIdVhsubpd_NameIndex = 5694,
  kX86InstIdVhsubps_NameIndex = 5702,
  kX86InstIdVinsertf128_NameIndex = 5710,
  kX86InstIdVinserti128_NameIndex = 5722,
  kX86InstIdVinsertps_NameIndex = 5734,
  kX86InstIdVlddqu_NameIndex = 5744,
  kX86InstIdVldmxcsr_NameIndex = 5751,
  kX86InstIdVmaskmovdqu_NameIndex = 5760,
  kX86InstIdVmaskmovpd_NameIndex = 5772,
  kX86InstIdVmaskmovps_NameIndex = 5783,
  kX86InstIdVmaxpd_NameIndex = 5794,
  kX86InstIdVmaxps_NameIndex = 5801,
  kX86InstIdVmaxsd_NameIndex = 5808,
  kX86InstIdVmaxss_NameIndex = 5815,
  kX86InstIdVminpd_NameIndex = 5822,
  kX86InstIdVminps_NameIndex = 5829,
  kX86InstIdVminsd_NameIndex = 5836,
  kX86InstIdVminss_NameIndex = 5843,
  kX86InstIdVmovapd_NameIndex = 5850,
  kX86InstIdVmovaps_NameIndex = 5858,
  kX86InstIdVmovd_NameIndex = 5866,
  kX86InstIdVmovddup_NameIndex = 5872,
  kX86InstIdVmovdqa_NameIndex = 5881,
  kX86InstIdVmovdqu_NameIndex = 5889,
  kX86InstIdVmovhlps_NameIndex = 5897,
  kX86InstIdVmovhpd_NameIndex = 5906,
  kX86InstIdVmovhps_NameIndex = 5914,
  kX86InstIdVmovlhps_NameIndex = 5922,
  kX86InstIdVmovlpd_NameIndex = 5931,
  kX86InstIdVmovlps_NameIndex = 5939,
  kX86InstIdVmovmskpd_NameIndex = 5947,
  kX86InstIdVmovmskps_NameIndex = 5957,
  kX86InstIdVmovntdq_NameIndex = 5967,
  kX86InstIdVmovntdqa_NameIndex = 5976,
  kX86InstIdVmovntpd_NameIndex = 5986,
  kX86InstIdVmovntps_NameIndex = 5995,
  kX86InstIdVmovq_NameIndex = 6004,
  kX86InstIdVmovsd_NameIndex = 6010,
  kX86InstIdVmovshdup_NameIndex = 6017,
  kX86InstIdVmovsldup_NameIndex = 6027,
  kX86InstIdVmovss_NameIndex = 6037,
  kX86InstIdVmovupd_NameIndex = 6044,
  kX86InstIdVmovups_NameIndex = 6052,
  kX86InstIdVmpsadbw_NameIndex = 6060,
  kX86InstIdVmulpd_NameIndex = 6069,
  kX86InstIdVmulps_NameIndex = 6076,
  kX86InstIdVmulsd_NameIndex = 6083,
  kX86InstIdVmulss_NameIndex = 6090,
  kX86InstIdVorpd_NameIndex = 6097,
  kX86InstIdVorps_NameIndex = 6103,
  kX86InstIdVpabsb_NameIndex = 6109,
  kX86InstIdVpabsd_NameIndex = 6116,
  kX86InstIdVpabsw_NameIndex = 6123,
  kX86InstIdVpackssdw_NameIndex = 6130,
  kX86InstIdVpacksswb_NameIndex = 6140,
  kX86InstIdVpackusdw_NameIndex = 6150,
  kX86InstIdVpackuswb_NameIndex = 6160,
  kX86InstIdVpaddb_NameIndex = 6170,
  kX86InstIdVpaddd_NameIndex = 6177,
  kX86InstIdVpaddq_NameIndex = 6184,
  kX86InstIdVpaddsb_NameIndex = 6191,
  kX86InstIdVpaddsw_NameIndex = 6199,
  kX86InstIdVpaddusb_NameIndex = 6207,
  kX86InstIdVpaddusw_NameIndex = 6216,
  kX86InstIdVpaddw_NameIndex = 6225,
  kX86InstIdVpalignr_NameIndex = 6232,
  kX86InstIdVpand_NameIndex = 6241,
  kX86InstIdVpandn_NameIndex = 6247,
  kX86InstIdVpavgb_NameIndex = 6254,
  kX86InstIdVpavgw_NameIndex = 6261,
  kX86InstIdVpblendd_NameIndex = 6268,
  kX86InstIdVpblendvb_NameIndex = 6277,
  kX86InstIdVpblendw_NameIndex = 6287,
  kX86InstIdVpbroadcastb_NameIndex = 6296,
  kX86InstIdVpbroadcastd_NameIndex = 6309,
  kX86InstIdVpbroadcastq_NameIndex = 6322,
  kX86InstIdVpbroadcastw_NameIndex = 6335,
  kX86InstIdVpclmulqdq_NameIndex = 6348,
  kX86InstIdVpcmov_NameIndex = 6359,
  kX86InstIdVpcmpeqb_NameIndex = 6366,
  kX86InstIdVpcmpeqd_NameIndex = 6375,
  kX86InstIdVpcmpeqq_NameIndex = 6384,
  kX86InstIdVpcmpeqw_NameIndex = 6393,
  kX86InstIdVpcmpestri_NameIndex = 6402,
  kX86InstIdVpcmpestrm_NameIndex = 6413,
  kX86InstIdVpcmpgtb_NameIndex = 6424,
  kX86InstIdVpcmpgtd_NameIndex = 6433,
  kX86InstIdVpcmpgtq_NameIndex = 6442,
  kX86InstIdVpcmpgtw_NameIndex = 6451,
  kX86InstIdVpcmpistri_NameIndex = 6460,
  kX86InstIdVpcmpistrm_NameIndex = 6471,
  kX86InstIdVpcomb_NameIndex = 6482,
  kX86InstIdVpcomd_NameIndex = 6489,
  kX86InstIdVpcomq_NameIndex = 6496,
  kX86InstIdVpcomub_NameIndex = 6503,
  kX86InstIdVpcomud_NameIndex = 6511,
  kX86InstIdVpcomuq_NameIndex = 6519,
  kX86InstIdVpcomuw_NameIndex = 6527,
  kX86InstIdVpcomw_NameIndex = 6535,
  kX86InstIdVperm2f128_NameIndex = 6542,
  kX86InstIdVperm2i128_NameIndex = 6553,
  kX86InstIdVpermd_NameIndex = 6564,
  kX86InstIdVpermil2pd_NameIndex = 6571,
  kX86InstIdVpermil2ps_NameIndex = 6582,
  kX86InstIdVpermilpd_NameIndex = 6593,
  kX86InstIdVpermilps_NameIndex = 6603,
  kX86InstIdVpermpd_NameIndex = 6613,
  kX86InstIdVpermps_NameIndex = 6621,
  kX86InstIdVpermq_NameIndex = 6629,
  kX86InstIdVpextrb_NameIndex = 6636,
  kX86InstIdVpextrd_NameIndex = 6644,
  kX86InstIdVpextrq_NameIndex = 6652,
  kX86InstIdVpextrw_NameIndex = 6660,
  kX86InstIdVpgatherdd_NameIndex = 6668,
  kX86InstIdVpgatherdq_NameIndex = 6679,
  kX86InstIdVpgatherqd_NameIndex = 6690,
  kX86InstIdVpgatherqq_NameIndex = 6701,
  kX86InstIdVphaddbd_NameIndex = 6712,
  kX86InstIdVphaddbq_NameIndex = 6721,
  kX86InstIdVphaddbw_NameIndex = 6730,
  kX86InstIdVphaddd_NameIndex = 6739,
  kX86InstIdVphadddq_NameIndex = 6747,
  kX86InstIdVphaddsw_NameIndex = 6756,
  kX86InstIdVphaddubd_NameIndex = 6765,
  kX86InstIdVphaddubq_NameIndex = 6775,
  kX86InstIdVphaddubw_NameIndex = 6785,
  kX86InstIdVphaddudq_NameIndex = 6795,
  kX86InstIdVphadduwd_NameIndex = 6805,
  kX86InstIdVphadduwq_NameIndex = 6815,
  kX86InstIdVphaddw_NameIndex = 6825,
  kX86InstIdVphaddwd_NameIndex = 6833,
  kX86InstIdVphaddwq_NameIndex = 6842,
  kX86InstIdVphminposuw_NameIndex = 6851,
  kX86InstIdVphsubbw_NameIndex = 6863,
  kX86InstIdVphsubd_NameIndex = 6872,
  kX86InstIdVphsubdq_NameIndex = 6880,
  kX86InstIdVphsubsw_NameIndex = 6889,
  kX86InstIdVphsubw_NameIndex = 6898,
  kX86InstIdVphsubwd_NameIndex = 6906,
  kX86InstIdVpinsrb_NameIndex = 6915,
  kX86InstIdVpinsrd_NameIndex = 6923,
  kX86InstIdVpinsrq_NameIndex = 6931,
  kX86InstIdVpinsrw_NameIndex = 6939,
  kX86InstIdVpmacsdd_NameIndex = 6947,
  kX86InstIdVpmacsdqh_NameIndex = 6956,
  kX86InstIdVpmacsdql_NameIndex = 6966,
  kX86InstIdVpmacssdd_NameIndex = 6976,
  kX86InstIdVpmacssdqh_NameIndex = 6986,
  kX86InstIdVpmacssdql_NameIndex = 6997,
  kX86InstIdVpmacsswd_NameIndex = 7008,
  kX86InstIdVpmacssww_NameIndex = 7018,
  kX86InstIdVpmacswd_NameIndex = 7028,
  kX86InstIdVpmacsww_NameIndex = 7037,
  kX86InstIdVpmadcsswd_NameIndex = 7046,
  kX86InstIdVpmadcswd_NameIndex = 7057,
  kX86InstIdVpmaddubsw_NameIndex = 7067,
  kX86InstIdVpmaddwd_NameIndex = 7078,
  kX86InstIdVpmaskmovd_NameIndex = 7087,
  kX86InstIdVpmaskmovq_NameIndex = 7098,
  kX86InstIdVpmaxsb_NameIndex = 7109,
  kX86InstIdVpmaxsd_NameIndex = 7117,
  kX86InstIdVpmaxsw_NameIndex = 7125,
  kX86InstIdVpmaxub_NameIndex = 7133,
  kX86InstIdVpmaxud_NameIndex = 7141,
  kX86InstIdVpmaxuw_NameIndex = 7149,
  kX86InstIdVpminsb_NameIndex = 7157,
  kX86InstIdVpminsd_NameIndex = 7165,
  kX86InstIdVpminsw_NameIndex = 7173,
  kX86InstIdVpminub_NameIndex = 7181,
  kX86InstIdVpminud_NameIndex = 7189,
  kX86InstIdVpminuw_NameIndex = 7197,
  kX86InstIdVpmovmskb_NameIndex = 7205,
  kX86InstIdVpmovsxbd_NameIndex = 7215,
  kX86InstIdVpmovsxbq_NameIndex = 7225,
  kX86InstIdVpmovsxbw_NameIndex = 7235,
  kX86InstIdVpmovsxdq_NameIndex = 7245,
  kX86InstIdVpmovsxwd_NameIndex = 7255,
  kX86InstIdVpmovsxwq_NameIndex = 7265,
  kX86InstIdVpmovzxbd_NameIndex = 7275,
  kX86InstIdVpmovzxbq_NameIndex = 7285,
  kX86InstIdVpmovzxbw_NameIndex = 7295,
  kX86InstIdVpmovzxdq_NameIndex = 7305,
  kX86InstIdVpmovzxwd_NameIndex = 7315,
  kX86InstIdVpmovzxwq_NameIndex = 7325,
  kX86InstIdVpmuldq_NameIndex = 7335,
  kX86InstIdVpmulhrsw_NameIndex = 7343,
  kX86InstIdVpmulhuw_NameIndex = 7353,
  kX86InstIdVpmulhw_NameIndex = 7362,
  kX86InstIdVpmulld_NameIndex = 7370,
  kX86InstIdVpmullw_NameIndex = 7378,
  kX86InstIdVpmuludq_NameIndex = 7386,
  kX86InstIdVpor_NameIndex = 7395,
  kX86InstIdVpperm_NameIndex = 7400,
  kX86InstIdVprotb_NameIndex = 7407,
  kX86InstIdVprotd_NameIndex = 7414,
  kX86InstIdVprotq_NameIndex = 7421,
  kX86InstIdVprotw_NameIndex = 7428,
  kX86InstIdVpsadbw_NameIndex = 7435,
  kX86InstIdVpshab_NameIndex = 7443,
  kX86InstIdVpshad_NameIndex = 7450,
  kX86InstIdVpshaq_NameIndex = 7457,
  kX86InstIdVpshaw_NameIndex = 7464,
  kX86InstIdVpshlb_NameIndex = 7471,
  kX86InstIdVpshld_NameIndex = 7478,
  kX86InstIdVpshlq_NameIndex = 7485,
  kX86InstIdVpshlw_NameIndex = 7492,
  kX86InstIdVpshufb_NameIndex = 7499,
  kX86InstIdVpshufd_NameIndex = 7507,
  kX86InstIdVpshufhw_NameIndex = 7515,
  kX86InstIdVpshuflw_NameIndex = 7524,
  kX86InstIdVpsignb_NameIndex = 7533,
  kX86InstIdVpsignd_NameIndex = 7541,
  kX86InstIdVpsignw_NameIndex = 7549,
  kX86InstIdVpslld_NameIndex = 7557,
  kX86InstIdVpslldq_NameIndex = 7564,
  kX86InstIdVpsllq_NameIndex = 7572,
  kX86InstIdVpsllvd_NameIndex = 7579,
  kX86InstIdVpsllvq_NameIndex = 7587,
  kX86InstIdVpsllw_NameIndex = 7595,
  kX86InstIdVpsrad_NameIndex = 7602,
  kX86InstIdVpsravd_NameIndex = 7609,
  kX86InstIdVpsraw_NameIndex = 7617,
  kX86InstIdVpsrld_NameIndex = 7624,
  kX86InstIdVpsrldq_NameIndex = 7631,
  kX86InstIdVpsrlq_NameIndex = 7639,
  kX86InstIdVpsrlvd_NameIndex = 7646,
  kX86InstIdVpsrlvq_NameIndex = 7654,
  kX86InstIdVpsrlw_NameIndex = 7662,
  kX86InstIdVpsubb_NameIndex = 7669,
  kX86InstIdVpsubd_NameIndex = 7676,
  kX86InstIdVpsubq_NameIndex = 7683,
  kX86InstIdVpsubsb_NameIndex = 7690,
  kX86InstIdVpsubsw_NameIndex = 7698,
  kX86InstIdVpsubusb_NameIndex = 7706,
  kX86InstIdVpsubusw_NameIndex = 7715,
  kX86InstIdVpsubw_NameIndex = 7724,
  kX86InstIdVptest_NameIndex = 7731,
  kX86InstIdVpunpckhbw_NameIndex = 7738,
  kX86InstIdVpunpckhdq_NameIndex = 7749,
  kX86InstIdVpunpckhqdq_NameIndex = 7760,
  kX86InstIdVpunpckhwd_NameIndex = 7772,
  kX86InstIdVpunpcklbw_NameIndex = 7783,
  kX86InstIdVpunpckldq_NameIndex = 7794,
  kX86InstIdVpunpcklqdq_NameIndex = 7805,
  kX86InstIdVpunpcklwd_NameIndex = 7817,
  kX86InstIdVpxor_NameIndex = 7828,
  kX86InstIdVrcpps_NameIndex = 7834,
  kX86InstIdVrcpss_NameIndex = 7841,
  kX86InstIdVroundpd_NameIndex = 7848,
  kX86InstIdVroundps_NameIndex = 7857,
  kX86InstIdVroundsd_NameIndex = 7866,
  kX86InstIdVroundss_NameIndex = 7875,
  kX86InstIdVrsqrtps_NameIndex = 7884,
  kX86InstIdVrsqrtss_NameIndex = 7893,
  kX86InstIdVshufpd_NameIndex = 7902,
  kX86InstIdVshufps_NameIndex = 7910,
  kX86InstIdVsqrtpd_NameIndex = 7918,
  kX86InstIdVsqrtps_NameIndex = 7926,
  kX86InstIdVsqrtsd_NameIndex = 7934,
  kX86InstIdVsqrtss_NameIndex = 7942,
  kX86InstIdVstmxcsr_NameIndex = 7950,
  kX86InstIdVsubpd_NameIndex = 7959,
  kX86InstIdVsubps_NameIndex = 7966,
  kX86InstIdVsubsd_NameIndex = 7973,
  kX86InstIdVsubss_NameIndex = 7980,
  kX86InstIdVtestpd_NameIndex = 7987,
  kX86InstIdVtestps_NameIndex = 7995,
  kX86InstIdVucomisd_NameIndex = 8003,
  kX86InstIdVucomiss_NameIndex = 8012,
  kX86InstIdVunpckhpd_NameIndex = 8021,
  kX86InstIdVunpckhps_NameIndex = 8031,
  kX86InstIdVunpcklpd_NameIndex = 8041,
  kX86InstIdVunpcklps_NameIndex = 8051,
  kX86InstIdVxorpd_NameIndex = 8061,
  kX86InstIdVxorps_NameIndex = 8068,
  kX86InstIdVzeroall_NameIndex = 8075,
  kX86InstIdVzeroupper_NameIndex = 8084,
  kX86InstIdWrfsbase_NameIndex = 8095,
  kX86InstIdWrgsbase_NameIndex = 8104,
  kX86InstIdXadd_NameIndex = 8113,
  kX86InstIdXchg_NameIndex = 8118,
  kX86InstIdXor_NameIndex = 8123,
  kX86InstIdXorpd_NameIndex = 8127,
  kX86InstIdXorps_NameIndex = 8133
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
  { G(ExtMov)        , 8 , F(Move)|F(ZeroIfMem)   , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_F20F00(11,U)   },
  { G(ExtMov)        , 4 , F(Move)|F(ZeroIfMem)   , { O(XmmMem)           , O(XmmMem)           , U                   , U                   }, O_F30F00(11,U)   },
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
  kX86InstIdCmpsd_ExtendedIndex = 3,
  kX86InstIdCmpss_ExtendedIndex = 3,
  kX86InstIdCmpxchg_ExtendedIndex = 20,
  kX86InstIdCmpxchg16b_ExtendedIndex = 21,
  kX86InstIdCmpxchg8b_ExtendedIndex = 22,
  kX86InstIdComisd_ExtendedIndex = 23,
  kX86InstIdComiss_ExtendedIndex = 23,
  kX86InstIdCpuid_ExtendedIndex = 15,
  kX86InstIdCqo_ExtendedIndex = 16,
  kX86InstIdCrc32_ExtendedIndex = 24,
  kX86InstIdCvtdq2pd_ExtendedIndex = 25,
  kX86InstIdCvtdq2ps_ExtendedIndex = 25,
  kX86InstIdCvtpd2dq_ExtendedIndex = 25,
  kX86InstIdCvtpd2pi_ExtendedIndex = 26,
  kX86InstIdCvtpd2ps_ExtendedIndex = 25,
  kX86InstIdCvtpi2pd_ExtendedIndex = 27,
  kX86InstIdCvtpi2ps_ExtendedIndex = 28,
  kX86InstIdCvtps2dq_ExtendedIndex = 25,
  kX86InstIdCvtps2pd_ExtendedIndex = 25,
  kX86InstIdCvtps2pi_ExtendedIndex = 26,
  kX86InstIdCvtsd2si_ExtendedIndex = 29,
  kX86InstIdCvtsd2ss_ExtendedIndex = 30,
  kX86InstIdCvtsi2sd_ExtendedIndex = 31,
  kX86InstIdCvtsi2ss_ExtendedIndex = 32,
  kX86InstIdCvtss2sd_ExtendedIndex = 33,
  kX86InstIdCvtss2si_ExtendedIndex = 29,
  kX86InstIdCvttpd2dq_ExtendedIndex = 25,
  kX86InstIdCvttpd2pi_ExtendedIndex = 26,
  kX86InstIdCvttps2dq_ExtendedIndex = 25,
  kX86InstIdCvttps2pi_ExtendedIndex = 26,
  kX86InstIdCvttsd2si_ExtendedIndex = 29,
  kX86InstIdCvttss2si_ExtendedIndex = 29,
  kX86InstIdCwd_ExtendedIndex = 15,
  kX86InstIdCwde_ExtendedIndex = 15,
  kX86InstIdDaa_ExtendedIndex = 15,
  kX86InstIdDas_ExtendedIndex = 15,
  kX86InstIdDec_ExtendedIndex = 34,
  kX86InstIdDiv_ExtendedIndex = 35,
  kX86InstIdDivpd_ExtendedIndex = 2,
  kX86InstIdDivps_ExtendedIndex = 2,
  kX86InstIdDivsd_ExtendedIndex = 2,
  kX86InstIdDivss_ExtendedIndex = 2,
  kX86InstIdDppd_ExtendedIndex = 3,
  kX86InstIdDpps_ExtendedIndex = 3,
  kX86InstIdEmms_ExtendedIndex = 17,
  kX86InstIdEnter_ExtendedIndex = 36,
  kX86InstIdExtractps_ExtendedIndex = 37,
  kX86InstIdF2xm1_ExtendedIndex = 38,
  kX86InstIdFabs_ExtendedIndex = 38,
  kX86InstIdFadd_ExtendedIndex = 39,
  kX86InstIdFaddp_ExtendedIndex = 40,
  kX86InstIdFbld_ExtendedIndex = 41,
  kX86InstIdFbstp_ExtendedIndex = 41,
  kX86InstIdFchs_ExtendedIndex = 38,
  kX86InstIdFclex_ExtendedIndex = 38,
  kX86InstIdFcmovb_ExtendedIndex = 42,
  kX86InstIdFcmovbe_ExtendedIndex = 42,
  kX86InstIdFcmove_ExtendedIndex = 42,
  kX86InstIdFcmovnb_ExtendedIndex = 42,
  kX86InstIdFcmovnbe_ExtendedIndex = 42,
  kX86InstIdFcmovne_ExtendedIndex = 42,
  kX86InstIdFcmovnu_ExtendedIndex = 42,
  kX86InstIdFcmovu_ExtendedIndex = 42,
  kX86InstIdFcom_ExtendedIndex = 43,
  kX86InstIdFcomi_ExtendedIndex = 42,
  kX86InstIdFcomip_ExtendedIndex = 42,
  kX86InstIdFcomp_ExtendedIndex = 43,
  kX86InstIdFcompp_ExtendedIndex = 38,
  kX86InstIdFcos_ExtendedIndex = 38,
  kX86InstIdFdecstp_ExtendedIndex = 38,
  kX86InstIdFdiv_ExtendedIndex = 39,
  kX86InstIdFdivp_ExtendedIndex = 40,
  kX86InstIdFdivr_ExtendedIndex = 39,
  kX86InstIdFdivrp_ExtendedIndex = 40,
  kX86InstIdFemms_ExtendedIndex = 44,
  kX86InstIdFfree_ExtendedIndex = 42,
  kX86InstIdFiadd_ExtendedIndex = 45,
  kX86InstIdFicom_ExtendedIndex = 45,
  kX86InstIdFicomp_ExtendedIndex = 45,
  kX86InstIdFidiv_ExtendedIndex = 45,
  kX86InstIdFidivr_ExtendedIndex = 45,
  kX86InstIdFild_ExtendedIndex = 46,
  kX86InstIdFimul_ExtendedIndex = 45,
  kX86InstIdFincstp_ExtendedIndex = 38,
  kX86InstIdFinit_ExtendedIndex = 38,
  kX86InstIdFist_ExtendedIndex = 45,
  kX86InstIdFistp_ExtendedIndex = 47,
  kX86InstIdFisttp_ExtendedIndex = 48,
  kX86InstIdFisub_ExtendedIndex = 45,
  kX86InstIdFisubr_ExtendedIndex = 45,
  kX86InstIdFld_ExtendedIndex = 49,
  kX86InstIdFld1_ExtendedIndex = 38,
  kX86InstIdFldcw_ExtendedIndex = 41,
  kX86InstIdFldenv_ExtendedIndex = 41,
  kX86InstIdFldl2e_ExtendedIndex = 38,
  kX86InstIdFldl2t_ExtendedIndex = 38,
  kX86InstIdFldlg2_ExtendedIndex = 38,
  kX86InstIdFldln2_ExtendedIndex = 38,
  kX86InstIdFldpi_ExtendedIndex = 38,
  kX86InstIdFldz_ExtendedIndex = 38,
  kX86InstIdFmul_ExtendedIndex = 39,
  kX86InstIdFmulp_ExtendedIndex = 40,
  kX86InstIdFnclex_ExtendedIndex = 38,
  kX86InstIdFninit_ExtendedIndex = 38,
  kX86InstIdFnop_ExtendedIndex = 38,
  kX86InstIdFnsave_ExtendedIndex = 41,
  kX86InstIdFnstcw_ExtendedIndex = 41,
  kX86InstIdFnstenv_ExtendedIndex = 41,
  kX86InstIdFnstsw_ExtendedIndex = 50,
  kX86InstIdFpatan_ExtendedIndex = 38,
  kX86InstIdFprem_ExtendedIndex = 38,
  kX86InstIdFprem1_ExtendedIndex = 38,
  kX86InstIdFptan_ExtendedIndex = 38,
  kX86InstIdFrndint_ExtendedIndex = 38,
  kX86InstIdFrstor_ExtendedIndex = 41,
  kX86InstIdFsave_ExtendedIndex = 41,
  kX86InstIdFscale_ExtendedIndex = 38,
  kX86InstIdFsin_ExtendedIndex = 38,
  kX86InstIdFsincos_ExtendedIndex = 38,
  kX86InstIdFsqrt_ExtendedIndex = 38,
  kX86InstIdFst_ExtendedIndex = 51,
  kX86InstIdFstcw_ExtendedIndex = 41,
  kX86InstIdFstenv_ExtendedIndex = 41,
  kX86InstIdFstp_ExtendedIndex = 52,
  kX86InstIdFstsw_ExtendedIndex = 53,
  kX86InstIdFsub_ExtendedIndex = 39,
  kX86InstIdFsubp_ExtendedIndex = 40,
  kX86InstIdFsubr_ExtendedIndex = 39,
  kX86InstIdFsubrp_ExtendedIndex = 40,
  kX86InstIdFtst_ExtendedIndex = 38,
  kX86InstIdFucom_ExtendedIndex = 40,
  kX86InstIdFucomi_ExtendedIndex = 42,
  kX86InstIdFucomip_ExtendedIndex = 42,
  kX86InstIdFucomp_ExtendedIndex = 40,
  kX86InstIdFucompp_ExtendedIndex = 38,
  kX86InstIdFwait_ExtendedIndex = 44,
  kX86InstIdFxam_ExtendedIndex = 38,
  kX86InstIdFxch_ExtendedIndex = 42,
  kX86InstIdFxrstor_ExtendedIndex = 41,
  kX86InstIdFxsave_ExtendedIndex = 41,
  kX86InstIdFxtract_ExtendedIndex = 38,
  kX86InstIdFyl2x_ExtendedIndex = 38,
  kX86InstIdFyl2xp1_ExtendedIndex = 38,
  kX86InstIdHaddpd_ExtendedIndex = 2,
  kX86InstIdHaddps_ExtendedIndex = 2,
  kX86InstIdHsubpd_ExtendedIndex = 2,
  kX86InstIdHsubps_ExtendedIndex = 2,
  kX86InstIdIdiv_ExtendedIndex = 54,
  kX86InstIdImul_ExtendedIndex = 55,
  kX86InstIdInc_ExtendedIndex = 56,
  kX86InstIdInsertps_ExtendedIndex = 3,
  kX86InstIdInt_ExtendedIndex = 57,
  kX86InstIdJa_ExtendedIndex = 58,
  kX86InstIdJae_ExtendedIndex = 58,
  kX86InstIdJb_ExtendedIndex = 58,
  kX86InstIdJbe_ExtendedIndex = 58,
  kX86InstIdJc_ExtendedIndex = 58,
  kX86InstIdJe_ExtendedIndex = 58,
  kX86InstIdJg_ExtendedIndex = 58,
  kX86InstIdJge_ExtendedIndex = 58,
  kX86InstIdJl_ExtendedIndex = 58,
  kX86InstIdJle_ExtendedIndex = 58,
  kX86InstIdJna_ExtendedIndex = 58,
  kX86InstIdJnae_ExtendedIndex = 58,
  kX86InstIdJnb_ExtendedIndex = 58,
  kX86InstIdJnbe_ExtendedIndex = 58,
  kX86InstIdJnc_ExtendedIndex = 58,
  kX86InstIdJne_ExtendedIndex = 58,
  kX86InstIdJng_ExtendedIndex = 58,
  kX86InstIdJnge_ExtendedIndex = 58,
  kX86InstIdJnl_ExtendedIndex = 58,
  kX86InstIdJnle_ExtendedIndex = 58,
  kX86InstIdJno_ExtendedIndex = 58,
  kX86InstIdJnp_ExtendedIndex = 58,
  kX86InstIdJns_ExtendedIndex = 58,
  kX86InstIdJnz_ExtendedIndex = 58,
  kX86InstIdJo_ExtendedIndex = 58,
  kX86InstIdJp_ExtendedIndex = 58,
  kX86InstIdJpe_ExtendedIndex = 58,
  kX86InstIdJpo_ExtendedIndex = 58,
  kX86InstIdJs_ExtendedIndex = 58,
  kX86InstIdJz_ExtendedIndex = 58,
  kX86InstIdJecxz_ExtendedIndex = 59,
  kX86InstIdJmp_ExtendedIndex = 60,
  kX86InstIdLahf_ExtendedIndex = 15,
  kX86InstIdLddqu_ExtendedIndex = 61,
  kX86InstIdLdmxcsr_ExtendedIndex = 18,
  kX86InstIdLea_ExtendedIndex = 62,
  kX86InstIdLeave_ExtendedIndex = 15,
  kX86InstIdLfence_ExtendedIndex = 63,
  kX86InstIdLzcnt_ExtendedIndex = 8,
  kX86InstIdMaskmovdqu_ExtendedIndex = 64,
  kX86InstIdMaskmovq_ExtendedIndex = 65,
  kX86InstIdMaxpd_ExtendedIndex = 2,
  kX86InstIdMaxps_ExtendedIndex = 2,
  kX86InstIdMaxsd_ExtendedIndex = 2,
  kX86InstIdMaxss_ExtendedIndex = 2,
  kX86InstIdMfence_ExtendedIndex = 63,
  kX86InstIdMinpd_ExtendedIndex = 2,
  kX86InstIdMinps_ExtendedIndex = 2,
  kX86InstIdMinsd_ExtendedIndex = 2,
  kX86InstIdMinss_ExtendedIndex = 2,
  kX86InstIdMonitor_ExtendedIndex = 15,
  kX86InstIdMov_ExtendedIndex = 66,
  kX86InstIdMovPtr_ExtendedIndex = 67,
  kX86InstIdMovapd_ExtendedIndex = 68,
  kX86InstIdMovaps_ExtendedIndex = 69,
  kX86InstIdMovbe_ExtendedIndex = 70,
  kX86InstIdMovd_ExtendedIndex = 71,
  kX86InstIdMovddup_ExtendedIndex = 72,
  kX86InstIdMovdq2q_ExtendedIndex = 73,
  kX86InstIdMovdqa_ExtendedIndex = 74,
  kX86InstIdMovdqu_ExtendedIndex = 75,
  kX86InstIdMovhlps_ExtendedIndex = 76,
  kX86InstIdMovhpd_ExtendedIndex = 77,
  kX86InstIdMovhps_ExtendedIndex = 78,
  kX86InstIdMovlhps_ExtendedIndex = 79,
  kX86InstIdMovlpd_ExtendedIndex = 80,
  kX86InstIdMovlps_ExtendedIndex = 81,
  kX86InstIdMovmskpd_ExtendedIndex = 82,
  kX86InstIdMovmskps_ExtendedIndex = 82,
  kX86InstIdMovntdq_ExtendedIndex = 83,
  kX86InstIdMovntdqa_ExtendedIndex = 84,
  kX86InstIdMovnti_ExtendedIndex = 85,
  kX86InstIdMovntpd_ExtendedIndex = 86,
  kX86InstIdMovntps_ExtendedIndex = 87,
  kX86InstIdMovntq_ExtendedIndex = 88,
  kX86InstIdMovq_ExtendedIndex = 89,
  kX86InstIdMovq2dq_ExtendedIndex = 90,
  kX86InstIdMovsd_ExtendedIndex = 91,
  kX86InstIdMovshdup_ExtendedIndex = 25,
  kX86InstIdMovsldup_ExtendedIndex = 25,
  kX86InstIdMovss_ExtendedIndex = 92,
  kX86InstIdMovsx_ExtendedIndex = 93,
  kX86InstIdMovsxd_ExtendedIndex = 94,
  kX86InstIdMovupd_ExtendedIndex = 95,
  kX86InstIdMovups_ExtendedIndex = 96,
  kX86InstIdMovzx_ExtendedIndex = 93,
  kX86InstIdMpsadbw_ExtendedIndex = 3,
  kX86InstIdMul_ExtendedIndex = 54,
  kX86InstIdMulpd_ExtendedIndex = 2,
  kX86InstIdMulps_ExtendedIndex = 2,
  kX86InstIdMulsd_ExtendedIndex = 2,
  kX86InstIdMulss_ExtendedIndex = 2,
  kX86InstIdMulx_ExtendedIndex = 4,
  kX86InstIdMwait_ExtendedIndex = 15,
  kX86InstIdNeg_ExtendedIndex = 97,
  kX86InstIdNop_ExtendedIndex = 17,
  kX86InstIdNot_ExtendedIndex = 97,
  kX86InstIdOr_ExtendedIndex = 1,
  kX86InstIdOrpd_ExtendedIndex = 2,
  kX86InstIdOrps_ExtendedIndex = 2,
  kX86InstIdPabsb_ExtendedIndex = 98,
  kX86InstIdPabsd_ExtendedIndex = 98,
  kX86InstIdPabsw_ExtendedIndex = 98,
  kX86InstIdPackssdw_ExtendedIndex = 98,
  kX86InstIdPacksswb_ExtendedIndex = 98,
  kX86InstIdPackusdw_ExtendedIndex = 2,
  kX86InstIdPackuswb_ExtendedIndex = 98,
  kX86InstIdPaddb_ExtendedIndex = 98,
  kX86InstIdPaddd_ExtendedIndex = 98,
  kX86InstIdPaddq_ExtendedIndex = 98,
  kX86InstIdPaddsb_ExtendedIndex = 98,
  kX86InstIdPaddsw_ExtendedIndex = 98,
  kX86InstIdPaddusb_ExtendedIndex = 98,
  kX86InstIdPaddusw_ExtendedIndex = 98,
  kX86InstIdPaddw_ExtendedIndex = 98,
  kX86InstIdPalignr_ExtendedIndex = 99,
  kX86InstIdPand_ExtendedIndex = 98,
  kX86InstIdPandn_ExtendedIndex = 98,
  kX86InstIdPause_ExtendedIndex = 17,
  kX86InstIdPavgb_ExtendedIndex = 98,
  kX86InstIdPavgw_ExtendedIndex = 98,
  kX86InstIdPblendvb_ExtendedIndex = 6,
  kX86InstIdPblendw_ExtendedIndex = 3,
  kX86InstIdPclmulqdq_ExtendedIndex = 3,
  kX86InstIdPcmpeqb_ExtendedIndex = 98,
  kX86InstIdPcmpeqd_ExtendedIndex = 98,
  kX86InstIdPcmpeqq_ExtendedIndex = 2,
  kX86InstIdPcmpeqw_ExtendedIndex = 98,
  kX86InstIdPcmpestri_ExtendedIndex = 3,
  kX86InstIdPcmpestrm_ExtendedIndex = 3,
  kX86InstIdPcmpgtb_ExtendedIndex = 98,
  kX86InstIdPcmpgtd_ExtendedIndex = 98,
  kX86InstIdPcmpgtq_ExtendedIndex = 2,
  kX86InstIdPcmpgtw_ExtendedIndex = 98,
  kX86InstIdPcmpistri_ExtendedIndex = 3,
  kX86InstIdPcmpistrm_ExtendedIndex = 3,
  kX86InstIdPdep_ExtendedIndex = 4,
  kX86InstIdPext_ExtendedIndex = 4,
  kX86InstIdPextrb_ExtendedIndex = 100,
  kX86InstIdPextrd_ExtendedIndex = 101,
  kX86InstIdPextrq_ExtendedIndex = 102,
  kX86InstIdPextrw_ExtendedIndex = 103,
  kX86InstIdPf2id_ExtendedIndex = 104,
  kX86InstIdPf2iw_ExtendedIndex = 104,
  kX86InstIdPfacc_ExtendedIndex = 104,
  kX86InstIdPfadd_ExtendedIndex = 104,
  kX86InstIdPfcmpeq_ExtendedIndex = 104,
  kX86InstIdPfcmpge_ExtendedIndex = 104,
  kX86InstIdPfcmpgt_ExtendedIndex = 104,
  kX86InstIdPfmax_ExtendedIndex = 104,
  kX86InstIdPfmin_ExtendedIndex = 104,
  kX86InstIdPfmul_ExtendedIndex = 104,
  kX86InstIdPfnacc_ExtendedIndex = 104,
  kX86InstIdPfpnacc_ExtendedIndex = 104,
  kX86InstIdPfrcp_ExtendedIndex = 104,
  kX86InstIdPfrcpit1_ExtendedIndex = 104,
  kX86InstIdPfrcpit2_ExtendedIndex = 104,
  kX86InstIdPfrsqit1_ExtendedIndex = 104,
  kX86InstIdPfrsqrt_ExtendedIndex = 104,
  kX86InstIdPfsub_ExtendedIndex = 104,
  kX86InstIdPfsubr_ExtendedIndex = 104,
  kX86InstIdPhaddd_ExtendedIndex = 98,
  kX86InstIdPhaddsw_ExtendedIndex = 98,
  kX86InstIdPhaddw_ExtendedIndex = 98,
  kX86InstIdPhminposuw_ExtendedIndex = 2,
  kX86InstIdPhsubd_ExtendedIndex = 98,
  kX86InstIdPhsubsw_ExtendedIndex = 98,
  kX86InstIdPhsubw_ExtendedIndex = 98,
  kX86InstIdPi2fd_ExtendedIndex = 104,
  kX86InstIdPi2fw_ExtendedIndex = 104,
  kX86InstIdPinsrb_ExtendedIndex = 105,
  kX86InstIdPinsrd_ExtendedIndex = 105,
  kX86InstIdPinsrq_ExtendedIndex = 106,
  kX86InstIdPinsrw_ExtendedIndex = 107,
  kX86InstIdPmaddubsw_ExtendedIndex = 98,
  kX86InstIdPmaddwd_ExtendedIndex = 98,
  kX86InstIdPmaxsb_ExtendedIndex = 2,
  kX86InstIdPmaxsd_ExtendedIndex = 2,
  kX86InstIdPmaxsw_ExtendedIndex = 98,
  kX86InstIdPmaxub_ExtendedIndex = 98,
  kX86InstIdPmaxud_ExtendedIndex = 2,
  kX86InstIdPmaxuw_ExtendedIndex = 2,
  kX86InstIdPminsb_ExtendedIndex = 2,
  kX86InstIdPminsd_ExtendedIndex = 2,
  kX86InstIdPminsw_ExtendedIndex = 98,
  kX86InstIdPminub_ExtendedIndex = 98,
  kX86InstIdPminud_ExtendedIndex = 2,
  kX86InstIdPminuw_ExtendedIndex = 2,
  kX86InstIdPmovmskb_ExtendedIndex = 108,
  kX86InstIdPmovsxbd_ExtendedIndex = 25,
  kX86InstIdPmovsxbq_ExtendedIndex = 25,
  kX86InstIdPmovsxbw_ExtendedIndex = 25,
  kX86InstIdPmovsxdq_ExtendedIndex = 25,
  kX86InstIdPmovsxwd_ExtendedIndex = 25,
  kX86InstIdPmovsxwq_ExtendedIndex = 25,
  kX86InstIdPmovzxbd_ExtendedIndex = 25,
  kX86InstIdPmovzxbq_ExtendedIndex = 25,
  kX86InstIdPmovzxbw_ExtendedIndex = 25,
  kX86InstIdPmovzxdq_ExtendedIndex = 25,
  kX86InstIdPmovzxwd_ExtendedIndex = 25,
  kX86InstIdPmovzxwq_ExtendedIndex = 25,
  kX86InstIdPmuldq_ExtendedIndex = 2,
  kX86InstIdPmulhrsw_ExtendedIndex = 98,
  kX86InstIdPmulhuw_ExtendedIndex = 98,
  kX86InstIdPmulhw_ExtendedIndex = 98,
  kX86InstIdPmulld_ExtendedIndex = 2,
  kX86InstIdPmullw_ExtendedIndex = 98,
  kX86InstIdPmuludq_ExtendedIndex = 98,
  kX86InstIdPop_ExtendedIndex = 109,
  kX86InstIdPopa_ExtendedIndex = 15,
  kX86InstIdPopcnt_ExtendedIndex = 8,
  kX86InstIdPopf_ExtendedIndex = 15,
  kX86InstIdPor_ExtendedIndex = 98,
  kX86InstIdPrefetch_ExtendedIndex = 110,
  kX86InstIdPrefetch3dNow_ExtendedIndex = 18,
  kX86InstIdPrefetchw3dNow_ExtendedIndex = 18,
  kX86InstIdPsadbw_ExtendedIndex = 98,
  kX86InstIdPshufb_ExtendedIndex = 98,
  kX86InstIdPshufd_ExtendedIndex = 111,
  kX86InstIdPshufhw_ExtendedIndex = 111,
  kX86InstIdPshuflw_ExtendedIndex = 111,
  kX86InstIdPshufw_ExtendedIndex = 112,
  kX86InstIdPsignb_ExtendedIndex = 98,
  kX86InstIdPsignd_ExtendedIndex = 98,
  kX86InstIdPsignw_ExtendedIndex = 98,
  kX86InstIdPslld_ExtendedIndex = 113,
  kX86InstIdPslldq_ExtendedIndex = 114,
  kX86InstIdPsllq_ExtendedIndex = 115,
  kX86InstIdPsllw_ExtendedIndex = 116,
  kX86InstIdPsrad_ExtendedIndex = 117,
  kX86InstIdPsraw_ExtendedIndex = 118,
  kX86InstIdPsrld_ExtendedIndex = 119,
  kX86InstIdPsrldq_ExtendedIndex = 120,
  kX86InstIdPsrlq_ExtendedIndex = 121,
  kX86InstIdPsrlw_ExtendedIndex = 122,
  kX86InstIdPsubb_ExtendedIndex = 98,
  kX86InstIdPsubd_ExtendedIndex = 98,
  kX86InstIdPsubq_ExtendedIndex = 98,
  kX86InstIdPsubsb_ExtendedIndex = 98,
  kX86InstIdPsubsw_ExtendedIndex = 98,
  kX86InstIdPsubusb_ExtendedIndex = 98,
  kX86InstIdPsubusw_ExtendedIndex = 98,
  kX86InstIdPsubw_ExtendedIndex = 98,
  kX86InstIdPswapd_ExtendedIndex = 104,
  kX86InstIdPtest_ExtendedIndex = 23,
  kX86InstIdPunpckhbw_ExtendedIndex = 98,
  kX86InstIdPunpckhdq_ExtendedIndex = 98,
  kX86InstIdPunpckhqdq_ExtendedIndex = 2,
  kX86InstIdPunpckhwd_ExtendedIndex = 98,
  kX86InstIdPunpcklbw_ExtendedIndex = 98,
  kX86InstIdPunpckldq_ExtendedIndex = 98,
  kX86InstIdPunpcklqdq_ExtendedIndex = 2,
  kX86InstIdPunpcklwd_ExtendedIndex = 98,
  kX86InstIdPush_ExtendedIndex = 123,
  kX86InstIdPusha_ExtendedIndex = 15,
  kX86InstIdPushf_ExtendedIndex = 15,
  kX86InstIdPxor_ExtendedIndex = 98,
  kX86InstIdRcl_ExtendedIndex = 124,
  kX86InstIdRcpps_ExtendedIndex = 25,
  kX86InstIdRcpss_ExtendedIndex = 30,
  kX86InstIdRcr_ExtendedIndex = 124,
  kX86InstIdRdfsbase_ExtendedIndex = 125,
  kX86InstIdRdgsbase_ExtendedIndex = 125,
  kX86InstIdRdrand_ExtendedIndex = 126,
  kX86InstIdRdtsc_ExtendedIndex = 15,
  kX86InstIdRdtscp_ExtendedIndex = 15,
  kX86InstIdRepLodsb_ExtendedIndex = 127,
  kX86InstIdRepLodsd_ExtendedIndex = 127,
  kX86InstIdRepLodsq_ExtendedIndex = 128,
  kX86InstIdRepLodsw_ExtendedIndex = 127,
  kX86InstIdRepMovsb_ExtendedIndex = 129,
  kX86InstIdRepMovsd_ExtendedIndex = 129,
  kX86InstIdRepMovsq_ExtendedIndex = 130,
  kX86InstIdRepMovsw_ExtendedIndex = 129,
  kX86InstIdRepStosb_ExtendedIndex = 127,
  kX86InstIdRepStosd_ExtendedIndex = 127,
  kX86InstIdRepStosq_ExtendedIndex = 128,
  kX86InstIdRepStosw_ExtendedIndex = 127,
  kX86InstIdRepeCmpsb_ExtendedIndex = 129,
  kX86InstIdRepeCmpsd_ExtendedIndex = 129,
  kX86InstIdRepeCmpsq_ExtendedIndex = 130,
  kX86InstIdRepeCmpsw_ExtendedIndex = 129,
  kX86InstIdRepeScasb_ExtendedIndex = 129,
  kX86InstIdRepeScasd_ExtendedIndex = 129,
  kX86InstIdRepeScasq_ExtendedIndex = 130,
  kX86InstIdRepeScasw_ExtendedIndex = 129,
  kX86InstIdRepneCmpsb_ExtendedIndex = 129,
  kX86InstIdRepneCmpsd_ExtendedIndex = 129,
  kX86InstIdRepneCmpsq_ExtendedIndex = 130,
  kX86InstIdRepneCmpsw_ExtendedIndex = 129,
  kX86InstIdRepneScasb_ExtendedIndex = 129,
  kX86InstIdRepneScasd_ExtendedIndex = 129,
  kX86InstIdRepneScasq_ExtendedIndex = 130,
  kX86InstIdRepneScasw_ExtendedIndex = 129,
  kX86InstIdRet_ExtendedIndex = 131,
  kX86InstIdRol_ExtendedIndex = 124,
  kX86InstIdRor_ExtendedIndex = 124,
  kX86InstIdRorx_ExtendedIndex = 132,
  kX86InstIdRoundpd_ExtendedIndex = 111,
  kX86InstIdRoundps_ExtendedIndex = 111,
  kX86InstIdRoundsd_ExtendedIndex = 133,
  kX86InstIdRoundss_ExtendedIndex = 134,
  kX86InstIdRsqrtps_ExtendedIndex = 25,
  kX86InstIdRsqrtss_ExtendedIndex = 30,
  kX86InstIdSahf_ExtendedIndex = 15,
  kX86InstIdSal_ExtendedIndex = 124,
  kX86InstIdSar_ExtendedIndex = 124,
  kX86InstIdSarx_ExtendedIndex = 5,
  kX86InstIdSbb_ExtendedIndex = 1,
  kX86InstIdSeta_ExtendedIndex = 135,
  kX86InstIdSetae_ExtendedIndex = 135,
  kX86InstIdSetb_ExtendedIndex = 135,
  kX86InstIdSetbe_ExtendedIndex = 135,
  kX86InstIdSetc_ExtendedIndex = 135,
  kX86InstIdSete_ExtendedIndex = 135,
  kX86InstIdSetg_ExtendedIndex = 135,
  kX86InstIdSetge_ExtendedIndex = 135,
  kX86InstIdSetl_ExtendedIndex = 135,
  kX86InstIdSetle_ExtendedIndex = 135,
  kX86InstIdSetna_ExtendedIndex = 135,
  kX86InstIdSetnae_ExtendedIndex = 135,
  kX86InstIdSetnb_ExtendedIndex = 135,
  kX86InstIdSetnbe_ExtendedIndex = 135,
  kX86InstIdSetnc_ExtendedIndex = 135,
  kX86InstIdSetne_ExtendedIndex = 135,
  kX86InstIdSetng_ExtendedIndex = 135,
  kX86InstIdSetnge_ExtendedIndex = 135,
  kX86InstIdSetnl_ExtendedIndex = 135,
  kX86InstIdSetnle_ExtendedIndex = 135,
  kX86InstIdSetno_ExtendedIndex = 135,
  kX86InstIdSetnp_ExtendedIndex = 135,
  kX86InstIdSetns_ExtendedIndex = 135,
  kX86InstIdSetnz_ExtendedIndex = 135,
  kX86InstIdSeto_ExtendedIndex = 135,
  kX86InstIdSetp_ExtendedIndex = 135,
  kX86InstIdSetpe_ExtendedIndex = 135,
  kX86InstIdSetpo_ExtendedIndex = 135,
  kX86InstIdSets_ExtendedIndex = 135,
  kX86InstIdSetz_ExtendedIndex = 135,
  kX86InstIdSfence_ExtendedIndex = 63,
  kX86InstIdShl_ExtendedIndex = 124,
  kX86InstIdShld_ExtendedIndex = 136,
  kX86InstIdShlx_ExtendedIndex = 5,
  kX86InstIdShr_ExtendedIndex = 124,
  kX86InstIdShrd_ExtendedIndex = 137,
  kX86InstIdShrx_ExtendedIndex = 5,
  kX86InstIdShufpd_ExtendedIndex = 3,
  kX86InstIdShufps_ExtendedIndex = 3,
  kX86InstIdSqrtpd_ExtendedIndex = 25,
  kX86InstIdSqrtps_ExtendedIndex = 25,
  kX86InstIdSqrtsd_ExtendedIndex = 33,
  kX86InstIdSqrtss_ExtendedIndex = 30,
  kX86InstIdStc_ExtendedIndex = 17,
  kX86InstIdStd_ExtendedIndex = 17,
  kX86InstIdStmxcsr_ExtendedIndex = 18,
  kX86InstIdSub_ExtendedIndex = 1,
  kX86InstIdSubpd_ExtendedIndex = 2,
  kX86InstIdSubps_ExtendedIndex = 2,
  kX86InstIdSubsd_ExtendedIndex = 2,
  kX86InstIdSubss_ExtendedIndex = 2,
  kX86InstIdTest_ExtendedIndex = 138,
  kX86InstIdTzcnt_ExtendedIndex = 139,
  kX86InstIdUcomisd_ExtendedIndex = 23,
  kX86InstIdUcomiss_ExtendedIndex = 23,
  kX86InstIdUd2_ExtendedIndex = 17,
  kX86InstIdUnpckhpd_ExtendedIndex = 2,
  kX86InstIdUnpckhps_ExtendedIndex = 2,
  kX86InstIdUnpcklpd_ExtendedIndex = 2,
  kX86InstIdUnpcklps_ExtendedIndex = 2,
  kX86InstIdVaddpd_ExtendedIndex = 140,
  kX86InstIdVaddps_ExtendedIndex = 140,
  kX86InstIdVaddsd_ExtendedIndex = 140,
  kX86InstIdVaddss_ExtendedIndex = 140,
  kX86InstIdVaddsubpd_ExtendedIndex = 140,
  kX86InstIdVaddsubps_ExtendedIndex = 140,
  kX86InstIdVaesdec_ExtendedIndex = 141,
  kX86InstIdVaesdeclast_ExtendedIndex = 141,
  kX86InstIdVaesenc_ExtendedIndex = 141,
  kX86InstIdVaesenclast_ExtendedIndex = 141,
  kX86InstIdVaesimc_ExtendedIndex = 142,
  kX86InstIdVaeskeygenassist_ExtendedIndex = 143,
  kX86InstIdVandnpd_ExtendedIndex = 140,
  kX86InstIdVandnps_ExtendedIndex = 140,
  kX86InstIdVandpd_ExtendedIndex = 140,
  kX86InstIdVandps_ExtendedIndex = 140,
  kX86InstIdVblendpd_ExtendedIndex = 144,
  kX86InstIdVblendps_ExtendedIndex = 144,
  kX86InstIdVblendvpd_ExtendedIndex = 145,
  kX86InstIdVblendvps_ExtendedIndex = 145,
  kX86InstIdVbroadcastf128_ExtendedIndex = 146,
  kX86InstIdVbroadcasti128_ExtendedIndex = 146,
  kX86InstIdVbroadcastsd_ExtendedIndex = 147,
  kX86InstIdVbroadcastss_ExtendedIndex = 147,
  kX86InstIdVcmppd_ExtendedIndex = 144,
  kX86InstIdVcmpps_ExtendedIndex = 144,
  kX86InstIdVcmpsd_ExtendedIndex = 148,
  kX86InstIdVcmpss_ExtendedIndex = 148,
  kX86InstIdVcomisd_ExtendedIndex = 142,
  kX86InstIdVcomiss_ExtendedIndex = 142,
  kX86InstIdVcvtdq2pd_ExtendedIndex = 149,
  kX86InstIdVcvtdq2ps_ExtendedIndex = 150,
  kX86InstIdVcvtpd2dq_ExtendedIndex = 151,
  kX86InstIdVcvtpd2ps_ExtendedIndex = 151,
  kX86InstIdVcvtph2ps_ExtendedIndex = 149,
  kX86InstIdVcvtps2dq_ExtendedIndex = 150,
  kX86InstIdVcvtps2pd_ExtendedIndex = 149,
  kX86InstIdVcvtps2ph_ExtendedIndex = 152,
  kX86InstIdVcvtsd2si_ExtendedIndex = 153,
  kX86InstIdVcvtsd2ss_ExtendedIndex = 141,
  kX86InstIdVcvtsi2sd_ExtendedIndex = 154,
  kX86InstIdVcvtsi2ss_ExtendedIndex = 154,
  kX86InstIdVcvtss2sd_ExtendedIndex = 141,
  kX86InstIdVcvtss2si_ExtendedIndex = 153,
  kX86InstIdVcvttpd2dq_ExtendedIndex = 155,
  kX86InstIdVcvttps2dq_ExtendedIndex = 150,
  kX86InstIdVcvttsd2si_ExtendedIndex = 153,
  kX86InstIdVcvttss2si_ExtendedIndex = 153,
  kX86InstIdVdivpd_ExtendedIndex = 140,
  kX86InstIdVdivps_ExtendedIndex = 140,
  kX86InstIdVdivsd_ExtendedIndex = 141,
  kX86InstIdVdivss_ExtendedIndex = 141,
  kX86InstIdVdppd_ExtendedIndex = 148,
  kX86InstIdVdpps_ExtendedIndex = 144,
  kX86InstIdVextractf128_ExtendedIndex = 156,
  kX86InstIdVextracti128_ExtendedIndex = 156,
  kX86InstIdVextractps_ExtendedIndex = 157,
  kX86InstIdVfmadd132pd_ExtendedIndex = 158,
  kX86InstIdVfmadd132ps_ExtendedIndex = 140,
  kX86InstIdVfmadd132sd_ExtendedIndex = 159,
  kX86InstIdVfmadd132ss_ExtendedIndex = 141,
  kX86InstIdVfmadd213pd_ExtendedIndex = 158,
  kX86InstIdVfmadd213ps_ExtendedIndex = 140,
  kX86InstIdVfmadd213sd_ExtendedIndex = 159,
  kX86InstIdVfmadd213ss_ExtendedIndex = 141,
  kX86InstIdVfmadd231pd_ExtendedIndex = 158,
  kX86InstIdVfmadd231ps_ExtendedIndex = 140,
  kX86InstIdVfmadd231sd_ExtendedIndex = 159,
  kX86InstIdVfmadd231ss_ExtendedIndex = 141,
  kX86InstIdVfmaddpd_ExtendedIndex = 160,
  kX86InstIdVfmaddps_ExtendedIndex = 160,
  kX86InstIdVfmaddsd_ExtendedIndex = 161,
  kX86InstIdVfmaddss_ExtendedIndex = 161,
  kX86InstIdVfmaddsub132pd_ExtendedIndex = 158,
  kX86InstIdVfmaddsub132ps_ExtendedIndex = 140,
  kX86InstIdVfmaddsub213pd_ExtendedIndex = 158,
  kX86InstIdVfmaddsub213ps_ExtendedIndex = 140,
  kX86InstIdVfmaddsub231pd_ExtendedIndex = 158,
  kX86InstIdVfmaddsub231ps_ExtendedIndex = 140,
  kX86InstIdVfmaddsubpd_ExtendedIndex = 160,
  kX86InstIdVfmaddsubps_ExtendedIndex = 160,
  kX86InstIdVfmsub132pd_ExtendedIndex = 158,
  kX86InstIdVfmsub132ps_ExtendedIndex = 140,
  kX86InstIdVfmsub132sd_ExtendedIndex = 159,
  kX86InstIdVfmsub132ss_ExtendedIndex = 141,
  kX86InstIdVfmsub213pd_ExtendedIndex = 158,
  kX86InstIdVfmsub213ps_ExtendedIndex = 140,
  kX86InstIdVfmsub213sd_ExtendedIndex = 159,
  kX86InstIdVfmsub213ss_ExtendedIndex = 141,
  kX86InstIdVfmsub231pd_ExtendedIndex = 158,
  kX86InstIdVfmsub231ps_ExtendedIndex = 140,
  kX86InstIdVfmsub231sd_ExtendedIndex = 159,
  kX86InstIdVfmsub231ss_ExtendedIndex = 141,
  kX86InstIdVfmsubadd132pd_ExtendedIndex = 158,
  kX86InstIdVfmsubadd132ps_ExtendedIndex = 140,
  kX86InstIdVfmsubadd213pd_ExtendedIndex = 158,
  kX86InstIdVfmsubadd213ps_ExtendedIndex = 140,
  kX86InstIdVfmsubadd231pd_ExtendedIndex = 158,
  kX86InstIdVfmsubadd231ps_ExtendedIndex = 140,
  kX86InstIdVfmsubaddpd_ExtendedIndex = 160,
  kX86InstIdVfmsubaddps_ExtendedIndex = 160,
  kX86InstIdVfmsubpd_ExtendedIndex = 160,
  kX86InstIdVfmsubps_ExtendedIndex = 160,
  kX86InstIdVfmsubsd_ExtendedIndex = 161,
  kX86InstIdVfmsubss_ExtendedIndex = 161,
  kX86InstIdVfnmadd132pd_ExtendedIndex = 158,
  kX86InstIdVfnmadd132ps_ExtendedIndex = 140,
  kX86InstIdVfnmadd132sd_ExtendedIndex = 159,
  kX86InstIdVfnmadd132ss_ExtendedIndex = 141,
  kX86InstIdVfnmadd213pd_ExtendedIndex = 158,
  kX86InstIdVfnmadd213ps_ExtendedIndex = 140,
  kX86InstIdVfnmadd213sd_ExtendedIndex = 159,
  kX86InstIdVfnmadd213ss_ExtendedIndex = 141,
  kX86InstIdVfnmadd231pd_ExtendedIndex = 158,
  kX86InstIdVfnmadd231ps_ExtendedIndex = 140,
  kX86InstIdVfnmadd231sd_ExtendedIndex = 159,
  kX86InstIdVfnmadd231ss_ExtendedIndex = 141,
  kX86InstIdVfnmaddpd_ExtendedIndex = 160,
  kX86InstIdVfnmaddps_ExtendedIndex = 160,
  kX86InstIdVfnmaddsd_ExtendedIndex = 161,
  kX86InstIdVfnmaddss_ExtendedIndex = 161,
  kX86InstIdVfnmsub132pd_ExtendedIndex = 158,
  kX86InstIdVfnmsub132ps_ExtendedIndex = 140,
  kX86InstIdVfnmsub132sd_ExtendedIndex = 159,
  kX86InstIdVfnmsub132ss_ExtendedIndex = 141,
  kX86InstIdVfnmsub213pd_ExtendedIndex = 158,
  kX86InstIdVfnmsub213ps_ExtendedIndex = 140,
  kX86InstIdVfnmsub213sd_ExtendedIndex = 159,
  kX86InstIdVfnmsub213ss_ExtendedIndex = 141,
  kX86InstIdVfnmsub231pd_ExtendedIndex = 158,
  kX86InstIdVfnmsub231ps_ExtendedIndex = 140,
  kX86InstIdVfnmsub231sd_ExtendedIndex = 159,
  kX86InstIdVfnmsub231ss_ExtendedIndex = 141,
  kX86InstIdVfnmsubpd_ExtendedIndex = 160,
  kX86InstIdVfnmsubps_ExtendedIndex = 160,
  kX86InstIdVfnmsubsd_ExtendedIndex = 161,
  kX86InstIdVfnmsubss_ExtendedIndex = 161,
  kX86InstIdVfrczpd_ExtendedIndex = 162,
  kX86InstIdVfrczps_ExtendedIndex = 162,
  kX86InstIdVfrczsd_ExtendedIndex = 163,
  kX86InstIdVfrczss_ExtendedIndex = 163,
  kX86InstIdVgatherdpd_ExtendedIndex = 164,
  kX86InstIdVgatherdps_ExtendedIndex = 165,
  kX86InstIdVgatherqpd_ExtendedIndex = 164,
  kX86InstIdVgatherqps_ExtendedIndex = 166,
  kX86InstIdVhaddpd_ExtendedIndex = 140,
  kX86InstIdVhaddps_ExtendedIndex = 140,
  kX86InstIdVhsubpd_ExtendedIndex = 140,
  kX86InstIdVhsubps_ExtendedIndex = 140,
  kX86InstIdVinsertf128_ExtendedIndex = 167,
  kX86InstIdVinserti128_ExtendedIndex = 167,
  kX86InstIdVinsertps_ExtendedIndex = 148,
  kX86InstIdVlddqu_ExtendedIndex = 168,
  kX86InstIdVldmxcsr_ExtendedIndex = 169,
  kX86InstIdVmaskmovdqu_ExtendedIndex = 170,
  kX86InstIdVmaskmovpd_ExtendedIndex = 171,
  kX86InstIdVmaskmovps_ExtendedIndex = 172,
  kX86InstIdVmaxpd_ExtendedIndex = 140,
  kX86InstIdVmaxps_ExtendedIndex = 140,
  kX86InstIdVmaxsd_ExtendedIndex = 140,
  kX86InstIdVmaxss_ExtendedIndex = 140,
  kX86InstIdVminpd_ExtendedIndex = 140,
  kX86InstIdVminps_ExtendedIndex = 140,
  kX86InstIdVminsd_ExtendedIndex = 140,
  kX86InstIdVminss_ExtendedIndex = 140,
  kX86InstIdVmovapd_ExtendedIndex = 173,
  kX86InstIdVmovaps_ExtendedIndex = 174,
  kX86InstIdVmovd_ExtendedIndex = 175,
  kX86InstIdVmovddup_ExtendedIndex = 150,
  kX86InstIdVmovdqa_ExtendedIndex = 176,
  kX86InstIdVmovdqu_ExtendedIndex = 177,
  kX86InstIdVmovhlps_ExtendedIndex = 178,
  kX86InstIdVmovhpd_ExtendedIndex = 179,
  kX86InstIdVmovhps_ExtendedIndex = 180,
  kX86InstIdVmovlhps_ExtendedIndex = 178,
  kX86InstIdVmovlpd_ExtendedIndex = 181,
  kX86InstIdVmovlps_ExtendedIndex = 182,
  kX86InstIdVmovmskpd_ExtendedIndex = 183,
  kX86InstIdVmovmskps_ExtendedIndex = 183,
  kX86InstIdVmovntdq_ExtendedIndex = 184,
  kX86InstIdVmovntdqa_ExtendedIndex = 168,
  kX86InstIdVmovntpd_ExtendedIndex = 185,
  kX86InstIdVmovntps_ExtendedIndex = 185,
  kX86InstIdVmovq_ExtendedIndex = 186,
  kX86InstIdVmovsd_ExtendedIndex = 187,
  kX86InstIdVmovshdup_ExtendedIndex = 150,
  kX86InstIdVmovsldup_ExtendedIndex = 150,
  kX86InstIdVmovss_ExtendedIndex = 188,
  kX86InstIdVmovupd_ExtendedIndex = 189,
  kX86InstIdVmovups_ExtendedIndex = 190,
  kX86InstIdVmpsadbw_ExtendedIndex = 144,
  kX86InstIdVmulpd_ExtendedIndex = 140,
  kX86InstIdVmulps_ExtendedIndex = 140,
  kX86InstIdVmulsd_ExtendedIndex = 140,
  kX86InstIdVmulss_ExtendedIndex = 140,
  kX86InstIdVorpd_ExtendedIndex = 140,
  kX86InstIdVorps_ExtendedIndex = 140,
  kX86InstIdVpabsb_ExtendedIndex = 150,
  kX86InstIdVpabsd_ExtendedIndex = 150,
  kX86InstIdVpabsw_ExtendedIndex = 150,
  kX86InstIdVpackssdw_ExtendedIndex = 140,
  kX86InstIdVpacksswb_ExtendedIndex = 140,
  kX86InstIdVpackusdw_ExtendedIndex = 140,
  kX86InstIdVpackuswb_ExtendedIndex = 140,
  kX86InstIdVpaddb_ExtendedIndex = 140,
  kX86InstIdVpaddd_ExtendedIndex = 140,
  kX86InstIdVpaddq_ExtendedIndex = 140,
  kX86InstIdVpaddsb_ExtendedIndex = 140,
  kX86InstIdVpaddsw_ExtendedIndex = 140,
  kX86InstIdVpaddusb_ExtendedIndex = 140,
  kX86InstIdVpaddusw_ExtendedIndex = 140,
  kX86InstIdVpaddw_ExtendedIndex = 140,
  kX86InstIdVpalignr_ExtendedIndex = 144,
  kX86InstIdVpand_ExtendedIndex = 140,
  kX86InstIdVpandn_ExtendedIndex = 140,
  kX86InstIdVpavgb_ExtendedIndex = 140,
  kX86InstIdVpavgw_ExtendedIndex = 140,
  kX86InstIdVpblendd_ExtendedIndex = 144,
  kX86InstIdVpblendvb_ExtendedIndex = 191,
  kX86InstIdVpblendw_ExtendedIndex = 144,
  kX86InstIdVpbroadcastb_ExtendedIndex = 149,
  kX86InstIdVpbroadcastd_ExtendedIndex = 149,
  kX86InstIdVpbroadcastq_ExtendedIndex = 149,
  kX86InstIdVpbroadcastw_ExtendedIndex = 149,
  kX86InstIdVpclmulqdq_ExtendedIndex = 148,
  kX86InstIdVpcmov_ExtendedIndex = 192,
  kX86InstIdVpcmpeqb_ExtendedIndex = 140,
  kX86InstIdVpcmpeqd_ExtendedIndex = 140,
  kX86InstIdVpcmpeqq_ExtendedIndex = 140,
  kX86InstIdVpcmpeqw_ExtendedIndex = 140,
  kX86InstIdVpcmpestri_ExtendedIndex = 143,
  kX86InstIdVpcmpestrm_ExtendedIndex = 143,
  kX86InstIdVpcmpgtb_ExtendedIndex = 140,
  kX86InstIdVpcmpgtd_ExtendedIndex = 140,
  kX86InstIdVpcmpgtq_ExtendedIndex = 140,
  kX86InstIdVpcmpgtw_ExtendedIndex = 140,
  kX86InstIdVpcmpistri_ExtendedIndex = 143,
  kX86InstIdVpcmpistrm_ExtendedIndex = 143,
  kX86InstIdVpcomb_ExtendedIndex = 193,
  kX86InstIdVpcomd_ExtendedIndex = 193,
  kX86InstIdVpcomq_ExtendedIndex = 193,
  kX86InstIdVpcomub_ExtendedIndex = 193,
  kX86InstIdVpcomud_ExtendedIndex = 193,
  kX86InstIdVpcomuq_ExtendedIndex = 193,
  kX86InstIdVpcomuw_ExtendedIndex = 193,
  kX86InstIdVpcomw_ExtendedIndex = 193,
  kX86InstIdVperm2f128_ExtendedIndex = 194,
  kX86InstIdVperm2i128_ExtendedIndex = 194,
  kX86InstIdVpermd_ExtendedIndex = 195,
  kX86InstIdVpermil2pd_ExtendedIndex = 196,
  kX86InstIdVpermil2ps_ExtendedIndex = 196,
  kX86InstIdVpermilpd_ExtendedIndex = 197,
  kX86InstIdVpermilps_ExtendedIndex = 198,
  kX86InstIdVpermpd_ExtendedIndex = 199,
  kX86InstIdVpermps_ExtendedIndex = 195,
  kX86InstIdVpermq_ExtendedIndex = 199,
  kX86InstIdVpextrb_ExtendedIndex = 200,
  kX86InstIdVpextrd_ExtendedIndex = 157,
  kX86InstIdVpextrq_ExtendedIndex = 201,
  kX86InstIdVpextrw_ExtendedIndex = 202,
  kX86InstIdVpgatherdd_ExtendedIndex = 165,
  kX86InstIdVpgatherdq_ExtendedIndex = 164,
  kX86InstIdVpgatherqd_ExtendedIndex = 166,
  kX86InstIdVpgatherqq_ExtendedIndex = 164,
  kX86InstIdVphaddbd_ExtendedIndex = 163,
  kX86InstIdVphaddbq_ExtendedIndex = 163,
  kX86InstIdVphaddbw_ExtendedIndex = 163,
  kX86InstIdVphaddd_ExtendedIndex = 140,
  kX86InstIdVphadddq_ExtendedIndex = 163,
  kX86InstIdVphaddsw_ExtendedIndex = 140,
  kX86InstIdVphaddubd_ExtendedIndex = 163,
  kX86InstIdVphaddubq_ExtendedIndex = 163,
  kX86InstIdVphaddubw_ExtendedIndex = 163,
  kX86InstIdVphaddudq_ExtendedIndex = 163,
  kX86InstIdVphadduwd_ExtendedIndex = 163,
  kX86InstIdVphadduwq_ExtendedIndex = 163,
  kX86InstIdVphaddw_ExtendedIndex = 140,
  kX86InstIdVphaddwd_ExtendedIndex = 163,
  kX86InstIdVphaddwq_ExtendedIndex = 163,
  kX86InstIdVphminposuw_ExtendedIndex = 142,
  kX86InstIdVphsubbw_ExtendedIndex = 163,
  kX86InstIdVphsubd_ExtendedIndex = 140,
  kX86InstIdVphsubdq_ExtendedIndex = 163,
  kX86InstIdVphsubsw_ExtendedIndex = 140,
  kX86InstIdVphsubw_ExtendedIndex = 140,
  kX86InstIdVphsubwd_ExtendedIndex = 163,
  kX86InstIdVpinsrb_ExtendedIndex = 203,
  kX86InstIdVpinsrd_ExtendedIndex = 204,
  kX86InstIdVpinsrq_ExtendedIndex = 205,
  kX86InstIdVpinsrw_ExtendedIndex = 206,
  kX86InstIdVpmacsdd_ExtendedIndex = 207,
  kX86InstIdVpmacsdqh_ExtendedIndex = 207,
  kX86InstIdVpmacsdql_ExtendedIndex = 207,
  kX86InstIdVpmacssdd_ExtendedIndex = 207,
  kX86InstIdVpmacssdqh_ExtendedIndex = 207,
  kX86InstIdVpmacssdql_ExtendedIndex = 207,
  kX86InstIdVpmacsswd_ExtendedIndex = 207,
  kX86InstIdVpmacssww_ExtendedIndex = 207,
  kX86InstIdVpmacswd_ExtendedIndex = 207,
  kX86InstIdVpmacsww_ExtendedIndex = 207,
  kX86InstIdVpmadcsswd_ExtendedIndex = 207,
  kX86InstIdVpmadcswd_ExtendedIndex = 207,
  kX86InstIdVpmaddubsw_ExtendedIndex = 140,
  kX86InstIdVpmaddwd_ExtendedIndex = 140,
  kX86InstIdVpmaskmovd_ExtendedIndex = 208,
  kX86InstIdVpmaskmovq_ExtendedIndex = 209,
  kX86InstIdVpmaxsb_ExtendedIndex = 140,
  kX86InstIdVpmaxsd_ExtendedIndex = 140,
  kX86InstIdVpmaxsw_ExtendedIndex = 140,
  kX86InstIdVpmaxub_ExtendedIndex = 140,
  kX86InstIdVpmaxud_ExtendedIndex = 140,
  kX86InstIdVpmaxuw_ExtendedIndex = 140,
  kX86InstIdVpminsb_ExtendedIndex = 140,
  kX86InstIdVpminsd_ExtendedIndex = 140,
  kX86InstIdVpminsw_ExtendedIndex = 140,
  kX86InstIdVpminub_ExtendedIndex = 140,
  kX86InstIdVpminud_ExtendedIndex = 140,
  kX86InstIdVpminuw_ExtendedIndex = 140,
  kX86InstIdVpmovmskb_ExtendedIndex = 183,
  kX86InstIdVpmovsxbd_ExtendedIndex = 150,
  kX86InstIdVpmovsxbq_ExtendedIndex = 150,
  kX86InstIdVpmovsxbw_ExtendedIndex = 150,
  kX86InstIdVpmovsxdq_ExtendedIndex = 150,
  kX86InstIdVpmovsxwd_ExtendedIndex = 150,
  kX86InstIdVpmovsxwq_ExtendedIndex = 150,
  kX86InstIdVpmovzxbd_ExtendedIndex = 150,
  kX86InstIdVpmovzxbq_ExtendedIndex = 150,
  kX86InstIdVpmovzxbw_ExtendedIndex = 150,
  kX86InstIdVpmovzxdq_ExtendedIndex = 150,
  kX86InstIdVpmovzxwd_ExtendedIndex = 150,
  kX86InstIdVpmovzxwq_ExtendedIndex = 150,
  kX86InstIdVpmuldq_ExtendedIndex = 140,
  kX86InstIdVpmulhrsw_ExtendedIndex = 140,
  kX86InstIdVpmulhuw_ExtendedIndex = 140,
  kX86InstIdVpmulhw_ExtendedIndex = 140,
  kX86InstIdVpmulld_ExtendedIndex = 140,
  kX86InstIdVpmullw_ExtendedIndex = 140,
  kX86InstIdVpmuludq_ExtendedIndex = 140,
  kX86InstIdVpor_ExtendedIndex = 140,
  kX86InstIdVpperm_ExtendedIndex = 210,
  kX86InstIdVprotb_ExtendedIndex = 211,
  kX86InstIdVprotd_ExtendedIndex = 212,
  kX86InstIdVprotq_ExtendedIndex = 213,
  kX86InstIdVprotw_ExtendedIndex = 214,
  kX86InstIdVpsadbw_ExtendedIndex = 140,
  kX86InstIdVpshab_ExtendedIndex = 215,
  kX86InstIdVpshad_ExtendedIndex = 215,
  kX86InstIdVpshaq_ExtendedIndex = 215,
  kX86InstIdVpshaw_ExtendedIndex = 215,
  kX86InstIdVpshlb_ExtendedIndex = 215,
  kX86InstIdVpshld_ExtendedIndex = 215,
  kX86InstIdVpshlq_ExtendedIndex = 215,
  kX86InstIdVpshlw_ExtendedIndex = 215,
  kX86InstIdVpshufb_ExtendedIndex = 140,
  kX86InstIdVpshufd_ExtendedIndex = 216,
  kX86InstIdVpshufhw_ExtendedIndex = 216,
  kX86InstIdVpshuflw_ExtendedIndex = 216,
  kX86InstIdVpsignb_ExtendedIndex = 140,
  kX86InstIdVpsignd_ExtendedIndex = 140,
  kX86InstIdVpsignw_ExtendedIndex = 140,
  kX86InstIdVpslld_ExtendedIndex = 217,
  kX86InstIdVpslldq_ExtendedIndex = 218,
  kX86InstIdVpsllq_ExtendedIndex = 219,
  kX86InstIdVpsllvd_ExtendedIndex = 140,
  kX86InstIdVpsllvq_ExtendedIndex = 158,
  kX86InstIdVpsllw_ExtendedIndex = 220,
  kX86InstIdVpsrad_ExtendedIndex = 221,
  kX86InstIdVpsravd_ExtendedIndex = 140,
  kX86InstIdVpsraw_ExtendedIndex = 222,
  kX86InstIdVpsrld_ExtendedIndex = 223,
  kX86InstIdVpsrldq_ExtendedIndex = 218,
  kX86InstIdVpsrlq_ExtendedIndex = 224,
  kX86InstIdVpsrlvd_ExtendedIndex = 140,
  kX86InstIdVpsrlvq_ExtendedIndex = 158,
  kX86InstIdVpsrlw_ExtendedIndex = 225,
  kX86InstIdVpsubb_ExtendedIndex = 140,
  kX86InstIdVpsubd_ExtendedIndex = 140,
  kX86InstIdVpsubq_ExtendedIndex = 140,
  kX86InstIdVpsubsb_ExtendedIndex = 140,
  kX86InstIdVpsubsw_ExtendedIndex = 140,
  kX86InstIdVpsubusb_ExtendedIndex = 140,
  kX86InstIdVpsubusw_ExtendedIndex = 140,
  kX86InstIdVpsubw_ExtendedIndex = 140,
  kX86InstIdVptest_ExtendedIndex = 150,
  kX86InstIdVpunpckhbw_ExtendedIndex = 140,
  kX86InstIdVpunpckhdq_ExtendedIndex = 140,
  kX86InstIdVpunpckhqdq_ExtendedIndex = 140,
  kX86InstIdVpunpckhwd_ExtendedIndex = 140,
  kX86InstIdVpunpcklbw_ExtendedIndex = 140,
  kX86InstIdVpunpckldq_ExtendedIndex = 140,
  kX86InstIdVpunpcklqdq_ExtendedIndex = 140,
  kX86InstIdVpunpcklwd_ExtendedIndex = 140,
  kX86InstIdVpxor_ExtendedIndex = 140,
  kX86InstIdVrcpps_ExtendedIndex = 150,
  kX86InstIdVrcpss_ExtendedIndex = 141,
  kX86InstIdVroundpd_ExtendedIndex = 216,
  kX86InstIdVroundps_ExtendedIndex = 216,
  kX86InstIdVroundsd_ExtendedIndex = 148,
  kX86InstIdVroundss_ExtendedIndex = 148,
  kX86InstIdVrsqrtps_ExtendedIndex = 150,
  kX86InstIdVrsqrtss_ExtendedIndex = 141,
  kX86InstIdVshufpd_ExtendedIndex = 144,
  kX86InstIdVshufps_ExtendedIndex = 144,
  kX86InstIdVsqrtpd_ExtendedIndex = 150,
  kX86InstIdVsqrtps_ExtendedIndex = 150,
  kX86InstIdVsqrtsd_ExtendedIndex = 141,
  kX86InstIdVsqrtss_ExtendedIndex = 141,
  kX86InstIdVstmxcsr_ExtendedIndex = 169,
  kX86InstIdVsubpd_ExtendedIndex = 140,
  kX86InstIdVsubps_ExtendedIndex = 140,
  kX86InstIdVsubsd_ExtendedIndex = 141,
  kX86InstIdVsubss_ExtendedIndex = 141,
  kX86InstIdVtestpd_ExtendedIndex = 226,
  kX86InstIdVtestps_ExtendedIndex = 226,
  kX86InstIdVucomisd_ExtendedIndex = 142,
  kX86InstIdVucomiss_ExtendedIndex = 142,
  kX86InstIdVunpckhpd_ExtendedIndex = 140,
  kX86InstIdVunpckhps_ExtendedIndex = 140,
  kX86InstIdVunpcklpd_ExtendedIndex = 140,
  kX86InstIdVunpcklps_ExtendedIndex = 140,
  kX86InstIdVxorpd_ExtendedIndex = 140,
  kX86InstIdVxorps_ExtendedIndex = 140,
  kX86InstIdVzeroall_ExtendedIndex = 227,
  kX86InstIdVzeroupper_ExtendedIndex = 227,
  kX86InstIdWrfsbase_ExtendedIndex = 228,
  kX86InstIdWrgsbase_ExtendedIndex = 228,
  kX86InstIdXadd_ExtendedIndex = 229,
  kX86InstIdXchg_ExtendedIndex = 230,
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
  INST(kX86InstIdCmpsd            , "cmpsd"            , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_F20F00(C2,U)  , U               ),
  INST(kX86InstIdCmpss            , "cmpss"            , G(ExtRmi)        , F(None)                , 0 , O(Xmm)              , O(XmmMem)           , O(Imm)              , U                   , O_F30F00(C2,U)  , U               ),
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
  INST(kX86InstIdMovsd            , "movsd"            , G(ExtMov)        , F(Move)|F(ZeroIfMem)   , 8 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_F20F00(10,U)  , O_F20F00(11,U)  ),
  INST(kX86InstIdMovshdup         , "movshdup"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(16,U)  , U               ),
  INST(kX86InstIdMovsldup         , "movsldup"         , G(ExtRm)         , F(Move)                , 16, O(Xmm)              , O(XmmMem)           , U                   , U                   , O_F30F00(12,U)  , U               ),
  INST(kX86InstIdMovss            , "movss"            , G(ExtMov)        , F(Move)|F(ZeroIfMem)   , 4 , O(XmmMem)           , O(XmmMem)           , U                   , U                   , O_F30F00(10,U)  , O_F30F00(11,U)  ),
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
static ASMJIT_INLINE int X86InstUtil_cmpName(const char* a, const char* b, size_t len) {
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
      if (X86InstUtil_cmpName(base->getName(), name, len) == 0)
        return static_cast<uint32_t>((size_t)(base - _x86InstInfo));
      base++;
    }
  }
  else {
    for (size_t lim = (size_t)(end - base); lim != 0; lim >>= 1) {
      const X86InstInfo* cur = base + (lim >> 1);
      int result = X86InstUtil_cmpName(cur->getName(), name, len);

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
