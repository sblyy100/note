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
void AVL_Rotate_Left(AVL_NODE **ppstSubTree)
{
    /* rotate a ppstSubTree of the AVL tree left                              */
    AVL_NODE *pstRightSon;

    pstRightSon = (*ppstSubTree)->pstRight;

    (*ppstSubTree)->pstRight = pstRightSon->pstLeft;
    if (NULL != (*ppstSubTree)->pstRight)
    {
        (*ppstSubTree)->pstRight->pstParent = (*ppstSubTree);
    }

    (*ppstSubTree)->sRHeight = pstRightSon->sLHeight;
    pstRightSon->pstParent   = (*ppstSubTree)->pstParent;
    pstRightSon->pstLeft     = *ppstSubTree;
    pstRightSon->pstLeft->pstParent = pstRightSon;
    pstRightSon->sLHeight    = (1 + VOS_V2_AVL_MAX((*ppstSubTree)->sRHeight,
                                                   (*ppstSubTree)->sLHeight));

    *ppstSubTree = pstRightSon;

    return;
} /* AVL_Rotate_Left */
void AVL_Swap_Right_Most(AVL_TREE *pstTree,
                             AVL_NODE *pstSubTree,
                             AVL_NODE *pstNode)
{
    /* swap pstNode with right-most descendent of specified pstSubTree        */
    AVL_NODE *pstSwapNode;
    AVL_NODE *pstSwapParent;
    AVL_NODE *pstSwapLeft;

    //VOS_ASSERT(NULL != pstNode->pstRight);
    //VOS_ASSERT(NULL != pstNode->pstLeft);
    if ((NULL == pstNode->pstRight) || (NULL == pstNode->pstLeft))
    {
        return;
    }
    /* find right-most descendent of pstSubTree                               */
    pstSwapNode = pstSubTree;
    while (NULL != pstSwapNode->pstRight)
    {
        pstSwapNode = pstSwapNode->pstRight;
    }

    //VOS_ASSERT(pstSwapNode->sRHeight == 0);
    //VOS_ASSERT(pstSwapNode->sLHeight <= 1);
    if ((0 != pstSwapNode->sRHeight) || (pstSwapNode->sLHeight > 1))
    {
        return;
    }

    /* save parent and left-son of right-most descendent                      */
    pstSwapParent = pstSwapNode->pstParent;
    pstSwapLeft = pstSwapNode->pstLeft;

    /* move swap pstNode to its new position                                  */
    pstSwapNode->pstParent = pstNode->pstParent;
    pstSwapNode->pstRight  = pstNode->pstRight;
    pstSwapNode->pstLeft   = pstNode->pstLeft;
    pstSwapNode->sRHeight  = pstNode->sRHeight;
    pstSwapNode->sLHeight  = pstNode->sLHeight;
    pstSwapNode->pstRight->pstParent = pstSwapNode;
    pstSwapNode->pstLeft->pstParent  = pstSwapNode;
    if (NULL == pstNode->pstParent)
    {
        /* pstNode is at root of pstTree                                      */
        pstTree->pstRoot = pstSwapNode;
    }
    else if (pstNode->pstParent->pstRight == pstNode)
    {
        /* pstNode is right-son of parent                                     */
        pstSwapNode->pstParent->pstRight = pstSwapNode;
    }
    else
    {
        /* pstNode is left-son of parent                                      */
        pstSwapNode->pstParent->pstLeft = pstSwapNode;
    }

    /* move pstNode to its new position                                       */
    pstNode->pstParent = pstSwapParent;
    pstNode->pstRight  = NULL;
    pstNode->pstLeft   = pstSwapLeft;
    if (NULL != pstNode->pstLeft)
    {
        pstNode->pstLeft->pstParent = pstNode;
        pstNode->sLHeight = 1;
    }
    else
    {
        pstNode->sLHeight = 0;
    }

    pstNode->sRHeight = 0;
    pstNode->pstParent->pstRight = pstNode;

    return;
} /* AVL_Swap_Right_Most */
