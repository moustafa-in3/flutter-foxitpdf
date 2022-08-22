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

@class FSReadToolbarItem;
/**@brief The item is in the bar*/
typedef NS_ENUM(NSInteger, FSMainToolbarItemPosition) {
    ///The item is on the left
    FSMainToolbarItemPositionLeft = 0,
    ///The item is on the center
    FSMainToolbarItemPositionCenter,
    ///The item is on the right
    FSMainToolbarItemPositionRight,
};
/**@brief The tool tag*/
typedef NS_ENUM(NSUInteger, FSMainTopbarToolTag) {
    ///The home tag
    FSMainTopbarToolTagHome,
    ///The edit tag
    FSMainTopbarToolTagEdit,
    ///The comment tag
    FSMainTopbarToolTagComment,
    ///The drawing tag
    FSMainTopbarToolTagDrawing,
    ///The view tag
    FSMainTopbarToolTagView,
    ///The form tag
    FSMainTopbarToolTagForm,
    ///The sign tag
    FSMainTopbarToolTagSign,
    ///The custom tag
    FSMainTopbarToolTagCustom,
};

/**@brief Defines existing-supplied images  for main tool bar items..*/
typedef NS_ENUM(NSUInteger, FSMainToolbarItemType) {
    //The unknown item
    FSMainToolbarItemTypeUnknown = 0,
    //The bark item
    FSMainToolbarItemTypeBack,
    //The more item
    FSMainToolbarItemTypeMore,
    //The search item
    FSMainToolbarItemTypeSearch,
    //The pan item
    FSMainToolbarItemTypePan,
    //The add tool item
    FSMainToolbarItemTypeAddTool,
    //The redo item
    FSMainToolbarItemTypeRedo,
    //The undo item
    FSMainToolbarItemTypeUndo,
    //The property item
    FSMainToolbarItemTypeProperty,
    //The multi-select item
    FSMainToolbarItemTypeMultiSelect,
    //The divide item
    FSMainToolbarItemTypeDivide,
    
    //The panel item
    FSMainToolbarItemTypePanel,
    //The view settings item
    FSMainToolbarItemTypeViewSettings,
    //The Thumbnai item
    FSMainToolbarItemTypeThumbnail,
    //The bookmark item
    FSMainToolbarItemTypeReadingBookmark,
};

/**@brief The subbar is in the bar*/
typedef NS_ENUM(NSUInteger, FSTopbarSubitemContentViewPosition) {
    ///The subbar is on the top
    FSTopbarSubitemContentViewPositionTop,
    ///The subbar is on the left
    FSTopbarSubitemContentViewPositionLeft,
    ///The subbar is on the right
    FSTopbarSubitemContentViewPositionRight,
};

@interface FSMainToolbarItem : NSObject
/**@brief Disable the default initialization.*/
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**@brief Get the  existing-supplied item. Please refer to {@link FSMainToolbarItemTypeXXX} and {@link FSMainToolbarItemType} values and it would be one of these values..*/
@property (nonatomic, assign, readonly) FSMainToolbarItemType itemType;
/**@brief Get/Set the  add spacing to the toolbar.*/
@property (nonatomic, assign) CGFloat spacing;
/**@brief Get/Set the  add  width to the toolbar.*/
@property (nonatomic, assign) CGFloat width;   

/** @brief Initialization method
 *
 *  @param[in]    customView         The custom view .
 *  @return       The main toolbar Item instance.
 */
- (instancetype)initWithCustomView:(UIView *)customView;
@end

@interface FSMainToolbar : NSObject
/**@brief Disable the default initialization.*/
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**@brief Get/Set the items displayed on the toolbar left.*/
@property (nonatomic, copy, nullable) NSArray<FSMainToolbarItem *> *itemsForPositionLeft;
/**@brief Get/Set the items displayed on the toolbar center.*/
@property (nonatomic, copy, nullable) NSArray<FSMainToolbarItem *> *itemsForPositionCenter;
/**@brief Get/Set the items displayed on the toolbar right.*/
@property (nonatomic, copy, nullable) NSArray<FSMainToolbarItem *> *itemsForPositionRight;

