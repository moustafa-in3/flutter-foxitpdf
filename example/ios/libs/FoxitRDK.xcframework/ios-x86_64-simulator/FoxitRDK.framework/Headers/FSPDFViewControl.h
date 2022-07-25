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
 * @file	FSPDFViewControl.h
 * @details	Foxit has implemented an automatically recovering system when the pdf viewer control receives memory warning notification, which is considered as the viewer control will soon run out of memory(OOM).
 *          When this happens, the Foxit PDF SDK will try to restore to the latest reading status before OOM. However, if the user has modified/added/deleted something on PDF document,
 *          those will not be recovered by Foxit PDF SDK.
 *          OOM recovery could be disabled by setting the property 'shouldRecover' of viewer control to 'NO'.
 */

#import "FSPDFObjC.h"
#import <UIKit/UIKit.h>
#import "FSLocalization.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief	Enumeration for PDF layout mode.
 * 
 * @details	Values of this enumeration should be used alone.
 */
typedef enum {
    /** @brief	Unknown page mode. */
    PDF_LAYOUT_MODE_UNKNOWN = 0,
    /** @brief	Single page mode. */
    PDF_LAYOUT_MODE_SINGLE,
    /** @brief	Facing mode. */
    PDF_LAYOUT_MODE_TWO,
    /** @brief	Reflow mode. */
    PDF_LAYOUT_MODE_REFLOW,
    /** @brief	Facing mode. Cover page left */
    PDF_LAYOUT_MODE_TWO_LEFT,
    /** @brief	Facing mode. Cover page right */
    PDF_LAYOUT_MODE_TWO_RIGHT,
    /** @brief	Facing mode. Cover page middle */
    PDF_LAYOUT_MODE_TWO_MIDDLE,
    
} PDF_LAYOUT_MODE;

/**
 * @brief	Enumeration for page reflow mode.
 *
 * @details	Values of this enumeration should be used alone.
 */
typedef enum {
    /** @brief	No reflow. */
    PDF_REFLOW_NONE = -1,
    /** @brief Reflow both text and image on PDF page. */
    PDF_REFLOW_WITHIMAGE = 0,
    /** @brief Reflow just text on PDF page. */
    PDF_REFLOW_ONLYTEXT
} PDF_REFLOW_REFLOWMODE;



/**
 * @brief	Enumeration for PDF display zoom mode.
 * 
 * @details	Values of this enumeration should be used alone.
 */
typedef enum {
    /** @brief	Zoom mode: unknown. */
    PDF_DISPLAY_ZOOMMODE_UNKNOWN = 0,
    /** @brief	Zoom mode: fit page. */
    PDF_DISPLAY_ZOOMMODE_FITPAGE,
    /** @brief	Zoom mode: fit page width. */
    PDF_DISPLAY_ZOOMMODE_FITWIDTH,
    /** @brief	Zoom mode: fit page height. */
    PDF_DISPLAY_ZOOMMODE_FITHEIGHT
} PDF_DISPLAY_ZOOMMODE;

/**
 * @brief	Enumeration for page crop mode.
 *
 * @details	Values of this enumeration should be used alone.
 */
typedef enum {
    /** @brief	No crop. */
    PDF_CROP_MODE_NONE = -1,
    /** @brief	Crop margin according to bounding box of all contents. */
    PDF_CROP_MODE_CONTENTSBOX,
    /** @brief	Crop margin by detecting paths or images. */
    PDF_CROP_MODE_DETECTION,
    /** @brief	Crop margin with specified pages & rects */
    PDF_CROP_MODE_CUSTOMIZED,
} PDF_CROP_MODE;

/**
 * @brief    Enumeration for page spacing direction.
 *
 */
typedef NS_ENUM(NSInteger, FS_PAGESPACING_DIRECTION) {
    /** @brief    PageSpcaing horizontal direction. */
    FS_PAGESPACING_HORIZONTAL = 0x0001,
    /** @brief    PageSpcaing vertical direction. */
    FS_PAGESPACING_VERTICAL = 0x0002
};

/**
 * @brief    Enumeration for page style direction.
 *
 */
typedef enum {
    /** @brief    Insert page blank style. */
    PDF_PAGE_STYLE_TYPE_BLANK = 0,
    /** @brief    Insert page lined style. */
    PDF_PAGE_STYLE_TYPE_LINED,
    /** @brief    Insert page grid style. */
    PDF_PAGE_STYLE_TYPE_GRID,
    /** @brief    Insert page graph style. */
    PDF_PAGE_STYLE_TYPE_GRAPH,
    /** @brief    Insert page music style. */
    PDF_PAGE_STYLE_TYPE_MUSIC
} PDF_PAGE_STYLE_TYPE;

typedef NS_ENUM(NSUInteger, FSNightColorMode) {
    ///< Night color mode: defaul
    FSNightColorModeDefault,
    ///< Night color mode: mapping gray
    FSNightColorModeMappingGray,
};

/** @brief	 Recovery event listener used when view control runs out of memory. */
@protocol IRecoveryEventListener <NSObject>
@optional
/** 
 * @brief	Triggered before recovering the view control.
 */
- (void)onWillRecover;
/** 
 * @brief	Triggered after the view control has recovered from running out of memory.
 */
- (void)onRecovered;
@end

/** @brief	Device rotation delegate. */
@protocol IRotationEventListener <NSObject>
@optional
/** 
 * @brief	Triggered when rotation begins. 
 *
 * @param[in]	toInterfaceOrientation      The UI interface orientation.
 * @param[in]	duration                    The Time duration.
 */
- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
/** 
 * @brief	Triggered when animated rotation begins. 
 *
 * @param[in]	toInterfaceOrientation      The UI interface orientation.
 * @param[in]	duration                    The Time duration.
 */
- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
/** 
 * @brief	Triggered after rotation is done.
 *
 * @param[in]	fromInterfaceOrientation    The UI interface orientation.
 */
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;
@end

/** @brief	The PDF document event listener. */
@protocol IDocEventListener <NSObject>
@optional
/** 
 * @brief	Triggered when the document will be opened.
 */
- (void)onDocWillOpen;
/** 
 * @brief	Triggered when the document is opened. 
 *
 * @param[in]	document	PDF document instance which is opened.
 * @param[in]	error		Error code. Please refer to {@link FSErrorCode::FSErrSuccess FSErrorCode::FSErrXXX} values and it should be one of these values.
 */
- (void)onDocOpened:(FSPDFDoc * _Nullable)document error:(int)error;
/** 
 * @brief	Triggered when the document will be closed. 
 *
 * @param[in]	document	PDF document instance which will be closed.
 */
- (void)onDocWillClose:(FSPDFDoc *)document;
/** 
 * @brief	Triggered when the document is closed. 
 *
 * @param[in]	document	PDF document instance which is closed.
 * @param[in]	error		Error code. Please refer to {@link FSErrorCode::FSErrSuccess FSErrorCode::FSErrXXX} values and it should be one of these values.
 */
- (void)onDocClosed:(FSPDFDoc * _Nullable)document error:(int)error;
/** 
 * @brief	Triggered when the document will be saved. 
 *
 * @param[in]	document	PDF document instance which will be saved.
 */
- (void)onDocWillSave:(FSPDFDoc *)document;
/** 
 * @brief	Triggered when the document is saved. 
 *
 * @param[in]	document	PDF document instance which is saved.
 * @param[in]	error		Error code. Please refer to {@link FSErrorCode::FSErrSuccess FSErrorCode::FSErrXXX} values and it should be one of these values.
 */
- (void)onDocSaved:(FSPDFDoc *)document error:(int)error;

@end

/** @brief	The page event listener. */
@protocol IPageEventListener <NSObject>
@optional
/** 
 * @brief	Triggered when current page is changed. 
 *
 * @param[in]	oldIndex		Old page index. Valid range: from 0 to (<i>count</i>-1).
 *								<i>count</i> is the page count.
 * @param[in]	currentIndex	Current page index. Valid range: from 0 to (<i>count</i>-1).
 *								<i>count</i> is the page count.
 */
- (void)onPageChanged:(int)oldIndex currentIndex:(int)currentIndex;
/** 
 * @brief	Triggered when the page becomes visible. 
 *
 * @param[in]	index		Page index. Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 */
- (void)onPageVisible:(int)index;
/** 
 * @brief	Triggered when the page becomes invisible. 
 *
 * @param[in]	index		Page index. Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 */
- (void)onPageInvisible:(int)index;
/** 
 * @brief	Triggered by the page navigation or link jump.
 */
- (void)onPageJumped;
/**
 * @brief	Triggered when pages will be removed.
 *
 * @param[in]	indexes		Page index array. Valid range of page index: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 */
