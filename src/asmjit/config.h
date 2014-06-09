// [AsmJit]
// Complete x86/x64 JIT and Remote Assembler for C++.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// [Guard]
#ifndef _ASMJIT_CONFIG_H
#define _ASMJIT_CONFIG_H

// This file can be used to modify built-in features of AsmJit. AsmJit is by
// default compiled only for host processor to enable JIT compilation. Both
// Assembler and Compiler code generators are compiled by default.
// 
// ASMJIT_BUILD_... flags can be defined to build additional backends that can
// be used for remote code generation.
//
// ASMJIT_DISABLE_... flags can be defined to disable standard features. These
// are handy especially when building asmjit statically and some features are
// not needed or unwanted (like Compiler).

// ============================================================================
// [AsmJit - Debugging]
// ============================================================================

// #define ASMJIT_DEBUG              // Define to enable debug-mode.
// #define ASMJIT_RELEASE            // Define to enable release-mode.

// ============================================================================
// [AsmJit - Library]
// ============================================================================

// #define ASMJIT_EMBED              // Asmjit is embedded (implies ASMJIT_STATIC).
// #define ASMJIT_STATIC             // Define to enable static-library build.

// ============================================================================
// [AsmJit - Features]
// ============================================================================

// If none of these is defined AsmJit will select host architecture by default.
// #define ASMJIT_BUILD_X86          // Define to enable x86 instruction set (32-bit).
// #define ASMJIT_BUILD_X64          // Define to enable x64 instruction set (64-bit).
// #define ASMJIT_BUILD_HOST         // Define to enable host instruction set.

// AsmJit features are enabled by default.
// #define ASMJIT_DISABLE_COMPILER   // Disable Compiler.
// #define ASMJIT_DISABLE_LOGGER     // Disable Logger (completely).
// #define ASMJIT_DISABLE_INST_NAMES // Disable Instruction names (and API).

// [Guard]
#endif // _ASMJIT_CONFIG_H
