import 'flutterfoxitpdf_platform_interface.dart';

class Flutterfoxitpdf {
  Future<String?> getPlatformVersion() {
    return FlutterfoxitpdfPlatform.instance.getPlatformVersion();
  }

  Future<int?> initialize(String sn, String key) {
    return FlutterfoxitpdfPlatform.instance.initialize(sn, key);
  }

  Future<void> openDocument(String path, String password) {
    return FlutterfoxitpdfPlatform.instance.openDocument(path, password);
  }
}
