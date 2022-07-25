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

#ifndef SpeechModule_h
#define SpeechModule_h

#import <Foundation/Foundation.h>

@protocol IModule;
@interface SpeechModule : NSObject<IModule>

/** @brief Get/Set the the reading speed. */
@property (nonatomic, assign) float readingSpeed;
/** @brief Whether to automatically adjust the next page. */
@property (nonatomic, assign) BOOL autoNextPage;

@end

#endif /* SpeechModule_h */

