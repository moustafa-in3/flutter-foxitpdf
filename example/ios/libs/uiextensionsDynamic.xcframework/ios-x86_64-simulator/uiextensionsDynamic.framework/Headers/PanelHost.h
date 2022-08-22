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
 * @file    PanelHost.h
 * @details    Panel host manage all the panels including annoation, attachment, outline, bookmark.. The caller may add or remove the specified panel on the panel host. The panels will be displayed when the panel button on the bottom bar is pressed.
 */

#import <UIKit/UIKit.h>

/** @brief Panel types. */
typedef NS_ENUM(NSUInteger, FSPanelType) {
    /** @brief Annotation panel type. */
    FSPanelTypeAnnotation = 1,
    /** @brief Attachment panel type. */
    FSPanelTypeAttachment,
    /** @brief Outline panel type. */
    FSPanelTypeOutline,
    /** @brief Reading bookmark panel type. */
    FSPanelTypeReadingBookmark,
    /** @brief Reading digital signature panel type. */
    FSPanelTypeDigitalSignature,
    /** @brief Custom panel type. */
    FSPanelTypeCustom,
};

/** @brief The custom UI, which acts as a button. */
@interface TabItem : NSObject
@property (nonatomic, strong) UIImage *image;
@property (nonatomic, strong) UIImage *selectImage;
@end

/** For adding a new panel type, caller could implement this protocal. */
@protocol IPanelSpec <NSObject>
/** @brief Return one of the predefined enumeration value FSPanelType. If the caller will implement a new panel type, then the return value should not conflict with the predefined values, or there will be undefined behavious. */
- (int)getType;
- (UIView *)getTopToolbar;
- (UIView *)getContentView;
- (TabItem *)getTabItem;
- (void)onActivated;
- (void)onDeactivated;
@end

/** @brief Panel UI implementation. */
@interface PanelHost : NSObject
@property (nonatomic, strong) NSMutableArray<id<IPanelSpec>> *specs;
@property (nonatomic, strong) id<IPanelSpec> currentSpec;
@property (nonatomic, strong) UIView *contentView;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (void)addSpec:(id<IPanelSpec>)spec;
- (void)insertSpec:(id<IPanelSpec>)spec atIndex:(int)index;
- (void)removeSpec:(id<IPanelSpec>)spec;
/** @brief Reload the panel segment view interface. If a panel is added or removed, then this function should be called.*/
- (void)reloadData;
@end
