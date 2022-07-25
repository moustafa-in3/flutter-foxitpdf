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

#import "UIExtensionsConfig.h"

NS_ASSUME_NONNULL_BEGIN
/**@brief The read tool settings type*/
typedef NS_ENUM(NSUInteger, FSReadToolSettingsType) {
    //MARK:edit
    //The text tool settings
    FSReadToolSettingsTypeText = 1,
    //The image tool settings
    FSReadToolSettingsTypeImage,
    //The audio tool settings
    FSReadToolSettingsTypeAudio,
    //The video tool settings
    FSReadToolSettingsTypeVideo,
    //The link tool settings
    FSReadToolSettingsTypeLink,
    
    //MARK:comment
    //The note tool settings
    FSReadToolSettingsTypeNote = 100,
    //The attachments tool settings
    FSReadToolSettingsTypeAttachments,
    //The stamp tool settings
    FSReadToolSettingsTypeStamp,
    //The typewriter tool settings
    FSReadToolSettingsTypeTypewriter,
    //The textbox tool settings
    FSReadToolSettingsTypeTextbox,
    //The callout tool settings
    FSReadToolSettingsTypeCallout,
    //The highlight tool settings
    FSReadToolSettingsTypeHighlight,
    //The underline tool settings
    FSReadToolSettingsTypeUnderline,
    //The squiggly tool settings
    FSReadToolSettingsTypeSquiggly,
    //The strikeout tool settings
    FSReadToolSettingsTypeStrikeout,
    //The replace text tool settings
    FSReadToolSettingsTypeReplaceText,
    //The insert text tool settings
    FSReadToolSettingsTypeInsertText,
    //The area highlight tool settings
    FSReadToolSettingsTypeAreaHighlight,
    //The measure tool settings
    FSReadToolSettingsTypeMeasure,
    //The image annotation tool settings
    FSReadToolSettingsTypeImageAnnotation,
    
    //MARK:drawing
    //The pencil tool settings
    FSReadToolSettingsTypePencil = 200,
    //The highlighter tool settings
    FSReadToolSettingsTypeHighlighter,
    //The eraser tool settings
    FSReadToolSettingsTypeEraser,
    //The rectangele tool settings
    FSReadToolSettingsTypeRectangle,
    //The oval tool settings
    FSReadToolSettingsTypeOval,
    //The line tool settings
    FSReadToolSettingsTypeLine,
    //The arrow tool settings
    FSReadToolSettingsTypeArrow,
    //The polygon tool settings
    FSReadToolSettingsTypePolygon,
    //The polyLine tool settings
    FSReadToolSettingsTypePolyLine,
    //The cloud tool settings
    FSReadToolSettingsTypeCloud,
    
    //MARK:form
    //The text filed tool settings
    FSReadToolSettingsTypeTextField = 300,
    //The check box tool settings
    FSReadToolSettingsTypeCheckBox,
    //The radio button tool settings
    FSReadToolSettingsTypeRadioButton,
    //The combo box tool settings
    FSReadToolSettingsTypeComboBox,
    //The list box tool settings
    FSReadToolSettingsTypeListBox,
    //The signature field tool settings
    FSReadToolSettingsTypeSignatureField,
    
    //MARK:fill&sign
    //The fill sign text tool settings
    FSReadToolSettingsTypeFillSignText = 400,
    //The fill sign seg text tool settings
    FSReadToolSettingsTypeFillSignSegText,
    //The fill sign profile text tool settings
    FSReadToolSettingsTypeFillSignProfile,
    //The fill sign check mark tool settings
    FSReadToolSettingsTypeFillSignCheckMark,
    //The fill sign cross mark tool settings
    FSReadToolSettingsTypeFillSignCrossMark,
    //The fill sign sign dot tool settings
    FSReadToolSettingsTypeFillSignDot,
    //The fill sign line tool settings
    FSReadToolSettingsTypeFillSignLine,
    //The fill sign round rectangle tool settings
    FSReadToolSettingsTypeFillSignRoundRectangle,
    
    //The digital signature tool settings
    FSReadToolSettingsTypeDigitalSignature = 500,
    
    //MARK:supplement
    //The redact tool settings
    FSReadToolSettingsTypeRedact,
};

/**@brief The read tool item type*/
typedef NS_ENUM(NSUInteger, FSReadToolbarItemType) {
    //This item is an existing type
    FSReadToolbarItemTypeExist,
    //This item is custom type
    FSReadToolbarItemTypeCustom,
};

