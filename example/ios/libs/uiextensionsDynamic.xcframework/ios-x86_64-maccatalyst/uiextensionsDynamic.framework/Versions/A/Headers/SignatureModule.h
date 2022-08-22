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

#import <Foundation/Foundation.h>

@interface SignatureModule : NSObject <IDocEventListener, IToolEventListener>

/** @brief Get signature view top bar*/
@property (nonatomic, strong, getter=getSignatureViewTopBar, readonly) FSMainToolbar *signatureViewTopBar;
/** @brief Get signature view has changed call back*/
@property (nonatomic, copy) void (^signatureViewHasChanged)(BOOL hasChanged);
/**
 * @brief Intialize thumbnail module.
 *
 * @param[in]    extensionsManager    The extensions manager.
 *
 * @return    The signature module.
 */
- (instancetype)initWithExtensionsManager:(UIExtensionsManager *)extensionsManager;

/**
 * @brief Get currnet signature view Image
 *
 * @return    The currnet signature view Image.
 */
- (UIImage *)getSignatureViewImage;
@end
