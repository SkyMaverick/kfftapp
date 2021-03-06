#include "kfa_defs.h"

static void
display_flags(kfft_info_t* info) {
    fprintf(stdout, "%s - %s\n", "Enable trace messages",
            (info->flags & KFFT_INFO_TRACE) ? "YES" : "NO");
    fprintf(stdout, "%s - %s\n", "Enable use SIMD instructions",
            (info->flags & KFFT_INFO_USE_SIMD) ? "YES" : "NO");
    fprintf(stdout, "%s - %s\n", "Enable use alloca() function",
            (info->flags & KFFT_INFO_USE_ALLOCA) ? "YES" : "NO");
    fprintf(stdout, "%s - %s\n", "Enable use system math functions",
            (info->flags & KFFT_INFO_USE_SYSMATH) ? "YES" : "NO");
    fprintf(stdout, "%s - %s\n", "Enable use OpenMP functions",
            (info->flags & KFFT_INFO_USE_OPENMP) ? "YES" : "NO");
    fprintf(stdout, "%s - %s\n", "Enable use Rader algoritm",
            (info->flags & KFFT_INFO_RADER_ALGO) ? "YES" : "NO");
    fprintf(stdout, "%s - %s\n", "Enable lesser memory mode",
            (info->flags & KFFT_INFO_MEMLESS_MODE) ? "YES" : "NO");
    fprintf(stdout, "%s - %s\n", "Enable half scalar mode",
            (info->flags & KFFT_INFO_HALF_SCALAR) ? "YES" : "NO");
}

static void
display_exts(state_t* st) {
    fprintf(stdout, "\n%s:\n", "Build with KFFT extensions");
#if defined(KFFT_2D_ENABLE)
    KCB_TYPE(eval2_cpx) t1 = KFFT_CALLBACK(st, eval2_cpx);
    fprintf(stdout, "%s (%s) - %s\n", "Enable 2-dims", "libkfft support",
            (t1 == NULL) ? "NO" : "YES");
#else
    fprintf(stdout, "%s - %s\n", "Enable 2-dims", "NO");
#endif /* KFFT_2D_ENABLE */
#if defined(KFFT_SPARSE_ENABLE)
    KCB_TYPE(eval_sparse_cpx) t2 = KFFT_CALLBACK(st, eval_sparse_cpx);
    fprintf(stdout, "%s (%s) - %s\n", "Enable sparse", "libkfft support",
            (t2 == NULL) ? "NO" : "YES");
#else
    fprintf(stdout, "%s - %s\n", "Enable sparse", "NO");
#endif /* KFFT_SPARSE_ENABLE */
}

