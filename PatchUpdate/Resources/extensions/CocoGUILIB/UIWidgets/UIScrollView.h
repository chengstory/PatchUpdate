/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __UISCROLLVIEW_H__
#define __UISCROLLVIEW_H__

#include "UIPanel.h"

NS_CC_EXT_BEGIN

enum SCROLLVIEW_DIR
{
    SCROLLVIEW_DIR_NONE,
    SCROLLVIEW_DIR_VERTICAL,
    SCROLLVIEW_DIR_HORIZONTAL
};

enum SCROLLVIEW_MOVE_DIR
{
    SCROLLVIEW_MOVE_DIR_NONE,
    SCROLLVIEW_MOVE_DIR_UP,
    SCROLLVIEW_MOVE_DIR_DOWN,
    SCROLLVIEW_MOVE_DIR_LEFT,
    SCROLLVIEW_MOVE_DIR_RIGHT,
};

enum SCROLLVIEW_MOVE_MODE
{
    SCROLLVIEW_MOVE_MODE_NONE,
    SCROLLVIEW_MOVE_MODE_NORMAL,
    SCROLLVIEW_MOVE_MODE_ACTION
};

enum SCROLLVIEW_BERTH_ORI
{
    SCROLLVIEW_BERTH_ORI_NONE,
    SCROLLVIEW_BERTH_ORI_TOP,
    SCROLLVIEW_BERTH_ORI_BOTTOM,
    SCROLLVIEW_BERTH_ORI_VERTICAL_CENTER,
    SCROLLVIEW_BERTH_ORI_LEFT,
    SCROLLVIEW_BERTH_ORI_RIGHT,
    SCROLLVIEW_BERTH_ORI_HORIZONTAL_CENTER
};

typedef void (CCObject::*SEL_ScrollToTopEvent)(CCObject*);
typedef void (CCObject::*SEL_ScrollToBottomEvent)(CCObject*);
typedef void (CCObject::*SEL_ScrollToLeftEvent)(CCObject*);
typedef void (CCObject::*SEL_ScrollToRightEvent)(CCObject*);
#define coco_ScrollToTopSelector(_SELECTOR) (cocos2d::extension::SEL_ScrollToTopEvent)(&_SELECTOR)
#define coco_ScrollToBottomSelector(_SELECTOR) (cocos2d::extension::SEL_ScrollToBottomEvent)(&_SELECTOR)
#define coco_ScrollToLeftSelector(_SELECTOR) (cocos2d::extension::SEL_ScrollToLeftEvent)(&_SELECTOR)
#define coco_ScrollToRightSelector(_SELECTOR) (cocos2d::extension::SEL_ScrollToRightEvent)(&_SELECTOR)

typedef void (CCObject::*SEL_BerthToTopEvent)(CCObject*);
typedef void (CCObject::*SEL_BerthToBottomEvent)(CCObject*);
typedef void (CCObject::*SEL_BerthToVerticalCenterEvent)(CCObject*);
typedef void (CCObject::*SEL_BerthToLeftEvent)(CCObject*);
typedef void (CCObject::*SEL_BerthToRightEvent)(CCObject*);
typedef void (CCObject::*SEL_BerthToHorizontalCenterEvent)(CCObject*);
#define coco_BerthToTopSelector(_SELECTOR) (cocos2d::extension::SEL_BerthToTopEvent)(&_SELECTOR)
#define coco_BerthToBottomSelector(_SELECTOR) (cocos2d::extension::SEL_BerthToBottomEvent)(&_SELECTOR)
#define coco_BerthToVerticalCenterSelector(_SELECTOR) (cocos2d::extension::SEL_BerthToVerticalCenterEvent)(&_SELECTOR)
#define coco_BerthToLeftSelector(_SELECTOR) (cocos2d::extension::SEL_BerthToLeftEvent)(&_SELECTOR)
#define coco_BerthToRightSelector(_SELECTOR) (cocos2d::extension::SEL_BerthToRightEvent)(&_SELECTOR)
#define coco_HorizontalCenterSelector(_SELECTOR) (cocos2d::extension::SEL_BerthToHorizontalCenterEvent)(&_SELECTOR)

class UIScrollView : public UIPanel
{
public:
    UIScrollView();
    virtual ~UIScrollView();
    static UIScrollView* create();
    virtual bool addChild(UIWidget* widget);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    void scrollToBottom();
    void scrollToTop();
    virtual void setSize(const CCSize &size);
    
    
    
    void addScrollToTopEvent(CCObject* target, SEL_ScrollToTopEvent selector);
    void addScrollToBottomEvent(CCObject* target, SEL_ScrollToBottomEvent selector);
    void addScrollToLeftEvent(CCObject* target, SEL_ScrollToLeftEvent selector);
    void addScrollToRightEvent(CCObject* target, SEL_ScrollToRightEvent selector);
    

    
    void addBerthToTopEvent(CCObject* target, SEL_BerthToTopEvent selector);
    void addBerthToBottomEvent(CCObject* target, SEL_BerthToBottomEvent selector);
    void addBerthToVerticalCenterEvent(CCObject* target, SEL_BerthToVerticalCenterEvent selector);
    void addBerthToLeftEvent(CCObject* target, SEL_BerthToLeftEvent selector);
    void addBerthToRightEvent(CCObject* target, SEL_BerthToRightEvent selector);
    void addBerthToHorizontalCenterEvent(CCObject* target, SEL_BerthToHorizontalCenterEvent selector);
    