- (void)onPagesWillRemove:(NSArray<NSNumber *> *)indexes;
/**
 * @brief	Triggered when pages will be moved to a new index.
 *
 * @param[in]	indexes		Page index array. Valid range of page index: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 * @param[in]	dstIndex	The destination page index, which the pages will be inserted before.
 */
- (void)onPagesWillMove:(NSArray<NSNumber *> *)indexes dstIndex:(int)dstIndex;
/**
 * @brief	Triggered when pages will be rotated.
 *
 * @param[in]	indexes		Page index array. Valid range of page index: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 * @param[in]   rotation    The page rotation, valid value will be 0(0 degree), 1(90 degree), 2(180 degree), 3(270 degree).
 */
- (void)onPagesWillRotate:(NSArray<NSNumber *> *)indexes rotation:(int)rotation;
/**
 * @brief	Triggered when pages were removed.
 *
 * @param[in]	indexes		Page index array. Valid range of page index: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 */
- (void)onPagesRemoved:(NSArray<NSNumber *> *)indexes;
/**
 * @brief	Triggered when pages were moved to a new index.
 *
 * @param[in]	indexes		Page index array. Valid range of page index: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 * @param[in]	dstIndex	The destination page index, which the pages will be inserted before.
 */
- (void)onPagesMoved:(NSArray<NSNumber *> *)indexes dstIndex:(int)dstIndex;
/**
 * @brief	Triggered when pages were rotated.
 *
 * @param[in]	indexes		Page index array. Valid range of page index: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 * @param[in]   rotation    The page rotation, valid value will be 0(0 degree), 1(90 degree), 2(180 degree), 3(270 degree).
 */
- (void)onPagesRotated:(NSArray<NSNumber *> *)indexes rotation:(int)rotation;
/**
 * @brief	Triggered when pages were inserted.
 *
 * @param[in]	range		Page index range.
 */
- (void)onPagesInsertedAtRange:(NSRange)range;
@end

/** @brief	The page layout event listener. */
@protocol ILayoutEventListener <NSObject>
@optional
/** 
 * @brief	Triggered when current page layout mode is changed.
 *
 * @param[in]	oldLayoutMode		Old layout mode. 
 *									Please refer to {@link PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_UNKNOWN PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_XXX} values and this should be one of these values.
 * @param[in]	newLayoutMode		New layout mode. 
 *									Please refer to {@link PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_UNKNOWN PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_XXX} values and this should be one of these values.
 */
- (void)onLayoutModeChanged:(PDF_LAYOUT_MODE)oldLayoutMode newLayoutMode:(PDF_LAYOUT_MODE)newLayoutMode;
/**
 * @brief    Triggered when current page layout is finished.
 */
- (void)onLayoutFinished;
@end

/** @brief	The event listener for scroll view, which is the container of page views. */
@protocol IScrollViewEventListener <NSObject>
@optional
/** 
 * @brief	Triggered when any offset changes.
 *
 * @param[in]	scrollView      The scroll view that displays PDF pages.
 */
- (void)onScrollViewDidScroll:(UIScrollView *)scrollView;
/** 
 * @brief	Triggered when any zoom scale changes.
 *
 * @param[in]	scrollView      The scroll view that displays PDF pages.
 */
- (void)onScrollViewDidZoom:(UIScrollView *)scrollView;
/** 
 * @brief	Triggered when called on start of dragging (may require some time or distance to move).
 *
 * @param[in]	scrollView      The scroll view that displays PDF pages.
 */
- (void)onScrollViewWillBeginDragging:(UIScrollView *)scrollView;
/** 
 * @brief	Triggered when called on finger up if the user dragged.
 *
 * @param[in]	scrollView      The scroll view that displays PDF pages.
 * @param[in]	decelerate      <b>YES</b> means it will continue moving afterwards, while <b>NO</b> means not.
 */
- (void)onScrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;
/** 
 * @brief	Triggered when called on finger up as we are moving.
 *
 * @param[in]	scrollView      The scroll view that displays PDF pages.
 */
- (void)onScrollViewWillBeginDecelerating:(UIScrollView *)scrollView;
/** 
 * @brief	Triggered when called when scroll view grinds to a halt.
 *
 * @param[in]	scrollView      The scroll view that displays PDF pages.
 */
- (void)onScrollViewDidEndDecelerating:(UIScrollView *)scrollView;
/** 
 * @brief	Triggered when called before the scroll view begins zooming its content.
 *
 * @param[in]	scrollView      The scroll view that displays PDF pages.
 */
- (void)onScrollViewWillBeginZooming:(UIScrollView *)scrollView;
/** 
 * @brief	Triggered when scale between minimum and maximum. called after any "bounce" animations.
 *
 * @param[in]	scrollView      The scroll view that displays PDF pages.
 */
- (void)onScrollViewDidEndZooming:(UIScrollView *)scrollView;
@end

@class FSPDFViewCtrl;
/** @brief    The event listener for  pdfview,  Some of apple's interfaces  */
@protocol IViewAppleEventListener <NSObject>
@optional

/**
 * @brief    -[UView layoutSubviews].
 */
- (void)layoutSubviewsFromPDFViewCtrl:(FSPDFViewCtrl *)pdfViewCtrl;

/**
 * @brief    -[UView didMoveToWindow].
 */
- (void)didMoveToWindowFromPDFViewCtrl:(FSPDFViewCtrl *)pdfViewCtrl;

@end

/** @brief	The gesture event listener. */
@protocol IGestureEventListener <NSObject>
@optional
/** 
 * @brief	Triggered on long press gesture.
 *
 * @param[in]	gestureRecognizer       The gesture recognizer.
 *
 * @return	<b>YES</b> means that this event has been handled by the event listener.
 *			<b>NO</b> means that the event listener did not handle this event.
 */
- (BOOL)onLongPress:(UILongPressGestureRecognizer *)gestureRecognizer;
/** 
 * @brief	Triggered on the tap gesture.
 *
 * @param[in]	gestureRecognizer       The gesture recognizer.
 *
 * @return	<b>YES</b> means that this event has been handled by the event listener.
 *			<b>NO</b> means that the event listener did not handle this event.
 */
- (BOOL)onTap:(UITapGestureRecognizer *)gestureRecognizer;
/**
 * @brief    Triggered on the double tap gesture.
 *
 * @param[in]    gestureRecognizer       The gesture recognizer.
 *
 * @return    <b>YES</b> means that this event has been handled by the event listener.
 *            <b>NO</b> means that the event listener did not handle this event.
 */
- (BOOL)onDoubleTap:(UITapGestureRecognizer *)gestureRecognizer;
/** 
 * @brief	Triggered on the pan gesture.
 *
 * @param[in]	gestureRecognizer       The gesture recognizer.
 *
 * @return	<b>YES</b> means that this event has been handled by the event listener.
 *			<b>NO</b> means that the event listener did not handle this event.
 */
- (BOOL)onPan:(UIPanGestureRecognizer *)gestureRecognizer;
/** 
 * @brief	Triggered when a gesture recognizer attempts to transition out of UIGestureRecognizerStatePossible.
 *
 * @param[in]	gestureRecognizer       The gesture recognizer.
 *
 * @return	<b>YES</b> means that this event has been handled by the event listener.
 *			<b>NO</b> means that the event listener did not handle this event.
 */
- (BOOL)onShouldBegin:(UIGestureRecognizer *)gestureRecognizer;
/**
 * @brief    Called before touchesBegan:withEvent: is called on the gesture recognizer for a new touch.
 *           return NO to prevent the gesture recognizer from seeing this touch
 *
 * @param[in]    gestureRecognizer       The gesture recognizer.
 * @param[in]    touch       A UITouch object represent touches event on the screen.
 *
 * @return    <b>YES</b> means that this event has been handled by the event listener.
 *            <b>NO</b> means that the event listener did not handle this event.
 */
- (BOOL)onPageGestureRecognizer:(int)pageIndex gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch;
@end

/** @brief	The draw event listener. */
@protocol IDrawEventListener <NSObject>
@required
/** 
 * @brief	Triggered when drawing on a specified page.
 *
 * @param[in]	pageIndex	Index of the specified page. Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 * @param[in]	context     The CGContext object.
 */
- (void)onDraw:(int)pageIndex inContext:(CGContextRef)context;
@end

/** @brief	The touch event listener. */
@protocol ITouchEventListener <NSObject>
@optional
/**
 * @brief	Triggered when the touches began.
 *
 * @param[in]	touches     A UITouch object represent touches event on the screen.
 * @param[in]	event       A UIEvent object represents an event in iOS.
 *
 * @return	<b>YES</b> means the touches has been handled successfully by extensions manager.
 *			<b>NO</b> means The extensions manager did not handle the touches.
 */
