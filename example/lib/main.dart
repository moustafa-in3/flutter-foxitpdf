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

  String _sn = 'c13unaGfZf+aj91a4pneElkoWjRdm27bAhTBwe2oxuXsstoWbEwLfw==';
  String _key =
      'ezJvjl3CtGp395vOPmXMq9aV4EP8NSoINN+NQHTX2i7VglVhz9CSxqxrHIqqn5HtEPe0kJ8LZsQtUKj1KM96tzKN8Mg0r/mKxLcgqPuunlaAVc2YWWqUKUZSXFhbCwo+8TyK4Df3K2HwiR7ocO+PhiLxgJ9Osyro2rCVlrbl9g3aJVUuzrJs4MPGBUkpic4XsrD4fhC6NIbD8PLUttyKCysawHLqq2Unl8xUPB7vsLtY+hJ6ghff0l0osriQIo0QOI7OSPoHRRFFcfksMxFa9GGkp+pFq/Es2r1uCtUZgtdh9dMqH8kckv2El0aGku5HGCJRza4T7Dh1M2nwe8offw2sxpWl9Dzi74kMKHbCvyrhjyvnb3a9qq2hxslMnTd2ZDC9/kjXxaov7fOsC8Ga+kYpmPk4jPIohEK5g38/3b8eS2oWyhoY7jFGOHOI0ySpGSVL6X5oSe0U847f7sh+GrVX+PXOrHJwU1DW0sXqyv2UMngCqA2/wwJJO9ZpWbN3oG9YYqKH8JmQbOd+sAV8cha6Wegvunp5g8V0VTwA5QNaqVJ8dlt4kSTr0XHizlsD+w/eFTgrD8q7SqH9QFK1myh4STuRy03oce/H5e6bleaccj9dcVsb7+Plo3y4Qer2p6Rfrsd66+WcvRkj5vVy8niRi/wsb9qxK+lTYwqEnCg8lhbtwNtOXjgGrN6scp2HEA2w3AcFrqAzMp4yLkewZh2SaO+S4BrgY5a8AnQ02139lCGCYcgDt/ypYG6OTHXCQzRqVT/2PcEsViy6sBSdPzmpqNF/z3JrIDfaQGhHEC5zR12xhcSRt6V8IC/bv80/qIzqHsudZQqnzKdIhkNo+c/9X8ENzLNGTwkOzEKWdhrS0mcyatQAlT1AmMGNIXxUk61E4fm6u0cfm8zQ5bEKuEj7CCbtLLodh82nCMaFO2VA7HL8J1w110HwBGosyomYwJoLIZ+qnojfPgsGyKLvRVLGMROrhOzDR5nQUH+fTf0dbUMLyBw6fpeO8RKZ98hCk60U+ozKGPR7VTVH24TMsJTP8YY526xp9S70seJrimo+jreMNFFHEaE7XgG+5hMdStB6MfAANEO/gPcDTvq97kZ9ba3m+Ip2lswVun6YzGyecZ2wfBf6M03waSllwuuCfcngApMWiYuHnx+Mmkfvfzwk0wXn+YHQs1GNNuQQ6wffAhl4o7MgRjg4FQ8b5xW0qShfrdWrjQsnBFnoaLhbQ6dj0LVlLfZSU1CjnqKTASVgMNdpFDSIehQmMerHg5ar32s8+TK6lrD5upYTHMCZ';

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
