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

/**
 * @file	UIExtensionsManager.h
 * @details	The UI extensions manager consists of additional UI bars and tools.
 */

#ifndef UIExtensionsManager_h
#define UIExtensionsManager_h

#import "PanelController.h"
#import "FSSettingBar.h"
#import "MoreView.h"
#import <FoxitRDK/FSPDFViewControl.h>
#import "FSReadToolbarItem.h"
#import "FSUtilities.h"
#import "FSMenuViewManager.h"
#import "FSMainToolbar.h"
#import "FSMenuControl.h"
#import "FSPermissionProvider.h"
@class UIExtensionsConfig;

NS_ASSUME_NONNULL_BEGIN

/** @brief Module base. */
@protocol IModule <NSObject>
/** @brief Get the module name. */
- (FSModuleStringName)getName;
@end

/** @brief Annotation permission delegate. */
@protocol FSAnnotPermissionDelegate <NSObject>
@optional
/** @brief Judge whether the annotation can be modified.
 *
 *  @param[in]    annot    The annotation object.
 *
 *  @return       If the annotation can be modified, return YES otherwise return NO.
 */
- (BOOL)canModifyAnnot:(FSAnnot*)annot;
/** @brief Judge whether the annotation can be deleted.
 *
 *  @param[in]    annot   The annotation object.
 *
 *  @return       If the annotation can be delete, return YES otherwise return NO.
 */
- (BOOL)canDeleteAnnot:(FSAnnot*)annot;
/** @brief Judge whether the annotation can add reply.
 *
 *  @param[in]    annot    The annotation object.
 *
 *  @return       If the annotation can add reply, return YES otherwise return NO.
 */
- (BOOL)canReplyAnnot:(FSAnnot*)annot;
@end

/** @brief Annotation event listener. */
@protocol IAnnotEventListener <NSObject>
@optional
/** @brief Triggered when the annotation is added.
 *
 * @param[in]    page    The page where the  annotation is located.
 *
 * @param[in]    annot   The added annotation.
 */
- (void)onAnnotAdded:(FSPDFPage *)page annot:(FSAnnot *)annot;
/** @brief Triggered before the annotation is deleted.
 *
 * @param[in]    page    The page where the  annotation is located.
 *
 * @param[in]    annot   The  annotation that  will be deleted.
 */
- (void)onAnnotWillDelete:(FSPDFPage *)page annot:(FSAnnot *)annot;
/** @brief Triggered when the annotation is deleted.
 *
 * @param[in]    page    The page where the  annotation is located.
 *
 * @param[in]    annot   The deleted annotation.
 */
- (void)onAnnotDeleted:(FSPDFPage *)page annot:(FSAnnot *)annot;
/** @brief Triggered when the annotation is modified.
 *
 * @param[in]    page    The page where the  annotation is located.
 *
 * @param[in]    annot   The modified annotation.
 */
- (void)onAnnotModified:(FSPDFPage *)page annot:(FSAnnot *)annot;
/** @brief Triggered when the annotation is selected.
 *
 * @param[in]    page    The page where the  annotation is located.
 *
 * @param[in]    annot   The selected annotation.
 */
- (void)onAnnotSelected:(FSPDFPage *)page annot:(FSAnnot *)annot;
/** @brief Triggered when the annotation is deselected.
 *
 * @param[in]    page    The page where the  annotation is located.
 *
 * @param[in]    annot   The deselected annotation.
 */
- (void)onAnnotDeselected:(FSPDFPage *)page annot:(FSAnnot *)annot;

#pragma mark - Batch Operation
/** @brief Triggered when the annotations are added.
 *
 * @param[in]    annots   The added annotations.
 */
- (void)onAnnotsAdded:(NSArray<FSAnnot*> *)annots;
/** @brief Triggered before the annotations will be deleted.
 *
 * @param[in]    annots   The  annotations that  will be deleted.
 */
- (void)onAnnotsWillDelete:(NSArray<FSAnnot*> *)annots;
@end

/** @brief A Tool event listener. */
@protocol IToolEventListener <NSObject>
@required
/** @brief Triggered when the current tool handler of extensions manager is changed.
 *
 * @param[in]    lastToolName    Last tool name.
 *
 * @param[in]    toolName   Current tool name.
 */
- (void)onToolChanged:(NSString *)lastToolName CurrentToolName:(NSString *)toolName;
@end

/** @brief A search event listener. */
@protocol ISearchEventListener <NSObject>
@optional
/** @brief Triggered when the text searching is started. */
- (void)onSearchStarted;
/** @brief Triggered when the text searching is canceled. */
- (void)onSearchCanceled;
@end