- (BOOL)onTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
/**
 * @brief	Triggered when the touches has moved.
 *
 * @param[in]	touches     A UITouch object represent touches event on the screen.
 * @param[in]	event       A UIEvent object represents an event in iOS.
 *
 * @return	<b>YES</b> means the touches has been handled successfully by extensions manager.
 *			<b>NO</b> means The extensions manager did not handle the touches.
 */
- (BOOL)onTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
/**
 * @brief	Triggered when the touches has ended.
 *
 * @param[in]	touches     A UITouch object represent touches event on the screen.
 * @param[in]	event       A UIEvent object represents an event in iOS.
 *
 * @return	<b>YES</b> means the touches has been handled successfully by extensions manager.
 *			<b>NO</b> means The extensions manager did not handle the touches.
 */
- (BOOL)onTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
/**
 * @brief	Triggered when the touches has been canceled.
 *
 * @param[in]	touches     A UITouch object represent touches event on the screen.
 * @param[in]	event       A UIEvent object represents an event in iOS.
 *
 * @return	<b>YES</b> means the touches has been handled successfully by extensions manager.
 *			<b>NO</b> means The extensions manager did not handle the touches.
 */
- (BOOL)onTouchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;
@end

/** @brief	The  UI extensions manager. */
@protocol FSPDFUIExtensionsManager <IGestureEventListener, IDrawEventListener, ITouchEventListener>
@optional
/**
 * @brief	Whether the view control should draw this annotation or not.
 *
 * @param[in]	annot     An annotation object.
 *
 * @return <b>YES</b> means the annotation is drew by view control, while <b>NO</b> means it will not been draw.
 */
- (BOOL)shouldDrawAnnot:(FSAnnot *)annot;
@end

/** @brief	The page organizer delegate, which handles moving/deleting/inserting pages..etc. */
@protocol FSPageOrganizerDelegate <NSObject>
/**
 * @brief    get file path to use in thumbnail
 *
 * @return   filepath
 */
-(NSString *)getDocumentFilePath ;
/**
 * @brief	Move the specifed pages to the destination page, the moved pages will be inserted after the destination page.
 *
 * @param[in]	sourcePageIndexes   The specified pages index array to be moved.
 * @param[in]	pageIndex           The page index to be inserted before.
 *
 * @return <b>YES</b> means success, while <b>NO</b> means fail.
 */
- (BOOL)movePagesFromIndexes:(NSArray<NSNumber *> *)sourcePageIndexes toIndex:(NSUInteger)pageIndex;
/**
 * @brief	Delete the specifed pages.
 *
 * @param[in]	pageIndexes     The specified pages index array to be deleted.
 *
 * @return <b>YES</b> means success, while <b>NO</b> means fail.
 */
- (BOOL)deletePagesAtIndexes:(NSArray<NSNumber *> *)pageIndexes;
/**
 * @brief	Rotate the specifed pages by 90 degree or -90 degree.
 *
 * @param[in]	pageIndexes     The specified pages index array to be rotated.
 * @param[in]	clockwise       If yes, the pages will be rotated by 90 degree, if no, the pages will be rotated by -90 degree.
 *
 * @return <b>YES</b> means success, while <b>NO</b> means fail.
 */
- (BOOL)rotatePagesAtIndexes:(NSArray<NSNumber *> *)pageIndexes clockwise:(BOOL)clockwise;
/**
 * @brief	Insert a new page from a specified image, the image will be converted to the new page.
 *
 * @param[in]	image       The specified image.
 * @param[in]	pageIndex	The page index for new page.<br>
 *                          If parameter <i>pageIndex</i> is equal to or less than 0, the new page will be inserted to the first. <br>
 *                          If parameter <i>pageIndex</i> is equal to or larger than current page count,
 *                          the new page will be inserted to the end.
 *
 * @return <b>YES</b> means success, while <b>NO</b> means fail.
 */
- (BOOL)insertPageFromImage:(UIImage *__nonnull)image atIndex:(NSUInteger)pageIndex;

/**
 * Insert new blank PDF pages to document, by index.
 * <p>
 * @param index A page index in current PDF document. This is used to specify where the imported pages will be inserted.<br>
 *                   If parameter <i>index</i> is less than 0, the new page will be inserted to the first. <br>
 *                   If parameter <i>index</i> is equal to or larger than current page count,
 *                   the new page will be inserted to the end.
 * @param width     Width of new page (unit is 1/72 inch,width is greater than 0).
 * @param height    Height of new page (unit is 1/72 inch,height is greater than 0).
 * @param style The syle of new page.Please refer to values starting from {@link FSPDFViewCtrl#PDF_PAGE_STYLE_TYPE_XXX}and
 *                   this should be one of these values.
 * @param color Color of new page.Format: 0xAARRGGBB.
 * @param rotation New page rotation value. Please refer to values starting from {@link FSPDFObjC::FSRotation#FSRotation0} and
 *                    this should be one of these values except {@link FSPDFObjC::FSRotation#FSRotationUnknown}
 * @param count The count of new pages to be inserted(count is greater than 0).
 * @return <CODE>YES</CODE> means success, while <CODE>NO</CODE> means failure.
 */
- (BOOL)insertPages:(int)index width:(float)width height:(float)height style:(PDF_PAGE_STYLE_TYPE)style color:(unsigned int)color rotation:(FSRotation)rotation count:(int)count;

/**
 * Insert new blank PDF pages to document, by index.
 * <p>
 * @param index A page index in current PDF document. This is used to specify where the imported pages will be inserted.<br>
 *                   If parameter <i>index</i> is less than 0, the new page will be inserted to the first. <br>
 *                   If parameter <i>index</i> is equal to or larger than current page count,
 *                   the new page will be inserted to the end.
 * @param pageSize PageSize type of new page. Please refer to values starting from {@link FSPDFObjC::FSPDFPageSize#FSPDFPageSizeLetter}and
 *                   this should be one of these values.
 * @param style The syle of new page.Please refer to values starting from {@link FSPDFViewCtrl#PDF_PAGE_STYLE_TYPE_XXX}and
 *                   this should be one of these values.
 * @param color Color of new page.Format: 0xAARRGGBB.
 * @param rotation New page rotation value. Please refer to values starting from {@link FSPDFObjC::FSRotation#FSRotation0} and
 *                    this should be one of these values except {@link FSPDFObjC::FSRotation#FSRotationUnknown}
 * @param count The count of new pages to be inserted(count is greater than 0).
 * @return <CODE>YES</CODE> means success, while <CODE>NO</CODE> means failure.
 */
- (BOOL)insertPages:(int)index pageSize:(FSPDFPageSize)pageSize style:(PDF_PAGE_STYLE_TYPE)style color:(unsigned int)color rotation:(FSRotation)rotation count:(int)count;

/**
 * @brief	Insert multiple new pages to the current document with the pdf pages copied from the source pdf document.
 *
 * @param[in]	document    The source pdf document.
 * @param[in]	sourcePagesIndexes   The specified pages index array to be copied.
 * @param[in]	flags			Options for importing pages.
 *								Please refer to {@link FSPDFDocImportPageFlags::FSPDFDocImportFlagNormal FSPDFDocImportPageFlags::FSPDFDocImportFlagXXX} and this can be one or a combination of them.
 * @param[in]	layerName		The name of non-selectable label or the prefix name of the non-selectable label to be shown in layer panel of application, in UTF-8 encoding.
 *								If parameter <i>flags</i> contains {@link FSPDFDocImportPageFlags::FSPDFDocImportFlagWithLayers}, this should not be empty and should be a valid string.
 *								If parameter <i>flags</i> does not contain {@link FSPDFDocImportPageFlags::FSPDFDocImportFlagWithLayers}, this string will be ignored.
 *								<ul>
 *								<li>If all the pages of source PDF document is to be imported to current document, all layers from source document will be grouped under a non-selectable label,
 *									and this string will be directly used as the label. </li>
 *								<li>If only part of pages of source PDF document is to be imported to current document, layers in the same page will be grouped under a single non-selectable label,
 *									and this string will be used as the prefix name of the label. The label will be like "layerName_Page_X". </li>
 *								</ul>
 * @param[in]   pageIndex   The specified page to be inserted before.
 *                          If parameter <i>pageIndex</i> is equal to or less than 0, the new page will be inserted to the first. <br>
 *                          If parameter <i>pageIndex</i> is equal to or larger than current page count,
 *                          the new page will be inserted to the end.
 * @param[in]   success     The callback will be called when the page insertion is successful.
 * @param[in]   error       The callback will be called when page insertion fails and error message info is thrown.
 */
- (void)insertPagesFromDocument:(FSPDFDoc *)document withSourceIndexes:(NSArray<NSNumber *> *)sourcePagesIndexes flags:(FSPDFDocImportPageFlags)flags layerName:(NSString * _Nullable)layerName atIndex:(NSUInteger)destinationIndex success:(void (^)(NSString *result))success error:(void (^)(NSString *errorInfo))error ;

