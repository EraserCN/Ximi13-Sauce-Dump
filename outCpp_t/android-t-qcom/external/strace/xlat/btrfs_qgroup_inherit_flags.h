/* Generated by ./xlat/gen.sh from ./xlat/btrfs_qgroup_inherit_flags.in; do not edit. */

#include "gcc_compat.h"
#include "static_assert.h"


#ifndef XLAT_MACROS_ONLY

# ifdef IN_MPERS

extern const struct xlat btrfs_qgroup_inherit_flags[];

# else

#  if !(defined HAVE_M32_MPERS || defined HAVE_MX32_MPERS)
static
#  endif
const struct xlat btrfs_qgroup_inherit_flags[] = {
#if defined(BTRFS_QGROUP_INHERIT_SET_LIMITS) || (defined(HAVE_DECL_BTRFS_QGROUP_INHERIT_SET_LIMITS) && HAVE_DECL_BTRFS_QGROUP_INHERIT_SET_LIMITS)
  XLAT_TYPE(uint64_t, BTRFS_QGROUP_INHERIT_SET_LIMITS),
#endif
 XLAT_END
};

# endif /* !IN_MPERS */

#endif /* !XLAT_MACROS_ONLY */