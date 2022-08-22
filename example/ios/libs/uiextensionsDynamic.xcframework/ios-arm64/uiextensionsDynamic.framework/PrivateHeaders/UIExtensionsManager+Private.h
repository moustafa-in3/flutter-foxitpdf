/**
 * Copyright (C) 2003-2021, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK for iOS to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 * Review legal.txt for additional license and legal information.
 */

#ifndef UIExtensionsManager_Private_h
#define UIExtensionsManager_Private_h

#import "TbBaseBar.h"
#import "MoreView.h"
#import "MenuItem.h"
#import "MenuControl.h"
#import "UIExtensionsManager.h"
#import "FSUndo.h"
#import "FSAnnotExtent.h"
#import "Preference.h"
#import "SettingPreference.h"
#import "GlableInstance.h"
#import "ThumbnailModule+Private.h"
#import "StampIconController.h"
#import "FSNavigationController.h"
#import "UIExtensionsConfig+private.h"
#import "FileSelectDestinationViewController.h"
#import "FSViewControllerManager.h"
#import "FSToolbarManager.h"
#import "FSMenuViewManager+Private.h"
#import "FSPropertyMainView.h"
#import "SpeechModule+Private.h"
#import "FSPDFViewCtrlContainerView.h"
#import "FillSignModule.h"
#import "FSCropManager.h"
#import "FSAutoFlipModule.h"
#import "FSViewSettingManager.h"
#import "FSFullScreenTopbar.h"
#import "FSFullScreenBottombar.h"
#import "FSFullScreenToolbarMgr.h"

/** @brief Module base. */
@protocol IReadToolSettingsModule <IModule>
@optional
/** @brief Get the module name. */
@property (nonatomic, assign) FSAnnotType annotType;
- (void)didClickedReadToolItem:(FSReadToolbarItem *_Nullable)readToolbarItem;
@end

/** @brief Module base. */
@protocol IMenuEventToolHandler <IToolHandler>
@optional
- (void)showMenu;
@end

NS_ASSUME_NONNULL_BEGIN

/** @brief The state change event listener. */
@protocol IStateChangeListener <NSObject>
@required
/**
 * @brief Triggered when state changed.
 *
 * @param[in] state     New state.
 */
- (void)onStateChanged:(FSUIManagerState)state;

@optional
/**
 * @brief Triggered when state changed.
 *
 * @param[in] state     New state.
 *
 * @param[in] lastState     Last state.
 */
- (void)onStateChanged:(FSUIManagerState)state lastState:(FSUIManagerState)lastState;
@end

/** @brief A listener for annotation property bar. */
@protocol IAnnotPropertyListener <NSObject>
@optional
- (void)onToolSettingsChanged:(FSReadToolSettings *)toolSettings;
@end

/** @brief The undo/redo listener. */
@protocol IFSUndoEventListener <NSObject>
@optional
/** @brief Triggered after the state of undo or redo changed. */
- (void)onUndoChanged;
- (void)onWillUndo;
- (void)onDidUndo;
- (void)onWillRedo;
- (void)onDidRedo;
@end

/** @brief The uiwindow frame changed listener. */
@protocol IWindowFrameChangedListener <NSObject>
@optional
- (void)onWindowFrameChanged:(CGRect)newFrame horizontalSizeClassChanged:(BOOL)changed;
@end

/** @brief The undo/redo handler,it should handle the operations about undo/redo. */
@protocol FSUndo <NSObject>
/** @brief Check whether can undo or not. */
- (BOOL)canUndo;
/** @brief Check whether can redo or not. */
- (BOOL)canRedo;
/** @brief Undo the previous operation. */
- (void)undo;
/** @brief Redo the previous operation. */
- (void)redo;
/** @brief Clear all the recorded undo/redo operations. */
- (void)clearUndoRedo;
@end

/** @brief A listener for property view. */
@protocol IPropertyViewEventListener <NSObject>
@optional
- (void)onPropertyViewDidShow;
- (void)onPropertyViewDidDismiss;
@end

@class MenuControl;
@class MenuControlDelegate;
@class ExAnnotIconProviderCallback;
@class ExActionHandler;
@class PasswordModule;
@class PanZoomView;
@class _FSPDFViewCtrlContainerView;
@protocol FSPageOrganizerDelegate;

/** @brief Private implementation for extension manager, these properites and methods are not supposed to be called. */
@interface UIExtensionsManager () <FSUndo, IDrawEventListener, IGestureEventListener, IScrollViewEventListener, ISearchEventListener, UIPopoverPresentationControllerDelegate, FSSettingBarDelegate, ILayoutEventListener, MenuControlDelegate, FSPropertyMainViewDelegate>