@end


/** @brief    The excecption logger delegate. */
@protocol FSExceptionLoggerDelegate <NSObject>
/** @brief    Return the stack trace info.*/
-(void)stacktraceInfo:(NSString*)stackInfo ;
@end


/** 
 * @brief	Foxit PDF view control for viewing/editing/saving the PDF file. 
 *
 * @details	There are three coordinate systems for PDF viewer control:
 *			<ul>
 *			<li>
 *			Display View CoordiNate System: Which is the displaying area of view control, all the pages will be displayed on the display view. 
 *											Basically it is same frame as the PDF viewer control itself.
 *			</li>
 *			<li>
 *			Page View Coordinate System: Each PDF page is displayed on a UIView, so that it is same as UIView coordinate system.
 *			</li>
 *			<li>
 *			PDF Coordinate System: The PDF page coordinate system.
 *			</li>
 *			</ul>
 */
@interface FSPDFViewCtrl : UIView <IRotationEventListener, FSPageOrganizerDelegate>

/** @brief	The UI extensions manager. UI extensions manager will implement the UI related features such as annotation, outline.*/
@property (nonatomic, weak, nullable) id<FSPDFUIExtensionsManager> extensionsManager;
/** @brief	The current PDF document. */
@property (nonatomic, strong, nullable) FSPDFDoc *currentDoc;
/** @brief	Night mode. A convenient way to set {@link FSPDFViewControl::colorMode} to {@link FSRendererColorMode::FSRendererColorModeMapping} and set corresponding colors. */
@property (nonatomic, assign) BOOL isNightMode;
/**
 * @brief   Color mode.
 * @details Defaults to {@link FSRendererColorMode::FSRendererColorModeNormal}. Note that you need to set {@link FSPDFViewCtrl::mappingModeBackgroundColor} and {@link FSPDFViewCtrl::mappingModeForegroundColor} first when set color mode to {@link FSRendererColorMode::FSRendererColorModeMapping} or {@link FSRendererColorMode::FSRendererColorModeMappingGray}.
 */
@property (nonatomic, assign) FSRendererColorMode colorMode;
/** @brief   Background color for {@link FSRendererColorMode::FSRendererColorModeMapping} or {@link FSRendererColorMode::FSRendererColorModeMappingGray} color mode. */
@property (nonatomic, strong, nullable) UIColor *mappingModeBackgroundColor;
/** @brief   Foreground color for {@link FSRendererColorMode::FSRendererColorModeMapping} or {@link FSRendererColorMode::FSRendererColorModeMappingGray} color mode. */
@property (nonatomic, strong, nullable) UIColor *mappingModeForegroundColor;
/** @brief  Get or set the background color for reflow mode. Format: 0.0~1.0, 0.0~1.0, 0.0~1.0, 1.0 RGBA.*/
@property (nonatomic, strong, nullable) UIColor *reflowBackgroundColor;
/** @brief	Get or set position of display view from the bottom of control. */
@property (nonatomic, assign) int bottomOffset;
/** @brief	Whether or not should view control recover itself when runs out of memory. Default is YES. */
@property (nonatomic, assign) BOOL shouldRecover;
/** @brief	The file path of current document, which is from openDoc. */
@property (nonatomic, strong, readonly, nullable) NSString *filePath;
/** @brief  The maximum zoom scale. */
@property (nonatomic) CGFloat maxZoomLimit;
/** @brief  The minimum zoom scale. */
@property (nonatomic) CGFloat minZoomLimit;
/** @brief  Whether enable page flipping by touch border. Defaults is YES*/
@property (nonatomic, assign) BOOL enablePageFlippingByTouchBorder;
/** @brief  Whether keep same page zoom when turning pages. Defaults is YES*/
@property (nonatomic, assign) BOOL keepZoomRatio;
/** @brief  is change layout mode. */
@property (nonatomic) BOOL IsChangeLayoutMode;
/** @brief The night color mode */
@property (nonatomic, assign) FSNightColorMode nightColorMode;
/** @brief Minimum long press interval */
@property (nonatomic) NSTimeInterval minimumPressDuration;

#pragma mark - View control Initialize
/** 
 * @brief	Initialize the view control.
 *
 * @param[in]	frame	.
 *
 * @return	The view control instance.
 */
- (instancetype)initWithFrame:(CGRect)frame;

#pragma mark - Events
/** 
 * @brief	Register a document event listener.
 *
 * @param[in]	listener	A document event listener to be registered.
 */
- (void)registerDocEventListener:(id<IDocEventListener>)listener;
/** 
 * @brief	Register a page event listener.
 *
 * @param[in]	listener	A page event listener to be registered.
 */
- (void)registerPageEventListener:(id<IPageEventListener>)listener;
/** 
 * @brief	Register an event listener for scrolling page views.
 *
 * @param[in]	listener	An event listener for scrolling page views to be registered.
 */
- (void)registerScrollViewEventListener:(id<IScrollViewEventListener>)listener;
/** 
 * @brief	Register an event listener for page layout.
 *
 * @param[in]	listener	An event listener for page layout to be registered.
 */
- (void)registerLayoutEventListener:(id<ILayoutEventListener>)listener;
/** 
 * @brief	Register an event listener for gesture.
 *
 * @details	If method implementation of protocol returns <b>YES</b>, then the next listener will not receive the method call. 
 *
 * @param[in]	listener	An event listener for gesture to be registered.
 */
- (void)registerGestureEventListener:(id<IGestureEventListener>)listener;
/** 
 * @brief	Register an event listener for drawing page.
 *
 * @param[in]	listener	An event listener for drawing page to be registered.
 */
- (void)registerDrawEventListener:(id<IDrawEventListener>)listener;
/** 
 * @brief	Register an event listener for recovery from running out of memory.
 *
 * @param[in]	listener	An event listener for recovery from running out of memory to be registered.
 */
- (void)registerRecoveryEventListener:(id<IRecoveryEventListener>)listener;
/**
 * @brief    Register an event listener for view from apple.
 *
 * @param[in]    listener    An event listener to receive apple's interface.
 */
- (void)registerViewAppleEventListener:(id<IViewAppleEventListener>)listener;
/** 
 * @brief	Unregister an event listener for recovery from running out of memory.
 *
 * @param[in]	listener	An event listener for recovery from running out of memory to be unregistered.
 */
- (void)unregisteRecoveryEventListener:(id<IRecoveryEventListener>)listener;
/** 
 * @brief	Unregister an event listener for drawing page.
 *
 * @param[in]	listener	An event listener for drawing page to be unregistered.
 */
- (void)unregisterDrawEventListener:(id<IDrawEventListener>)listener;
/** 
 * @brief	Unregister an event listener for gesture.
 *
 * @param[in]	listener	An event listener for gesture to be unregistered.
 */
- (void)unregisterGestureEventListener:(id<IGestureEventListener>)listener;
/** 
 * @brief	Unregister a document event listener.
 *
 * @param[in]	listener	A document event listener to be unregistered.
 */
- (void)unregisterDocEventListener:(id<IDocEventListener>)listener;
/** 
 * @brief	Unregister a page event listener.
 *
 * @param[in]	listener	A page event listener to be unregistered.
 */
- (void)unregisterPageEventListener:(id<IPageEventListener>)listener;
/** 
 * @brief	Unregister an event listener for scrolling page views.
 *
 * @param[in]	listener	An event listener for scrolling page views to be unregistered.
 */
- (void)unregisterScrollViewEventListener:(id<IScrollViewEventListener>)listener;
/** 
 * @brief	Unregister an event listener for page layout.
 *
 * @param[in]	listener	An event listener for page layout to be unregistered.
 */
- (void)unregisterLayoutEventListener:(id<ILayoutEventListener>)listener;

/**
 * @brief    Unregister an event listener for view from apple.
 *
 * @param[in]    listener    An event listener to receive apple's interface.
 */
- (void)unregisterViewAppleEventListener:(id<IViewAppleEventListener>)listener;

#pragma mark - Open/Close/Save Document
/** 
 * @brief	Set the PDF document object to view control, then open the document.
 *
 * @param[in]	doc		A PDF document object.
 */
- (void)setDoc:(FSPDFDoc *)doc;

/**
 * @brief    Set the PDF document object and XFA document object to view control, then open the document.
 *
 * @param[in]    doc        A PDF document object.
 * @param[in]    xfadoc     A XFA document object.
 */
- (void)setPDFDoc:(FSPDFDoc *)doc XFADoc:(FSXFADoc *)xfadoc;

/** 
 * @brief	Get the current PDF document object from view control
 *
 * @return	Current PDF document object.
 */
- (FSPDFDoc *)getDoc;

/**
 * @brief    Get the permissions of the current PDF document.
 *
 * @return   Permissions of the current PDF document, which is combined of one or more enumeration type FSPDFDocUserPermissions.
 */
