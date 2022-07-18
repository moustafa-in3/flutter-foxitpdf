import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'flutterfoxitpdf_method_channel.dart';

abstract class FlutterfoxitpdfPlatform extends PlatformInterface {
  /// Constructs a FlutterfoxitpdfPlatform.
  FlutterfoxitpdfPlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterfoxitpdfPlatform _instance = MethodChannelFlutterfoxitpdf();

  /// The default instance of [FlutterfoxitpdfPlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterfoxitpdf].
  static FlutterfoxitpdfPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterfoxitpdfPlatform] when
  /// they register themselves.
  static set instance(FlutterfoxitpdfPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  Future<int?> initialize(String sn, String key) {
    throw UnimplementedError('initialize() has not been implemented.');
  }

  Future<void> openDocument(String path, String password) {
    throw UnimplementedError('openDocument() has not been implemented.');
  }
}
