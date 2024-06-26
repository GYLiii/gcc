/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64 -O3" } */

#include "riscv_vector.h"

size_t __attribute__ ((noinline))
normalize_vl (size_t vl)
{
  if (vl % 4 == 0)
    return vl;

  return ((vl / 4) + 1) * 4;
}

vfloat32m1_t
test_float_point_dynamic_frm (vfloat32m1_t op1, vfloat32m1_t op2, size_t vl)
{
  vfloat32m1_t result = op1;

  result = __riscv_vfadd_vv_f32m1_rm (result, op2, 4, vl);
  result = __riscv_vfadd_vv_f32m1_rm (op1, result, 2, vl);

  vl = normalize_vl (vl);

  return vl > 128 ? result : op2;
}

/* { dg-final { scan-assembler-times {vfadd\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[fav]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {frrm\s+[axs][0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {fsrmi\s+[01234]} 2 } } */
/* { dg-final { scan-assembler-times {fsrm\s+[axs][0-9]+} 1 } } */
/* { dg-final { scan-assembler-not {fsrmi\s+[axs][0-9]+,\s*[01234]} } } */