- (FSPDFDocUserPermissions)getDocPermissions;

/** @brief Check if the current document is opened with the owner access.*/
- (bool)isOwner;

/** @brief Check if the current document is PPDF format, which is Microsoft Rights Management PDF protected document. Usually with the .ppdf file extension. */
- (bool)isPPDF;

/** 
 * @brief	Open PDF document from a specified PDF file path.
 *
 * @param[in]	filePath	A PDF file full path.
 * @param[in]	password	The password string, used to load the PDF document content. It can be either user password or owner password.
 *							Set it to <b>nil</b> if the password is unknown.
 * @param[in]   completion  The callback will be called when current document object becomes available or the view control fail to open the document.
 */
- (void)openDoc:(NSString *)filePath password:(NSString *_Nullable)password completion:(void (^_Nullable)(FSErrorCode error))completion;
/** 
 * @brief	Open PDF document from a memory buffer.
 *
 * @param[in]	buffer		A memory buffer, containing the whole PDF file data.
 * @param[in]	password	The password string, used to load the PDF document content. It can be either user password or owner password.
 *							Set it to <b>nil</b> if the password is unknown.
 * @param[in]   completion  The callback will be called when document becomes available or fail to open the document.
 */
- (void)openDocFromMemory:(NSData *)buffer password:(NSString *_Nullable)password completion:(void (^_Nullable)(FSErrorCode error))completion;
/**
 * @brief    Open PDF document from a memory buffer.
 *
 * @param[in]    fileReader        A file reader callback, used to open the PDF fie..
 * @param[in]    password    The password string, used to load the PDF document content. It can be either user password or owner password.
 *                            Set it to <b>nil</b> if the password is unknown.
 * @param[in]   completion  The callback will be called when document becomes available or fail to open the document.
 */
- (void)openDocFromFileReader:(id<FSFileReaderCallback>)fileReader password:(NSString *_Nullable)password completion:(void (^_Nullable)(FSErrorCode error))completion;
/**
 * @brief	Close the document.
 *
 * @param[in]	cleanup		A callback function to clean up caller managed resources.
 */
- (void)closeDoc:(void (^_Nullable)(void))cleanup;

/** 
 * @brief	Save the document to a specified file path with saving flag.
 *
 * @param[in]	filePath	File path for the new saved PDF file.
 * @param[in]	flag		Document saving flags. 
 *
 * @return	<b>YES</b> means the saving is successfully finished, while <b>NO</b> means failure.
 */
- (BOOL)saveDoc:(NSString *)filePath flag:(FSPDFDocSaveFlags)flag;

/**
 * @brief    Save the document to a specified file writer with saving flag.
 *
 * @param[in]    fileWriter    File writer callback for the new saved PDF file.
 * @param[in]    flag        Document saving flags.
 *
 * @return    <b>YES</b> means the saving is successfully finished, while <b>NO</b> means failure.
 */
- (BOOL)saveDocToFileWriter:(id<FSFileWriterCallback>)fileWriter flag:(FSPDFDocSaveFlags)flag;

#pragma mark - Get Page
/** 
 * @brief	Get the page count of PDF document.
 *
 * @return	The count of page.
 */
- (int)getPageCount;
/** 
 * @brief	Get current page index.
 *
 * @return	Index of current page, starting from 0.
 */
- (int)getCurrentPage;
/** 
 * @brief	Get the page index at the specified point, in display view space.
 *
 * @param[in]	displayViewPt	Point in display view space.
 *
 * @return	Page index, starting from 0.
 */
- (int)getPageIndex:(CGPoint)displayViewPt;
/** 
 * @brief	Get the visible pages in current view control.
 *
 * @details	This method works with layout mode  {@link PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_SINGLE} and get continuous is true.
 *
 * @return	NSNumber array of visible pages' indexes.
 */
- (NSMutableArray *)getVisiblePages;
/** 
 * @brief	Check whether a specified page is visible or not.
 *
 * @details	This method works with layout mode {@link PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_SINGLE} and get continuous is true.
 *
 * @param[in]	pageIndex		Index of the specified page. Valid range: from 0 to (<i>count</i>-1).
 *								<i>count</i> is the page count.
 *
 * @return	<b>YES</b> means the specified page is visible.
 *			<b>NO</b> means the specified page is invisible.
 */
- (BOOL)isPageVisible:(int)pageIndex;

#pragma mark - Rotation View
/**
 * Rotates all pages in the document by using the specified degrees clockwise.
 *
 * @param rotation The rotation to be used.
 *                 Please refer to <CODE>{@link FSRotation }</CODE> values and this should be one of these values.
 */
-(void)rotateView:(int)rotation;
/**
 * Returns the rotation of the view.
 * Please refer to <CODE>{@link FSRotation}</CODE> values and this should be one of these values.
 */
-(int)getViewRotation;

#pragma mark - Page Navigation
/** 
 * @brief	Go to a specified page. 
 *
 * @param[in]	index			Page index. Valid range: from 0 to (<i>count</i>-1).
 *								<i>count</i> is the page count.
 * @param[in]	animated		<b>YES</b> means to use animation effects.
 *								<b>NO</b> means not to use animation effects.
 *
 * @return	<b>YES</b> means succeed.
 *			<b>NO</b> means failed.
 */
- (BOOL)gotoPage:(int)index animated:(BOOL)animated;
/** 
 * @brief	Go to a specified page, then move to a specified position in page. 
 *
 * @param[in]	index			Page index. Valid range: from 0 to (<i>count</i>-1).
 *								<i>count</i> is the page count.
 * @param[in]	point			Specified position.
 * @param[in]	animated		<b>YES</b> means to use animation effects.
 *								<b>NO</b> means not to use animation effects.
 *
 * @return	<b>YES</b> means succeed.
 *			<b>NO</b> means failed.
 */
- (BOOL)gotoPage:(int)index withDocPoint:(FSPointF *)point animated:(BOOL)animated;
/**
 * @brief    Go to a specified page.
 *
 * @param[in]    index                             Page index. Valid range: from 0 to (<i>count</i>-1).
 *                                 <i>count</i> is the page count.
 * @param[in]    animated                      <b>YES</b> means to use animation effects.
 *                                 <b>NO</b> means not to use animation effects.
 *
 * @param[in]    needJumpedNode         <b>YES</b> means to add the jumped node to page navigation stack.
 *                                 <b>NO</b> means not to add the jumped node to page navigation stack.
 *
 * @return    <b>YES</b> means succeed.
 *            <b>NO</b> means failed.
 */
- (BOOL)gotoPage:(int)index animated:(BOOL)animated needJumpedNode:(BOOL)needJumpedNode;
/**
 * @brief    Add the page jumped node to page navigation stack.
 *
 * @param[in]    indexOld                       The old page index for before the jump. Valid range: from 0 to (<i>count</i>-1).
 *                                 <i>count</i> is the page count.
 *
 * @param[in]    indexNew                       The new page index for after the jump. Valid range: from 0 to (<i>count</i>-1).
 *                                 <i>count</i> is the page count.
 *
 * @param[in]    animated                       <b>YES</b> means to use animation effects.
 *                                 <b>NO</b> means not to use animation effects.
 *
 */
- (void)addPageJumpedNode:(int)indexOld index:(int)indexNew animated:(BOOL)animated;
/** 
 * @brief	Go to the first page. 
 *
 * @param[in]	animated		<b>YES</b> means to use animation effects.
 *								<b>NO</b> means not to use animation effects.
 *
 * @return	<b>YES</b> means succeed.
 *			<b>NO</b> means failed.
 */
- (BOOL)gotoFirstPage:(BOOL)animated;
/** 
 * @brief	Go to the last page. 
 *
 * @param[in]	animated		<b>YES</b> means to use animation effects.
 *								<b>NO</b> means not to use animation effects.
 *
 * @return	<b>YES</b> means succeed.
 *			<b>NO</b> means failed.
 */
- (BOOL)gotoLastPage:(BOOL)animated;
/** 
 * @brief	Go to the next page. 
 *
 * @param[in]	animated		<b>YES</b> means to use animation effects.
 *								<b>NO</b> means not to use animation effects.
 *
 * @return	<b>YES</b> means succeed.
 *			<b>NO</b> means failed.
 */
- (BOOL)gotoNextPage:(BOOL)animated;
/** 
 * @brief	Go to the previous page. 
 *
 * @param[in]	animated		<b>YES</b> means to use animation effects.
 *								<b>NO</b> means not to use animation effects.
 *
 * @return	<b>YES</b> means succeed.
 *			<b>NO</b> means failed.
 */