@property (nonatomic, strong) FSPDFViewCtrlContainerView *containerView;
@property (nonatomic, strong) FSToolbarManager *toolbarManager;
@property (nonatomic, strong) FSFullScreenToolbarMgr *fullScreenToolbarMgr;

//@property (nonatomic, assign) BOOL isDocModified;
@property (nonatomic, assign) BOOL isFileEdited;
@property (nonatomic, assign) BOOL isSupportRedaction;
@property (nonatomic, assign) BOOL currentIsFullScreen;

@property (nonatomic, strong) NSMutableArray *stateChangeListeners;
@property (nonatomic, strong) NSMutableArray *annotListeners;
@property (nonatomic, strong) NSMutableArray *toolListeners;
@property (nonatomic, strong) NSMutableArray *searchListeners;
@property (nonatomic, strong) NSMutableArray *toolHandlers;
@property (nonatomic, strong) NSMutableArray *annotHandlers;
@property (nonatomic, strong) NSMutableArray *docModifiedListeners;
@property (nonatomic, strong) NSMutableArray<IWindowFrameChangedListener> *windowFrameListeners;
@property (nonatomic, strong) NSMutableArray<IPropertyViewEventListener> *propertyViewListeners;
@property (nonatomic, assign) int noteIcon;
@property (nonatomic, assign) int attachmentIcon;
@property (nonatomic, assign) int stampIcon;
@property (nonatomic, strong) FSPropertyMainView *propertyMainView;
@property (nonatomic, strong, nullable) FSReadToolSettings *currentToolSettings;
@property (nonatomic, strong) FSTaskServer *taskServer;
@property (nonatomic, strong) MenuControl *menuControl;

@property (nonatomic, strong) ExAnnotIconProviderCallback *iconProvider;
//@property (nonatomic, strong) ExActionHandler *actionHandler;

@property (nonatomic, strong) UIExtensionsConfig *config;
@property (nonatomic, strong) PasswordModule *passwordModule;
@property (nonatomic, strong) SpeechModule *speechModule;
@property (nonatomic, strong) FSAutoFlipModule *autoFlipModule;

@property (nonatomic, assign) BOOL isShowBlankMenu;
@property (nonatomic, assign) CGPoint currentPoint;
@property (nonatomic, assign) int currentPageIndex;

@property (nonatomic, assign) BOOL hiddenPanel;
@property (nonatomic, assign) BOOL hiddenTopToolbar;
@property (nonatomic, assign) BOOL hiddenBottomToolbar;
@property (nonatomic, assign) BOOL hiddenSettingBar;

// in dragging, rotation and zooming, menu or property bar is hidden first and shown later
// these properties record states before animation, don't use them in other conditions
@property (nonatomic) BOOL shouldShowMenu;
@property (nonatomic) BOOL shouldShowPropertyBar;
@property (nonatomic) BOOL isRotating;
@property (nonatomic) BOOL isScrollViewDragging;
@property (nonatomic) BOOL isScrollViewDecelerating;
@property (nonatomic) BOOL isScrollViewZooming;

@property (nonatomic, strong) NSMutableArray<UndoItem *> *undoItems;
@property (nonatomic, strong) NSMutableArray<UndoItem *> *redoItems;
@property (nonatomic, strong) NSMutableArray<IFSUndoEventListener> *undoListeners;

@property (nonatomic, strong) NSMutableArray *rotateListeners;

@property (nonatomic, strong) NSMutableArray<IAnnotPropertyListener> *annotPropertyListeners;

@property (nonatomic, strong) NSMutableArray<IGestureEventListener> *guestureEventListeners;

@property (nonatomic, strong) NSMutableArray<ILinkEventListener> *linkEventListeners;

@property (nonatomic, strong) NSMutableArray<ISignatureEventListener> *signatureEventListeners;

@property (nonatomic, strong, nullable) StampIconController *stampIconController;
//@property (nonatomic, strong) UIPopoverController *popOverController;

@property (nonatomic, strong) NSMutableArray *securityHandlers;
@property (nonatomic, strong) NSMutableArray *modules;

@property (nonatomic, strong) ThumbnailModule *thumbnailModule;
@property (nonatomic, strong) FillSignModule *fillSignModule;
@property (nonatomic, strong) FSPresentedViewControllerAnimator *presentedVCAnimator;

