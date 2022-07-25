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

typedef NS_ENUM(NSUInteger, FSMenuViewType) {
    ///< The thumbnail controller clicks on the insertBlankPage pop-up view
    FSMenuViewTypeThumbnailInsertBlankPagePop = 0,
    ///< Extraction controller
    FSMenuViewTypeExtract,
    ///< Save as controller
    FSMenuViewTypeSaveAs,
};
@class FSMenuItem;
/** @brief Callback for click action. */
typedef void (^FSMenuItemAction)(FSMenuItem *_item);

/** brief Definition for custom item.*/
@interface FSMenuItem : NSObject
/** brief Get  index of the  custom Item in the group It will be NSNotFound if it is not added*/
@property (nonatomic, assign, readonly) NSUInteger index;
/** brief The custom title text.*/
@property (nonatomic, copy) NSString *title;
/** brief The custom item image.*/
@property (nonatomic, strong) UIImage *image;
/** brief The callback action associated with this menu item.*/
@property (nonatomic, copy, nullable) FSMenuItemAction action;
/**
 * @brief Intialize custom Item.
 *
 * @param[in]    title        The Item title.
 * @param[in]    image        The custom item image
 * @param[in]    action      The custom item action callback
 *
 * @return    The custom Item instance.
 */
- (instancetype)initWithTitle:(NSString *)title image:(UIImage *)image action:(FSMenuItemAction)action;
@end
/** @brief The custom item group. */
@interface FSMenuItemGroup : NSObject
/** @brief Get  index of the  custom group in the view. It will be NSNotFound if it is not added*/
@property (nonatomic, assign, readonly) NSUInteger index;
/** @brief The title for custom group.*/
@property (nonatomic, copy) NSString *title;
/** @brief Set/Get the custom items.*/
@property (nonatomic, strong) NSMutableArray<FSMenuItem *> * items;
/**
 * @brief Intialize custom group.
 *
 * @param[in]    title        The group title.
 * @param[in]    items        The custom group items
 *
 * @return    The custom group instance.
 */
- (instancetype)initWithTitle:(nullable NSString *)title items:(NSArray <FSMenuItem *> *)items;
@end

@protocol FSMenuView <NSObject>

@required
/** @brief Whether to be present by the RDK.*/
- (BOOL)shouldPresentByRDK;

@optional
/** @brief If shouldPresentByRDK is YES it will be provided by the RDK.*/
@property (nonatomic, weak) UIViewController *containerController;
/** @brief If shouldPresentByrdK is Yes the RDK will need getCustomView.*/
- (UIView *)getCustomView;
/** @brief If shouldPresentByrdK is NO the RDK will respond*/
- (void)presentActionInMenuView;
@end

@interface FSMenuViewManager : NSObject

/** @brief Disable the default initialization.*/
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * @brief Set id<FSMenuView> for menu vew type. If the current menu view uses the current interface, the menu group is invalidated and the id<FSMenuView> is responsible for all behavior.
 *
 * @param[in]    menuView        The  id<FSMenuView>.
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 */
- (void)setMenuView:(id<FSMenuView>)menuView forMenuViewType:(FSMenuViewType)menuViewType;
/**
 * @brief Get id<FSMenuView>  for menu view type.
 *
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 * @return     The id<FSMenuView> .
 */
- (id<FSMenuView>)getMenuViewForMenuViewType:(FSMenuViewType)menuViewType;

/**
 * @brief Add group for menu vew type. If the current menu view uses the current interface, the menu group is invalidated and the id<FSMenuView> is responsible for all behavior.
 *
 * @param[in]    group        The  group.
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 */
- (void)addMenuItemGroup:(FSMenuItemGroup *)group forMenuViewType:(FSMenuViewType)menuViewType;

/**
 * @brief Insert group  at index . If the current menu view uses the current interface, the menu group is invalidated and the id<FSMenuView> is responsible for all behavior.
 *
 * @param[in]    group        The  group.
 * @param[in]    index                    Index of group in menu view.
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 */
- (void)insertMenuItemGroup:(FSMenuItemGroup *)group atIndex:(NSInteger)index forMenuViewType:(FSMenuViewType)menuViewType;

/**
 * @brief Exchange  group1's index with group2's index .If the current menu view uses the current interface, the menu group is invalidated and the id<FSMenuView> is responsible for all behavior.
 *
 * @param[in]    index1       The  group1's index.
 * @param[in]    index2                     The  group2's index.
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 */
- (void)exchangeMenuItemGroupAtIndex:(NSInteger)index1 withMenuItemGroupAtIndex:(NSInteger)index2 forMenuViewType:(FSMenuViewType)menuViewType;

/**
 * @brief Insert the group before the sibling group. If the current menu view uses the current interface, the menu group is invalidated and the id<FSMenuView> is responsible for all behavior.
 *
 * @param[in]    group                                    The group that needs to be inserted.
 * @param[in]    siblingGroup                     Existing sibling group.
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 */
- (void)insertMenuItemGroup:(FSMenuItemGroup *)group beforeGroup:(FSMenuItemGroup *)siblingGroup forMenuViewType:(FSMenuViewType)menuViewType;

/**
 * @brief Insert the group after the sibling group. If the current menu view uses the current interface, the menu group is invalidated and the id<FSMenuView> is responsible for all behavior.
 *
 * @param[in]    group                                    The group that needs to be inserted.
 * @param[in]    siblingGroup                     Existing sibling group.
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 */
- (void)insertMenuItemGroup:(FSMenuItemGroup *)group afterGroup:(FSMenuItemGroup *)siblingGroup forMenuViewType:(FSMenuViewType)menuViewType;

/**
 * @brief Remove group  for menu view type. If the current menu view uses the current interface, the menu group is invalidated and the id<FSMenuView> is responsible for all behavior.
 *
 * @param[in]    group        The group that need to be removed.
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 */
- (void)removeMenuItemGroup:(FSMenuItemGroup *)group forMenuViewType:(FSMenuViewType)menuViewType;

/**
 * @brief Get groups  for menu vew type. If the current menu view uses the current interface, the menu group is invalidated and the id<FSMenuView> is responsible for all behavior.
 *
 * @param[in]    menuViewType         The view type that supports menu view. Please refer to {@link FSMenuViewTypeXXX} and {@link FSMenuViewType} values and it would be one of these values.
 *
 * @return    The groups.
 */
- (NSArray <FSMenuItemGroup *> *)getMenuItemGroupsForMenuViewType:(FSMenuViewType)menuViewType;


@end

NS_ASSUME_NONNULL_END
