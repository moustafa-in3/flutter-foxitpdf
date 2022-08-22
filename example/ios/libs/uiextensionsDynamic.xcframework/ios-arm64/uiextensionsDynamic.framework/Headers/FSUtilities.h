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
 * @file    FSUtilities.h
 * @details    Macros of constants or helper functions. Shared among the public headers.
 */

#if defined(__cplusplus)
    #define FS_EXTERN extern "C"
#else
    #define FS_EXTERN extern
#endif

/** @brief States of extensions manager. */
typedef NS_ENUM(NSUInteger, FSUIManagerState) {
    ///< tag of normal ui state
    FSUIManagerStateNormal = 1,
    ///< tag of reflow ui state
    FSUIManagerStateReflow,
    ///< tag of search ui state
    FSUIManagerStateSearch,
    ///< tag of annottool ui state
    FSUIManagerStateAnnotTool,
    ///< tag of panandzoom state
    FSUIManagerStatePanZoom,
    ///< tag of create form state
    FSUIManagerStateCreateForm,
    ///< tag of panandzoom state
    FSUIManagerStateSpeech,
    ///< tag of fill sign state
    FSUIManagerStateFillSign,
    ///< tag of auto flip
    FSUIManagerStateAutoFlip,
    ///< tag of redaction ui state
    FSUIManagerStateRedaction,
    ///< tag of redaction pdf comparision
    FSUIManagerStateComparision,
    ///< tag of editor state
    FSUIManagerStateEditor
};

/** @brief Customized annotation type on application level. */

FS_EXTERN const FSAnnotType FSAnnotArrowLine;     ///< tag of Arrow custom annot type
FS_EXTERN const FSAnnotType FSAnnotInsert;       ///< tag of Insert custom annot type
FS_EXTERN const FSAnnotType FSAnnotTextbox;      ///< tag of Textbox custom annot type
FS_EXTERN const FSAnnotType FSAnnotCloud;        ///< tag of Cloud custom annot type
FS_EXTERN const FSAnnotType FSAnnotCallout;      ///< tag of Callout custom annot type
FS_EXTERN const FSAnnotType FSAnnotDistance;     ///< tag of Distance custom annot type
FS_EXTERN const FSAnnotType FSAnnotReplace;      ///< tag of Replace custom annot type

typedef NSString *FSStringName;
typedef FSStringName FSToolStringName;
FS_EXTERN FSToolStringName const Tool_Select;         ///< name of select tool
FS_EXTERN FSToolStringName const Tool_Note;             ///< name of note tool
FS_EXTERN FSToolStringName const Tool_Freetext;     ///< name of free text tool
FS_EXTERN FSToolStringName const Tool_Textbox;       ///< name of text box tool
FS_EXTERN FSToolStringName const Tool_Callout;       ///< name of callout tool
FS_EXTERN FSToolStringName const Tool_Pencil;         ///< name of pencil tool
FS_EXTERN FSToolStringName const Tool_Eraser;         ///< name of eraser tool
FS_EXTERN FSToolStringName const Tool_Stamp;           ///< name of stamp tool
FS_EXTERN FSToolStringName const Tool_Insert;         ///< name of insert text tool
FS_EXTERN FSToolStringName const Tool_Replace;       ///< name of replace text tool
FS_EXTERN FSToolStringName const Tool_Attachment; ///< name of attachment tool
FS_EXTERN FSToolStringName const Tool_Signature;   ///< name of signature tool
FS_EXTERN FSToolStringName const Tool_Line;             ///< name of line tool
FS_EXTERN FSToolStringName const Tool_Arrow;           ///< name of arrow line tool
FS_EXTERN FSToolStringName const Tool_Markup;         ///< name of markup tool, which includes highlight squiggly strikeout and underline tools
FS_EXTERN FSToolStringName const Tool_Highlight;   ///< name of highlight tool
FS_EXTERN FSToolStringName const Tool_Squiggly;     ///< name of squiggly tool
FS_EXTERN FSToolStringName const Tool_Strikeout;   ///< name of strikeout tool
FS_EXTERN FSToolStringName const Tool_Underline;   ///< name of underline tool
FS_EXTERN FSToolStringName const Tool_Shape;           ///< name of shape tool, which includes rectangle and oval tools
FS_EXTERN FSToolStringName const Tool_Rectangle;   ///< name of rectangle tool
FS_EXTERN FSToolStringName const Tool_Oval;             ///< name of oval tool
FS_EXTERN FSToolStringName const Tool_Distance;     ///< name of distance tool
FS_EXTERN FSToolStringName const Tool_Image;           ///< name of image tool
FS_EXTERN FSToolStringName const Tool_Polygon;       ///< name of polygon tool
FS_EXTERN FSToolStringName const Tool_Cloud;           ///< name of cloud tool
FS_EXTERN FSToolStringName const Tool_PolyLine;     ///< name of polyline tool
FS_EXTERN FSToolStringName const Tool_Audio;           ///< name of audio tool
FS_EXTERN FSToolStringName const Tool_Video;           ///< name of video tool
FS_EXTERN FSToolStringName const Tool_Link;           ///< name of Link tool
FS_EXTERN FSToolStringName const Tool_Multiple_Selection;           ///< name of MultipleSelection tool
FS_EXTERN FSToolStringName const Tool_Redaction;       ///< name of redact tool
FS_EXTERN FSToolStringName const Tool_Form;              ///< name of form tool
FS_EXTERN FSToolStringName const Tool_Fill_Sign;         ///< name of fill sign tool


typedef FSStringName FSModuleStringName;
FS_EXTERN FSModuleStringName const Module_Thumbnail;        ///< name of thumbnail module
FS_EXTERN FSModuleStringName const Module_Signature;        ///< name of signature module
FS_EXTERN FSModuleStringName const Module_Speech;

/**@brief Defines existing-supplied images  for main tool bar items..*/
typedef int FS_TOOLBAR_ITEM_TAG;
//The back item
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_BACK;
//The more item
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_MORE;
//The search item
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_SEARCH;
//The panel item
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_PANEL;
//The view settings item. When FS_TOOLBAR_ITEM_TAG_VIEW_SETTINGS is hidden, FS_TOOLBAR_ITEM_TAG_VIEW is also hidden.
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_VIEW_SETTINGS;
//The Thumbnai item
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_THUMBNAIL;
//The bookmark item
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_READING_BOOKMARK;
///The home tag
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_HOME;
///The edit tag
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_EDIT;
///The comment tag
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_COMMENT;
///The drawing tag
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_DRAWING;
///The view tag.  When FS_TOOLBAR_ITEM_TAG_VIEW is hidden, FS_TOOLBAR_ITEM_TAG_VIEW_SETTINGS is also hidden.
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_VIEW;
///The form tag
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_FORM;
///The sign tag
FS_EXTERN const FS_TOOLBAR_ITEM_TAG FS_TOOLBAR_ITEM_TAG_SIGN;
