//
//  Generated file. Do not edit.
//

// clang-format off

#import "GeneratedPluginRegistrant.h"

#if __has_include(<file_picker/FilePickerPlugin.h>)
#import <file_picker/FilePickerPlugin.h>
#else
@import file_picker;
#endif

#if __has_include(<flutter_foxitpdf/FlutterFoxitpdfPlugin.h>)
#import <flutter_foxitpdf/FlutterFoxitpdfPlugin.h>
#else
@import flutter_foxitpdf;
#endif

@implementation GeneratedPluginRegistrant

+ (void)registerWithRegistry:(NSObject<FlutterPluginRegistry>*)registry {
  [FilePickerPlugin registerWithRegistrar:[registry registrarForPlugin:@"FilePickerPlugin"]];
  [FlutterFoxitpdfPlugin registerWithRegistrar:[registry registrarForPlugin:@"FlutterFoxitpdfPlugin"]];
}

@end