- (BOOL)gotoPrevPage:(BOOL)animated;
/** 
 * @brief	Check if there it is a page view in the preceding of current page view on the page navigation stack.
 *
 * @details	PDF view control keeps a stack to track navigation on all pages.
 *
 * @return	<b>YES</b> means there is a previous page view.
 *			<b>NO</b> means there is no previous page view.
 */
- (BOOL)hasPrevView;
/** 
 * @brief	Check if there it is a page view next to the current page view on the page navigation stack.
 *
 * @details	PDF view control keeps a stack to track navigation on all pages.
 *
 * @return	<b>YES</b> means there is a next page view.
 *			<b>NO</b> means there is no next page view.
 */
- (BOOL)hasNextView;
/**
 * @brief	Clear prev and next stack.
 */
- (void)clearPrevNextStack;
/** 
 * @brief	Go to the previous view.
 *
 * @param[in]	animated		<b>YES</b> means to use animation effects.
 *								<b>NO</b> means not to use animation effects.
 */
- (void)gotoPrevView:(BOOL)animated;
/** 
 * @brief	Go to the next view.
 *
 * @param[in]	animated		<b>YES</b> means to use animation effects.
 *								<b>NO</b> means not to use animation effects.
 */
- (void)gotoNextView:(BOOL)animated;

#pragma mark - Reflow

/**
 * @brief	Get reflow mode.
 *
 * @return	Reflow mode. PDF_REFLOW_NONE if the current view mode is not reflow.
 */
- (PDF_REFLOW_REFLOWMODE)getReflowMode;
/**
 * @brief	Set reflow mode.
 *
 * @param[in]	reflowMode	reflow mode.
 */
- (void)setReflowMode:(PDF_REFLOW_REFLOWMODE)reflowMode;
#pragma mark - Scale
/**
 * @brief    Get the page scale.
 *
 * @return   page scale.
 */
- (float)getScale;
/**
 * @brief    Get the default page scale.
 *
 * @return    default page scale.
 */
- (float)getDefaultPageScale;
#pragma mark - Zoom
/** 
 * @brief	Get the zoom level. Valid range: from 1.0 to 20.0 for reflow mode, others 1.0 to 10.0.
 *
 * @details For the layout mode except reflow, 1.0 represents that the pdf pages would fit to the width of the view control.
 *
 * @return	Zoom level.
 */
- (float)getZoom;
/** 
 * @brief	Set the zoom level.
 *
 * @details For the layout mode except reflow, 1.0 represents that the pdf pages would fit to the width of the view control.
 *
 * @param[in]	zoom	New zoom level.Valid range: from 1.0 to 20.0 for reflow mode, others 1.0 to 10.0.
 */
- (void)setZoom:(float)zoom;
/**
 * @brief    Set the zoom level.
 *
 * @details For the layout mode except reflow, 1.0 represents that the pdf pages would fit to the width of the view control.
 *
 * @param[in]    zoom    New zoom level.Valid range: from 1.0 to 20.0 for reflow mode, others 1.0 to 10.0.
 * @param[in]    isWithSlider    Whether to use the slider tool directly.
 */
- (void)setZoom:(float)zoom withSlider:(BOOL)isWithSlider;
/** 
 * @brief	Zoom page from the specified position.
 *
 * @details For the layout mode except reflow, 1.0 represents that the pdf pages would fit to the width of the view control.
 *
 * @param[in]	zoom	New zoom level.Valid range: from 1.0 to 20.0 for reflow mode, others 1.0 to 10.0.
 * @param[in]	origin	A specified position, in display view space.
 */
- (void)setZoom:(float)zoom origin:(CGPoint)origin;

/**
 * @brief    get the zoom mode.
 *
 */
- (PDF_DISPLAY_ZOOMMODE)getZoomMode;
/** 
 * @brief	Set the zoom mode.
 *
 * @param[in]	zoomMode	New zoom mode.
 */
- (void)setZoomMode:(PDF_DISPLAY_ZOOMMODE)zoomMode;

#pragma mark - Display mode
/** 
 * @brief	Get the page layout mode.
 *
 * @return	Page layout mode.
 *			Please refer to {@link PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_UNKNOWN PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_XXX} values and it would be one of these values.
 */
- (PDF_LAYOUT_MODE)getPageLayoutMode;
/** 
 * @brief	Set the page layout mode.
 *
 * @param[in]	mode	Page layout mode.
 *						Please refer to {@link PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_UNKNOWN PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_XXX} values and it should be one of these values. 
 *						{@link PDF_LAYOUT_MODE::PDF_LAYOUT_MODE_UNKNOWN} will not work.
 */
- (void)setPageLayoutMode:(PDF_LAYOUT_MODE)mode;
/**
 * @brief    Get the page layout mode wether is continuous.
 *
 * @return <b>YES</b> means continuous mode, while <b>NO</b> means not continuous mode .
 */
- (BOOL)isContinuous;
/**
 * @brief    Set the page layout mode wether is continuous.
 *
 * @param[in]    isContinuous    <b>YES</b> means continuous mode, while <b>NO</b> means not continuous mode.
 */
- (void)setContinuous:(BOOL)isContinuous;
/**
 * @brief    Get the value wether is view sign history document.
 *
 * @return <b>YES</b> means view sign history document, while <b>NO</b> means not view sign history document .
 */
- (BOOL)isViewSignedDocument;
/**
 * @brief    Set the value wether is view sign history document.
 *
 * @param[in]    isViewSignedDocument    <b>YES</b> means sign history document, while <b>NO</b> means not sign history document.
 */
- (void)setViewSignedDocument:(BOOL)isViewSignedDocument;
#pragma mark - Crop mode
/**
 * @brief    Get crop mode inset.
 *
 * @param[in]    pageIndex    Page index of the cropped page. Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count.
 *                            -1 means the same rect to all pages.
 * @return    crop mode inset.
 */
- (UIEdgeInsets)getCropInsets:(int)pageIndex;
/**
 * @brief	Get crop mode.
 *
 * @return	crop mode. PDF_CROP_MODE_NONE if the current view mode is not crop.
 */
- (PDF_CROP_MODE)getCropMode ;
/**
 * @brief	Set the page crop mode.
 *
 * @details	Each page will be cropped separately according to the crop mode.
 *
 * @param[in]	mode	Crop mode. It should be one of following values:
 *						<ul>
 * 						<li>PDF_CROP_MODE::PDF_CROP_MODE_NONE means exiting crop mode.</li>
 *						<li>PDF_CROP_MODE::PDF_CROP_MODE_CONTENTSBOX means cropping margin according to bounding box of all contents.</li>
 * 						<li>PDF_CROP_MODE::PDF_CROP_MODE_DETECTION means cropping margin by detecting paths or images.</li>
 * 						<li>PDF_CROP_MODE::PDF_CROP_MODE_CUSTOMIZED means cropping margin with custom pages & rects from addCropPageRect:pdfRect:. Meaningful after addCropPageRect:pdfRect: is called.</li>
 *						</ul>
 *
 * @return <b>YES</b> means success, while <b>NO</b> means failure.
 */
- (BOOL)setCropMode:(PDF_CROP_MODE)mode;
/**
 * @brief	Set crop rect of the specified page, others are original as default.
 *
 * @details	It won't take effert until calling setCropMode:PDF_CROP_MODE::PDF_CROP_MODE_CUSTOMIZED.
 *
 * @param[in]	pageIndex	Page index of the cropped page. Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count.
 *							-1 means the same rect to all pages.
 * @param[in]	pdfRect     The crop rectangle on the PDF page, in pdf coordinate.
 *
 * @return <b>YES</b> means success, while <b>NO</b> means failure.
 */
- (BOOL)setCropPageRect:(int)pageIndex pdfRect:(FSRectF *_Nullable)pdfRect;

#pragma mark - Viewer preference
/** 
 * @brief	Set background color of viewer.
 *
 * @param[in]	color		New background color.
 */
- (void)setBackgroundColor:(UIColor *_Nullable)color;

#pragma mark - Viewer properties
/** 
 * @brief	Get the horizontal scroll position.
 *
 * @return	Horizontal scroll position.
 */
- (double)getHScrollPos;
/** 
 * @brief	Get the vertical scroll position.
 *
 * @return	Vertical scroll position.
 */
- (double)getVScrollPos;
/** 
 * @brief	Set the horizontal scroll position.
 *
 * @param[in]	pos         New horizontal scroll position.
 * @param[in]	animated	<b>YES</b> means to use animation effects.
 *							<b>NO</b> means not to use animation effects.
 */
- (void)setHScrollPos:(double)pos animated:(BOOL)animated;
/** 
 * @brief	Set the vertical scroll position.
 *
 * @param[in]	pos         New vertical scroll position.
 * @param[in]	animated	<b>YES</b> means to use animation effects.
 *							<b>NO</b> means not to use animation effects.
 */