@class FSReadToolSettings;
/** @brief The tool handler, it handles the gesture and touch events, which a tool should always implement most of them.*/
@protocol IToolHandler <NSObject>
/** @brief Get/set the current annot type if it's an annotation tool handler. */
@property (nonatomic, assign) FSAnnotType type;
/** @brief Get the tool name.
 *
 * @return     Tool name.*/
- (NSString *)getName;

/** @brief If the tool handler is enabled.
 *
 * @return     Whether the tool handler is  enable or not.
 */
- (BOOL)isEnabled;
/** @brief If the tool handler is activated. */
- (void)onActivate;
/** @brief If the tool handler is deactivated. */
- (void)onDeactivate;

#pragma mark - PageView Gesture+Touch
/** @brief Long press gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    recognizer   Long press gesture.
 *
 * @return       Whether the long press gesture on the specified page responds or not.
 */
- (BOOL)onPageViewLongPress:(int)pageIndex recognizer:(UILongPressGestureRecognizer *)recognizer;
/** @brief Tap gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    recognizer   Tap gesture.
 *
 * @return       Whether the tap gesture on the specified page responds or not.
 */
- (BOOL)onPageViewTap:(int)pageIndex recognizer:(UITapGestureRecognizer *_Nullable)recognizer;
/** @brief Pan gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    recognizer   Pan gesture.
 *
 * @return       Whether the pan gesture on the specified page responds or not.
 */
- (BOOL)onPageViewPan:(int)pageIndex recognizer:(UIPanGestureRecognizer *)recognizer;
/** @brief Should being gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    gestureRecognizer    Responsive gesture.
 *
 * @return       Whether should begin gesture on the specified page gesture on the specified page.
 */
- (BOOL)onPageViewShouldBegin:(int)pageIndex recognizer:(UIGestureRecognizer *)gestureRecognizer;
/** @brief Touches began on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @return       Whether touch began on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesBegan:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event;
/** @brief Touches moved on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @return       Whether touch moved on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesMoved:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event;
/** @brief Touches ended on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @return       Whether touch ended on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesEnded:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event;
/** @brief Touches cancelled on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @return       Whether touch cancelled on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesCancelled:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event;
@optional
/** @brief Get/set the tool settings */
@property (nonatomic, weak) FSReadToolSettings *toolSettings;
/** @brief Drawing event on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    context      Drawing context.
 */
- (void)onDraw:(int)pageIndex inContext:(CGContextRef)context;
@end

/** @brief The annotation handler, it should handle the operations on the specified annotation. */
@protocol IAnnotHandler <NSObject>
/** @brief Can hit the annotation at specified point.
 *
 * @param[in]    annot    The pdf annotation.
 *
 * @param[in]    point    The point on PDF page, in PDF coordination.
 *
 * @return    Whether the verified point is on the annotation.
 */
- (BOOL)isHitAnnot:(FSAnnot *)annot point:(FSPointF *)point;
/** @brief When the annotation is selected.
 *
 * @param[in]    annot    The selected annotation.
 */
- (void)onAnnotSelected:(FSAnnot *)annot;
/** @brief When the annotation is deselected.
 *
 * @param[in]    annot    The deselected annotation.
 */
- (void)onAnnotDeselected:(FSAnnot *)annot;
@optional
/** @brief Add a new annotation to a specified page. It's equal to the following one with the param addUndo YES.
 *
 * @param[in]    annot     The annotation to be added.
 *
 * @return       Whether add successfully.
 */
- (BOOL)addAnnot:(FSAnnot *)annot;
/** @brief Add a new annotation to a specified page, undo/redo will be supported if the param addUndo is YES.
 *
 * @param[in]    annot     The annotation to be added.
 *
 * @param[in]    addUndo   Whether the adding operation is added to undo stack..
 *
 * @return       Whether add successfully.
 */
- (BOOL)addAnnot:(FSAnnot *)annot addUndo:(BOOL)addUndo;
/** @brief Modify an annotation. It's equal to the following one with the param addUndo YES.
 *
 * @param[in]    annot    The annotation to be modified.
 *
 * @return       Whether modify successfully.
 */
- (BOOL)modifyAnnot:(FSAnnot *)annot;
/** @brief Modify an annotation, undo/redo will be supported if the param addUndo is YES.
 *
 * @param[in]    annot    The annotation to be modified.
 *
 * @param[in]    addUndo   Whether the modification operation is added to undo stack.
 *
 * @return       Whether modify successfully.
 */
- (BOOL)modifyAnnot:(FSAnnot *)annot addUndo:(BOOL)addUndo;
/** @brief Remove an annotation. It's equal to the following one with the param addUndo YES.
 *
 * @param[in]    annot     The annotation to be removed.
 *
 * @return       Whether remove successfully.
 */