@interface FSReadToolSettings : SettingObj<NSCopying>
/**@brief Get the settings color. If it doesn't exist, it will be 0.*/
@property (nonatomic, assign, readonly) unsigned int settingsColor;
/**@brief Set/Get the note icon.Only FSReadToolSettingsTypeNote is effective. If it doesn't exist, it will be -1.*/
@property (nonatomic, assign) int noteIcon;
/**@brief Set/Get the note icon.Only FSReadToolSettingsTypeStamp is effective. If it doesn't exist, it will be -1.*/
@property (nonatomic, assign) int stampIcon;
/**@brief Set/Get the stamp icon.Only FSReadToolSettingsTypeAttachments is effective. If it doesn't exist, it will be -1.*/
@property (nonatomic, assign) int attachmentIcon;
/**@brief Set/Get the eraser  line width.Only FSReadToolSettingsTypeEraser is effective. If it doesn't exist, it will be -1.*/
@property (nonatomic, assign) float eraserLineWidth;
/**@brief Set/Get the screen rotation.Only FSReadToolSettingsTypeImageAnnotation is effective. If it doesn't exist, it will be FSRotationUnknown.*/
@property (nonatomic, assign) FSRotation screenAnnotRotation;
/**@brief Set/Get the measure unit.Only FSReadToolSettingsTypeMeasure is effective. If it doesn't exist, it will be nil.*/
@property (nonatomic, copy) NSString *distanceUnit;
/**@brief Get the read tool item type. Please refer to {@linkFSReadToolSettingsTypeXXX} and {@link FSReadToolSettingsType} values and it would be one of these values..*/
@property (nonatomic, assign, readonly) FSReadToolSettingsType settingsType;

/** @brief Initialization method
 *
 *  @param[in]    type         The read tool item type.Please refer to {@linkFSReadToolSettingsTypeXXX} and {@link FSReadToolSettingsType} values and it would be one of these values.
 *
 *  @return       The read tool settings.
 */
- (instancetype)initWithToolSettingType:(FSReadToolSettingsType)type;

/** @brief Initialization method
 *
 *  @param[in]    type         The read tool item type.Please refer to {@linkFSReadToolSettingsTypeXXX} and {@link FSReadToolSettingsType} values and it would be one of these values.
 *
 *  @param[in]    extensionsManager        The current UIExtensionsManager object. The default configuration in UIExtensionsManager will be used.
 *
 *  @return       The read tool settings.
 */
- (instancetype)initWithToolSettingType:(FSReadToolSettingsType)type extensionsManager:(UIExtensionsManager *)extensionsManager;

@end

@class FSMainToolbarItem;
@interface FSReadToolbarItem : NSObject
/**@brief Get the custom Item. If it doesn't exist, it will be nil*/
@property (nonatomic, strong, readonly, nullable) FSMainToolbarItem *customItem;
/**@brief Get the tool settings Item. If it doesn't exist, it will be nil*/
@property (nonatomic, strong, readonly, nullable) FSReadToolSettings *toolSettings;
/**@brief Get the tool settings type. If toolSettings doesn't exist, it will be 0*/
@property (nonatomic, assign, readonly) FSReadToolSettingsType settingsType;
/**@brief Get the current read tool item type*/
@property (nonatomic, assign, readonly) FSReadToolbarItemType readToolbarItemType;
/**@brief Get the current  item property color, If it doesn't exist, it will be nil*/
@property (nonatomic, strong, readonly, nullable) UIColor *propertyColor;
/**@brief A Boolean value indicating whether the item is enabled*/
@property (nonatomic, assign) BOOL enabled;

/** @brief Initialization method
 *
 *  @param[in]    customItem         Create your own item.
 *
 *  @return       The read tool item.
 */
- (instancetype)initWithCustomItem:(FSMainToolbarItem *)customItem;
/** @brief Initialization method
 *
 *  @param[in]    settingType      The read tool settings .Please refer to {@linkFSReadToolSettingsTypeXXX} and {@link FSReadToolSettingsType} values and it would be one of these values.
 *
 *  @return       The read tool item.
 */
- (instancetype)initWithToolSettingType:(FSReadToolSettingsType)settingType;
/** @brief Initialization method
 *
 *
 *  @param[in]    toolSettings       The tool settings. The item is created with the tool settings passed in.
 *
 *  @return       The read tool item.
 */
- (instancetype)initWithToolSettings:(FSReadToolSettings *)toolSettings;
/** @brief Replace  tool settings,It is valid only if the control is not initialized.
 *
 *
 *  @param[in]    settings       The tool settings.
 *
 *  @return       Whether the replacement is successful.
 */
- (BOOL)replaceSettings:(FSReadToolSettings *)settings;
@end

NS_ASSUME_NONNULL_END