static void
__display_exts(kfft_simd_t st) {
    if ((st.arch == HW_ARCH_X86) || (st.arch == HW_ARCH_X64)) {
        //  Misc.
        // clang-format off
        if (kfft_simd_check(st, HW_MMX        )) fprintf (stdout, "%s ", "MMX");
        if (kfft_simd_check(st, HW_x64        )) fprintf (stdout, "%s ", "x64");
        if (kfft_simd_check(st, HW_ABM        )) fprintf (stdout, "%s ", "ABM");
        if (kfft_simd_check(st, HW_RDRAND     )) fprintf (stdout, "%s ", "RDRAND");
        if (kfft_simd_check(st, HW_BMI1       )) fprintf (stdout, "%s ", "BMI1");
        if (kfft_simd_check(st, HW_BMI2       )) fprintf (stdout, "%s ", "BMI2");
        if (kfft_simd_check(st, HW_ADX        )) fprintf (stdout, "%s ", "ADX");
        if (kfft_simd_check(st, HW_PREFETCHWT1)) fprintf (stdout, "%s ", "PREFETCHWT1");
        if (kfft_simd_check(st, HW_MPX        )) fprintf (stdout, "%s ", "MPX");
        if (kfft_simd_check(st, HW_SSE        )) fprintf (stdout, "%s ", "SSE");
        if (kfft_simd_check(st, HW_SSE2       )) fprintf (stdout, "%s ", "SSE2");
        if (kfft_simd_check(st, HW_SSE3       )) fprintf (stdout, "%s ", "SSE3");
        if (kfft_simd_check(st, HW_SSSE3      )) fprintf (stdout, "%s ", "SSSE3");
        if (kfft_simd_check(st, HW_SSE41      )) fprintf (stdout, "%s ", "SSE41");
        if (kfft_simd_check(st, HW_SSE42      )) fprintf (stdout, "%s ", "SSE42");
        if (kfft_simd_check(st, HW_SSE4a      )) fprintf (stdout, "%s ", "SSE4a");
        if (kfft_simd_check(st, HW_AES        )) fprintf (stdout, "%s ", "AES");
        if (kfft_simd_check(st, HW_SHA        )) fprintf (stdout, "%s ", "SHA");
        if (kfft_simd_check(st, HW_AVX        )) fprintf (stdout, "%s ", "AVX");
        if (kfft_simd_check(st, HW_XOP        )) fprintf (stdout, "%s ", "XOP");
        if (kfft_simd_check(st, HW_FMA3       )) fprintf (stdout, "%s ", "FMA3");
        if (kfft_simd_check(st, HW_FMA4       )) fprintf (stdout, "%s ", "FMA4");
        if (kfft_simd_check(st, HW_AVX2       )) fprintf (stdout, "%s ", "AVX2");
        if (kfft_simd_check(st, HW_AVX512_F   )) fprintf (stdout, "%s ", "AVX512_F");
        if (kfft_simd_check(st, HW_AVX512_PF  )) fprintf (stdout, "%s ", "AVX512_PF");
        if (kfft_simd_check(st, HW_AVX512_ER  )) fprintf (stdout, "%s ", "AVX512_ER");
        if (kfft_simd_check(st, HW_AVX512_CD  )) fprintf (stdout, "%s ", "AVX512_CD");
        if (kfft_simd_check(st, HW_AVX512_VL  )) fprintf (stdout, "%s ", "AVX512_VL");
        if (kfft_simd_check(st, HW_AVX512_BW  )) fprintf (stdout, "%s ", "AVX512_BW");
        if (kfft_simd_check(st, HW_AVX512_DQ  )) fprintf (stdout, "%s ", "AVX512_DQ");
        if (kfft_simd_check(st, HW_AVX512_IFMA)) fprintf (stdout, "%s ", "AVX512_IFMA");
        if (kfft_simd_check(st, HW_AVX512_VBMI)) fprintf (stdout, "%s ", "AVX512_VBMI");
        // clang-format on
    }
    // TODO
    fprintf(stdout, "\n");
}

#if defined(KFFT_USE_SIMD)
static void
display_simd(state_t* st) {

    KCB_TYPE(simd_analize) cb_analize = KFFT_CALLBACK(st, simd_analize);
    KCB_TYPE(simd_info) cb_info = KFFT_CALLBACK(st, simd_info);

    if (cb_analize && cb_info) {
        kfft_simd_t s_info = cb_info();
        fprintf(stdout, "\n%s:\n", "Build with CPU extensions (libkfft)");
        __display_exts(s_info);

        s_info = cb_analize();
        fprintf(stdout, "%s:\n", "Found CPU extensions");
        __display_exts(s_info);

    } else
        fprintf(stdout, "%s\n", "Don't found kfft_simd_analize() callback");
}
#endif /* KFFT_USE_SIMD */

static void
display_info(state_t* st) {
    kfft_info_t info;
    KRNL_FUNCS(st).cb_info(&info);

    fprintf(stdout, "%s version: %d.%d.%d\n", APP_NAME, VER_MAJOR, VER_MINOR, VER_PATCH);
    fprintf(stdout, "Uses libkfft version : %d.%d.%d\n\n", info.vmajor, info.vminor, info.vpatch);

    display_flags(&info);
    display_exts(st);
#if defined(KFFT_USE_SIMD)
    display_simd(st);
#endif /* KFFT_USE_SIMD */
}

static void
display_help(void) {
    fprintf(stdout, "%s", help_msg);
}
