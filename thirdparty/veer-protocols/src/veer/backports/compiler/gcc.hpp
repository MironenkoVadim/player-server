#ifndef VEER_BACKPORTS_COMPILER_GCC_HPP_
#define VEER_BACKPORTS_COMPILER_GCC_HPP_

#pragma once

#ifdef __GNUC__
#define GCC_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )
#if GCC_VERSION <= 40702

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif

// NOLINTNEXTLINE
#define override

// NOLINTNEXTLINE
#define constexpr const

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif // if GCC_VERSION <= 40702
#endif // ifdef __GNUC__

#endif // ifndef VEER_BACKPORTS_COMPILER_GCC_HPP_
