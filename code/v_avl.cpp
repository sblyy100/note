#include "v_avl.h"

#ifndef VOS_OK
#define VOS_OK (0)
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*lint -save -e818*/

/* OSE-684 y00165807 */
unsigned int VOS_V_AVLInit(const char *pscKey)
{
    (void)pscKey;
    return VOS_OK;
}


unsigned int VOS_V_AVLFini()
{
    return VOS_OK;
}