@property (nonatomic, strong) NSMutableArray *fullScreenListeners;
@property (nonatomic, strong) UIButton *backButton;
@property (nonatomic, strong) UIViewController *settingbarPopoverCtr;
@property (nonatomic, strong) UIButton *annotButton;
@property (nonatomic, assign) BOOL enableTopToolbar;
@property (nonatomic, assign) BOOL enableBottomToolbar;
@property (nonatomic, assign) BOOL enableSmallTopToolbar;
@property (nonatomic, assign) BOOL enableSmallBottomToolbar;
@property (nonatomic, assign) BOOL isSuspendAutoFullScreen;
@property (nonatomic, assign) FSUIManagerState currentState;
@property (nonatomic, assign) FSUIManagerState lastManagerStateWhenAnnotTool;
@property (nonatomic, strong, readwrite) MoreMenuView *more;

//@property (nonatomic, strong) UIControl *settingBarMaskView;
//@property (nonatomic, strong) UIView *settingBarContainer;
@property (nonatomic, strong) NSMutableArray *pageNumberListeners;

//pan&zoom
@property (nonatomic, strong, nullable) PanZoomView* panZoomView;

@property (nonatomic, strong) NSArray *bottomToolbarVerticalConstraints;

@property (nonatomic, assign) BOOL isViewSignedDocument;

@property (nonatomic, strong) FSViewControllerManager *viewCtrlManager;

@property (nonatomic, strong) FSCropManager *cropManager;

@property (nonatomic, strong) NSMutableDictionary<NSNumber *, FSReadToolSettings *> *defaultReadToolSettingItems;
@property (nonatomic, strong) FSFullScreenTopbar *smallTopToolbar;
@property (nonatomic, strong) FSFullScreenBottombar *smallBottomToolbar;

@property (nonatomic, assign) UIUserInterfaceSizeClass lastWindowHorizontalSizeClass;

@property (nonatomic, strong) VoidBlock_id moreItemClickedCallback;
@property (nonatomic, assign) BOOL isSaveAsAlertControllerShow;
@property (nonatomic, assign) int panBeginPageIndex;
@property (nonatomic, assign) BOOL isComparisonViewCtrlVisible;


- (NSMutableArray *)didForMenuControlWillShow:(FSMenuControlScene)menuControlScene array:(NSMutableArray *)array;
- (void)setCurrentAnnot:(FSAnnot *_Nullable)anot;
- (FSAnnotType)filterAnnotType:(FSAnnotType)annotType;
- (id<IAnnotHandler>)getAnnotHandlerByAnnot:(FSAnnot *)annot;
- (id<IAnnotHandler>)getDynamicAnnotHandler;

- (void)hideMenu;
- (void)showMenu;
- (void)showMenuIfNeed;

- (void)cancelAutoFullScreen;
- (void)delayAutoFullScreen;
- (void)delayHideTopBottomToolBar;
- (BOOL)canAutoHideTopBottomToolBar;

- (void)onClickBackButton:(UIControl *)button;
- (void)saveAndCloseCurrentDoc:(void (^_Nullable)(BOOL success))completion;

- (void)registerRotateChangedListener:(id<IRotationEventListener>)listener;
- (void)unregisterRotateChangedListener:(id<IRotationEventListener>)listener;

- (void)registerGestureEventListener:(id<IGestureEventListener>)listener;
- (void)unregisterGestureEventListener:(id<IGestureEventListener>)listener;

/** @brief Register annotation property change event listener. */
- (void)registerAnnotPropertyListener:(id<IAnnotPropertyListener>)listener;
/** @brief Unregister annotation property change event listener. */
- (void)unregisterAnnotPropertyListener:(id<IAnnotPropertyListener>)listener;

/** @brief Register a state change event listener. */
- (void)registerStateChangeListener:(id<IStateChangeListener>)listener;
/** @brief Unregister a state change event listener. */
- (void)unregisterStateChangeListener:(id<IStateChangeListener>)listener;

/** @brief Register a window frame change event listener. */
- (void)registerWindowFrameChangedListener:(id<IWindowFrameChangedListener>)listener;
/** @brief Unregister a window frame change event listener. */
- (void)unregisterWindowFrameChangedListener:(id<IWindowFrameChangedListener>)listener;

- (void)registerPropertyViewEvnetListener:(id<IPropertyViewEventListener>)listener;
- (void)unregisterPropertyViewEvnetListener:(id<IPropertyViewEventListener>)listener;

- (void)showPropertyBar;
- (void)hidePropertyBar;

-(FSXFAWidget *)getXFAWidgetAtPoint:(CGPoint)pvPoint pageIndex:(int)pageIndex;