- (BOOL)removeAnnot:(FSAnnot *)annot;
/** @brief Remove an annotation, undo/redo will be supported if the param addUndo is YES.
 *
 * @param[in]    annot     The annotation to be removed.
 *
 * @param[in]    addUndo   Whether the removing operation is added to undo stack.
 *
 * @return       Whether remove successfully.
 */
- (BOOL)removeAnnot:(FSAnnot *)annot addUndo:(BOOL)addUndo;
#pragma mark - PageView Gesture+Touch
/** @brief Long press gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    recognizer   Long press gesture.
 *
 * @param[in]    annot        Gesture corresponding to the annotation.
 *
 * @return       Whether the long press gesture on the specified page responds or not.
 */
- (BOOL)onPageViewLongPress:(int)pageIndex recognizer:(UILongPressGestureRecognizer *)recognizer annot:(FSAnnot *_Nullable)annot;
/** @brief Tap gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    recognizer   Tap gesture.
 *
 * @param[in]    annot        Gesture corresponding to the annotation.
 *
 * @return       Whether the tap gesture on the specified page responds or not.
 */
- (BOOL)onPageViewTap:(int)pageIndex recognizer:(UITapGestureRecognizer *)recognizer annot:(FSAnnot *_Nullable)annot;
/** @brief Pan gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    recognizer   Pan gesture.
 *
 * @param[in]    annot        Gesture corresponding to the annotation.
 *
 * @return       Whether the pan press gesture on the specified page responds or not.
 */
- (BOOL)onPageViewPan:(int)pageIndex recognizer:(UIPanGestureRecognizer *)recognizer annot:(FSAnnot *)annot;
/** @brief Should being gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    gestureRecognizer    Responsive gesture.
 *
 * @param[in]    annot        Gesture corresponding to the annotation.
 *
 * @return       Whether should begin gesture on the specified page gesture on the specified page.
 */
- (BOOL)onPageViewShouldBegin:(int)pageIndex recognizer:(UIGestureRecognizer *)gestureRecognizer annot:(FSAnnot *_Nullable)annot;
/** @brief Touches began on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @param[in]    annot        Touch corresponding to the annotation.
 *
 * @return       Whether touch began on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesBegan:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event annot:(FSAnnot *)annot;
/** @brief Touches moved on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @param[in]    annot        Touch corresponding to the annot.
 *
 * @return       Whether touch moved on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesMoved:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event annot:(FSAnnot *)annot;
/** @brief Touches ended on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @param[in]    annot        Touch corresponding to the annot.
 *
 * @return       Whether touch ended on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesEnded:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event annot:(FSAnnot *)annot;
/** @brief Touches cancelled on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @param[in]    annot        Touch corresponding to the annot.
 *
 * @return       Whether touch cancelled on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesCancelled:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event annot:(FSAnnot *)annot;
@optional
/** brief Get the annotation type
 *
 * @return   Annotation type.
 */
- (FSAnnotType)getType;
/** brief Get the annotHandler name
 *
 * @return   AnnotHandler name.
 */
- (NSString *)getName;
/** @brief Drawing event on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    context      Drawing context.
 *
 * @param[in]    annot        The annotation to be drew.
 */
- (void)onDraw:(int)pageIndex inContext:(CGContextRef)context annot:(FSAnnot *_Nullable)annot;
/** @brief Changed property event on the specified annot.
 *
 * @param[in]    annot         Annot that need to be modified.
 *
 * @param[in]    property      Modified property.
 *
 * @param[in]    oldValue      Old value.
 *
 * @param[in]    newValue      New value.
 */
- (void)onAnnotChanged:(FSAnnot *)annot property:(long)property from:(NSValue *)oldValue to:(NSValue *)newValue;
/** @brief Should pdfViewCtrl draw annot, if NO annot handler will draw annot by itself in onDraw:inContext:annot:.
 *
 * @param[in]    annot         Annot to draw.
 *
 * @param[in]    pdfViewCtrl   The pdf view control.
 *
 * @return       Whether should draw annot by pdf view control.
 */
- (BOOL)shouldDrawAnnot:(FSAnnot *)annot inPDFViewCtrl:(FSPDFViewCtrl *)pdfViewCtrl;
/** @brief When the dynamic xfa widget is selected.
 *
 * @param[in]    widget    Selected widget.
 */
- (void)onXFAWidgetSelected:(FSXFAWidget *)widget;
/** @brief When the dynamic xfa widget is deselected.
 *
 * @param[in]    widget    Deselected widget.
 */
- (void)onXFAWidgetDeselected:(FSXFAWidget *)widget;
/** @brief Tap gesture on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    recognizer   Tap gesture.
 *
 * @param[in]    widget       The xfa widget.
 *
 * @return       Whether the tap press gesture on the specified page responds or not.
 */
