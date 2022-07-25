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

@class FSMenuItem;
@class FSMenuControl;

/** @brief The scene of menucontrol show. */
typedef NS_ENUM(NSUInteger, FSMenuControlScene) {
    ///< The scene of menucontrol show for selected text.
    FSMenuControlSceneSelectedText,
    ///< The scene of menucontrol show for clicked in blank space.
    FSMenuControlSceneBlankSpace,
};

/** @brief The delegate of menucontrol. */
@protocol FSMenuControlDelegate <NSObject>

/** @brief The delegate method for menucontrol will show.
 *
 * @param[in]    menuControl       The menucontrol for show.
 * @param[in]    menuControlScene        The scene of menucontrol for show.
 *
 */
- (void)menuControlWillShow:(FSMenuControl *)menuControl menuControlScene:(FSMenuControlScene)menuControlScene;

@end

/** @brief The  menucontrol. */
@interface FSMenuControl : NSObject
/** @brief The  menuitems for add when menucontrol will show. */
@property (nonatomic, copy) NSArray<FSMenuItem*> *menuItems;
/** @brief The  pageIndex when menucontrol will show. */
@property (nonatomic, assign) int pageIndex;
/** @brief The  displayPoint when menucontrol will show. */
@property (nonatomic, assign) CGPoint displayPoint;
@end

NS_ASSUME_NONNULL_END