- (void)setVScrollPos:(double)pos animated:(BOOL)animated;
/** 
 * @brief	Get the maximum horizontal scroll range.
 *
 * @return	Horizontal scroll range.
 */
- (double)getHScrollRange;
/** 
 * @brief	Get the maximum vertical scroll range.
 *
 * @return	Vertical scroll range.
 */
- (double)getVScrollRange;

/**
 * @brief    Scroll display view by the specified offset.
 * @param[in]   distanceX   The distance along the X axis that has been scrolled.
 * @param[in]   distanceY   The distance along the Y axis that has been scrolled.
 */
- (void)scrollDisplayView:(float)distanceX distanceY: (float)distanceY;

#pragma mark - Viewer dimension
/** 
 * @brief	Get the width of the display view.
 *
 * @return	Width of the display view.
 */
- (float)getDisplayViewWidth;
/** 
 * @brief	Get the height of the display view.
 *
 * @return	Height of the display view.
 */
- (float)getDisplayViewHeight;
/** 
 * @brief	Get the width of a specified page view.
 *
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *							The page specified by this index should be visible.
 *
 * @return	Width of the specified page view.
 */
- (float)getPageViewWidth:(int)pageIndex;
/** 
 * @brief	Get the height of a specified page view.
 *
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
*							The page specified by this index should be visible.
 *
 * @return	Height of the specified page view.
 */
- (float)getPageViewHeight:(int)pageIndex;
/** 
 * @brief	Get the display view. PDF pages and page transition effects are displayed on the display view.
 *
 * @return	Display view.
 */
- (UIView *)getDisplayView;
/** 
 * @brief	Get the page view by page index. 
 *
 * @details	Page view is used to draw PDF page content and annotations.
 *
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.<br>
 *							The page specified by this index should be visible.
 *
 * @return	The page UI view.
 */
- (UIView *)getPageView:(int)pageIndex;
/**
 * @brief	Get the overlay view on the page, specified by page index. 
 *
 * @details	Overlay view is on top of the page view，visual effects such as the highlight on text, will be drawn on it.
 *			To draw onto the overlay view, IDrawEventListener should be registered first.
 *
 * @param[in]	pageIndex	Page index. Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count. <br>
 *							The page specified by this index should be visible.
 *
 * @return	The overlay UI view.
 */
- (UIView *)getOverlayView:(int)pageIndex;

/**
 * @brief    Get the page container.
 *
 * @return   Page container.
 */
- (UIScrollView *)getPageContainer;

/**
 * @brief	Append a customized UI view to pdf page views.
 *
 * @details	User-defined view is appended as the new last page view. User events and interactions of the appended view is handled by themself.
            The pdf file is not changed. This method can be called multi-times.
 *
 * @param[in]	pageView	User-defined view to be appended as the last page view. 
                            Note that it should NOT be a subview of FSPDFViewControl, that is, it's invalid to append a view returned by {@link FSPDFViewControl::getPageView:} {@link FSPDFViewControl::getOverlayView:} or {@link FSPDFViewControl::getDisplayView:}.
 * @return <b>YES</b> means success, while <b>NO</b> means failure.
 */
- (BOOL)appendPageView:(UIView *)pageView;

/** @brief Stop the current gesture recognizer immediately */
- (void)stopCurrentGestureRecognizerShouldBegin;

#pragma mark - Coordinate Conversion
/** 
 * @brief	Convert the page view rectangle to display view coordination.
 *
 * @param[in]	rect        The rectangle on page view, in page view coordinate.
 * @param[in]	pageIndex   Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 *
 * @return	Rectangle on display page view.
 */
- (CGRect)convertPageViewRectToDisplayViewRect:(CGRect)rect pageIndex:(int)pageIndex;
/** 
 * @brief	Convert the display view rectangle to page view coordination.
 *
 * @param[in]	rect        The rectangle on display view, in display view coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
*                          The specified page should be visible.
 *
 * @return	Rectangle on page view.
 */
- (CGRect)convertDisplayViewRectToPageViewRect:(CGRect)rect pageIndex:(int)pageIndex;
/** 
 * @brief	Convert the display view point to page view point.
 *
 * @param[in]	point		The point on the display view, in display view coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 *
 * @return	Point on page view.
 */
- (CGPoint)convertDisplayViewPtToPageViewPt:(CGPoint)point pageIndex:(int)pageIndex;
/** 
 * @brief	Convert the page view point to display view point.
 *
 * @param[in]	point       The point on the page view, in page view coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 *
 * @return	Point on display page view.
 */
- (CGPoint)convertPageViewPtToDisplayViewPt:(CGPoint)point pageIndex:(int)pageIndex;
/** 
 * @brief	Convert the PDF page point to page view point.
 *
 * @param[in]	point		The point on the PDF Page, in PDF coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 *
 * @return	Point on page view.
 */
- (CGPoint)convertPdfPtToPageViewPt:(FSPointF *)point pageIndex:(int)pageIndex;
/** 
 * @brief	Convert the page view point to PDF page point.
 *
 * @param[in]	point       The point on the page view, in page view coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 *
 * @return	Point on PDF page.
 */
- (FSPointF *)convertPageViewPtToPdfPt:(CGPoint)point pageIndex:(int)pageIndex;
/** 
 * @brief	Convert the PDF rectangle to page view rectangle.
 *
 * @param[in]	rect		The rectangle on the PDF page, in pdf coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 *
 * @return	Page view rectangle.
 */
- (CGRect)convertPdfRectToPageViewRect:(FSRectF *)rect pageIndex:(int)pageIndex;
/** 
 * @brief	Convert the page view rectangle to PDF rectangle.
 *
 * @param[in]	rect        The rectangle on page view, in page view coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 *
 * @return	PDF rectangle.
 */
- (FSRectF *)convertPageViewRectToPdfRect:(CGRect)rect pageIndex:(int)pageIndex;
/** 
 * @brief	Get the display matrix of a specified page, which transforms from PDF coordinate to page view coordinate.
 *
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 *
 * @return	Display matrix.
 */
- (FSMatrix2D *)getDisplayMatrix:(int)pageIndex;

/**
 * @brief	Get the display matrix of a specified page from the origin point on page view, which transforms from PDF coordinate to page view coordinate.
 *
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *                          The specified page should be visible.
 * @param[in]   originPoint The origin point on the page view, in page view coordinate.
 *
 * @return	Display matrix.
 */
- (FSMatrix2D *)getDisplayMatrix:(int)pageIndex fromOrigin:(CGPoint)originPoint;

#pragma mark - Refresh

/** @brief If page content is currently being edited or annotation is reseting the appearance, caller should lock refreshing before editting is done. */
-(void)lockRefresh;
/** @brief Unlock refreshing. */
-(void)unlockRefresh;
/** 
 * @brief	Refresh a specified rectangle area on page, in page view coordinate.
 *
 * @param[in]	rect        The rectangle are on page, in page view coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 */
- (void)refresh:(CGRect)rect pageIndex:(int)pageIndex;
/**
 * @brief	Refresh a specified rectangle area on page, in page view coordinate.
 *
 * @param[in]	rect        The rectangle are on page, in page view coordinate.
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 * @param[in]   needRender  If YES, will render the specified PDF page, then refresh the overlay view; if NO, will refresh the overlay view only.
 */
- (void)refresh:(CGRect)rect pageIndex:(int)pageIndex needRender:(BOOL)needRender;
/** 
 * @brief	Refresh a specified page view.
 *
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 *
 */
- (void)refresh:(int)pageIndex;
/**
 * @brief	Refresh a specified page view.
 *
 * @param[in]	pageIndex	Page index.Valid range: from 0 to (<i>count</i>-1).
 *							<i>count</i> is the page count.
 * @param[in]   needRender  If YES, will render the specified PDF page, then refresh the overlay view; if NO, will refresh the overlay view only.
 */
- (void)refresh:(int)pageIndex needRender:(BOOL)needRender;
/** 
 * @brief	Refresh the display view.
 */
- (void)refresh;
/**
 * @brief    Refresh the overlay view.
 */
- (void)refreshOverlay;
/**
 * @brief	Do the recovering when Foxit PDF SDK runs out of memory.
 *
 * @details	Foxit PDF SDK will call this method automatically. 
 *			Caller should use it carefully, current reading status will be restored, but all the editing to document won't be 
 *          restored.
 */
+ (void)recoverForOOM;
/**
 * @brief    Set page space between adjacent pages in view , Only valid for PDF_LAYOUT_MODE_TWO and PDF_LAYOUT_MODE_TWO_XXX mode.
 *
 * @param[in]    pageSpace    Space of adjacent pages in view. default: 1. valid range: from 0 to 100;
 */