- (BOOL)onPageViewTap:(int)pageIndex recognizer:(UITapGestureRecognizer *)recognizer widget:(FSXFAWidget *_Nullable)widget;
/** @brief Should being gesture on the specified page.
 *
 * @param[in]    pageIndex    The PDF page index.
 *
 * @param[in]    gestureRecognizer    Responsive gesture.
 *
 * @param[in]    widget       The xfa widget.
 *
 * @return       Whether should begin gesture on the specified page gesture on the specified page.
 */
- (BOOL)onPageViewShouldBegin:(int)pageIndex recognizer:(UIGestureRecognizer *)gestureRecognizer widget:(FSXFAWidget *_Nullable)widget;
/** @brief Touches began on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @param[in]    widget       The xfa widget.
 *
 * @return       Whether touch began on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesBegan:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event widget:(FSXFAWidget *_Nullable)widget;
/** @brief Touches moved on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @param[in]    widget       The xfa widget.
 *
 * @return       Whether touch moved gesture on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesMoved:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event widget:(FSXFAWidget *_Nullable)widget;
/** @brief Touches ended on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    touches      Touch set.
 *
 * @param[in]    event        Touch event.
 *
 * @param[in]    widget       The xfa widget.
 *
 * @return       Whether touch ended on the specified page responds or not.
 */
- (BOOL)onPageViewTouchesEnded:(int)pageIndex touches:(NSSet *)touches withEvent:(UIEvent *)event widget:(FSXFAWidget *_Nullable)widget;
/** @brief Drawing event on the specified page.
 *
 * @param[in]    pageIndex    The pdf page index,0 for the first page.
 *
 * @param[in]    context      Drawing context.
 *
 * @param[in]    widget       The drawing XFA widget.
 */
- (void)onDraw:(int)pageIndex inContext:(CGContextRef)context widget:(FSXFAWidget *_Nullable)widget;
@end

/** @brief The full screen event listener. */
@protocol IFullScreenListener <NSObject>
/**
 * @brief Triggered when toggle full screen. When full screen, top/bottom tool bars are to be hidden.
 *
 * @param[in] isFullScreen      Whether is in full screen mode.
 */
- (void)onFullScreen:(BOOL)isFullScreen;
@end

/** @brief The page number event listener. */
@protocol IPageNumberListener <NSObject>
/**
 * @brief update page number.
 */
- (void)updatePageNumber;
@end

/** @brief A link event listener. */
@protocol ILinkEventListener <NSObject>
@optional
/** @brief Triggered when the link is clicked.
 *
 * @param[in] link        Clicked link.
 *
 * @param[in] pointParam  The link location on page, in device coordination.
 */
- (BOOL)onLinkOpen:(id)link LocationInfo:(CGPoint)pointParam;
@end

/** @brief Panel types. */
typedef NS_ENUM(NSUInteger, FSToolbarType) {
    /** @brief The top tool bar. */
    FSTopBar = 1,
    /** @brief The bottom tool bar. */
    FSBottomBar
};

/** @brief Document modified event listener. */
@protocol IDocModifiedEventListener <NSObject>
@optional
/** @brief Triggered when the document is modified.
 *
 * @param[in]    doc    The pdf document which is modified.
 */
- (void)onDocModified:(FSPDFDoc *)doc;

@end

/** @brief Signature modified event listener. */
@protocol ISignatureEventListener <NSObject>
@optional
/** @brief Triggered when a digital signature  is signed.
 *
 * @param[in]    success    Whether the digital signature was added successfully.
 */
- (void)onDigitalSignatureSigned:(BOOL)success;

@end

@class UIExtensionsManager;
@protocol UIExtensionsManagerDelegate <NSObject>
@optional
/** @brief Customize toolbar position and animation when toggle hidden state.
 *  By default, top toolbar shows with top anchor equaling top anchor of pdf view ctrl and hides with bottom anchor equaling top anchor of pdf view ctrl.
 *  User can replace the default behavior by implementing this method.
 *  For instance top toolbar can change to top layout guide when it shows, or be added with additional subviews.
 *
 * @param[in]    uiextensionsManager    Current UIExtensionsManager.
 *
 * @param[in]    type    The type of toolbar, see macros FSToolbarType.
 * @param[in]    hidden    Whether to set toolbar to be hidden.
 *
 *
 */
- (void)uiextensionsManager:(UIExtensionsManager *)uiextensionsManager onToolBar:(FSToolbarType)type hidden:(BOOL)hidden;
/** @brief Open new pdf doc by path.
 *
 * @param[in]    uiextensionsManager    Current UIExtensionsManager.
 *
 * @param[in]    path    New pdf doc path.
 * @param[in]    closeCurrentDoc    Whether to close the current document. If NO, then the sdk caller should use a new PDF view Control to open the new document, if YES, then caller should close the current document and open the new document with the current PDF view control.
 *
 * @return    Whether to open successfully.
 */
