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

NS_ASSUME_NONNULL_BEGIN

@interface ThumbnailModule : NSObject<IModule>
/**
 * @brief Intialize thumbnail module.
 *
 * @param[in]    extensionsManager    The extensions manager.
 *
 * @return    The thumbnail module.
 */
- (instancetype)initWithExtensionsManager:(UIExtensionsManager *)extensionsManager;

/** @brief Show thumbnails to switch and manipulate pages. */
- (void)showThumbnailView;

/**
 * @brief Get currnet doc for selected page Indexs.
 *
 * @return    The currnet doc for selected page Indexs .
 */
- (FSPDFDoc *)getCurrnetDocForSelectedPageIndexs;

/**
 * @brief Insert  pdf documen from the path.
 * @param[in]   path    The  pdf document the path.
 * @param[in]   success     The callback will be called when the page insertion is successful.
 * @param[in]   error       The callback will be called when page insertion fails and error message info is thrown.
 */
- (void)improtDocumentFromPath:(NSString *)path success:(void (^)(NSString *result))success error:(void (^)(NSString *errorInfo))error;
@end

NS_ASSUME_NONNULL_END
