/* Generated by ./xlat/gen.sh from ./xlat/epollctls.in; do not edit. */

#include "gcc_compat.h"
#include "static_assert.h"

#if defined(EPOLL_CTL_ADD) || (defined(HAVE_DECL_EPOLL_CTL_ADD) && HAVE_DECL_EPOLL_CTL_ADD)
DIAG_PUSH_IGNORE_TAUTOLOGICAL_COMPARE
static_assert((EPOLL_CTL_ADD) == (1), "EPOLL_CTL_ADD != 1");
DIAG_POP_IGNORE_TAUTOLOGICAL_COMPARE
#else
# define EPOLL_CTL_ADD 1
#endif
#if defined(EPOLL_CTL_DEL) || (defined(HAVE_DECL_EPOLL_CTL_DEL) && HAVE_DECL_EPOLL_CTL_DEL)
DIAG_PUSH_IGNORE_TAUTOLOGICAL_COMPARE
static_assert((EPOLL_CTL_DEL) == (2), "EPOLL_CTL_DEL != 2");
DIAG_POP_IGNORE_TAUTOLOGICAL_COMPARE
#else
# define EPOLL_CTL_DEL 2
#endif
#if defined(EPOLL_CTL_MOD) || (defined(HAVE_DECL_EPOLL_CTL_MOD) && HAVE_DECL_EPOLL_CTL_MOD)
DIAG_PUSH_IGNORE_TAUTOLOGICAL_COMPARE
static_assert((EPOLL_CTL_MOD) == (3), "EPOLL_CTL_MOD != 3");
DIAG_POP_IGNORE_TAUTOLOGICAL_COMPARE
#else
# define EPOLL_CTL_MOD 3
#endif

#ifndef XLAT_MACROS_ONLY

# ifdef IN_MPERS

#  error static const struct xlat epollctls in mpers mode

# else

static
const struct xlat epollctls[] = {
 XLAT(EPOLL_CTL_ADD),
 XLAT(EPOLL_CTL_DEL),
 XLAT(EPOLL_CTL_MOD),
 XLAT_END
};

# endif /* !IN_MPERS */

#endif /* !XLAT_MACROS_ONLY */