- (BOOL)uiextensionsManager:(UIExtensionsManager *)uiextensionsManager openNewDocAtPath:(NSString *)path shouldCloseCurrentDoc:(BOOL)closeCurrentDoc;
/* @brief normally should save doc and close it.
 *
 * @param[in]    uiextensionsManager    Current UIExtensionsManager.
 *
 * @param[in]    control    Current clicked control.
 *
 */
- (void)quitUIExtensionsManager:(UIExtensionsManager *)uiextensionsManager control:(UIControl *)control;

@end

/** @brief The UI extensions manager which has included the default implementation of text selection tool, annotation tools... and so on. */
@interface UIExtensionsManager : NSObject <FSPDFUIExtensionsManager, IDocEventListener, IPageEventListener, IRotationEventListener, IAnnotEventListener, IRecoveryEventListener, ILinkEventListener, UIToolbarDelegate, ISignatureEventListener>
/** @brief The controller preferred status bar style for UIExtensionsManager. The default  is UIStatusBarStyleDefault*/
@property (class, nonatomic, assign) UIStatusBarStyle preferredStatusBarStyle;
/** @brief Get/Set  the primary color The default  is #923094*/
@property (class, nonatomic, strong) UIColor *primaryColor;
/** @brief Set/get annot author. */
@property (nonatomic, copy) NSString *annotAuthor;
/** @brief The PDF view control. */
@property (nonatomic, strong ,readonly) FSPDFViewCtrl *pdfViewCtrl;
/** @brief The more menu View. */
@property (nonatomic, strong, readonly) MoreMenuView *more;
/** @brief The custom view manager  . */
@property (nonatomic, strong, readonly) FSMenuViewManager *menuViewManager;
/**@brief Get/set settings on add tools .If set to nil, it will be automatically created using default config*/
@property (nonatomic, strong) NSMutableDictionary<NSNumber *, FSReadToolSettings *> *addToolsSettings;
/** @brief Delegate of UI extensions manager. */
@property (nonatomic, weak) id<UIExtensionsManagerDelegate> delegate;
/** @brief The Current tool handler. */
@property (nonatomic, strong, nullable) id<IToolHandler> currentToolHandler;
/** @brief Can update annot default properties, default is yes*/
@property (nonatomic, assign) BOOL canUpdateAnnotDefaultProperties;
/** @brief The Current selected annotation. */
@property (nonatomic, strong, nullable) FSAnnot *currentAnnot;
/** @brief Whether to allow to jump to link address when tap on the link annotation. */
@property (nonatomic, assign) BOOL enableLinks;
/** @brief Whether to allow to highlight links. */
@property (nonatomic, assign) BOOL enableHighlightLinks;
/** @brief Whether to allow to highlight form  and call -[FSPDFViewCtrl Refresh] if you want to take effect immediately.*/
@property (nonatomic, assign) BOOL enableHighlightForm;
/** @brief Get/Set the highlight color for links. */
@property (nonatomic, strong) UIColor *linksHighlightColor;
/** @brief Get/Set the highlight color for text selection. */
@property (nonatomic, strong) UIColor *selectionHighlightColor;
/** @brief Get/Set the highlight color for form  and call -[FSPDFViewCtrl Refresh] if you want to take effect immediately*/
@property (nonatomic, strong) UIColor *highlightFormColor;
/** @brief Caller can choose to provide a block to execute when user tap on 'back' button on the top toolbar. */
@property (nonatomic, copy, nullable) void (^goBack)(void);
/** @brief The Current UIExtensionsManager topToolbar. */
@property (nonatomic, strong, readonly, nullable) FSMainTopbar *topToolbar;
/** @brief The Current UIExtensionsManager bottomToolbar. */
@property (nonatomic, strong, readonly, nullable) FSMainBottombar *bottomToolbar;
/** @brief The panel controller. */
@property (nonatomic, strong) FSPanelController *panelController;
/** @brief The setting bar. It shows when tap on the view button in the bottom bar. */
@property (nonatomic, strong) FSSettingBar *settingBar;
/** @brief Whether to keep tool active after using it to add an annotation. */
@property (nonatomic, assign) BOOL continueAddAnnot;
/** @brief Whether is full screen. When full screen, top and bottom bar is not shown. */
@property (nonatomic, assign) BOOL isFullScreen;
/** @brief Whether screen rotation is locked or not. */
@property (nonatomic, assign, readonly) BOOL isScreenLocked;
/** @brief Prevent to override original pdf file. */
@property (nonatomic, strong) NSString *preventOverrideFilePath;
/** @brief Whether the current document is modified or not. */
@property (nonatomic, assign, setter=setDocModified:) BOOL isDocModified;
/** @brief Whether the preview mode is multiple file mode. */
@property (nonatomic, assign) BOOL isMultiFileMode;
/** @brief Set to automatically save documents Yes/No. */
@property (nonatomic, assign, setter=setAutoSaveDoc:) BOOL isAutoSaveDoc;
/** @brief The Current doc save flag. */
@property (nonatomic, assign) FSPDFDocSaveFlags docSaveFlag;
/** @brief The Current action handler. */
@property (nonatomic, strong) id<FSActionCallback> actionHandler;

