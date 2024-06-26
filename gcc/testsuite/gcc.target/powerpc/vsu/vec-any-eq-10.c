/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-require-effective-target powerpc_vsx_ok } */
/* { dg-options "-mdejagnu-cpu=power9 -mvsx" } */

#include <altivec.h>

int
test_any_equal (vector unsigned long long *arg1_p,
		vector unsigned long long *arg2_p)
{
  vector unsigned long long arg_1 = *arg1_p;
  vector unsigned long long arg_2 = *arg2_p;

  return vec_any_eq (arg_1, arg_2);
}

/* { dg-final { scan-assembler "vcmpequd." } } */
/* { dg-final { scan-assembler "rlwinm r?\[0-9\]+,r?\[0-9\]+,27,1" } } */
