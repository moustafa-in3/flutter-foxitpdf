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
 * @file	PanelController.h
 * @details	The panel controller consists panels of annotation, outline and so on.
 */
#import <Foundation/Foundation.h>
#import "PanelHost.h"
@class UIExtensionsManager;
@class FSPanelController;

/** @brief Panel hidden event listener. */
@protocol IPanelChangedListener <NSObject>
/**
 * @brief	Triggered when panel is hidden or shown.
 *
 * @param[in]	isHidden	Whether is hidden or not.
 */
- (void)onPanelChanged:(BOOL)isHidden;

@end


/** @brief Panel controller. */
@interface FSPanelController : UIViewController

/** @brief panel implementation, for internal use. */
@property (nonatomic, strong) PanelHost *panel;
/** @brief Whether to hide the panel control, set to YES to hide.*/
@property (nonatomic, assign) BOOL isHidden;
/**
 * @brief	Initialize the panel controller.
 *
 * @param[in]	extensionsManager	The extensions manager.
 *
 * @return	The panel controller instance.
 */
- (instancetype)initWithExtensionsManager:(UIExtensionsManager *)extensionsManager;

/** @brief Deprecated, use isPanelHidden instead.
 * get panels show/hide status
 */
-(NSMutableDictionary *)getItemHiddenStatus;

/** @brief  Get the specified panel by type. */
- (id<IPanelSpec>)getPanel:(FSPanelType) type;

/** @brief  Check if the specific panel is visible or not. */
- (BOOL)isPanelHidden:(FSPanelType) type;

/**
 * @brief	Hide or show panel of a specific type.
 *
 * @param[in]	isHidden	Whether is hidden or not.
 * @param[in]	type        Panel type. Please refer to {@link FSPanelType::FSPanelTypeAnnotation FSPanelType::FSPanelTypeXXX} values and it would be one of these values.
 */
- (void)setPanelHidden:(BOOL)isHidden type:(FSPanelType)type;
/**
 * @brief	Register a panel hidden event listener.
 *
 * @param[in]	listener	A panel hidden event listener.
 */
- (void)registerPanelChangedListener:(id<IPanelChangedListener>)listener;
/**
 * @brief	Unregister a panel hidden event listener.
 *
 * @param[in]	listener	A panel hidden event listener.
 */
- (void)unregisterPanelChangedListener:(id<IPanelChangedListener>)listener;

@end