/** @brief The Current selected xfa widget. */
@property (nonatomic, strong, nullable) FSXFAWidget *currentWidget;

/** @brief Set to automatically save the signed document Yes/No. */
@property (nonatomic, assign, setter=setAutoSaveSignedDoc:) BOOL isAutoSaveSignedDoc;
/** @brief Set/Get the full PDF file path where the signed document is saved and it works when set to automatically save the signed document*/
@property (nonatomic, strong) NSString *signedDocSavePath;
/** @brief Whether the PDF view hide the status bar*/
@property (nonatomic, assign, readonly) BOOL prefersStatusBarHidden;
/** @brief Delegate of annotation permission. If set, once one of the implementation results is false,  the form function will  be disabled. */
@property (nonatomic, weak) id<FSAnnotPermissionDelegate> annotPermissionDelegate;
/** @brief Delegate of menucontrol. */
@property (nonatomic, weak) id<FSMenuControlDelegate> menuControlDelegate;
/** @brief Permission provider */
@property (nonatomic, strong) FSPermissionProvider* permissionProvider;

/**
 * @brief Intialize extensions manager.
 *
 * @param[in]	viewctrl	The PDF view control.
 *
 * @return	The extensions mananger instance.
 */
- (id)initWithPDFViewControl:(FSPDFViewCtrl *)viewctrl;
/**
 * @brief Intialize extensions manager.
 *
 * @param[in]	viewctrl        The PDF view control.
 * @param[in]	jsonConfigData	The json file data. See uiextensions_config.json for an example
 *
 * @return	The extensions mananger instance.
 */
- (id)initWithPDFViewControl:(FSPDFViewCtrl *)viewctrl configuration:(NSData *_Nullable)jsonConfigData;
/**
 * @brief Intialize extensions manager.
 *
 * @param[in]	viewctrl        The PDF view control.
 * @param[in]	configuration	The modules configuration.
 *
 * @return	The extensions mananger instance.
 */
- (id)initWithPDFViewControl:(FSPDFViewCtrl *)viewctrl configurationObject:(UIExtensionsConfig *_Nonnull)configuration;

/**
 * @brief Register a full screen event listener.
 *
 * @param[in]    listener    The Full Screen Listener.
 *
 */
- (void)registerFullScreenListener:(id<IFullScreenListener>)listener;
/**
 * @brief Unregister a full screen event listener.
 *
 * @param[in]    listener    The Full Screen Listener.
 *
 */
- (void)unregisterFullScreenListener:(id<IFullScreenListener>)listener;

/**
 * @brief Register a page number event listener.
 *
 * @param[in]    listener    The Page Number Listener.
 *
 */
- (void)registerPageNumberListener:(id<IPageNumberListener>)listener ;
/**
 * @brief Unregister a page number  event listener.
 *
 * @param[in]    listener    The Page Number Listener.
 *
 */
- (void)unregisterPageNumerListener:(id<IPageNumberListener>)listener ;

/**
 * @brief Register a rotation event listener.
 *
 * @param[in]    listener    The Rotation Event Listener.
 *
 */
- (void)registerRotateChangedListener:(id<IRotationEventListener>)listener;
/**
 * @brief Unregister a rotation event listener.
 *
 * @param[in]    listener    The Rotation Event Listener.
 *
 */
- (void)unregisterRotateChangedListener:(id<IRotationEventListener>)listener;
/**
 * @brief Enable or disable top toolbar.No effect on top toolbar in full screen mode.
 *
 * @param[in]	isEnabled	Whether top toolbar is enabled or not.
 */
- (void)enableTopToolbar:(BOOL)isEnabled;
/**
 * @brief Enable or disable bottom toolbar.No effect on bottom toolbar in full screen mode
 *
 * @param[in]	isEnabled	Whether bottom toolbar is enabled or not.
 */
- (void)enableBottomToolbar:(BOOL)isEnabled;

/**
 * @brief Enable or disable small top toolbar.
 *
 * @param[in]    isEnabled    Whether small top toolbar is enabled or not.
 */
