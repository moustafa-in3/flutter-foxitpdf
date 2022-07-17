import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter_foxitpdf/flutter_foxitpdf.dart';
import 'package:file_picker/file_picker.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final _flutterfoxitpdfPlugin = Flutterfoxitpdf();
  String _platformVersion = 'Unknown';
  int _error = -1;

  String _sn = 'YOUR_RDK_SN';
  String _key = 'YOUR_RDK_KEY';
  String _path = '/mnt/sdcard/FoxitSDK/complete_pdf_viewer_guide_android.pdf';

  @override
  void initState() {
    super.initState();
    initPlatformState();

    init(_sn, _key);
    openDocument();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    String platformVersion;
    // Platform messages may fail, so we use a try/catch PlatformException.
    try {
      platformVersion = await _flutterfoxitpdfPlugin.getPlatformVersion() ??
          'Unknown platform version';
    } on PlatformException {
      platformVersion = 'Failed to get platform version.';
    }

    // If the widget was removed from the tree while the asynchronous platform
    // message was in flight, we want to discard the reply rather than calling
    // setState to update our non-existent appearance.
    if (!mounted) return;

    setState(() {
      _platformVersion = platformVersion;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: Text('Running on: $_platformVersion\n'),
        ),
      ),
    );
  }

  Future<void> init(String sn, String key) async {
    int? error;
    try {
      error = await _flutterfoxitpdfPlugin.initialize(sn, key);
    } on PlatformException {
      error = -1;
    }
    setState(() {
      if (error != null) {
        _error = error;
      }
    });
  }

  Future<void> openDocument() async {
    FilePickerResult? result = await FilePicker.platform.pickFiles();
    if (result != null) {
      String path = result.files.first.path as String;
      await _flutterfoxitpdfPlugin.openDocument(path, '');
    }
  }
}
