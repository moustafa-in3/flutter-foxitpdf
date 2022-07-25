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

typedef NSUInteger FSLocalizationLanguageOptional;

NS_ASSUME_NONNULL_BEGIN

/**
 * You can use this to switch the current locale.
 * Current sdk supports 11 languages,you can switch languages by the following currentLanguageID.
 * FSLocalizationLanguageOptionalEnglish(int = 0) for English.
 * FSLocalizationLanguageOptionalChineseSimplified(int = 1) for Chinese simplified.
 * FSLocalizationLanguageOptionalChineseTraditional(int = 2) for Chinese traditional.
 * FSLocalizationLanguageOptionalKorean(int = 3) for Korean.
 * FSLocalizationLanguageOptionalSpanishLatinAmerica(int = 4) for Spanish Latin America.
 * FSLocalizationLanguageOptionalFrench(int = 5) for French.
 * FSLocalizationLanguageOptionalGerman(int = 6) for German.
 * FSLocalizationLanguageOptionalRussian (int = 7) for Russian
 * FSLocalizationLanguageOptionalPortugueseBrazil(int = 8) for Portuguese Brazil.
 * FSLocalizationLanguageOptionalItalian(int = 9) for Italian
 * FSLocalizationLanguageOptionalDutch(int = 10) for Dutch
 */

extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalEnglish;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalChineseSimplified;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalChineseTraditional;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalKorean;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalSpanishLatinAmerica;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalFrench;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalGerman;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalRussian;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalPortugueseBrazil;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalItalian;
extern const FSLocalizationLanguageOptional FSLocalizationLanguageOptionalDutch;

/**
 *******************************************************************************
 If you want to use some kind of our existing language.
 Example:
    [FSLocalization setCurrentLanguage:FSLocalizationLanguageOptionalEnglish];
 
 *******************************************************************************
 If you want to add your own language resources.
 Example:
    [FSLocalization addLanguage:11 table:@"your tableName" languageAbbr:@"your language resources"];
    [FSLocalization setCurrentLanguage:11];//If you want to follow system changes, remove this line of code.
 
 *******************************************************************************
 You can also cover our language.
 Example:
    [FSLocalization addLanguage:FSLocalizationLanguageOptionalEnglish table:@"your tableName" languageAbbr:@"your language resources"];
    [FSLocalization setCurrentLanguage:FSLocalizationLanguageOptionalEnglish];//If you want to follow system changes, remove this line of code.
 */

@interface FSLocalization : NSObject

/** @brief  Optional language set and get. The default is 0~10. This is a static variable. You need to call the setup method before initialization or you may not be able to reach the expected */
@property (class, nonatomic, assign) NSUInteger currentLanguage;
/** @brief  Language branches are allowed. For example "es" can use "es-419" ,the defualt is YES*/
@property (class, nonatomic, assign) BOOL allowLanguageBranch;
/**
 * @brief Add the languages you want to support. You need to call the setup method before initialization or you may not be able to reach the expected.
 *
 * @param[in]    language     The language of your custom ID, unique, you can override our definition.
 *
 * @param[in]    tableName    The receiIver’s string table to search, Can't be empty.
 *
 * @param[in]    abbr         Abbreviation for language resources.For example, the prefix "en" of "en.lproj".
 */
+ (void)addLanguage:(NSUInteger)language table:(nonnull NSString *)tableName languageAbbr:(nonnull NSString *)abbr;

/**
 * @brief      Get language abbreviation;
 *
 * @return     Such as en, zh-Hans, zh-Hant, ko.
 */
+ (NSString *)languageAbbr;

/**
 * @brief      Get the receiver’s string table to search;
 *
 * @return     For example, the prefix "Localizable" of "Localizable.strings"
 */
+ (NSString *)tableName;
@end

NS_ASSUME_NONNULL_END
