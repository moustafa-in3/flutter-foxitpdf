import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'flutterfoxitpdf_platform_interface.dart';

/// An implementation of [FlutterfoxitpdfPlatform] that uses method channels.
class MethodChannelFlutterfoxitpdf extends FlutterfoxitpdfPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutterfoxitpdf');

  @override
  Future<String?> getPlatformVersion() async {
    final version =
        await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }

  @override
  Future<int?> initialize(String sn, String key) async {
    final error = await methodChannel.invokeMethod<int>('initialize', {
      'sn': sn,
      'key': key,
    });
    return error;
  }

  @override
  Future<void> openDocument(String path, String password) async {
    return await methodChannel.invokeMethod<void>('openDocument', {
      'path': path,
      'password': password,
    });
  }
}
