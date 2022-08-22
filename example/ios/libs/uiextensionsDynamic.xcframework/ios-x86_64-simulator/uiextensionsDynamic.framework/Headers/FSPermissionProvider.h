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

typedef NS_ENUM(NSUInteger, FSPermissionState) {
    ///< The permission state is to show
    FSPermissionStateShow,
    ///< The permission state is no permission
    FSPermissionStateNo,
    ///< The permission state is to hide
    PermissionStateHide,
};

typedef NS_ENUM(NSUInteger, FSFunction) {
    ///< The function is mobile delete multimedia annotation
    FSFunctionMultiMediaEdit,
    ///< The function is edit document Information
    FSFunctionDocInfoEdit,
    ///< The function is edit
    FSFunctionEdit,
    ///< The function is reduce
    FSFunctionReduce,
    ///< The function is pdf sign and add certificate file function
    FSFunctionPDFDigitalSignAdd,
    ///< The function is RMS encryption function
    FSFunctionRMS,
    FSFunctionDigitalSignField,
    FSFunctionRedaction,
    FSFunctionCanSaveToLocal,
    FSFunctionStandEncrypt,
    FSFunctionFlatten,
};

typedef void(^CheckPermissionState)(FSPermissionState state);

@interface FSPermissionProvider : NSObject

/** @brief    check the permission with callback
 *
 * @param[in]    function        The  function of check permission.
 * @param[in]    checkPermissionState   the callback function of check the permission
 */
- (void) checkPermission:(FSFunction)function checkPermissionState:(CheckPermissionState)checkPermissionState;

- (BOOL) checkPermission:(FSFunction)function;
@end

NS_ASSUME_NONNULL_END