- (void)enableSmallTopToolbar:(BOOL)isEnabled;
/**
 * @brief Enable or disable small bottom toolbar.
 *
 * @param[in]    isEnabled    Whether small bottom toolbar is enabled or not.
 */
- (void)enableSmallBottomToolbar:(BOOL)isEnabled;

#pragma mark - Toolhandler and AnnotHandler registration.
/**
 * @brief Get the current tool handler by name, which is defined above Tool_XXX.
 *
 * @param[in]    name    The name of tool handler.
 *
 * @return    The tool handler .
 */
- (id<IToolHandler>)getToolHandlerByName:(NSString *)name;
/**
 * @brief Get the annotation handler by annotation type.
 *
 * @param[in]    type    The type of annotation. Please refer to {@link FSAnnotType} values and it would be one of these values.
 *
 * @return    The annotation handler .
 */
- (id<IAnnotHandler>)getAnnotHandlerByType:(FSAnnotType)type;
/**
 * @brief Register a tool handler.
 *
 * @param[in]    toolHandler    The tool handler.
 *
 */
- (void)registerToolHandler:(id<IToolHandler>)toolHandler;
/**
 * @brief Remove a tool handler.
 *
 * @param[in]    toolHandler    The tool handler.
 *
 */
- (void)unregisterToolHandler:(id<IToolHandler>)toolHandler;
/**
 * @brief Register an annotation handler.
 *
 * @param[in]    annotHandler    The annot handler.
 *
 */
- (void)registerAnnotHandler:(id<IAnnotHandler>)annotHandler;
/**
 * @brief Remove an annotation handler.
 *
 * @param[in]    annotHandler    The annot handler.
 *
 */
- (void)unregisterAnnotHandler:(id<IAnnotHandler>)annotHandler;

#pragma mark - Tool and annotation event listeners.
/**
 * @brief Register the annotation event listener.
 *
 * @param[in]    listener    The annot event listener.
 *
 */
- (void)registerAnnotEventListener:(id<IAnnotEventListener>)listener;
/**
 * @brief Unregister the annotation event listener.
 *
 * @param[in]    listener    The annot event listener.
 *
 */
- (void)unregisterAnnotEventListener:(id<IAnnotEventListener>)listener;
/**
 * @brief Register the tool event listener.
 *
 * @param[in]    listener    The tool event listener.
 *
 */
- (void)registerToolEventListener:(id<IToolEventListener>)listener;
/**
 * @brief Unregister the tool event listener.
 *
 * @param[in]    listener    The tool event listener.
 *
 */
- (void)unregisterToolEventListener:(id<IToolEventListener>)listener;

#pragma mark - Document modified event listeners.
/**
 * @brief Register the document modified event listener.
 *
 * @param[in]    listener    The document modified event listener.
 *
 */
- (void)registerDocModifiedEventListener:(id<IDocModifiedEventListener>)listener;

/**
 * @brief Unregister the document modified event listener.
 *
 * @param[in]    listener    The document modified event listener.
 *
 */
- (void)unregisterDocModifiedEventListener:(id<IDocModifiedEventListener>)listener;

#pragma mark - link event listeners.
/**
 * @brief Register the link event listener.
 *
 * @param[in]    listener    The link event listener.
 *
 */
- (void)registerLinkEventListener:(id<ILinkEventListener>)listener;
/**
 * @brief Unregister the link event listener.
 *
 * @param[in]    listener    The link event listener.
 *
 */
- (void)unregisterLinkEventListener:(id<ILinkEventListener>)listener;

#pragma mark - signature event listeners.
/**
 * @brief Register the signature event listener.
 *
 * @param[in]    listener    The signature event listener.
 *
 */
- (void)registerSignatureEventListener:(id<ISignatureEventListener>)listener;
/**
 * @brief Unregister the signature event listener.
 *
 * @param[in]    listener    The signature event listener.
 *
 */
- (void)unregisterSignatureEventListener:(id<ISignatureEventListener>)listener;

#pragma mark - Property bar of annotation for setting/getting annotation color and opacity.
/**
 * @brief Show the property bar to set annotation color and opacity.
 *
 * @param[in]    toolSettings    Tool settings item
 * @param[in]    rect    The rect of property bar.
 * @param[in]    view    The view that property bar belong.
 *
 */
- (void)showPropertyWithToolSettings:(FSReadToolSettings *)toolSettings rect:(CGRect)rect inView:(UIView *)view;
/**
 * @brief Show or hide the text searching bar on the UI main screen. It will appear on the top of main screen.
 *
 * @param[in]    show    The search bar show/hide.
 *
 */
- (void)showSearchBar:(BOOL)show;
/**
 * @brief Register the tool event listener.
 *
 * @param[in]    listener    The search event listener.
 *
 */
