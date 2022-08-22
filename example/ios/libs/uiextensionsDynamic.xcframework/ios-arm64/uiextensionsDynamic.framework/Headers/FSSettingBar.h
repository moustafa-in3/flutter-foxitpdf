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
 * @file	SettingBar.h
 * @details	The setting bar consists controls to set page layout, screen brightness, reflow, crop and so on.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol IRotationEventListener;
@class UIExtensionsManager;
@class FSPDFViewCtrl;
@class FSSettingBar;
/**
 * @brief	Enumeration for item types in setting bar.
 *
 * @details	Values of this enumeration should be used alone.
 */
typedef NS_ENUM(NSUInteger, SettingItemType) {
    /** @brief    Single page layout button. */
    SINGLE,
    /** @brief    Double page layout button. */
    DOUBLEPAGE,
    /** @brief    Cover page layout button. */
    COVERPAGE,
    /** @brief    Day mode button. */
    DAYMODE,
    /** @brief    Page color mode button. */
    PAGECOLOR,
    /** @brief    Night mode button. */
    NIGHTMODE,
    /** @brief    Continuous page layout button. */
    CONTINUOUS,
    /** @brief  Fitpage button. */
    FITPAGE,
    /** @brief  Fitwidth button. */
    FITWIDTH,
    /** @brief    Reflow button. */
    REFLOW,
    /** @brief    Crop page button. */
    CROPPAGE,
    /** @brief  Speak button. */
    SPEECH,
    /** @brief  Auto flip button. */
    AUTOFLIP,
    /** @brief  rotate button. */
    ROTATE,
    /** @brief  Pan&zoom button. */
    PANZOOM,
};

/** @brief    application life cycle listener. */
@protocol IAppLifecycleListener <NSObject>
@optional
/** @brief    triggered when application will resign active. */
- (void)applicationWillResignActive:(UIApplication *)application;
/** @brief    triggered when application did enter the background. */
- (void)applicationDidEnterBackground:(UIApplication *)application;
/** @brief    triggered when application did enter the foreground. */
- (void)applicationWillEnterForeground:(UIApplication *)application;
/** @brief    triggered when application did become active. */
- (void)applicationDidBecomeActive:(UIApplication *)application;
@end


/** @brief	SettingBar delegate. */
@protocol FSSettingBarDelegate <NSObject>
@optional
// Methods for notification of selection/deselection events.
/**
 * @brief	Triggered when select single page layout.
 *
 * @param[in]	settingBar      The setting bar.
 */
- (void)settingBarSinglePageLayout:(FSSettingBar *)settingBar;
/**
 * @brief	Triggered when select continuous page layout.
 *
 * @param[in]	settingBar      The setting bar.
 */
- (void)settingBarContinuousLayout:(FSSettingBar *)settingBar;
/**
 * @brief	Triggered when select double page layout.
 *
 * @param[in]	settingBar      The setting bar.
 */
- (void)settingBarDoublePageLayout:(FSSettingBar *)settingBar;
/**
 * @brief	Triggered when select double page layout with cover.
 *
 * @param[in]	settingBar      The setting bar.
 */
- (void)settingBarCoverPageLayout:(FSSettingBar *)settingBar;
/**
 * @brief	Triggered when select thumbnail item.
 *
 * @param[in]	settingBar      The setting bar.
 */
- (void)settingBarThumbnail:(FSSettingBar *)settingBar;
/**
 * @brief	Triggered when select reflow item.
 *
 * @param[in]	settingBar      The setting bar.
 */
- (void)settingBarReflow:(FSSettingBar *)settingBar;
/**
 * @brief	Triggered when select crop page mode.
 *
 * @param[in]	settingBar      The setting bar.
 */
- (void)settingBarCrop:(FSSettingBar *)settingBar;
/**
 * @brief    Triggered when speech page text mode.
 *
 * @param[in]    settingBar      The setting bar.
 */
- (void)settingBarSpeech:(FSSettingBar *)settingBar;
/**
 * @brief	Triggered when select pan&zoom mode.
 *
 * @param[in]	settingBar      The setting bar.
 */
- (void)settingBarPanAndZoom:(FSSettingBar *)settingBar;
/**
 * @brief	Triggered when select lock screen item.
 *
 * @param[in]	settingBar      The setting bar.
 * @param[in]	isLockScreen    Whether to lock screen rotation.
 */
- (void)settingBar:(FSSettingBar *)settingBar isLockScreen:(BOOL)isLockScreen;
/**
 * @brief	Triggered when select night mode item.
 *
 * @param[in]	settingBar      The setting bar.
 * @param[in]	isNightMode     Night mode or not.
 */
- (void)settingBar:(FSSettingBar *)settingBar isNightMode:(BOOL)isNightMode;
/**
 * @brief    Triggered when select page color mode item.
 *
 * @param[in]    settingBar      The setting bar.
 */
- (void)settingBarPageColor:(FSSettingBar *)settingBar;
/**
 * @brief    Triggered when select fitpage item.
 *
 * @param[in]    settingBar      The setting bar.
 */
- (void)settingBarFitPage:(FSSettingBar *)settingBar;
/**
 * @brief    Triggered when select fitwidth item.
 *
 * @param[in]    settingBar      The setting bar.
 */
- (void)settingBarFitWidth:(FSSettingBar *)settingBar;
/**
 * @brief    Triggered when select rotate item.
 *
 * @param[in]    settingBar      The setting bar.
 */
- (void)settingBarRotate:(FSSettingBar *)settingBar;
/**
 * @brief    Triggered when select autoflip item.
 *
 * @param[in]    settingBar      The setting bar.
 */
- (void)settingBarAutoFlip:(FSSettingBar *)settingBar;
/**
 * @brief    Triggered when setting bar size is changed.
 *
 * @param[in]    settingBar      The setting bar.
 */
- (void)settingBarDidChangeSize:(FSSettingBar *)settingBar;

@end

/** @brief Setting bar is actived by tapping "View" item on the bottom bar. */
@interface FSSettingBar : NSObject <IAppLifecycleListener>
/** @brief Content view for setting bar. */
@property (nonatomic, strong) UIView *contentView;
/** @brief Get/Set delegate for setting bar. */
@property (nonatomic, weak) id<FSSettingBarDelegate> delegate;

/**
 * @brief  Deprecated, use isItemHidden instead.
 * Get setting bar items show/hide status.
 */
- (NSMutableDictionary *)getItemHiddenStatus;

/** @brief  Check if item is visible or not. */
- (BOOL)isItemHidden:(SettingItemType) type;

/**
 * @brief	Hide or show item in setting bar.
 *
 * @param[in]	itemType     Item type. Please refer to {@link SettingItemType::SINGLE SettingItemType::XXX} values and this should be one of these values.
 */
- (void)setItem:(SettingItemType)itemType hidden:(BOOL)hidden;
/**
 * @brief	Update layout of items in setting bar.
 */
- (void)updateBtnLayout;
@end