-(void)setPageSpacing:(int)pageSpace;
/**
 * @brief    Sets the vertical and horizontal spacing between adjacent pages in the view.
 *           Note: Currently, It supports in {@link PDFViewCtrl#PAGELAYOUTMODE_CONTINUOUS},
 *           {@link PDFViewCtrl#PAGELAYOUTMODE_FACING} and {@link PDFViewCtrl#PAGELAYOUTMODE_COVER} mode.
 *
 * @param[in]    pageSpace    Space of adjacent pages in view. valid range: from 0 to 10;
 *                            Note: The default value of the vertical spacing is 2,and the default value of the horizontal spacing is 1.
 *
 * @param[in]    direction    Used to decide which kind of direction spacing will be set.
 *                            Please refer to values starting from {@link PDFViewCtrl#FS_PAGESPACING_DIRECTION}
 *                            and this can be one or a combination of these values.
 */
-(void)setPageSpacing:(int)pageSpace direction:(FS_PAGESPACING_DIRECTION)direction;
/**
 * @brief    The exception logger is for collecting info of exceptions or crashes. It will catch the unhandled NSException and applciation-wide signals.
 *
 * @param[in]    logger      A protocal to be implemented for getting the exception info. If it is set to nil, then SDK will not catch the exceptions.
 */
+(void)setExceptionLogger:(nullable id<FSExceptionLoggerDelegate>) logger;

/**
 * @brief    Sets the edge insets of pdf page view.
 *
 * @param[in]    pageViewEdgeInsets     Edge insets value of pdf page view.
 *
 * @param[in]    moveOffset                     Whether to offset after setting page margins.
 */
- (void)setPageViewEdgeInsets:(UIEdgeInsets)pageViewEdgeInsets moveOffset:(BOOL)moveOffset;

@end

#pragma mark - XML Forms Architecture File
@interface FSPDFViewCtrl (xfa)
/** @brief Whether the current document is dynamic XFA. */
-(BOOL)isDynamicXFA;
/** @brief Return XFA document object if the current document is XFA, else return nil. */
-(FSXFADoc *)getXFADoc;
/**
 * @brief  Reload the XFA document when pages are added or deleted from the XFA document.
 *
 * @param[in]    page_view_event_type    The event such as adding/deleting pages.
 * @param[in]    pageIndexes             The related page indexes associate with event.
 */
-(BOOL)reloadXFADoc:(FSDocProviderCallbackPageViewEventType)page_view_event_type page_index:(NSArray<NSNumber *> *)pageIndexes;
@end

#pragma mark - Rights Management Services
@interface FSPDFViewCtrl (rms)
/*!
 Ask ADAL to handle URL response. You MUST implement this API in following cases:
 1. Your application is using brokered authentication (ADCredentialsType is set to AD_CREDENTIALS_AUTO and you have configured your application to use broker), AND
 2. You're using iOS 13 multiple window feature and your code implements UISceneDelegate instead of UIApplicationDelegate
 
 You should call this API from your UISceneDelegate implementation, for example:
 
 - (void)scene:(UIScene *)scene openURLContexts:(NSSet<UIOpenURLContext *> *)URLContexts
 {
     UIOpenURLContext *context = URLContexts.anyObject;
     NSURL *url = context.URL;
     NSString *sourceApplication = context.options.sourceApplication;
     
     [FSPDFViewCtrl handleADALResponse:url sourceApplication:sourceApplication];
 }
 
 Calling this API ensures that ADAL can receive tokens from the Microsoft Authenticator application.
 @return    YES if it is ADAL response and it was handled
            NO if it is not ADAL response or there was a failure in handling.
 */
+ (BOOL)handleADALResponse:(nonnull NSURL *)response sourceApplication:(nullable NSString *)sourceApplication;
/**
 * @brief	Set the app client id and server URL for encryption or decryption of RMS protected PDF file.
 *
 */
- (void)setRMSAppClientId:(nonnull NSString *)appClientId redirectURI:(nonnull NSString *)redirectURI;
/** @brief Check whether the current document is protected by RMS(Right Management Services). */
- (BOOL)isRMSProtected;
@end

#pragma mark - Open file async
@interface CacheFileOption : NSObject
/**
 * @brief  The cache file path. The cache path used to download the PDF file. If null or blank, the document will be stored in a default cache location.
 */
@property (nonatomic, strong, nullable) NSString *cacheFilePath;
/**
 * @brief Whether to download the full document and then open.
 */
@property (nonatomic, assign) BOOL isDownloadAll;

@end

@interface HttpRequestProperties : NSObject
/**
 * @brief  The properties of HttpRequestProperties class.
 */
@property (nonatomic, strong) NSMutableDictionary *properties;

/**
 * @brief Sets the general request property. If a property with the key alreadyexists, overwrite its value with the new value.
 *
 * @param key   The keyword by which the request is known(e.g., " {@code Accept}").
 *
 * @param value The value associated with the key.
 */
-(void) setRequestProperty:(NSString *)key Value:(NSString *)value ;

@end

@interface FSPDFViewCtrl (async)

/**
 * @brief    Open PDF document from a specified URL. This function is deprecated, it will be removed in future.
 *
 * @param[in]   url        PDF URL.
 * @param[in]   password   The password string, used to load the PDF document content. It can be either user password or owner password.
 *                         Set it to <b>nil</b> if the password is unknown.
 * @param[in]   completion  The callback will be called when current document object becomes available or the view control fail to open the document.
 *
 * Note that it will create a temporary file as cache for downloading the PDF file. The cache will be
 * removed after closing the document.
 */
- (void)openDocAtURL:(NSURL *)url password:(NSString *)password completion:(void (^)(FSErrorCode error))completion;
/**
 * @brief    Open PDF document from a specified URL.
 *
 * @param[in]   url        PDF URL.
 * @param[in]   password   The password string, used to load the PDF document content. It can be either user password or owner password.
 *                         Set it to <b>nil</b> if the password is unknown.
 * @param[in]   cacheOption  The cache option. Please refer to {@link FSCacheFileOption}.
 * @param[in]   completion  The callback will be called when current document object becomes available or the view control fail to open the document.
 *
 * Note that it will create a temporary file as cache for downloading the PDF file. The cache will be
 * removed after the document closed.
 */
- (void)openDocFromURL:(NSURL *)url password:(NSString *)password cacheOption:(nullable CacheFileOption *)cacheOption httpRequestProperties:(nullable HttpRequestProperties *)properties completion:(void (^)(FSErrorCode error))completion;

/**
 * @brief Clear the cache file.
 * @param url It should be a remote path.
 *
 */
-(void)clearCacheFile:(NSString *)url;

/**
 * @brief Clear all files cached by SDK.
 */
-(void)clearAllCacheFile;

@end

@interface FSPDFViewCtrl (fips)
/** * @brief Check that whether the view control works on the FIPS mode (Federal Information Processing Standard). FIPS mode support requires a special build from Foxit.  */
+(BOOL) fipsMode;
@end


@interface CERT_INFO : NSObject
@property (nonatomic, copy) NSString *certSerialNum;
@property (nonatomic, copy) NSString *certPublisher;
@property (nonatomic, copy) NSString *certStartDate;
@property (nonatomic, copy) NSString *certEndDate;
@property (nonatomic, copy) NSString *certEmailInfo;
@property (nonatomic, strong) FSDateTime *signDate;
@property (nonatomic, assign) const unsigned int *byteRangeArray;
@property (nonatomic, assign) int sizeofArray;
@property (nonatomic, assign) int ltvState;
@property (nonatomic, copy) NSDictionary *cerInfoDic;
@end

@interface DIGITALSIGNATURE_PARAM : NSObject
@property (nonatomic, copy) NSString *certFile;
@property (nonatomic, copy) NSString *certPwd;
@property (nonatomic, copy) NSString *subfilter;
@property (nonatomic, copy) NSString *signFilePath;
@property (nonatomic, copy) NSString *imagePath;
@property (nonatomic, strong) FSRectF *rect;
@property (nonatomic, copy) NSString *sigName;
@end

/**
 * @brief    Enumeration for certificate related error code.
 *
 */
typedef enum {
    PDF_CERT_ERROR_SUCESSS = 0,
    /** @brief    File format error or invalid file. */
    PDF_CERT_ERROR_FILE,
    /** @brief    Invalid password. */
    PDF_CERT_ERROR_PASSWORD
} PDF_CERT_ERROR_CODE;

@interface FSPDFCertUtil : NSObject
+(PDF_CERT_ERROR_CODE)getCertInfo:(NSString *) path password:(NSString *)pwd certInfo:(CERT_INFO *)info;
+(NSMutableArray *)getCertFromSignatureContent:(FSSignature *)signature ;
+(NSMutableDictionary *)getTrustCertificateInformation:(NSData *)certData ;
+(BOOL)isCertTrusted:(NSData *)cert toTrust:(NSData*)needBeTrustedCertData;
@end

NS_ASSUME_NONNULL_END
