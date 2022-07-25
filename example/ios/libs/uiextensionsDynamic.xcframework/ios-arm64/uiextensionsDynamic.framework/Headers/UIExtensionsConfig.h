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
 * @file	UIExtensionsConfig.h
 * @details	UIExtensions modules config allows you to choose modules to load and designate annotation types.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SettingObj : NSObject<NSCoding>
@property (nonatomic, copy, nullable) NSString *icon;
@property (nonatomic, copy, nullable) NSString *textFace;
@property (nonatomic, copy, nullable) NSString *scaleFromUnit;
@property (nonatomic, copy, nullable) NSString *scaleToUnit;
@property (nonatomic, assign) CGFloat textSize;
@property (nonatomic, assign) CGFloat opacity;
@property (nonatomic, assign) float thickness;
@property (nonatomic, assign) unsigned int rotation;
@property (nonatomic, assign) unsigned int scaleFromValue;
@property (nonatomic, assign) unsigned int scaleToValue;
@property (nonatomic, strong, nullable) UIColor *color;
@property (nonatomic, strong, nullable) UIColor *fillColor;
@property (nonatomic, strong, nullable) UIColor *textColor;
@property (nonatomic, assign) BOOL multipleSelection;
@property (nonatomic, assign) BOOL customText;
@end

@interface Annotations : NSObject
@property (nonatomic, assign) BOOL continuouslyAdd;
@property (nonatomic, strong) SettingObj *highlight;
@property (nonatomic, strong) SettingObj *areaHighlight;
@property (nonatomic, strong) SettingObj *underline;
@property (nonatomic, strong) SettingObj *squiggly;
@property (nonatomic, strong) SettingObj *strikeout;
@property (nonatomic, strong) SettingObj *insert;
@property (nonatomic, strong) SettingObj *replace;
@property (nonatomic, strong) SettingObj *line;
@property (nonatomic, strong) SettingObj *rectangle;
@property (nonatomic, strong) SettingObj *oval;
@property (nonatomic, strong) SettingObj *arrow;
@property (nonatomic, strong) SettingObj *pencil;
@property (nonatomic, strong) SettingObj *highlighter;
@property (nonatomic, strong) SettingObj *polygon;
@property (nonatomic, strong) SettingObj *cloud;
@property (nonatomic, strong) SettingObj *polyline;
@property (nonatomic, strong) SettingObj *typewriter;
@property (nonatomic, strong) SettingObj *textbox;
@property (nonatomic, strong) SettingObj *callout;
@property (nonatomic, strong) SettingObj *note;
@property (nonatomic, strong) SettingObj *attachment;
@property (nonatomic, strong) SettingObj *measure;
@property (nonatomic, strong) SettingObj *image;
@property (nonatomic, strong) SettingObj *redaction;
@end

@interface Form : NSObject
@property (nonatomic, strong) SettingObj *textField;
@property (nonatomic, strong) SettingObj *checkBox;
@property (nonatomic, strong) SettingObj *radioButton;
@property (nonatomic, strong) SettingObj *comboBox;
@property (nonatomic, strong) SettingObj *listBox;
@end

@interface UISettingsModel : NSObject
@property (nonatomic, copy) NSString *pageMode;
@property (nonatomic, assign) BOOL continuous;
@property (nonatomic, copy) NSString *colorMode;
@property (nonatomic, copy) NSString *zoomMode;
//to do ..
//@property (nonatomic, assign) BOOL screenLock;
//@property (nonatomic, assign) BOOL autoBrightness;
@property (nonatomic, assign) BOOL fullscreen;
@property (nonatomic, assign) BOOL highlightForm;
@property (nonatomic, assign) BOOL highlightLink;
@property (nonatomic, assign) BOOL disableFormNavigationBar;
@property (nonatomic, strong) UIColor *highlightFormColor;
@property (nonatomic, strong) UIColor *highlightLinkColor;
@property (nonatomic, strong) UIColor *mapForegroundColor;
@property (nonatomic, strong) UIColor *mapBackgroundColor;
@property (nonatomic, strong) UIColor *reflowBackgroundColor;
@property (nonatomic, strong) Annotations *annotations;
@property (nonatomic, strong) Form *form;
@property (nonatomic, strong) SettingObj *signature;
@property (nonatomic, strong) SettingObj *commonlyUsed;
@end

@interface NSObject (UISettingsModel)
+ (instancetype)modelWithDict:(NSDictionary *)dict;
- (id)replaceSettingsWithDict:(NSDictionary *)dict;
+ (NSDictionary *) defaultSettings;
@end

/** @brief Modules config for UIExtensionsManager. */
@interface UIExtensionsConfig : NSObject
/** @brief Whether to load the thumbnail module, set YES to allow users to delete/add/rotate PDF Pages. */
@property (nonatomic, assign) BOOL loadThumbnail;
/** @brief Whether to load the reading bookmark module, set YES to allow users to add/remove their own bookmark.*/
@property (nonatomic, assign) BOOL loadReadingBookmark;
/** @brief Whether to load the PDF outline module, set YES to allow users to view/navigate from the outline in PDF document.*/
@property (nonatomic, assign) BOOL loadOutline;
/** @brief Whether to load the PDF attachment module, set YES to allow users to view the file attachment in PDF document.*/
@property (nonatomic, assign) BOOL loadAttachment;
/** @brief Whether to load the PDF form module, set YES to allow users to fill the form or export/import form data to/from PDF document.*/
@property (nonatomic, assign) BOOL loadForm;
/** @brief Whether to load the PDF signature module, set YES to allow users to sign/verify the signature on PDF document.*/
@property (nonatomic, assign) BOOL loadSignature;
/** @brief Fillsign switch. Default is YES*/
@property (nonatomic, assign) BOOL fillSign;
/** @brief Whether to load the text search module, set YES to allow users to search text on PDF document.*/
@property (nonatomic, assign) BOOL loadSearch;
/** @brief Whether to load the page navigation module, set YES to allow users to navigate pages by inputing page number.*/
@property (nonatomic, assign) BOOL loadPageNavigation;
/** @brief Whether to load the encryption module, set YES to allow users to encrypt the PDF document by password.*/
@property (nonatomic, assign) BOOL loadEncryption;
/** @brief Whether JavaScript is supported,  set YES to allow users to response JavaScript.*/
@property (nonatomic, assign) BOOL runJavaScript;
/** @brief Whether allow user to copy the text on document or not.*/
@property (nonatomic, assign) BOOL copyText;
/** @brief Whether to disable the hyperlink. By default, view control will jump to the link when finger tap on. Set to YES to disable this behaviour.*/
@property (nonatomic, assign) BOOL disableLink;
/** @brief Supported tools. For elements please refer to {@link Tool_Note Tool_XXX} values. Annotation of unsupported types are not interactable. */
@property (nonatomic, strong, nullable) NSMutableSet<NSString *> *tools;
/** @brief More UI settings, internal use only. */
@property (nonatomic, nullable, readonly) UISettingsModel *defaultSettings;
/**
 * @brief Intialize extensions config.
 *
 * @param[in]    data    The JSON data.
 *
 * @return    The extensions config instance.
 */
- (id __nullable)initWithJSONData:(NSData *__nonnull)data;

@end

NS_ASSUME_NONNULL_END
