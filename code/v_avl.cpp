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
void AVL_Rotate_Right(AVL_NODE **ppstSubTree)
{
    /* rotate ppstSubTree of AVL tree right                                   */
    AVL_NODE *pstLeftSon;

    pstLeftSon = (*ppstSubTree)->pstLeft;

    (*ppstSubTree)->pstLeft = pstLeftSon->pstRight;
    if (NULL != (*ppstSubTree)->pstLeft)
    {
        (*ppstSubTree)->pstLeft->pstParent = (*ppstSubTree);
    }

    (*ppstSubTree)->sLHeight = pstLeftSon->sRHeight;
    pstLeftSon->pstParent    = (*ppstSubTree)->pstParent;
    pstLeftSon->pstRight     = *ppstSubTree;
    pstLeftSon->pstRight->pstParent = pstLeftSon;
    pstLeftSon->sRHeight     = (1 + VOS_V2_AVL_MAX((*ppstSubTree)->sRHeight,
                                                   (*ppstSubTree)->sLHeight));

    *ppstSubTree = pstLeftSon;

    return;
} /* AVL_Rotate_Right */
