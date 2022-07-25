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
 * @file    FileListViewController.h
 * @details    Classes associated with file list view controller. This view controller enable user to view all the PDF files on the document folder, and user may select a PDF file on the view to open it.
 */

#import <FoxitRDK/FSPDFViewControl.h>

/* @brief The delegate for selection on file list.*/
@protocol FSFileSelectDelegate <NSObject>
@required
/* @brief Triggered when a file is selected by user.*/
- (void)didFileSelected:(NSString *_Nonnull)filePath;
@end

/* @brief File list controller to manage the pdf file list in the home directory.*/
@interface FSFileListViewController : UIViewController <IDocEventListener>
/* @brief Delegate for file selection.*/
@property (nonatomic, weak, nullable) id<FSFileSelectDelegate> delegate;
/** @brief The top tool bar on file list view. */
@property (nonatomic, strong, nonnull) UIToolbar *topToolbar;

@end
