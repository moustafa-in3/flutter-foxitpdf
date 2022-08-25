import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter_foxitpdf/flutter_foxitpdf.dart';
import 'package:file_picker/file_picker.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _platformVersion = 'Unknown';
  int _error = -1;

  String _sn = 'Ly7X9zlkQY4B6ylDjoG2UhkxmNuN08ACdrI+JY90XwFGh0mxA0Z5xQ==';
  String _key =
      'ezJvjl/GrGp39NsXJVWofPUF/oytvG6ZymdCusc77U+yjsFWj4G4wL19E20uF5ntEH9Mkmd93QEtxLG6hVbx/yrBxcskr/mKJoco6OuqqgqTs4OcHniGQYOEmzhmgHiqB32ODuaMrgG04nO92a2A/dVlvtnOhge72OwiTa8gmH5v69/5K+6AqPHun/+nMLWeW6Stnm0QWpRMRE/hxQbT0758L5R6jBSD8zkIPTIpKF+ZzeKTbfx5YbUZ158cKpaqiRcm2cq85lpnhlULsbei09Sr9eTGs9KMSK06kaN7aHdEeRaIVjpiN/GryeRGB6jY4vyX1VteISnlGhSYMbNnPmCdi9w0ypUGwXOY4AF+OF3Oc5l3t62IAcy6B7rnqa928us6Gu0ZjsSxklMjVtKGBb1CuZ5hb/pttyJl07BValAwfPBj01MKYMLGOqVoYiuIdzpzH4KwKmaTCfjg584WuCMu27gI61CVAQ+v12CoIVwPIvAnuqpu7GcscdApqIbV/PoHQ5B/HbHJtV3afP7oVaRLx0sfHCFLKPN7lUuOINC9nEpE4TYH8h+7LBF75oPzyh1Ikfiv77wxf7F0jNphzVsOZNSwYewm+4rMElYANNLMrH5dTbc26sDuRcbdS6Fl5Jhfp5TTNnwlRg0XHetTKpG+rSG3DIxWIXeDzZipHTPXlh11/IEuBe5TFTgdBcRczIZJwaaYRi6Evx0QpYOhF4kFBf0n1s7skYAsx7meyABstzH7Ys3oKlSBztBODySND9mig2KlCVwJMwfCwTMS8523+qycN4ZyAtqDJ/zFmusCksevi90qCafUVdhmJR7VGXMDHKb3S2vLWykHobfQihU7SW9qf7vV8lorwshnhffVB324YsvKZMXxv3Zb0ZJvaVHbmT+Ywm8+JDG649JSZPLg5QfUFe+TgtzI2I01X+bwUfEMTTb0R2x4iZ3ifHA1DdNZ8Dvt6islch93l1AyNjVTaxLgIzF67nteak99G6hmQszqsF3TyV6BLv7dFPghl/8sHmrkoZTF9Q1MPW8wUrgUtNSbd2ltZf0tl6bccsWnP/oZg0fZzOqFQn3XguSq4ndFBrz7rQ6FivmFh/FuRoQubOou/pUhZtBH9X/Pl1Irna8cw/GGtI7NYFsBIwS5Vuj0z+EKlb86s24HFxvyweb1puIczuwgfZaLYwe3jYiBTalIF0V59H1pYjbfhEncwutud5EzLnh+GDi9b/HGqQqIKe7u0ouDBRXA9F+s5S3Lu/UjDf4ibELu5DW6oXYaXKhk5P8RM6+QOpfGHscd';
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
      platformVersion = await FlutterFoxitpdf.platformVersion;
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
    int error;
    try {
      error = await FlutterFoxitpdf.initialize(sn, key);
    } on PlatformException {
      error = -1;
    }
    setState(() {
      _error = error;
    });
  }

  Future<void> openDocument() async {
    FilePickerResult? result = await FilePicker.platform.pickFiles();
    if (result != null) {
      String path = result.files.first.path as String;
      await FlutterFoxitpdf.openDocument(path, '');
    }
  }
}