- (BOOL)annotPermissionCanModify:(FSAnnot *)annot;

- (BOOL)annotPermissionCanDelete:(FSAnnot *)annot;

- (BOOL)annotPermissionCanReply:(FSAnnot *)annot;

- (BOOL)allAnnotPermissionAnnot:(nullable FSAnnot *)annot;
#pragma mark - Undo/redo event listeners.
/** @brief Register the undo/redo event listener. */
- (void)registerUndoEventListener:(id<IFSUndoEventListener>)listener;
/** @brief Unregister the undo/redo event listener. */
- (void)unregisterUndoEventListener:(id<IFSUndoEventListener>)listener;

- (void)addUndoItem:(UndoItem *)undoItem;
- (void)removeUndoItem:(UndoItem *)undoItem;
- (void)addUndoItems:(NSMutableArray *)undoItems;
- (void)removeUndoItems;
-(void)removeUndoItems:(NSArray<UndoItem *> *)items;

- (void)setStatusBarHidden:(BOOL)hidden;
- (void)onDigitalSignatureSigned:(BOOL)success;
- (void)showPropertyWithToolSettings:(FSReadToolSettings *)toolSettings devicePos:(DevicePosition*)devicePos;
@end

@interface UIExtensionsManager (Private)
- (void)addPopupWithAnnot:(FSAnnot *)annot;
- (void)deletePopupWithAnnot:(FSAnnot *)annot;
- (void)changeAnnot:(FSAnnot *)annot property:(FSPropertyType)property from:(NSValue *)oldValue to:(NSValue *)newValue;
@end

@interface ExAnnotIconProviderCallback : NSObject <FSIconProviderCallback>
- (NSString *)getProviderID;
- (NSString *)getProviderVersion;
- (BOOL)hasIcon:(FSAnnotType)annotType iconName:(NSString *)iconName;
- (BOOL)canChangeColor:(FSAnnotType)annotType iconName:(NSString *)iconName;
- (FSPDFPage *)getIcon:(FSAnnotType)annotType iconName:(NSString *)iconName color:(unsigned int)color;
- (FSShadingColor *)getShadingColor:(FSAnnotType)annotType iconName:(NSString *)iconName refColor:(unsigned int)refColor shadingIndex:(int)shadingIndex;
- (NSNumber *)getDisplayWidth:(FSAnnotType)annotType iconName:(NSString *)iconName;
- (NSNumber *)getDisplayHeight:(FSAnnotType)annotType iconName:(NSString *)iconName;
@end


@interface JSAlertViewDelegate: NSObject
- (id)initWithType:(int)type;
@property (nonatomic) int type;
@property (nonatomic, readwrite) int retCode;
@end

@interface ExActionHandler : NSObject <FSActionCallback>
@property (nonatomic, weak) FSPDFViewCtrl *pdfViewCtrl;
@property (nonatomic, weak) UIExtensionsManager *extensionsManager;
@property (nonatomic, strong, nullable) JSAlertViewDelegate *delegate;

- (id)initWithExtensionsManager:(UIExtensionsManager *)extensionsManager;
- (int)getCurrentPage:(FSPDFDoc *)pdfDoc;
- (void)setCurrentPage:(FSPDFDoc *)pdfDoc pageIndex:(int)pageIndex;
- (FSRotation)getPageRotation:(FSPDFDoc *)pdfDoc pageIndex:(int)pageIndex;
- (BOOL)setPageRotation:(FSPDFDoc *)pdfDoc pageIndex:(int)pageIndex rotation:(FSRotation)rotation;
- (int)alert:(NSString *)msg title:(NSString *)title type:(int)type icon:(int)icon;
- (FSIdentityProperties *)getIdentityProperties;
- (BOOL)setDocChangeMark:(FSPDFDoc*)document change_mark:(BOOL)change_mark;
- (BOOL)getDocChangeMark:(FSPDFDoc*)document;
@end

@protocol FSPopupCarrierViewDelegate <NSObject>
- (UIView*)getPopupCarrierView;
@end

@interface DevicePosition : NSObject
@property (nonatomic, assign) CGRect phoneRect;
@property (nonatomic, strong) UIView *inPhoneView;
@property (nonatomic, assign) CGRect padRect;
@property (nonatomic, strong) UIView *inPadView;
@property (nonatomic, strong) FSAnnot *annot;
@property (nonatomic, weak) id<FSPopupCarrierViewDelegate> carrierViewDelegate;
@end

NS_ASSUME_NONNULL_END

#endif /* UIExtensionsManager_Private_h */
