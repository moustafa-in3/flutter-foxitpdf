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
 * @file    MoreView.h
 * @details    The definition of the more view. Click the "more" button on the top tool bar to see the more view.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FSUtilities.h"
NS_ASSUME_NONNULL_BEGIN

/** brief Tags of the group and menu, arranged according to the value of the tag. */
/** brief Tag of the protect group.  Its value is 10.*/
FS_EXTERN int const TAG_GROUP_PROTECT;
/** brief Tag of the redaction menu.  Its value is 10.*/
FS_EXTERN int const TAG_ITEM_REDACTION;
/** brief Tag of the password menu.  Its value is 20.*/
FS_EXTERN int const TAG_ITEM_PASSWORD;
/** brief Tag of the certificate menu.  Its value is 30.*/
FS_EXTERN int const TAG_ITEM_CERTIFICATE;

/** brief Tag of the comments&fields group.  Its value is 20.*/
FS_EXTERN int const TAG_GROUP_COMMENT_FIELD;
/** brief Tag of the importComments menu.  Its value is 40.*/
FS_EXTERN int const TAG_ITEM_IMPORTCOMMENT;
/** brief Tag of the exportComments menu.  Its value is 50.*/
FS_EXTERN int const TAG_ITEM_EXPORTCOMMENT;
/** brief Tag of the summarizeComments menu.  Its value is 60.*/
FS_EXTERN int const TAG_ITEM_SUMARIZECOMMENT;
/** brief Tag of the resetFromFields menu.  Its value is 70.*/
FS_EXTERN int const TAG_ITEM_RESETFORM;
/** brief Tag of the importFromData menu.  Its value is 80.*/
FS_EXTERN int const TAG_ITEM_IMPORTFORM;
/** brief Tag of the exportFromData menu.  Its value is 90.*/
FS_EXTERN int const TAG_ITEM_EXPORTFORM;

/** brief Tag of the individual saveAs  menu.  Its value is 110.*/
FS_EXTERN int const TAG_ITEM_SAVE_AS;
/** brief Tag of the individual reduceFileSize  menu.  Its value is 120.*/
FS_EXTERN int const TAG_ITEM_REDUCEFILESIZE;
/** brief Tag of the individual print  menu.  Its value is 130.*/
FS_EXTERN int const TAG_ITEM_WIRELESSPRINT;
/** brief Tag of the individual flatten  menu.  Its value is 140.*/
FS_EXTERN int const TAG_ITEM_FLATTEN;
/** brief Tag of the individual screen  menu.  Its value is 150.*/
FS_EXTERN int const TAG_ITEM_SCREENCAPTURE;

@protocol IMoreMenuViewListener <NSObject>
- (void)onMoreMenuChanged:(BOOL)isHidden;
@end

/** @brief Callback for click action. */
typedef void (^CancelCallback)(void);

@protocol MoreItemProtocol;
/** brief Protocol for menu callback action. */
@protocol MoreItemActionProtocol <NSObject>
/** brief Callback triggered when click on a group/memu item. */
- (void)onClick:(id<MoreItemProtocol>)item;
@end

/** brief Protocol for group/menu callback action. */
@protocol MoreItemProtocol <NSObject>
/** brief The menu tag.*/
@property (nonatomic, assign) NSUInteger tag;
/** brief The menu title text.*/
@property (nonatomic, strong) NSString *title;
@end

/** brief Definition for menu item.*/
@interface MoreMenuItem : NSObject <MoreItemProtocol>
/** brief The menu tag.*/
@property (nonatomic, assign) NSUInteger tag;
/** brief The menu title text.*/
@property (nonatomic, strong) NSString *title;
/** brief The menu icon id. Unused.*/
@property (nonatomic, assign) NSInteger iconId;
/** brief The menu icon.*/
@property (nonatomic, strong) UIImage *image;
/** brief The menu item is enabled or not.*/
@property (nonatomic, assign) BOOL enable;
/** brief The callback action associated with this menu item.*/
@property (nonatomic, weak) id<MoreItemActionProtocol> callBack;
/** brief The custom view for item. Unused.*/
@property (nonatomic, strong) UIView *menuView;
@end

/** @brief The menu group. */
@interface MoreMenuGroup : NSObject <MoreItemProtocol>
/** @brief The tag for menu group.*/
@property (nonatomic, assign) NSUInteger tag;
/** @brief The title for menu group.*/
@property (nonatomic, strong) NSString *title;
/** @brief Get the menu items.*/
- (NSMutableArray *)getItems;
/** brief The callback action associated with this Group.*/
@property (nonatomic, weak) id<MoreItemActionProtocol> callBack;
/** @brief Set the menu items.*/
- (void)setItems:(NSMutableArray *)arr;
@end

/** brief Menu view for "more menu". */
@interface MoreMenuView : NSObject
/** brief Add a new menu group. */
- (void)addGroup:(MoreMenuGroup *)group;
/** brief Remove menu group by group tag.*/
- (void)removeGroup:(NSUInteger)tag;
/** brief Get menu group by group tag.*/
- (MoreMenuGroup *)getGroup:(NSUInteger)tag;
/** brief Add a new memu item on the specified group. */
- (void)addMenuItem:(NSUInteger)groupTag withItem:(MoreMenuItem *)item;
/** brief Remove a existing memu item from the specified group. */
- (void)removeMenuItem:(NSUInteger)groupTag WithItemTag:(NSUInteger)itemTag;
/** brief Add a new memu item on the individual group. */
- (void)addIndividualMenuItem:(MoreMenuItem *)item;
/** brief Remove a existing memu item from the individual group. */
- (void)removeIndividualMenuItemWithTag:(NSUInteger)itemTag;
/** brief Get a existing memu item from the individual group. */
- (MoreMenuItem*)getIndividualMenuItemWithTag:(NSUInteger)itemTag;
/** brief Set visible or invisible state  from the individual group. */
- (void)setIndividualMenuItemHiddenWithItemTag:(NSUInteger)itemTag hidden:(BOOL)isHidden;
/** brief Get the content view for the menu view. */
- (UIView *)getContentView;
/** brief Set the title for the menu view. */
- (void)setMenuTitle:(NSString *)title;
/** brief Reload the data for this menu view, which is based on a table view. */
- (void)reloadData;
/** brief Set visible or invisible state for specified menu group. */
- (void)setMoreViewItemHiddenWithGroup:(NSUInteger)groupTag hidden:(BOOL)isHidden;
/** brief Set visible or invisible state for specified menu item on specified menu group. */
- (void)setMoreViewItemHiddenWithGroup:(NSUInteger)groupTag andItemTag:(NSUInteger)itemTag hidden:(BOOL)isHidden;
/** brief Set visible or invisible state for title bar of more view. */
- (void)setTitleBarHidden:(BOOL)isHidden;

- (void)registerEventListener:(id<IMoreMenuViewListener>)listener;
- (void)unregisterEventListener:(id<IMoreMenuViewListener>)listener;
@end

NS_ASSUME_NONNULL_END