- (void)registerSearchEventListener:(id<ISearchEventListener>)listener;
/**
 * @brief Unregister the tool event listener.
 *
 * @param[in]    listener    The search event listener.
 *
 */
- (void)unregisterSearchEventListener:(id<ISearchEventListener>)listener;

/**
 * @brief Get current selected text.
 *
 * @return    The current selected text.
 *
 */
- (NSString *)getCurrentSelectedText;

#pragma mark - Module
/** @brief Get the module by module name.
 *
 * @return    id<IModule>    The id<IModule>;
 */
- (__kindof id<IModule>)getModuleByName:(FSModuleStringName)name;

/** @brief Enter or exit full screen mode.
 *
 * @param[in]    fullScreen    Boolean flag to indicate whether to enter full screen mode or not.
 *
 */
- (void)setFullScreen:(BOOL)fullScreen;

/** @brief Suspend the auto full screen mode. */
- (void)suspendAutoFullScreen;

/** @brief Resume the auto full screen mode. */
 - (void)resumeAutoFullScreen;

/** @brief Print the document by displaying an UI to select printer.
 *
 * @param[in]   doc The pdf document.
 * @param[in]   animated    Use animation or not .
 * @param[in]   jobName The printing job name.
 * @param[in]   delegate    The delegate for printing.
 * @param[in]   completion  A completion handler to be invoked after printing job is done.
 *
 */
+ (void)printDoc:(FSPDFDoc *)doc animated:(BOOL)animated jobName:(nullable NSString *)jobName delegate:(nullable id<UIPrintInteractionControllerDelegate>)delegate completionHandler:(nullable UIPrintInteractionCompletionHandler)completion;

/** @brief Print the rect in the specified view by displaying an UI to select printer.
 *
 * @param[in]   doc The pdf document.
 * @param[in]   rect The rectangle area in the specified UIView.
 * @param[in]   view  The specified UIView.
 * @param[in]   animated    Use animation or not .
 * @param[in]   jobName The printing job name.
 * @param[in]   delegate    The delegate for printing.
 * @param[in]   completion  A completion handler to be invoked after printing job is done.
 *
 */
+ (void)printDoc:(FSPDFDoc *)doc fromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated jobName:(nullable NSString *)jobName delegate:(nullable id<UIPrintInteractionControllerDelegate>)delegate completionHandler:(nullable UIPrintInteractionCompletionHandler)completion;

/** @brief Get t tool settings
 *
 * @param[in]   settingsType     The type of settings. Please refer to {@link FSReadToolSettingsTypeXXX} and {@link FSReadToolSettingsType} values and it would be one of these values.
 *
 * @return    FSReadToolSettings ,If the default tool settings ;
 */
- (FSReadToolSettings *)getReadToolSettingsForType:(FSReadToolSettingsType)settingsType;

/**
 * @brief Get state of extensions manager.
 *
 * @return    The current state. Please refer to {@link FSUIManagerStateXXX } and {@link FSUIManagerState } values and it would be one of these values.
 */
- (FSUIManagerState)getState;
/**
 * @brief Change state of extensions manager. It is only be supported after the document is opened.
 *
 * @param[in]    state    New state. Please refer to {@link FSUIManagerStateXXX } and {@link FSUIManagerState }  values and it would be one of these values.
 */
- (void)changeState:(FSUIManagerState)state;
/**
 * @brief Save the file to the specified location.
 *
 * @param[in]    successed callback.
 *
 * @param[in]    error callback.
 */
-(void)documentSaveAS:(void (^_Nullable)(void))successed error:(void (^_Nullable)(void))error;

/**
 * @brief Set the callback method of  more Item Clicked
 *
 * @param[in]    clickedCallback the callback method
 */
- (void)setMoreItemClikedCallback:(void (^)(UIView* moreItem))clickedCallback;

#pragma mark - Main toolbar item info
/**
 * @brief Get toolbar item hide/show status.
 *
 * @return    The toolbar item hide/show status dictionary.
 *
 */
-(NSMutableDictionary *)getToolbarItemHiddenStatus;

/** @brief Set mainToolbar item hide/show.
 *
 * @details Currently, if the itemTag is just one of following formats,
 *          {@link FS_TOOLBAR_ITEM_TAG_XXX},
 *          For other unsupported itemTag, this function will do nothing change.
 *
 * @param[in]   itemTag The item tag will show/hide.
 * @param[in]   isHidden The item show/hide .
 *
 */
-(void)setToolbarItemHiddenWithTag:(FS_TOOLBAR_ITEM_TAG)itemTag hidden:(BOOL)isHidden;

@end


NS_ASSUME_NONNULL_END

#endif /* UIExtensionsManager_h */