/**@brief Get the  the toolbar content view.
 *
 *  @return  The toolbar content view.    It's a subclass of UIStackView,  the axis of the default is UILayoutConstraintAxisVertical
 */
- (__kindof UIStackView *)getToolbarContentView;

/**@brief Add item at position, Please refer to {@linkFSMainToolbarItemPositionXXX} and {@link FSMainToolbarItemPosition} values and it would be one of these values..*/
- (void)addItem:(FSMainToolbarItem *)item atPosition:(FSMainToolbarItemPosition)position;
/**@brief Removes the index item at position, Please refer to {@linkFSMainToolbarItemPositionXXX} and {@link FSMainToolbarItemPosition} values and it would be one of these values..*/
- (void)removeItemAtPosition:(FSMainToolbarItemPosition)position index:(NSUInteger)index;
/**@brief Removes  item at position, Please refer to {@linkFSMainToolbarItemPositionXXX} and {@link FSMainToolbarItemPosition} values and it would be one of these values..*/
- (void)removeItem:(FSMainToolbarItem *)item atPosition:(FSMainToolbarItemPosition)position;
@end

@interface FSMainTopbarToolTagItem : NSObject
/**@brief Disable the default initialization.*/
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**@brief Get/Set the item title.*/
@property (nonatomic, copy) NSString *title;
/**@brief Get/Set the item image.*/
@property (nonatomic, strong) UIImage *image;

/**@brief Get/Set the read Items displayed on the toolbar.*/
@property (nonatomic, copy, nullable) NSArray<FSReadToolbarItem *> *readToolbarItems;
/**@brief Get/Set the main Items displayed on the toolbar.*/
@property (nonatomic, copy, nullable) NSArray<FSMainToolbarItem *> *mainToolbarItems;

/**@brief Get the  existing-supplied tool tag. Please refer to {@link FSMainTopbarToolTagXXX} and {@link FSMainTopbarToolTag} values and it would be one of these values..*/
@property (nonatomic, assign, readonly) FSMainTopbarToolTag toolTag;

/** @brief Initialization method
 *
 *  @param[in]    toolTag         The tool tag.
 *
 *  @param[in]    readToolbarItems        The read Items displayed on the toolbar
 *
 *  @return       The main topbar tool tag Item.
 */
+ (instancetype)ItemWithToolTag:(FSMainTopbarToolTag)toolTag readToolbarItems:(nullable NSArray<FSReadToolbarItem *> *)readToolbarItems;
@end

@interface FSMainTopbar : FSMainToolbar
/**@brief Disable this method.*/
@property (nonatomic, copy, nullable) NSArray<FSMainToolbarItem *> *itemsForPositionCenter NS_UNAVAILABLE;
/**@brief Get/Set the main tag Items displayed on the toolbar.*/
@property (nonatomic, copy, nullable) NSArray<FSMainTopbarToolTagItem *> *tagItems;
/**@brief Get the current tag Item */
@property (nonatomic, strong, readonly) FSMainTopbarToolTagItem *currentTagItem;
/**@brief Get the subtoolbar position. Please refer to {@link FSTopbarSubitemContentViewPositionXXX} and {@link FSTopbarSubitemContentViewPosition} values and it would be one of these values..*/
@property (nonatomic, assign) FSTopbarSubitemContentViewPosition subitemContentPosition;
/**@brief Get/Set the subview to contview.*/
@property (nonatomic, strong, nullable) __kindof UIView *attachView;
/**@brief Reset the tag Item in order to update on the view.Calling this method causes the current toolbar to be updated immediately*/
- (void)resetCurrentTagItem;
@end

@interface FSMainBottombar : FSMainToolbar
/**@brief Disable these methods.*/
@property (nonatomic, copy, nullable) NSArray<FSMainToolbarItem *> *itemsForPositionLeft NS_UNAVAILABLE;
@property (nonatomic, copy, nullable) NSArray<FSMainToolbarItem *> *itemsForPositionRight NS_UNAVAILABLE;

/**@brief Whether to evenly distribute items across the toolbar.*/
@property (nonatomic, assign, getter=isAverage) BOOL average;
@end

NS_ASSUME_NONNULL_END