    void stopAction();
    virtual void onTouchBegan(CCPoint &touchPoint);
    virtual void onTouchMoved(CCPoint &touchPoint);
    virtual void onTouchEnded(CCPoint &touchPoint);
    virtual void onTouchCancelled(CCPoint &touchPoint);
    virtual void onTouchLongClicked(CCPoint &touchPoint);
    void setDirection(SCROLLVIEW_DIR dir);
    SCROLLVIEW_DIR getDirection();
    void setMoveMode(SCROLLVIEW_MOVE_MODE mode);
    SCROLLVIEW_MOVE_MODE getMoveMode();
    void setBerthOrientation(SCROLLVIEW_BERTH_ORI mode);
    SCROLLVIEW_BERTH_ORI getBerthOrientation();
protected:
    virtual void removeChildMoveToTrash(UIWidget* child);
    virtual void removeChildReferenceOnly(UIWidget* child);
    virtual bool init();
    virtual void initProperty();
    virtual void resetProperty();
    void resortChildren();
    void moveChildren(float offset);
    void autoScrollChildren(float dt);
    void startAutoScrollChildren(float v);
    void stopAutoScrollChildren();
    float getCurAutoScrollDistance(float time);
    void resetPositionWithAction();
    virtual UIWidget* getCheckPositionChild();
    float calculateOffsetWithDragForce(float moveOffset);
    void handleScrollActionEvent();
    void berthChildren(SCROLLVIEW_DIR direction);
    virtual bool scrollChildren(float touchOffset);
    virtual void drag(float offset);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();
    void handlePressLogic(CCPoint &touchPoint);
    void handleMoveLogic(CCPoint &touchPoint);
    void handleReleaseLogic(CCPoint &touchPoint);
    virtual void update(float dt);
    void recordSlidTime(float dt);
    virtual void checkChildInfo(int handleState,UIWidget* sender,CCPoint &touchPoint);
    void scrollToTopEvent();
    void scrollToBottomEvent();
    void scrollToLeftEvent();
    void scrollToRightEvent();
    void berthToTopEvent();
    void berthToBottomEvent();
    void berthToVerticalCenterEvent();
    void berthToLeftEvent();
    void berthToRightEvent();
    void berthToHorizontalCenterEvent();
    void setMoveDirection(SCROLLVIEW_MOVE_DIR dir);
    SCROLLVIEW_MOVE_DIR getMoveDirection();
protected:
    SCROLLVIEW_DIR m_eDirection;
    SCROLLVIEW_MOVE_DIR m_eMoveDirection;
//    int m_nDirection;
    float m_fTouchStartLocation;
    float m_fTouchEndLocation;
    float m_fTouchMoveStartLocation;
    float m_fTopBoundary;//test
    float m_fBottomBoundary;//test
    float m_fLeftBoundary;
    float m_fRightBoundary;
    UIWidget* m_pTopChild;
    UIWidget* m_pBottomChild;
    UIWidget* m_pLeftChild;
    UIWidget* m_pRightChild;
    
    float m_fDisBoundaryToChild_0;
    float m_fDisBetweenChild;
    float m_fDragForce;
    
    int m_nHandleState;//0 normal, 1 top boundary, 2 bottom boundary
    int m_nMoveDirection;//0 pull down, 1 push up
    SCROLLVIEW_MOVE_MODE m_eMoveMode;
    SCROLLVIEW_BERTH_ORI m_eBerthOrientation;
    bool isRunningAction;
    
    bool m_bTopEnd;
    bool m_bBottomEnd;
    bool m_bLeftEnd;
    bool m_bRightEnd;
    
    bool m_bBerthToTop;
    bool m_bBerthToBottom;
    bool m_bBerthToLeft;
    bool m_bBerthToRight;
    bool m_bBerthToVerticalCenter;
    bool m_bBerthToHorizontalCenter;
    
    bool m_bAutoScroll;
    
    float m_fAutoScrollOriginalSpeed;
    float m_fAutoScrollAcceleration;
    
    bool m_bBePressed;
    float m_fSlidTime;
    CCPoint moveChildPoint;
    float m_fChildrenSizeHeight;
    float m_fChildrenSizeWidth;
    float m_fChildFocusCancelOffset;
    
    CCObject* m_pScrollToTopListener;
    SEL_ScrollToTopEvent m_pfnScrollToTopSelector;
    CCObject* m_pScrollToBottomListener;
    SEL_ScrollToBottomEvent m_pfnScrollToBottomSelector;
    CCObject* m_pScrollToLeftListener;
    SEL_ScrollToLeftEvent m_pfnScrollToLeftSelector;
    CCObject* m_pScrollToRightListener;
    SEL_ScrollToRightEvent m_pfnScrollToRightSelector;
    
    CCObject* m_pBerthToTopListener;
    SEL_BerthToTopEvent m_pfnBerthToTopSelector;
    CCObject* m_pBerthToBottomListener;
    SEL_BerthToBottomEvent m_pfnBerthToBottomSelector;
    CCObject* m_pBerthToVerticalCenterListener;
    SEL_BerthToVerticalCenterEvent m_pfnBerthToVerticalCenterSelector;
    CCObject* m_pBerthToLeftListener;
    SEL_BerthToLeftEvent m_pfnBerthToLeftSelector;
    CCObject* m_pBerthToRightListener;
    SEL_BerthToRightEvent m_pfnBerthToRightSelector;
    CCObject* m_pBerthToHorizontalCenterListener;
    SEL_BerthToHorizontalCenterEvent m_pfnBerthToHorizontalCenterSelector;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIScrollView__) */